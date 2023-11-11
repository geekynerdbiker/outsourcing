import sys
import cv2


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


src = cv2.imread(sys.argv[1])
corners = get_corners(src)

warped = perspective_transform(src, corners)
warped = warped[corners[0][1]:corners[3][1], corners[0][0]:corners[3][0]]

cv2.imshow(warped)
cv2.waitKey(0)
