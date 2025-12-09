#include <omniMath.h>

//=== Initializing library ===
omniMath omniMath;

void setup() {
    //=== Initializing serial ===
    Serial.begin(9600);
}

void loop() {
    //=== Evaluating math ===
    /*
     *
     */
    String eval1 = omniMath.evaluate("23+54*4+(34-5+3)*2.58");
    Serial.print("Equation: ");
    Serial.println(eval1);
    //
    /*
     *
     */
    String eval2 = omniMath.evaluate("sin 30");
    Serial.print("Sine 30deg: ");
    Serial.println(eval2);
    //
    /*
     *
     */
    String eval3 = omniMath.evaluate("64 rt 6");
    Serial.print("Root 6th root of 64: ");
    Serial.println(eval3);
    //
    /*
     *
     */
    String eval4 = omniMath.evaluate("rand 0 10 0.1");
    Serial.print("Random number between 0 and 10, step 0.1: ");
    Serial.println(eval4);
    //
    /*
     *
     */
    String eval5 = omniMath.evaluate("pi");
    Serial.print("Pi: ");
    Serial.println(eval5);
}
