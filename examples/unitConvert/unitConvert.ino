#include <omniMath.h>

//=== Initializing library ===
omniMath omniMath;

void setup() {
    //=== Initializing serial ===
    Serial.begin(9600);
}

void loop() {
    //=== Converting units ===
    /*
     *
     */
    String convertedTemp = omniMath.convertUnit("100", omniMath.degC, omniMath.degF);
    Serial.print("Converted temp: ");
    Serial.println(convertedTemp);
    //
    /*
     *
     */
    String convertedMass = omniMath.convertUnit("1", omniMath.kg, omniMath.lb);
    Serial.print("Converted mass: ");
    Serial.println(convertedMass);
    //
    /*
     *
     */
    String convertedLength = omniMath.convertUnit("100", omniMath.ft, omniMath.m);
    Serial.print("Converted length: ");
    Serial.println(convertedLength);
    //
    /*
     *
     */
    String convertedCharge = omniMath.convertUnit("2500", omniMath.mAh, omniMath.C);
    Serial.print("Converted charge: ");
    Serial.println(convertedCharge);
}
