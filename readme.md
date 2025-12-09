<img width="1700" height="460" alt="github-header-banner(2)" src="https://github.com/user-attachments/assets/2bf6727c-9d23-4f23-9acd-b21b25cff212" />
<p align="center"> <b>Notice!</b> Parts of this library have been made with assistance of Gemini AI </p>

# omniMath Library
A comprehensive Arduino library for evaluating mathematical expressions, handling Reverse Polish Notation (RPN), and performing unit conversions.
## Features
* **Expression Evaluation**: Parse and solve string equations (e.g., `"2+2*2"`) respecting order of operations.
* **Advanced Math Functions**: Support for trigonometry, logarithms, roots, powers, factorials, and percentages.
* **RPN Support**: Convert standard infix notation to Reverse Polish Notation (RPN) and evaluate RPN expressions.
* **Unit Conversion**: Built-in conversion for length, mass, temperature, pressure, energy, charge, angle, torque, and number bases.
* **Constants**: Easy access to mathematical constants like PI and Euler's number.


## Instalation
There are two ways to install this library:
1. Download this repository as .zip and include it using Arduino IDE (Sketch>>Include Library>>Add .ZIP Library...)
![image](https://github.com/user-attachments/assets/76835efe-9595-47fe-bc95-d909f662d4a9)
2. Add this library from Arduino IDE's library manager by typing *omniMath* and selecting *omniMath by Szymon GLinka*


# Documentation
### Initialization
To use the library, include the header file and create an instance of the `omniMath` class.
```cpp
#include <omniMath.h>
omniMath omniMath;
```
### RPN
The library allows converting infix notation (standard) to RPN and evaluating it.   
**Note:** When using `convertToRPN`, operators and numbers **must NOT** be separated by spaces in the input string.
```cpp
// 1. Convert to RPN
String rpn = omniMath.convertToRPN("321+4*(43-12*4)*3.5");
// 2. Evaluate RPN
String result = omniMath.evaluateRPN(rpn);
```
### Evaluate
The `evaluate()` function parses a mathematical string and returns the result. It supports standard arithmetic operators: +, -, *, /, ^, and ( ).
**Note:** When using `evaluate`, you can either input math equation OR math function. **You can NOT mix it**
```cpp
// Basic arithmetic
String result = omniMath.evaluate("23+54*4+(34-5+3)*2.58");
// Trigonometry (input in Degrees)
String sineVal = omniMath.evaluate("sin 30");
// Constants
String piVal = omniMath.evaluate("pi");
```
| Category | Function | Syntax | Description |
|----------|----------|--------|-------------|
| Trig | Sine | `sin DEG` | Sine of an angle in degrees |
| Trig | Cosine | `cos DEG` | Cosine of an angle in degrees |
| Trig | Tangent | `tg DEG` / `tan DEG` | Tangent of an angle in degrees |
| Trig | Arc Sine | `asin VAL` | Arc sine, returns degrees |
| Trig | Arc Cosine | `acos VAL` | Arc cosine, returns degrees |
| Trig | Arc Tangent | `atg VAL` / atan VAL | Arc tangent, returns degrees |
| Powers | Square | `sq VA`L | Square of a value |
| Powers | Cube | `cb VAL` | Cube of a value |
| Powers | Power | `pw VAL POW` / `VAL pw POW` / `pow VAL POW` / `VAL pow POW` | Value to the power of exponent |
| Powers | Ten Power | `tenPw POW` / `tenpw PWO` | 10 to the power of exponent |
| Roots | Square Root | `sqrt VAL` | Square root of a value |
| Roots | Cube Root | `cbrt VAL` | Cube root of a value |
| Roots | N-th Root | `rt VAL ROOT` / `VAL rt ROOT` | Specific root of a value |
| Logs | Natural | `nlog VAL` | Natural logarithm (ln) |
| Logs | Base 10 | `tlog VAL` | Logarithm base 10 |
| Logs | Custom Base | `log BASE VAL` | Logarithm with custom base |
| Other | Percent | `pcnt BASE VAL` | What % of BASE is VAL |
| Other | Inverse | `inv VAL` | Inverts value (1/x) |
| Other | Modulo | `mod VAL DIV` / `VAL mod DIV` | Remainder of division |
| Other | Factorial | `fact VAL` / `fct VAL` | Factorial (x!), max input 12 |
| Other | Random | `rand MIN MAX STEP` / `rndNum MIN MAX STEP` / `rndnum MIN MAX STEP` | Random number in range with step |
| Constants | Pi | `pi` / `pi DECIMAL_PLACES` | Pi value (default 11 decimal places) |
| Constants | Euler | `e` / `e DECIMAL_PLACES` | e value (default 11 decimal places) |
### Unit Conversion
Use `convertUnit()` to convert values between different unit systems. The function takes the value (string), source unit, and target unit.
```cpp
String val = omniMath.convertUnit("Value", omniMath.FromUnit, omniMath.ToUnit);
```
Examples
```cpp
// Temperature: Celsius to Fahrenheit
omniMath.convertUnit("100", omniMath.degC, omniMath.degF);
// Mass: Kilograms to Pounds
omniMath.convertUnit("1", omniMath.kg, omniMath.lb);
// Charge: mAh to Coulombs
omniMath.convertUnit("2500", omniMath.mAh, omniMath.C);
```
Use the syntax `omniMath.UNIT_NAME` (e.g., `omniMath.km`).
| Category | Library Syntax (units) |
|----------|------------------------|
| Length | `m`, `km`, `cm`, `mm`, `in` (Inch), `ft` (Foot), `yd` (Yard), `mi` (Mile) |
| Mass | `kg`, `g`, `mg`, `lb` (Pound), `oz` (Ounce) |
| Temperature | `degC` (Celsius), `degF` (Fahrenheit), `K` (Kelvin) |
| Pressure | `Pa`, `kPa`, `hPa`, `bar`, `psi`, `tAtm` (Technical Atm) |
| Energy | `Wh`, `mWh`, `kWh`, `GWh`, `J`, `kJ`, `MJ`, `cal`, `kcal`, `BTU` |
| Charge | `Ah`, `mAh`, `kAh`, `C` (Coulomb) |
| Angle | `deg` (Degree), `rad` (Radian), `grad`, `DMS` |
| Angle Speed | `radPERs`, `RPM`, `degPERs` |
| Torque | `NM`, `mNM`, `kNM`, `MNM`, `kgPERcm`, `ozPERin`, `gPERcm`, `tPERcm` |
| Number Base | `dec` (Decimal), `hex` (Hexadecimal), `oct` (Octal), `bin` (Binary) |


# License
This library is licensed under Creative Commons CC BY 4.0 available [here](license)
**You are free to:**    
- Share — copy and redistribute the material in any medium or format for any purpose, even commercially.    
- Adapt — remix, transform, and build upon the material for any purpose, even commercially. The licensor cannot revoke these freedoms as long as you follow the license terms.

**Under the following terms:**    
- Attribution — You must give appropriate credit , provide a link to the license, and indicate if changes were made . You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.    
- No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
  
**Notices:**    
You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation .    
No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material.    

# Author
This library has been created by **Szymon *Glinek* Glinka** to help with development of custom firmware for PicoCalc

