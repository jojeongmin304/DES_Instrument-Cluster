import can
import socket
import os
import json
import time
import ensure_can_interface

SOCKET_PATH = "/tmp/mysocket"
can_interface = 'can1'
bitrate = 50000
ensure_can_interface(can_interface, bitrate)


bus = can.interface.Bus(can_interface, bustype='socketcan')



# Clean up any existing socket file
if os.path.exists(SOCKET_PATH):
    os.remove(SOCKET_PATH)

# Create a UNIX socket
server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server.bind(SOCKET_PATH)
server.listen(1)
print("Waiting for connection...")

conn, _ = server.accept()
print("Client connected.")

try:
    while True:
        msg = bus.recv(1.0)  # timeout 1 sec
        if msg is not None:
            can_data = {
                'id': msg.arbitration_id,
                'dlc': msg.dlc,
                'data': list(msg.data),
                'timestamp': msg.timestamp
            }
            json_msg = json.dumps(can_data) + "\n"
            conn.sendall(json_msg.encode('utf-8'))
        else:
            time.sleep(0.01)
except KeyboardInterrupt:
    print("Stopping server.")
finally:
    conn.close()
    server.close()
    os.remove(SOCKET_PATH)
