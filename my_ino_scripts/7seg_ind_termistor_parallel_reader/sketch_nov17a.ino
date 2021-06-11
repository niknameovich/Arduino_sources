#define PERIOD 5000
#define THERMO 1000

int measures[5];
uint32_t timer = 0;
uint32_t T_timer = 0;
bool incdec;
void one(byte *port);
void two(byte *port);
void three(byte *port);
void four(byte *port);
void five(byte *port);
void six(byte *port);
void seven(byte *port);
void eigth(byte *port);
void nine(byte *port);
void ten(byte *port);
void zero(byte *port);
void (*numbers[11])(byte*) ={zero, one, two, three, four, five, six, seven, eigth, nine, ten}; 
byte *indicator;
byte *ARDREG;
volatile int currentindex;
volatile int counter;
String hh = "";
bool cB = LOW;
bool lB = LOW;
byte mcount = 0;
int averageT = 0;
const int Rb = 9800;
const int Ma = 1023;
const int beta = 3970;
const int Tr = 298;
const int Rr = 10000;
void setup() {
  // put your setup code here, to run once:
  DDRB = 0b11111111;
  attachInterrupt(1, increase, LOW);
  pinMode(3,INPUT);
  counter = 0;
  incdec = true;
  ARDREG = &PORTB;
  timer = millis();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  int state = ButtonClearDown();
  //  if (state == HIGH && lB == LOW)
  //  {
  if (currentindex == 10 && incdec)
  {
    counter = -1;
    incdec = false;
  }
  if (currentindex == 0 && !incdec)
  {
    counter = 1;
    incdec = true;
  }
  if (millis() - T_timer >= THERMO)
  {
    increase();
    Serial.println("Value on display is");
    Serial.println(currentindex);
    measures[mcount] = analogRead(A0);
    Serial.println("measure is");
    Serial.println(measures[mcount]);
    mcount++;
    if (mcount > 4)
      mcount = 0;
    do
    {
      T_timer += THERMO;
      if (T_timer < THERMO)break;
    }
    while (T_timer < millis() - THERMO);
    }


  if (millis() - timer >= PERIOD)
  {
    for (int i = 0; i < 5; i++)
    {
      averageT += measures[i];
    }
    averageT = averageT / 5;
    Serial.println("Current Temperature =");
    Serial.println(readThermistor());
    averageT = 0;
    do
    {
      timer += PERIOD;
      if (timer < PERIOD)break;
    }
    while (timer < millis() - PERIOD);
    }
  //задаем значение для семисегментника = значение + counter
  // проверяем, если текущее значение == 9 и флаг повышайки тру, кидаем 0 на пин 2 и ставим флаг на понижение
  // если значение ==0 и флаг на понижайке кидаем 5В на пин 2
  // параллельно читать что нибудь с датчика и выводить в сериалпор
  // поставить фильтр на кнопку, убрать дребезг(найти инфу про фронтоформирующие цепи) подключить выход в пин 2 напрямую т
}


double readThermistor()
{
  double Rt = 0;
  double Tc = 0;
  Rt = ((Ma / averageT) - 1);
  Rt=Rt*Rb;
 
  Tc = ((beta * Tr) / (beta + (Tr * log(Rt / Rr))));
  Serial.println(Tc);
  Tc=Tc-273;
  Serial.println(Tc);
  return Tc;
}

void increase()
{
  currentindex += counter;
  numbers[currentindex](ARDREG);
}





bool ButtonClearDown()
{
  bool current = digitalRead(4);
  if (current != lB)
  {
    delay(30);
    current = digitalRead(4);
  }
  return current;
}

void zero(byte* port)
{
  *port = B00111111;
}
void one(byte* port)
{
  *port = B01010000;
}
void two(byte* port)
{
  *port = B01011011;
}
void three(byte* port)
{
  *port = B01111001;
}
void four(byte* port)
{
  *port = B01110100;
}
void five(byte* port)
{
  *port = B01101101;
}
void six(byte* port)
{
  *port = B01101111;
}
void seven(byte* port)
{
  *port = B01011000;
}
void eigth(byte* port)
{
  *port = B01111111;
}
void nine(byte* port)
{
  *port = B01111101;
}
void ten(byte* port)
{
  *port = B10000000;
}


void set_reg(byte *port, byte* val, int bitnum)
{
}
void set_pins(int index, byte *indicator)
{
//  indicator = &currentvalue[index];
//  Serial.println("Current state is");
//  Serial.println(index);
//  *ARDREG = *indicator;
}
