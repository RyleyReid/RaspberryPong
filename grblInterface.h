/** \Ryan Schmidt, Tariq Hirji
*   \Brief: a class to interface and move an arduino's motors
*/
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "rs232.h"
#include <string>
#include <cstring>
#include<sstream>

#define BUF_SIZE 128

using namespace std;

class grblInterface{

	private:

		unsigned char* read;
		int i=0;
		int cport_nr; /* /dev/ttyUSB0 */
		int bdrate; /* 9600 baud */
  		char str_send[2][BUF_SIZE]; // send data buffer
  		unsigned char str_recv[BUF_SIZE]; // recv data buffer
  		char mode[4]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit

	public:

		grblInterface();
		~grblInterface();
		void moveDistance(float dist);
/**\Brief converts a degree input to a distance for the  motor to move via a grbll command
*\Parameters: arm moves the robot arm on TRUE and the base on FALSE
*            degree is the final resting degree saught by the user    
*/ 
        void moveDegree(bool arm, float degree);

/**Brief returns the motor to x = 0	
*/
        void resetX();
    
/**Brief returns the motor to y = 0
*/
        void resetY();
    
/**  \Brief: Send grbl commands from user to motor
*    \Parameters: send is the grbll command for a specified move
*             time is the wait period for the system after the command is sent
*    \return: returns an error code of 1, 0 if signal causes no errors
*/
		int sendCode(const char* send, unsigned int time);
    
/**Brief fires cylinder to fire ball	
*/   
        void fire();
};
