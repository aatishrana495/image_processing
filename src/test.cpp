#include <opencv2/opencv.hpp>
#include <iostream>
#include <limits.h>

using namespace cv;

int thresh_R = 0, thresh_G = 0, thresh_h_R = 255;
int thresh_B = 0, thresh_h_B = 255, thresh_h_G = 255;;
Mat channels[3], src, hsv;
Mat thrsh_B, thrsh_R, thrsh_G;
Mat gray;
int ker = 1;



//SimpleBlobDetector detector;
//std::vector<KeyPoint> keypoints;
//Mat im_with_keypoints;




void adaThr(Mat *t, int th, int th_h, Mat in, int type){

        //inRange( in, th, th_h, *t);
        //adaptiveThreshold( in, *t, 255, ADAPTIVE_THRESH_GAUSSIAN_C, type,  2 * th + 3, th_h);

}

void perform(){
     	
	Mat blur;
        //medianBlur(src, blur, ker * 2 + 3);
        split(src, channels);
        //threshold(channels[0], thrsh_B, thresh_B, 255, THRESH_BINARY);
	inRange(hsv, Scalar(thresh_B, thresh_G, thresh_R), Scalar(thresh_h_B, thresh_h_G, thresh_h_R), gray);        
//adaptiveThreshold( channels[1], thrsh_G, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 3, 4);

        //threshold(channels[1], thrsh_G, thresh_G, 255, THRESH_BINARY);
        //threshold(channels[2], thrsh_R, thresh_R, 255, THRESH_BINARY);
        //erode(thrsh_G, thrsh_G, Mat(), Point(-1, -1), 2, 1, 1);
        //dilate(thrsh_G, thrsh_G, Mat(), Point(-1, -1), 2, 1, 1);
        //erode(thrsh_G, thrsh_G, Mat(), Point(-1, -1), 2, 1, 1);
        //dilate(thrsh_G, thrsh_G, Mat(), Point(-1, -1), 2, 1, 1);

        //detector.detect( thrsh_G, keypoints);


        //drawKeypoints( thrsh_G, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        //threshold(channels[2], thrsh_R, thresh_R, 255, THRESH_BINARY);
        //bitwise_and(thrsh_R, thrsh_G ,thrsh_G);
        //bitwise_and(thrsh_G, thrsh_B ,thrsh_G);
        //adaThr(&thrsh_B, thresh_B, thresh_h_B, channels[0], THRESH_BINARY);
        //adaThr(&thrsh_R, thresh_B, thresh_h_B, channels[2], THRESH_BINARY_INV);

	

	

	
   
}

void inR(){

}

void show(){

        imshow("Threshold", gray);
        //imshow("thresh_R", thrsh_R);
        //imshow("thresh_G", im_with_keypoints);
        imshow("R", channels[2]);
        imshow("G", channels[1]);
        imshow("B", channels[0]);
        imshow("original", src);
}

int main(int argc, char **argv){



        VideoCapture cap(argv[1]);

        if(!cap.isOpened()) return -1;
        //namedWindow("Gray");

        namedWindow("Threshold");


        createTrackbar( "thresh_B", "Threshold",
                        &thresh_B,
                        255, NULL );

        createTrackbar( "thresh_hB","Threshold",
                         &thresh_h_B, 255, NULL );

        createTrackbar( "thresh_hG", "Threshold",
                        &thresh_h_G, 255, NULL );

        createTrackbar( "thresh_G","Threshold",
                         &thresh_G,
                        255, NULL );
        createTrackbar( "thresh_R","Threshold",
                         &thresh_R,
                        255, NULL );
        createTrackbar( "kernel",
                        "thresh_B", &ker,
                        255, NULL );

        createTrackbar( "thresh_hR","Threshold",
                         &thresh_h_R,
                        255, NULL );
        Mat blur;
        while(cap.isOpened()) {
                cap >> src;
                if(src.empty())
                        break;

                //cvtColor(src, gray, CV_BGR2GRAY);
                cvtColor(src, hsv, CV_BGR2HSV);
                int k = waitKey(10);

                if(k == ' ')
                        while((k = waitKey(10)) != ' ') {
                                if(k == 'q') return 0;
                                perform();
                                show();
                        }

                else if(k == 'q')
                        return 0;

                //printf("Hello\n");

                perform();
                show();
                Mat temp;
                //imshow("G", channels[1]);
                //bitwise_xor(thrsh_R, thrsh_B ,temp);

        }
}
