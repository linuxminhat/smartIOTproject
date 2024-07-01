import os
import datetime
import requests
import shutil
from ultralytics import YOLO

CAPTURE_URL = "http://192.168.178.244/capture"
RESOLUTION_UXGA_URL = "http://192.168.178.244/control?var=framesize&val=13"
LED_INTENSITY_URL = "http://192.168.178.244/control?var=led_intensity&val=50"

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
CURRENT_DATE = datetime.datetime.now().strftime("%Y.%m.%d")
CAPTURE_PATH = os.path.join(SCRIPT_DIR, ".\\captures", CURRENT_DATE)
PREDICT_PATH = os.path.join(SCRIPT_DIR, ".\\predicts", CURRENT_DATE)
os.makedirs(CAPTURE_PATH, exist_ok=True)
os.makedirs(PREDICT_PATH, exist_ok=True)
MODEL = YOLO(r"D:\PBL4_Fruits_Detection\best.pt")


def capture(CAPTURE_URL):
    response = requests.get(CAPTURE_URL)

    if response.status_code == 200:
        # Count the number of images in the directory
        num_images = len([name for name in os.listdir(
            CAPTURE_PATH) if name.endswith(".jpg")])

        # The new image will have a name that is one greater than the number of images
        file_path = os.path.join(CAPTURE_PATH, f"{num_images + 1}.jpg")

        # Open a file in write-binary mode and write the response content to it
        with open(file_path, "wb") as file:
            file.write(response.content)

        return os.path.abspath(file_path)

    else:
        return None


def predict(source_path, **kwargs):
    if not os.path.isfile(source_path):
        return None, None
    """
        Tạo 1 folder có tên = số folder trong PREDICT_PATH
        Model.predict(project=folder) lưu kết quả trong
        folder\image.jpg
        folder\label\image.txt
    """
    # count how many folders in PREDICT_PATH
    nums_folder = len([name for name in os.listdir(PREDICT_PATH) if os.path.isdir(os.path.join(PREDICT_PATH, name))])
    project = os.path.join(PREDICT_PATH,  str(nums_folder))
    ### Make predict ###
    MODEL.predict(source=source_path, imgsz=kwargs.get("imgsz", 640), conf=kwargs.get("conf", 0.8), device=kwargs.get("device", "cpu"), save=True, save_txt=True, project=project)
    ### RETURN project\image.jpg and project\labels\image.txt
    # Get image name (image.jpg and image.txt)
    img_name = os.path.basename(source_path)
    label_name = img_name.replace(".jpg", ".txt")
    return os.path.join(project, "predict", img_name), os.path.join(project, "predict", "labels", label_name)

# Driver
if __name__ == "__main__":
    # requests.get(RESOLUTION_UXGA_URL)
    # requests.get(LED_INTENSITY_URL)
    captured_path = r"D:\PBL4_Fruits_Detection\test\images\7_dragon_fruit_666.jpg"
    image_path, label_path = predict(captured_path)
    print("Image path:", image_path)
    print("Label path:", label_path)

    

