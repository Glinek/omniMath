/*
 * Title:       example of converting and evaluating RPN notation
 * Made by:     Szymon "Glinek" Glinka
 * Date:        09.12.2025
 * Rev.:        1
 * Description: This is an example of converting equation to RPN notation and then evaluating this notation
 * Notice:      For more complete documentation visit https://github.com/Glinek/omniMath
*/

//=== Include omniMath library ===
#include <omniMath.h>

//=== Create omniMath object ===
omniMath myMath;

void setup() {
    //=== Initialize Serial connection ===
    Serial.begin(9600);
}

void loop() {
    //=== Converting to RPN notation ===
    /*
     * convertToRPN function converts regular notation into RPN, the allowed operators are: '( ) + - * / ^ .'. 
     * IMPORTANT! operators and numbers can not be separated by a space!
     * This function takes equation as a string as an input and returns equation converted to RPN as a string. 
     */
    String rpnEquation = myMath.convertToRPN("321+4*(43-12*4)*3.5+43-1+2^3");
    //
    //---- Printing RPN ----
    Serial.print("RPN equation: ");
    Serial.print(rpnEquation);

    //=== Converting to RPN notation ===
    /* 
     *  evaluateRPN evaluates RPN equation. It takes RPN equation as a string as an input and returns evaluated equation also as a string
     */
    String evaluatedRpn = myMath.evaluateRPN(rpnEquation);
    //
    //---- Printing evaluated RPN ----
    Serial.print(" evaluated RPN: ");
    Serial.println(evaluatedRpn);
}
