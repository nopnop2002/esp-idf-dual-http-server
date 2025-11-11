# esp-idf-dual-http-server
Dual HTTP server using WiFi interface.   

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-dual-http-server
cd esp-idf-dual-http-server/WiFi
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

# Configuratio   
![Image](https://github.com/user-attachments/assets/9888afeb-f9a9-4782-b244-c25b3ec0686e)   
![Image](https://github.com/user-attachments/assets/de733b2f-cf78-4338-a86b-b6e17588f6de)   
The listening port for primary and the listening port for secondary must be different ports.   

# WEB pages   
- Primary port   
![Image](https://github.com/user-attachments/assets/ff097ee9-a5b3-418e-b92a-64e1afdbcf0e)
![Image](https://github.com/user-attachments/assets/328fa4d1-d59f-4144-b112-aa4a24b46656)

- Secondary port   
![Image](https://github.com/user-attachments/assets/97614197-4b05-415a-9589-3f9c3b5bc3dc)
![Image](https://github.com/user-attachments/assets/056d053a-3e62-417a-8d15-00f2b8043841)
