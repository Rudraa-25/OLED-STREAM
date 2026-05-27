/*
  OLED-STREAM: Main Firmware for Xiao ESP32-S3
  Hardware: Xiao ESP32-S3 + 0.96" SSD1306 OLED Display
  
  I2C Pins:
  - SDA: GPIO 4
  - SCL: GPIO 5
  - OLED Address: 0x3C
*/

#include "OLEDManager.h"

// Global OLED manager instance
OLEDManager oledManager;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n\n=== OLED-STREAM Starting ===");
  Serial.println("Hardware: Xiao ESP32-S3 + 0.96\" OLED");
  Serial.println("Initializing OLED Display...");
  
  // Initialize OLED display
  if (!oledManager.begin()) {
    Serial.println("ERROR: OLED initialization failed!");
    while (1) {
      delay(100); // Halt if OLED fails
    }
  }
  
  Serial.println("✓ OLED initialized successfully");
  
  // Display startup message
  oledManager.displayMessage("OLED-STREAM Ready\nWaiting for input...");
  delay(2000);
}

void loop() {
  // Show connecting animation
  Serial.println("Showing connection animation...");
  oledManager.showConnectingAnimation();
  delay(1000);
  
  // Show playing animation
  Serial.println("Showing playback animation...");
  oledManager.showPlayingAnimation();
  delay(1000);
  
  // Display FPS info
  char fpsBuffer[32];
  sprintf(fpsBuffer, "FPS: %d", oledManager.getFPS());
  oledManager.displayMessage(fpsBuffer);
  
  Serial.print("Current FPS: ");
  Serial.println(oledManager.getFPS());
  
  delay(500);
}
