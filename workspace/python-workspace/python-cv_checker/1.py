import cv2
import numpy as np


def find(image):
    src = cv2.imread(image)
    dst = src.copy()

    if src is None:
        print('Cannot load image.')
        return

    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (3, 3), 0)

    min_distance = 10
    max_corners = 0
    quality_level = 0.3

    corners = cv2.goodFeaturesToTrack(blur, maxCorners=max_corners, qualityLevel=quality_level,
                                      minDistance=min_distance)

    if np.sqrt(len(corners)) - 1 <= 9:
        print('8 x 8')
    else:
        print('10 x 10')

    if corners is not None:
        for i in range(corners.shape[0]):
            pt = (int(corners[i, 0, 0]), int(corners[i, 0, 1]))
            cv2.circle(dst, pt, 5, (0, 0, 255), 2)
    else:
        print('Cannot find checkerboard')


# TEST
find(' path ')
