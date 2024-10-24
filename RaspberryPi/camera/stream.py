import io
import logging
import socketserver
from threading import Condition
from http.server import HTTPServer, BaseHTTPRequestHandler
import cv2
from picamera2 import Picamera2

#Make sure to change this if Pi's IP address changes
HOST=   "0.0.0.0" # I think 0.0.0.0 should always work?
capture = Picamera2()
capture.start()

# Set some stuff, might help but not necessary

PORT = 9000
#PAGE="""\
#<html>
#<head>
#<title>Raspberry Pi - Surveillance Camera</title>
#</head>
#<body>
#<center><h1>Raspberry Pi - Surveillance Camera</h1></center>
#<center><img src="stream.mjpg" width="640" height="480"></center>
#</body>
#</html>
#"""

class StreamHTTP(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'multipart/x-mixed-replace; boundary=--jpgboundary')
        self.end_headers()

        while True:
            img = capture.capture_array()
            img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB) 

            r, buf = cv2.imencode(".jpg", img)
            self.wfile.write("--jpgboundary\r\n".encode())
            self.send_header('Content-type', 'image/jpeg')
            self.send_header('Content-length', str(len(buf)))
            self.end_headers()
            self.wfile.write(bytearray(buf))
            self.wfile.write('\r\n'.encode())

server = HTTPServer((HOST,PORT), StreamHTTP)
server.serve_forever()
server.server_close()

