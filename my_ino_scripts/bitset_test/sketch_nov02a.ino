byte[]reg_my;
uint32_t mt;
int interval;
int* pointer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  interval = 500;
  pointer = &interval;
  DDRD = 0b11111000;
  DDRB = 0b00011111;
  mt = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {

int mult = Serial.read()-'0';
*pointer = mult*100;
  }
    for (int j = 0; j <= 7; j++)
    {
      if (bitRead(DDRD, j) == 1)
      {
        while (millis() - mt < *interval)
        {
          bitSet(PORTD, j);
        }
        bitClear(PORTD, j);
      }
  }
}
