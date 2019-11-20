#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int incomingByte = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("Reseted");
  delay(1000);
  lcd.clear();
  lcd.print("Again");
  
}

// the loop function runs over and over again forever

void loop() {
  
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    //delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
      delay(1000);
      //lcd.print("joli");
      //Serial.write("Holis");
    }
  }
}
