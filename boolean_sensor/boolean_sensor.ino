
#include <LiquidCrystal.h>

const int button_pin   = 13;    //button pinout/variables
const int switch_A_pin = 5;
const int switch_B_pin = 4;
const int LED_A_pin    = 8;
const int LED_B_pin    = 9;
const int LED_array_true_pin      = 10;    //pin LED works for speaker.
const int LED_array_false_pin     = 11;

int button_push_counter = 0;    //initalize counter to 0 so program only starts after inital button press from splash screen
int button_state        = 0;        
int last_button_state   = 0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

void PrintLogicFunction(int option);
bool LogicalFunctions(int option);
void DigitalReadHallSensor(bool &Left, bool &Right);
//void SatisfiedProcedure(int bounded_rand);

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
  pinMode(button_pin,INPUT);
  pinMode(LED_array_true_pin,OUTPUT);
  pinMode(LED_array_false_pin,OUTPUT);
  pinMode(LED_A_pin,OUTPUT);
  pinMode(LED_B_pin,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2); 
  lcd.clear(); 
  lcd.createChar(1, smiley);

  lcd.setCursor(0,0);
  lcd.print("GIRL");
  lcd.setCursor(2,1);
  lcd.print("DAY ");
  lcd.write((byte)1);
  //delay(66);
}


void loop() {
  //int bounded_rand = rand() % (101); //random number bounded between 0 and 100 
  //int num = (rand() %
  //(upper - lower + 1)) + lower;
  button_state = digitalRead(button_pin);
  
  if (button_state != last_button_state) {   // compare the button_state to its previous state
    
      if (button_state == HIGH){             //increment counter each time button is pressed on
        lcd.clear();
        button_push_counter+=1;
      }
      delay(400);
      do{
        //lcd.clear();
        lcd.print("Function");                  
        lcd.setCursor(0,1);
        PrintLogicFunction( button_push_counter );
         
        lcd.setCursor(10,0);
        lcd.print("Output ");
        lcd.setCursor(10,1);
                                
        if( LogicalFunctions(button_push_counter) ){
          //lcd.clear();
          lcd.print("TRUE ");
          lcd.write((byte)1);
          digitalWrite(LED_array_true_pin, HIGH);
          digitalWrite(LED_array_false_pin, LOW);
          delay(500);
        }
        else{
          digitalWrite(LED_array_false_pin, HIGH);
          digitalWrite(LED_array_true_pin, LOW);
          lcd.print("FALSE ");
        }
        
        delay(10);
        button_state = digitalRead(button_pin);
      }while(button_state == last_button_state); 

  last_button_state = (button_state - 1);         // save the current state as the last state, for next time through the loop

  if (button_push_counter % 5 == 0){
    button_push_counter = 0;                      //restart menu options once final menu option is reached
  }
  }
}

void PrintLogicFunction(int option) {
    switch(option){
    case 1:
        lcd.print("AND");
        break;
    case 2:
        lcd.print("OR");
        break;
    case 3:
        lcd.print("XOR");
        break;
    case 4:
        lcd.print("NAND");
        break;
    case 5:
        lcd.print("NOR");
        break;
    }
}

bool LogicalFunctions(int option) {
    bool function_satisfied = false;
    bool switch_A_state, switch_B_state;
    DigitalReadHallSensor(switch_A_state, switch_B_state);

    switch(option){
    case 1:
      if(switch_A_state && switch_B_state)
        function_satisfied = true;
      break;
    case 2:
      if(switch_A_state || switch_B_state)
        function_satisfied = true;
      break;
    case 3:
      if(!switch_A_state != !switch_B_state)
        function_satisfied = true;
      break;
    case 4:
      if( !(switch_A_state && switch_B_state) )
        function_satisfied = true;
      break;
    case 5:
      if( !(switch_A_state || switch_B_state) )
        function_satisfied = true;
      break;
    }
    return function_satisfied;
}


void DigitalReadHallSensor(bool &A, bool &B) {
  float switch_A_data = analogRead(switch_A_pin) * (5.0 / 1023);
  delay(250);
  float switch_B_data = analogRead(switch_B_pin) * (5.0 / 1023);
  
  if(switch_A_data < 1){
    A = true;
    digitalWrite(LED_A_pin, HIGH);
  }
  else{
    A = false;
    digitalWrite(LED_A_pin, LOW);
  }

  if(switch_B_data < 1){
    B = true;
    digitalWrite(LED_B_pin, HIGH);
  }
  else{
    B = false;
    digitalWrite(LED_B_pin, LOW);
  }
}


/*
void SatisfiedProcedure(int bounded_rand) {
    lcd.clear();
    //lcd.autoscroll();
    //bounded_rand = 10;
    if(bounded_rand <= 33){
        lcd.print("SUCCESS!");
        digitalWrite(LED_array_true_pin, HIGH);
    }
    else if(bounded_rand <= 66){
        lcd.print("GREAT JOB ");
        lcd.write((byte)1);
        digitalWrite(LED_array_true_pin, HIGH);
    }
    else{
        lcd.print("MISSION");
        lcd.setCursor(0,1);
        lcd.print("COMPLETE");
        digitalWrite(LED_array_true_pin, HIGH);
    }
    
}
*/
