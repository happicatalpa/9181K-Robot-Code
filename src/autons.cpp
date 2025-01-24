#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Default speeds
// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;
const int INTAKE_SPEED = 127;
const int ARM_SPEED = 110;
const int BLUE = 190; // colour of blue ring
const int RED = 13; // colour of red ring

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_forward_set(9, .005, 4.5);
  chassis.pid_drive_constants_backward_set(9.1, 0.025,1.75);
  chassis.pid_turn_constants_set(2.4, 0, 10.25, 15);
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

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
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

void safeAWPLeft() { // right side for now
  // ~~ Move back and score preload onto the alliance stake ~~
  //chassis.pid_drive_set(xx_in, speed);
  //chassis.pid_wait();
  //arm.move(127);

  // ~~ Turn and move backwards towards the nearest mobile goal ~~
  MogoClamp.retract();
  chassis.pid_turn_relative_set(12_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-30_in, DRIVE_SPEED);
  chassis.pid_wait();

  // ~~ Clamp onto the goal ~~
  MogoClamp.extend();

  // ~~ Turn and intake the ring on the right ~~
  //chassis.pid_turn_relative_set(xx_deg, speed);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, speed);
  //chassis.pid_wait_until(xx_in)
  //intake.move(120);
  //chassis.pid_wait();
  //intake.move(0);

  // ~~ Turn and intake rings in the corner ~~
  //chassis.pid_turn_relative_set(xx_deg, speed);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, speed)
  //chassis.pid_wait_until(xx_in);
  //intake.move(120);
  //chassis.pid_wait();
  //pros::delay(2000);

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

void testIntakeTask() {
  // Start intake managing task
  pros::Task intakeTask(unstuckIntake); 

  intake.move(INTAKE_SPEED);
  pros::delay(200000);

}


void skillsAuto() {
  // Start intake managing task
  pros::Task intakeTask(unstuckIntake); 

  // ~~ Score Preload onto alliance stake ~~
  //arm.move(ARM_SPEED);
  //pros::delay(1000);

  // ~~ get the left mogo ~~
  chassis.pid_drive_set(-10_in, 70);
  chassis.pid_wait_until(3.8_in);
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(-xx_in, DRIVE_SPEED);
  MogoClamp.set_value(true);
  chassis.pid_wait();

  // ~~ collect 6 rings on the left ~~
  intake.move(INTAKE_SPEED);
  chassis.pid_turn_relative_set(-157_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(1000);
  // 1st ring done

  chassis.pid_turn_relative_set(-75_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(31_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(1000);
  // 2nd ring done

  chassis.pid_turn_relative_set(66_deg, 100);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(26_in, DRIVE_SPEED);
  chassis.pid_wait_until(17_in);
  chassis.pid_speed_max_set(88);
  chassis.pid_wait();
  pros::delay(1700);
  // 3rd ring done

  chassis.pid_drive_set(-26_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(179_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(750);
  chassis.pid_turn_relative_set(17_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(14_in, 95);
  chassis.pid_wait();
  pros::delay(1200);
  // 4, 5th ring done

  chassis.pid_drive_set(-36_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_relative_set(23_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(25_in, 70);
  chassis.pid_wait_quick_chain();
  pros::delay(2000);
  // 6th ring done

  // ~~ put 1st mogo into corner ~~
  chassis.pid_turn_relative_set(-163_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  MogoClamp.set_value(false);
  pros::delay(20);
  intake.move(0);
  chassis.pid_drive_set(8_in, 90);
  chassis.pid_wait_quick_chain();


  // ~~ get second mogo ~~
  chassis.pid_turn_relative_set(-130_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-90_in, DRIVE_SPEED);
  chassis.pid_wait_until(-50_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait();
  MogoClamp.set_value(true);

  // ~~ collect 6 rings on the right ~~
  chassis.pid_turn_relative_set(80_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move(INTAKE_SPEED);
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(1000);
  // 1st ring done

  chassis.pid_turn_relative_set(92_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(24_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(1000);
  // 2nd ring done

  chassis.pid_turn_relative_set(-49_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(26_in, 100);
  chassis.pid_wait();
  pros::delay(1000);
  // 3rd ring done

  chassis.pid_drive_set(-26_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_relative_set(179_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(750);
  //chassis.pid_turn_relative_set(-17_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(14_in, 95);
  //chassis.pid_wait();
  //pros::delay(1200);
  // 4, 5th ring done

  //chassis.pid_wait_quick_chain();
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait_quick_chain();
  // 6th ring done
  //intake.move(0);

  // ~~ put 2nd mogo into corner ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(-xx_in, DRIVE_SPEED);
  //chassis.pid_wait_quick_chain();
  //MogoClamp.set_value(false);
  //pros::delay(20);

  // ~~ Store two rings ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait_until(xx_in);
  //intake.move(INTAKE-SPEED);
  //pros::delay(xx):
  //intake.move(0);
  // 1st ring done
  //chassis.pid_wait_quick_chain();
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(xx_in, DRIVE_SPEED);
  //chassis.pid_wait_until(xx_in);
  //intake.move(INTAKE-SPEED);
  //pros::delay(xx):
  //intake.move(0);
  // 2nd ring done
  //chassis.pid_wait();

  // ~~ Get 3rd mogo ~~
  //chassis.pid_turn_relative_set(xx_deg, TURN_SPEED);
  //chassis.pid_wait_quick_chain();
  //chassis.pid_drive_set(-xx_in, DRIVE_SPEED);
  //chassis.pid_wait();
  //MogoClamp.set_value(true);
  
  // ~~ get the last 4 rings ~~
  // too tired :(

  chassis.pid_wait();
  pros::delay(10000);

  intakeTask.remove();

}



void unstuckIntake() {
  bool isRed;
  bool isBlue;

  while (true) {
    // Only trigger the push back if there is no ring at the roller intake
    isRed = checkIsColour(RED, 25);
    isBlue = checkIsColour(BLUE, 20);

    // Trigger push back if the intake stops moving
    if (intake.get_efficiency() < 5.0) {
      intake.move(-100);
      if (isRed || isBlue) {
        pros::delay(250); 
      }
      else {
        pros::delay(750);
      }
      
      intake.move(INTAKE_SPEED);
    }

    pros::delay(100);

  }
}

