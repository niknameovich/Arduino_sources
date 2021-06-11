#define DRYINTERVAL 10
#define DRYLIMIT 400
#define MPOWER_PIN PD7

uint32_t PERIOD = 300000;
uint32_t MEASURE = 60000;
uint32_t PUMPISON = 1000;
uint32_t PUMPMEASURE = 200;
uint32_t * currentmeasure;
uint32_t * currentperiod;
int measures[5];
byte mcount = 0;
int averageT = 0;
uint32_t timer = 0;
uint32_t T_timer = 0;
byte mode=0;
int measure = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
 // Serial.begin(9600);
  timer = millis();
  currentmeasure = &MEASURE;
  currentperiod = &PERIOD;

}
void set_mode(byte mode)
{
  switch (mode)
  {
    case 1:
      currentperiod = &PUMPISON;
      currentmeasure = &PUMPMEASURE;
      break;
    case 0:
      currentperiod = &PERIOD;
      currentmeasure = &MEASURE;
      break;
  }
}

void loop() {

set_mode(mode);
  if (millis() - T_timer >= *currentmeasure)
  {
    bitSet(PORTD,MPOWER_PIN);
    measure = analogRead(A0);
    measures[mcount] = measure;
  //  Serial.println("measure is");
   // Serial.println(measures[mcount]);
    mcount++;
    bitClear(PORTD,MPOWER_PIN);
    do
    {
      T_timer += *currentmeasure;
      if (T_timer < *currentmeasure)break;
    }
    while (T_timer < millis() - *currentmeasure);
  }
  if (millis() - timer >= *currentperiod)
  {
    for (int i = 0; i < 5; i++)
    {
      averageT += measures[i];
    }
    averageT = averageT / 5;
 //   Serial.println("Current Hydro =");
 //   Serial.println(averageT);
    if (averageT>=DRYLIMIT+DRYINTERVAL)
    {
      mode = 1;
      bitSet(PORTB, PB0);
    }
    else if (averageT<=DRYLIMIT-DRYINTERVAL)
    {
      mode=0;
      bitClear(PORTB, PB0);
    }

    averageT = 0;
    mcount = 0;
    do
    {
      timer += *currentperiod;
      if (timer < *currentperiod)break;
    }
    while (timer < millis() - *currentperiod);
  }
  // put your main code here, to run repeatedly:

}
