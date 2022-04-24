import numpy as np
import cv2


def on_change(pos):
    global img
    b = cv2.getTrackbarPos('b', 'img')
    img[:] = (b, b, b)
    cv2.imshow('img', img)


img = np.zeros((512, 512, 3), np.uint8)
cv2.imshow('img', img)

# cv2.createTrackbar('b', 'img', 0, 150, on_change)
# cv2.setTrackbarPos('b', 'img', 255)
#
# cv2.waitKey()
# cv2.destroyAllWindows()
