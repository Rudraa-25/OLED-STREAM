// OLED Display Manager Implementation
#include "OLEDManager.h"
#include <Wire.h>

OLEDManager::OLEDManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
  memset(frameBuffer, 0, FRAME_BUFFER_SIZE);
  lastFrameTime = 0;
  currentFPS = 0;
}

bool OLEDManager::begin() {
  Wire.begin(I2C_SDA, I2C_SCL);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("SSD1306 allocation failed");
    return false;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("OLED Studio");
  display.println("Initializing...");
  display.display();

  return true;
}

void OLEDManager::displayFrame(const uint8_t* buffer) {
  if (!buffer) return;

  memcpy(frameBuffer, buffer, FRAME_BUFFER_SIZE);
  
  display.clearDisplay();
  
  // Draw frame buffer directly
  for (uint16_t i = 0; i < FRAME_BUFFER_SIZE; i++) {
    uint8_t byte = buffer[i];
    
    for (uint8_t bit = 0; bit < 8; bit++) {
      if (byte & (1 << bit)) {
        uint16_t pixelIndex = i * 8 + bit;
        uint8_t x = pixelIndex % SCREEN_WIDTH;
        uint8_t y = pixelIndex / SCREEN_WIDTH;
        display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
  }

  display.display();

  // Calculate FPS
  unsigned long now = millis();
  if (lastFrameTime > 0) {
    unsigned long frameDelta = now - lastFrameTime;
    if (frameDelta > 0) {
      currentFPS = 1000 / frameDelta;
    }
  }
  lastFrameTime = now;
}

void OLEDManager::displayMessage(const char* message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}

void OLEDManager::showConnectingAnimation() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.println("BLE Connecting");
  display.setCursor(30, 40);
  display.println("...");
  display.display();
}

void OLEDManager::showPlayingAnimation() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.println("Playing...");
  display.display();
}

void OLEDManager::clear() {
  memset(frameBuffer, 0, FRAME_BUFFER_SIZE);
  display.clearDisplay();
  display.display();
}

void OLEDManager::update() {
  display.display();
}
