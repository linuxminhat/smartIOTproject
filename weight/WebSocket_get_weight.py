import websocket
import json

WebSocket = websocket.WebSocket()
WebSocket.connect("ws://192.168.178.245")
# WebSocket.connect("ws://192.168.178.246")


def get_weight(WebSocket):
    WebSocket.println(float(weight / 1000, 3))
    WebSocket.send(json.dumps({"command": "get_weight"}))
    return float(WebSocket.recv())

if __name__ == "__main__":
    print(get_weight(WebSocket))
