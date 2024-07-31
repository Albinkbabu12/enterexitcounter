#include <Wire.h>
#include <LiquidCrystal_I2C_Hangul.h>

// LCD Address
int lcdAddress = 0x27;

// Create LCD object
LiquidCrystal_I2C_Hangul lcd(lcdAddress, 16, 2);

// IR Sensor Pin Definitions
const int enterSensorPin = 7;
const int exitSensorPin = 8;
// light in room

// Counter Variables
int enterCount = 0;
int exitCount = 0;

void setup() {
    Serial.begin(9600);  // Initialize Serial Monitor
    lcd.init();         // Initialize LCD
    lcd.backlight();    // Turn on the backlight
    lcd.setCursor(0, 0);
    lcd.print("Enter:0  Exit:0");

    // IR Sensor Pin Setup
    pinMode(enterSensorPin, INPUT);
    pinMode(exitSensorPin, INPUT);
    pinMode(11,OUTPUT);
    
}

void loop() {
   if(enterCount-exitCount>0){
       digitalWrite(11,HIGH);
   }
   else{
    digitalWrite(11,LOW);
   
   }   
    // Check Enter Sensor
    if (digitalRead(enterSensorPin) == LOW) {
        delay(100); // Debounce
        if (digitalRead(enterSensorPin) == HIGH) {
            enterCount++;
            updateLCD();
            updateSerial();
            delay(1000); // Delay to avoid multiple counts for a single entry
        }
    }

    // Check Exit Sensor
    
    if (digitalRead(exitSensorPin) == LOW ) {
        delay(100); // Debounce
        if (digitalRead(exitSensorPin) == HIGH ) {
            if (enterCount>0 && enterCount-exitCount>0){       
                exitCount++;
                updateLCD();
                updateSerial();
               
                delay(1000); // Delay to avoid multiple counts for a single exit
            }
        }
    }
}

void updateLCD() {
    lcd.setCursor(6, 0);
    lcd.print(enterCount);

    lcd.setCursor(14,0 );
    lcd.print(exitCount);
    lcd.setCursor(1,1);
    lcd.print("count:");
    lcd.setCursor(7,1);
    lcd.print(enterCount-exitCount);
}
void updateSerial()
{
    Serial.print("Enter Count: " );
    Serial.print(enterCount);
    Serial.print(" | Exit Count: ");
    Serial.println(exitCount);
    Serial.println( "NO.OF PERSON IN THE HALL:");
    Serial.println(enterCount-exitCount);

}

