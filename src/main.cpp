#include  <Arduino.h>

const int clkPin = 25;
const int dataPin = 26;

int choice;

void SoundChip_Play(int addr);
void I2Cdata(int cmd);
void volume_control(int vol);
int volume_mapping(int vol);

void setup()
{
  pinMode(dataPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  /* VOLUME CONTROL*/
    Serial.print("Enter preffered volume level:\n");
    Serial.print("Enter 0 -> 4 for MAX volume\n");
    Serial.print("Enter 5 -> 9 for MEDIUM Volume\n");
    Serial.print("Enter 'a -> f' for MIN volume\n");
    Serial.print("\n");
    Serial.print("!!! IF YOU SET A PERTICULAR VOLUME LEVEL, THAT WILL REMAIN UNTIL NEXT RESET !!!\n");
    Serial.print("!!! YOU CAN'T CHANGE IN BETWEEN !!! FOR RESETTING DEVICE, JUST SWITCH OFF AND ON !!!\n");
    Serial.print("\n");

      while(Serial.available() == 0) {
      }
      int vol = Serial.read();

      vol = volume_mapping(vol);

      vol = vol - 48;

      //volume_control(vol);
      int volumes_levels[16]={  0x00, 0x01, 0x02, 0x03,
                                0x04, 0x05, 0x06, 0x07, 
                                0x08, 0x09, 0x0A, 0x0B, 
                                0x0C, 0x0D, 0x0E, 0x0F };

      volume_control(volumes_levels[vol]);
      // volume_control(0x4400);

/* SELECTING TUNES*/
  B:
    Serial.print("Enter 1 for tune 1\n");
    Serial.print("Enter 2 for tune 2\n");

    while(Serial.available() == 0) {
    }
    choice = Serial.read();
    choice = choice - 48;


    if (choice == 1)
    {
      SoundChip_Play(0);
      goto B;
    }
    else if (choice == 2)
    {
      SoundChip_Play(1);
      goto B;
    }
}

void I2Cdata(int cmd)
{
  
  int mask = 0;
  for(mask = 0x8000; mask > 0; mask >>=1)
  {
    digitalWrite(clkPin, LOW);
    if(cmd & mask)
    {
      digitalWrite(dataPin, HIGH);      
    }
    else
    {
      digitalWrite(dataPin, LOW);
    }
    digitalWrite(clkPin, HIGH);
  }
  digitalWrite(clkPin, LOW);
}
void SoundChip_Play(int addr)
{
  int cmd = 0;
 
  cmd = 0x9800 + addr;

  // Serial.print("Tune: ");
  // Serial.println(cmd, HEX);

  digitalWrite(clkPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(dataPin, LOW);

  I2Cdata(cmd);
  
  digitalWrite(dataPin, LOW);
  digitalWrite(clkPin, HIGH);
  digitalWrite(dataPin, HIGH);

  delayMicroseconds(20);
}

void volume_control(int vol)
{
  int cmd = 0;
  cmd = 0x4400 + vol;

  Serial.print("Volume: ");
  Serial.println(cmd, HEX);

  digitalWrite(clkPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(dataPin, LOW);

  I2Cdata(cmd);

  digitalWrite(dataPin, LOW);
  digitalWrite(clkPin, HIGH);
  digitalWrite(dataPin, HIGH);
}
int volume_mapping(int vol)
{
  if (vol >= 48 && vol <= 58)
  {
    return vol;
  }
  else if (vol >= 97 && vol <= 102)
  {
    return vol = vol - 39;
    return vol;
  }
  else 
    return Serial.print("Input Value Error");
}
