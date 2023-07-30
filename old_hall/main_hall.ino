
#include <LiquidCrystal.h>

const int buttonPin  = 13;    //button pinout/variables
const int hall_L_pin = 4;
const int hall_R_pin = 5;
const int LED_L_pin  = 11;
const int LED_R_pin  = 10;

int buttonPushCounter = 0;    //initalize counter to 1 so program only starts after inital button press from splash screen
int buttonState       = 0;        
int lastButtonState   = 0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
void GMR();
void Hall();


void setup() {
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Edison");
  lcd.setCursor(2,1);
  lcd.print("Lectures");
  delay(100);
}


void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState != lastButtonState) {   // compare the buttonState to its previous state
    
      if (buttonState == HIGH){             //increment counter each time button is pressed on
        buttonPushCounter+=1;
      }
  
      switch(buttonPushCounter){            //toggle between case options
      case 1:                               
      lcd.clear();
      lcd.print("GMR");               //print menu choice, then delay
      delay(750);
      lcd.clear();
      do{                                   
        lcd.clear();
        GMM();
        delay(100);
        buttonState = digitalRead(buttonPin);
      }while(buttonState == lastButtonState); 
      break;
 
      case 2:                            
      lcd.clear();
      lcd.print("Hall");
      delay(750);
      lcd.clear();
      do{
        lcd.clear();
        Hall();
        buttonState = digitalRead(buttonPin);
        delay(100);
      }while(buttonState == lastButtonState);
      break;
  
    }
  }

  lastButtonState = buttonState-1;          // save the current state as the last state, for next time through the loop

  if (buttonPushCounter % 2 == 0)
    buttonPushCounter = 0;                //reset button to 0, to begin menu options again

}

void GMM() { 
  lcd.print("GMM Mode Ready");
}


void Hall(){
  float hall_L_data = analogRead(hall_L_pin);
  float hall_R_data = analogRead(hall_R_pin);
  float volt_L = hall_L_data * (5.0 / 1023);
  float volt_R = hall_R_data * (5.0 / 1023);
  
  lcd.setCursor(0,0);
  if(volt_L < 1 || volt_R < 1){
    lcd.print("MAG FIELD");
    lcd.setCursor(0,1);
    lcd.print("DETECTED");
    if (volt_L < 1){
      digitalWrite(LED_L_pin, HIGH);
    }
    else{
      digitalWrite(LED_R_pin, HIGH);
    }
  }
  else{
    lcd.print("No Mag Field");
    lcd.setCursor(0,1);
    lcd.print("Detected");
    digitalWrite(LED_R_pin, LOW);
    digitalWrite(LED_L_pin, LOW);
  }
  
}
