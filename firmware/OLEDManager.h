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
    OLEDManager();
    
    // Initialize OLED display
    bool begin();
    
    // Display frame from buffer
    void displayFrame(const uint8_t* buffer);
    
    // Display text message
    void displayMessage(const char* message);
    
    // Show BLE connecting animation
    void showConnectingAnimation();
    
    // Show playing animation
    void showPlayingAnimation();
    
    // Clear display
    void clear();
    
    // Update display
    void update();
    
    // Get current FPS
    uint16_t getFPS() const { return currentFPS; }
    
    // Get display reference
    Adafruit_SSD1306& getDisplay() { return display; }
};

#endif // OLEDMANAGER_H
