// TODO: define PIN_LED's number based on connection figure.
// Hint: please refer the lab0 code and connection figure
// Hint: toggle indicates the LED status (1=off/0=on).

unsigned int toggle;

// setup function
void setup(){

  pinMode(7, OUTPUT);
  Serial.begin(115200);

  // TODO: Give toggle initial value.
  // Hint: set the variable that we defined to 0.
  toggle = 0;

}


// main code execution
void loop(){

  // TODO: write value to LED using digitalWrite function
  // Hint: please refer the usage of function digitalWrite
  digitalWrite(7, toggle);

  delay(1000);

  // TODO: writing a for loop to blink the LED 5 times.
  // Hint: Please refer to waveform figure that we provide
  for (int i = 1; i < 12; i++) {
    toggle = i % 2;
    digitalWrite(7, toggle);
    delay(100);
  }

  // suspend the execution
  while (1){}
}
