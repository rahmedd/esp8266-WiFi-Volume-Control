
# esp8266 Volume Control

This is a highly impractical means of wirelessly controlling volume in windows using a Potentiometer to emulate analog volume control. The latency is fairly low, and can be improved slightly by using a C++ UDP server.

This can also be used to hide the windows 8/10 OSD popup!

All credits go to the original author of the ChangeVolume function used in [volctrl.exe](https://github.com/rahmedd/Windows-Volume-Control/releases), Sayyed Mostafa Hashemi [from codeproject.com](https://www.codeproject.com/Tips/233484/Change-Master-Volume-in-Visual-Cplusplus)

### Parts & Pin out (for NodeMCU)
esp8266 dev board

B10K Potentiometer (linear pot)
- A0 - Output
- 3V3 - VCC
- GND - GND

1602 i2c LCD (optional)
- D1 - SCL
- D2 - SDA
- 3V3 - VCC
- GND - GND
	



### Dependencies
[Arduino i2c display library](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library) - You must install from this repo

[Windows Volume Control tool](https://github.com/rahmedd/Windows-Volume-Control/releases)

## Usage
1. [volctrl.exe](https://github.com/rahmedd/Windows-Volume-Control/releases) and newvolserver.py **must** be within the same folder.
2. Configure newvolserver.py on host PC using the host's IP and port and run using python 3.5+ (I'm using 3.7)
3. Configure espvolclient.ino with your WiFi's SSID and password and Upload.

### Troubleshooting
 - If you're encountering port errors on the server, the port is probably in use. Try changing the port configured on both the board and server.

- If the display is glitched or blank on boot and resetting isn't helping, try unplugging and plugging it back in. (reset doesn't usually resolve this issue)

- If you're having connectivity issues, you can debug the WiFi status with or without the display by using the serial console.
