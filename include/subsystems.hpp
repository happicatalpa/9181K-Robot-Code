#pragma once

#include "api.h"

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake (1, pros::v5::MotorGears::blue);
inline pros::Motor arm (2, pros::v5::MotorGears::red, pros::v5::MotorEncoderUnits::degrees);
inline pros::adi::DigitalOut MogoClamp ('A');


// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');