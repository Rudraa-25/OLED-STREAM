# OLED-STREAM

A real-time OLED display streaming application for Xiao ESP32-S3 with 0.96" SSD1306 OLED display.

## Hardware Requirements

- **Microcontroller:** Seeed Xiao ESP32-S3
- **Display:** 0.96" SSD1306 OLED (128x64 pixels)
- **Interface:** I2C (SDA: GPIO 4, SCL: GPIO 5)
- **Display Address:** 0x3C

## Hardware Connections

```
Xiao ESP32-S3     0.96" OLED
─────────────────────────────
GND       ────────  GND
3.3V      ────────  VCC
GPIO 4    ────────  SDA
GPIO 5    ────────  SCL
```

## Software Setup

### 1. Install PlatformIO
- Download [Visual Studio Code](https://code.visualstudio.com/)
- Install PlatformIO extension
- Restart VS Code

### 2. Clone Repository
```bash
git clone https://github.com/Rudraa-25/OLED-STREAM.git
cd OLED-STREAM
```

### 3. Configure Serial Port
Edit `platformio.ini` and set your serial port:
- **Windows:** `COM3` (or check Device Manager)
- **Linux:** `/dev/ttyACM0` or `/dev/ttyUSB0`
- **macOS:** `/dev/cu.usbmodem14201`

```ini
upload_port = /dev/ttyACM0  ; Change this to your port
```

### 4. Build & Upload
```bash
# Build firmware
platformio run

# Upload to device
platformio run --target upload

# Open serial monitor
platformio device monitor
```

## Project Structure

```
OLED-STREAM/
├── firmware/
│   ├── main.ino              # Main sketch
│   ├── OLEDManager.h         # OLED manager header
│   └── OLEDManager.cpp       # OLED manager implementation
├── web/                      # Web interface (TypeScript)
├── platformio.ini            # PlatformIO configuration
└── README.md                 # This file
```

## Features

- ✅ SSD1306 OLED display driver
- ✅ Real-time frame buffering
- ✅ BLE connectivity animations
- ✅ Playback status display
- ✅ FPS monitoring
- ✅ Serial debugging

## Troubleshooting

### ❌ Error: "OLEDManager.h: No such file or directory"
**Solution:** Ensure all files are in the correct directory structure:
```
firmware/
├── main.ino
├── OLEDManager.h      ← Must exist
└── OLEDManager.cpp
```

### ❌ Error: "Board not found"
**Solution:** 
1. Install Xiao ESP32-S3 board in PlatformIO
2. Edit `platformio.ini` and verify board name
3. Check USB drivers are installed

### ❌ OLED not displaying
**Solution:**
1. Check I2C connections (SDA/SCL pins)
2. Verify OLED I2C address (should be 0x3C)
3. Test I2C communication:
```bash
platformio device monitor
# Look for "OLED initialized successfully" message
```

### ❌ Upload fails
**Solution:**
1. Hold BOOT button on Xiao ESP32-S3
2. Click Upload in PlatformIO
3. Release BOOT button when upload starts
4. Or update `platformio.ini` with higher upload timeout

## Dependencies

| Library | Version | Purpose |
|---------|---------|---------|
| Adafruit SSD1306 | ≥2.5.7 | OLED driver |
| Adafruit GFX | ≥1.11.9 | Graphics library |
| Wire | ≥1.0 | I2C communication |

## Serial Output Example

```
=== OLED-STREAM Starting ===
Hardware: Xiao ESP32-S3 + 0.96" OLED
Initializing OLED Display...
✓ OLED initialized successfully
Showing connection animation...
Current FPS: 12
```

## Next Steps

- [ ] Implement BLE connectivity
- [ ] Add web dashboard for control
- [ ] Implement streaming protocol
- [ ] Add animation library

## License

MIT License

## Author

[@Rudraa-25](https://github.com/Rudraa-25)
