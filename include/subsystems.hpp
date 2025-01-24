#pragma once

#include "api.h"


inline pros::Motor intake (7, pros::v5::MotorGears::blue);
inline pros::MotorGroup arm ({13, -20}, pros::MotorGears::red, pros::v5::MotorEncoderUnits::degrees);
inline pros::adi::Pneumatics MogoClamp ('A', false);
inline pros::IMU inertial (17);
inline pros::Optical optical (16);
inline pros::adi::Ultrasonic wallMechSensor ('B', 'C'); // Ultrasonic sensor - Ping, Echo
inline pros::adi::DigitalIn clampLimitSwitch ('E'); 


// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');