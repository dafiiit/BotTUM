volatile long temp, counter = 0; // This variable will increase or decrease depending on the rotation of encoder
float divi = 1;

void setup()
{
    Serial.begin(9600);
    pinMode(2, INPUT_PULLUP); // internal pullup input pin 2

    pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
    // Setting up interrupt
    // A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
    attachInterrupt(0, ai0, RISING);

    // B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
    attachInterrupt(1, ai1, RISING);
}

void loop()
{
    // Send the value of counter
    if (counter != temp)
    {
        // Serial.println (counter/divi);
        Serial.println(((counter / 1200.0) - (counter / 1200))360);
        temp = counter;
    }
    if (Serial.available() > 0)
    {
        char inbyte = (char)Serial.read();
        switch (inbyte)
        {
        case 'r':
            counter = 0;
            break;
        case 'u':
            divi = 1200;
            break;
        case 'd':
            Serial.println(((counter / 1200.0) - (counter / 1200))360);
            break;
        case 'a':
            counter = 0;
            break;
        case 'b':
            counter = 0;
            break;
        case 'c':
            counter = 0;
            break;
        }
    }
}

void ai0()
{
    // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
    // Check pin 3 to determine the direction
    if (digitalRead(3) == LOW)
    {
        counter++;
    }
    else
    {
        counter--;
    }
}

void ai1()
{
    // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
    // Check with pin 2 to determine the direction
    if (digitalRead(2) == LOW)
    {
        counter--;
    }
    else
    {
        counter++;
    }
}