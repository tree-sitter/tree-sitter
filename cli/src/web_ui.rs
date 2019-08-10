use super::error::Error;
use super::wasm;
use std::fs;
use std::net::TcpListener;
use std::path::Path;
use std::str::FromStr;
use tiny_http::{Header, Response, Server};
use webbrowser;

const HTML: &'static str = include_str!("./web_ui.html");
const PLAYGROUND_JS: &'static [u8] = include_bytes!("../../docs/assets/js/playground.js");

#[cfg(unix)]
const LIB_JS: &'static [u8] = include_bytes!("../../lib/binding_web/tree-sitter.js");
#[cfg(unix)]
const LIB_WASM: &'static [u8] = include_bytes!("../../lib/binding_web/tree-sitter.wasm");

#[cfg(windows)]
const LIB_JS: &'static [u8] = &[];
#[cfg(windows)]
const LIB_WASM: &'static [u8] = &[];

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

    let html = HTML
        .replace("THE_LANGUAGE_NAME", &grammar_name)
        .into_bytes();
    let html_header = Header::from_str("Content-Type: text/html").unwrap();
    let js_header = Header::from_str("Content-Type: application/javascript").unwrap();
    let wasm_header = Header::from_str("Content-Type: application/wasm").unwrap();

    for request in server.incoming_requests() {
        let res = match request.url() {
            "/" => response(&html, &html_header),
            "/playground.js" => response(PLAYGROUND_JS, &js_header),
            "/tree-sitter-parser.wasm" => response(&language_wasm, &wasm_header),
            "/tree-sitter.js" => {
                if cfg!(windows) {
                    redirect("https://tree-sitter.github.io/tree-sitter.js")
                } else {
                    response(LIB_JS, &js_header)
                }
            }
            "/tree-sitter.wasm" => {
                if cfg!(windows) {
                    redirect("https://tree-sitter.github.io/tree-sitter.wasm")
                } else {
                    response(LIB_WASM, &wasm_header)
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
