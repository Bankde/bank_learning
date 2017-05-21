#!/usr/bin/env python
"""
Very simple HTTP server in python.
Usage::
    ./dummy-web-server.py [<port>]
Send a GET request::
    curl http://localhost
Send a HEAD request::
    curl -I http://localhost
Send a POST request::
    curl -d "foo=bar&bin=baz" http://localhost
"""
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import urlparse

class myServer(BaseHTTPRequestHandler):
    def _set_headers(self, code=200):
        if code == 200:
            self.send_response(200)
        elif code == 404:
            self.send_response(404)
        else:
            self.send_response(code)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        parsed_path = urlparse.urlparse(self.path)
        # ParseResult(scheme='', netloc='', path='/test/hi', params='', query='a=b', fragment='')
        if parsed_path.path == "/index.html" or parsed_path.path == "/":
            self._set_headers(200)
            f = file("index.html", "r")
            for line in f:
                self.wfile.write(line)
        else:
            self._set_headers(404)
            self.wfile.write("Page not found: %s. <a href=\"/\">Click here to continue</a>" % (parsed_path.path))

    def do_HEAD(self):
        self._set_headers()
        
    def do_POST(self):
        # Doesn't do anything with posted data
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        print post_data
        self._set_headers()
        self.wfile.write("<html><body><h1>hello!</h1></body></html>")
        
def run(server_class=HTTPServer, handler_class=myServer, port=80):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print 'Starting httpd...'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()
