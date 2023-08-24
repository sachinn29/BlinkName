// Define the pin for the button and initial button states
const int button = 12;
int buttonState = 0; 
int lastButtonState = HIGH; // Store the previous button state
bool blinking_name = false; 
int charIndex = 0;

// Array to hold the input name and its index
char nameInput[100];       
int indexInput = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as output
  pinMode(button, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  Serial.begin(9600); // Initialize serial communication
}

// Function to blink a dot
void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to blink a dash
void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

// Function to convert a character to Morse code
void morse_encryption(char character) {
  switch (character) {
    // Cases for each character's Morse code
    // ...
    default:
      // Do nothing for characters not in the Morse code table
      break;
  }
}

void loop() {
  buttonState = digitalRead(button);

  // Check for a button press (transition from HIGH to LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    blinking_name = !blinking_name; // Toggle blinking state
    charIndex = 0; // Reset the character index
  }

  lastButtonState = buttonState; // Store the current button state

  if (blinking_name) {
    if (nameInput[charIndex] != '\0') {
      char currentChar = nameInput[charIndex];
      morse_encryption(currentChar); // Blink Morse code for the current character
      delay(1000);

      charIndex++;
    } else {
      blinking_name = false; // Finish blinking the name
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW); // Turn off LED if not blinking
  }

  // Read characters from serial input
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar == '\n' || indexInput >= sizeof(nameInput) - 1) {
      nameInput[indexInput] = '\0'; // Null-terminate the input name
      indexInput = 0; // Reset the index for the next input
      Serial.print("THE NAME ");
      Serial.print(nameInput);
      Serial.print(" IS BLINKING ON THE LED ");
      blinking_name = true; // Start blinking the name
    } else {
      nameInput[indexInput] = incomingChar; // Store the incoming character
      indexInput++;
    }
  }
}
