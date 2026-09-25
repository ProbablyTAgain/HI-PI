#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
void autonomous() {}

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
#include "main.h"
#include <stdio.h>

void opcontrol() {
    // Initialize the LLEMU (Legacy LCD Emulator) on the V5 Screen
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Waiting for Pi...");

    char buffer[50]; // Buffer to store the incoming string
    int index = 0;

    while (true) {
        // Read characters from standard input (USB connection)
        int c = getchar();

        // If a valid character is read and it's not EOF (End of File)
        if (c != EOF) {
            // Check for newline character which indicates end of message
            if (c == '\n' || index >= sizeof(buffer) - 1) {
                buffer[index] = '\0'; // Null-terminate the string
                
                // Print the message received from the Pi onto line 2 of the brain screen
                pros::lcd::print(2, "From Pi: %s", buffer);
                
                index = 0; // Reset index for the next message
            } else {
                buffer[index] = (char)c;
                index++;
            }
        }

        pros::delay(10); // Small delay to prevent resource hogging
    }
}
