#include <Arduino.h>

/* Commands */

#define CMD_TEST_INPUTS '1'
#define CMD_TEST_LIGHTS_EXT '2'
#define CMD_TEST_LIGHTS_PRESS '3'
#define CMD_TEST_DEBOUNCE '4'
#define CMD_TEST_LEGACY '5'

/* 
 * Map Arduino Mega pins to BD845-PWB pins.
 * The pinout for the BD845-PWB can be found here 
 * https://docs.bluedotarcade.com/boards/bd845-pwb
 */

/* Comm inputs */

#define FL1       PF0
#define FL2       PF1
#define FL3       PF2
#define FL4       PF3
#define FL5       PF4
#define TEST      PF5
#define IN_DDR    DDRF
#define IN_PORT   PORTF
#define IN_OFFSET 0

/* Comm outputs */

#define C_OUT      PK0 
#define R_OUT      PK1 
#define L_OUT      PK2 
#define D_OUT      PK3 
#define U_OUT      PK4 
#define OUT_DDR    DDRK
#define OUT_PIN    PINK
#define OUT_OFFSET 0

/* Panel up sensors */

#define U_S1     PA0 
#define U_S2     PA1 
#define U_S3     PA2 
#define U_S4     PA3 
#define U_DDR    DDRA
#define U_PORT   PORTA
#define U_OFFSET 0

/* Panel down sensors */

#define D_S1     PA4 
#define D_S2     PA5 
#define D_S3     PA6 
#define D_S4     PA7 
#define D_DDR    DDRA
#define D_PORT   PORTA
#define D_OFFSET 4

/* Panel left sensors */

#define L_S1     PC0 
#define L_S2     PC1 
#define L_S3     PC2 
#define L_S4     PC3 
#define L_DDR    DDRC
#define L_PORT   PORTC
#define L_OFFSET 0

/* Panel right sensors */

#define R_S1     PC4 
#define R_S2     PC5 
#define R_S3     PC6 
#define R_S4     PC7 
#define R_DDR    DDRC
#define R_PORT   PORTC3
#define R_OFFSET 4

/* Panel center sensors */

#define C_S1     PB0 
#define C_S2     PB1 
#define C_S3     PB2 
#define C_S4     PB3 
#define C_DDR    DDRB
#define C_PORT   PORTB
#define C_OFFSET 0

/* Lights */

#define U_LIGHT      PL0 
#define D_LIGHT      PL1 
#define L_LIGHT      PL2 
#define R_LIGHT      PL3 
#define C_LIGHT      PL4
#define LIGHT_DDR    DDRL
#define LIGHT_PIN    PINL
#define LIGHT_OFFSET 0

void setupSerialPort();
void setupLeds();
void setupCommInputPins();
void setupCommOutputPins();
void setupUpPins();
void setupDownPins();
void setupLeftPins();
void setupRightPins();
void setupCenterPins();
void setupLightPins();

bool testInputs();
bool testLightsExt();
bool testLightsPress();
bool testDebounce();
bool testLegacy();

uint8_t readCommOutputPins();
uint8_t readLightPins();
void setCommInputPins(uint8_t state);
void setUpPins(uint8_t state);
void setDownPins(uint8_t state);
void setLeftPins(uint8_t state);
void setRightPins(uint8_t state);
void setCenterPins(uint8_t state);
void setHighZ(int pin);
void printMenu();
void setErrored();
void clearError();

// Setup ---------------------------------------------------------------

void setup() {
  setupSerialPort();
  setupLeds();

  setupCommInputPins();
  setupCommOutputPins();
  
  setupUpPins();
  setupDownPins();
  setupLeftPins();
  setupRightPins();
  setupLightPins();
}

void setupSerialPort() {
  Serial.begin(115200);
}

void setupLeds() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void setupCommInputPins() {
  setHighZ(TEST);
  setHighZ(FL5);
  setHighZ(FL4);
  setHighZ(FL3);
  setHighZ(FL2);
  setHighZ(FL1);
}

void setupCommOutputPins() {
  pinMode(C_OUT, INPUT_PULLUP);
  pinMode(R_OUT, INPUT_PULLUP);
  pinMode(L_OUT, INPUT_PULLUP);
  pinMode(D_OUT, INPUT_PULLUP);
  pinMode(U_OUT, INPUT_PULLUP);
}

void setupUpPins() {
  setHighZ(U_S1);
  setHighZ(U_S2);
  setHighZ(U_S3);
  setHighZ(U_S4);
}

void setupDownPins() {
  setHighZ(U_S1);
  setHighZ(U_S2);
  setHighZ(U_S3);
  setHighZ(U_S4);
}

void setupLeftPins() {
  setHighZ(U_S1);
  setHighZ(U_S2);
  setHighZ(U_S3);
  setHighZ(U_S4);
}

void setupRightPins() {
  setHighZ(U_S1);
  setHighZ(U_S2);
  setHighZ(U_S3);
  setHighZ(U_S4);
}

void setupCenterPins() {
  setHighZ(U_S1);
  setHighZ(U_S2);
  setHighZ(U_S3);
  setHighZ(U_S4);
}

void setupLightPins() {
  pinMode(U_LIGHT, INPUT_PULLUP);
  pinMode(D_LIGHT, INPUT_PULLUP);
  pinMode(L_LIGHT, INPUT_PULLUP);
  pinMode(R_LIGHT, INPUT_PULLUP);
  pinMode(C_LIGHT, INPUT_PULLUP);
}

// Loop ----------------------------------------------------------------

void loop() {
  //Serial.flush();
  printMenu();

  // Wait for command
  while(Serial.available() <= 0);

  clearError();
  char cmd = Serial.read();
  bool successful = true;
 
  switch(cmd) {
    case CMD_TEST_INPUTS:
      successful = testInputs();
      break;
    case CMD_TEST_LIGHTS_EXT:
      successful = testLightsExt();
      break;
    case CMD_TEST_LIGHTS_PRESS:
      successful = testLightsPress();
      break;
    case CMD_TEST_DEBOUNCE:
      successful = testDebounce();
      break;
    case CMD_TEST_LEGACY:
      successful = testLegacy();
      break;
    default:
      Serial.println(F("Command not found!"));
      return;
  }

  if(successful) {
    Serial.println(F("TEST SUCCESSFUL"));
  } else {
    Serial.println(F("TEST FAILED"));
    setErrored();
  }
}

bool testInputs() {
  uint8_t up = 0;
  uint8_t down = 0;
  uint8_t left = 0;
  uint8_t right = 0;
  uint8_t center = 0;

  setUpPins(up);
  setDownPins(down);
  setLeftPins(left);
  setRightPins(right);
  setCenterPins(center);

  if(readCommOutputPins() != 0)
    return false;
  
  while(++up < 0x10) {
    setUpPins(up);

    if(readCommOutputPins() != U_OUT)
      return false;
  }

  return true;
}

bool testLightsExt() {
  Serial.println(F("Testing lights external..."));
  uint8_t inputs = 0;
  uint8_t lights = 0;
  uint8_t expected = 0;

  while(inputs < 0x20) {
    setCommInputPins(inputs);
    delay(1);
    lights = readLightPins();
    expected = ~inputs & 0x1F;
    
    if(lights != expected) {
      Serial.print(F("inputs: "));
      Serial.print(inputs, HEX);
      Serial.print(F(", lights: "));
      Serial.print(lights, HEX);
      Serial.print(F(", expected: "));
      Serial.print(expected, HEX);
      Serial.println();
      return false;
    }
    
    inputs++;
  }

  return true;
}

bool testLightsPress() {
  return true;
}

bool testDebounce() {
  return true;
}

bool testLegacy() {

  return true;
}

// Utilities -----------------------------------------------------------

uint8_t readCommOutputPins() {
  return OUT_PIN & (0x1F << OUT_OFFSET);
}

uint8_t readLightPins() {
  return LIGHT_PIN & (0x1F << LIGHT_OFFSET);
}

void setCommInputPins(uint8_t state) {
  IN_DDR = (IN_DDR & (0xC0 >> IN_OFFSET)) | (state << IN_OFFSET);
}

void setUpPins(uint8_t state) {
  U_DDR = (U_DDR & (0xF0 >> U_OFFSET)) | (state << U_OFFSET);
}

void setDownPins(uint8_t state) {
  D_DDR = (D_DDR & (0xF0 >> D_OFFSET)) | (state << D_OFFSET);
}

void setLeftPins(uint8_t state) {
  L_DDR = (L_DDR & (0xF0 >> L_OFFSET)) | (state << L_OFFSET);
}

void setRightPins(uint8_t state) {
  R_DDR = (R_DDR & (0xF0 >> R_OFFSET)) | (state << R_OFFSET);
}

void setCenterPins(uint8_t state) {
  C_DDR = (C_DDR & (0xF0 >> C_OFFSET)) | (state << C_OFFSET);
}

void setHighZ(int pin) {
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
}

void printMenu() {
  Serial.println(F("\n*** BD845-PWB Test Routines ***\n"));
  Serial.println(F("Select option:"));
  Serial.println(F("1. Test inputs"));
  Serial.println(F("2. Test lights external"));
  Serial.println(F("3. Test lights press mode"));
  Serial.println(F("4. Test debounce"));
  Serial.println(F("5. Test legacy"));
  Serial.println();
}

void clearError() {
  digitalWrite(LED_BUILTIN, LOW);
}

void setErrored() {
  digitalWrite(LED_BUILTIN, HIGH);
}