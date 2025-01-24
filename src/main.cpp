#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-19, -18, -8},     // Left Chassis Ports (negative port will reverse it!)
    {3, 2, 1},  // Right Chassis Ports (negative port will reverse it!) back to front

    15,      // IMU Port
    2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


// GLOBAL CONSTANTS
const int BLUE = 190; // colour of blue ring
const int RED = 11; // colour of red ring
const int TEAM_COLOUR = RED; // CHANGE THIS WHEN SWITCHING TEAMS (Should be the opponent's colour)



void initialize() {

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU

  ez::as::auton_selector.autons_add({
      Auton("Skills Auto", skillsAuto),
      Auton("Test the intake task", testIntakeTask),
      Auton("Heritage Left Auto", HeritageAutoLeft),
      Auton("Heritage Right Auto", HeritageAutoRight),
      Auton("Risky AWP Left", riskyAWPLeft),
      Auton("Drive forward.", drive_forward),
      Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Right side match auto.", SeaquamAutoRight),
      Auton("Left side mathc auto.", SeaquamAutoRight),
      Auton("trial skills", trial_skills_auto),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
      Auton("AWP safe left side", safeAWPLeft),
      Auton("AWP risky right side", riskyAWPRight),

  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");

  // Reset motor encoder position to zero for the wall stake arm
  arm.tare_position();
  arm.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);

  // Initalize arm
  arm.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
  arm.brake();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
 

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency


  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  
  // Start Subsystem Threads
  pros::Task armControlTask(armControl); 
  pros::Task mogoClampControlTask(clampControl);
  pros::Task intakeControlTask(intakeControl);
  pros::Task scoreSensingTask (scoreSensing);


  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;
  chassis.drive_brake_set(driver_preference_brake);

  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X))
        chassis.pid_tuner_toggle();

      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_LEFT) && master.get_digital(DIGITAL_DOWN)) {

        // Pause driver control threads
        armControlTask.suspend();
        mogoClampControlTask.suspend();
        intakeControlTask.suspend();
        scoreSensingTask.suspend();

        // Run autonomous
        autonomous();

        // Resume driver control threads
        armControlTask.resume();
        mogoClampControlTask.resume();
        intakeControlTask.resume();
        scoreSensingTask.resume();

        chassis.drive_brake_set(driver_preference_brake);
      }

      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }
  
    chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
   
    
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

void armControl() {
  // Variables
  double targetAngle = 110; // How much the actual arm should turn
  double gearRatio = 5; // 60:12 gear ratio
  double MAX_ANGLE = targetAngle * gearRatio;
  double INIT_ANGLE = 35 * gearRatio;

  // Start match with arm up
  arm.move_absolute(INIT_ANGLE, 100);
  while (!((arm.get_position() < INIT_ANGLE+15) && (arm.get_position() > INIT_ANGLE-15))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  


  while (true) {
    double currentPosition = arm.get_position();

    // Driver Control 
    if (master.get_digital(DIGITAL_L1)) { // move the arm forward when the button is pressed
      if (currentPosition < MAX_ANGLE) {
        arm.move_absolute(MAX_ANGLE, 70*(MAX_ANGLE-currentPosition)); // Slow down the arm as it approaches the target angle
      }

      else {
        arm.move_velocity(0);
      }
    }
    else if ((master.get_digital(DIGITAL_B))) {
      arm.move_absolute(0, -70*currentPosition);
      while (!((arm.get_position() < 5) && (arm.get_position() > -5))) {
        // Continue running this loop as long as the motor is not within +-5 units of its goal
        pros::delay(2);
      }
    }
    else {
      if (currentPosition > INIT_ANGLE) {
        arm.move_absolute(INIT_ANGLE, -80*currentPosition);
      }
    }

    pros::delay(50);
  }
}

void clampControl() {
  // Control loop
  while (true) {

    if (master.get_digital_new_press(DIGITAL_R1)) {
        //switch the state of mogo clamp
        MogoClamp.toggle();
      }

    pros::delay(50);
  }

}
// refactor instake code
void intakeControl () {
  int INTAKE_SPEED = 112;

  // INTAKE CONTROL LOOP
  while (true) {
    
    // Driver control
    if (master.get_digital(DIGITAL_R2)) {
      // Set intake speed to max if the arm is in the lowest position
      if (-5 < arm.get_position() && arm.get_position() < 5) {
        intake.move(120);
      }
      else {
        intake.move(INTAKE_SPEED); // in-take
      }
      
      // COLOUR SORT -- Slow down intake if it is the wrong colour to prevent scoring
      /*if (!isAllianceColour()) { 
        intake.move(40);
      }*/
    }
    else if (master.get_digital(DIGITAL_L2)){
      intake.move(-100); // out-take
    }
    else {
      intake.move(0);
    }

    pros::delay(50);
  }
}


// Shake the controller to warn the driver when they can score onto the wall stake
void scoreSensing () {
  const double scoringRange = 15; // Distance from the wall that the robot has to be to score on wall stake, in cm
  bool sensingActivated = false; // Toggle to activate distance sensing

  while (true) {
    if (sensingActivated) {
      double distance = wallMechSensor.get_value(); // get distance to the closest object in front of the robot, in cm
      if (scoringRange + 3 > distance && distance > scoringRange - 3) { // Check if the robot is within +/- 3cm of the range
        master.rumble(".-.-"); // warn driver by shaking controller
      }
    }
    
    // Toggle distance sensig
    if (master.get_digital_new_press(DIGITAL_DOWN)) {
      sensingActivated = !sensingActivated;
    }

    pros::delay(100);
  }
}


// Automatically close the mobile goal clamp if a mobile goal is in range
void mogoSensing () {

  while (true) {
    // Check that the clamp is not already holding a mobile goal; close the clamp if the limit switch is triggered
    if (!MogoClamp.is_extended() && clampLimitSwitch.get_new_press()) {
        MogoClamp.extend();
    }

    pros::delay(50);
  }

}

bool isAllianceColour() {
  int this_colour;

  this_colour = optical.get_hue();

  // Check to see if current colour is +/- 20 the RGB value of team colour
  if (this_colour < (TEAM_COLOUR + 10) && this_colour > (TEAM_COLOUR - 10)) { 
      return true;
  }
  else {
    return false;
  }
}

bool checkIsColour(int thisColor, int range) {
  int detectedColour;

  detectedColour = optical.get_hue();

  // Check to see if current colour is +/- 20 the RGB value of team colour
  if (detectedColour < (thisColor + range) && detectedColour > (thisColor - range)) { 
      return true;
  }
  else {
    return false;
  }
}