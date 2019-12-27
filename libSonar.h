/** Github.com/Omar Aflak
* \brief Library for the HC-SRO4 distance sensor
*/
#ifndef DEF_SONAR
#define DEF_SONAR

class Sonar
{
  public:
    Sonar();
    void init(int trigger, int echo);
    /* \breif Returns the distance recorded by the sensor */
    double distance(int timeout);

  private:
    void recordPulseLength();
    int trigger;
    int echo;
    volatile long startTimeUsec;
    volatile long endTimeUsec;
    double distanceMeters;
    long travelTimeUsec;
    long now;
};

#endif
