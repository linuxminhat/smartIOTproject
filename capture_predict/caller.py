from main import *


if __name__ == "__main__":
    print("Script DIR:", SCRIPT_DIR)
    print("Predict path:", PREDICT_PATH)
    captured_path = "D:\PBL4_Fruits_Detection\test\images\6_green_apple_1.jpg"
    image_path, label_path = predict(captured_path)
    print("Image path:", image_path)
    print("Label path:", label_path)
