/*
  Display (1.8" TFT ST7735):
  - VCC     --> 5V
  - GND     --> GND
  - CS      --> D10
  - RESET   --> D8
  - A0 / DC --> D9
  - SDA     --> D11
  - SCK     --> D13
  - LED     --> 3V3

  Encoder (https://www.elextra.dk/details/H35684/rotary-encoder-18-trin-m-trykknap-funktion):
  -         --> GND
  -         --> GND
  -         --> A0
  -         --> A1
  -         --> A2
*/

#include <Arduino.h>
#include <ClickEncoder.h>
#include <EEPROM.h>
#include <TimerOne.h>
#include "display.h"

#include <HX711_ADC.h>
#include <EEPROM.h>

// Relay settings
#define RELAY 2 // Relay on pin D2
#define RELAY_ON HIGH
#define RELAY_OFF LOW

// EEPROM Locations
#define EEPROM_LOC_SINGLESHOT 20
#define EEPROM_LOC_DOUBLESHOT 40
#define EEPROM_LOC_SINGLESHOT_USER2 60
#define EEPROM_LOC_DOUBLESHOT_USER2 80

// pins for HX711:
const int HX711_dout = 10;          // mcu > HX711 dout pin
const int HX711_sck = 8;            // mcu > HX711 sck pin
const int serialPrintInterval = 15; // increase value to slow down serial print/BLE activity
// Var for calibration and t for timer
const int calVal_eepromAdress = 0;
unsigned long t = 0;
float newMass = 0.0;
float error = 0.04;
float fudge = 1;    // fudge factor for hysteresis: increase if too heavy
bool state = 0;     // state variable, 0 = off, 1 = on
float target = 0.0; // initial target weight for grinder

// Trickle Variables
const unsigned long bump = 100;    // trickle time
const unsigned long settle = 2000; // settling time
unsigned long tt = 0;              // timer for settling
bool isSettle = true;

// Default grind times
uint16_t SINGLESHOT = 8000;  // Max 65,535 milliseconds because of datatype
uint16_t SINGLESHOT_TEMP;    // Max 65,535 milliseconds because of datatype
uint16_t DOUBLESHOT = 15000; // Max 65,535 millisecond because of datatype
uint16_t DOUBLESHOT_TEMP;    // Max 65,535 milliseconds because of datatype

uint16_t SINGLESHOT_USER2 = 8000; // Max 65,535 milliseconds because of datatype
// uint16_t SINGLESHOT_TEMP_USER2;    // Max 65,535 milliseconds because of datatype
uint16_t DOUBLESHOT_USER2 = 15000; // Max 65,535 millisecond because of datatype
// uint16_t DOUBLESHOT_TEMP_USER2;    // Max 65,535 milliseconds because of datatype

// States
uint8_t prevMenu = 255;      // High number to ensure that start screen gets drawn
uint8_t realPrevMenu = 0;    // Default settings: 0
uint8_t currentMenu = 0;     // Default settings: 0
uint8_t inQuickSettings = 0; // Bool
uint8_t inGrindMode = 0;     // Bool
uint8_t showValue = 0;       // Bool
bool steamState = false;
bool reRenderStream = false;
uint8_t user = 1;

uint8_t grindActive = false; // Bool -> Is grinder currently grinding?
bool returnToStarMenu = false;
// uint32_t grindUntil = 0;

uint32_t currentMillis = 0;
uint32_t previousMillis = 0; // will store last time
uint32_t interval = 500;     // interval at which to blink (milliseconds)

uint32_t menueMillis = 0;
uint32_t previousMenueMillis = 0; // will store last time
uint32_t menueInterval = 5000;    // time before reset to startmenu

ClickEncoder *encoder;

int8_t encoderValue = 0;
uint8_t encoderButton = 0;

// HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

void timerIsr()
{
  encoder->service();
}

void renderDisplay(uint8_t user)
{
  if (prevMenu != currentMenu)
  {
    prevMenu = currentMenu;
    switch (currentMenu)
    {
    case 0:
      screenDefault(steamState, currentMenu);
      drawUser(user);
      break;

    case 1:
      screenManualGrind(currentMenu);
      drawUser(user);
      break;

    case 2:
      screenSingleShot(currentMenu, SINGLESHOT);
      drawUser(user);
      break;

    case 3:
      screenDoubleShot(currentMenu, DOUBLESHOT);
      drawUser(user);
      break;

    case 4:
      screenQuickSettings();
      break;

    case 5:
      screenQuickSettingsSaved();
      break;

    case 6:
      screenQuickSettingsCancelled();
      break;

    default:
      screenDefault(steamState, currentMenu);
      drawUser(user);
      break;
    }
  }
  else if (currentMenu == 0 && reRenderStream)
  {
    reRenderStream = !reRenderStream;
    drawSteam(50, 65, steamState);
  }
  else if (currentMenu == 0 && reRenderStream)
  {
    reRenderStream = !reRenderStream;
    drawSteam(50, 65, steamState);
  }
}

void writeToEEPROM(uint8_t location)
{
  uint16_t tempEEPROMVal;
  EEPROM.get(location, tempEEPROMVal);
  if ((location == EEPROM_LOC_SINGLESHOT || location == EEPROM_LOC_SINGLESHOT_USER2) && tempEEPROMVal != SINGLESHOT)
  {
    EEPROM.put(location, SINGLESHOT);
  }
  else if ((location == EEPROM_LOC_DOUBLESHOT || location == EEPROM_LOC_DOUBLESHOT_USER2) && tempEEPROMVal != DOUBLESHOT)
  {
    EEPROM.put(location, DOUBLESHOT);
  }
}

void relayOn()
{
  digitalWrite(RELAY, RELAY_ON);
}

void relayOff()
{
  digitalWrite(RELAY, RELAY_OFF);
}

void setGrindState()
{
  ucg.setColor(0, 0, 0);
  ucg.drawBox(0, 120, 128, 20);

  if (grindActive)
  {
    ucg.setColor(255, 0, 0);
    ucg.setPrintPos(41, 130);
    ucg.print("GRINDING");
  }
  else if (!grindActive)
  {
    ucg.setColor(255, 0, 0);
    if (currentMenu == 1)
    {
      ucg.setPrintPos(27, 130);
      ucg.print("Hold to grind");
    }
    else
    {
      ucg.setPrintPos(25, 130);
      ucg.print("Press to start");
    }
  }
}

void startGrind(uint16_t target)
{
  if (!grindActive) // START GRINDING
  {
    float i = LoadCell.getData();
    newMass = i;

    grindActive = true;
    setGrindState();
    relayOn();

    // scale
    Serial.print("Motor Running. Target = " + String(target) + "  Current = " + String(newMass) + "\n");
  }
  else if (newMass >= target + error) // GRINDING ENDED - check if the weight is equal to or larger than goal (with some rounding error)
  {
    relayOff();
    grindActive = false;
    inGrindMode = false;
    Serial.print("Motor Off. Target = " + String(target) + "  Current = " + String(newMass) + "\n");
    setGrindState();
    clearProgress();
  }

  else

  {
    if (target > (newMass + fudge)) // WHILE GRINDING
    // if (grindActive && (target > (newMass + fudge))) // WHILE GRINDING
    // if (grindActive && millis() < grindUntil)
    {
      if (encoderButton == 5) // CLICK --> CANCEL GRINDING WHILE GRINDING
      {
        relayOff();
        Serial.print("Motor Off. Target = " + String(target) + "  Current = " + String(newMass) + "\n");
      }

      uint16_t actMass = target - newMass;
      actMass = map(actMass, 0, target, 0, 128);
      drawProgress(actMass);
    }
    else
    { // If we are close to our target (less than fudge factor)
      if (isSettle)
      {             // Do we need to let the reading settle? (starts as "true")
        relayOff(); // if yes, turn the motor off for our settling time
        if (millis() - tt >= settle)
        {                   // if we've waited long enough
          tt = millis();    // reset the time
          isSettle = false; // we're done settling
        }
      }
      else
      {            // if we are done waiting to settle
        relayOn(); // turn the motor on
        if (millis() - tt >= bump)
        {                  // but just for our bump time
          tt = millis();   // reset the timer
          isSettle = true; // then go back to settling so we can check the weight
        }
      }
    }
  }
}

void readEEprom(uint8_t user)
{
  if (user == 1)
  {
    EEPROM.get(EEPROM_LOC_SINGLESHOT, SINGLESHOT);
    EEPROM.get(EEPROM_LOC_DOUBLESHOT, DOUBLESHOT);
  }
  else
  {
    EEPROM.get(EEPROM_LOC_SINGLESHOT_USER2, SINGLESHOT);
    EEPROM.get(EEPROM_LOC_DOUBLESHOT_USER2, DOUBLESHOT);
  }
  SINGLESHOT_TEMP = SINGLESHOT;
  DOUBLESHOT_TEMP = DOUBLESHOT;
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("System: Running");
  delay(1000);
  ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.clearScreen();

  // Initialise the ClickEndoder
  encoder = new ClickEncoder(A1, A0, A2);

  LoadCell.begin();
  // LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  float calibrationValue;      // calibration value (see example file "Calibration.ino")
  calibrationValue = -2137.60; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266) || defined(ESP32)
  // EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  // EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true;                 // set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag())
  {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    // display.clearDisplay();
    // display.setTextSize(1);
    // display.setTextColor(WHITE);
    // display.setCursor(0, 10);
    // display.println("Timeout, check MCU>HX711 wiring and pin designations");
    // display.display();
    while (1)
      ;
  }
  else
  {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
    // display.clearDisplay();
    // display.setTextSize(1);
    // display.setTextColor(WHITE);
    // display.setCursor(0, 10);
    // display.println("Load Cell Ok");
    // display.display();
  }

  // begin BLE initialization
  // if (!BLE.begin()) {
  //   Serial.println("BLE failed to start!");
  //   display.clearDisplay();
  //   display.setTextSize(1);
  //   display.setTextColor(WHITE);
  //   display.setCursor(0, 10);
  //   display.println("BLE failed to start!");
  //   display.display();
  //   while (1)
  //  ;
  // }

  // Initialise the Arduino data pins for OUTPUT
  pinMode(RELAY, OUTPUT);
  relayOff();

  readEEprom(user);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  currentMillis = millis();
}

void changeUser()
{
  user == 1 ? user = 2 : user = 1;
  drawUser(user);
  readEEprom(user);
}

void loop(void)
{
  currentMillis = millis();
  if (!grindActive)
  {
    encoderValue = encoder->getValue();
  }
  encoderButton = encoder->getButton();

  switch (currentMenu)
  {
  case 0: // START SCREEN
    if (!inQuickSettings)
    {
      if (encoderButton == 5)
      {
        changeUser();
      }
      if (encoderValue > 0)
      {
        currentMenu = 1;
      }
      else if (encoderValue < 0)
      {
        currentMenu = 3;
      }

      if (currentMillis - previousMillis > interval)
      {
        previousMillis = currentMillis;
        steamState = !steamState;
        reRenderStream = !reRenderStream;
      }
    }
    renderDisplay(user);
    break;

  case 1: // MANUAL GRIND
    if (!inQuickSettings)
    {
      if (encoderButton == 3)
      {
        relayOn();
        grindActive = true;
        setGrindState();
      }
      else if (encoderButton == 4)
      { // HOLD --> START GRINDING
        relayOff();
        grindActive = false;
        setGrindState();
      }

      if (encoderValue > 0)
      {
        currentMenu = 2;
      }
      else if (encoderValue < 0)
      {
        currentMenu = 0;
      }
    }
    renderDisplay(user);
    break;

  case 2: // SINGLE SHOT
    realPrevMenu = 2;
    if (!inQuickSettings)
    {
      if (encoderValue > 0)
      {
        currentMenu = 3;
      }
      else if (encoderValue < 0)
      {
        currentMenu = 1;
      }

      if (encoderButton == 5)
      { // CLICK --> START GRINDING
        inGrindMode = true;
      }

      if (inGrindMode == true)
      {
        startGrind(SINGLESHOT);
      }

      if (encoderButton == 4)
      { // HOLD --> ENTER SETTINGS
        inQuickSettings = true;
        currentMenu = 4;
      }
    }
    renderDisplay(user);
    break;

  case 3: // DOUBLE SHOT
    realPrevMenu = 3;
    if (!inQuickSettings)
    {
      if (encoderValue > 0)
      {
        currentMenu = 0;
      }
      else if (encoderValue < 0)
      {
        currentMenu = 2;
      }

      if (encoderButton == 5)
      { // CLICK --> START GRINDING
        inGrindMode = true;
      }

      if (inGrindMode == true)
      {
        startGrind(DOUBLESHOT);
      }

      if (encoderButton == 4)
      { // HOLD --> ENTER SETTINGS
        inQuickSettings = true;
        currentMenu = 4;
      }
    }
    renderDisplay(user);
    break;

  case 4: // QUICK SETTINGS
    if (realPrevMenu == 2)
    {
      if (!showValue)
      {
        screenQuickSettingsValue(SINGLESHOT_TEMP);
        encoder->setAccelerationEnabled(true);
        showValue = true;
      }

      if (encoderValue > 0)
      {
        if (SINGLESHOT_TEMP < 65500)
        {
          SINGLESHOT_TEMP += (encoderValue * 100);
        }
        else
        {
          SINGLESHOT_TEMP = 65500;
        }
        screenQuickSettingsValue(SINGLESHOT_TEMP);
      }
      else if (encoderValue < 0)
      {
        if (SINGLESHOT_TEMP > 0)
        {
          SINGLESHOT_TEMP += (encoderValue * 100);
        }
        else
        {
          SINGLESHOT_TEMP = 0;
        }
        screenQuickSettingsValue(SINGLESHOT_TEMP);
      }

      if (encoderButton == 5)
      { // CLICK --> SAVE SETTINGS
        SINGLESHOT = SINGLESHOT_TEMP;
        user == 1 ? writeToEEPROM(EEPROM_LOC_SINGLESHOT) : writeToEEPROM(EEPROM_LOC_SINGLESHOT_USER2);
        inQuickSettings = false;
        currentMenu = 5;
        showValue = false;
        encoder->setAccelerationEnabled(false);
      }

      if (encoderButton == 4)
      { // HOLD --> CANCEL SETTINGS
        SINGLESHOT_TEMP = SINGLESHOT;
        inQuickSettings = false;
        currentMenu = 6;
        showValue = false;
        encoder->setAccelerationEnabled(false);
      }
    }
    else if (realPrevMenu == 3)
    {
      if (!showValue)
      {
        screenQuickSettingsValue(DOUBLESHOT_TEMP);
        encoder->setAccelerationEnabled(true);
        showValue = true;
      }

      if (encoderValue > 0)
      {
        if (DOUBLESHOT_TEMP < 65500)
        {
          DOUBLESHOT_TEMP += (encoderValue * 100);
        }
        else
        {
          DOUBLESHOT_TEMP = 65500;
        }
        screenQuickSettingsValue(DOUBLESHOT_TEMP);
      }
      else if (encoderValue < 0)
      {
        if (DOUBLESHOT_TEMP > 0)
        {
          DOUBLESHOT_TEMP += (encoderValue * 100);
        }
        else
        {
          DOUBLESHOT_TEMP = 0;
        }
        screenQuickSettingsValue(DOUBLESHOT_TEMP);
      }

      if (encoderButton == 5)
      { // CLICK --> SAVE SETTINGS
        DOUBLESHOT = DOUBLESHOT_TEMP;
        user == 1 ? writeToEEPROM(EEPROM_LOC_DOUBLESHOT) : writeToEEPROM(EEPROM_LOC_DOUBLESHOT_USER2);
        inQuickSettings = false;
        currentMenu = 5;
        showValue = false;
        encoder->setAccelerationEnabled(false);
      }

      if (encoderButton == 4)
      { // HOLD --> CANCEL SETTINGS
        DOUBLESHOT_TEMP = DOUBLESHOT;
        inQuickSettings = false;
        currentMenu = 6;
        showValue = false;
        encoder->setAccelerationEnabled(false);
      }
    }
    renderDisplay(user);
    break;

  case 5: // QUICK SETTINGS SAVED
    renderDisplay(user);
    delay(1500);
    currentMenu = realPrevMenu;
    break;

  case 6: // QUICK SETTINGS CANCELLED
    renderDisplay(user);
    delay(1500);
    currentMenu = realPrevMenu;
    break;

  default:
    break;
  }
}
