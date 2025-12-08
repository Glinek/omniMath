#ifndef OMNIMATH_H
#define OMNIMATH_H
    #include <Arduino.h>

    class omniMath{
        public:
            enum UnitType {
                // Length (Base: m)
                m,
                km,
                cm,
                mm ,
                in,
                ft,
                yd,
                mi,

                // Mass (Base: kg)
                kg,
                g,
                mg,
                lb,
                oz,

                // Energy (Base: WATTtHour)
                mWh,
                Wh,
                kWh,
                GWh,
                J,        // New: 1 Wh = 3600 J
                kJ,    // New
                MJ,    // New
                cal,      // New: 1 cal = 4.184 J
                kcal,  // New
                BTU,          // New: British Thermal Unit
                
                // Charge (Base: Ah)
                mAh,
                Ah,
                kAh,
                C, 

                // Torque (Base: Newton-m)
                mNM,
                NM,
                kNM,
                MNM,
                gPERcm,    
                kgPERcm, 
                tPERcm,      
                gPERmm,
                kgPERmm,
                ozPERin,           

                // Angle speed (Base: rads per second)
                radPERs,
                RPM,   
                degPERs,

                // Pressure (Base: Pa)
                Pa,
                kPa,
                hPa,
                bar,
                psi,
                tAtm, 

                // Angle (base: dege)
                deg,
                rad,
                grad,
                DMS, 

                // Different bases (base: decmal)
                dec,
                oct,
                hex,
                bin,

                // Temperature (Base: degC)
                degC,
                degF,
                K,

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