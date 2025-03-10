
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
}
void dash()
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);
}
void dot()
{
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);
}
// dot = half a second 
// dash = full second
void loop() {
  //J
  dot();
  dash();
  dash();
  dash();
  // A
  dot();
  dash();
  //C
  dash();
  dot();
  dash();
  dot();
  //K
  dash();
  dot();
  dash();
  //S
  dot();
  dot();
  dot();
  //O
  dash();
  dash();
  dash();
  //N
  dash();
  dot();
  delay(5000);
}
