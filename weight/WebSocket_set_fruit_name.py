import websocket
import json
from websockets.client import connect

WebSocket = websocket.WebSocket()
WebSocket.connect("ws://192.168.178.245")
# WebSocket.connect("ws://192.168.178.246")


def set_fruit_name(WebSocket):
    WebSocket.send(json.dumps({"command": "set_fruit_name", "fruit_name": "THANH LONG"}))

if __name__ == "__main__":
    set_fruit_name(WebSocket)


# import json
# import asyncio
# from websockets.client import connect

# async def set_fruit_name():
#     async with connect("ws://192.168.178.245") as websocket:
#         await websocket.send(json.dumps({"command": "set_fruit_name", "fruit_name": "THANH LONG"}))

# if __name__ == "__main__":
#     asyncio.get_event_loop().run_until_complete(set_fruit_name())
