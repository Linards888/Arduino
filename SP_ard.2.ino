#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char message;

int LedB = A1;
int LedG = A2;
int LedR = A3;

int DS_pin = 4;
int STCP_pin = 3;
int SHCP_pin = 2;

int gg; int menu; long cp1; long cp2; long pl;
int bin[5] = {1, 1, 1, 1, 0};
int q[8] = {0, 1, 0, 0,   0, 0, 0};

LiquidCrystal_I2C lcd(0x27, 16, 4);

int digits [10][8]{
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,0,0,0,0},
  {0,1,1,0,1,1,0,1},
  {0,1,1,1,1,0,0,1},
  {0,0,1,1,0,0,1,1},
  {0,1,0,1,1,0,1,1},
  {0,1,0,1,1,1,1,1},
  {0,1,1,1,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,1,1,1,1,0,1,1}
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 4);
  lcd.clear();
  lcd.setCursor(4, 2);
  delay(1000);
  lcd.print(".");
  delay(3000);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  for (int x = 0; x < 4; x++) {
    lcd.clear();
    lcd.setCursor(4, 2);
    lcd.print("..");
    delay(500);
    lcd.print(".");
    delay(500);
    }
  delay(2000);
  lcd.clear();
  delay(200);
  lcd.setCursor(4, 2);
  lcd.print("!!!");
  delay(1000);
  lcd.clear();
  lcd.print("use <> to move");
  RGB_color(255, 255, 0);
  delay(2000);
  RGB_color(255, 0, 255);
  lcd.clear();
  
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);

  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedB, OUTPUT);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(">Servo  | Game");
  lcd.setCursor(16, 1);
  lcd.print(" remote | blokn.");
  lcd.setCursor(8, 1);
  lcd.print(" MakePin| ");
  lcd.setCursor(24, 1);
  lcd.print(" MadePid| ");
}

void loop() {
  while (1){
    if (Serial.available()){
      Serial.print(menu);
      message = Serial.read();
      if(message == 1){ 
        delay(30);
        if (Serial.available()){
          message = Serial.read();
          gg = message;
          bloknots();}}
      else if(message == 2){
        delay(25);
        if (Serial.available()){
          message = Serial.read();
          menu = message;
          Menu();}} 
      else if(message >= 2000000000){
        if (message == 2255000000){RGB_color(255, 0, 0);}
        else if (message == 2000255000){RGB_color(0, 255, 0);}
        else if (message == 2255255000){RGB_color(255, 255, 0);}
        else if (message == 2000000255){RGB_color(0, 0, 255);}
        else if (message == 2255000255){RGB_color(255, 0, 255);}
        else if (message == 2000255255){RGB_color(0, 255, 255);}
        else if (message == 2255255255){RGB_color(255, 255, 255);}
        else {RGB_color(1, 1, 1);}
        }
      else if(message >= 10 and message <= 19){DisplayDigit(message - 10);}
      else if(message == 3){
        delay(20);
        cp1 = Serial.read();
        delay(20);
        cp2 = Serial.read();
        delay(20);
        pl = Serial.read();
        //for (int i = 7; i>=0; i--){
        for(int i = 1; i>=9; i++){
          if(i == 4){
            i = 6;
          }
          delay(20);
          q[i] = Serial.read();
        }
        witch();}
      else if(message == 4){
        for(int i = 0; i>=4; i++){
          delay(20);
          bin[i] = Serial.read();
        }
        burts();}
    }
    delay(20);
  }
}

void bloknots(){
  switch (gg){
    lcd.clear();
    case 1:
      lcd.setCursor(0, 1);
      lcd.print("    izvelies");
      lcd.setCursor(16, 1);
      lcd.print(">blok1  | blok 4");
      lcd.setCursor(8, 1);
      lcd.print(" blok2  | blok 5");
      lcd.setCursor(24, 1);
      lcd.print(" blok3");
      break;
    case 2:
      lcd.setCursor(0, 1);
      lcd.print("    izvelies");
      lcd.setCursor(16, 1);
      lcd.print(" blok1  | blok 4");
      lcd.setCursor(8, 1);
      lcd.print(">blok2  | blok 5");
      lcd.setCursor(24, 1);
      lcd.print(" blok3"); 
      break;
    case 3:
      lcd.setCursor(0, 1);
      lcd.print("    izvelies");
      lcd.setCursor(16, 1);
      lcd.print(" blok1  | blok 4");
      lcd.setCursor(8, 1);
      lcd.print(" blok2  | blok 5");
      lcd.setCursor(24, 1);
      lcd.print(">blok3");
      break;
    case 4:
      lcd.setCursor(0, 1);
      lcd.print("    izvelies");
      lcd.setCursor(16, 1);
      lcd.print(" blok1  |>blok 4");
      lcd.setCursor(8, 1);
      lcd.print(" blok2  | blok 5");
      lcd.setCursor(24, 1);
      lcd.print(" blok3");
      break;
    case 5:
      lcd.setCursor(0, 1);
      lcd.print("    izvelies");
      lcd.setCursor(16, 1);
      lcd.print(" blok1  | blok 4");
      lcd.setCursor(8, 1);
      lcd.print(" blok2  |>blok 5");
      lcd.setCursor(24, 1);
      lcd.print(" blok3");
      break;
  }
  delay(250);
  menu = 1;
  Menu();
}

void Menu(){
  Serial.print(menu);
  switch (menu){
    RGB_color(255, 255, 0);
    delay(50);
    RGB_color(255, 0, 255);
    case 0:
      menu = 1;
      break;
    case 1:
      DisplayDigit(1);
      lcd.setCursor(0, 1);
      lcd.print(">");
      lcd.setCursor(16, 1);
      lcd.print(" ");
      break;
    case 2:
      DisplayDigit(2);
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(16, 1);
      lcd.print(">");
      lcd.setCursor(8, 1);
      lcd.print(" ");
      break;
    case 3:
      DisplayDigit(3);
      lcd.setCursor(16, 1);
      lcd.print(" ");
      lcd.setCursor(8, 1);
      lcd.print(">");
      lcd.setCursor(24, 1);
      lcd.print(" ");
      break;
    case 4:
      DisplayDigit(4);
      lcd.setCursor(0, 1);
      lcd.print(" Servo  | ");
      lcd.setCursor(8, 1);
      lcd.print(" ");
      lcd.setCursor(24, 1);
      lcd.print(">");
      break;
    case 5:
      DisplayDigit(5);
      lcd.setCursor(0, 1);
      lcd.print(" Servo  |>");
      lcd.setCursor(16, 1);
      lcd.print(" remote | ");
      lcd.setCursor(24, 1);
      lcd.print(" ");
      break;
    case 6:
      DisplayDigit(6);
      lcd.setCursor(0, 1);
      lcd.print(" Servo  | ");
      lcd.setCursor(16, 1);
      lcd.print(" remote |>");
      lcd.setCursor(8, 1);
      lcd.print(" MakePin| ");
      break;
    case 7:
      DisplayDigit(7);
      lcd.setCursor(16, 1);
      lcd.print(" remote | ");
      lcd.setCursor(8, 1);
      lcd.print(" MakePin|>");
      lcd.setCursor(24, 1);
      lcd.print(" MadePid| ");
      break;
      
    case 8:
      DisplayDigit(8);
      lcd.setCursor(8, 1);
      lcd.print(" MakePin| ");
      lcd.setCursor(24, 1);
      lcd.print(" MadePid|>");
      break;
      
  }
  delay(200);
  menu = 1;
}

void RGB_color(int LedRv, int LedGv, int LedBv){
  analogWrite(LedR, LedRv);
  analogWrite(LedG, LedGv);
  analogWrite(LedB, LedBv);
}

void DisplayDigit(int Digit){
  digitalWrite(STCP_pin, LOW);
  for (int i = 7; i>=0; i--){
    digitalWrite(SHCP_pin, LOW);
    if (digits[Digit][i]==1) digitalWrite(DS_pin, LOW);
    if (digits[Digit][i]==0) digitalWrite(DS_pin, HIGH);
    digitalWrite(SHCP_pin, HIGH);
  }
  digitalWrite(STCP_pin, HIGH);
}

void witch(){
  //cp1, cp2, pl, q[l], q[2], q[3], q[6], q[7], q[8]
    lcd.clear();
    lcd.print(cp1);
    if(q[1] == 1){
      lcd.print(" + ");}
    else if(q[1] == 2){
      lcd.print(" - ");}
    else if(q[1] == 3){
      lcd.print(" * ");}
    else if(q[1] == 4){
      lcd.print(" / ");}
    lcd.print(cp2);
    lcd.print(" = ?");
    lcd.setCursor(16, 1);
    if (q[3] == 0 and q[2] == 0){
      q[8] = 1;
      lcd.print(">");
      lcd.print(pl);
      lcd.print("  ");
      lcd.print(q[6]);
      lcd.print("  ");
      lcd.print(q[7]);
    }else if (q[3] == 1 and q[2] == 0){
      q[8] = 0;
      lcd.print(">");
      lcd.print(q[6]);
      lcd.print("  ");
      lcd.print(pl);
      lcd.print("  ");
      lcd.print(q[7]);
    }else if (q[3] == 2 and q[2] == 0){
      q[8] = 0;
      lcd.print(">");
      lcd.print(q[6]);
      lcd.print("  ");
      lcd.print(q[7]);
      lcd.print("  ");
      lcd.print(pl);
    }


    else if (q[3] == 0 and q[2] == 1){
      q[8] = 0;
      lcd.print(" ");
      lcd.print(pl);
      lcd.print(" >");
      lcd.print(q[6]);
      lcd.print("  "); 
      lcd.print(q[7]);
    }else if (q[3] == 1 and q[2] == 1){
      q[8] = 1;
      lcd.print(" ");
      lcd.print(q[6]);
      lcd.print(" >");
      lcd.print(pl);
      lcd.print("  ");
      lcd.print(q[7]);
    }else if (q[3] == 2 and q[2] == 1){
      q[8] = 0;
      lcd.print(" ");
      lcd.print(q[6]);
      lcd.print(" >");
      lcd.print(q[7]);
      lcd.print("  ");
      lcd.print(pl);
    }


    else if (q[3] == 0 and q[2] == 2){
      q[8] = 0;
      lcd.print(" ");
      lcd.print(pl);
      lcd.print("  ");
      lcd.print(q[6]);
      lcd.print(" >");
      lcd.print(q[7]);
    }else if (q[3] == 1 and q[2] == 2){
      q[8] = 0;
      lcd.print(" ");
      lcd.print(q[6]);
      lcd.print("  ");
      lcd.print(pl);
      lcd.print(" >");
      lcd.print(q[7]);
    }else if (q[3] == 2 and q[2] == 2){
      q[8] = 1;
      lcd.print(" ");
      lcd.print(q[6]);
      lcd.print("  ");
      lcd.print(q[7]);
      lcd.print(" >");
      lcd.print(pl);
    }

    delay(300);
}

void burts(){
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(bin[1]);
  gg = 1 + (bin[3] - 1) + ((bin[2] - 1) * 5) + ((bin[1] - 1) * 21);
  if(bin[0] == 1){
    gg = gg + 22;
    }
  lcd.print(bin[1]);
  lcd.setCursor(16, 1);
  lcd.print(bin[0]);
  lcd.print(bin[1]);
  lcd.print(bin[2]);
  lcd.print(bin[3]);
  lcd.setCursor(8, 1);
  if (bin[4] == 1){ lcd.clear(); lcd.print("^");}
  else if (bin[4] == 2){ lcd.clear(); lcd.print(" ^");}
  else if (bin[4] == 3){ lcd.clear(); lcd.print("  ^");}
  else if (bin[4] == 4){ lcd.clear(); lcd.print("   ^");}
  delay(250);
  exit;
}
