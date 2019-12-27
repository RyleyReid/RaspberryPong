// @authors: Ryan Schmidt, Faiez Alkhouri
// @Brief: Help class for all I/O purposes. Computes angles and distance.
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <wiringPi.h>
#include "libSonar.h"
using namespace std;

class Control{

	private:
		
		int trigger;
		int echo;


		

	public:
		Control();

		~Control();
// @Brief: method that computes the angle of fire
// @Parameters: Force is a fixed double based on compressed air PSI
//              Mass is the weight of our projectile
//              ActuationDistance is the length of the pneumatic cylinder
//              Distance is the distance to our target location given by grbll class
//              Height is a fixed displacement off the shooting surface by our robot's frame
// @return: Returns the angle of fire

		double calcAngle(double force, double mass, double actuationDistance, double distance, double height);
// @Brief: This function works using the libsonar library for HR-S04 sensor to return a distance array
// @ return: returns an array of 7 distances taken so the user has the option of taking an average or median distance

		double getDistance();
		
};
