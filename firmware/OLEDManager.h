#ifndef OLEDMANAGER_H
#define OLEDMANAGER_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

// OLED Display Configuration - 0.96" SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// ╔══════════════════════════════════════════════════════════╗
// ║  CORRECT I2C Pinout for Xiao ESP32-S3                   ║
// ║  SDA: GPIO 5  (labeled as D4 on Xiao board)             ║
// ║  SCL: GPIO 6  (labeled as D5 on Xiao board)             ║
// ╚══════════════════════════════════════════════════════════╝
#define I2C_SDA 5     // GPIO 5 - D4
#define I2C_SCL 6     // GPIO 6 - D5
#define I2C_FREQ 400000  // 400kHz standard I2C frequency

#define FRAME_BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 8)

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
    
    // Initialize OLED display with correct I2C configuration
    bool begin() {
      // Initialize I2C with correct pins for Xiao ESP32-S3
      Serial.println("Initializing I2C...");
      Wire.begin(I2C_SDA, I2C_SCL, I2C_FREQ);
      delay(200);
      
      Serial.println("Probing OLED at address 0x3C...");
      
      // Try to initialize display
      if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("✗ ERROR: SSD1306 not responding at 0x3C");
        Serial.println();
        Serial.println("Troubleshooting:");
        Serial.println("1. Check SDA is connected to GPIO 5 (D4)");
        Serial.println("2. Check SCL is connected to GPIO 6 (D5)");
        Serial.println("3. Add 4.7kΩ pull-up resistors to SDA and SCL");
        Serial.println("4. Verify OLED I2C address with scanner below:");
        Serial.println();
        
        // Scan I2C bus
        scanI2C();
        return false;
      }
    
      Serial.println("✓ SSD1306 OLED found at address 0x3C");
      
      // Clear and display test
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println("Xiao ESP32-S3");
      display.println("OLED Init OK!");
      display.println();
      display.println("GPIO5(SDA)<->GPIO6(SCL)");
      display.display();
      delay(500);
    
      return true;
    }
    
    // I2C Scanner for debugging connection issues
    void scanI2C() {
      byte error, address;
      int nDevices = 0;
      
      Serial.println("╔═══════════════════════════════╗");
      Serial.println("║  I2C Device Scanner           ║");
      Serial.println("╚═══════════════════════════════╝");
      
      for(address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if (error == 0) {
          Serial.print("✓ Found I2C device at: 0x");
          if (address < 16) Serial.print("0");
          Serial.println(address, HEX);
          nDevices++;
        }
      }
      
      Serial.println();
      if (nDevices == 0) {
        Serial.println("✗ NO I2C DEVICES FOUND!");
        Serial.println("Check your I2C connections!");
      } else {
        Serial.print("✓ Found ");
        Serial.print(nDevices);
        Serial.println(" I2C device(s)");
      }
      Serial.println();
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
      display.println("Connecting...");
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
