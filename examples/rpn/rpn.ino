#include <omniMath.h>

//=== Initializing omniMath library ===
omniMath omniMath;

void setup() {
    //=== Initializing Serial ===
    Serial.begin(9600);
}

void loop() {
    //=== Converting to RPN notation ===
    /* 
     * 
     */
    String rpnEquation = omniMath.convertToRPN("321+4*(43-12*4)*3.5+43-1+2^3");
    //
    //---- Printing RPN ----
    Serial.print("RPN equation: ");
    Serial.print(rpnEquation);

    //=== Converting to RPN notation ===
    /* 
     *
     */
    String evaluatedRpn = omniMath.evaluateRPN(rpnEquation);
    //
    //---- Printing evaluated RPN ----
    Serial.print(" evaluated RPN: ");
    Serial.println(evaluatedRpn);
}
