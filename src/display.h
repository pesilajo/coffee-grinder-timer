#include "Arduino.h"
#include "Ucglib.h"
#include <SPI.h>

#define DISPLAY_RESET 8
#define DISPLAY_CD 9
#define DISPLAY_CS 10

Ucglib_ST7735_18x128x160_HWSPI ucg(DISPLAY_CD, DISPLAY_CS, DISPLAY_RESET);
void drawStepper(uint8_t xPos, uint8_t yPos, uint8_t r, uint8_t actPos);
/**************************************************************/
/* DRAWINGS                                                   */
/**************************************************************/
void drawSteam(uint8_t xPos, uint8_t yPos, bool steamState)
{
  int x, y;
  steamState ? x = y = 6 : x = y = 0;

  //clear
  ucg.setColor(0, 0, 0);
  ucg.drawBox(xPos, yPos - 20, 30, 20);

  ucg.setColor(90, 90, 90);
  ucg.drawBox(xPos + 7 + x, yPos - 20 + y / 2, 2, 2);
  ucg.drawBox(xPos + 9 + x, yPos - 18 + y / 2, 2, 2);
  ucg.drawBox(xPos + 8 + x, yPos - 16 + y / 2, 1, 4);
  ucg.drawBox(xPos + 9 + x, yPos - 12 + y / 2, 2, 4);
  ucg.drawBox(xPos + 8 + x, yPos - 8 + y / 2, 1, 2);

  ucg.setColor(80, 80, 80);
  ucg.drawBox(xPos + 15 - x, yPos - 20, 2, 2);
  ucg.drawBox(xPos + 13 - x, yPos - 18, 2, 4);
  ucg.drawBox(xPos + 15 - x, yPos - 14, 2, 2);
  ucg.drawBox(xPos + 13 - x, yPos - 12, 2, 2);
  ucg.drawBox(xPos + 14 - x, yPos - 10, 1, 2);
  ucg.drawBox(xPos + 13 - x, yPos - 8, 2, 2);
}

void drawMug(uint8_t xPos, uint8_t yPos, bool steamState)
{
  // Top
  ucg.setColor(255, 255, 255);
  ucg.drawBox(xPos + 8, yPos + 0, 8, 1);

  ucg.drawBox(xPos + 4, yPos + 1, 4, 1);
  ucg.drawBox(xPos + 16, yPos + 1, 4, 1);

  ucg.drawBox(xPos + 2, yPos + 2, 2, 1);
  ucg.drawBox(xPos + 20, yPos + 2, 2, 1);

  ucg.drawBox(xPos + 1, yPos + 3, 1, 1);
  ucg.drawBox(xPos + 22, yPos + 3, 1, 1);

  ucg.drawBox(xPos + 0, yPos + 4, 1, 3);
  ucg.drawBox(xPos + 23, yPos + 4, 1, 3);

  ucg.drawBox(xPos + 1, yPos + 7, 1, 1);
  ucg.drawBox(xPos + 22, yPos + 7, 1, 1);

  ucg.drawBox(xPos + 2, yPos + 8, 2, 1);
  ucg.drawBox(xPos + 20, yPos + 8, 2, 1);

  ucg.drawBox(xPos + 4, yPos + 9, 4, 1);
  ucg.drawBox(xPos + 16, yPos + 9, 4, 1);

  ucg.drawBox(xPos + 8, yPos + 10, 8, 1);

  // Coffee
  ucg.setColor(139, 69, 19);
  ucg.drawBox(xPos + 8, yPos + 3, 8, 1);
  ucg.drawBox(xPos + 4, yPos + 4, 16, 1);
  ucg.drawBox(xPos + 2, yPos + 5, 20, 1);
  ucg.drawBox(xPos + 1, yPos + 6, 22, 1);
  ucg.drawBox(xPos + 2, yPos + 7, 20, 1);
  ucg.drawBox(xPos + 4, yPos + 8, 16, 1);
  ucg.drawBox(xPos + 8, yPos + 9, 8, 1);

  // Marble
  ucg.setColor(205, 133, 63);
  ucg.drawPixel(xPos + 8, yPos + 5);
  ucg.drawPixel(xPos + 7, yPos + 5);
  ucg.drawPixel(xPos + 6, yPos + 6);
  ucg.drawPixel(xPos + 7, yPos + 7);
  ucg.drawPixel(xPos + 8, yPos + 7);
  ucg.drawPixel(xPos + 9, yPos + 7);
  ucg.drawPixel(xPos + 10, yPos + 7);
  ucg.drawPixel(xPos + 11, yPos + 8);
  ucg.drawPixel(xPos + 12, yPos + 8);
  ucg.drawPixel(xPos + 13, yPos + 8);
  ucg.drawPixel(xPos + 14, yPos + 7);
  ucg.drawPixel(xPos + 15, yPos + 7);
  ucg.drawPixel(xPos + 16, yPos + 7);
  ucg.drawPixel(xPos + 17, yPos + 6);
  ucg.drawPixel(xPos + 16, yPos + 5);
  ucg.drawPixel(xPos + 14, yPos + 4);
  ucg.drawPixel(xPos + 13, yPos + 4);
  ucg.drawPixel(xPos + 12, yPos + 4);

  // 1. ring
  ucg.setColor(255, 255, 255);
  ucg.drawBox(xPos + 0, yPos + 7, 1, 5);
  ucg.drawBox(xPos + 23, yPos + 7, 1, 5);

  ucg.drawBox(xPos + 1, yPos + 8, 1, 5);
  ucg.drawBox(xPos + 22, yPos + 8, 1, 5);

  ucg.drawBox(xPos + 2, yPos + 9, 2, 5);
  ucg.drawBox(xPos + 20, yPos + 9, 2, 5);

  ucg.drawBox(xPos + 4, yPos + 10, 4, 5);
  ucg.drawBox(xPos + 16, yPos + 10, 4, 5);

  ucg.drawBox(xPos + 8, yPos + 11, 8, 5);

  // 2. ring
  ucg.setColor(81, 141, 193);
  ucg.drawBox(xPos + 0, yPos + 12, 1, 5);
  ucg.drawBox(xPos + 23, yPos + 12, 1, 5);

  ucg.drawBox(xPos + 1, yPos + 13, 1, 5);
  ucg.drawBox(xPos + 22, yPos + 13, 1, 5);

  ucg.drawBox(xPos + 2, yPos + 14, 2, 5);
  ucg.drawBox(xPos + 20, yPos + 14, 2, 5);

  ucg.drawBox(xPos + 4, yPos + 15, 4, 5);
  ucg.drawBox(xPos + 16, yPos + 15, 4, 5);

  ucg.drawBox(xPos + 8, yPos + 16, 8, 5);

  // 3. ring
  ucg.setColor(255, 255, 255);
  ucg.drawBox(xPos + 0, yPos + 17, 1, 5);
  ucg.drawBox(xPos + 23, yPos + 17, 1, 5);

  ucg.drawBox(xPos + 1, yPos + 18, 1, 5);
  ucg.drawBox(xPos + 22, yPos + 18, 1, 5);

  ucg.drawBox(xPos + 2, yPos + 19, 2, 5);
  ucg.drawBox(xPos + 20, yPos + 19, 2, 5);

  ucg.drawBox(xPos + 4, yPos + 20, 4, 5);
  ucg.drawBox(xPos + 16, yPos + 20, 4, 5);

  ucg.drawBox(xPos + 8, yPos + 21, 8, 5);

  // 4. ring
  ucg.setColor(81, 141, 193);
  ucg.drawBox(xPos + 0, yPos + 22, 1, 5);
  ucg.drawBox(xPos + 23, yPos + 22, 1, 5);

  ucg.drawBox(xPos + 1, yPos + 23, 1, 5);
  ucg.drawBox(xPos + 22, yPos + 23, 1, 5);

  ucg.drawBox(xPos + 2, yPos + 24, 2, 5);
  ucg.drawBox(xPos + 20, yPos + 24, 2, 5);

  ucg.drawBox(xPos + 4, yPos + 25, 4, 5);
  ucg.drawBox(xPos + 16, yPos + 25, 4, 5);

  ucg.drawBox(xPos + 8, yPos + 26, 8, 5);

  // 5. ring
  ucg.setColor(255, 255, 255);
  ucg.drawBox(xPos + 0, yPos + 27, 1, 5);
  ucg.drawBox(xPos + 23, yPos + 27, 1, 5);

  ucg.drawBox(xPos + 1, yPos + 28, 1, 5);
  ucg.drawBox(xPos + 22, yPos + 28, 1, 5);

  ucg.drawBox(xPos + 2, yPos + 29, 2, 5);
  ucg.drawBox(xPos + 20, yPos + 29, 2, 5);

  ucg.drawBox(xPos + 4, yPos + 30, 4, 5);
  ucg.drawBox(xPos + 16, yPos + 30, 4, 5);

  ucg.drawBox(xPos + 8, yPos + 31, 8, 5);

  // Handle
  ucg.setColor(255, 255, 255);
  ucg.drawBox(xPos + 24, yPos + 9, 1, 3);
  ucg.drawBox(xPos + 24, yPos + 23, 1, 3);

  ucg.drawBox(xPos + 25, yPos + 8, 3, 3);
  ucg.drawBox(xPos + 25, yPos + 24, 3, 3);

  ucg.drawBox(xPos + 28, yPos + 9, 1, 3);
  ucg.drawBox(xPos + 28, yPos + 23, 1, 3);

  ucg.drawBox(xPos + 29, yPos + 10, 1, 15);

  ucg.drawBox(xPos + 30, yPos + 11, 1, 13);

  drawSteam(xPos, yPos, steamState);
}

void resetColor()
{
  ucg.setColor(0, 0, 0, 0);
  ucg.setColor(1, 0, 0, 0);
  ucg.setColor(2, 0, 0, 0);
  ucg.setColor(3, 0, 0, 0);
}

void drawGrinder(uint8_t xPos, uint8_t yPos)
{
  ucg.setColor(0, 48, 32, 24); //
  ucg.setColor(1, 64, 27, 5);
  ucg.setColor(2, 12, 5, 1);
  ucg.setColor(3, 139, 69, 19);
  ucg.drawGradientBox(xPos, yPos + 7, 40, 28);
  resetColor();

  ucg.setColor(12, 5, 1); //dark
  ucg.drawDisc(xPos + 20, yPos - 20, 20, UCG_DRAW_LOWER_LEFT);
  ucg.drawDisc(xPos + 20, yPos - 20, 20, UCG_DRAW_LOWER_RIGHT);
  ucg.setColor(255, 150, 10); //light
  ucg.drawDisc(xPos + 20, yPos - 20, 18, UCG_DRAW_LOWER_LEFT);
  ucg.drawDisc(xPos + 20, yPos - 20, 18, UCG_DRAW_LOWER_RIGHT); //funnel

  ucg.setColor(255, 255, 255);
  ucg.drawDisc(xPos + 28, yPos - 13, 3, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 24, yPos - 7, 1, UCG_DRAW_ALL);

  ucg.setColor(255, 150, 20);
  // ucg.setColor(255, 0, 0);
  ucg.drawDisc(xPos + 6, yPos - 15, 2, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 10, yPos - 13, 4, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 12, yPos - 9, 3, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 16, yPos - 6, 2, UCG_DRAW_ALL);

  ucg.setColor(170, 170, 50);
  ucg.drawDisc(xPos + 6, yPos - 15, 1, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 10, yPos - 13, 2, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 12, yPos - 9, 2, UCG_DRAW_ALL);
  ucg.drawDisc(xPos + 16, yPos - 6, 1, UCG_DRAW_ALL);

  ucg.setColor(12, 5, 1); //dark

  ucg.drawFrame(xPos, yPos + 6, 40, 29);
  ucg.drawFrame(xPos + 1, yPos + 7, 38, 27); //frame

  ucg.drawBox(xPos - 5, yPos + 36, 50, 5); //bottom

  ucg.drawFrame(xPos + 7, yPos + 11, 26, 18);
  ucg.drawFrame(xPos + 8, yPos + 12, 24, 16); //drawer

  ucg.drawDisc(xPos + 20, yPos + 20, 3, UCG_DRAW_ALL); //drawer button

  ucg.drawBox(xPos, yPos - 20, 40, 2); //funnel top

  ucg.drawBox(xPos - 5, yPos, 50, 5); //top

  ucg.drawBox(xPos + 17, yPos - 32, 6, 5);
  ucg.drawBox(xPos + 13, yPos - 26, 14, 5);
  ucg.drawBox(xPos + 20, yPos - 31, 33, 2);
  ucg.drawBox(xPos + 52, yPos - 40, 2, 10); //Crank
  ucg.setColor(150, 150, 20);
  ucg.drawBox(xPos + 51, yPos - 42, 4, 8);

  ucg.setColor(0, 0, 0);
  ucg.drawLine(xPos - 5, yPos, xPos + 60, yPos);
}

void drawBean(uint8_t xPos, uint8_t yPos)
{
  // Outline
  ucg.setColor(139, 69, 19);
  ucg.drawBox(xPos + 10, yPos + 0, 4, 2);
  ucg.drawBox(xPos + 16, yPos + 0, 4, 2);

  ucg.drawBox(xPos + 6, yPos + 2, 4, 2);
  ucg.drawBox(xPos + 20, yPos + 2, 4, 2);

  ucg.drawBox(xPos + 4, yPos + 4, 2, 2);
  ucg.drawBox(xPos + 24, yPos + 4, 2, 2);

  ucg.drawBox(xPos + 2, yPos + 6, 2, 4);
  ucg.drawBox(xPos + 26, yPos + 6, 2, 4);

  ucg.drawBox(xPos + 0, yPos + 10, 2, 14);
  ucg.drawBox(xPos + 28, yPos + 10, 2, 14);

  ucg.drawBox(xPos + 12, yPos + 6, 2, 22);
  ucg.drawBox(xPos + 14, yPos + 2, 2, 30);
  ucg.drawBox(xPos + 16, yPos + 6, 2, 22);

  ucg.drawBox(xPos + 2, yPos + 24, 2, 4);
  ucg.drawBox(xPos + 26, yPos + 24, 2, 4);

  ucg.drawBox(xPos + 4, yPos + 28, 2, 2);
  ucg.drawBox(xPos + 24, yPos + 28, 2, 2);

  ucg.drawBox(xPos + 6, yPos + 30, 4, 2);
  ucg.drawBox(xPos + 20, yPos + 30, 4, 2);

  ucg.drawBox(xPos + 10, yPos + 32, 4, 2);
  ucg.drawBox(xPos + 16, yPos + 32, 4, 2);

  // Highlight
  ucg.setColor(245, 222, 179);
  ucg.drawBox(xPos + 6, yPos + 6, 2, 4);
  ucg.drawBox(xPos + 4, yPos + 10, 2, 14);
  ucg.drawBox(xPos + 6, yPos + 24, 2, 4);

  ucg.drawBox(xPos + 18, yPos + 8, 2, 20);

  // Fill
  ucg.setColor(205, 133, 63);
  ucg.drawBox(xPos + 2, yPos + 10, 2, 14);

  ucg.drawBox(xPos + 4, yPos + 6, 2, 4);
  ucg.drawBox(xPos + 4, yPos + 24, 2, 4);

  ucg.drawBox(xPos + 6, yPos + 4, 2, 2);
  ucg.drawBox(xPos + 6, yPos + 10, 2, 14);
  ucg.drawBox(xPos + 6, yPos + 28, 2, 2);

  ucg.drawBox(xPos + 8, yPos + 4, 2, 26);

  ucg.drawBox(xPos + 10, yPos + 2, 2, 30);

  ucg.drawBox(xPos + 12, yPos + 2, 2, 4);
  ucg.drawBox(xPos + 12, yPos + 28, 2, 4);

  ucg.drawBox(xPos + 16, yPos + 2, 2, 4);
  ucg.drawBox(xPos + 16, yPos + 28, 2, 4);

  ucg.drawBox(xPos + 18, yPos + 2, 2, 6);
  ucg.drawBox(xPos + 18, yPos + 28, 2, 4);

  ucg.drawBox(xPos + 20, yPos + 4, 4, 26);

  ucg.drawBox(xPos + 24, yPos + 6, 2, 22);

  ucg.drawBox(xPos + 26, yPos + 10, 2, 14);
}

void drawSettingsSaved(uint8_t xPos, uint8_t yPos)
{
  ucg.setColor(0, 222, 0);
  ucg.drawCircle(xPos, yPos, 18, UCG_DRAW_ALL);
  ucg.drawCircle(xPos, yPos, 17, UCG_DRAW_ALL);

  ucg.drawLine(xPos - 5, yPos, xPos, yPos + 6);
  ucg.drawLine(xPos, yPos + 6, xPos + 6, yPos - 4);

  ucg.drawLine(xPos - 6, yPos, xPos, yPos + 7);
  ucg.drawLine(xPos, yPos + 7, xPos + 7, yPos - 4);
}

void drawSettingsCancelled(uint8_t xPos, uint8_t yPos)
{
  ucg.setColor(222, 0, 0);
  ucg.drawCircle(xPos, yPos, 18, UCG_DRAW_ALL);
  ucg.drawCircle(xPos, yPos, 17, UCG_DRAW_ALL);

  ucg.drawLine(xPos - 6, yPos - 6, xPos + 6, yPos + 6);

  ucg.drawLine(xPos - 6, yPos + 6, xPos + 6, yPos - 6);
}

/**************************************************************/
/* PROGRESS                                                   */
/**************************************************************/

void drawProgress(uint8_t timePassed)
{
  ucg.setColor(255, 255, 255);
  ucg.drawBox(0, 0, timePassed, 5);
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
  ucg.drawBox(1, 81, 126, 78);

  ucg.setColor(255, 0, 0);
  ucg.drawFrame(0, 80, 128, 80);

}

void screenDefault(bool steamState, uint8_t currentMenu)
{
  ucg.clearScreen();
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(22, 20);
  ucg.print("COFFEE GRINDER");

  drawMug(50, 65, steamState);

  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(10, 130);
  ucg.print("(c) Arneth Edition");

  drawStepper(42, 150, 4, currentMenu);
}

void screenManualGrind(uint8_t currentMenu)
{
  ucg.clearScreen();
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(30, 20);
  ucg.print("MANUAL GRIND");

  drawGrinder(45, 70);

  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(27, 130);
  ucg.print("Hold to grind");

  drawStepper(42, 150, 4, currentMenu);
}

void screenSingleShot(uint8_t currentMenu, uint16_t time)
{
  ucg.clearScreen();

  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(30, 20);
  ucg.print("SINGLE SHOT");

  drawBean(50, 50);

  float seconds = (float)time / 1000;
  ucg.setPrintPos(45, 110);
  ucg.setColor(0, 255, 0);
  ucg.setFont(ucg_font_9x18B_mf);
  ucg.print(seconds, 1);
  ucg.print(" s");
  ucg.setFont(ucg_font_6x10_tr);


  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(25, 130);
  ucg.print("Press to start");

  drawStepper(42, 150, 4, currentMenu);
}

void screenDoubleShot(uint8_t currentMenu, uint16_t time)
{
  ucg.clearScreen();
  ucg.setFont(ucg_font_6x10_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(30, 20);
  ucg.print("DOUBLE SHOT");

  drawBean(30, 50);
  drawBean(70, 54);

   float seconds = (float)time / 1000;
  ucg.setPrintPos(40, 110);
  ucg.setColor(0, 255, 0);
  ucg.setFont(ucg_font_9x18B_mf);
  ucg.print(seconds, 1);
  ucg.print(" s");
  ucg.setFont(ucg_font_6x10_tr);

  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(25, 130);
  ucg.print("Press to start");

  drawStepper(42, 150, 4, currentMenu);
}

void drawStepper(uint8_t xPos, uint8_t yPos, uint8_t r, uint8_t actPos)
{
  ucg.setColor(255, 255, 255);

  ucg.drawCircle(xPos, yPos, r, UCG_DRAW_ALL);
  ucg.drawCircle(xPos + 15, yPos, r, UCG_DRAW_ALL);
  ucg.drawCircle(xPos + 30, yPos, r, UCG_DRAW_ALL);
  ucg.drawCircle(xPos + 45, yPos, r, UCG_DRAW_ALL);

  switch (actPos)
  {
  case 0:
    ucg.drawDisc(xPos, yPos, r, UCG_DRAW_ALL);
    break;
  case 1:
    ucg.drawDisc(xPos + 15, yPos, r, UCG_DRAW_ALL);
    break;
  case 2:
    ucg.drawDisc(xPos + 30, yPos, r, UCG_DRAW_ALL);
    break;
  case 3:
    ucg.drawDisc(xPos + 45, yPos, r, UCG_DRAW_ALL);
    break;
  default:
    break;
  }
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
  ucg.setPrintPos(centerPos, 130);
  ucg.print(seconds, 1);

  ucg.setColor(255, 0, 0);
  ucg.setPrintPos(26, 150);
  ucg.print("Press to save");
}