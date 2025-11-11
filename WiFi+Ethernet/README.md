# esp-idf-dual-http-server
Dual HTTP server using WiFi interface and Ethernet interface.   

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-dual-http-server
cd esp-idf-dual-http-server/WiFi+Ethernet
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

# Hardware requirements
- For ESP32   
	LAN8720 RMII PHY or W5500 SPI PHY.   
	![Image](https://github.com/user-attachments/assets/c9d50275-d897-4df8-86dd-f4cbaaa27ab2)
	![Image](https://github.com/user-attachments/assets/b8bc8403-5a6f-44da-b6d9-17e472a77ce7)

	You can use WT32-ETH01 development board.   
	WT32-ETH01 is a development board that integrates ESP32 and LAN8720A.   
	![Image](https://github.com/user-attachments/assets/8886f354-4121-4617-8e10-c6552442d85c)

- For the ESP32S series   
	W5500 SPI PHY.   
	![Image](https://github.com/user-attachments/assets/fb138a71-2f3e-4f7e-a32b-6e7de3b448a2)   
	![Image](https://github.com/user-attachments/assets/20fabd0f-3222-4bc4-8c99-f9773934d00d)   

- For the ESP32C series   
	W5500 SPI PHY.   
	![Image](https://github.com/user-attachments/assets/9d5ff23a-8152-41bc-85cb-57d21ad7da1f)

# Configuration for HTTP Server   
![Image](https://github.com/user-attachments/assets/cec26b98-a664-4973-a9f5-f0015f637c7b)   
![Image](https://github.com/user-attachments/assets/e4a138ec-b7dc-4962-a834-ad2db7b46b68)   
The listening port for WiFi and the listening port for Ethernet must be different ports.   

# Configuration for Connection   
- Using external LAN8720 RMII PHY   
You will need to add a jumper to the LAN8270 according to [this](https://sautter.com/blog/ethernet-on-esp32-using-lan8720/) page.   
Then, connect the LAN8720 and ESP32 with wires according to [this](https://sautter.com/blog/ethernet-on-esp32-using-lan8720/) page.   
![Image](https://github.com/user-attachments/assets/9a0e7dbd-29f9-4ec5-9032-1ba454eea785)

- Using WT32-ETH01   
![Image](https://github.com/user-attachments/assets/ecf17ee4-2b27-4f0b-8b3b-1d150de6af1d)

- Using external W5500 SPI PHY   
Any GPIO can be used.   
However, interrupts require a GPIO that supports interrupts.   
Increasing the SPI clock speed will result in an error.   
![Image](https://github.com/user-attachments/assets/00c3dd99-59c7-48d1-930f-ae4a6a2fca18)

- Using WiFi and Ethernet   
The WiFi interface must be enabled.   
![Image](https://github.com/user-attachments/assets/b8630da0-a559-49ad-8962-83764722e1b5)

# WEB pages   
- WiFi port
![Image](https://github.com/user-attachments/assets/18a83dcc-560a-43c2-ae9b-7880e2719223)
![Image](https://github.com/user-attachments/assets/24beb4f5-4295-47c4-9b44-81d27c4d847d)

- Ethernet port
![Image](https://github.com/user-attachments/assets/c83fa7d8-89cd-4543-b169-8e7f9d7122ae)
![Image](https://github.com/user-attachments/assets/cd3486f0-a7bf-4d3a-b6a6-03b3a4087b1e)

# Performance   
LAN8720's performance is up to 2.5MB/sec.   
W5500's performance is up to 0.9MB/sec.   
LAN8720 is very fast.   
