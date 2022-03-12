# IOT-Project

**Smart Letter Box** 

Smart Letter box is a parcel box by some parcel company to ship parcels of users. It can either be a letter box placed in front of the house or a letter box used by some company to ship goods. The idea is to provide live tracking and security features along with connecting box with user’s app as well as company’s main server. One can check the location of all boxes, weight of parcel placed in them, and each box will have security feature in terms of unique password linked to its unique ID. The main functionality as well as components required are listed below:

**Conceptual Design:**

The Conceptual DEsign of the project is shown in the figure below:

![image](https://user-images.githubusercontent.com/100766772/158037050-59107cc0-7013-4c59-bdfd-5310b4449445.png)

**Features:**

The key features of the project includes:

- Real time location tracking through internet connectivity.

- Password protected lock system implementation.

- Mobile app for control 

NETPIE will be used as a cloud server as well as for mobile app GUI.

**Hardware:**

The main hardware components used in project are

- MCU: ESP32 
 
- Location (GPS): GPS Module NEO 6M 
 
- Connectivity: ESP32 built-in Wi-Fi & GSM Module SIM800L
 
- Display: 16*2 LCD

- Keypad: Hex Keypad 
 
- Electric Lock: Servo Motor 
 
- Weight: Half Bridge Load HX711 
 
**Software Flow: ** 

The software flow of the Project is shown following:

![image](https://user-images.githubusercontent.com/100766772/158037452-c0b73991-f753-41b2-a9bb-ce44fb2fcbc1.png)

While the software flow at the receiver side is as follow:

![image](https://user-images.githubusercontent.com/100766772/158037469-38d2c5ee-45d2-4faf-9ffe-83ae5e7f9b55.png)
