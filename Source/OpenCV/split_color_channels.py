import cv2

src = cv2.imread("img.png",CV_LOAD_IMAGE_COLOR); #Load image

bgr[3];   //destination array
cv2.split(src,bgr);//split source

# Note: OpenCV uses BGR color order
cv2.imwrite("blue.png",bgr[0]); //blue channel
cv2.imwrite("green.png",bgr[1]); //green channel
cv2.imwrite("red.png",bgr[2]); //red channel
