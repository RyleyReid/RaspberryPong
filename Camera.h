/** @authors Arshia Abdipour, Savio Joseph
* \brief The Class opens a video stream which is scanned for the presence of a red cup.
* \parameters: none
* \returns: The distance from a center point is calculated
* return 1 for a right of center, 
* 2 for a left of center cup, 
* and 3 if the cup is now centered.
*/
#include <unistd.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

class Camera{

	private:
		bool centered;


	public:
		Camera();

		~Camera();
	/** \brief opens a video stream & scans for the presence of a red cup, creates a collison box 24 pixels wide (12 pixels on either side) from the center of the camera view to detect if the cup has been centered
	* \returns: The distance from a center point is calculated
	* return 1 for a right of center, 
	*2 for a left of center cup, 
	* and 3 if the cup is now centered.
	*/
		int openCV();
};
