//
//
//
//
//


#include "filadry.h"




// Neopixel

German::German(byte wordPIN) : Adafruit_NeoMatrix(11, 11, wordPIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800){}

// 80┌--> F N Ü F <-- T S I <-- S E                88   ES IST MFÜNF
// 79└--  G I Z N A W Z --> N H E Z          <--┐ 69   MZEHN ZWANZIG
// 62┌--> L E T R E I V <-- (I E R D)         --┘ 68   DREI VIERTEL
// 61└--  R O V --> H C A N                  <--┐ 55   NACH VOR
// 46┌--> F L Ö W Z <-- B L A H               --┘ 54   HALB ZWÖLF
// 45└--  N E B E I <-- S <-- N I E <-- W Z  <--┐ 35   ZWEI EIN SIEBEN
// 27┌--> F N Ü F --> I E R D                 --┘ 34   HDREI HFÜNF
// 26└--  R E I V <-- N U E N <-- F L E      <--┐ 16   ELF NEUN HVIER
// 8 ┌--> N H E Z --> T H C A                 --┘ 15   ACHT HZEHN
// 7 └--  R H U  <-- S H C E S                <--   0   SECHS UHR

const byte wordPositions[][8] = {{5 , 1, 2, 4, 5, 6, 0 , 0 }, // 5 LEDs total, Position 0,1,2,3,4 in the string   => 0: ES IST
                                {4 , 8, 9, 10, 11, 0 , 0 , 0 }, // 4 LEDs total, Position 5,6,7,8 in the string     => 1: MFÜNF
                                {4 , 22, 21, 20, 19, 0 , 0 , 0 }, //                                                  => 2: MZEHN
                                {7 , 18, 17, 16, 15, 14, 13, 12}, //                                                  => 3: ZWANZIG
                                {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }, // Not used in west german                          => 4: DREI
                                {7 , 27, 28, 29, 30, 31, 32, 33}, //                                                  => 5: VIERTEL
                                {4 , 42, 41, 40, 39, 0 , 0 , 0 }, //                                                  => 6: NACH
                                {3 , 38, 37, 36, 0 , 0 , 0 , 0 }, //                                                  => 7: VOR
                                {4 , 45, 46, 47, 48, 0 , 0 , 0 }, //                                                  => 8: HALB
                                {5 , 50, 51, 52, 53, 54, 0 , 0 }, //                                                  => 9: ZWÖLF
                                {4 , 66, 65, 64, 63, 0 , 0 , 0 }, //                                                  => 10: ZWEI
                                {3 , 64, 63, 62, 0 , 0 , 0 , 0 }, //                                                  => 11: EIN
                                {4 , 64, 63, 62, 61, 0 , 0 , 0 }, //                                                  => 12: EINS
                                {6 , 61, 60, 59, 58, 57, 56, 0 }, //                                                  => 13: SIEBEN
                                {4 , 68, 69, 70, 71, 0 , 0 , 0 }, //                                                  => 14: HDREI
                                {4 , 74, 75, 76, 77, 0 , 0 , 0 }, //                                                  => 15: HFÜNF
                                {3 , 88, 87, 86, 0 , 0 , 0 , 0 }, //                                                  => 16: ELF
                                {4 , 85, 84, 83, 82, 0 , 0 , 0 }, //                                                  => 17: NEUN
                                {4 , 81, 80, 79, 78, 0 , 0 , 0 }, //                                                  => 18: HVIER
                                {4 , 90, 91, 92, 93, 0 , 0 , 0 }, //                                                  => 19: ACHT
                                {4 , 94 , 95 , 96, 97, 0 , 0 , 0 }, //                                                  => 20: HZEHN
                                {5 , 109, 108, 107, 106, 105, 0 , 0 }, //                                                  => 21: SECHS
                                {3 , 102, 101, 100, 0 , 0 , 0 , 0 } //                                                   => 22: UHR
};

// MZWEI  <-- MEINS
//   |          ^
//   |          |
//   v          |
// MDREI      MVIER <-- 0

const byte minutePositions[][5] = {{1 , 111 , 0 , 0 , 0},                                                            //  => MEINS
                                  {2 , 111 , 112 , 0 , 0},                                                            //  => MEINS, MZWEI
                                  {3 , 111 , 112 , 113 , 0},                                                            //  => MEINS, MZWEI, MDREI
                                  {4 , 111 , 112 , 113 , 114}                                                             //  => MEINS, MZWEI, MDREI
};


const byte colours[][3] = {{255, 255, 255},                                                                        // WHITE
                          {255, 0  ,   0},                                                                        // RED
                          {0  , 255,   0},                                                                        // GREEN
                          {0  , 0  , 255},                                                                        // BLUE
                          {255, 135, 0  },                                                                        // ORANGE
                          {255, 255, 0  },                                                                        // YELLOW
                          {0  , 255, 255},                                                                        // CYAN
                          {128, 0  , 128},                                                                        // PURPLE
                          {139, 99 , 108}                                                                         // PINK
};

const char* colourName[9] = {"WHITE","RED","GREEN","BLUE","ORANGE","YELLOW","CYAN","PURPLE","PINK"};

// To adjust the brightness
byte LEDbrightness = 50;                                  // base LED brightness, value between 1 - 255 (with 255 being the brightest)
byte maxBrightness = 230;                                // limit the maximum brightness to lower stress on the LEDs
//int IncBrightPin=7;
//int RedBrightPin=9;
// Value of each colour, starting with White
byte rValue = 255;
byte gValue = 255;
byte bValue = 255;

// To turn LED fading on (=true) or off (=false)
boolean wordFading = true;
boolean minuteFading = true;
byte fadingDelay = 20;
byte fadingStep = 1;


void German::ledsOff() {
  if ( wordFading == true && minuteFading == true){
//    int step = LEDbrightness / 20;                // fade out in 20 steps, 100 ms apart
//    for ( int i = LEDbrightness ; i > 0 ; i-=step ) {
    for ( int i = LEDbrightness ; i > 0 ; i-=fadingStep ) {
      for ( int j = 0 ; j < wordLEDS ; j++ ){                 // we fade every LED ...
        if ( getPixelColor(j) != 0){               // that is not off
          setPixelColor(j,i*rValue/255,i*gValue/255,i*bValue/255);
        }
      }
      show();
      delay(fadingDelay);
    }
  }

  if ( wordFading == true && minuteFading == false){
//    int step = LEDbrightness / 20;                // fade out in 20 steps, 100 ms apart
//    for ( int i = LEDbrightness ; i > 0 ; i-=step ) {
    for ( int i = LEDbrightness ; i > 0 ; i-=fadingStep ) {
      for ( int j = 0 ; j < wordLEDS ; j++ ){                 // we fade every LED ...
        if ( getPixelColor(j) != 0){ // that is not off
            if(j < 111){    //excludes minute pixels
              setPixelColor(j,LEDbrightness*rValue/255,LEDbrightness*gValue/255,LEDbrightness*bValue/255);
          }
        }
      }
      show();
      delay(fadingDelay);
    }
  }

  if ( wordFading == false && minuteFading == true){
//    int step = LEDbrightness / 20;                // fade out in 20 steps, 100 ms apart
//    for ( int i = LEDbrightness ; i > 0 ; i-=step ) {
    for ( int i = LEDbrightness ; i > 0 ; i-=fadingStep ) {
      for ( int j = 111 ; j < wordLEDS ; j++ ){ //minute leds start at 111
        setPixelColor(j,LEDbrightness*rValue/255,LEDbrightness*gValue/255,LEDbrightness*bValue/255);   // here we know that each LED is ON
      }
      show();
      delay(fadingDelay);
    }
  }

  // make sure that they are really off and in case both wordFading and minuteFading is false
  for ( int j = 0 ; j < wordLEDS ; j++ ){
    setPixelColor(j,0,0,0);
  }
  show();
}

void German::minutesOff() {
  if ( minuteFading == true){
//    int step = LEDbrightness / 20;                // fade out in 20 steps, 100 ms apart
//    for ( int i = LEDbrightness ; i > 0 ; i-=step ) {
    for ( int i = LEDbrightness ; i > 0 ; i-=fadingStep ) {
      for ( int j = 111 ; j < wordLEDS ; j++ ){                 // we fade every LED ...
        if ( getPixelColor(j) != 0){               // that is not off
          setPixelColor(j,i*rValue/255,i*gValue/255,i*bValue/255);
        }
      }
      show();
      delay(fadingDelay);
    }
  }

  // make sure that they are really off and in case minuteFading is false
  for ( int j = 111 ; j < 115 ; j++ ){ //minute leds start at 111
    setPixelColor(j,0,0,0);
  }
  show();
}

void German::writeWords(int Words[]) {
if ( wordFading == true) {
    for ( int i = 0 ; i <= LEDbrightness ; i+=fadingStep ){
      for ( int k = 1 ; k < Words[0]+1 ; k++ ) {
        for ( int j=1 ; j < wordPositions[Words[k]][0]+1 ; j++ ){
          setPixelColor(wordPositions[Words[k]][j],i*rValue/255,i*gValue/255,i*bValue/255);
        }
      }
      show();
      delay(fadingDelay);
    }
  } else {
    for ( int k = 1 ; k < Words[0]+1 ; k++ ) {
      for ( int j=1 ; j < wordPositions[Words[k]][0]+1 ; j++ ){
        setPixelColor(wordPositions[Words[k]][j],LEDbrightness*rValue/255,LEDbrightness*gValue/255,LEDbrightness*bValue/255);
      }
    }
    show();
  }
}

void German::writeMinutes(int Minute){
  if ( minuteFading == true ) {
    for ( int i = 0 ; i <= LEDbrightness ; i+=fadingStep ){
      for ( int j=1 ; j < minutePositions[Minute][0]+1 ; j++ ){
        setPixelColor(minutePositions[Minute][j],i*rValue/255,i*gValue/255,i*bValue/255);
      }
      show();
      delay(fadingDelay);
    }
  } else {
    for ( int j=1 ; j < minutePositions[Minute][0]+1 ; j++ ){
      setPixelColor(minutePositions[Minute][j],LEDbrightness*rValue/255,LEDbrightness*gValue/255,LEDbrightness*bValue/255);
    }
    show();
  }
}

void German::displayWords(byte minute, byte hour){
  // start by clearing the display to a known state
  ledsOff();
  int Words[6] = {1, 0, 0, 0, 0, 0};

  //Serial.println("");
  //Serial.print(F("ES IST "));

  // now we display the appropriate minute counter
  if ((minute>4) && (minute<10)) {
    // MFUENF;
    Words[Words[0]+1] = 1;
    // NACH;
    Words[Words[0]+2] = 6;
    Words[0] += 2;
    //Serial.print(F("FUENF NACH "));
  }
  if ((minute>9) && (minute<15)) {
    // MZEHN;
    Words[Words[0]+1] = 2;
    // NACH;
    Words[Words[0]+2] = 6;
    Words[0] += 2;
    //Serial.print(F("ZEHN NACH "));
  }
  if ((minute>14) && (minute<20)) {
    // VIERTEL;
    Words[Words[0]+1] = 5;
    // NACH;
    Words[Words[0]+2] = 6;
    Words[0] += 2;
    //Serial.print(F("VIERTEL NACH "));
  }
  if ((minute>19) && (minute<25)) {
    // ZWANZIG;
    Words[Words[0]+1] = 3;
    // NACH;
    Words[Words[0]+2] = 6;
    Words[0] += 2;
    //Serial.print(F("ZWANZIG NACH "));
  }
  if ((minute>24) && (minute<30)) {
    // MFUENF;
    Words[Words[0]+1] = 1;
    // VOR;
    Words[Words[0]+2] = 7;
    // HALB;
    Words[Words[0]+3] = 8;
    Words[0] += 3;
    //Serial.print(F("FUENF VOR HALB "));
  }
  if ((minute>29) && (minute<35)) {
    // HALB;
    Words[Words[0]+1] = 8;
    Words[0] += 1;
    //Serial.print(F("HALB "));
  }
  if ((minute>34) && (minute<40)) {
    // MFUENF;
    Words[Words[0]+1] = 1;
    // NACH;
    Words[Words[0]+2] = 6;
    // HALB;
    Words[Words[0]+3] = 8;
    Words[0] += 3;
    //Serial.print(F("FUENF NACH HALB "));
  }
  if ((minute>39) && (minute<45)) {
    // ZWANZIG;
    Words[Words[0]+1] = 3;
    // VOR;
    Words[Words[0]+2] = 7;
    Words[0] += 2;
    //Serial.print(F("ZWANZIG VOR "));
  }
  if ((minute>44) && (minute<50)) {
    // VIERTEL;
    Words[Words[0]+1] = 5;
    // VOR;
    Words[Words[0]+2] = 7;
    Words[0] += 2;
    //Serial.print(F("VIERTEL VOR "));
  }
  if ((minute>49) && (minute<55)) {
    // MZEHN;
    Words[Words[0]+1] = 2;
    // VOR;
    Words[Words[0]+2] = 7;
    Words[0] += 2;
    //Serial.print(F("ZEHN VOR "));
  }
  if (minute>54) {
    // MFUENF;
    Words[Words[0]+1] = 1;
    // VOR;
    Words[Words[0]+2] = 7;
    Words[0] += 2;
    //Serial.print(F("FUENF VOR "));
  }

  if (minute <5) {
    switch (hour) {
    case 0:
        // ZWOELF;
        Words[Words[0]+1] = 9;
        Words[0] += 1;
        //Serial.print(F("ZWOELF "));
        break;
    case 1:
      // EIN;
      Words[Words[0]+1] = 11;
      Words[0] += 1;
      //Serial.print(F("EIN "));
      break;
    case 2:
      // ZWEI;
      Words[Words[0]+1] = 10;
      Words[0] += 1;
      //Serial.print(F("ZWEI "));
      break;
    case 3:
      // HDREI;
      Words[Words[0]+1] = 14;
      Words[0] += 1;
      //Serial.print(F("DREI "));
      break;
    case 4:
      // HVIER;
      Words[Words[0]+1] = 18;
      Words[0] += 1;
      //Serial.print(F("VIER "));
      break;
    case 5:
      // HFUENF;
      Words[Words[0]+1] = 15;
      Words[0] += 1;
      //Serial.print(F("FUENF "));
      break;
    case 6:
      // SECHS;
      Words[Words[0]+1] = 21;
      Words[0] += 1;
      //Serial.print(F("SECHS "));
      break;
    case 7:
      // SIEBEN;
      Words[Words[0]+1] = 13;
      Words[0] += 1;
      //Serial.print(F("SIEBEN "));
      break;
    case 8:
      // ACHT;
      Words[Words[0]+1] = 19;
      Words[0] += 1;
      //Serial.print(F("ACHT "));
      break;
    case 9:
      // NEUN;
      Words[Words[0]+1] = 17;
      Words[0] += 1;
      //Serial.print(F("NEUN "));
      break;
    case 10:
      // HZEHN;
      Words[Words[0]+1] = 20;
      Words[0] += 1;
      //Serial.print(F("ZEHN "));
      break;
    case 11:
      // ELF;
      Words[Words[0]+1] = 16;
      Words[0] += 1;
      //Serial.print(F("ELF "));
      break;
    case 12:
      // ZWOELF;
      Words[Words[0]+1] = 9;
      Words[0] += 1;
      //Serial.print(F("ZWOELF "));
      break;
    }
  // UHR;
  Words[Words[0]+1] = 22;
  Words[0] += 1;
  //Serial.print(F("UHR "));
  } else if ((minute < 25) && (minute >4)) {
    switch (hour) {
      case 0:
        // ZWOELF;
        Words[Words[0]+1] = 9;
        Words[0] += 1;
        //Serial.print(F("ZWOELF "));
        break;
      case 1:
        // EINS;
        Words[Words[0]+1] = 12;
        Words[0] += 1;
        //Serial.print(F("EINS"));
        break;
      case 2:
        // ZWEI;
        Words[Words[0]+1] = 10;
        Words[0] += 1;
        //Serial.print(F("ZWEI "));
        break;
      case 3:
        // HDREI;
        Words[Words[0]+1] = 14;
        Words[0] += 1;
        //Serial.print(F("DREI "));
        break;
      case 4:
        // HVIER;
        Words[Words[0]+1] = 18;
        Words[0] += 1;
        //Serial.print(F("VIER "));
        break;
      case 5:
        // HFUENF;
        Words[Words[0]+1] = 15;
        Words[0] += 1;
        //Serial.print(F("FUENF "));
        break;
      case 6:
        // SECHS;
        Words[Words[0]+1] = 21;
        Words[0] += 1;
        //Serial.print(F("SECHS "));
        break;
      case 7:
        // SIEBEN;
        Words[Words[0]+1] = 13;
        Words[0] += 1;
        //Serial.print(F("SIEBEN "));
        break;
      case 8:
        // ACHT;
        Words[Words[0]+1] = 19;
        Words[0] += 1;
        //Serial.print(F("ACHT "));
        break;
      case 9:
        // NEUN;
        Words[Words[0]+1] = 17;
        Words[0] += 1;
        //Serial.print(F("NEUN "));
        break;
      case 10:
        // HZEHN;
        Words[Words[0]+1] = 20;
        Words[0] += 1;
        //Serial.print(F("ZEHN "));
        break;
      case 11:
        // ELF;
        Words[Words[0]+1] = 16;
        Words[0] += 1;
        //Serial.print(F("ELF "));
        break;
      case 12:
        // ZWOELF;
        Words[Words[0]+1] = 9;
        Words[0] += 1;
        //Serial.print(F("ZWOELF "));
        break;
      }
    } else {
      // if we are greater than 24 minutes past the hour then display
      // the next hour, as we will be displaying a 'to' sign
      switch (hour) {
        case 0:
          // EINS;
          Words[Words[0]+1] = 12;
          Words[0] += 1;
          //Serial.print(F("EINS "));
          break;
        case 1:
          // ZWEI;
          Words[Words[0]+1] = 10;
          Words[0] += 1;
          //Serial.print(F("ZWEI "));
          break;
        case 2:
          // HDREI;
          Words[Words[0]+1] = 14;
          Words[0] += 1;
          //Serial.print(F("DREI "));
          break;
        case 3:
          // HVIER;
          Words[Words[0]+1] = 18;
          Words[0] += 1;
          //Serial.print(F("VIER "));
          break;
        case 4:
          // HFUENF;
          Words[Words[0]+1] = 15;
          Words[0] += 1;
          //Serial.print(F("FUENF "));
          break;
        case 5:
          // SECHS;
          Words[Words[0]+1] = 21;
          Words[0] += 1;
          //Serial.print(F("SECHS "));
          break;
        case 6:
          // SIEBEN;
          Words[Words[0]+1] = 13;
          Words[0] += 1;
          //Serial.print(F("SIEBEN "));
          break;
        case 7:
          // ACHT;
          Words[Words[0]+1] = 19;
          Words[0] += 1;
          //Serial.print(F("ACHT "));
          break;
        case 8:
          // NEUN;
          Words[Words[0]+1] = 17;
          Words[0] += 1;
          //Serial.print(F("NEUN "));
          break;
        case 9:
          // HZEHN;
          Words[Words[0]+1] = 20;
          Words[0] += 1;
          //Serial.print(F("ZEHN "));
          break;
        case 10:
          // ELF;
          Words[Words[0]+1] = 16;
          Words[0] += 1;
          //Serial.print(F("ELF "));
          break;
        case 11:
          // ZWOELF;
          Words[Words[0]+1] = 9;
          Words[0] += 1;
          //Serial.print(F("ZWOELF "));
          break;
        case 12:
          // EINS;
          Words[Words[0]+1] = 12;
          Words[0] += 1;
          //Serial.print(F("EINS "));
          break;
      }
   }
   writeWords(Words);
}

void German::displayMinutes(byte minute){
   minutesOff();
   // In order to make use of the four minute LEDs
   if (minute % 5 == 1) {
    writeMinutes(0);
//    //Serial.print(F("+1 "));
  }
  if (minute % 5 == 2) {
    writeMinutes(1);
//    //Serial.print(F("+2 "));
  }
  if (minute % 5 == 3) {
    writeMinutes(2);
//    //Serial.print(F("+3 "));
  }
  if (minute % 5 == 4) {
    writeMinutes(3);
//    //Serial.print(F("+4"));
  }
}
