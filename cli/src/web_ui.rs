use super::error::Error;
use super::wasm;
use std::env;
use std::fs;
use std::net::TcpListener;
use std::path::{Path, PathBuf};
use std::str::FromStr;
use tiny_http::{Header, Response, Server};
use webbrowser;

macro_rules! resource {
    ($name: tt, $path: tt) => {
        fn $name(tree_sitter_dir: &Option<PathBuf>) -> Vec<u8> {
            if let Some(tree_sitter_dir) = tree_sitter_dir {
                fs::read(tree_sitter_dir.join($path)).unwrap()
            } else {
                include_bytes!(concat!("../../", $path)).to_vec()
            }
        }
    };
}

macro_rules! posix_resource {
    ($name: tt, $path: tt) => {
        #[cfg(unix)]
        fn $name(tree_sitter_dir: &Option<PathBuf>) -> Vec<u8> {
            if let Some(tree_sitter_dir) = tree_sitter_dir {
                fs::read(tree_sitter_dir.join($path)).unwrap()
            } else {
                include_bytes!(concat!("../../", $path)).to_vec()
            }
        }

        #[cfg(windows)]
        fn $name(_: &Option<PathBuf>) -> Vec<u8> {
            Vec::new()
        }
    };
}

resource!(get_main_html, "cli/src/web_ui.html");
resource!(get_playground_js, "docs/assets/js/playground.js");
posix_resource!(get_lib_js, "lib/binding_web/tree-sitter.js");
posix_resource!(get_lib_wasm, "lib/binding_web/tree-sitter.wasm");

pub fn serve(grammar_path: &Path) {
    let port = get_available_port().expect("Couldn't find an available port");
    let url = format!("127.0.0.1:{}", port);
    let server = Server::http(&url).expect("Failed to start web server");
    let grammar_name = wasm::get_grammar_name(&grammar_path.join("src"))
        .map_err(Error::wrap(|| "Failed to get wasm filename"))
        .unwrap();
    let wasm_filename = format!("tree-sitter-{}.wasm", grammar_name);
    let language_wasm = fs::read(grammar_path.join(&wasm_filename))
        .map_err(Error::wrap(|| {
            format!(
                "Failed to read {}. Run `tree-sitter build-wasm` first.",
                wasm_filename
            )
        }))
        .unwrap();

    webbrowser::open(&format!("http://127.0.0.1:{}", port))
        .map_err(Error::wrap(|| {
            format!("Failed to open '{}' in a web browser", url)
        }))
        .unwrap();

    let tree_sitter_dir = env::var("TREE_SITTER_BASE_DIR").map(PathBuf::from).ok();
    let main_html = String::from_utf8(get_main_html(&tree_sitter_dir))
        .unwrap()
        .replace("THE_LANGUAGE_NAME", &grammar_name)
        .into_bytes();
    let playground_js = get_playground_js(&tree_sitter_dir);
    let lib_js = get_lib_js(&tree_sitter_dir);
    let lib_wasm = get_lib_wasm(&tree_sitter_dir);

    let html_header = Header::from_str("Content-Type: text/html").unwrap();
    let js_header = Header::from_str("Content-Type: application/javascript").unwrap();
    let wasm_header = Header::from_str("Content-Type: application/wasm").unwrap();

    for request in server.incoming_requests() {
        let res = match request.url() {
            "/" => response(&main_html, &html_header),
            "/playground.js" => response(&playground_js, &js_header),
            "/tree-sitter-parser.wasm" => response(&language_wasm, &wasm_header),
            "/tree-sitter.js" => {
                if cfg!(windows) {
                    redirect("https://tree-sitter.github.io/tree-sitter.js")
                } else {
                    response(&lib_js, &js_header)
                }
            }
            "/tree-sitter.wasm" => {
                if cfg!(windows) {
                    redirect("https://tree-sitter.github.io/tree-sitter.wasm")
                } else {
                    response(&lib_wasm, &wasm_header)
                }
            }
            _ => response(b"Not found", &html_header).with_status_code(404),
        };
        request.respond(res).expect("Failed to write HTTP response");
    }
}

fn redirect<'a>(url: &'a str) -> Response<&'a [u8]> {
    Response::empty(302)
        .with_data("".as_bytes(), Some(0))
        .with_header(Header::from_bytes("Location", url.as_bytes()).unwrap())
}

fn response<'a>(data: &'a [u8], header: &Header) -> Response<&'a [u8]> {
    Response::empty(200)
        .with_data(data, Some(data.len()))
        .with_header(header.clone())
}

fn get_available_port() -> Option<u16> {
    (8000..12000).find(port_is_available)
}

fn port_is_available(port: &u16) -> bool {
    TcpListener::bind(("127.0.0.1", *port)).is_ok()
}
