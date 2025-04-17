#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Default speeds
// These are out of 127
int DRIVE_SPEED = 105;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;
const int INTAKE_SPEED = 120;
const int ARM_SPEED = 110;
const int BLUE = 170; // colour of blue ring
const int RED = 13; // colour of red ring
int intakeDelayTime = 750; // ms that the intake will go back for when trying to get unstuck


// CHANGE THIS BEFORE EACH MATCH
const int ALLY_COLOUR = RED;
const int ENEMY_COLOUR = BLUE;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_forward_set(8.8, .005, 4.5);
  chassis.pid_drive_constants_backward_set(9.1, 0.025,1.75);
  chassis.pid_turn_constants_set(1.5, 0.003, 1.25, 10);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///


void HeritageAutoLeft() {
  arm.move_absolute(35*5, 100);
  while (!((arm.get_position() < 35*5+15) && (arm.get_position() > 35*5-15))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  pros::delay(4000);
  chassis.pid_drive_set(17_in, 40);
  chassis.pid_wait();
  chassis.pid_turn_set(-90, 40);
  chassis.pid_wait();
  chassis.pid_drive_set(-4_in, 40);
  chassis.pid_wait();
  intake.move(70);
  pros::delay(2000);
  intake.move(-70);
  pros::delay(1000);
  chassis.pid_drive_set(5_in, 40);
  intake.move(127);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(2000);
  chassis.pid_drive_set(48_in, 80);
  chassis.pid_wait_until(30_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();


}

void HeritageAutoRight() {
  arm.move_absolute(35*5, 100);
  while (!((arm.get_position() < 35*5+15) && (arm.get_position() > 35*5-15))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
    pros::delay(4000);
  chassis.pid_drive_set(16_in, 40);
  chassis.pid_wait();
  chassis.pid_turn_set(92, 40);
  chassis.pid_wait();
  chassis.pid_drive_set(-4.5_in, 40);
  chassis.pid_wait();
  intake.move(70);
  pros::delay(2000);
  intake.move(-70);
  pros::delay(1000);
  chassis.pid_drive_set(5_in, 40);
  intake.move(127);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(2000);
  chassis.pid_drive_set(48_in, 80);
  chassis.pid_wait_until(30_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();

}

void SeaquamAutoRight () {
   // ~~ Turn and move backwards towards the nearest mobile goal ~~
  MogoClamp.retract();
  chassis.pid_drive_set(-27_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-30_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-4.2_in, 80);
  chassis.pid_wait();

  // ~~ Clamp onto the goal ~~
  MogoClamp.extend();
  pros::delay(200);
  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-3.5_in, DRIVE_SPEED);

  // ~~ Three-point turn into the next ring ~~
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-50_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(30_in, DRIVE_SPEED);
  chassis.pid_wait_until(15_in);
  chassis.pid_speed_max_set(60);
  intake.move(127);
  chassis.pid_wait();
  pros::delay(3000);

  // ~~ Turn and touch the ladder ~~
  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(175_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(35_in, 60);
  chassis.pid_wait();

}

void SeaquamAutoLeft () {
   // ~~ Turn and move backwards towards the nearest mobile goal ~~
  MogoClamp.retract();
  chassis.pid_drive_set(-27_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(30_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-4.2_in, 80);
  chassis.pid_wait();

  // ~~ Clamp onto the goal ~~
  MogoClamp.extend();
  pros::delay(200);
  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-3.5_in, DRIVE_SPEED);

  // ~~ Three-point turn into the next ring ~~
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(50_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(30_in, DRIVE_SPEED);
  chassis.pid_wait_until(15_in);
  chassis.pid_speed_max_set(60);
  intake.move(127);
  chassis.pid_wait();
  pros::delay(3000);

  // ~~ Turn and touch the ladder ~~
  chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-175_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(35_in, 60);
  chassis.pid_wait();

}

void trial_skills_auto () {
  // ~~ Move backwards towards the nearest mobile goal ~~
  MogoClamp.retract();
  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait();
  MogoClamp.extend();
  chassis.pid_drive_set(-2_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  intake.move(127);
  chassis.pid_wait();
  chassis.pid_drive_set(32_in, 80);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-93_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-48_in, 80);
  chassis.pid_wait();
  MogoClamp.retract();
  chassis.pid_drive_set(24_in, 80);
  chassis.pid_wait();

}

void drive_forward () {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  //chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  //chassis.pid_wait();

  //chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  //chassis.pid_wait();

  //chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  //chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}


/* Autonomous Functions */ 

void safeAWPRight() { // right side for now

  // Release the intake
  intake.move(INTAKE_SPEED);
  pros::delay(200);
  intake.move(0);

    // Release the intake
    intake.move(-INTAKE_SPEED);
    pros::delay(75);
    intake.move(0);

  // ~~ Move back towards the closest mogo ~~
  chassis.pid_drive_set(-14.3_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(80);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-32_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, 60);
  chassis.pid_wait();

  // ~~ Clamp onto the goal ~~
  MogoClamp.extend();

    // Start intake and tasks
  pros::delay(1000);
  intake.move(INTAKE_SPEED);

  

  // ~~ Turn and intake the ring on the right ~~
  chassis.pid_drive_set(-8_in, 60);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  pros::Task intakeTask(unstuckIntake); 
  pros::Task colourSortTask(colourSort);
  chassis.pid_drive_set(24.3_in, DRIVE_SPEED);
  chassis.pid_wait_until(18_in);
  chassis.pid_speed_max_set(60);
  pros::delay(500);



  // Go touch the ladder?
  
  chassis.pid_turn_relative_set(197_deg, TURN_SPEED);
  chassis.pid_drive_set(50_in, DRIVE_SPEED);
  chassis.pid_wait_until(28_in);
  intakeTask.remove();
  colourSortTask.remove();
  intake.move(0);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait();

/*
  // ~~ Turn and intake rings in the corner ~~
  chassis.pid_turn_relative_set(66_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait_until(24_in);
  doinker.extend();
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-30_deg, TURN_SPEED);
*/

  // ~~ Go to the corner of the ladder (drop the mobile goal halfway) ~~
  //chassis.pid_turn_relative_set(xx_deg, speed);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, speed);
  //chassis.pid_wait_until(xx_in);
  //MogoClamp.set_value(false);
  //chassis.pid_wait();

}


void safeAWPLeft() { // right side for now
  // Release the intake
  intake.move(INTAKE_SPEED);
  pros::delay(200);
  intake.move(0);

    // Release the intake
    intake.move(-INTAKE_SPEED);
    pros::delay(75);
    intake.move(0);

  // ~~ Move back towards the closest mogo ~~
  chassis.pid_drive_set(-15.3_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(80);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(29_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, 60);
  chassis.pid_wait();

  // ~~ Clamp onto the goal ~~
  MogoClamp.extend();

    // Start intake and tasks
  pros::delay(1000);
  intake.move(INTAKE_SPEED);

  

  // ~~ Turn and intake the ring on the right ~~
  chassis.pid_drive_set(-8_in, 60);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  pros::Task intakeTask(unstuckIntake); 
  pros::Task colourSortTask(colourSort);
  chassis.pid_drive_set(24.3_in, DRIVE_SPEED);
  chassis.pid_wait_until(18_in);
  chassis.pid_speed_max_set(60);
  pros::delay(500);



  // Go touch the ladder?
  
  chassis.pid_turn_relative_set(-197_deg, TURN_SPEED);
  chassis.pid_drive_set(50_in, DRIVE_SPEED);
  chassis.pid_wait_until(28_in);
  intakeTask.remove();
  colourSortTask.remove();
  intake.move(0);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait();


/*
  // ~~ Turn and intake rings in the corner ~~
  chassis.pid_turn_relative_set(66_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait_until(24_in);
  doinker.extend();
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-30_deg, TURN_SPEED);
*/

  // ~~ Go to the corner of the ladder (drop the mobile goal halfway) ~~
  //chassis.pid_turn_relative_set(xx_deg, speed);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, speed);
  //chassis.pid_wait_until(xx_in);
  //MogoClamp.set_value(false);
  //chassis.pid_wait();

}

void riskyAWPRight() { // AWP on the right side, rushes center mogo
  // ~~ Move backwards as fast as possible to get the center mobile goal
  //chassis.pid_drive_set(-xx_in, DRIVE_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(-xx_in, speed);
  //chassis.pid_wait();

  // ~~ get the center goal ~~
  //MogoClamp.set_value(true);
  
  // ~~ get the nearest ring ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait();
  //intake.move(INTAKE_SPEED);
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);

  // ~~ turn and drop mogo to the back ~~ //
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait();
  //intake.move(0);
  //MogoClamp.set_value(false);

  // ~~ 180 then back into the second mogo, grab it ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait();
  //MogoClamp.set_value(false);

  // ~~ Grab the next ring ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait_until(xx_in);
  //intake.move(120);
  //chassis.pid_wait();

  // ~~ Go touch the ladder (drop the mogo on the way) ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //intake.move(0);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //MogoClamp.set_value(false);
  //chassis.pid_wait();

}

void riskyAWPLeft() { // AWP on the left side, rushes center mogo
  // Run through the line of rings
  intake.move(127);
  chassis.pid_drive_set(40_in, 70 );
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(40);
  chassis.pid_wait();

  // Turn around and grab the mobile goal
  chassis.pid_turn_set(10, TURN_SPEED);
  
  // 


  pros::delay(5000);


  // ~~ Move backwards as fast as possible to get the center mobile goal

  /*chassis.pid_drive_set(-30_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_relative_set(25_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-4_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
  chassis.pid_wait();*/

  //chassis.pid_swing_relative_set(ez::RIGHT_SWING, -30, 110);
  //chassis.pid_wait();


  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(-xx_in, speed);
  //chassis.pid_wait();

  // ~~ get the center goal ~~
  //MogoClamp.set_value(true);
  
  // ~~ get the nearest ring ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait();
  //intake.move(INTAKE_SPEED);
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);

  // ~~ turn and drop mogo to the back ~~ //
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait();
  //intake.move(0);
  //MogoClamp.set_value(false);

  // ~~ 180 then back into the second mogo, grab it ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait();
  //MogoClamp.set_value(false);

  // ~~ Grab the next ring ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait_until(xx_in);
  //intake.move(120);
  //chassis.pid_wait();

  // ~~ Go touch the ladder (drop the mogo on the way) ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //intake.move(0);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //MogoClamp.set_value(false);
  //chassis.pid_wait();

}

void AWPRight() {
  // Move to wall stake
  chassis.pid_drive_set(12.5_in, 90);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(2.3_in, 50);
  chassis.pid_wait();

  // ~ SCORE WALL STAKE ~
  // Initalize arm
  // Variables
  double targetAngle = 110; // How much the actual arm should turn
  double gearRatio = 5; // 60:12 gear ratio
  double MAX_ANGLE = targetAngle * gearRatio;
  double INIT_ANGLE = 40 * gearRatio;
  double currentPosition = arm.get_position();


  // Start match with arm up
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  // Start intake managing task
  pros::Task intakeTask(unstuckIntake); 

  // ~~ Score Preload onto alliance stake ~~
  arm.move_absolute(MAX_ANGLE, 70*(MAX_ANGLE-currentPosition)); // Slow down the arm as it approaches the target angle
  while (currentPosition < MAX_ANGLE-1) {
    currentPosition = arm.get_position();
    pros::delay(2);
  }  
  pros::delay(500);
  // Move arm back down
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  // ~ GET THE MOGO ~
  //chassis.pid_drive_set(-4_in, DRIVE_SPEED);
  //chassis.pid_wait();
  chassis.pid_turn_relative_set(37_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();
  MogoClamp.set_value(true);
  pros::delay(1000);

  // Get Ring 1
  chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(28_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(500);

  // Get Ring 2
  chassis.pid_turn_relative_set(-105_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(13_in, 70);
  chassis.pid_wait_until(4);
  chassis.pid_speed_max_set(40);
  chassis.pid_wait();
  pros::delay(1500);
  chassis.pid_drive_set(-13_in, 70);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(20_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(14_in, 70);
  chassis.pid_wait_until(4);
  chassis.pid_speed_max_set(40);
  chassis.pid_wait();
  pros::delay(2000);
  chassis.pid_drive_set(-14_in, 70);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-92_deg, TURN_SPEED);

  // Go to the ladder
  chassis.pid_wait();
  chassis.pid_drive_set(65_in, DRIVE_SPEED);
  chassis.pid_wait_until(35_in); 
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  intakeTask.remove();


}

void AWPLeft() {
  // Move to wall stake
  chassis.pid_drive_set(12.5_in, 90);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(2.1_in, 50);
  chassis.pid_wait();

  // ~ SCORE WALL STAKE ~
  // Initalize arm
  // Variables
  double targetAngle = 110; // How much the actual arm should turn
  double gearRatio = 5; // 60:12 gear ratio
  double MAX_ANGLE = targetAngle * gearRatio;
  double INIT_ANGLE = 46 * gearRatio;
  double currentPosition = arm.get_position();


  // Start match with arm up
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  // ~~ Score Preload onto alliance stake ~~
  arm.move_absolute(MAX_ANGLE, 70*(MAX_ANGLE-currentPosition)); // Slow down the arm as it approaches the target angle
  while (currentPosition < MAX_ANGLE-1) {
    currentPosition = arm.get_position();
    pros::delay(2);
  }  
  pros::delay(500);
  // Move arm back down
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  // ~ GET THE MOGO ~
  chassis.pid_drive_set(-4_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-37_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();
  MogoClamp.set_value(true);
  pros::delay(50);
    // Start intake managing task
  intake.move(INTAKE_SPEED);
  pros::Task intakeTask(unstuckIntake); 

  // Get Ring 1
  chassis.pid_turn_relative_set(135_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(28_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(300);

  // Get Ring 2
  chassis.pid_turn_relative_set(105_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(13_in, 70);
  chassis.pid_wait_until(4_in);
  chassis.pid_speed_max_set(40);
  chassis.pid_wait();
  pros::delay(500);
  chassis.pid_drive_set(-13_in, 70);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-23_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(13.5_in, 70);
  chassis.pid_wait_until(4_in);
  chassis.pid_speed_max_set(40);
  chassis.pid_wait();
  pros::delay(500);
  chassis.pid_drive_set(-13.5_in, 70);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(92_deg, TURN_SPEED);

  // Go to the ladder
  chassis.pid_wait();
  chassis.pid_drive_set(65_in, DRIVE_SPEED);
  chassis.pid_wait_until(35_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  intakeTask.remove();


}

void testIntakeTask() {
  // Start intake managing task
  pros::Task intakeTask(unstuckIntake);  

  intake.move(INTAKE_SPEED);
  waitUntilRingIntaked();
  intake.move(0);

}


void skillsAuto() {
  /*
  // Initalize arm
  // Variables
  double targetAngle = 110; // How much the actual arm should turn
  double gearRatio = 5; // 60:12 gear ratio
  double MAX_ANGLE = targetAngle * gearRatio;
  double INIT_ANGLE = 45 * gearRatio;
  double currentPosition = arm.get_position();


  // Start match with arm up
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  */

  // Release the intake
  intake.move(INTAKE_SPEED);
  pros::delay(200);
  intake.move(0);

  // Release the intake
  intake.move(-INTAKE_SPEED);
  pros::delay(75);
  intake.move(0);


  // Start intake managing task
  pros::Task intakeTask(unstuckIntake); 

  /*
  // ~~ Score Preload onto alliance stake ~~
  arm.move_absolute(MAX_ANGLE, 70*(MAX_ANGLE-currentPosition)); // Slow down the arm as it approaches the target angle
  while (currentPosition < MAX_ANGLE-1) {
    currentPosition = arm.get_position();
    pros::delay(2);
  }  
  pros::delay(500);
  // Move arm back down
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }
*/
  // ~~ get the left mogo ~~
  chassis.pid_drive_set(-8_in, 70);
  chassis.pid_wait(); 
  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-23_in, DRIVE_SPEED);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();
  MogoClamp.set_value(true);
  pros::delay(100);

  // ~~ collect 6 rings on the left ~~
  intake.move(INTAKE_SPEED);
  chassis.pid_turn_relative_set(-104_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait_until(18_in);
  chassis.pid_speed_max_set(100);
  chassis.pid_wait();
  // 1st ring done

  chassis.pid_turn_relative_set(-44_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(35_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in); // 18
  chassis.pid_speed_max_set(80);
  chassis.pid_wait();
  pros::delay(100);
  // 2nd ring done

  chassis.pid_turn_relative_set(-136_deg, 100);
  chassis.pid_wait();
  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait_until(17_in);
  chassis.pid_speed_max_set(100);
  chassis.pid_wait();
  // 3rd ring done

  chassis.pid_turn_relative_set(50, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(21_in, 100);
  chassis.pid_wait(); 
  pros::delay(100);
  chassis.pid_drive_set(-12_in, 100);
  chassis.pid_wait();
  chassis.pid_swing_relative_set(LEFT_SWING, -43_deg, 100);
  chassis.pid_wait();
  // 4th Ring done

  chassis.pid_drive_set(15.3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_relative_set(15_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(12_in, DRIVE_SPEED);
  chassis.pid_wait();
  // 5th, 6th Ring done

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(-136_deg, TURN_SPEED);
  chassis.pid_wait();
  MogoClamp.set_value(false);
  chassis.pid_drive_set(-15.3_in, 95);
  chassis.pid_wait();
  //chassis.pid_drive_set(16_in, 80);
  //chassis.pid_wait();
  //chassis.pid_drive_set(-16_in, DRIVE_SPEED);
  //chassis.pid_wait();
  chassis.pid_drive_set(16.3_in, 80);
  chassis.pid_wait();
  // Back into the corner and drop the mogo

  // ~~ Get the second mogo ~~
  chassis.pid_turn_relative_set(-142.5_deg, TURN_SPEED);
  chassis.pid_wait();
  //chassis.pid_drive_set(32.5_in, DRIVE_SPEED);
  //chassis.pid_wait_until(20_in);
  //chassis.pid_speed_max_set(70);
  //chassis.pid_wait();
  chassis.pid_drive_set(-68_in, 80);
  chassis.pid_wait_until(-30_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();
  MogoClamp.set_value(true);

  // ~~ collect 6 rings on the right ~~
  intake.move(INTAKE_SPEED);
  chassis.pid_turn_relative_set(96_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait_until(18_in);
  chassis.pid_speed_max_set(70);
  chassis.pid_wait();
  // 1st ring done

  chassis.pid_turn_relative_set(54_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(37_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();
  pros::delay(200);
  // 2nd ring done

  chassis.pid_turn_relative_set(139_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait_until(17_in);
  chassis.pid_speed_max_set(88);
  chassis.pid_wait();
  // 3rd ring done

  chassis.pid_turn_relative_set(-52.5_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(21_in, 70);
  chassis.pid_wait(); 
  pros::delay(100);
  chassis.pid_drive_set(-12_in, 70);
  chassis.pid_wait();
  chassis.pid_swing_relative_set(RIGHT_SWING, 43_deg, 100);
  chassis.pid_wait();
  // 4th Ring done

  chassis.pid_drive_set(15.3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_relative_set(-10_deg, TURN_SPEED);
  chassis.pid_wait();
  pros::delay(100);
  chassis.pid_drive_set(14_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(100);
  // 5th, 6th Ring done

  chassis.pid_turn_relative_set(136_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, 95);
  chassis.pid_wait();
  MogoClamp.set_value(false);
  //chassis.pid_drive_set(24_in, 80);
  //chassis.pid_wait();
  //chassis.pid_drive_set(-23_in, DRIVE_SPEED);
  //chassis.pid_wait();
  chassis.pid_drive_set(9_in, 80);
  chassis.pid_wait();
  // Back into the corner and drop the mogo

  // ~~ Set up next side ~~
  chassis.pid_turn_relative_set(49_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(75_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(420);
  intake.move(0);
  intakeTask.suspend();

  // Push 3rd mogo in corner
  chassis.pid_turn_relative_set(-53_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(48_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_relative_set(LEFT_SWING, 130, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Get the third empty mogo
  chassis.pid_turn_relative_set(-30_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_relative_set(50_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-200_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  //chassis.pid_wait_until(-30_in);
  //chassis.pid_speed_max_set(60);
  //chassis.pid_wait();
  //MogoClamp.set_value(true);
  pros::delay(400);

  intake.move(INTAKE_SPEED);
  intakeTask.resume();
  //chassis.pid_turn_relative_set(30_deg, TURN_SPEED);
  //chassis.pid_wait();
  //chassis.pid_drive_set(36_in, DRIVE_SPEED);
  //chassis.pid_wait();
  // 1st ring done

  chassis.pid_drive_set(54_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(121_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait();
  intake.move(0);
  intakeTask.suspend();
  MogoClamp.set_value(false);
  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  chassis.pid_wait();
  MogoClamp.set_value(true);
  chassis.pid_drive_set(-9_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  // Put 3rd mogo in corner

  chassis.pid_turn_relative_set(30_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(27_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_relative_set(-137_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-200_in, DRIVE_SPEED);
  chassis.pid_wait();

  pros::delay(100000);

  intakeTask.remove();

}

void driverSkillsAuto() {
    // Initalize arm
  // Variables
  double targetAngle = 110; // How much the actual arm should turn
  double gearRatio = 5; // 60:12 gear ratio
  double MAX_ANGLE = targetAngle * gearRatio;
  double INIT_ANGLE = 45 * gearRatio;
  double currentPosition = arm.get_position();


  // Start match with arm up
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  // Start intake managing task
  pros::Task intakeTask(unstuckIntake); 

  // ~~ Score Preload onto alliance stake ~~
  arm.move_absolute(MAX_ANGLE, 70*(MAX_ANGLE-currentPosition)); // Slow down the arm as it approaches the target angle
  while (currentPosition < MAX_ANGLE-1) {
    currentPosition = arm.get_position();
    pros::delay(2);
  }  
  pros::delay(500);
  // Move arm back down
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
  // Continue running this loop as long as the motor is not within +-5 units of its goal
  pros::delay(2);
  }

  // ~~ get the left mogo ~~
  chassis.pid_drive_set(-9_in, 70);
  chassis.pid_wait(); 
  chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-22.7_in, DRIVE_SPEED);
  chassis.pid_wait_until(-7_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait_until(-22_in);
  MogoClamp.set_value(true);
  chassis.pid_wait();

  intakeTask.remove();
}


void unstuckIntake() {

  while (true) {

   // Trigger push back if the intake stops moving
    if (intake.get_efficiency() < 5.0) {
      intake.move(-100);
      pros::delay(500);
      intake.move(INTAKE_SPEED);
    }

    pros::delay(100);

  }
}


void colourSort() {
  while (true) {
    if (checkIsColour(ENEMY_COLOUR, 25)) {
      intake.move(-INTAKE_SPEED);
      pros::delay(2000);
      intake.move(INTAKE_SPEED);
    }
    pros::delay(10);
  }

}

void waitUntilRingIntaked() {
  bool hasRing = false;
  intakeDelayTime = 20;
    
  int timeElapsed = 0;

  while (!hasRing && timeElapsed < 3000) { // Wait a maximum of 4 seconds
    if (checkIsColour(RED, 25) || checkIsColour(BLUE, 25)) {
      hasRing = true;
    } 
    timeElapsed += 5;
    pros::delay(5);
  }

  intakeDelayTime = 750;
}

void waitUntilAllyRingIntaked() {
  bool hasRing = false;
  intakeDelayTime = 20;
    
  int timeElapsed = 0;

  while (!hasRing && timeElapsed < 2500) { // Wait a maximum of 4 seconds
    if (checkIsColour(ALLY_COLOUR, 25)) {
      hasRing = true;
    } 
    timeElapsed += 5;
    pros::delay(5);
  }

  intakeDelayTime = 750;
}

void stopWhenRingIntaked() {
  bool hasRing = false;
    
  int timeElapsed = 0;

  while (!hasRing && timeElapsed < 10000) { // Wait a maximum of 4 seconds
    if (checkIsColour(RED, 25) || checkIsColour(BLUE, 25)) {
      hasRing = true;
    } 
    timeElapsed += 5;
    pros::delay(5);
  }

  intake.move(0);
}
