#include "ServoController.h"
#include <Time.h>
#include <Arduino.h>


ServoController::ServoController(int startDeg, int maxDeg, int minDeg) {
  
  setMaxDegree(maxDeg);
  setMinDegree(minDeg);
  setMaxSpeed(SERVO_MAX_SPEED);
  setMinSpeed(SERVO_MIN_SPEED);

  if ( (startDeg <= maxDeg) && (startDeg >= minDeg) ) {
    m_degree = startDeg;
  } else {
    m_degree =  m_maxDegree;
  }

  m_speed = SERVO_MIN_SPEED;
  m_direction = SERVO_DOWN;
  m_lastStepTime = millis();
}


ServoController::~ServoController() {
  
}


int ServoController::nextStep() {
  unsigned long diff = (millis() - m_lastStepTime);

  if ( diff < (SERVO_SPEED_OFFSET + (m_maxSpeed - m_speed)*SERVO_SPEED_STEP) ) {
    return m_degree;
  } else {
    m_lastStepTime = 0;
  }

  if (m_direction == SERVO_UP) {
    m_degree++;
    if (m_degree == m_maxDegree) {
      m_direction = SERVO_DOWN;
    }
  } else {
    m_degree--;
    
    if (m_degree == m_minDegree) {
      m_direction = SERVO_UP;
    }
  }

  m_lastStepTime = millis();
  return m_degree;
}


bool ServoController::increaseSpeed() {
  if (m_speed < m_maxSpeed) {
    m_speed++;
  }
  return (m_speed == m_maxSpeed)? true: false;
}

bool ServoController::decreaseSpeed() {
  if (m_speed > m_minSpeed) {
    m_speed--;
  }
  return (m_speed == m_minSpeed)? true: false;
}

void ServoController::setMaxSpeed(int maxSpeed) {
  if ( (maxSpeed < SERVO_MAX_SPEED) && (maxSpeed > SERVO_MIN_SPEED) ) {
    m_maxSpeed = maxSpeed;
  }else {
    m_maxSpeed = SERVO_MAX_SPEED;
  }
}

void ServoController::setMinSpeed(int minSpeed) {
  if ( (minSpeed > SERVO_MIN_SPEED) && (minSpeed < SERVO_MAX_SPEED) ) {
    m_minSpeed = minSpeed;
  }else {
    m_minSpeed = SERVO_MIN_SPEED;
  }
}

void ServoController::setMaxDegree(int maxDegree) {
  if ( (maxDegree < SERVO_MAX_DEG) && (maxDegree > SERVO_MIN_DEG) ) {
    m_maxDegree = maxDegree;
  }else {
    m_maxDegree = SERVO_MAX_DEG;
  }
}

void ServoController::setMinDegree(int minDegree) {
  if ( (minDegree > SERVO_MIN_DEG) && (minDegree < SERVO_MAX_DEG) ) {
    m_minDegree = minDegree;
  }else {
    m_minDegree = SERVO_MIN_DEG;
  }
}
