/** \Ryan Schmidt, Tariq Hirji
* \Brief: a class to interface and move an arduino's motors
*/
#include "grblInterface.h"

using namespace std;

grblInterface::grblInterface(){

	i=0;
	cport_nr=16; /* /dev/ttyUSB0 */
	bdrate=115200; /* 9600 baud */
  		
  	if(RS232_OpenComport(cport_nr, bdrate, mode, 0)){

		printf("Can not open comport\n");
		return;
	}

	sleep(5);  /* waits 2000ms for stable condition */

	sendCode("M3\n", 1);
	sendCode("G90\n", 3);
	sendCode("F25\n", 3);
	resetX();
	resetY();
}
/**\Brief: Send grbl commands from user to motor
*\Parameters: send is the grbll command for a specified move
*             time is the wait period for the system after the command is sent
*\return: returns an error code of 1, 0 if signal causes no errors
*/
int grblInterface::sendCode(const char* send, unsigned int time){

	RS232_cputs(cport_nr, send); // sends string on serial
	printf("Sent to Arduino: '%s'\n", send);
	sleep(1);  /* waits for reply 1000ms */
	int n = RS232_PollComport(cport_nr, read, (int)BUF_SIZE);
	while(n <= 0){
		printf("sleeping");
		int n = RS232_PollComport(cport_nr, read, (int)BUF_SIZE);
		sleep(1);
	}
	if(n > 0){
	  read[n] = 0;   /* always put a "null" at the end of a string! */
	  printf("Received %i bytes: '%s'\n", n, read);
	  sleep(time);  /* sleep for 5 Second */
	  return 0;
	}

	else{
		return 1;
	}
}

grblInterface::~grblInterface(){

}

void grblInterface::moveDistance(float dist){
}

/**\Brief converts a degree input to a distance for the  motor to move via a grbll command
*\Parameters: arm moves the robot arm on TRUE and the base on FALSE
*            degree is the final resting degree saught by the user    
*/
void grblInterface::moveDegree(bool arm, float degree){

	float convFactor = 720;

	float mm = (degree/convFactor)*16;

	if(arm){

		mm*=3;

		ostringstream ss;
		ss << mm;
		string str = ("G01 Y" + ss.str() +"\n");

		char code[str.size()+1];
		strcpy(code, str.c_str());

		int x = sendCode(code, 2);
	}
	
	else{

		ostringstream ss;
		ss << mm;
		string str = ("G01 X" + ss.str() +"\n");

		char code[str.size()+1];
		strcpy(code, str.c_str());

		int x = sendCode(code, 2);
	}
}
//**\Brief returns the motor to x = 0
*/
void grblInterface::resetX(){

	sendCode("G01 X0\n", 5);
}
/**Brief returns the motor to y = 0
*/
void grblInterface::resetY(){

	sendCode("G01 Y0\n", 3);
}
/**Brief fires cylinder to fire ball
*/
void grblInterface::fire(){

	sendCode("M4\n", 1);
    sendCode("M3\n", 1);
}
