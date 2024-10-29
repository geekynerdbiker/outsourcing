import cv2
import numpy as np


def refacor(image):
    width, height, _ = image.shape
    sizer = 1024 // max(width, height)
    return cv2.resize(image, (width * sizer, height * sizer), cv2.INTER_LINEAR)


def order(points):
    rect = np.zeros((4, 2), dtype="float32")

    rect[0] = points[np.argmin(points.sum(axis=1))]
    rect[1] = points[np.argmin(np.diff(points, axis=1))]
    rect[2] = points[np.argmax(points.sum(axis=1))]
    rect[3] = points[np.argmax(np.diff(points, axis=1))]

    return rect


def canny(image):
    lower = int(max(0, (1.0 - 0.3) * np.median(image)))
    upper = int(min(255, (1.0 + 0.3) * np.median(image)))
    edged = cv2.Canny(image, lower, upper)

    return edged


def find(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edged = canny(cv2.GaussianBlur(gray, (5, 5), 0))

    contours, _ = cv2.findContours(edged.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    contours = sorted(contours, key=cv2.contourArea, reverse=True)[:5]

    for c in contours:
        peri = cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, 0.02 * peri, True)

        # if len(approx) == 4:
        #     return order(approx.reshape(4, 2))
    return None


def transform(image, pts):
    rect = order(pts)

    maxWidth = 500
    maxHeight = 500

    dst = np.array([
        [0, 0],
        [maxWidth - 1, 0],
        [maxWidth - 1, maxHeight - 1],
        [0, maxHeight - 1]], dtype="float32")

    M = cv2.getPerspectiveTransform(rect, dst)
    return cv2.warpPerspective(image, M, (maxWidth, maxHeight))


# TEST
image = refacor(cv2.imread('1.jpeg'))
corners = find(image)

if corners is not None:
    warped = transform(image, corners)
    cv2.imshow('Warped', warped)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
else:
    print("Cannot find edges.")
