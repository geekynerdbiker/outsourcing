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


def get_corners(image):
    edges = cv2.Canny(image, 50, 150)
    x, y, w, h = cv2.boundingRect(edges)
    corners = [(x, y), (x + w, y), (x + w, y + h), (x, y + h)]

    return corners


def perspective_transform(image, corners):
    H = cv2.getPerspectiveTransform(corners, [[0, 0], [image.shape[1], 0], [image.shape[1], image.shape[0]],
                                              [0, image.shape[0]]])
    warped = cv2.warpPerspective(image, H, (image.shape[1], image.shape[0]))

    return warped


def get_piece_color(src, x, y):
    pixel = src[x, y]
    if pixel[0] > 127:
        return "w"
    else:
        return "b"


def count_pieces(src, size):
    white = 0
    black = 0

    board_size = size
    for i in range(src.shape[0] // size // 2, src.shape[0], src.shape[0] // size):
        for j in range(src.shape[1] // size // 2, src.shape[1], src.shape[1] // size):
            pixel_color = get_piece_color(src, i, j)
            if pixel_color == "w":
                white += 1
            elif pixel_color == "b":
                black += 1
    return white, black


# src = cv2.imread(sys.argv[1])
src = cv2.imread("board1.jpeg")
gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
res = cv2.preCornerDetect(gray, ksize=3)
ret, res2 = cv2.threshold(np.abs(res), 0.1, 0, cv2.THRESH_TOZERO)

corners = get_corners(src)

warped = perspective_transform(src, corners)
warped = warped[corners[0][1]:corners[3][1], corners[0][0]:corners[3][0]]
res = cv2.preCornerDetect(warped, ksize=3)
ret, res2 = cv2.threshold(np.abs(res), 0.1, 0, cv2.THRESH_TOZERO)

corners = findLocalMaxima(res2)

if corners.shape[0] < 100:
    size = 8
else:
    size = 10

white, black = count_pieces(src, size)
print("w:" + str(white) + " b:" + str(black))
