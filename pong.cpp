/* 
* \Authors Ryley Reid, Arshia Abdipour
* \Brief Main class for activating the sensor and camera, processing the peripheral's data
* and using the grblinterface to activate motors and eventually fire the projectile
*/
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "rs232.h"
#include <string>
#include <cstring>
#include <math.h>
#include "Camera.h"
#include "grblInterface.h"
#include "Control.h"
using namespace std;
using namespace cv;
	
 	int main(){
	const char* code = "G01 X10 F500\n";
	grblInterface interface; //creating an interface object for motor I/O
	Camera cam;	 //creating camera object for camera I/O
	bool centerCup = false;
	int check = 0; //variable that checks if the camera has overshot the camera & needs to change direction
	int lateralMove = 0; //counter variable that is passed through to rotate the robots base. 
	while(!centerCup){ //while the cup is not centered in the cameras view 
		int apple = lateralMove;
		int direction = cam.openCV(); //cameras openCV() method, creates a camera stream and returns a value indicating if the cup is to the left, right or centered in the camera.
		/*based on the return value of the openCV() method & the check variable, updates the lateralMove variable by either +/- 1,5,10 degrees*/
		if(direction == 1){ //cup is to the right of the view
			if(check == 0 || check == 1){
				lateralMove = lateralMove - 10;
				interface.moveDegree(false, lateralMove);
				check = 1;
			}
			if(check == 2 || check == 3){
				lateralMove = lateralMove - 5;
				interface.moveDegree(false, lateralMove);
				check = 3;
			}
			if(check == 4){
				lateralMove = lateralMove - 1;
				interface.moveDegree(false, lateralMove);
			}
		}
		else if(direction == 2){ //cup is to the left of the view
			if(check == 0 || check == 2){
				lateralMove = lateralMove + 10;
				interface.moveDegree(false, lateralMove);
				check = 2;
			}
			if(check == 1 || check == 4){
				lateralMove = lateralMove + 5;
				interface.moveDegree(false, lateralMove);
				check = 4;
			}
			if(check == 3){ 
				lateralMove = lateralMove + 1;
				interface.moveDegree(false, lateralMove);
			}
		}
		else if(direction == 3){ //cup is centered 
			centerCup = true;
			printf("DONE\n");
			break;
		}
	}
	
	Control cntrl; //control object for angle and distance computation. 
	double distance = cntrl.getDistance(); //getting the distance from the arm to the cup 
	distance = distance + 10; //adding 10 centemers to account for distance censors forward displacement
	distance = distance/100.0; //converting to meters 
	printf("Distance = %f\n", distance);
	double angle = cntrl.calcAngle(30.9, 0.002, 0.05, distance, 0.25); //calcuating angle to shoot the shot 
	printf("%f\n", angle);
	
	interface.moveDegree(true, -(90.0-angle)); //moving pnumatic cylinder to angle returned from calcAngle() function
	
	for(int i=0; i<3; i++){ //3 attempts for shit
		inerface.fire(); //fire shot & retract
		interface.resetY(); //reseting Y 

	}
	interface.resetX(); //reseting X
	return 0;
}
 

