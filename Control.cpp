// @authors: Ryan Schmidt, Faiez Alkhouri
// @Brief: Help class for all I/O purposes. Computes angles and distance.
#include "Control.h"

using namespace std;

	Control::Control(){
	    
	}

	Control::~Control(){

	}
// @Brief: method that computes the angle of fire
// @Parameters: Force is a fixed double based on compressed air PSI
//              Mass is the weight of our projectile
//              ActuationDistance is the length of the pneumatic cylinder
//              Distance is the distance to our target location given by grbll class
//              Height is a fixed displacement off the shooting surface by our robot's frame
// @return: Returns the angle of fire
	double Control::calcAngle(double force, double mass, double actuationDistance, double distance, double height){

		double velocity, angle, phi, num, j;

		velocity = 4.989;
		printf("v0 = %f\n", velocity);

		num = distance/height;
		printf("num = %f\n", num);
		phi = atan(num);
		phi = 180/3.1416*phi;
		
		printf("phi = %f\n", phi);
		printf("distance/height = %f/%f = %f\n", distance, height, distance/height);

		angle = ( ( (acos( ( ( ( 9.8*pow(distance,2))/pow(velocity, 2.0) ) -height) / sqrt( ( pow(height, 2.0) + pow(distance, 2.0) ) ) ) )*180.0/3.1416)+phi)/2.0;
		
		printf("angle = %f\n", angle);
		return angle;
	}
// @Brief: This function works using the libsonar library for HR-S04 sensor to return a distance array
// @ return: returns an array of 7 distances taken so the user has the option of taking an average or median distance
	double Control::getDistance(){  

		trigger = 1;
		echo = 0;
	 
	    if (wiringPiSetup() == -1)
	        return -1;
	 
	    Sonar sonar;
	    sonar.init(trigger, echo);
	    double distanceArray[7];
	    
	    for(int i=0; i<7; i++){
	      distanceArray[i] = sonar.distance(30000);
	      sleep(1);
	    }
	    
	    double min;
	    int index = 0;
	    
	    for(int i=0; i<7; i++){
	      
		min = distanceArray[i];
		index = i;
		
		for(int j=i; j<7; j++){
		
		    if(distanceArray[j] < min){
			  min = distanceArray[j];
			  index = j;
		      }
		}
		
		double temp = distanceArray[i];
		distanceArray[i] = distanceArray[index];
		distanceArray[index] = temp;
	    }
	    
	    printf("%f", distanceArray[3]);
	    
	    for(int i=0; i<7; i++){
        
            printf("%f, ", distanceArray[i]);
        }
	    printf("\n");
	 	
	    return distanceArray[3];
 }
 	

