import time
import numpy as np

import cv2
import picamera
import picamera.array

def contrast_stretch(im):
    """
    Performs a simple contrast stretch of the given image, from 5-95%.
    """
    in_min = np.percentile(im, 5)
    in_max = np.percentile(im, 95)

    out_min = 0.0
    out_max = 255.0

    out = im - in_min
    out *= ((out_min - out_max) / (in_min - in_max))
    out += in_min

    return out


def run():
    with picamera.PiCamera() as camera:
        # Set the camera resolution
        #x = 1600
        #camera.resolution = (int(1.33 * x), x)
        camera.resolution = (2592, 1944)
        # Various optional camera settings below:
        # camera.framerate = 5
        # camera.awb_mode = 'off'
        # camera.awb_gains = (0.5, 0.5)

        # Need to sleep to give the camera time to get set up properly
        time.sleep(1)

        with picamera.array.PiRGBArray(camera) as stream:
            # Grab data from the camera, in colour format
            # NOTE: This comes in BGR rather than RGB, which is important
            # for later!

            # Current time for filename 2012_05_15-15_50_45
            timestr = time.strftime("%Y_%m_%d-%H_%M_%S")
            camera.capture(stream, format='bgr')
            image = stream.array

            # Get the individual colour components of the image
            b, g, r = cv2.split(image)

            cv2.imwrite('/home/pi/ndvi_b.jpg', b)
            cv2.imwrite('/home/pi/ndvi_g.jpg', g)
            cv2.imwrite('/home/pi/ndvi_r.jpg', r)

            # Calculate the NDVI

            # Bottom of fraction
            bottom = (r.astype(float) + b.astype(float))
            bottom[bottom == 0] = 0.01  # Make sure we don't divide by zero!

            ndvi = (r.astype(float) - b) / bottom
            cv2.imwrite('/home/pi/ndvi_1.jpg', ndvi)
            ndvi = contrast_stretch(ndvi)
            cv2.imwrite('/home/pi/ndvi_2.jpg', ndvi)
            ndvi = ndvi.astype(np.uint8)
            cv2.imwrite('/home/pi/ndvi_3.jpg', ndvi)

            # Convert to RGB
            cv2.cvtColor(ndvi, cv2.COLOR_GRAY2RGB)

            # Save NDVI image
            cv2.imwrite('/home/pi/ndvi_color.jpg', ndvi);

            # stream.truncate(0)

if __name__ == '__main__':
    run()
