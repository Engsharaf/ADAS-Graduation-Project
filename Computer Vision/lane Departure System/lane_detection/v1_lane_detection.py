import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import math
import cv2
from moviepy.editor import VideoFileClip


# getting image
imgDir = 'test_images/'
imgFiles = os.listdir(imgDir)

imgList = []
for i in imgFiles:
    imgList.append(mpimg.imread(imgDir + i))

# Display Image
def display_image(images,cmap=None):
    plt.figure(figsize=(40,40))
    for i , image in enumerate(images):
        plt.subplot(3,2,i+1)
        plt.imshow(image,cmap)
        plt.autoscale(tight=True)
    plt.show()

display_image(imgList)

# masking uncessary color
def color_filter(images):
    hls = cv2.cvtColor(images, cv2.COLOR_RGB2HLS)

    lower = np.array([0,190,0])
    upper = np.array([255,255,255])

    yelLower = np.array([10,0,90])
    yelUpper = np.array([50,255,255])

    whiteMask = cv2.inRange(hls, lower, upper)
    yellowMask = cv2.inRange(hls, yelLower, yelUpper)

    mask = cv2.bitwise_or(whiteMask, yellowMask)
    masked = cv2.bitwise_and(images,images,mask = mask)

    return masked

filteredImage = list(map(color_filter,imgList))
display_image(filteredImage)

# region of interest
def roi(images):
    x = int(images.shape[1])     #width
    y = int(images.shape[0])     # height
    shape = np.array([[int(0), int(y)], [int(x), int(y)], [int(0.55*x), int(0.6*y)], [int(0.45*x), int(0.6*y)]])
    
    mask = np.zeros_like(images)

    if len(images.shape) > 2:
        channel_count = images.shape[2]
        ignoreMaskColor = (255,) * channel_count
    else:
        ignoreMaskColor = 255

    cv2.fillPoly(mask, np.int32([shape]), ignoreMaskColor)

    maskedImage = cv2.bitwise_and(images,mask)
    return maskedImage

roiImage = list(map(roi,filteredImage))
display_image(roiImage)

# edge detection
def grayScale(images):
    return cv2.cvtColor(images, cv2.COLOR_RGB2GRAY)

def canny(images):
    return cv2.Canny(grayScale(images), 50 , 150)

cannyImage = list(map(canny, roiImage))
display_image(cannyImage , cmap='gray')

# finding lanes
rightSlope , leftSlope , rightIntercept , leftIntercept = [],[],[],[]
def draw_lines(img, lines, thickness=5):
    global rightSlope, leftSlope, rightIntercept, leftIntercept
    rightColor = [0, 255, 0]
    leftColor = [255, 0, 0]

    # get right slope & intercept 
    # get left slope & intercept
    for line in lines:
        print(line)
        for x1, y1, x2, y2 in line:
            slope = (y1-y2)/(x1-x2)
            if slope > 0:
                if x1 > 500:
                    yintercept = y2 - (slope*x2)
                    rightSlope.append(slope)
                    rightIntercept.append(yintercept)
                else:
                    None
            elif slope < 0:
                if x1 < 600:
                    yintercept = y2 - (slope*x2)
                    leftSlope.append(slope)
                    leftIntercept.append(yintercept)

    #We use slicing operators and np.mean() to find the averages of the 30 previous frames
    #This makes the lines more stable, and less likely to shift rapidly
    leftavgSlope = np.mean(leftSlope[-30:])
    leftavgIntercept = np.mean(leftIntercept[-30:])

    rightavgSlope = np.mean(rightSlope[-30:])
    rightavgIntercept = np.mean(rightIntercept[-30:])

    #Here we plot the lines and the shape of the lane using the average slope and intercepts
    try:
        left_line_x1 = int((0.65*img.shape[0] - leftavgIntercept)/leftavgSlope)
        left_line_x2 = int((img.shape[0] - leftavgIntercept)/leftavgSlope)

        right_line_x1 = int((0.65*img.shape[0] - rightavgIntercept)/rightavgSlope)
        right_line_x2 = int((img.shape[0] - rightavgIntercept)/rightavgSlope)

        pts = np.array([[left_line_x1, int(0.65*img.shape[0])], [left_line_x2, int(img.shape[0])],[right_line_x2, int(img.shape[0])], [right_line_x1, int(0.65*img.shape[0])]], np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.fillPoly(img, [pts], (0, 0, 255))

        cv2.line(img, (left_line_x1, int(0.65*img.shape[0])), (left_line_x2, int(img.shape[0])), leftColor, 10)
        cv2.line(img, (right_line_x1, int(0.65*img.shape[0])), (right_line_x2, int(img.shape[0])), rightColor, 10)
    except ValueError:
        #I keep getting errors for some reason, so I put this here. Idk if the error still persists.
        pass


def hough_lines(img,rho,theta,threshold,min_line_len , max_line_gap):

    lines = cv2.HoughLinesP(img, rho, theta, threshold, np.array([]),minLineLength=min_line_len , maxLineGap = max_line_gap)
    lineImg = np.zeros((img.shape[0] , img.shape[1] , 3) , dtype=np.uint8)
    draw_lines(lineImg,lines)

    return lineImg

def line_detect(image):
    return hough_lines(image , 1 , np.pi/180 , 10 , 20 , 100)


hough_img = list(map(line_detect, cannyImage))


def weighted_img(img, initial_img, alpha=0.8, beta=1., lamda=0.):
    # # calculate weight image on out = initial_img*alpha + img*beta + lamda
    return cv2.addWeighted(initial_img, alpha, img, beta, lamda)


def weightSum(input_set):
    img = list(input_set)
    return weighted_img(img[0] ,img[1])


result_img = list(map(weightSum, zip(hough_img, imgList)))
display_image(result_img)


def processImage(image):
    interest = roi(image)
    filterimg = color_filter(interest)
    canny = cv2.Canny(grayScale(filterimg), 50, 120)
    myline = hough_lines(canny, 1, np.pi/180, 10, 20, 5)
    weightedImg = weighted_img(myline ,image)

    return weightedImg


output1 = 'test_videos_output/solidYellowLeft.mp4'
output2 = 'test_videos_output/solidWhiteRight.mp4'
output3 = 'test_videos_output/challenge.mp4'
output4 = 'test_videos_output/test2.mp4'
clip1 = VideoFileClip("test_videos/solidYellowLeft.mp4")  # .subclip(3,5)
clip2 = VideoFileClip("test_videos/solidWhiteRight.mp4")  # .subclip(3,5)
clip3 = VideoFileClip("test_videos/challenge.mp4")  # .subclip(3,5)
clip4 = VideoFileClip("test_videos/test2.mp4")  # .subclip(3,5)
# NOTE: this function expects color images!!
pclip1 = clip1.fl_image(processImage)
# NOTE: this function expects color images!!
pclip2 = clip2.fl_image(processImage)
# NOTE: this function expects color images!!
pclip3 = clip3.fl_image(processImage)
# NOTE: this function expects color images!!
pclip4 = clip4.fl_image(processImage)

pclip1.write_videofile(output1, audio=False)
pclip2.write_videofile(output2, audio=False)
pclip3.write_videofile(output3, audio=False)
pclip4.write_videofile(output4, audio=False)