import sys

import cv2
import numpy as np

def findLocalMaxima(src):
    kernel = cv2.getStructuringElement(shape=cv2.MORPH_RECT, ksize=(11, 11))
    dilate = cv2.dilate(src, kernel)
    localMax = (src == dilate)

    erode = cv2.erode(src, kernel)
    localMax2 = src > erode
    localMax &= localMax2
    points = np.argwhere(localMax == True)
    points[:, [0, 1]] = points[:, [1, 0]]
    return points


src = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
res = cv2.preCornerDetect(gray, ksize=3)
ret, res2 = cv2.threshold(np.abs(res), 0.1, 0, cv2.THRESH_TOZERO)

corners = findLocalMaxima(res2)
dst = src.copy()
for x, y in corners:
    cv2.circle(dst, (x, y), 5, (0, 0, 255), 2)

if corners.shape[0] < 100:
    print("8X8")
else:
    print("10X10")
