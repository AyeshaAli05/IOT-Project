# Design and Implementation of the IoT in Smart Delivery Box #

Smart Letter box is a parcel box by some parcel company to ship parcels of users. It can either be a letter box placed in front of the house or a letter box used by some company to ship goods. The idea is to provide live tracking and security features along with connecting box with user’s app as well as company’s main server. One can check the location of all boxes, weight of parcel placed in them, and each box will have security feature in terms of unique password linked to its unique ID. The main functionality as well as components required are listed below:

## Conceptual Design: ##

The Conceptual Design of the project is shown in the figure below:

![image](https://user-images.githubusercontent.com/100766772/158037560-96014433-83dc-48c6-b398-9446f60d45cd.png)

The conceptual design based on the available components is as follow:

![image](https://user-images.githubusercontent.com/100766772/158037634-5eda56de-da57-4891-90a1-5c8977086eca.png)

## Features: ##

The key features of the project includes:

- Real time location tracking through internet connectivity.

- Password protected lock system implementation.

- Mobile app for control 

NETPIE will be used as a cloud server as well as for mobile app GUI.

## System Compenents: ##

The main hardware components used in project are

- MCU: ESP32 
 
- Location (GPS): GPS Module URANUS-622f
 
- Connectivity: ESP32 built-in Wi-Fi & GSM Module
 
- Display: 16*2 LCD with I2C interface

- Keypad: Hex Keypad 
 
- Electric Lock: Servo Motor 
 
## Software Flow: ##

The software flow of the Project is shown following:

![image](https://user-images.githubusercontent.com/100766772/158037506-70935154-fb8e-4f35-b959-eacff436c228.png)

While the software flow at the receiver side is as follow:

![image](https://user-images.githubusercontent.com/100766772/158037520-d6427623-2e90-489e-9fc5-155297fd33e1.png)

## Task Distribution ##

**Ayesha Ali (real time tracking)**

- Real time location tracking through GPS {SW A1.1} 

- Backup Internet Connectivity  {SW A1.2}

- Hardware Configuration: ESP32, GPS {HW A1.1}

**Usama Azhar** 

- Controlling Lock system through server NETPIE {SW B1.1}

- Display of information on box {SW B1.2}

- Servo Control through mobile app {SW B1.3} 

- Hardware Configuration: ESP32, 16*2 LCD & GPS Module NEO 6M {HW B1.1}

**Abdul Wahab (lock system)**

- Electric lock operated using MCU controlled by keypad  {SW C1.1}

- Max number of wrong attempts detection and disable unlock. {SW C1.2}

- Update Server and app notifications and warnings {SW C1.3}

- Hardware Configuration: ESP32, Hex Keypad & Half Bridge Load Cell HX711 {HW C1.1}


## Timeline of Project ##

![Capture22](https://user-images.githubusercontent.com/76215573/161130336-5ec5b7e0-420c-4949-af2d-657fee118388.JPG)


## Weekly Progress ##

### Week 1 ###

**Tasks**

- Configuration and Testing of ESP82

- Configuration and Testing of 16*2 LCD display

- Configuration and Testing of Hex Keypad

**Problems**

- No big issue was faced

### Week 2 ###

**Tasks**

- Get familiar with the basics of Iot

- IoT labs Implementation (NETPIE).

- Tried GPS connection with ESP32 

**Problems**

- We were not able to connect GPS module with ESP32 due to less current limit of ESP32 than what was required for for operation of GPS module

### Week 3 ###

**Tasks**

- NETPIE Connection with arduino

- GPS connection with mega (not succesfull)

- Basic Servo control for lock System

- Keypad Password Implementation

**Problems**

- Tried GPS connection with mega as it provides more current limit than ESP32 but we were unsuccessfull in its connection too and we figure out to use voltage    regulator with GPS module 

### Week 4 ###

**Tasks**

- NETPIE connection with ESP32

- Tried GPS connection with ESP32 along with voltage regulator 

**Problems**

- The GPS does not connect with satellite during indoor testing, once got connected but gave inaccurate location information.

### Week 5 ###

**Tasks**

- NETPIE freeboard password keypad implementation to allow user enter password and unlock from app.

- Combined NETPIE, lock & keypad into main working code.

- GPS test at various locations.

**Problems**

No connection of GPS to sattelite despite test at following location: close indoor location, open location outside apartment, Indoor location at TGGS Communication lab, Outdoor location at TGGS.

### Week 6 ###

**Tasks**

- LCD (2*16) display implementation using I2C interface with ESP32.

- Integration of LCD with main working code to display status and password information.

- Further testing of GPS.

**GPS test Results**

At open location achived connection after 30-45 mins , connection reminded stable afterwards even in indoor location and gave accurate location value.

**Problems**

GPS takes too long to connect for the first time while fixing to a satellite outdoor in open sky and doesnot connect at all at indoor location.
