// Musik abspielen

const int Speaker = 11;
const int Speaker2 = 12;
int Speed = 1000;

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

// alle meine entchen
const String song0[] = {"c4d4e4f4g2g2a4a4a4a4g1a4a4a4a4g1f4f4f4f4e2e2d4d4d4d4c1", "1000"};

// song von Smaxx: Hänschen Klein
const String song1[] = {"g2e2e4f2d2d4c2d2e2f2g2g2g4g2e2e4f2d2d4c2e2g2g2c4", "1000"};

// song von green: Oh, du Fröhliche
const String song2[] = {"g2a2g4f4e4f4g2a2g4f4e4f4g2g2a2h4c4h2a2g2", "2000"};

// song von Smaxx: super mario (anfang)
const String song3 [] = {"a8a4a4f8a4h2c2", "1000"};

// song von green: Darude Sandstorm
// zu lang!!!: const String song4[] = {"d8d8d8d8d8a8d8d8d8d8d8a8d8d8d8d8d8a8a8a8f8f8f8c8d8d8d8d8d8a8d8d8d8d8d8c8d8d8d8d8d8a8a8a8f8f8f8c8d8d8d8d8d8a8d8d8d8d8d8c8d8d8d8d8d8a8a8a8f8f8f8c8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8d8", "800"};
const String song4[] = {"d8d8d8d8d8a8d8d8d8d8d8a8d8d8d8d8d8a8a8a8f8f8f8c8d8d8d8d8d8a8d8", "800"};

// song von green: Korobeiniki (Tetris Song)
const String song5[] = {"h2f4g4a2g4f4e2e4g4h2a4g4f2f4g4a4h4g4e4e2", "1000"};
// mit bassspur: const String song5[] = {"h2f4g4a2g4f4e2e4g4h2a4g4f2f4g4a4h4g4e4e2", "1000", "e4h4e4h4e4h4e4h4f4a4f4a4f4a4f4a4e4h4e4h4e4h4e4h4f4a4f4a4f4a4f4a4"};

// song von green: Twinkle twinkle little star
const String song6[] = {"c2c2g2g2a2a2g1f2f2efefd2d2c1", "1000"};


// song von green: Für Elise
const String song7[] = {"e4d4e4d4e4d4e4d4e4h4d4c4a2c2e2a2", "1000"};

// song von green: Axel F.
const String song8[] = {"g4h4g8g8g8c8g4f4g4d4g8g8g8e8d4h4", "1000"};

// album der oben stehenden Songs
const String album [][2] = {song0, song1, song2, song3, song4, song5, song6, song7};

int playTime = (sizeof(album) / sizeof(album[0])) - 1;

void setup() {
  pinMode(Speaker, OUTPUT);
  Serial.begin(9600);
  Serial.println("<Arduino is ready: Type in Song>");
}

void playTone(char c, int duration) {
  switch (c) {
    case 'c':
      tone(Speaker, 264);
      break;

    case 'd':
      tone(Speaker, 294);
      break;

    case 'e':
      tone(Speaker, 330);
      break;

    case 'f':
      tone(Speaker, 352);
      break;

    case 'g':
      tone(Speaker, 396);
      break;

    case 'a':
      tone(Speaker, 440);
      break;

    case 'h': case 'b':
      tone(Speaker, 495);
      break;

  default: case 'p':
      noTone(Speaker);
      break;
  }

  delay(Speed / duration);
  noTone(Speaker);
  delay(Speed / 16);
}

/* 2 oktaven tiefer (das hier auf piezo laufen lassen, das höhere auf dem summer)
  void playTone(char c, int duration) {
  switch (c) {
    case 'c':
      tone(Speaker2, 66);
      break;

    case 'd':
      tone(Speaker2, 74);
      break;

    case 'e':
      tone(Speaker2, 83);
      break;

    case 'f':
      tone(Speaker2, 88);
      break;

    case 'g':
      tone(Speaker2, 99);
      break;

    case 'a':
      tone(Speaker2, 110);
      break;

    case 'h': case 'b':
      tone(Speaker2, 124);
      break;

  default: case 'p':
      noTone(Speaker2);
      break;
  }

  delay(Speed / duration);
  noTone(Speaker);
  delay(Speed / 16);
  }
*/

// Methode, um Song von Album abzuspielen
void readSongFromAlbum(const String song[]) {
  for (int i = 0; i < song[0].length(); i = i +  2) {
    char note = song[0][i];
    int duration = atoi(song[0].c_str() + i + 1);
    playTone(note, duration);
  }
}

/*
  void playSingleTone(const char *c){
  while (*c) playTone(*c++,2);
  }
*/

void loop() {

  // receive new data
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 &&  newData == false) {
    rc = Serial.read();

    if (rc !=  endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }

  // print new data
  if (newData == true) {
    Serial.print("This is the current song: ");
    Serial.println(receivedChars);
    newData = false;
  }


  for (int i = 0; i <= 30; i = i + 2) {
    char currentTone = receivedChars[i];
    char durationChar = receivedChars[i + 1];
    char durationCharArray[] = {durationChar};
    //char durationCharArray[] = "durationChar";
    Serial.print("Char: ");
    Serial.println(durationChar, DEC);
    String durationString = durationCharArray;
    Serial.print("String: ");
    Serial.println(durationString);
    int durationInt = atoi(durationCharArray);
    //int durationInt = (int) durationChar - (int) '0';
    //int durationInt = (int) durationChar - '0';
    //int durationInt = (int) durationChar - 48;
    //int durationInt = 2;
    //int durationInt = durationChar.parseInt(); // geht nicht! durationChar ist non-class type 'char'
    //int durationInt = durationString.toInt();    
    Serial.print("Int: ");
    //Serial.println(durationInt, DEC);
    Serial.println(durationString.toInt());
    //playTone(currentTone, 2);
    playTone(currentTone, durationString.toInt());
    //playTone(currentTone, durationInt);
    //Serial.println(durationInt);
  }
  /*// play songs from album
    if (playTime >= 0) {
    Speed = album[playTime][1].toInt();
    readSongFromAlbum(album[playTime]);
    playTime = playTime - 1;
    }
  */

  /*
    if (Serial.available() > 0){
      char in = Serial.read();
      if(in != -1){
        playTone('c',2);
        delay(1000);
      }
    }
  */
  /*
    delay(4000); // last note played for 4 seconds
    noTone(Speaker); // mute speaker as last operation
  */
}
