#define PROG_NAME "HW2_BiColorOLED128x64"
#define VERSION " V.0.1 "
//#define MODEL_NAME "Model: BUTTON"
#define MODEL_NAME "HW2_BiColorOLED128x64"  //Hardware is Homework2 with OLED.
#define DEVICE_UNDER_TEST "SN: 00001"
#define LICENSE "GNU Affero General Public License, version 3 "
//#define ORIGIN "LB"

#define BAUDRATE 115200  //Serial port UART0

/* Scrolling Text demo from: https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/
Modified by Forrest Lee Erickson
Date: 20250518

Hardware is Homework2 which is ESP32 S2
Bicolor I2C (CLK=??, SDA=?? ), OLED 
*/



/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void splashserial() {
  Serial.println(F("==================================="));
  Serial.println(PROG_NAME);
  Serial.println(VERSION);
  Serial.println(MODEL_NAME);
  Serial.println(DEVICE_UNDER_TEST);
  Serial.print(F("Compiled at: "));
  Serial.println(F(__DATE__ " " __TIME__));
  Serial.println(LICENSE);
  Serial.println(F("==================================="));
  Serial.println();
}

#define LED_BUILTIN 2  //The ESP kit
bool SSD1306_allocated = false;
//Functions
//Wink the LED
void wink(void) {
  // TODO
//  const int LED_BUILTIN = 2;  // ESP32 Kit//const int LED_BUILTIN = 13;    //Not really needed for Arduino UNO it is defined in library
  pinMode(LED_BUILTIN, OUTPUT);
  // const int HIGH_TIME_LED = 900;
  // const int LOW_TIME_LED = 100;
  const int HIGH_TIME_LED = 1400;
  const int LOW_TIME_LED = 500;
  static unsigned long lastLEDtime = 0;
  static unsigned long nextLEDchange = 500;  //time in ms.
  if (((millis() - lastLEDtime) > nextLEDchange) || (millis() < lastLEDtime)) {
    if (digitalRead(LED_BUILTIN) == LOW) {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      nextLEDchange = HIGH_TIME_LED;
    } else {
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
      nextLEDchange = LOW_TIME_LED;
    }
    lastLEDtime = millis();
  }
}  //end LED wink

//end of functions
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB
  }
  splashserial();

  //Init display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    SSD1306_allocated = false;
    //    for (;;)  //DO NOT TRAP program exicution.
    //      ;

  } else {
    SSD1306_allocated = true;
  }

  //Display splash screen
  if (true == SSD1306_allocated) {
    delay(2000);
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    // Display static text
    display.println(PROG_NAME);
//    display.println("Scrolling Hello");
    display.display();
    delay(100);
  }


  digitalWrite(LED_BUILTIN, LOW);
}  // end splash()

void loop() {
  wink();
  // // Scroll in various directions, pausing in-between:
  // display.startscrollright(0x00, 0x0F);
  // delay(2000);
  // display.stopscroll();
  // delay(1000);
  // display.startscrollleft(0x00, 0x0F);
  // delay(2000);
  // display.stopscroll();
  // delay(1000);
  // display.startscrolldiagright(0x00, 0x07);
  // delay(2000);
  // display.startscrolldiagleft(0x00, 0x07);
  // delay(2000);
  // display.stopscroll();
  // delay(1000);
  
}