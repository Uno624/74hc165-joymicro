#define NUMBER_OF_SHIFT_CHIPS   2
/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8
/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5
/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   50
/* You will need to change the "int" to "long" If the

 * NUMBER_OF_SHIFT_CHIPS is higher than 2.
*/
#define joyButton17 7
#define joyButton18 6
#define joyButton19 5
#define joyButton20 4
#define joyButton21 3
#define joyButton22 2
#define joyButton23 14
#define joyButton24 15
#define joyButton25 2

#define BYTES_VAL_T unsigned int
int ploadPin        = 8;  // Connects to Parallel load pin the 165
int clockEnablePin  = 16;  // Connects to Clock Enable pin the 165
int dataPin         = 10; // Connects to the Q7 pin the 165
int clockPin        = 9; // Connects to the Clock pin the 165

BYTES_VAL_T pinValues;
BYTES_VAL_T oldPinValues;

/* This function is essentially a "shift-in" routine reading the

 * serial Data from the shift register chips and representing

 * the state of those pins in an unsigned integer (or long).
*/
BYTES_VAL_T read_shift_regs()
{
    long bitVal;
    BYTES_VAL_T bytesVal = 0;
    /* Trigger a parallel Load to latch the state of the data lines,
    */
    digitalWrite(clockEnablePin, HIGH);
    digitalWrite(ploadPin, LOW);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(ploadPin, HIGH);
    digitalWrite(clockEnablePin, LOW);
    /* Loop to read each bit value from the serial out line
     * of the SN74HC165N.
    */
    for(int i = 0; i < DATA_WIDTH; i++)
    {
        bitVal = digitalRead(dataPin);
        /* Set the corresponding bit in bytesVal.
        */
        bytesVal |= (bitVal << ((DATA_WIDTH-1) - i));
        /* Pulse the Clock (rising edge shifts the next bit).
        */
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(clockPin, LOW);
    }
    return(bytesVal);
}


/* Dump the list of zones along with their current status.

*/

void display_pin_values()
{
    pinValues = ~read_shift_regs();
  int Pin1 = (pinValues >> 0) & 1;
    int Pin2 = (pinValues >> 1) & 1;
    int Pin3 = (pinValues >> 2) & 1;
    int Pin4 = (pinValues >> 3) & 1;
    int Pin5 = (pinValues >> 4) & 1;
    int Pin6 = (pinValues >> 5) & 1;
    int Pin7 = (pinValues >> 6) & 1;
    int Pin8 = (pinValues >> 7) & 1;
    int Pin9 = (pinValues >> 8) & 1;
    int Pin10 = (pinValues >> 9) & 1;
    int Pin11 = (pinValues >> 10) & 1;
    int Pin12 = (pinValues >> 11) & 1;
    int Pin13 = (pinValues >> 12) & 1;
    int Pin14 = (pinValues >> 13) & 1;
    int Pin15 = (pinValues >> 14) & 1;
    int Pin16 = (pinValues >> 15) & 1;
    Serial.print(Pin1);
    Serial.print(Pin2);
    Serial.print(Pin3);
    Serial.print(Pin4);
    Serial.print(Pin5);
    Serial.print(Pin6);
    Serial.print(Pin7);
    Serial.print(Pin8);
     Serial.print("   ");
    Serial.print(Pin9);
    Serial.print(Pin10);
    Serial.print(Pin11);
    Serial.print(Pin12);
    Serial.print(Pin13);
    Serial.print(Pin14);
    Serial.print(Pin15);
    Serial.print(Pin16);
    Serial.print(" D = ");
    Serial.print(digitalRead(joyButton17));
    Serial.print(digitalRead(joyButton18));
    Serial.print(digitalRead(joyButton19));
    Serial.print(digitalRead(joyButton20));
    Serial.print(digitalRead(joyButton21));
    Serial.print(digitalRead(joyButton22));
    Serial.print(digitalRead(joyButton23));
    Serial.print(digitalRead(joyButton24));
    Serial.println(digitalRead(joyButton25));
    
}

void setup()
{
    Serial.begin(115200);
    pinMode(joyButton17, INPUT_PULLUP);
  pinMode(joyButton18, INPUT_PULLUP);
  pinMode(joyButton19, INPUT_PULLUP);
  pinMode(joyButton20, INPUT_PULLUP);
  pinMode(joyButton21, INPUT_PULLUP);
  pinMode(joyButton22, INPUT_PULLUP);
  pinMode(joyButton23, INPUT_PULLUP);
  pinMode(joyButton24, INPUT_PULLUP);
  pinMode(joyButton25, INPUT_PULLUP);
    /* Initialize our digital pins...
    */
    pinMode(ploadPin, OUTPUT);
    pinMode(clockEnablePin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT);
    digitalWrite(clockPin, LOW);
    digitalWrite(ploadPin, HIGH);
    /* Read in and display the pin states at startup.
    */
    pinValues = read_shift_regs();
    display_pin_values();
    oldPinValues = pinValues;
    
}
void loop()
{
    /* Read the state of all zones.
    */
    display_pin_values();
    
    delay(POLL_DELAY_MSEC);
}