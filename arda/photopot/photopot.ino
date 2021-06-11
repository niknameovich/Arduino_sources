int BRPT;
int* brightness;
bool mode;
void setup()
{
  Serial.begin(9600);
  DDRC &= (0 << 0) & (0 << 5);
  DDRC |= (1 << 1) | (1 << 2) | (1 << 3);
  brightness = &BRPT;
  mode = false;
}
void loop()
{
  set_bright(brightness);
  set_light(brightness);
}

void set_bright(int* phR)
{
  *phR = 255-map(analogRead(A5), 0, 1023, 0, 255);
  Serial.println(*phR);
}
void set_light(int* pOM)
{
  int val =  analogRead(A0);
  Serial.println(val);
  if (val < 255)
  {
    analogWrite(3, abs(val-*pOM));
    analogWrite(5, 0);
    analogWrite(6, 0);
  }
  else if (val < 511)
  {
    analogWrite(3, abs(val-*pOM));
    analogWrite(5, 255 - abs(255 - (val - *pOM)));
    analogWrite(6, 0);
  }
  else if (val < 766)
  {
    analogWrite(3, 0);
    analogWrite(5, 255 - *pOM);
    analogWrite(6, 255 - abs(511 - (val - *pOM)));
  }
  else
  {
    analogWrite(3, 255 - abs(766 - (val - *pOM)));
    analogWrite(5, 255 - *pOM);
    analogWrite(6, 255 - *pOM);
  }
}
