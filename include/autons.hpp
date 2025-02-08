#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

// Autonomous routes
void safeAWPRight();
void safeAWPLeft();
void riskyAWPRight();
void skillsAuto();
void AWPRight();


// Example routines
void HeritageAutoLeft ();
void HeritageAutoRight();
void SeaquamAutoRight ();
void SeaquamAutoLeft ();
void trial_skills_auto ();
void drive_forward ();
void riskyAWPLeft();

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void motion_chaining();
void combining_movements();
void interfered_example();

void default_constants();


// Helper functions / Threads
void unstuckIntake();
void testIntakeTask();
void waitUntilRingIntaked();
void stopWhenRingIntaked();
void colourSort();
void waitUntilAllyRingIntaked();