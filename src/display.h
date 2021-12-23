#include "Arduino.h"
#include "Ucglib.h"
#include <SPI.h>

#define DISPLAY_RESET 8
#define DISPLAY_CD 9
#define DISPLAY_CS 10

Ucglib_ST7735_18x128x160_HWSPI ucg(DISPLAY_CD, DISPLAY_CS, DISPLAY_RESET);

/**************************************************************/
/* DRAWINGS                                                   */
/**************************************************************/
void drawSteam(uint8_t _xPos, uint8_t _yPos, bool steamState)
{
  int x;
  steamState ? x = 6 : x = 0;

  //clear
  ucg.setColor(0, 0, 0);
  ucg.drawBox(_xPos, _yPos - 20, 30, 20);
  // delay(50);

  ucg.setColor(90, 90, 90);
  ucg.drawBox(57 + x, 25 + x / 2, 2, 2);
  ucg.drawBox(59 + x, 27 + x / 2, 2, 2);
  ucg.drawBox(58 + x, 29 + x / 2, 1, 4);
  ucg.drawBox(59 + x, 33 + x / 2, 2, 4);
  ucg.drawBox(58 + x, 37 + x / 2, 1, 2);

  ucg.setColor(80, 80, 80);
  ucg.drawBox(65 - x, 25, 2, 2);
  ucg.drawBox(63 - x, 27, 2, 4);
  ucg.drawBox(65 - x, 31, 2, 2);
  ucg.drawBox(63 - x, 33, 2, 2);
  ucg.drawBox(64 - x, 35, 1, 2);
  ucg.drawBox(63 - x, 37, 2, 2);
}

void drawMug(uint8_t _xPos, uint8_t _yPos, bool steamState)
{
  // Top
  ucg.setColor(255, 255, 255);
  ucg.drawBox(_xPos + 8, _yPos + 0, 8, 1);

  ucg.drawBox(_xPos + 4, _yPos + 1, 4, 1);
  ucg.drawBox(_xPos + 16, _yPos + 1, 4, 1);

  ucg.drawBox(_xPos + 2, _yPos + 2, 2, 1);
  ucg.drawBox(_xPos + 20, _yPos + 2, 2, 1);

  ucg.drawBox(_xPos + 1, _yPos + 3, 1, 1);
  ucg.drawBox(_xPos + 22, _yPos + 3, 1, 1);

  ucg.drawBox(_xPos + 0, _yPos + 4, 1, 3);
  ucg.drawBox(_xPos + 23, _yPos + 4, 1, 3);

  ucg.drawBox(_xPos + 1, _yPos + 7, 1, 1);
  ucg.drawBox(_xPos + 22, _yPos + 7, 1, 1);

  ucg.drawBox(_xPos + 2, _yPos + 8, 2, 1);
  ucg.drawBox(_xPos + 20, _yPos + 8, 2, 1);

  ucg.drawBox(_xPos + 4, _yPos + 9, 4, 1);
  ucg.drawBox(_xPos + 16, _yPos + 9, 4, 1);

  ucg.drawBox(_xPos + 8, _yPos + 10, 8, 1);

  // Coffee
  ucg.setColor(139, 69, 19);
  ucg.drawBox(_xPos + 8, _yPos + 3, 8, 1);
  ucg.drawBox(_xPos + 4, _yPos + 4, 16, 1);
  ucg.drawBox(_xPos + 2, _yPos + 5, 20, 1);
  ucg.drawBox(_xPos + 1, _yPos + 6, 22, 1);
  ucg.drawBox(_xPos + 2, _yPos + 7, 20, 1);
  ucg.drawBox(_xPos + 4, _yPos + 8, 16, 1);
  ucg.drawBox(_xPos + 8, _yPos + 9, 8, 1);

  // Marble
  ucg.setColor(205, 133, 63);
  ucg.drawPixel(_xPos + 8, _yPos + 5);
  ucg.drawPixel(_xPos + 7, _yPos + 5);
  ucg.drawPixel(_xPos + 6, _yPos + 6);
  ucg.drawPixel(_xPos + 7, _yPos + 7);
  ucg.drawPixel(_xPos + 8, _yPos + 7);
  ucg.drawPixel(_xPos + 9, _yPos + 7);
  ucg.drawPixel(_xPos + 10, _yPos + 7);
  ucg.drawPixel(_xPos + 11, _yPos + 8);
  ucg.drawPixel(_xPos + 12, _yPos + 8);
  ucg.drawPixel(_xPos + 13, _yPos + 8);
  ucg.drawPixel(_xPos + 14, _yPos + 7);
  ucg.drawPixel(_xPos + 15, _yPos + 7);
  ucg.drawPixel(_xPos + 16, _yPos + 7);
  ucg.drawPixel(_xPos + 17, _yPos + 6);
  ucg.drawPixel(_xPos + 16, _yPos + 5);
  ucg.drawPixel(_xPos + 14, _yPos + 4);
  ucg.drawPixel(_xPos + 13, _yPos + 4);
  ucg.drawPixel(_xPos + 12, _yPos + 4);

  // 1. ring
  ucg.setColor(255, 255, 255);
  ucg.drawBox(_xPos + 0, _yPos + 7, 1, 5);
  ucg.drawBox(_xPos + 23, _yPos + 7, 1, 5);

  ucg.drawBox(_xPos + 1, _yPos + 8, 1, 5);
  ucg.drawBox(_xPos + 22, _yPos + 8, 1, 5);

  ucg.drawBox(_xPos + 2, _yPos + 9, 2, 5);
  ucg.drawBox(_xPos + 20, _yPos + 9, 2, 5);

  ucg.drawBox(_xPos + 4, _yPos + 10, 4, 5);
  ucg.drawBox(_xPos + 16, _yPos + 10, 4, 5);

  ucg.drawBox(_xPos + 8, _yPos + 11, 8, 5);

  // 2. ring
  ucg.setColor(81, 141, 193);
  ucg.drawBox(_xPos + 0, _yPos + 12, 1, 5);
  ucg.drawBox(_xPos + 23, _yPos + 12, 1, 5);

  ucg.drawBox(_xPos + 1, _yPos + 13, 1, 5);
  ucg.drawBox(_xPos + 22, _yPos + 13, 1, 5);

  ucg.drawBox(_xPos + 2, _yPos + 14, 2, 5);
  ucg.drawBox(_xPos + 20, _yPos + 14, 2, 5);

  ucg.drawBox(_xPos + 4, _yPos + 15, 4, 5);
  ucg.drawBox(_xPos + 16, _yPos + 15, 4, 5);

  ucg.drawBox(_xPos + 8, _yPos + 16, 8, 5);

  // 3. ring
  ucg.setColor(255, 255, 255);
  ucg.drawBox(_xPos + 0, _yPos + 17, 1, 5);
  ucg.drawBox(_xPos + 23, _yPos + 17, 1, 5);

  ucg.drawBox(_xPos + 1, _yPos + 18, 1, 5);
  ucg.drawBox(_xPos + 22, _yPos + 18, 1, 5);

  ucg.drawBox(_xPos + 2, _yPos + 19, 2, 5);
  ucg.drawBox(_xPos + 20, _yPos + 19, 2, 5);

  ucg.drawBox(_xPos + 4, _yPos + 20, 4, 5);
  ucg.drawBox(_xPos + 16, _yPos + 20, 4, 5);

  ucg.drawBox(_xPos + 8, _yPos + 21, 8, 5);

  // 4. ring
  ucg.setColor(81, 141, 193);
  ucg.drawBox(_xPos + 0, _yPos + 22, 1, 5);
  ucg.drawBox(_xPos + 23, _yPos + 22, 1, 5);

  ucg.drawBox(_xPos + 1, _yPos + 23, 1, 5);
  ucg.drawBox(_xPos + 22, _yPos + 23, 1, 5);

  ucg.drawBox(_xPos + 2, _yPos + 24, 2, 5);
  ucg.drawBox(_xPos + 20, _yPos + 24, 2, 5);

  ucg.drawBox(_xPos + 4, _yPos + 25, 4, 5);
  ucg.drawBox(_xPos + 16, _yPos + 25, 4, 5);

  ucg.drawBox(_xPos + 8, _yPos + 26, 8, 5);

  // 5. ring
  ucg.setColor(255, 255, 255);
  ucg.drawBox(_xPos + 0, _yPos + 27, 1, 5);
  ucg.drawBox(_xPos + 23, _yPos + 27, 1, 5);

  ucg.drawBox(_xPos + 1, _yPos + 28, 1, 5);
  ucg.drawBox(_xPos + 22, _yPos + 28, 1, 5);

  ucg.drawBox(_xPos + 2, _yPos + 29, 2, 5);
  ucg.drawBox(_xPos + 20, _yPos + 29, 2, 5);

  ucg.drawBox(_xPos + 4, _yPos + 30, 4, 5);
  ucg.drawBox(_xPos + 16, _yPos + 30, 4, 5);

  ucg.drawBox(_xPos + 8, _yPos + 31, 8, 5);

  // Handle
  ucg.setColor(255, 255, 255);
  ucg.drawBox(_xPos + 24, _yPos + 9, 1, 3);
  ucg.drawBox(_xPos + 24, _yPos + 23, 1, 3);

  ucg.drawBox(_xPos + 25, _yPos + 8, 3, 3);
  ucg.drawBox(_xPos + 25, _yPos + 24, 3, 3);

  ucg.drawBox(_xPos + 28, _yPos + 9, 1, 3);
  ucg.drawBox(_xPos + 28, _yPos + 23, 1, 3);

  ucg.drawBox(_xPos + 29, _yPos + 10, 1, 15);

  ucg.drawBox(_xPos + 30, _yPos + 11, 1, 13);

  drawSteam(_xPos, _yPos, steamState);
}

void resetColor()
{
  ucg.setColor(0, 0, 0, 0);
  ucg.setColor(1, 0, 0, 0);
  ucg.setColor(2, 0, 0, 0);
  ucg.setColor(3, 0, 0, 0);
}

void testBlock()
{
  ucg.setColor(222, 184, 135);
  ucg.drawBox(0, 10, 10, 10);

  ucg.setColor(255, 211, 155);
  ucg.drawBox(15, 10, 10, 10);

  ucg.setColor(139, 115, 85);
  ucg.drawBox(30, 10, 10, 10);

  ucg.setColor(139, 69, 19);
  ucg.drawBox(45, 10, 10, 10); //

  ucg.setColor(91, 58, 41);
  ucg.drawBox(60, 10, 10, 10);

  ucg.setColor(205, 133, 63);
  ucg.drawBox(75, 10, 10, 10);
}

void drawGrinder(uint8_t xPos, uint8_t yPos)
{
  testBlock();

  ucg.setColor(0, 222, 184, 135);
  ucg.setColor(1, 255, 211, 155);
  ucg.setColor(2, 139, 115, 85);
  ucg.setColor(3, 139, 69, 19);
  ucg.drawGradientBox(xPos, yPos, 40, 40);
  resetColor();

  ucg.setColor(91, 58, 41); //dark
  ucg.drawFrame(xPos, yPos, 40, 40);
  ucg.drawFrame(xPos + 1, yPos + 1, 38, 38);
  ucg.drawFrame(xPos + 10, yPos + 10, 20, 20);
  ucg.drawFrame(xPos + 11, yPos + 11, 18, 18);
  ucg.drawBox(xPos + 17, yPos - 6, 6, 6);
}

void drawBean(uint8_t _xPos, uint8_t _yPos)
{
  // Outline
  ucg.setColor(139, 69, 19);
  ucg.drawBox(_xPos + 10, _yPos + 0, 4, 2);
  ucg.drawBox(_xPos + 16, _yPos + 0, 4, 2);

  ucg.drawBox(_xPos + 6, _yPos + 2, 4, 2);
  ucg.drawBox(_xPos + 20, _yPos + 2, 4, 2);

  ucg.drawBox(_xPos + 4, _yPos + 4, 2, 2);
  ucg.drawBox(_xPos + 24, _yPos + 4, 2, 2);

  ucg.drawBox(_xPos + 2, _yPos + 6, 2, 4);
  ucg.drawBox(_xPos + 26, _yPos + 6, 2, 4);

  ucg.drawBox(_xPos + 0, _yPos + 10, 2, 14);
  ucg.drawBox(_xPos + 28, _yPos + 10, 2, 14);

  ucg.drawBox(_xPos + 12, _yPos + 6, 2, 22);
  ucg.drawBox(_xPos + 14, _yPos + 2, 2, 30);
  ucg.drawBox(_xPos + 16, _yPos + 6, 2, 22);

  ucg.drawBox(_xPos + 2, _yPos + 24, 2, 4);
  ucg.drawBox(_xPos + 26, _yPos + 24, 2, 4);

  ucg.drawBox(_xPos + 4, _yPos + 28, 2, 2);
  ucg.drawBox(_xPos + 24, _yPos + 28, 2, 2);

  ucg.drawBox(_xPos + 6, _yPos + 30, 4, 2);
  ucg.drawBox(_xPos + 20, _yPos + 30, 4, 2);

  ucg.drawBox(_xPos + 10, _yPos + 32, 4, 2);
  ucg.drawBox(_xPos + 16, _yPos + 32, 4, 2);

  // Highlight
  ucg.setColor(245, 222, 179);
  ucg.drawBox(_xPos + 6, _yPos + 6, 2, 4);
  ucg.drawBox(_xPos + 4, _yPos + 10, 2, 14);
  ucg.drawBox(_xPos + 6, _yPos + 24, 2, 4);

  ucg.drawBox(_xPos + 18, _yPos + 8, 2, 20);

  // Fill
  ucg.setColor(205, 133, 63);
  ucg.drawBox(_xPos + 2, _yPos + 10, 2, 14);

  ucg.drawBox(_xPos + 4, _yPos + 6, 2, 4);
  ucg.drawBox(_xPos + 4, _yPos + 24, 2, 4);

  ucg.drawBox(_xPos + 6, _yPos + 4, 2, 2);
  ucg.drawBox(_xPos + 6, _yPos + 10, 2, 14);
  ucg.drawBox(_xPos + 6, _yPos + 28, 2, 2);

  ucg.drawBox(_xPos + 8, _yPos + 4, 2, 26);

  ucg.drawBox(_xPos + 10, _yPos + 2, 2, 30);

  ucg.drawBox(_xPos + 12, _yPos + 2, 2, 4);
  ucg.drawBox(_xPos + 12, _yPos + 28, 2, 4);

  ucg.drawBox(_xPos + 16, _yPos + 2, 2, 4);
  ucg.drawBox(_xPos + 16, _yPos + 28, 2, 4);

  ucg.drawBox(_xPos + 18, _yPos + 2, 2, 6);
  ucg.drawBox(_xPos + 18, _yPos + 28, 2, 4);

  ucg.drawBox(_xPos + 20, _yPos + 4, 4, 26);

  ucg.drawBox(_xPos + 24, _yPos + 6, 2, 22);

  ucg.drawBox(_xPos + 26, _yPos + 10, 2, 14);
}

void drawSettingsSaved(uint8_t _xPos, uint8_t _yPos)
{
  ucg.setColor(0, 222, 0);
  ucg.drawCircle(_xPos, _yPos, 18, UCG_DRAW_ALL);
  ucg.drawCircle(_xPos, _yPos, 17, UCG_DRAW_ALL);

  ucg.drawLine(_xPos - 5, _yPos, _xPos, _yPos + 6);
  ucg.drawLine(_xPos, _yPos + 6, _xPos + 6, _yPos - 4);

  ucg.drawLine(_xPos - 6, _yPos, _xPos, _yPos + 7);
  ucg.drawLine(_xPos, _yPos + 7, _xPos + 7, _yPos - 4);
}

void drawSettingsCancelled(uint8_t _xPos, uint8_t _yPos)
{
  ucg.setColor(222, 0, 0);
  ucg.drawCircle(_xPos, _yPos, 18, UCG_DRAW_ALL);
  ucg.drawCircle(_xPos, _yPos, 17, UCG_DRAW_ALL);

  ucg.drawLine(_xPos - 6, _yPos - 6, _xPos + 6, _yPos + 6);

  ucg.drawLine(_xPos - 6, _yPos + 6, _xPos + 6, _yPos - 6);
}

/**************************************************************/
/* PROGRESS                                                   */
/**************************************************************/

void drawProgress(uint8_t timePassed)
{
  ucg.setColor(255, 255, 255);
  ucg.drawBox(0, 0, timePassed, 2);
}

void clearProgress()
{
  ucg.setColor(0, 0, 0);
  ucg.drawBox(0, 0, 132, 10);
}

/**************************************************************/
/* SCREENS                                                    */
/**************************************************************/

void clearHalfBottom()
{
  ucg.setColor(0, 0, 0);
  ucg.drawBox(0, 80, 128, 80);
}

void screenDefault(bool steamState)
{
  ucg.clearScreen();
  drawMug(50, 45, steamState);
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(22, 110);
  ucg.print("COFFEE GRINDER");

  // ucg.setColor(70, 70, 70);
  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(10, 150);
  ucg.print("(c) Arneth Edition");
}

void screenManualGrind()
{
  ucg.clearScreen();
  drawGrinder(45, 45);
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(30, 110);
  ucg.print("MANUAL GRIND");

  ucg.setColor(70, 70, 70);
  ucg.setPrintPos(27, 150);
  ucg.print("Hold to grind");
}

void screenSingleShot()
{
  ucg.clearScreen();
  drawBean(50, 45);
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(30, 110);
  ucg.print("SINGLE SHOT");

  ucg.setColor(70, 70, 70);
  ucg.setPrintPos(25, 150);
  ucg.print("Press to start");
}

void screenDoubleShot()
{
  ucg.clearScreen();
  drawBean(30, 43);
  drawBean(70, 47);
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(30, 110);

  ucg.print("DOUBLE SHOT");

  ucg.setColor(70, 70, 70);
  ucg.setPrintPos(25, 150);
  ucg.print("Press to start");
}

void screenQuickSettings()
{
  clearHalfBottom();
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(40, 110);
  ucg.print("SET TIME");
}

void screenQuickSettingsSaved()
{
  ucg.clearScreen();

  drawSettingsSaved(64, 57);

  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(23, 110);
  ucg.print("SETTINGS SAVED");
}

void screenQuickSettingsCancelled()
{
  ucg.clearScreen();

  drawSettingsCancelled(64, 57);

  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(12, 110);
  ucg.print("SETTINGS CANCELLED");
}

void screenQuickSettingsValue(uint16_t time)
{
  uint8_t centerPos = 0;
  ucg.setColor(0, 0, 0);
  ucg.drawBox(0, 120, 128, 20);

  float seconds = (float)time / 1000;
  if (time < 10000)
  {
    centerPos = (ucg.getWidth() / 2) - 9;
  }
  else if (time >= 10000)
  {
    centerPos = (ucg.getWidth() / 2) - 12;
  }
  ucg.setColor(255, 255, 255);
  ucg.setColor(1, 0, 0, 0);
  ucg.setPrintPos(centerPos, 130);
  ucg.print(seconds, 1);

  ucg.setColor(70, 70, 70);
  ucg.setPrintPos(26, 150);
  ucg.print("Press to save");
}