# esp-idf-dual-http-server
Dual HTTP server for ESP-IDF.   

The esp-idf repository comes with many example projects.   
However, there is no example project that starts two HTTP servers simultaneously.   
This project is an example that demonstrates how to run two HTTP servers simultaneously. 
The two HTTP servers can display different HTML documents.

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# WiFi project
The WiFi interface can run two HTTP servers on different port numbers.   
You can display different HTML documents for Primary port and Secondary port.   

# WiFi+Ethernet project
The ESP32 can use two interfaces simultaneously: WiFi and Ethernet.   
The WiFi interface and the Ethernet interface can run two HTTP servers on different address and port number.
You can display different HTML documents for WiFi interface and Ethernet interface.   

