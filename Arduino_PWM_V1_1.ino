    //Version 1.1 code with better blinking of pin 13 integrated LED according to PWM pulses:
     const int setPoint = 13.5 * 20 / (20+82) * 1024 / 5;
     int measurement = 0;
     int pulseWidth = 0;
     int difference = 0;
     int stepSize = 0;
     int calculation = 0;
     int led = 13;

    void setup() {
     TCCR2A = TCCR2A | 0x30;
     TCCR2B = TCCR2B & 0xF8 | 0x01;
     analogWrite(11, 117);
     analogWrite(3, 137);
     //  Serial.begin(9600);
     pinMode(led, OUTPUT);
     }

    void loop() {
     measurement = analogRead(A1);
     calculation = setPoint - measurement;
     difference = abs(calculation);
     stepSize = difference;

     if (measurement < setPoint)
    {
    pulseWidth += stepSize;
    if (pulseWidth > 255) pulseWidth = 255;
     analogWrite(led, 0); // pwm to LED
     }
     if (measurement > setPoint)
     {
     pulseWidth -= stepSize;
     if (pulseWidth < 0) pulseWidth = 0;
    analogWrite(led, 255); // pwm to LED
    }
    //  Serial.println(pulseWidth);
    analogWrite(9, pulseWidth);
    delay(10);
    }

