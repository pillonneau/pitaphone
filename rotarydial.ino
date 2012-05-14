int count                 = 0;
int needToPrint           = 0;
int in                    = 2;
int lastState             = LOW;
int trueState             = LOW;
int cleared               = 0;
float power10             = 0;
int number_read           = 0;
long lastStateChangeTime  = 0;

const int ledPin = 11;   // Teensy has LED on 11, Teensy++ on 6

//void execute_command(int);

int debounceDelay                  = 10;
int dialHasFinishedRotatingAfterMs = 100;
int oneDigitRotationDelay          = 100;

void setup()
{
  Serial.begin(9600);
  pinMode(in, INPUT);
}

void execute_command(int number)
{
  
  if(number == 1) {
    Keyboard.println();
  }
  else if(number == 2) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.set_key1(KEY_P);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  else if(number == 3) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.set_key1(KEY_O);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  else if(number == 4) {
    Keyboard.print("Et les specs ? Ou elles sont les specs ?");
  }
  else if(number == 8) {
    Keyboard.print("Hey Cedric, arrete les mantis !");
  }
  else if(number == 5) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.set_key1(KEY_SPACE);
    Keyboard.send_now();
    
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  else {
    Keyboard.print(number);
  }
}


void loop()
{
  int reading = digitalRead(in);

  // si on a dépassé le délai d'attente final
  if ((millis() - lastStateChangeTime) > dialHasFinishedRotatingAfterMs) {

    if (needToPrint) {
      
      execute_command(count%10);
      
      number_read = 0;
      count       = 0;
      cleared     = 0;
      needToPrint = 0;
    }
  }
//  else if((millis() - lastStateChangeTime) > oneDigitRotationDelay) {
////    number_read = count % 10;
////    number_read = (int)((count%10) * pow(10,power10));
//    number_read = (int)(pow(10.0f,power10));
//    
//    power10++;
//    count = 0;
//  }

  if (reading != lastState) {
    lastStateChangeTime = millis();
  }
  
  if ((millis() - lastStateChangeTime) > debounceDelay) {
    // debounce - this happens once it's stablized
    if (reading != trueState) {
    
      // this means that the switch has either just gone from closed->open or vice versa.
      trueState = reading;
      if (trueState == HIGH) {
        // increment the count of pulses if it's gone high.
        count++; 
        needToPrint = 1; // we'll need to print this number (once the dial has finished rotating)
       } 
    }
  }
  
  lastState = reading;

}

