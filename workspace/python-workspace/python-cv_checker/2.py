import cv2
import numpy as np


def mouseCallback(event, x, y, flags, param):
    global image
    if event == cv2.EVENT_LBUTTONDOWN:
        param.append((x, y))
        cv2.circle(image, (x, y), 5, (0, 0, 255), -1)


# Test
image = cv2.imread('check8_8_8.jpg')
points = []

cv2.namedWindow('Original Image')
cv2.setMouseCallback('Original Image', mouseCallback, points)

while len(points) < 4:
    cv2.imshow('Original Image', image)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cv2.destroyAllWindows()

selected = np.float32(points)
edges = np.float32([[0, 0], [300, 0], [300, 300], [0, 300]])

mat = cv2.getPerspectiveTransform(selected, edges)
res = cv2.warpPerspective(image, mat, (300, 300))

cv2.imshow('Transformed Image', res)
cv2.waitKey(0)
cv2.destroyAllWindows()
