const int button = 12;   
int buttonState = 0;       
int buttonState = HIGH; 
bool blinking_name = false;  
int charIndex = 0;         

char nameInput[100];       
int indexInput = 0;       

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button, INPUT_PULLUP); 
  Serial.begin(9600);
}

void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void morse_encryption(char character) {
  switch (character) {
    case 'a':
      dot(); dash();
      break;
    case 'b':
      dash(); dot(); dot(); dot();
      break;
    case 'c':
      dash(); dot(); dash(); dot();
      break;
    case 'd':
      dash(); dot(); dot();
      break;
    case 'e':
      dot();
      break;
    case 'f':
      dot(); dot(); dash(); dot();
      break;
    case 'g':
      dash(); dash(); dot();
      break;
    case 'h':
      dot(); dot(); dot(); dot();
      break;
    case 'i':
      dot(); dot();
      break;
    case 'j':
      dot(); dash(); dash(); dash();
      break;
    case 'k':
      dash(); dot(); dash();
      break;
    case 'l':
      dot(); dash(); dot(); dot();
      break;
    case 'm':
      dash(); dash();
      break;
    case 'n':
      dash(); dot();
      break;
    case 'o':
      dash(); dash(); dash();
      break;
    case 'p':
      dot(); dash(); dash(); dot();
      break;
    case 'q':
      dash(); dash(); dot(); dash();
      break;
    case 'r':
      dot(); dash(); dot();
      break;
    case 's':
      dot(); dot(); dot();
      break;
    case 't':
      dash();
      break;
    case 'u':
      dot(); dot(); dash();
      break;
    case 'v':
      dot(); dot(); dot(); dash();
      break;
    case 'w':
      dot(); dash(); dash();
      break;
    case 'x':
      dash(); dot(); dot(); dash();
      break;
    case 'y':
      dash(); dot(); dash(); dash();
      break;
    case 'z':
      dash(); dash(); dot(); dot();
      break;
    default:
      
      break;
  }
}


void loop() {
  buttonState = digitalRead(button);

  if (buttonState == LOW && buttonState == HIGH) {
    blinking_name = !blinking_name; 
    charIndex = 0; 
  }

  buttonState = buttonState;

  if (blinking_name) {
    if (nameInput[charIndex] != '\0') {
      char currentChar = nameInput[charIndex];
      morse_encryption(currentChar);
      delay(1000); 

      charIndex++;
    } else {
      blinking_name = false; 
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar == '\n' || indexInput >= sizeof(nameInput) - 1) {
      nameInput[indexInput] = '\0'; 
      indexInput = 0; 
      Serial.print("THE NAME ");
      Serial.print(nameInput);
      Serial.print(" IS BLINKING ON THE LED ");
      blinking_name = true; 
    } else {
      nameInput[indexInput] = incomingChar;
      indexInput++;
    }
  }
}
