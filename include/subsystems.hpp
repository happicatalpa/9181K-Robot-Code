#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake (18, pros::v5::MotorGears::blue);
inline pros::MotorGroup arm ({1, -2}, pros::MotorGears::red, pros::v5::MotorEncoderUnits::degrees);
//inline pros::Motor armRight (1, pros::v5::MotorGears::red, pros::v5::MotorEncoderUnits::degrees);
//inline pros::Motor armLeft (-2, pros::v5::MotorGears::red, pros::v5::MotorEncoderUnits::degrees); // one of these will be reversed?
inline pros::adi::Pneumatics MogoClamp ('E', false);
inline pros::IMU inertial (19);
inline pros::Optical optical (6);
inline pros::adi::Ultrasonic clampSensor ('A', 'B'); // Ultrasonic sensor - Ping, Echo
inline pros::adi::Ultrasonic wallMechSensor ('C', 'D'); 


// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');