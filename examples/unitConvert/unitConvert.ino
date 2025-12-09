/*
 * Title:       example of unit conversion
 * Made by:     Szymon "Glinek" Glinka
 * Date:        09.12.2025
 * Rev.:        1
 * Description: This is an example of converting various units (temperature, mass, length, charge) using omniMath library
 * Notice:      For more complete documentation visit https://github.com/Glinek/omniMath
*/

#include <omniMath.h>

//=== Initializing library ===
omniMath omniMath;

void setup() {
    //=== Initialize Serial connection ===
    Serial.begin(9600);
}

void loop() {
    //=== Converting Temperature ===
    /*
     * convertUnit function converts values between specified units.
     * Here: converting 100 degrees Celsius to Fahrenheit.
     */
    String convertedTemp = omniMath.convertUnit("100", omniMath.degC, omniMath.degF);
    //
    //---- Printing converted temp ----
    Serial.print("Converted temp: ");
    Serial.println(convertedTemp);

    //=== Converting Mass ===
    /*
     * Converts mass units using defined constants.
     * Here: converting 1 Kilogram to Pounds (lb).
     */
    String convertedMass = omniMath.convertUnit("1", omniMath.kg, omniMath.lb);
    //
    //---- Printing converted mass ----
    Serial.print("Converted mass: ");
    Serial.println(convertedMass);

    //=== Converting Length ===
    /*
     * Converts length units.
     * Here: converting 100 Feet to Meters.
     */
    String convertedLength = omniMath.convertUnit("100", omniMath.ft, omniMath.m);
    //
    //---- Printing converted length ----
    Serial.print("Converted length: ");
    Serial.println(convertedLength);

    //=== Converting Charge ===
    /*
     * Converts electric charge units.
     * Here: converting 2500 milliamp-hours (mAh) to Coulombs (C).
     */
    String convertedCharge = omniMath.convertUnit("2500", omniMath.mAh, omniMath.C);
    //
    //---- Printing converted charge ----
    Serial.print("Converted charge: ");
    Serial.println(convertedCharge);
}
