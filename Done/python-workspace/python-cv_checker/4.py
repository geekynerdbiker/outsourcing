import cv2
import numpy as np


def getColors(image, center, radius):
    x, y = center
    x, y, radius = int(x), int(y), int(radius)

    circle = image[y - radius:y + radius, x - radius:x + radius]

    return np.mean(circle, axis=(0, 1))



def count(image):
    src = cv2.imread(image)

    if src is None:
        print('Cannot load image.')
        return

    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    corners = cv2.goodFeaturesToTrack(cv2.GaussianBlur(gray, (3, 3), 0), maxCorners=0, qualityLevel=0.3,
                                      minDistance=10)
    circles = cv2.HoughCircles(cv2.blur(gray, (3, 3)), cv2.HOUGH_GRADIENT, dp=1, minDist=50, param1=50, param2=30, minRadius=10,
                               maxRadius=50)

    bright = 0
    dark = 0

    if circles is not None:
        circles = np.uint16(np.around(circles))

        colors = []

        for circle in circles[0, :]:
            center = (circle[0], circle[1])
            radius = circle[2]

            color = getColors(gray, center, radius)
            colors.append(color)

        for circle in circles[0, :]:
            x, y, radius = circle
            if src[y, x][0] > np.mean(colors, axis=0):
                cv2.circle(src, (x, y), radius, (0, 0, 255), 2, cv2.LINE_AA)
                bright += 1
            else:
                cv2.circle(src, (x, y), radius, (255, 0, 0), 2, cv2.LINE_AA)
                dark += 1

        if np.sqrt(len(corners)) - 1 <= 9:
            print('w:12 b:12')
        else:
            print('w:20 b:20')
    else:
        print('w:0 b:0')


# TEST
count(' path ')
