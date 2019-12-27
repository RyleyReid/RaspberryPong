/** @authors Arshia Abdipour, Savio Joseph
* \brief The Class opens a video stream which is scanned for the presence of a red cup.
* \parameters: none
* \returns: The distance from a center point is calculated
* return 1 for a right of center, 
* 2 for a left of center cup, 
* and 3 if the cup is now centered.
*/
#include "Camera.h"
using namespace std;

	Camera::Camera(){ //constructor 
	}

	Camera::~Camera(){ //destructor 

	}
	/** \brief opens a video stream & scans for the presence of a red cup, creates a collison box 24 pixels wide (12 pixels on either side) from the center of the camera view to detect if the cup has been centered
	* \returns: The distance from a center point is calculated
	* return 1 for a right of center, 
	*2 for a left of center cup, 
	* and 3 if the cup is now centered.
	*/
	int Camera::openCV(){ 
	bool centered = false;
	VideoCapture cap(0); //capture the video from webcam
    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
  
    }

    namedWindow("Control", WINDOW_AUTOSIZE); //create a window called "Control"

	 int iLowH = 170;
	 int iHighH = 179;

	 int iLowS = 150; 
	 int iHighS = 255;

	 int iLowV = 60;
	 int iHighV = 255;

	 //Create trackbars in "Control" window
	 createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	 createTrackbar("HighH", "Control", &iHighH, 179);

	 createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	 createTrackbar("HighS", "Control", &iHighS, 255);

	 createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	 createTrackbar("HighV", "Control", &iHighV, 255);

	 int iLastX = -1; 
	 int iLastY = -1;

	 //Capture a temporary image from the camera
	 Mat imgTmp;
	 cap.read(imgTmp); 

	 //Create a black image with the size as the camera output
	 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
	 

	    while (!centered)
	    {
	        Mat imgOriginal;

	        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

	         while (!bSuccess) //if not success, break loop
	        {
	             cout << "Cannot read a frame from video stream" << endl;
	             break;
	        }

	  /* from lines 65-89 of this code are creating a region of intrest 24 pixels wide that will act as a collison box to determine when the camera has centered on the cup*/
	  Mat imgHSV;
	  int radius = 12;
	  Point center(imgOriginal.cols / 2, imgOriginal.rows / 2); //getting the center coordinate of the cameras view 
	  Rect r(center.x-radius, 0, radius*2, imgOriginal.size().height);
	  cout << "centx: " << center.x << "\n"; //outputting the x coordinate for center of cameras view
	  Mat roi(imgOriginal, r);
	  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
	 
	  Mat imgThresholded;
	  inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image      
	  
	  //morphological opening (removes small objects from the foreground)
	  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

	  //morphological closing (removes small holes from the foreground)
	  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	  //Calculate the moments of the thresholded image
	  Moments oMoments = moments(imgThresholded);
	  double dM01 = oMoments.m01;
	  double dM10 = oMoments.m10;
	  double dArea = oMoments.m00;


	  // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
	  if (dArea > 10000)
	  {

	   int posX = dM10 / dArea; /* updating center of cups  x coordinate for most recent frame*/
	   int posY = dM01 / dArea;   /* updating center of cups y coordinate for most recent frame*/
	   cout << "cupx: " << posX << "\n"; // printing out the x coordinate for the center of the cup
	   Point cent(posX, posY); //creating a point objet containing the cups x & y value. 
	   
	   if (r.contains(cent)) //if cups in the center of the camera veiw (if it falls within a 24 pixel range pixel #: 308 - 332)
	  { 
	      return 3; //@return 3; cup centered 
	  }
	   if(cent.x < center.x){ 
		 return 1; //@return 1; cup to the right 
	   }else{
		   return 2; //@return 2; cup to the left
	   } 
	  }

	        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
	       {
	            cout << "esc key is pressed by user" << endl;
	            break; 
	       }
	    }
	  return 0;
	}

