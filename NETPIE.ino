#include <MicroGear.h>
#include "WiFi.h"

const char* ssid = "ThailandFang24_2G"; //Enter SSID
const char* password = "0887688468"; //Enter Password

  #define APPID   "IoTSmartDeliveryBox"              // use group AppID 
  #define KEY     "CC0IB4rbIMvbKe9"                // use group Key
  #define SECRET  "1zhnZ9P8rHN3HXRWt3lBSI5eC"             // use group Secret
  #define ALIAS   "IoTProject"  // your device name, ex. "A01"
  #define DATATOPIC "/Lock/IoTProject"         // topic 
  #define BUTTONTOPIC "/Button/IoTProject"         // topic 

  #define LEDPIN     25  // LED on NodeMCU board 

   WiFiClient client;
     MicroGear microgear(client);
       int timer = 0;
  int lastSend = 0;
bool lock_status = 0;
  int currentLEDState = 1;


/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
    
    if (*(char *)msg == '0') updateLED(0);
    else if (*(char *)msg == '1') updateLED(1);
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}

     

void setup(void)
{ 
  Serial.begin(115200);


 /* Add Event listeners */

    /* Call onMsghandler() when new message arraives */
    microgear.on(MESSAGE,onMsghandler);

    /* Call onFoundgear() when new gear appear */
    microgear.on(PRESENT,onFoundgear);

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.println("Starting..."); 
      // Connect to WiFi
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);     
}

void loop() 
{
  
 /* To check if the microgear is still connected */
    if (microgear.connected()) {
        Serial.println("connected");

        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();
     
    }
        else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }

    if(millis() - lastSend > 2000)
    {
        StatusSend(lock_status);
        lock_status= !lock_status;
        lastSend=millis();
      }

    
    delay(100);
}

void StatusSend (bool lock_status) {           
    Serial.print("Lock Status: "); Serial.print(lock_status); ;
      String datastring = (String)lock_status;
      Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(DATATOPIC,datastring);             
      }

void updateLED(int state) {
    // LED on NodeMCU is on when LEDPIN=LOW
    if(state==1 && currentLEDState == 0){
        currentLEDState = 1;
        digitalWrite(LEDPIN, LOW);    //LED ON
    }
    else if (state==0 && currentLEDState == 1) {
        currentLEDState = 0;
        digitalWrite(LEDPIN, HIGH);  //LED OFF
    }
    microgear.publish(BUTTONTOPIC, currentLEDState);

}   
