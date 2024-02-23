#include <LiquidCrystal_I2C.h>
#include <pitches.h>

const byte ADDRESS = 0x38;
const byte LCD_H = 4;
const byte LCD_W = 20;

LiquidCrystal_I2C lcd(ADDRESS, LCD_W, LCD_H);

const byte BUTTON_R = 2;
const byte BUTTON_L = 3;
const byte BUTTON_UP = 4;
const byte BUTTON_DOWN = 5;
const byte BUTTON_Rp2 = 12;
const byte BUTTON_Lp2 = 6;
const byte BUTTON_UPp2 = 13;
const byte BUTTON_DOWNp2 = 7;

int twoplayergame = 0;
int player_x = 0;
int player_y = 0;
int player_xp2 = 0;
int player_yp2 = 1;
float enemy_xf = 10;
float enemy_yf = 0;
int enemy_x = 10;
int enemy_y = 0;
float enemy_xfp2 = 10;
float enemy_yfp2 = 0;
int enemy_xp2 = 10;
int enemy_yp2 = 0;
int menu_x;
int selector_m;
int game_started = 0;
uint8_t enemy_img = 0;
uint8_t pacman_img = 0;
int scorep2;
const float speed = 0.25;
int randNumberx;
int randNumbery;
int foodExists;
int score;
int scoresave;
int scoresavep2;


const int death[] = { 17,
                      NOTE_C4, 32, NOTE_CS4, 32, NOTE_D4, 16, NOTE_H, 4, NOTE_H, 2, NOTE_B3, 8, NOTE_F4, 8, NOTE_H, 8, NOTE_F4, 8, NOTE_F4, 6,
                      NOTE_E4, 6, NOTE_D4, 6, NOTE_C4, 8, NOTE_E3, 8, NOTE_H, 8, NOTE_E3, 8, NOTE_C3, 8 };

const int flagpole[] = { 27,
                         NOTE_G2, 10, NOTE_C3, 10, NOTE_E3, 10, NOTE_G3, 10, NOTE_C4, 10, NOTE_E4, 10, NOTE_G4, 3, NOTE_E4, 3, NOTE_GS2, 10, NOTE_C3, 10,
                         NOTE_DS3, 10, NOTE_GS3, 10, NOTE_C4, 10, NOTE_DS4, 10, NOTE_GS4, 3, NOTE_DS4, 3, NOTE_AS2, 10, NOTE_D3, 10, NOTE_F3, 10,
                         NOTE_AS3, 10, NOTE_D4, 10, NOTE_F4, 10, NOTE_AS4, 3, NOTE_B4, 10, NOTE_B4, 10, NOTE_B4, 10, NOTE_C5, 2 };


byte downpac[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b11101,
  0b11011,
  0b10001,
  0b00000,
  0b00000
};

byte downclosed[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b11101,
  0b11111,
  0b11111,
  0b01110,
  0b00000
};

byte uppac[8] = {
  0b00000,
  0b00000,
  0b10001,
  0b11011,
  0b10111,
  0b01110,
  0b00000,
  0b00000
};

byte upclosed[8] = {
  0b00000,
  0b01110,
  0b11111,
  0b11111,
  0b10111,
  0b01110,
  0b00000,
  0b00000
};

byte rightpac[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10100,
  0b11000,
  0b01100,
  0b01110,
  0b00000
};

byte rightclosed[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10111,
  0b11111,
  0b01110,
  0b01110,
  0b00000
};

byte leftpac[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b00101,
  0b00011,
  0b00110,
  0b01110,
  0b00000
};

byte leftclosed[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10111,
  0b11111,
  0b01110,
  0b01110,
  0b00000
};

byte enemy[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b10101,
  0b11111,
  0b01010,
  0b10001
};

byte enemyanim[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b10101,
  0b11111,
  0b01010,
  0b01010
};


byte food[8] = {
  0b00001,
  0b00010,
  0b00100,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01110
};

byte door[8] = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b10001,
  0b10001,
  0b11111
};

void foodgen() {
  if (foodExists == 0) {
    randNumberx = random(1, 20);
    randNumbery = random(1, 3);
  }
  if (foodExists == 1) {
  }
  foodExists = 1;
}

void upsound() {
  tone(8, NOTE_E6, 125);
  delay(130);
  tone(8, NOTE_G6, 125);
  delay(130);
  tone(8, NOTE_E6, 125);
  delay(130);
  tone(8, NOTE_G6, 125);
  delay(130);
  tone(8, NOTE_E7, 125);
  delay(130);
  tone(8, NOTE_C7, 125);
  delay(130);
  tone(8, NOTE_D7, 125);
  delay(130);
  tone(8, NOTE_G7, 125);
  delay(125);
  noTone(8);
  tone(8, NOTE_E7, 125);
  delay(130);
  tone(8, NOTE_C7, 125);
  delay(130);
  tone(8, NOTE_D7, 125);
  delay(130);
  tone(8, NOTE_G7, 125);
  delay(125);
  noTone(8);
}

void deathsound() {
  for (int thisNote = 1; thisNote < (death[0] * 2 + 1); thisNote = thisNote + 2) {
    tone(8, death[thisNote], (1000 / death[thisNote + 1]));
    delay((1000 / death[thisNote + 1]) * 1.30);
    noTone(8);
  }
}

void winsound() {

  for (int thisNote = 1; thisNote < (flagpole[0] * 2 + 1); thisNote = thisNote + 2) {
    tone(8, flagpole[thisNote], (1000 / flagpole[thisNote + 1]));
    delay((1000 / flagpole[thisNote + 1]) * 1.30);
    noTone(8);
  }
}

void eatsound() {
  tone(8, NOTE_B5, 100);
  delay(100);
  tone(8, NOTE_E6, 850);
  delay(400);
  noTone(8);
}

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(BUTTON_R, INPUT_PULLUP);
  pinMode(BUTTON_L, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_Rp2, INPUT_PULLUP);
  pinMode(BUTTON_Lp2, INPUT_PULLUP);
  pinMode(BUTTON_UPp2, INPUT_PULLUP);
  pinMode(BUTTON_DOWNp2, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
}



void loop() {
  if (game_started == 0) {

    if (digitalRead(BUTTON_UP) == LOW) {
      menu_x++;
    }
    if (digitalRead(BUTTON_DOWN) == LOW) {
      menu_x--;
    }
    if (menu_x >= 4) {
      menu_x = 3;
    }
    if (menu_x <= 0) {
      menu_x = 1;
    }

    if (menu_x == 1) {
      lcd.setCursor(4, 0);
      lcd.print("Snakeman  v3");
      lcd.setCursor(4, 1);
      lcd.print("> START!");
      lcd.setCursor(4, 2);
      lcd.print("  SCOREBOARD");
      lcd.setCursor(4, 3);
      lcd.print("  About");
      if (digitalRead(BUTTON_R) == LOW) {

        lcd.clear();
        delay(20);
        selector();
      }
    }

    if (menu_x == 2) {

      lcd.setCursor(4, 0);
      lcd.print("Snakeman  v3");
      lcd.setCursor(4, 1);
      lcd.print("  START!");
      lcd.setCursor(4, 2);
      lcd.print("> SCOREBOARD");
      lcd.setCursor(4, 3);
      lcd.print("  About");
      if (digitalRead(BUTTON_R) == LOW) {
        lcd.clear();
        scoreboard();
      }
    }
    if (menu_x == 3) {

      lcd.setCursor(4, 0);
      lcd.print("Snakeman  v3");
      lcd.setCursor(4, 1);
      lcd.print("  START!");
      lcd.setCursor(4, 2);
      lcd.print("  SCOREBOARD");
      lcd.setCursor(4, 3);
      lcd.print("> Abort");
      if (digitalRead(BUTTON_R) == LOW) {
        lcd.clear();
        about();
      }
    }
  } else {
    game();
  }
}

void about() {
  while (1) {
    lcd.setCursor(4, 1);
    lcd.print("Snakeman  v3");
    lcd.setCursor(2, 2);
    lcd.print("by LeX04 and Out");
    lcd.setCursor(0, 3);
    lcd.print("Now With Multiplayer");
    if (digitalRead(BUTTON_L) == LOW) {
      lcd.clear();
      break;
    }
  }
}

void scoreboard() {
  while (1) {
    lcd.setCursor(5, 0);
    lcd.print("SCOREBOARD");
    lcd.setCursor(0, 1);
    lcd.print("PLAYER 1 BEST - ");
    lcd.print(scoresave);
    lcd.setCursor(0, 2);
    lcd.print("PLAYER 2 BEST - ");
    lcd.print(scoresavep2);
    if (digitalRead(BUTTON_L) == LOW) {
      lcd.clear();
      break;
    }
  }
}

void selector() {
  while (1) {

    if (digitalRead(BUTTON_UP) == LOW) {
      selector_m++;
    }
    if (digitalRead(BUTTON_DOWN) == LOW) {
      selector_m--;
    }
    if (selector_m >= 3) {
      selector_m = 2;
    }
    if (selector_m <= 0) {
      selector_m = 1;
    }
    if (selector_m == 1) {
      lcd.setCursor(2, 0);
      lcd.print("How Many Players");
      lcd.setCursor(3, 1);
      lcd.print("> 1 Player");
      lcd.setCursor(3, 2);
      lcd.print("  2 Players");
      if (digitalRead(BUTTON_R) == LOW) {
        game_started = 1;
        twoplayergame = 0;
        lcd.clear();
        game();
        break;
      }
      if (digitalRead(BUTTON_L) == LOW) {
        lcd.clear();
        break;
      }
    }
    if (selector_m == 2) {

      lcd.setCursor(2, 0);
      lcd.print("How Many Players");
      lcd.setCursor(3, 1);
      lcd.print("  1 Player");
      lcd.setCursor(3, 2);
      lcd.print("> 2 Players");
      if (digitalRead(BUTTON_R) == LOW) {
        twoplayergame = 1;
        game_started = 1;
        lcd.clear();
        game();
        break;
      }
      if (digitalRead(BUTTON_L) == LOW) {
        lcd.clear();
        break;
      }
    }
  }
}

void game() {
  game_started = 1;
  foodgen();
  if (digitalRead(BUTTON_R) == LOW) {
    lcd.createChar(0, rightpac);
    lcd.createChar(1, rightclosed);
    player_x = player_x + 1;
  }
  if (digitalRead(BUTTON_L) == LOW) {
    lcd.createChar(0, leftpac);
    lcd.createChar(1, leftclosed);
    player_x = player_x - 1;
  }
  if (digitalRead(BUTTON_UP) == LOW) {
    lcd.createChar(0, downpac);
    lcd.createChar(1, downclosed);
    player_y = player_y + 1;
  }
  if (digitalRead(BUTTON_DOWN) == LOW) {
    lcd.createChar(0, uppac);
    lcd.createChar(1, upclosed);
    player_y = player_y - 1;
  }


  if (digitalRead(BUTTON_Rp2) == LOW) {
    lcd.createChar(0, rightpac);
    lcd.createChar(1, rightclosed);
    player_xp2 = player_xp2 + 1;
  }
  if (digitalRead(BUTTON_Lp2) == LOW) {
    lcd.createChar(0, leftpac);
    lcd.createChar(1, leftclosed);
    player_xp2 = player_xp2 - 1;
  }
  if (digitalRead(BUTTON_UPp2) == LOW) {
    lcd.createChar(0, downpac);
    lcd.createChar(1, downclosed);
    player_yp2 = player_yp2 + 1;
  }
  if (digitalRead(BUTTON_DOWNp2) == LOW) {
    lcd.createChar(0, uppac);
    lcd.createChar(1, upclosed);
    player_yp2 = player_yp2 - 1;
  }


  float dir_x = player_x - enemy_x;
  float dir_y = player_y - enemy_y;
  float hyp = sqrt(dir_x * dir_x + dir_y * dir_y);
  dir_x /= hyp;
  dir_y /= hyp;
  enemy_xf += dir_x * speed;
  enemy_yf += dir_y * speed;
  enemy_x = enemy_xf;
  enemy_y = enemy_yf;

  if (twoplayergame == 1) {
    float dir_xp2 = player_xp2 - enemy_xp2;
    float dir_yp2 = player_yp2 - enemy_yp2;
    float hypp2 = sqrt(dir_xp2 * dir_xp2 + dir_yp2 * dir_yp2);
    dir_xp2 /= hypp2;
    dir_yp2 /= hypp2;
    enemy_xfp2 += dir_xp2 * speed;
    enemy_yfp2 += dir_yp2 * speed;
    enemy_xp2 = enemy_xfp2;
    enemy_yp2 = enemy_yfp2;
  }

  pacman_img = random(0, 2);
  lcd.createChar(6, enemy);
  lcd.createChar(5, enemyanim);
  enemy_img = random(5, 7);
  lcd.createChar(2, food);
  lcd.createChar(3, door);
  lcd.setCursor(18, 3);
  lcd.write((uint8_t)3);
  lcd.setCursor(player_x, player_y);
  lcd.write((uint8_t)pacman_img);
  if (twoplayergame == 1) {
    lcd.setCursor(player_xp2, player_yp2);
    lcd.write((uint8_t)10);
  }

  lcd.setCursor(enemy_x, enemy_y);
  lcd.write((uint8_t)enemy_img);
  if (twoplayergame == 1) {
    lcd.setCursor(enemy_xp2, enemy_yp2);
    lcd.write((uint8_t)11);
  }

  lcd.setCursor(randNumberx, randNumbery);
  lcd.write((uint8_t)2);
  lcd.setCursor(0, 10);
  lcd.print("P1: ");
  lcd.print(score);
  if (twoplayergame == 1) {
    lcd.setCursor(5, 10);
    lcd.print(" P2: ");
    lcd.print(scorep2);
  }
  delay(120);
  lcd.clear();

  if (player_x >= 20) {
    player_x = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_x = 0;
    player_y = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_x = 0;
    player_y = 0;

    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_xp2 >= 20) {
    player_xp2 = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_xp2 = 0;
    player_yp2 = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_xp2 = 0;
    player_yp2 = 0;

    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_y >= 4) {
    player_y = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_x = 0;
    player_y = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_x = 0;
    player_y = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_yp2 >= 4) {
    player_yp2 = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_xp2 = 0;
    player_yp2 = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_x <= -1) {
    player_x = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_x = 0;
    player_y = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_x = 0;
    player_y = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_xp2 <= -1) {
    player_xp2 = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_xp2 = 0;
    player_yp2 = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }


  if (player_y <= -1) {
    player_y = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_x = 0;
    player_y = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_x = 0;
    player_y = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    scorep2 = 0;
    score = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_yp2 <= -1) {
    player_yp2 = 0;
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("You touched a wall!!");
    lcd.setCursor(0, 1);
    lcd.print("Game Over!");
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    deathsound();
    player_xp2 = 0;
    player_yp2 = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    score = 0;
    scorep2 = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_x == randNumberx && player_y == randNumbery) {
    delay(150);
    lcd.setCursor(12, 3);
    lcd.print("+1 Fruit");
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    lcd.setCursor(0, 10);
    lcd.print("P1: ");
    lcd.print(score);
    if (twoplayergame == 1) {
      lcd.setCursor(5, 10);
      lcd.print(" P2: ");
      lcd.print(scorep2);
    }
    delay(150);
    foodExists = 0;
    score++;
    eatsound();
  }

  if (player_xp2 == randNumberx && player_yp2 == randNumbery) {
    delay(150);
    lcd.setCursor(12, 3);
    lcd.print("+1 Fruit");
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    lcd.setCursor(0, 10);
    lcd.print("P1: ");
    lcd.print(score);
    if (twoplayergame == 1) {
      lcd.setCursor(5, 10);
      lcd.print(" P2: ");
      lcd.print(scorep2);
    }
    delay(150);
    foodExists = 0;
    scorep2++;
    eatsound();
  }

  if (player_x == 0 && player_y == 3) {
    lcd.setCursor(0, 2);
    digitalWrite(9, HIGH);
    delay(250);
    digitalWrite(9, LOW);
    delay(250);
    digitalWrite(11, HIGH);
    delay(250);
    digitalWrite(11, LOW);
    delay(250);
    lcd.print("A SECRET IS REVEALED");
    delay(50);
    lcd.clear();
    delay(50);
    lcd.print("A SECRET IS REVEALED");
    delay(50);
    lcd.clear();
    delay(50);
    lcd.print("A SECRET IS REVEALED");
    delay(50);
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 10);
    lcd.print("SCORE: ");
    lcd.print(score);

    score = score + 50;
    upsound();
    player_x = 0;
    player_y = 0;
  }

  if (player_xp2 == 0 && player_yp2 == 3) {
    lcd.setCursor(0, 2);
    digitalWrite(9, HIGH);
    delay(250);
    digitalWrite(9, LOW);
    delay(250);
    digitalWrite(11, HIGH);
    delay(250);
    digitalWrite(11, LOW);
    delay(250);
    lcd.print("A SECRET IS REVEALED");
    delay(50);
    lcd.clear();
    delay(50);
    lcd.print("A SECRET IS REVEALED");
    delay(50);
    lcd.clear();
    delay(50);
    lcd.print("A SECRET IS REVEALED");
    delay(50);
    lcd.clear();
    delay(50);
    lcd.setCursor(0, 10);
    lcd.print("SCORE: ");
    lcd.print(scorep2);

    scorep2 = scorep2 + 50;
    upsound();
    player_xp2 = 0;
    player_yp2 = 0;
  }

  if (player_x == 18 && player_y == 3) {

    game_started = 0;
    player_x = 0;
    player_y = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    score = 0;
    scorep2 = 0;
  }

  if (player_xp2 == 18 && player_yp2 == 3) {

    game_started = 0;
    player_x = 0;
    player_y = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    score = 0;
    scorep2 = 0;
  }

  if (score >= 50) {
    lcd.clear();
    delay(150);
    lcd.setCursor(0, 0);
    lcd.print("YOUR SCORE WAS - ");
    lcd.print(score);
    lcd.setCursor(6, 1);
    lcd.print("You Win!");
    game_started = 0;
    player_x = 0;
    player_y = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    score = 0;
    scorep2 = 0;
    winsound();
    delay(2000);
    lcd.clear();
  }

  if (player_x == enemy_x && player_y == enemy_y) {
    delay(150);
    lcd.setCursor(0, 0);
    lcd.print("P1 SCORE - ");
    lcd.print(score);
    lcd.setCursor(0, 2);
    lcd.print("P1 WAS HIT");

    if (twoplayergame == 1) {
      lcd.setCursor(0, 1);
      lcd.print("P2 SCORE - ");
      lcd.print(scorep2);
    }
    lcd.setCursor(0, 3);
    lcd.print("You Were eaten");
    lcd.setCursor(0, 10);
    deathsound();
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    if (score > scoresave) {
      scoresave = score;
    }
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    score = 0;
    scorep2 = 0;
    player_x = 0;
    player_y = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    delay(100);
    lcd.clear();
    loop();
  }

  if (player_xp2 == enemy_xp2 && player_yp2 == enemy_yp2) {
    delay(150);
    lcd.setCursor(0, 0);
    lcd.print("P1 SCORE - ");
    lcd.print(score);
    lcd.setCursor(0, 2);
    lcd.print("P2 WAS HIT");
    lcd.setCursor(0, 1);
    lcd.print("P2 SCORE - ");
    lcd.print(scorep2);
    lcd.setCursor(0, 3);
    lcd.print("You Were eaten");
    lcd.setCursor(0, 10);
    deathsound();
    digitalWrite(9, HIGH);
    delay(50);
    digitalWrite(9, LOW);
    delay(50);
    if (scorep2 > scoresavep2) {
      scoresavep2 = scorep2;
    }
    if (score > scoresave) {
      scoresave = score;
    }
    score = 0;
    scorep2 = 0;
    player_xp2 = 0;
    player_yp2 = 0;
    player_x = 0;
    player_y = 0;
    enemy_xf = 10;
    enemy_yf = 0;
    enemy_x = 10;
    enemy_y = 0;
    enemy_xfp2 = 10;
    enemy_yfp2 = 0;
    enemy_xp2 = 10;
    enemy_yp2 = 0;
    game_started = 0;
    delay(100);
    lcd.clear();
    loop();
  }
}