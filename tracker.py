#! /usr/bin/env python
import numpy as np
import cv2
import imutils
import time
import sys
from scipy.signal import argrelextrema, argrelmax
from collections import deque
import matplotlib.pyplot as plt

import math

#Get these using ball_tracker.py file
redLower = (7, 124, 50)		#Lower (Hue, Saturation, Value) for red color
redUpper = (28, 255, 255)	#Upper (HUE, Saturation, Value) for red color

theta = []
theta_range = [-1.51 + x*(1.51+1.51)/180 for x in range(180)]
average = [0,0,0]		#average of center point and radius to get better reading
depth = 0			    #distance

data = [0, 0]

cap = cv2.VideoCapture(sys.argv[1])
plt.show()
try:
    while(cap.isOpened()):

	# grab the current frame

        _, frame = cap.read()

        if frame is None:
            break

	# resize the frame, blur it, and convert it to the HSV
	# color space
        blurred = cv2.GaussianBlur(frame, (11, 11), 4)          #Blurring to remove noise
        cv2.imshow("blur", blurred)
        cv2.imshow("original", frame)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)          #Convert image from BGR to HSV format

        mask = cv2.inRange(hsv, redLower, redUpper)             #Values within this range are set to 1 otherwise 0
        cv2.imshow("threshold", mask)
        
        mask = cv2.erode(mask, None, iterations=6)              #noise removal
        mask = cv2.dilate(mask, None, iterations=6)             #noise removal
    	
    	cv2.imshow("morph", mask)
	# find contours in the mask and initialize the current
	# (x, y) center of the ball
        im, cnts, heir = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        #print cnts
        #cnts = imutils.grab_contours(cnts)
        #center = None

	# only proceed if at least one contour was found
        blank = np.zeros((488,648,1), np.uint8)
        blank2 = np.zeros((488,648,3), np.uint8)	    
        if len(cnts) > 1:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
		    
            cnt = sorted(cnts, key=cv2.contourArea, reverse=True)

            #cv2.drawContours(blank, cnts, -1, (0,0,255), 2)
            #tmp = frame.copy()            
            cv2.drawContours(blank, [cnt[0], cnt[1]], -1, (255,255,255), 2)
            #rect = cv2.boundingRect(cnt[0])
            #rect1 = cv2.boundingRect(cnt[1])
            
            lines = cv2.HoughLinesP(blank, 1, np.pi/180, 50, 30)
            
            if lines is not None:
                #print lines
                theta = []
                for x in range(0, len(lines)):
                    for x1,y1,x2,y2 in lines[x]:
                        theta = theta + [math.atan2(y2-y1, x2-x1)]
                        cv2.line(blank2,(x1,y1),(x2,y2),(0,255,0),2)
                
                h,b = np.histogram(theta,bins=theta_range)
                plt.clf()
                plt.plot(b[:len(b) - 1],h)
                
                plt.draw()
                plt.pause(0.001)
                plt.show(block=False)
                print argrelmax(h, order=5)
                
            cv2.imshow("contour", blank2)
            
            #x,y,w,h = rect
            #x1,y1,w1,h1 = rect1
            
            #cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
            #cv2.rectangle(frame,(x1,y1),(x1+w1,y1+h1),(0,255,0),2)
            
            #M = cv.moments(cnt[0])
            #M1 = cv.moments(cnt[1])
            
            #cx = int(M['m10']/M['m00'])
            #cy = int(M['m01']/M['m00'])
            
            #cx1 = int(M1['m10']/M1['m00'])
            #cy1 = int(M1['m01']/M1['m00'])
            
            
#            c = max(cnts, key=cv2.contourArea)
#            ((x, y), radius) = cv2.minEnclosingCircle(c)
#            M = cv2.moments(c)
#            center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

		# only proceed if the radius meets a minimum size


	cv2.imshow("mask", blank)
	cv2.imshow("orig", frame)
	if cv2.waitKey(50) == ord(' '):
	    while cv2.waitKey(20) != ord(' '):
	        pass


except KeyboardInterrupt:
    pass
