#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

// Autonomous routes
void safeAWPLeft();
void riskyAWPRight();
void skillsAuto();


// Example routines
void SeaquamAutoRight ();
void SeaquamAutoLeft ();
void trial_skills_auto ();
void drive_forward ();

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void motion_chaining();
void combining_movements();
void interfered_example();

void default_constants();