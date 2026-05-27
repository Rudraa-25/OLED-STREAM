/*
  OLED-STREAM: Main Firmware for Xiao ESP32-S3
  
  Hardware: 
  - Microcontroller: Xiao ESP32-S3
  - Display: 0.96" SSD1306 OLED (128x64)
  
  CORRECT I2C Pinout for Xiao ESP32-S3:
  - SDA: GPIO 5 (D4 on board)
  - SCL: GPIO 6 (D5 on board)
  - Address: 0x3C
*/

#include "OLEDManager.h"

// Global OLED manager instance
OLEDManager oledManager;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  delay(500);
  
  Serial.println("\n\n╔════════════════════════════════════╗");
  Serial.println("║   OLED-STREAM Starting             ║");
  Serial.println("║   Xiao ESP32-S3 + 0.96\" OLED       ║");
  Serial.println("╚════════════════════════════════════╝");
  Serial.println();
  
  Serial.println("I2C Configuration:");
  Serial.println("  SDA: GPIO 5 (D4)");
  Serial.println("  SCL: GPIO 6 (D5)");
  Serial.println("  Freq: 400kHz");
  Serial.println("  Address: 0x3C");
  Serial.println();
  Serial.println("Initializing OLED Display...");
  
  // Initialize OLED display
  if (!oledManager.begin()) {
    Serial.println("✗ OLED initialization FAILED!");
    Serial.println("Please check:");
    Serial.println("  1. Wiring connections (SDA, SCL)");
    Serial.println("  2. Pull-up resistors (4.7k ohm)");
    Serial.println("  3. OLED I2C address");
    while (1) {
      delay(1000);
    }
  }
  
  Serial.println("✓ OLED initialized successfully!");
  Serial.println();
  
  // Display startup message
  oledManager.displayMessage("Xiao ESP32-S3\n0.96 OLED Ready!");
  delay(2000);
}

void loop() {
  // Test 1: Show connecting animation
  Serial.println("[1/3] Showing connection animation...");
  oledManager.showConnectingAnimation();
  delay(2000);
  
  // Test 2: Show playing animation
  Serial.println("[2/3] Showing playback animation...");
  oledManager.showPlayingAnimation();
  delay(2000);
  
  // Test 3: Display FPS and test pattern
  Serial.println("[3/3] Displaying FPS info...");
  char buffer[32];
  sprintf(buffer, "FPS: %d", oledManager.getFPS());
  oledManager.displayMessage(buffer);
  
  Serial.print("Current FPS: ");
  Serial.println(oledManager.getFPS());
  delay(2000);
  
  // Test 4: Clear display
  Serial.println("Clearing display...");
  oledManager.clear();
  delay(500);
}
