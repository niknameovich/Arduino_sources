#include "RobotIRremote.h"
#define CHN 2
IRrecv irrecv(9); // указываем вывод, к которому подключен приемник
int chanels[] = {A0, A1};
decode_results results;
int i = 0;
struct Chanel_adress
{
  int* pinadr;
  unsigned long IRadr;
};

Chanel_adress storedadr[CHN];

void setup() {
  // put your setup code here, to run once:
  IRsetup();
}

void IRsetup() {
  irrecv.enableIRIn(); // запускаем прием
  do
  {
    pinMode(chanels[i], OUTPUT);
    digitalWrite(chanels[i], LOW);
    if ( irrecv.decode( &results ) && results.value != 0xFFFFFFFF)
    {                 
      storedadr[i].pinadr = &chanels[i];
      storedadr[i].IRadr = results.value;
      digitalWrite(chanels[i], HIGH);
      delay(1000);
      i++;
      irrecv.resume(); // принимаем следующую команду
    }
  } while (i < CHN);
  i = 0;
}


void loop()
{

//irrecv.enableIRIn();
// запускаем прием
  IRloop();

}


void IRloop() {
  // put your main code here, to run repeatedly:
  if ( irrecv.decode( &results )&& results.value != 0xFFFFFFFF)
  { // если данные пришли
    for (i = 0; i < CHN; i++)
    {
      if (storedadr[i].IRadr == results.value){
        if (digitalRead(chanels[i]) == HIGH)
        {
          digitalWrite(chanels[i],LOW);
        }
        else
        {
          digitalWrite(chanels[i] ,HIGH);
        }
     // break;
      }
    }
    delay(100);
    irrecv.resume();// принимаем следующую команду
  }
}// принимаем следующую команду
