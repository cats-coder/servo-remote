#ifndef SERVO_CONTROLLER_IG
#define SERVO_CONTROLLER_IG

/* Code defines - do not change */
#define SERVO_UP            1
#define SERVO_DOWN          0
#define SERVO_MAX_DEG       180  // servos absolute maximum
#define SERVO_MIN_DEG       0    // servos absolute minimum
// hint: max and min degrees can be defined further via the constructor

/* Configure servo motor - change at own risk */
#define SERVO_SPEED_OFFSET  5     // smaller means faster, shouldnt be smaller than 5
#define SERVO_SPEED_STEP    5     // used in nextStep() to determine delay time, steps of 5 seem okay

/* Configure servo use - change if more steps inbetween are desired (you might want to decrease SPEED_STEP aswell then) */
#define SERVO_MAX_SPEED     3 
#define SERVO_MIN_SPEED     0


/**
 * Custom servo helper to control the speed of the motor
 * when the calling loop can't afford to use delay for this
 * because it might have to check on other things such as an IR-module.
 */
class ServoController {
  public:

    /**
     * Constructor
     *  @param startDeg: first angle position in degree
     *  @param maxDeg: maximum of allowed rotation
     *  @param minDeg: minimum of allowed rotation
     *  maxDeg and minDeg must be within 0 and 180
     */
    ServoController(int startDeg, int maxDeg, int minDeg);
    ~ServoController();

    /** 
     * Move the servo by one degree according to the current speed
     *  @return : the current servo degree
     */
    int nextStep();
    
    /**
     * Increase the servo speed by 1 step
     *  @return: true if maximum speed reached, false otherwise
     */
    bool increaseSpeed();
    /**
     * Decrease the servo speed by 1 step
     *  @return: true if maximum speed reached, false otherwise
     */
    bool decreaseSpeed();

    /* Setters - checking the edge cases */
    void setMaxSpeed(int maxSpeed);
    void setMinSpeed(int minSpeed);
    void setMaxDegree(int maxDegree);
    void setMinDegree(int minDegree);

  private:
    unsigned long m_lastStepTime;
    int m_direction;
    int m_degree;
    int m_speed;
    int m_maxDegree;
    int m_minDegree;
    int m_maxSpeed;
    int m_minSpeed;
    
};

#endif
