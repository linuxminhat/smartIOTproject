import requests


LOADCELL_WebServer_URL = "http://192.168.178.245/"

def get_weight(WebServer_URL: str):
    response = requests.get(WebServer_URL)
    if response.status_code == 200:
        return float(response.content)
    return None


if __name__ == "__main__":
    print(get_weight(LOADCELL_WebServer_URL))
