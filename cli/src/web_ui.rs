use super::wasm;
use std::fs;
use std::net::TcpListener;
use std::path::Path;
use std::str::FromStr;
use tiny_http::{Header, Response, Server};
use webbrowser;

const PLAYGROUND_JS: &'static [u8] = include_bytes!("../../docs/assets/js/playground.js");
const LIB_JS: &'static [u8] = include_bytes!("../../lib/binding_web/tree-sitter.js");
const LIB_WASM: &'static [u8] = include_bytes!("../../lib/binding_web/tree-sitter.wasm");
const HTML: &'static [u8] = include_bytes!("./web_ui.html");

pub fn serve(grammar_path: &Path) {
    let port = get_available_port().expect("Couldn't find an available port");
    let url = format!("127.0.0.1:{}", port);
    let server = Server::http(&url).expect("Failed to start web server");
    let grammar_name = wasm::get_grammar_name(&grammar_path.join("src"))
        .map_err(|e| format!("Failed to get wasm filename: {:?}", e))
        .unwrap();
    let language_wasm = fs::read(format!("./tree-sitter-{}.wasm", grammar_name)).unwrap();

    webbrowser::open(&format!("http://127.0.0.1:{}", port))
        .map_err(|e| format!("Failed to open '{}' in a web browser. Error: {}", url, e))
        .unwrap();

    let html_header = Header::from_str("Content-type: text/html").unwrap();
    let js_header = Header::from_str("Content-type: application/javascript").unwrap();
    let wasm_header = Header::from_str("Content-type: application/wasm").unwrap();

    for request in server.incoming_requests() {
        let (body, header) = match request.url() {
            "/" => (HTML, &html_header),
            "/playground.js" => (PLAYGROUND_JS, &js_header),
            "/tree-sitter.js" => (LIB_JS, &js_header),
            "/tree-sitter.wasm" => (LIB_WASM, &wasm_header),
            "/tree-sitter-parser.wasm" => (language_wasm.as_slice(), &wasm_header),
            _ => {
                request
                    .respond(Response::from_string("Not found").with_status_code(404))
                    .expect("Failed to write HTTP response");
                continue;
            }
        };
        let response = Response::from_string("")
            .with_data(body, Some(body.len()))
            .with_header(header.clone());
        request
            .respond(response)
            .expect("Failed to write HTTP response");
    }
}

fn get_available_port() -> Option<u16> {
    (8000..12000).find(port_is_available)
}

fn port_is_available(port: &u16) -> bool {
    TcpListener::bind(("127.0.0.1", *port)).is_ok()
}
