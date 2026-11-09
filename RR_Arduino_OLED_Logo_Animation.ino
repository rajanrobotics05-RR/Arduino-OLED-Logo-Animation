/*
* Created by Balaji for Rajan Robotics
* Rajan Robotics
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // Change to 64 if using a 128x64 display

#define OLED_RESET     -1   // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Use 0x3D if 0x3C stays blank
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Custom 32x32 Bitmap of the Rajan Robotics Gear + 'R' Emblem
// Saved in PROGMEM to preserve Arduino RAM
#define LOGO_W 32
#define LOGO_H 32

static const unsigned char PROGMEM rajan_logo_bmp[] = {
  0x00, 0x00, 0x00, 0x00, // ................................
  0x00, 0x00, 0x00, 0x00, // ................................
  0x00, 0x06, 0x3F, 0xE0, // .....##...#########.............
  0x00, 0x1E, 0x7F, 0xF8, // ....####.###########............
  0x00, 0x1F, 0x7F, 0xFC, // ....#####.###########...........
  0x00, 0x7E, 0x7C, 0x3E, // ..######..#####.....#####.......
  0x00, 0xFC, 0x00, 0x1E, // .######............####.........
  0x00, 0xF8, 0x00, 0x0F, // .#####..............####........
  0x03, 0xF8, 0x00, 0x0F, // #######.............####........
  0x03, 0xF0, 0x00, 0x0F, // ######..............####........
  0x01, 0xF0, 0x00, 0x0F, // .#####..............####........
  0x07, 0xF0, 0x00, 0x1E, // #######............####.........
  0x07, 0xE0, 0x00, 0x3E, // ######............#####.........
  0x03, 0xE0, 0x07, 0xFC, // .#####..........#########.......
  0x03, 0xE0, 0x0F, 0xF8, // .#####.........#########........
  0x07, 0xE0, 0x07, 0xF0, // ######..........#######.........
  0x07, 0xF0, 0x01, 0xF8, // #######..........######.........
  0x01, 0xF0, 0x00, 0xFC, // .#####............######........
  0x03, 0xF8, 0x00, 0x7E, // #######............######.......
  0x03, 0xFC, 0x00, 0x3F, // ########............######......
  0x00, 0xFE, 0x00, 0x1F, // .#######.............#####......
  0x00, 0xFF, 0x00, 0x0F, // .########.............####......
  0x00, 0x3F, 0x80, 0x0F, // ...#######............####......
  0x00, 0x3F, 0xC0, 0x07, // ...########............###......
  0x00, 0x0F, 0xE0, 0x00, // .....#######....................
  0x00, 0x07, 0xF0, 0x00, // ......#######...................
  0x00, 0x01, 0xF8, 0x00, // ........######..................
  0x00, 0x00, 0x7C, 0x00, // ..........#####.................
  0x00, 0x00, 0x00, 0x00, // ................................
  0x00, 0x00, 0x00, 0x00, // ................................
  0x00, 0x00, 0x00, 0x00, // ................................
  0x00, 0x00, 0x00, 0x00  // ................................
};

void setup() {
  Serial.begin(9600);
  delay(300);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

}

void loop() { 
  // STEP 1: 5-Second Countdown (Exact 5000ms)
  runCountdown(3);

  // STEP 2: 5-Second Robotics Animation Sequence (Exact 5000ms)
  runFiveSecAnimation();

  // STEP 3: Reveal & Hold the Rajan Robotics Logo
  showRajanRoboticsLogo();
  delay(3000);
  display.clearDisplay();
  delay(1000);
  
}

// ---------------------------------------------------------
// STEP 1: 5-Second Countdown with Progress Bar (5000 ms)
// ---------------------------------------------------------
void runCountdown(int seconds) {
  for (int i = seconds; i >= 1; i--) {
    // 20 frames per second (50ms each) = 1000ms per number
    for (int step = 0; step < 20; step++) {
      display.clearDisplay();

      // Draw outer frame
      display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);

      // Draw large centered countdown digit
      display.setTextSize(3);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(56, 4);
      display.print(i);

      // Smooth shrinking timer bar at the bottom
      int barWidth = map(step, 0, 19, 120, 0);
      display.fillRect(4, 28, barWidth, 2, SSD1306_WHITE);

      display.display();
      delay(50);
    }
  }
}

// ---------------------------------------------------------
// STEP 2: 5-Second Robotics Animation (5000 ms total)
// ---------------------------------------------------------
void runFiveSecAnimation() {
  int centerY = display.height() / 2;

  // Part A: Expressive Robot Eyes (3000 ms)
  // 1. Eyes Open (900 ms)
  display.clearDisplay();
  display.fillRoundRect(30, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.fillRoundRect(76, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.display();
  delay(900);

  // 2. Blink (200 ms)
  display.clearDisplay();
  display.fillRect(30, centerY - 1, 22, 3, SSD1306_WHITE);
  display.fillRect(76, centerY - 1, 22, 3, SSD1306_WHITE);
  display.display();
  delay(200);

  // 3. Look Right (700 ms)
  display.clearDisplay();
  display.fillRoundRect(40, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.fillRoundRect(86, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.display();
  delay(700);

  // 4. Look Left (700 ms)
  display.clearDisplay();
  display.fillRoundRect(20, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.fillRoundRect(66, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.display();
  delay(700);

  // 5. Center & Blink (500 ms)
  display.clearDisplay();
  display.fillRoundRect(30, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.fillRoundRect(76, centerY - 8, 22, 16, 4, SSD1306_WHITE);
  display.display();
  delay(500);

  // Part B: Fast LiDAR / Sensor Scan Sweep (2000 ms)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 1);
  display.print(F("PRACTICAL LEARNING"));//Practical Learn
  display.display();

  // 32 steps * 35ms = ~1120ms sweep
  for (int x = 0; x < display.width(); x += 4) {
    display.drawLine(display.width() / 2, display.height() - 1, x, 11, SSD1306_WHITE);
    display.display();
    delay(35);
  }
  delay(880); // Hold completed scan to complete exact 5000ms block
}

// ---------------------------------------------------------
// STEP 3: Rajan Robotics Brand Logo Reveal
// ---------------------------------------------------------
void showRajanRoboticsLogo() {
  display.clearDisplay();

  // Draw the Gear + 'R' Emblem on the left (32x32)
  display.drawBitmap(2, 0, rajan_logo_bmp, LOGO_W, LOGO_H, SSD1306_WHITE);

  // Draw "Rajan" and "Robotics" cleanly on the right
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(40, 2);
  display.println(F("RAJAN"));

  display.setCursor(40, 12);
  display.println(F("ROBOTICS"));

  // Draw divider line and "Vision to Reality" tagline
  display.drawFastHLine(40, 22, 84, SSD1306_WHITE);
  display.setCursor(40, 24);
  display.println(F("Vision2Reality"));

  display.display();
  delay(600);

  // Highlight pulse (invert display briefly for Reel punch)
  display.invertDisplay(true);
  delay(250);
  display.invertDisplay(false);
}
