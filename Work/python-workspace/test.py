import time
import win32gui
import numpy as np
import cv2
import pyautogui


class WindowCapture:
    def __init__(self, window_name, capture_rate):
        self.window_name = window_name
        self.wait_time = 1 / capture_rate

        self.frame = self.screenshot()

    def screenshot(self):
        hwnd = win32gui.FindWindow(None, self.window_name)
        if not hwnd:
            raise Exception('Window not found: ' + self.window_name)

        left, top, right, bot = win32gui.GetClientRect(hwnd)
        x, y = win32gui.ClientToScreen(hwnd, (left, top))
        return cv2.cvtColor(
            np.asarray(
                pyautogui.screenshot(
                    region=(x, y,
                            *win32gui.ClientToScreen(hwnd, (right - x, bot - y))))), cv2.COLOR_RGB2BGR)


ESC_KEY = 27
FRAME_RATE = 120
SLEEP_TIME = 1 / FRAME_RATE

capture = WindowCapture("HangamePoker.exe", FRAME_RATE)

while True:
    start = time.time()
    frame = capture.screenshot()
    cv2.imshow("frame1", frame)
    delta = time.time() - start
    if delta < SLEEP_TIME:
        time.sleep(SLEEP_TIME - delta)
    key = cv2.waitKey(1) & 0xFF
    if key == ESC_KEY:
        break
