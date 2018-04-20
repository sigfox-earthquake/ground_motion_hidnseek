#include <EEPROM.h>

int a = 0;
int value;

void setup()
{
  Serial.begin(57600);
  for (int i = 0; i < 255; i++)
    EEPROM.write(i, i);
}
//just a test I was doing. Not working
//void get_frequency(uint8_t *array_of_xyz, uint8_t time_passed, uint8_t values)
//{
//  int z_amplitude = NULL;
//  //0, 3, -4, 7, -8, 5, -2
//  //find the frequency of x and y
//  //absvalue/time. 
//  //how long does it take to get from 0 to 0. that is the hertz
//  //what is the distance between the highest value and the lowest value 
//
//  time_between_vals = time_passed / values;
//    //find the frequency of z
//  for (int n = 0; n < values - 1; n++)
//  {
//    if (n > 0)
//      z_amplitude = array_of_xyz[n] + abs(array_of_xyz[n + 1]);
//    else
//      z_amplitude = abs(array_of_xyz[n + 1]) + array_of_xyz[n];
//  }
//
//}
//int main()
//{
//  uint8_t array_one[7] = {0, 3, -4, 7, -8, 5, -2};
//  get_frequency(array_one, 10, 7);
//}


void loop()
{
int i = 32;
//int n = 0;

//  for (int i = 0; i < 255; i++)
    EEPROM.update(3, i);

    
  value = EEPROM.read(a);

  Serial.print(a);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  a = a + 1;

  if (a == 512)
    a = 0;

  delay(500);
}

