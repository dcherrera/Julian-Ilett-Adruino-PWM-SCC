//PWM Solar charge controller using Julian Iletts design and code (http://256.uk) but adapted to work on the ATTiny25/45/85 by Adam Welch (http://adamwelch.co.uk)
const int setPoint = 13.5 * 20 / (20+82) * 1024 / 5 ;
int measurement = 0;
int pulseWidth = 0;
int difference = 0;
int stepSize = 0;
 
void setup() {
   
    TCCR0A = 2<<COM0A0 | 3<<COM0B0 | 3<<WGM00;  // Timer 0 Control Register A - Set None Inverting Mode, Set Inverting Mode, Enable Fast PWM
    TCCR0B = 0<<WGM02 | 1<<CS00;  // Timer 0 Control Register B - Enable Fast PWM, No Prescaler
    TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;  // Timer 1 Control Register - Prevent timer using pin OC1A, again prevents use, No Prescaler
    GTCCR = 1<<PWM1B | 2<<COM1B0;  // General Control Register for Timer 1 - Enable use of pin OC1B, None inverting mode.
   
  analogWrite(0, 117); //ATTiny85 Leg 5 // OC0A
  analogWrite(1, 137); //ATTiny85 Leg 3 // OC1B
}
 
void loop() {
  measurement = analogRead(4); //ATTiny85 Leg 3
  difference = abs(setPoint - measurement);
  stepSize = difference;
   
  if (measurement < setPoint)
  {
    pulseWidth += stepSize;
    if (pulseWidth > 255) pulseWidth = 255;
  }
  else if (measurement > setPoint)
  {
    pulseWidth -= stepSize;
    if (pulseWidth < 0) pulseWidth = 0;
  }
  //Serial.println(pulseWidth);
  analogWrite(3, pulseWidth); //ATTiny Leg 2 
  delay(10);
