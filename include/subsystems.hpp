#pragma once

#include "api.h"


inline pros::MotorGroup intake ({21, -10}, pros::v5::MotorGears::blue);
inline pros::Motor arm (12, pros::MotorGears::red, pros::v5::MotorEncoderUnits::degrees);
inline pros::adi::Pneumatics MogoClamp ('A', false);
inline pros::adi::Pneumatics PTO ('B', false);
inline pros::IMU inertial (20);
inline pros::Optical optical (10);
inline pros::adi::Ultrasonic wallMechSensor ('B', 'C'); // Ultrasonic sensor - Ping, Echo
inline pros::adi::DigitalIn clampLimitSwitch ('E'); 


// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');