#!/usr/bin/env python

# from https://wiki.python.org/moin/TcpCommunication
import socket


TCP_IP = '127.0.0.1'
# or '0.0.0.0' for universal ip
TCP_PORT = 5005
# or 0 for universal port
BUFFER_SIZE = 20  # Normally 1024, but we want fast response

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

conn, addr = s.accept()
print 'Connection address:', addr
while 1:
    data = conn.recv(BUFFER_SIZE)
    if not data: break
    print "received data:", data
    conn.send(data)  # echo
conn.close()
