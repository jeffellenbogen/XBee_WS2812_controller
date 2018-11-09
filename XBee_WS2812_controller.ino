/*This version uses ElapsedMillis to track time since last button
 * was pressed and sends a confirmation of the current mode
 * so that the controller and receiver are always in sync
 * 
 */


#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <elapsedMillis.h>

SoftwareSerial XBee(2, 3); // Arduino RX, TX (XBee Dout, Din)
const int button1Pin = 8;
int potPosition;  

LiquidCrystal lcd(12, 11, 5, 4, 6, 7);
elapsedMillis timeElapsed;
int mode = 1;
int ledSpeed = 10;

void setup()
{
  // Initialize XBee Software Serial port. Make sure the baud
  // rate matches your XBee setting (9600 is default).
  lcd.begin(16, 2); //Initialize the 16x2 LCD
  lcd.clear();  //Clear any old data displayed on the 
  lcd.setCursor(0,0);
  lcd.print("XBee Series 1"); 
  lcd.setCursor(0,1);
  lcd.print("2812 Controller");
  delay(1500);
  XBee.begin(9600); 

  pinMode(button1Pin, INPUT_PULLUP);

}

void loop()
{
     
     int button1State;  
     button1State = digitalRead(button1Pin);
     if (button1State == LOW) { // Button Pressed!
        timeElapsed = 0;
        mode++;
        if (mode > 5)
          mode = 0;
        delay (200); 
        sendMode();
        printLCD();

     }
     
    if (timeElapsed > 2000) {
        timeElapsed = 0;
        sendMode();
        printLCD();
        checkPotentiometer();
        sendLedSpeed();

     }
}

void checkPotentiometer(){
    potPosition = analogRead(A0); 
    ledSpeed = map(potPosition, -100, 1023, 1, 10);
}

void sendLedSpeed(){
  if       (ledSpeed == 1)
        XBee.print('A');
  else if (ledSpeed == 2)
        XBee.print('B');  
  else if (ledSpeed == 3)
        XBee.print('C');  
  else if (ledSpeed == 4)
        XBee.print('D');  
  else if (ledSpeed == 5)
        XBee.print('E');  
  else if (ledSpeed == 6)
        XBee.print('F');                      
  else if (ledSpeed == 7)
        XBee.print('G');  
  else if (ledSpeed == 8)
        XBee.print('H');  
  else if (ledSpeed == 9)
        XBee.print('I');  
  else if (ledSpeed == 10)
        XBee.print('J');  

}
void sendMode(){
      if (mode == 1) 
           XBee.print(1); 
      else if (mode == 2) 
           XBee.print(2); 
      else if (mode == 3) 
           XBee.print(3); 
      else if (mode == 4) 
           XBee.print(4); 
      else if (mode == 5) 
           XBee.print(5);    
      else if (mode == 0) 
           XBee.print(0);              
}

void printLCD(){
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Mode = ");
      lcd.setCursor(8,0);
      lcd.print(mode);
      lcd.setCursor(0,1);
      lcd.print("Speed = "); 
      lcd.setCursor(9,1);
      lcd.print(ledSpeed* 10);
}

