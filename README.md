# Wemos D1 R1 tank, controlled over WebSocket
## Introduction
This is a demo project, implementing a simple tank with a Wemos D1 R1 development board and it's DC motor shield, that can be controlled over WebSocket protocol.
It has also operational head, reverse, brake lights and turn signals.
Connection will be signaled over the built-in LED, but currently not supported because of GPIO mismatch.

## Usage
1. Once turned on, the tank should host it's own WiFi address, without password with SSID: "TigerTank"
2. The tank hosts a webpage, where it can be controlled. This should be reachable over `http://tank.local`, `192.168.4.1`. A captive portal is in operation, so every other request will result in this page in fact
3. The tank can be controlled by the left joystick. The red circles in the middle are buttons. Current functions are:
    1. reserved
    2. Turn on headlights
    3. Turn on emergency signal
    4. reserved
    5. reserved
    6. reserved
    7. reserved
    8. reserved
4. If the tank doesn't recieve a command for 1s, it stops to avoid a crash.
  
## Implementation details
### Communication
The webserver is on port `80` WebSocket server is set on port `81` by default. The control WebSocket signal consists of 3 bytes:
| Idx | Name             | Range | Description                                         |
|-----|------------------|-------|-----------------------------------------------------|
| 1   | Linear velocity  | 0-255 | 0: reverse max, 127: stop, 255: forward max         |
| 2   | Angular velocity | 0-255 | 0: left max, 127: straight, 255: right max          |
| 3   | Button states    | 2,4,6 | 2: headlight on, 4: emergency signal on, 6: both on |

### Pin connection
| GPIO | Functionality        | Active state |
|------|----------------------|--------------|
| 0    | Reverse light        | high         |
| 2    | Left turn signal     | high         |
| 4    | I2C SDA              | -            |
| 5    | I2C SCL              | -            |
| 12   | RIght turn signal    | high         |
| 14   | WebSocket connection | low          |
| 15   | Head light           | high         |
| 16   | Brake light          | high         |
