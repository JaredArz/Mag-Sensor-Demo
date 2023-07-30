
#include <LiquidCrystal.h>

const int buttonPin  = 13;    //button pinout/variables
const int hall_L_pin = 4;
const int hall_R_pin = 5;

const int LED_pin  = 10;

int buttonPushCounter = 0;    //initalize counter to 1 so program only starts after inital button press from splash screen
int buttonState       = 0;        
int lastButtonState   = 0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
void And();
void Or();
void Xor();
void Nor();
void Nand();

byte smiley[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000
    };


void setup() {
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.createChar(1, smiley);

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
      lcd.print("Logic Function:");               //print menu choice, then delay
      lcd.setCursor(0,1);
      lcd.print("AND");
      delay(750);
      lcd.clear();
      do{                                   
        lcd.clear();
        And();
        delay(100);
        buttonState = digitalRead(buttonPin);
      }while(buttonState == lastButtonState); 
      break;
 
      case 2:                            
      lcd.clear();
      lcd.print("Logic Function:");               //print menu choice, then delay
      lcd.setCursor(0,1);
      lcd.print("OR");
      delay(750);
      lcd.clear();
      do{
        lcd.clear();
        Or();
        buttonState = digitalRead(buttonPin);
        delay(100);
      }while(buttonState == lastButtonState);
      break;

      case 3:                            
      lcd.clear();
      lcd.print("Logic Function:");               //print menu choice, then delay
      lcd.setCursor(0,1);
      lcd.print("XOR");
      delay(750);
      lcd.clear();
      do{
        lcd.clear();
        Xor();
        buttonState = digitalRead(buttonPin);
        delay(100);
      }while(buttonState == lastButtonState);
      break;

      case 4:                            
      lcd.clear();
      lcd.print("Logic Function:");               //print menu choice, then delay
      lcd.setCursor(0,1);
      lcd.print("NAND");
      delay(750);
      lcd.clear();
      do{
        lcd.clear();
        Nand();
        buttonState = digitalRead(buttonPin);
        delay(100);
      }while(buttonState == lastButtonState);
      break;

      case 5:                            
      lcd.clear();
      lcd.print("Logic Function:");               //print menu choice, then delay
      lcd.setCursor(0,1);
      lcd.print("NOR");
      delay(750);
      lcd.clear();
      do{
        lcd.clear();
        Nor();
        buttonState = digitalRead(buttonPin);
        delay(100);
      }while(buttonState == lastButtonState);
      break;
  
    }
  }

  lastButtonState = buttonState-1;          // save the current state as the last state, for next time through the loop

  if (buttonPushCounter % 5 == 0)
    buttonPushCounter = 0;                //reset button to 0, to begin menu options again

}



void And(){
    bool L_hall, R_hall;
    DigitalReadHall(L_hall, R_hall);
    if(L_hall && R_hall){
        digitalWrite(LED_pin, HIGH);
    }
}

void Or(){
    bool L_hall, R_hall;
    DigitalReadHall(L_hall, R_hall);
    if(L_hall || R_hall){
        digitalWrite(LED_pin, HIGH);
    }
}

void Xor(){
    bool L_hall, R_hall;
    DigitalReadHall(L_hall, R_hall);
    if(!L_hall != !R_hall){
        digitalWrite(LED_pin, HIGH);
    }
}

void Nand(){
    bool L_hall, R_hall;
    DigitalReadHall(L_hall, R_hall);
    if( !(L_hall && R_hall) ){
        digitalWrite(LED_pin, HIGH);
    }
}

void Nor(){
    bool L_hall, R_hall;
    DigitalReadHall(L_hall, R_hall);
    if( !(L_hall || R_hall) ){
        digitalWrite(LED_pin, HIGH);
    }
}

void DigitalReadHall(bool &Left, bool &Right){
  float hall_L_data = analogRead(hall_L_pin);
  float hall_R_data = analogRead(hall_R_pin);
  float volt_L = hall_L_data * (5.0 / 1023);
  float volt_R = hall_R_data * (5.0 / 1023);
  
  if(volt_L < 1){
    Left = true;
  }
  else{
    Left = false;
  }

  if(volt_R < 1){
    Right = true;
  }
  else{
    Right = false;
  }

}



void PrintSuccess(){
    int random_int = rand();
    int bounded_rand = random_int % (101); //bounded between 0 and 100 
    //int num = (rand() %
    //(upper - lower + 1)) + lower;

    if(rand <= 33){
        lcd.print("SUCCESS!");
    }
    else if(rand <= 66){
        lcd.print("GREAT JOB ");
        lcd.write((byte)1);
    }
    else{
        lcd.print("MISSION");
        lcd.setCursor(0,1);
        lcd.print("COMPLETE");
    }
    lcd.autoscroll();
}
