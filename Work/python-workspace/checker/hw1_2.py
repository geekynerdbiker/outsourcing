import sys
import cv2


def perspective_transform(image, corners):
    H = cv2.getPerspectiveTransform(corners, [[0, 0], [image.shape[1], 0], [image.shape[1], image.shape[0]],
                                              [0, image.shape[0]]])
    warped = cv2.warpPerspective(image, H, (image.shape[1], image.shape[0]))

    return warped


src = cv2.imread(sys.argv[1])
corners = []
for i in range(4):
    x, y = cv2.selectROI("coordinate", src, False, False)
    corners.append((x, y))
    point = cv2.waitKey(0)

warped = perspective_transform(src, corners)
warped = warped[corners[0][1]:corners[3][1], corners[0][0]:corners[3][0]]

cv2.imshow(warped)
cv2.waitKey(0)
