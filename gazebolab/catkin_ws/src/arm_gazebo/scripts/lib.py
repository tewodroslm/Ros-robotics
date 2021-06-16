import cv2 as cv
import numpy as np

image = cv.imread("tesla.jpg")
#image = cv.imread("rockli.jpg", cv.IMREAD_GRAYSCALE)

new_image = np.zeros_like(image)

#kernel also filter
# filter = np.array([
#     [1,1,1],
#     [1,1,1],
#     [1,1,1]
# ], dtype=np.int)

# for the gx  edge ditection....
filter = np.array([
    [-1,0,1],
    [-2,0,2],
    [-1,0,1]
], dtype=np.int)

#filter = filter/9.0

k = 3 #size of kernel


for i in range(image.shape[0] - 2):
    for j in range(image.shape[1] - 2):
        patch = image[i: i+k, j:j+k]            # taking a section of image by creating patch
        # result = filter * patch
        # result = result.mean()                  # taking the mean

        # new_image[i, j] = result

        Gx = (filter * patch).sum()
        Gy = (filter.T * patch).sum()
        G = np.sqrt(Gy ** 2 + Gx ** 2)
        new_image[i,j] = G


cv.imshow("tesla", new_image)

cv.waitKey(0)










