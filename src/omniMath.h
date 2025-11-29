#ifndef OMNIMATH_H
#define OMNIMATH_H
    #include <Arduino.h>

    class omniMath{
        public:
            enum UnitType {
                // Length (Base: Meter)
                METER,
                KILOMETER,
                CENTIMETER,
                MILLIMETER,
                INCH,
                FOOT,
                YARD,
                MILE,

                // Mass (Base: Kilogram)
                KILOGRAM,
                GRAM,
                MILLIGRAM,
                POUND,
                OUNCE,

                // Energy (Base: WATTtHour)
                MILIWATTHOUR,
                WATTHOUR,
                KILOWATTHOUR,
                GIGAWATTHOUR,
                JOULE,        // New: 1 Wh = 3600 J
                KILOJOULE,    // New
                MEGAJOULE,    // New
                CALORIE,      // New: 1 cal = 4.184 J
                KILOCALORIE,  // New
                BTU,          // New: British Thermal Unit
                
                // Charge (Base: AmpHour)
                MILIAMPHOUR,
                AMPHOUR,
                KILOAMPHOUR,
                CULOMB, 

                // Torque (Base: Newton-meter)
                MILINM,
                NM,
                KILONM,
                MEGANM,
                GRAMSPERCENTIMETER,    
                KILOGRAMSPERCENTIMETER, 
                TONSPERCENTIMETER,      
                GRAMSPERMILIMETER,
                KILOGRAMSPERMILIMETER,
                OUNCEPERINCH,           

                // Angle speed (Base: radians per second)
                RADIANPERSECOND,
                REVOLUTIONSPERMINUTE,   
                DEGREESPERSECOND,

                // Pressure (Base: pascal)
                PASCAL,
                KILOPASCAL,
                HECTOPASCAL,
                BAR,
                PSI,
                TECHNICALATM, 

                // Angle (base: degree)
                DEGRE,
                RADIAN,
                GRAD,
                DMS, 

                // Different bases (base: DECIMALmal)
                DECIMAL,
                OCTAGONAL,
                HEXADECIMAL,
                BINARY,

                // Temperature (Base: Celsius)
                CELSIUS,
                FAHRENHEIT,
                KELVIN,

                // Error flag
                UNKNOWN
                };

            String convertToRPN(String equation);
            String evaluateRPN(String rpnEquation);
            void splitString(String inputString, char delimiter, String outputArray[], int maxElements) ;
            bool greaterPrecedence(String firstOperator, String secondOperator);
            String evaluate(String expresion);
            double nthRoot(double number, int n);
            bool findString(String mainString, String strToFind);
            String convertUnit(String strValue, UnitType from, UnitType to);
    };
#endif