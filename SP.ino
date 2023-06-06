#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <IRremote.h>

Servo myservo;

uint8_t EEPROMadress = 130;
uint8_t EEPROMadress2 = 131;
uint8_t EEPROMadress3 = 132;
int but = 8;
int but2 = 9;
int but3 = 10;
int but4 = 11;
int but5 = 12;

uint8_t txt1 = 133;
uint8_t txt2 = 134;
uint8_t txt3 = 135;
uint8_t txt4 = 136;
uint8_t txt5 = 137;

long cp1;
long cp2;
long pl;
int menu = 1;
float pos = 90;
float x = 0;
float y = 0;
int q[8] = {0, 1, 0, 0,   0, 0, 0};
int gg = 1;
int DS_pin = 4;
int STCP_pin = 3;
int SHCP_pin = 2;
int numb = 1;
int pin2 = 1;
int how[2] = {0, 5};
String ana = "mt"; 
String prn = "none";
int bin[5] = {1, 1, 1, 1, 0};
String str = "l";
String alfa[53] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","r","s","t","u","v","z",
"ā","#","č","#","ē","#","ģ","ī","#","ķ","ļ","#","ņ","#","#","#","š","#","ū","#","ž","#",
"1","2","3","4","5","6","7","8","9"};


IRrecv IR(A0);

LiquidCrystal_I2C lcd(0x27, 16, 4);
void setup() {
  lcd.begin(16, 4);
  lcd.setCursor(0, 1);
  
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  
  pinMode(but, INPUT);
////////////////////////////////

  RGB_color(0, 255, 255); 
  //delay(5000);
  RGB_color(255, 0, 255);

  delay(18800);
  Menu();
////////////////////////////////
  myservo.attach(13);
  digitalWrite(SHCP_pin, HIGH);
  digitalWrite(A7, LOW);

  IR.enableIRIn();

  Serial.begin(9600);
  x = EEPROM.read(EEPROMadress);
  y = EEPROM.read(EEPROMadress2);
}


void loop() {
    if (digitalRead(but) != 0) {
      lcd.clear(); 
      thing();
    }
    if (digitalRead(but3) != 0) {
      if (menu == 1){
      Serial.println("Can't go lower");
      }else {
      menu--;
      Menu();
      }
    }
    if (digitalRead(but2) != 0) {
       if (menu == 8){
      Serial.println("Can't go highir");
      }else {
      menu++;
      Menu();
      }
    }

}
  
void thing(){
  numb = 1;
  lcd.clear();
  while (digitalRead(but2) == 0){
    if (menu == 1){
      lcd.clear();
      lcd.print("use ^v to rotate");
       while (digitalRead(but2) == 0){
         if (digitalRead(but5) != 0){
          if (pos > 179.9){
          } else {
            pos += 0.4;
            numb += 1;
            DisplayDigit(numb);
          } 
         }
         if (digitalRead(but4) != 0){
          if (pos < 0.1){
          } else {
            pos -= 0.4;
            numb -= 1;
            DisplayDigit(numb);
          }
         }
         if (digitalRead(but) != 0 and gg == 1){
          x = pos;
          pos = 90;
          gg = 2;
          RGB_color(0, 255, 255);
          delay(50);
          RGB_color(255, 0, 255);
          while (digitalRead(but) != 0){
          } exit;
         }else if (digitalRead(but) != 0 and gg == 2){
          y = pos;
          pos = 90;
          gg = 1;
          RGB_color(0, 255, 255);
          delay(50);
          RGB_color(255, 0, 255);
          while (digitalRead(but) != 0){
          } exit;
         }
         myservo.write(pos);
         delay(10);
       }
       EEPROM.write(EEPROMadress2, y);
       EEPROM.write(EEPROMadress, x);
       Serial.println("lol");
    }else if (menu == 2){
      lcd.clear();
      lcd.print("use IR remote");
      while (digitalRead(but2) == 0){
        if (IR.decode()){
          Serial.println(IR.decodedIRData.decodedRawData, HEX);
          if (IR.decodedIRData.decodedRawData == 0xE718FF00){
            pos += 5;
            RGB_color(0, 255, 255);
            delay(20);
            RGB_color(255, 0, 255);
          }
          if (IR.decodedIRData.decodedRawData == 0xAD52FF00){
            pos -= 5;
            RGB_color(0, 255, 255);
            delay(20);
            RGB_color(255, 0, 255);
          }
          if (IR.decodedIRData.decodedRawData == 0xBA45FF00){
            pos = y;
            RGB_color(0, 255, 255);
            delay(50);
            RGB_color(255, 0, 255);
          }
          if (IR.decodedIRData.decodedRawData == 0xBB44FF00){
            pos = x;
            RGB_color(0, 255, 255);
            delay(50);
            RGB_color(255, 0, 255);
          }
          IR.resume();
          myservo.write(pos);
        }
      }
      
    }else if (menu == 3){
      lcd.clear();
      lcd.print("use ^v how to activise pin");
      RGB_color(255, 255, 0);
      delay(3000);
      RGB_color(255, 0, 255);
      lcd.clear();
      lcd.print("IR remote");
      while (digitalRead(but2) == 0){
        if(digitalRead(but4) != 0 and how[0] < 3){
            how[0] ++;
            lcd.clear();
            if(how[0] == 1){
              lcd.print("IR remote");
            }else if(how[0] == 2){
              lcd.print("Time");
            }else if(how[0] == 3){
              lcd.print("Button");
            }else if(how[0] == 4) lcd.print("Button");
            delay(300);
        }else if(digitalRead(but5) != 0 and how[0] > 1){
          how[0] --;
          if(how[0] == 1){
            lcd.clear();
            lcd.print("IR remote");
          }else if(how[0] == 2){
            lcd.clear();
            lcd.print("Time");
          }else if(how[0] == 3){
            lcd.clear();
            lcd.print("Button");
          }
          delay(300);
        }else if(digitalRead(but) != 0){
          while (digitalRead(but2) == 0){
            lcd.clear();
            if(how[0] == 1); lcd.print("IR remote");
            if(how[0] == 2){
              lcd.print("Time");
              while (digitalRead(but2) == 0){
                if(digitalRead(but4) != 0){
                  how[1] += 1;
                  lcd.clear();
                  lcd.setCursor(16, 1);
                  lcd.print(how[1]);
                }else if(digitalRead(but5) != 0){
                  if(how[1] != 1){
                    how[1] -= 1;
                    lcd.clear();
                    lcd.print(how[1]);
                  }
                }else if(digitalRead(but) != 0){
                  lcd.print("Ok. Done");
                  delay(1000);
                }
              }
            }else if(how[0] == 3); lcd.print("Button");
            lcd.setCursor(0, 1);
            lcd.print("Pin - A6");
            while (digitalRead(but5) != 0){
              if(digitalRead(but4) != 0){
                if(pin2 == 0){
                  lcd.setCursor(16, 1);
                  lcd.clear();
                  pin2 = 1;
                  lcd.print("but'>'");
                }
              }else if(digitalRead(but5) != 0){
                if(pin2 == 1){
                  lcd.clear();
                  pin2 = 0;
                  lcd.print("but'<'");
                }
              }
            }
            while (digitalRead(but2) == 0){}exit;
            while (digitalRead(but2) == 0){
              if(digitalRead(but4) != 0){
                lcd.clear();
                ana = "analog";
                else if(digitalRead(but5) != 0){
                lcd.clear();
                ana = "digital";
                lcd.print(ana);
              }else if(digitalRead(but) != 0){
                while (digitalRead(but2) == 0){}
              }
            }
          }
        }
      }
    }else if (menu == 4){
      lcd.print("pin: "); lcd.print(" ;  activision: ");
      if(how[0] == 1){
        lcd.print("IR remote ; ");
      }else if (how[0] == 2) {
        lcd.print("Time ; ");
        lcd.print(how[1]);
      }else if(how[0] == 3){
        lcd.print("Button ; ");}
      lcd.print(ana);
      lcd.println("are its true???");
      delay(2000);
      lcd.clear();
      lcd.print("< = YES");
      lcd.setCursor(0, 16);
      lcd.print("> = NO");
      while(digitalRead(but2) == 0){
        if(digitalRead(but4) != 0){
          lcd.clear();
          lcd.print("ok");
          delay(1000);
        }else if(digitalRead(but5) != 0){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print(" Servo  | Game");
          lcd.setCursor(16, 1);
          lcd.print(" remote | blokn.");
          lcd.setCursor(8, 1);
          lcd.print(" MakePin| ");
          lcd.setCursor(24, 1);
          lcd.print(">MadePid| ");
          delay(1000);
          lcd.setCursor(8, 1);
          lcd.print(">");
          lcd.setCursor(24, 1);
          lcd.print(" ");
          delay(1000);
          menu = 3;
          thing();
        }
        while(digitalRead(but2) == 0){
          if(how[0] == 1){
            while(digitalRead(but2) == 0){
              if(IR.decodedIRData.decodedRawData == 0xE718FF00){
                digitalWrite(A7, HIGH);
                exit;
              }
            }
          }else if(how[0] == 2){
            while(digitalRead(but2) == 0){
              lcd.print(how[1]);
              delay(1000);
              how[1] = how[1] - 1;
              if(how[1] == -1);exit;
            }
            digitalWrite(A7, HIGH);
          }else if(how[0] == 3){
            while(digitalRead(but2) == 0){
              if(digitalRead(but5) != 0){
                digitalWrite(A7, HIGH);
              }
            }
          }
        }
      }
    }else if (menu == 5){
      while (digitalRead(but2) == 0){
        lcd.clear();
        lcd.print("GAME");
        delay(1500);
        lcd.clear();
        lcd.print("Press OK to start");
        while(digitalRead(but) == 0){}
          lcd.setCursor(0, 0);
          while (digitalRead(but2) == 0){
          lcd.clear();
          q[4] = 50;
          q[2] = 0;
          q[8] = 8;
          q[1] = random(1, 4);
          q[3] = random(1, 3);
          cp1 = random(100);
          cp2 = random(100);
          q[6] = random(-20, 100);
          q[7] = random(-20, 100);
          lcd.setCursor(0, 1);
          if(q[1] == 1){
            pl = cp1 + cp2;}
          else if(q[1] == 2){
            pl = cp1 - cp2;}
          else if(q[1] == 3){
            pl = cp1 * cp2;
            q[6] = random(0, 1000);
            q[7] = random(0, 1000);}
          else if(q[1] == 4){
            pl = cp1 / cp2;
          }
          witch();

//pl = pareizais rezultāts
//q[1] = random +-*
//q[2] = wich place
//q[3] = the random vhere is
//q[4] = laiks
          
          while (q[4] != 0){
            if (digitalRead(but4) != 0){
              if (q[2] != 0){
                q[2] = q[2] - 1;
                witch();
              }
             } else if (digitalRead(but5) != 0){
                if (q[2] != 2){
                  q[2] = q[2] + 1;
                  witch();
                }
              }
              else if (digitalRead(but) != 0){
              if(q[8] == 1){
                lcd.clear();
                lcd.print("   RIGHT!!!");
                q[8] = 10;
                delay(1000);
              }else{
                lcd.clear();
                lcd.print("   wrong!");
                q[8] = 10;
                delay(1000);
              }exit;
            }
              q[4] -= 1;
              delay(50);
          }
          if (q[8] != 10){
          lcd.clear();
          lcd.print("you're ded");
          delay(1000);}
        }
      } 
    }
    else if (menu == 6){
      bloknots();
      while(digitalRead(but2) == 0){
        if (digitalRead(but4) != 0){
          if (gg != 1){
            gg = gg - 1;
            bloknots();
          }
        }if (digitalRead(but5) != 0){
          if (gg != 5){
            gg = gg + 1;
            bloknots();
          }
        }
        if (digitalRead(but) != 0){
          burts();
          while (digitalRead(but2) == 0){
            if (digitalRead(but4) != 0){
              if (bin[4] != 1){
              bin[4] --;}
            }if (digitalRead(but5) != 0){
              if (bin[4] != 4){
              bin[4] ++;}
            }if (digitalRead(but) != 0){
              EEPROM.write(EEPROMadress3, bin[4]);
              str = txt1 + alfa[bin[4]];
              lcd.print(str);
            }
          }
        }
      }
    }
  }
  menu = 1;
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Servo  | Game");
  lcd.setCursor(16, 1);
  lcd.print(" remote | blokn.");
  lcd.setCursor(8, 1);
  lcd.print(" MakePin| ");
  lcd.setCursor(24, 1);
  lcd.print(" MadePid| ");
  exit;
}

void burts(){
  Serial.write(4);
  delay(20);
  Serial.write(bin[0]);
  delay(20);
  Serial.write(bin[1]);
  delay(20);
  Serial.write(bin[2]);
  delay(20);
  Serial.write(bin[3]);
  delay(20);
  Serial.write(bin[4]);
}

void bloknots(){
  Serial.write(1);
  delay(25);
  Serial.write(gg);
  delay(250);
}

void Menu(){
  Serial.write(2);
  delay(25);
  Serial.write(menu);
  delay(200);
}

//--------------------------------------------------------------------------------------------------

public void RGB_color(int LedRv, int LedGv, int LedBv){
  Serial.write(2000000000 + (LedRv * 1000000) + (LedGv * 1000) + LedBv);
}

void DisplayDigit(int Digit){
  Serial.write(10 + Digit);
}

void witch(){
    Serial.write(3);
    delay(20);
    Serial.write(cp1);
    delay(20);
    Serial.write(cp2);
    delay(20);
    Serial.write(pl);
    delay(20);
    Serial.write(q[1]);
    delay(20);
    Serial.write(q[2]);
    delay(20);
    Serial.write(q[3]);
    delay(20);
    Serial.write(q[6]);
    delay(20);
    Serial.write(q[7]);
    delay(20);
    Serial.write(q[8]);
    delay(300);
}
