#include "omniMath.h"


/*
 * name:    convertToRPN
 * desc.:   function that converts given equation into RPN 
 * input:   infix equation as string
 * output:  RPN equation as string
*/
String omniMath::convertToRPN(String equation){
    //=== Fixing equation ===
    //---- Removing spaces ----
    equation.replace(" ", ""); // Usuń spacje
    //
    //---- fixing double operators ----
    for(int i=0; i<2; i++) { 
       equation.replace("--", "+");
       equation.replace("++", "+");
       equation.replace("+-", "-");
       equation.replace("-+", "-");
    }
    //
    //---- fixing equation starting from operator
    if (equation.startsWith("-")) equation = "0" + equation;
    else if (equation.startsWith("+")) equation = "0" + equation;
    equation.replace("(-", "(0-");
    equation.replace("(+", "(0+");

    //=== Declaring variables ===
    String convertedEquation = "";
    // Zwiększyłem stos do 30, bo trik z zerem dodaje znaki
    String operatorStack[30]; 
    // Inicjalizacja pustymi stringami
    for(int j=0; j<30; j++) operatorStack[j] = ""; 
    
    String currentChar = "", previousChar = "";
    int operatorStackCount = 0, whilePcounter = 1, whileOcounter = 1;
    bool runElse = false, escapeWhile = false;

    //=== Itterating through the entire string ===
    for(int i=0; i < equation.length(); i++){
        currentChar = String(equation[i]);

        //---- If currentChar is a number or a . add it to covertedEquation ----
        if((currentChar >= "0" && currentChar <= "9") || currentChar == "."){
            convertedEquation += currentChar;
        }
        //
        //---- Else perform RPN operator shenanigans ----
        else if(currentChar == "+" || currentChar == "-" || currentChar == "*" || currentChar == "/" || currentChar == "^"){
            // Dodaj spację jeśli jej nie ma
            if(convertedEquation.length() > 0 && String(convertedEquation[convertedEquation.length()-1]) != " ") {
                convertedEquation += " ";
            }
            
            while(operatorStackCount > 0 && !escapeWhile){
                previousChar = operatorStack[operatorStackCount-whileOcounter];

                if(greaterPrecedence(previousChar, currentChar) && previousChar != "(" && operatorStackCount-whileOcounter >= 0){
                    convertedEquation += previousChar;
                    convertedEquation += " ";
                    operatorStack[operatorStackCount-whileOcounter] = "";
                    whileOcounter++;
                }
                else{
                    escapeWhile = true;
                    operatorStackCount = operatorStackCount-whileOcounter+1;
                    operatorStack[operatorStackCount] = currentChar;
                    operatorStackCount++;
                }
            }
            whileOcounter = 1;
            escapeWhile = false;

            if(operatorStackCount == 0 || runElse){
                operatorStack[operatorStackCount] = currentChar;
                operatorStackCount++;
                runElse = false;
            }
        }
        //---- Operator is ( shenanigans ---
        else if(currentChar == "("){
            operatorStack[operatorStackCount] = currentChar;
            operatorStackCount++;
        }
        //---- Operator is ) shenanigans ----
        else if(currentChar == ")"){
            if(convertedEquation.length() > 0 && String(convertedEquation[convertedEquation.length()-1]) != " ") convertedEquation += " ";
            
            while(operatorStackCount > 0 && operatorStack[operatorStackCount-whilePcounter] != "("){
                convertedEquation += operatorStack[operatorStackCount-whilePcounter];
                operatorStack[operatorStackCount-whilePcounter] = "";
                convertedEquation += " ";
                whilePcounter++;
            }
            
            //---- Tbh i dont remember
            if (operatorStackCount >= whilePcounter) {
                operatorStackCount = operatorStackCount-whilePcounter;
                operatorStack[operatorStackCount] = "";
            }
            whilePcounter = 1;
        }
    }

    //---- Pop every operator that is left in stack when at the end of equation ----
    while(operatorStackCount > 0){
        operatorStackCount--;
        if(convertedEquation.length() > 0 && String(convertedEquation[convertedEquation.length()-1]) != " ") convertedEquation += " ";
        convertedEquation += operatorStack[operatorStackCount];
    }

    return convertedEquation;
}


/*
 * name:    evaluateRPN
 * desc.:   function that evaluates the value of an RPN equation
 * input:   rpn equation
 * output:  double converted to string with 9 decimal places
*/
String omniMath::evaluateRPN(String rpnEquation){
    //=== Declaring variables ===
    int itteration = 0, numberStackCount = 0;
    double num1=0, num2=0, output=0;
    double equationEval = 0;
    double numberStack[100];
    String splitArray[100];
    String equation;

    //=== Spliting the string based on space ===
    splitString(rpnEquation, ' ', splitArray, 100);
    
    //=== Looping through created aray and evaluating expresion ===
    while(splitArray[itteration] != ""){
        //---- If current character is not an operator, add it to the stack of doubles ----
        if(splitArray[itteration] != "*" && splitArray[itteration] != "/" && splitArray[itteration] != "-" && splitArray[itteration] != "+" && splitArray[itteration] != "^"){
            numberStack[numberStackCount] = splitArray[itteration].toDouble();
            numberStackCount++;
        }
        //
        //---- If current character is an operator perform math ---
        else{
            //---- Get the second number ----
            numberStackCount--;
            num2 = numberStack[numberStackCount];
            numberStack[numberStackCount] = 0;
            //
            //---- Get the first number ----
            numberStackCount--;
            num1 = numberStack[numberStackCount];
            numberStack[numberStackCount] = 0;
            //
            //---- Do the math ----
            if(splitArray[itteration] == "*") output = num1*num2;
            else if(splitArray[itteration] == "/") output = num1/num2;  
            else if(splitArray[itteration] == "+") output = num1+num2;
            else if(splitArray[itteration] == "-") output = num1-num2;
            else if(splitArray[itteration] == "^") output = pow(num1, num2);
            numberStack[numberStackCount] = output;
            //
            //---- Reset variables ----
            num1=0;
            num2=0;
            numberStackCount++;
        }
        itteration++;
    }
    
    //=== Covert solution back to string with 9 decimal places ===
    equation = String(numberStack[0], 9);

    //=== Return the solution ===
    return equation;
}


/*
 * name:    splitString
 * desc.:   function that splits a string basaed on a given delimiter
 * input:   string to split, delimiter, output array to put the data to, maximum elements in an array
 * output:  0 if string is empty, else element count
*/
void omniMath::splitString(String inputString, char delimiter, String outputArray[], int maxElements) {
    //=== Declaring variables ===
    int elementCount = 0;
    int lastIndex = 0;

    //=== Else itterate through it and split it ===
    for (int i = 0; i < inputString.length(); i++) {
        //---- Check if current character is a delimiter, if it is, add data between last delimiter and the current one to the array ----
        if (inputString.charAt(i) == delimiter) {
            outputArray[elementCount] = inputString.substring(lastIndex, i);
            elementCount++;
            lastIndex = i + 1;
        }
    }
    //=== TBH idfk... ===
    if (elementCount < maxElements) {
        outputArray[elementCount] = inputString.substring(lastIndex);
        elementCount++;
    }
    
}


/*
 * name:    greaterPrecedence
 * desc.:   determines if first operator has greater or equal precedence to second one
 * input:   first and second operator, strings
 * output:  true or false
*/
bool omniMath::greaterPrecedence(String firstOperator, String secondOperator){
    //---- Check for + and - ----
    if(firstOperator == "+" || firstOperator == "-"){
        if(secondOperator == "+" || secondOperator == "-") return true;
        else return false;
    }
    //
    //---- check for * and / ----
    else if(firstOperator == "*" || firstOperator == "/"){
        if(secondOperator == "^") return false;
        else return true;
    }
    //
    //---- check for ^ ----
    else if(firstOperator == "^"){
        return true;
    }
    //
    //---- else return false ----
    else return false;
}


/*
 * name:    evaluate
 * desc.:   evaluates basic math equations (addition, subraction, dividion, multiplication, power) trig, arithmetic, logarithms, powers and roots, random number, constants
 * input:   string with an expresion
 * output:  evaluted value as a string
*/
String omniMath::evaluate(String expresion){   
    const double mathPi = 3.14159265359;
    const char PI_CONSTANT[] PROGMEM = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    const char E_CONSTANT[] PROGMEM = "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274";

    //=== Calculate Trig ===
    if(findString(expresion, "sin") || findString(expresion, "cos") || findString(expresion, "tg") || findString(expresion, "tan") || findString(expresion, "asin") || findString(expresion, "acos") || findString(expresion, "atg") || findString(expresion, "atan")){
        //---- Looks if the function has a space (so probably an argument) ----
        if(findString(expresion, " ")){
            //---- Creating variables and spliting the string ----
            String trigArray[3];
            expresion.replace("(", "");
            expresion.replace(")", "");
            float value, evaluated;
            splitString(expresion, ' ', trigArray, 3);
            //
            //---- sine in deges ----
            if(trigArray[0] == "sin"){
                value = trigArray[1].toFloat();
                evaluated = sin((mathPi/180)*value);
                return String(evaluated, 4);
            }
            //
            //---- cosine in deges ----
            else if(trigArray[0] == "cos"){
                value = trigArray[1].toFloat();
                evaluated = cos((mathPi/180)*value);
                return String(evaluated, 4);
            } 
            //
            //---- tangent in deges ----
            else if(trigArray[0] == "tg" || trigArray[0] == "tan"){
                value = trigArray[1].toFloat();
                evaluated = tan((mathPi/180)*value);
                return String(evaluated, 4);
            }
            //
            //---- asine in deges ----
            else if(trigArray[0] == "asin"){
                value = trigArray[1].toFloat();
                evaluated = asin(value)*(180/mathPi);
                return String(evaluated, 4);
            } 
            //
            //---- acosine in deges ----
            else if(trigArray[0] == "acos"){
                value = trigArray[1].toFloat();
                evaluated = acos(value)*(180/mathPi);
                return String(evaluated, 4);
            } 
            //
            //---- atangent in deges ----
            else if(trigArray[0] == "atg" || trigArray[0] == "atan"){
                value = trigArray[1].toFloat();
                evaluated = atan(value)*(180/mathPi);
                return String(evaluated, 4);
            }
            //
            //---- return error if syntax is wrong ----
            else return "Err: wrong operation or syntax!";
        }
        //---- return error if syntax is wrong ----
        else return "Err: too little arguments!";
    }

    //=== Calculate arithmetic ===
    else if(findString(expresion, "pcnt") || findString(expresion, "inv") || findString(expresion, "mod")){
        //---- Looks if the function has a space (so probably an argument) ----
        if(findString(expresion, " ")){
            //---- Creating variables and spliting the string ----
            String aritArray[5];
            double value1, value2, evaluated;
            float value1F, value2F, evaluatedF;
            splitString(expresion, ' ', aritArray, 5);
            //
            //---- calculating percent, operator first ----
            if(aritArray[0] == "pcnt"){
                value1 = aritArray[1].toDouble();
                value2 = aritArray[2].toDouble();
                evaluated = value2/value1*100;
                return String(evaluated);
            }
            //
            //---- calculating percent, operator second ----
            else if(aritArray[1] == "pcnt"){
                value1 = aritArray[0].toDouble();
                value2 = aritArray[2].toDouble();
                evaluated = value2/value1*100;
                return String(evaluated);
            }
            //
            //---- calculating inversion ----
            else if(aritArray[0] == "inv"){
                value1 = aritArray[1].toDouble();
                evaluated = 1/value1;
                return String(evaluated);
            }
            //
            //---- calculating modulo, operator first ----
            else if(aritArray[0] == "mod"){
                value1F = aritArray[1].toFloat();
                value2F = aritArray[2].toFloat();
                evaluatedF = fmod(value1F, value2F);
                return String(evaluatedF);
            }
            //
            //---- calculating modulo, operator second ----
            else if(aritArray[1] == "mod"){
                value1F= aritArray[0].toFloat();
                value2F = aritArray[2].toFloat();
                evaluatedF = fmod(value1F, value2F);
                return String(evaluatedF);
            }
            //
            //---- return error if syntax is wrong ----
            else return "Err: wrong operation or syntax!";
        }
        else return "Err: too little arguments!";
    }

    //=== Calculate powers and roots ===
    else if(findString(expresion, "sq") || findString(expresion, "cb") || findString(expresion, "pow") || findString(expresion, "pw") || findString(expresion, "sqrt") || findString(expresion, "cbrt") || findString(expresion, "rt") || findString(expresion, "nlog") || findString(expresion, "log") || findString(expresion, "tlog") || findString(expresion, "tenPw") || findString(expresion, "tenpw")){
        //---- Looks if the function has a space (so probably an argument) ----
        if(findString(expresion, " ")){
            //---- Creating variables and spliting the string ----
            expresion.replace("(", "");
            expresion.replace(")", "");
            String powArray[5];
            double value1, value2, evaluated;
            splitString(expresion, ' ', powArray, 5);
            //
            //---- square ----
            if(powArray[0] == "sq"){
                value1 = powArray[1].toDouble();
                evaluated = value1*value1;
                return String(evaluated, 9);
            }
            //
            //---- cube ----
            else if(powArray[0] == "cb"){
                value1 = powArray[1].toDouble();
                evaluated = value1*value1*value1;
                return String(evaluated, 9);
            }
            //
            //---- power, operator first ----
            else if(powArray[0] == "pw" || powArray[0] == "pow"){
                value1 = powArray[1].toDouble();
                value2 = powArray[2].toDouble();
                evaluated = pow(value1, value2);
                return String(evaluated, 9);
            }
            //
            //---- power, operator second ----
            else if(powArray[1] == "pw" || powArray[1] == "pow"){
                value1 = powArray[0].toDouble();
                value2 = powArray[2].toDouble();
                evaluated = pow(value1, value2);
                return String(evaluated, 9);
            }
            //
            //---- square root ----
            else if(powArray[0] == "sqrt"){
                value1 = powArray[1].toDouble();
                evaluated = sqrt(value1);
                return String(evaluated, 9);
            }
            //
            //---- cube root----
            else if(powArray[0] == "cbrt"){
                value1 = powArray[1].toDouble();
                evaluated = nthRoot(value1, 3);
                return String(evaluated, 9);
            }
            //
            //---- root, operator first ----
            else if(powArray[0] == "rt"){
                value1 = powArray[1].toDouble();
                value2 = powArray[2].toDouble();
                evaluated = nthRoot(value1, int(value2));
                return String(evaluated, 9);
            }
            //
            //---- root, operator second ----
            else if(powArray[1] == "rt"){
                value1 = powArray[0].toDouble();
                value2 = powArray[2].toDouble();
                evaluated = nthRoot(value1, int(value2));
                return String(evaluated, 9);
            }
            //
            //---- logarithm of custom base and value ----
            else if(powArray[0] == "log"){
                value1 = powArray[1].toDouble();
                value2 = powArray[2].toDouble();
                evaluated = log(value2) / log(value1);
                return String(evaluated, 9);
            }
            //
            //---- natural logarithm ----
            else if(powArray[0] == "nlog"){
                value1 = powArray[1].toDouble();
                evaluated = log(value1);
                return String(evaluated, 9);
            }
            //
            //---- logarithm of ten ----
            else if(powArray[0] == "tlog"){
                value1 = powArray[1].toDouble();
                evaluated = log10(value1);
                return String(evaluated, 9);
            }
            //
            //---- ten to the power----
            else if(powArray[0] == "tenPw" || powArray[0] == "tenpw"){
                value1 = powArray[1].toDouble();
                evaluated = pow(10, value1);
                return String(evaluated, 9);
            }
            else return "Err: wrong operation or syntax!";
        }
        else return "Err: too little arguments!";
    }

    //=== Other ===
    else if(findString(expresion, "fct") || findString(expresion, "fact") || findString(expresion, "rndNum") || findString(expresion, "rndnum") || findString(expresion, "rand") || findString(expresion, "pi") || findString(expresion, "euler") || findString(expresion, "e")){
        //---- Looks if the function has a space (so probably an argument) ----
        if(findString(expresion, " ") || findString(expresion, "pi") || findString(expresion, "euler") || findString(expresion, "e")){
            //---- Creating variables and spliting the string ----
            String otherArray[5];
            expresion.replace("(", "");
            expresion.replace(")", "");
            splitString(expresion, ' ', otherArray, 5);
            //
            //---- factorials, up to 12 ----
            if(otherArray[0] == "fct" || otherArray[0] == "fact"){
                long factorial = 1;
                int factorialVal = otherArray[1].toInt();
                if(factorialVal <= 12){
                    for(int i = 1; i <= factorialVal; i++) factorial = factorial * i;
                    return String(factorial);
                }
                else return "Err: factorial above 12!";
            }
            //
            //---- generating random number ----
            else if(otherArray[0] == "rndNum" || otherArray[0] == "rndnum" || otherArray[0] == "rand"){
                double maxVal, minVal, step, numSteps, randomStep, evaluated;
                minVal = otherArray[1].toDouble();
                maxVal = otherArray[2].toDouble();
                step = otherArray[3].toDouble();

                numSteps = (maxVal-minVal)/step;
                randomStep = random(0, numSteps + 1);
                evaluated = minVal + (randomStep * step);
                
                return String(evaluated);
            }
            //
            //---- pi with a given dec places ----
            else if(otherArray[0] == "pi" && otherArray[1] != ""){
                int maxdecs = strlen_P(PI_CONSTANT) - 2;
                int dec = otherArray[1].toInt();
                if (dec > maxdecs) dec= maxdecs;
                int totalLength = dec + 2;
                char buffer[totalLength + 1];
                strncpy_P(buffer, PI_CONSTANT, totalLength);
                buffer[totalLength] = '\0';

                return String(buffer);
            }
            //
            //---- pi ----
            else if(findString(expresion, "pi")){
                return "3.14159265359";
            }
            //
            //---- euler with a given dec places ----
            else if(otherArray[0] == "euler" && otherArray[1] != "" || otherArray[0] == "e" && otherArray[1] != ""){
                int maxdecs = strlen_P(E_CONSTANT) - 2;
                int dec = otherArray[1].toInt();
                if (dec > maxdecs) dec= maxdecs;
                int totalLength = dec + 2;
                char buffer[totalLength + 1];
                strncpy_P(buffer, E_CONSTANT, totalLength);
                buffer[totalLength] = '\0';

                return String(buffer);
            }
            //
            //---- euler  ----
            else if(findString(expresion, "euler") || findString(expresion, "e")){
                return "2.71828182845";
            }
            else return "Err: wrong operation or syntax!";
        }
        else return "Err: too little arguments!";
    }

    //=== Evaluating expresion ===
    else if(findString(expresion, "+") || findString(expresion, "-") || findString(expresion, "*") || findString(expresion, "/") || findString(expresion, "^")){
        if(expresion.length()>2){
            String rpnEquation = convertToRPN(expresion);     
            return evaluateRPN(rpnEquation);;
        }
        else return "Err: too little arguments!";
    }

    //=== Return expresion if nothing happened ===
    expresion.replace("(", "");
    expresion.replace(")", "");
    return expresion;
}


/*
 * name:    nthRoot
 * desc.:   calculates root of a number
*/
double omniMath::nthRoot(double number, int n) {
  // 1. Handle the case of 0
  if (number == 0) return 0;

  // 2. If number is negative
  if (number < 0) {
    // If root is even (like square root), result is imaginary (NaN)
    if (n % 2 == 0) {
      return NAN; 
    }
    // If root is odd (like cube root), calculate positive root and flip sign
    return -pow(-number, 1.0 / n);
  }

  // 3. Standard positive case
  return pow(number, 1.0 / n);
}


/*
 * name:    findString
 * desc.:   finds strToFind in mainString
 * input:   mainString, strToFind
 * output:  1 if found, 0 if not found
*/
bool omniMath::findString(String mainString, String strToFind){
    return mainString.indexOf(strToFind) != -1;
}


/*
 * name:    isUNIT
 * desc.:   helper functions for unit convert
 * input:   value
 * output:  1 if correct, 0 if not
*/
bool isLength(omniMath::UnitType t) { return (t >= omniMath::m && t <= omniMath::mi); }
bool isMass(omniMath::UnitType t) { return (t >= omniMath::kg && t <= omniMath::oz); }
bool isEnergy(omniMath::UnitType t) { return (t >= omniMath::mWh && t <= omniMath::BTU); } 
bool isCharge(omniMath::UnitType t) { return (t >= omniMath::mAh && t <= omniMath::C); }
bool isTorque(omniMath::UnitType t) { return (t >= omniMath::mNM && t <= omniMath::ozPERin); }
bool isAngleSpeed(omniMath::UnitType t) { return (t >= omniMath::radPERs && t <= omniMath::degPERs); }
bool isPressure(omniMath::UnitType t) { return (t >= omniMath::Pa && t <= omniMath::tAtm); }
bool isAngle(omniMath::UnitType t) { return (t >= omniMath::deg && t <= omniMath::DMS); }
bool isBase(omniMath::UnitType t) { return (t >= omniMath::dec && t <= omniMath::bin); }
bool isTemp(omniMath::UnitType t) { return (t >= omniMath::degC && t <= omniMath::K); }
bool isSpeed(omniMath::UnitType t) { return (t >= omniMath::kph && t <= omniMath::mmPERs); }

/*
 * name:    isUNIT
 * desc.:   helper functions for unit convert
 * input:   value
 * output:  1 if correct, 0 if not
*/
String omniMath::convertUnit(String strValue, UnitType from, UnitType to) {
    //=== Declaring variables ===
    double value = strValue.toDouble();
    
    //=== If value converted and value to convert is the same return it ===
    if (from == to) return strValue;

    //=== Convert number base ===
    if (isBase(from) && isBase(to)) {
        long valueLong = 0;
        if (from == dec) valueLong = strValue.toInt();
        else if (from == hex) valueLong = strtol(strValue.c_str(), NULL, 16);
        else if (from == oct) valueLong = strtol(strValue.c_str(), NULL, 8);
        else if (from == bin) valueLong = strtol(strValue.c_str(), NULL, 2);

        if (to == dec) return String(valueLong, DEC);
        else if (to == hex) return String(valueLong, HEX);
        else if (to == oct) return String(valueLong, OCT);
        else if (to == bin) return String(valueLong, BIN);
    }

    //=== Converting length ===
    if (isLength(from) && isLength(to)) {
        double valms = 0;
        if (from == m) valms = value;
        else if (from == km) valms = value * 1000.0;
        else if (from == cm) valms = value * 0.01;
        else if (from == mm ) valms = value * 0.001;
        else if (from == in) valms = value * 0.0254;
        else if (from == ft) valms = value * 0.3048;
        else if (from == yd) valms = value * 0.9144;
        else if (from == mi) valms = value * 1609.34;

        if (to == m) return String(valms, 6);
        else if (to == km) return String(valms / 1000.0, 6);
        else if (to == cm) return String(valms / 0.01, 6);
        else if (to == mm ) return String(valms / 0.001, 6);
        else if (to == in) return String(valms / 0.0254, 6);
        else if (to == ft) return String(valms / 0.3048, 6);
        else if (to == yd) return String(valms / 0.9144, 6);
        else if (to == mi) return String(valms / 1609.34, 6);
    }

    //=== Converting mass ===
    else if (isMass(from) && isMass(to)) {
        double valKg = 0;
        if (from == kg) valKg = value;
        else if (from == g) valKg = value * 0.001;
        else if (from == mg) valKg = value * 0.000001;
        else if (from == t) valKg = value * 1000;
        else if (from == lb) valKg = value * 0.453592;
        else if (from == oz) valKg = value * 0.0283495;

        if (to == kg) return String(valKg, 6);
        else if (to == g) return String(valKg / 0.001, 6);
        else if (to == mg) return String(valKg / 0.000001, 6);
        else if (to == t) return String(valKg / 1000, 6);
        else if (to == lb) return String(valKg / 0.453592, 6);
        else if (to == oz) return String(valKg / 0.0283495, 6);
    }

    //=== Converting temperature ===
    else if (isTemp(from) && isTemp(to)) {
        double valC = 0;
        if (from == degC) valC = value;
        else if (from == degF) valC = (value - 32.0) / 1.8;
        else if (from == K) valC = value - 273.15;

        if (to == degC) return String(valC, 2);
        else if (to == degF) return String((valC * 1.8) + 32.0, 2);
        else if (to == K) return String(valC + 273.15, 2);
    }

    //=== Converting pressure ===
    else if (isPressure(from) && isPressure(to)) {
        double valPa = 0;
        if (from == Pa) valPa = value;
        else if (from == kPa) valPa = value * 1000.0;
        else if (from == hPa) valPa = value * 100.0;
        else if (from == bar) valPa = value * 100000.0;
        else if (from == psi) valPa = value * 6894.76;
        else if (from == tAtm) valPa = value * 98066.5;

        if (to == Pa) return String(valPa, 2);
        else if (to == kPa) return String(valPa / 1000.0, 4);
        else if (to == hPa) return String(valPa / 100.0, 2);
        else if (to == bar) return String(valPa / 100000.0, 5);
        else if (to == psi) return String(valPa / 6894.76, 4);
        else if (to == tAtm) return String(valPa / 98066.5, 4);
    }

    //=== Converting angle ===
    else if (isAngle(from) && isAngle(to)) {
        double valDeg = 0;
        if (from == deg) valDeg = value;
        else if (from == rad) valDeg = value * (180.0 / PI);
        else if (from == grad) valDeg = value * 0.9;
        else if (from == DMS) valDeg = value; 
        
        if (to == deg) return String(valDeg, 4);
        else if (to == rad) return String(valDeg * (PI / 180.0), 4);
        else if (to == grad) return String(valDeg / 0.9, 4);
        else if (to == DMS) {
             int d = (int)valDeg;
             double mFrac = (valDeg - d) * 60;
             int m = (int)mFrac;
             double s = (mFrac - m) * 60;
             return String(d) + ":" + String(m) + ":" + String(s, 2);
        }
    }

    //=== Converting torque
    else if (isTorque(from) && isTorque(to)) {
        double valNm = 0;
        if (from == NM) valNm = value;
        else if (from == mNM) valNm = value * 0.001;
        else if (from == kNM) valNm = value * 1000.0;
        else if (from == MNM) valNm = value * 1000000.0;
        else if (from == gPERcm) valNm = value * 0.0000980665;
        else if (from == kgPERcm) valNm = value * 0.0980665;
        else if (from == tPERcm) valNm = value * 98.0665;
        else if (from == gPERmm) valNm = value * 0.00000980665;
        else if (from == kgPERmm) valNm = value * 0.00980665;
        else if (from == ozPERin) valNm = value * 0.00706155;

        if (to == NM) return String(valNm, 6);
        else if (to == mNM) return String(valNm / 0.001, 6);
        else if (to == kNM) return String(valNm / 1000.0, 6);
        else if (to == MNM) return String(valNm / 1000000.0, 8);
        else if (to == gPERcm) return String(valNm / 0.0000980665, 4);
        else if (to == kgPERcm) return String(valNm / 0.0980665, 4);
        else if (to == tPERcm) return String(valNm / 98.0665, 4);
        else if (to == gPERmm) return String(valNm / 0.00000980665, 4);
        else if (to == kgPERmm) return String(valNm / 0.00980665, 4);
        else if (to == ozPERin) return String(valNm / 0.00706155, 4);
    }

    //=== Converting angle speed ===
    else if (isAngleSpeed(from) && isAngleSpeed(to)) {
        double valRadS = 0;
        if (from == radPERs) valRadS = value;
        else if (from == RPM) valRadS = value * 0.10472;
        else if (from == degPERs) valRadS = value * (PI / 180.0);

        if (to == radPERs) return String(valRadS, 4);
        else if (to == RPM) return String(valRadS / 0.10472, 4);
        else if (to == degPERs) return String(valRadS * (180.0 / PI), 4);
    }
    
    //=== Converting energy ===
    else if (isEnergy(from) && isEnergy(to)) {
        double valWh = 0;
        
        // --- Step A: Convert FROM unit to Base (WATTtHour) ---
        if (from == Wh) valWh = value;
        else if (from == mWh) valWh = value / 1000.0;
        else if (from == kWh) valWh = value * 1000.0;
        else if (from == GWh) valWh = value * 1e9;
        // 1 Wh = 3600 Js -> 1 J = 1/3600 Wh
        else if (from == J) valWh = value / 3600.0;
        else if (from == kJ) valWh = (value * 1000.0) / 3600.0;
        else if (from == MJ) valWh = (value * 1000000.0) / 3600.0;
        // 1 cal = 4.184 Js
        else if (from == cal) valWh = (value * 4.184) / 3600.0;
        else if (from == kcal) valWh = (value * 4184.0) / 3600.0;
        // 1 BTU = 0.293071 Wh
        else if (from == BTU) valWh = value * 0.293071;
        
        // --- Step B: Convert Base (WATTtHour) to TO unit ---
        if (to == Wh) return String(valWh, 4);
        else if (to == mWh) return String(valWh * 1000.0, 4);
        else if (to == kWh) return String(valWh / 1000.0, 6);
        else if (to == GWh) return String(valWh / 1e9, 9);
        else if (to == J) return String(valWh * 3600.0, 2);
        else if (to == kJ) return String((valWh * 3600.0) / 1000.0, 4);
        else if (to == MJ) return String((valWh * 3600.0) / 1000000.0, 6);
        else if (to == cal) return String((valWh * 3600.0) / 4.184, 2);
        else if (to == kcal) return String((valWh * 3600.0) / 4184.0, 4);
        else if (to == BTU) return String(valWh / 0.293071, 4);
    }

    //=== Converting charge ===
    else if (isCharge(from) && isCharge(to)) {
        double valAh = 0;
        if (from == Ah) valAh = value;
        else if (from == mAh) valAh = value / 1000.0;
        else if (from == kAh) valAh = value * 1000.0;
        else if (from == mC) valAh = value / 3600000.0;
        else if (from == kC) valAh = value / 3.6;
        else if (from == C) valAh = value / 3600.0;
        
        if (to == Ah) return String(valAh, 4);
        else if (to == mAh) return String(valAh * 1000.0, 4);
        else if (to == mC) return String(valAh * 3600000.0, 4);
        else if (to == kC) return String(valAh * 3.6, 4);
        else if (to == kAh) return String(valAh / 1000.0, 6);
        else if (to == C) return String(valAh * 3600.0, 2);
    }

    //=== Converting speed ===
    else if (isSpeed(from) && isSpeed(to)) {
        double valMs = 0;
        if(from == kph) valMs = value/3.6;
        else if(from == mph) valMs = value*0/44704;
        else if(from == kn) valMs = value*0.534444;
        else if(from == ftPERs) valMs = value*0.3048;
        else if(from == Ma) valMs = value*340.3;
        else if(from == ms) valMs = value;
        else if(from == mPERmin) valMs = value/60;
        else if(from == kmPERs) valMs = value*1000;
        else if(from == mmPERs) valMs = value*0.001;

        if(to == kph) return String(valMs*3.6, 4);
        else if(to == mph) return String(valMs*2.23694, 4);
        else if(to == kn) return String(valMs*1.94384, 4);
        else if(to == ftPERs) return String(valMs*3.28084, 4);
        else if(to == Ma) return String(valMs*0.002938, 4);
        else if(to == ms) return String(valMs, 4);
        else if(to == mPERmin) return String(valMs*60, 4);
        else if(to == kmPERs) return String(valMs*0.001, 4);
        else if(to == mmPERs) return String(valMs*1000, 4);
    }

    //=== Return error bc units wrong ===
    return "Err: unit type mismatch";
}