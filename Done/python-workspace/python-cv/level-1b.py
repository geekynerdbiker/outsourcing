import cv2 as cv

images = []

img1 = cv.imread('1-1.jpg')
img2 = cv.imread('1-2.jpg')
img3 = cv.imread('2-1.jpg')
img4 = cv.imread('2-2.jpg')

images.append(img1)
images.append(img2)
images.append(img3)
images.append(img4)

stitcher = cv.Stitcher.create(cv.STITCHER_PANORAMA)
status, pano = stitcher.stitch(images)

if status != cv.Stitcher_OK:
    print("Can't stitch images, error code = %d" % status)
    exit(-1)

cv.imwrite('result.jpg', pano)