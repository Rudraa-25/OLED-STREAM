#ifndef OLEDMANAGER_H
#define OLEDMANAGER_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define FRAME_BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 8)

// Xiao ESP32-S3 I2C Pins
#define I2C_SDA 4
#define I2C_SCL 5

class OLEDManager {
  private:
    Adafruit_SSD1306 display;
    uint8_t frameBuffer[FRAME_BUFFER_SIZE];
    unsigned long lastFrameTime;
    uint16_t currentFPS;

  public:
    OLEDManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
      memset(frameBuffer, 0, FRAME_BUFFER_SIZE);
      lastFrameTime = 0;
      currentFPS = 0;
    }
    
    // Initialize OLED display
    bool begin() {
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
    
    // Display frame from buffer
    void displayFrame(const uint8_t* buffer) {
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
    
    // Display text message
    void displayMessage(const char* message) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println(message);
      display.display();
    }
    
    // Show BLE connecting animation
    void showConnectingAnimation() {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20, 20);
      display.println("BLE Connecting");
      display.setCursor(30, 40);
      display.println("...");
      display.display();
    }
    
    // Show playing animation
    void showPlayingAnimation() {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(20, 20);
      display.println("Playing...");
      display.display();
    }
    
    // Clear display
    void clear() {
      memset(frameBuffer, 0, FRAME_BUFFER_SIZE);
      display.clearDisplay();
      display.display();
    }
    
    // Update display
    void update() {
      display.display();
    }
    
    // Get current FPS
    uint16_t getFPS() const { return currentFPS; }
    
    // Get display reference
    Adafruit_SSD1306& getDisplay() { return display; }
};

#endif // OLEDMANAGER_H
