import numpy as np
import cv2 as cv
from math import atan2, pi, pow, sqrt

img = cv.imread('minute_37.JPG', cv.IMREAD_GRAYSCALE)
assert img is not None, "file could not be read, check with os.path.exists()"

middle_x, middle_y = img.shape
middle_x /= 2
middle_y /= 2
ret, thresh = cv.threshold(img, 127, 255, 0)
contours, hierarchy = cv.findContours(thresh, 1, 2)

cnt1, cnt2 = None, None

maximum, max_idx = 0, 0
difference, circle_idx = 100000, 0

rect1, rect2, box1, box2 = 0, 0, 0, 0

maximum = 0
for c in contours:
    if maximum < c.shape[0]:
        rect2 = cv.minAreaRect(c)
        box2 = cv.boxPoints(rect2)
        box2 = np.int0(box2)
        maximum = c.shape[0]
        continue

    for c2 in c:
        if middle_x * 0.75 < c2[0][0] < middle_x * 1.25 and middle_y * 0.75 < c2[0][1] < middle_y * 1.25:
            rect1 = cv.minAreaRect(c)
            box1 = cv.boxPoints(rect1)
            box1 = np.int0(box1)
            break

cv.drawContours(img, [box2], 0, (0, 0, 255), 2)

x1, y1 = box2[0]
x2, y2 = box2[1]

angle = (atan2(y1 - y2, x1 - x2) * 180 / pi)
minute = 60 / 360 * angle

center = box1[0]
end = []

dist1 = sqrt(pow(center[0] - x1, 2) + pow(center[1] - y1, 2))
dist2 = sqrt(pow(center[0] - x2, 2) + pow(center[1] - y2, 2))

if dist1 > dist2:
    if abs(dist1 - dist2) > 1:
        end = box2[0]
    else:
        end = box2[1]
else:
    if abs(dist1 - dist2) > 1:
        end = box2[1]
    else:
        end = box2[0]

if center[0] < end[0] and center[1] > end[1]:
    angle = abs(angle)
elif center[0] < end[0] and center[1] < end[1]:
    angle = abs(angle) + 90
elif center[0] > end[0] and center[1] < end[1]:
    angle = abs(angle) + 180
elif center[0] > end[0] and center[1] > end[1]:
    angle = abs(angle) + 270

print(angle * 60 / 360)
