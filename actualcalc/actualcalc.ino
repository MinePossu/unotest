#include "tinyexpr.h" //this beatifull library https://github.com/codeplea/tinyexpr  //line 164 changed fabs to abs for compatibility
#include <stdio.h>
//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
// try me ( 7 + 7 - 2 + 27*8 + sin(7) )+( 7 + 7 - 2 + 27*8 + sin(7) )+( 7 + 7 - 2 + 27*8 + sin(7) )

double ans = 0;

//LiquidCrystal_I2C lcd(0x27,20,4); 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //lcd.init(); 
  //lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {  // Check if there is data available to read
    String input = Serial.readString();  // Read the data as a string
    long int t1 = millis(); //calculate the diff
    input.trim(); //remove something
    String result = calcme(input);
    long int t2 = millis();
    Serial.print("Time taken: "); Serial.print(t2-t1); Serial.println(" milliseconds");
    Serial.println(input);
    Serial.println(result);  // Print the result
    //lcd.clear(); 
    //lcd.setCursor(0,0);
    //lcd.print(input);
    //lcd.setCursor(0,3);
    //lcd.print(result);
  };
}

/**
String calcme(String input){
  String result = String(te_interp(input.c_str(), 0),6);
  return result;
};
**/

String calcme(String input){
  double x, y;
  /* Store variable names and pointers. */
  te_variable vars[] = {{"x", &x}, {"y", &y}, {"ans", &ans}};
  te_expr *expr = te_compile(input.c_str(), vars, 3, 0);
  x = 0; y = 0;
  String result = String(te_eval(expr), 6);
  ans = result.toDouble();
  //String result = String(te_interp(input.c_str(), 0),6);
  return result;
};
