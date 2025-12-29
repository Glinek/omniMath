/*
 * Title:       example of evaluating math equations
 * Made by:     Szymon "Glinek" Glinka
 * Date:        09.12.2025
 * Rev.:        1
 * Description: This is an example of evaluating various mathematical expressions using omniMath library
 * Notice:      For more complete documentation visit https://github.com/Glinek/omniMath
*/

#include <omniMath.h>

//=== Initializing library ===
omniMath myMath;

void setup() {
    //=== Initialize Serial connection ===
    Serial.begin(9600);
}

void loop() {
    /*
     * IMPORTANT! evaluate functions takes equation OR one of the functions as input. YOU CAN NOT MIX THEM!
     */

    //=== Evaluating math equations ===
    /*
     * evaluate function parses and solves standard mathematical equations.
     * It handles order of operations for addition, subtraction, multiplication, division and parentheses.
     */
    String eval1 = myMath.evaluate("23+54*4+(34-5+3)*2.58");
    //
    //---- Printing result ----
    Serial.print("Equation: ");
    Serial.println(eval1);

    //=== Evaluating trigonometric function ===
    /*
     * Calculates trigonometric values (sin, cos, tan, etc.).
     * Input angle is in degrees. Example: "sin 30" returns 0.5.
     */
    String eval2 = myMath.evaluate("sin 30");
    //
    //---- Printing result ----
    Serial.print("Sine 30deg: ");
    Serial.println(eval2);

    //=== Evaluating roots ===
    /*
     * Calculates N-th root of a value using syntax "VALUE rt ROOT".
     * In this example: 6th root of 64.
     */
    String eval3 = myMath.evaluate("64 rt 6");
    //
    //---- Printing result ----
    Serial.print("Root 6th root of 64: ");
    Serial.println(eval3);

    //=== Generating random number ===
    /*
     * Generates a random number within a range with a specific step.
     * Syntax: "rand MIN MAX STEP".
     */
    String eval4 = myMath.evaluate("rand 0 10 0.1");
    //
    //---- Printing result ----
    Serial.print("Random number between 0 and 10, step 0.1: ");
    Serial.println(eval4);

    //=== Getting constants ===
    /*
     * Returns mathematical constants.
     * "pi" returns value of PI, "e" or "euler" returns Euler's number.
     */
    String eval5 = myMath.evaluate("pi");
    //
    //---- Printing result ----
    Serial.print("Pi: ");
    Serial.println(eval5);
}