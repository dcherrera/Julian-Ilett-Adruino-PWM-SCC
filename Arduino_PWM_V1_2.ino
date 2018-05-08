const int setPoint = 13.5 * 20 / (20+82) * 1024 / 5 ;
int measurement = 0;
int pulseWidth = 0;
int difference = 0;
int stepSize = 0;
 
void setup() {
TCCR2A = TCCR2A | 0x30;
TCCR2B = TCCR2B & 0xF8 | 0x01;
analogWrite(11, 117);
analogWrite(3, 137);
Serial.begin(9600);
}
 
void loop() {
measurement = analogRead(A1);
difference = abs(setPoint - measurement);
stepSize = difference;
 
if (measurement < setPoint) { pulseWidth += stepSize; if (pulseWidth > 255) pulseWidth = 255;
}
else if (measurement > setPoint)
{
pulseWidth -= stepSize;
if (pulseWidth < 0) pulseWidth = 0;
}
Serial.println(pulseWidth);
analogWrite(9, pulseWidth);
analogWrite(5, 255 - pulseWidth); // pwm to LED
delay(10);
}
