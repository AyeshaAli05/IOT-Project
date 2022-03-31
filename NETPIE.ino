#include "ESP8266WiFi.h"
#include <MicroGear.h>

const char* ssid = "PTCL-383"; //Enter SSID
const char* password = "qwertyuiop123"; //Enter Password

  #define APPID   "IoTProject"              // use group AppID 
  #define KEY     "yBz3cPmIZ8PoCKk"                // use group Key
  #define SECRET  "zENetgpO6ijU6O7i0GLyIWUcb"             // use group Secret
  #define ALIAS   "IoT"  // your device name, ex. "A01"
  #define DHTDATATOPIC "/letterbox/IoT"         // topic 

   WiFiClient client;
     MicroGear microgear(client);
       int timer = 0;
  int lastsend = 0;




/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
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
    Serial.println("Debug");
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
        ReadandSend();
    }
        else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}

void Send () {if(millis() - lastsend > 2000){        // setup a 2-second period
    bool lock_status = 0;       
    lastsend = millis();
          
    Serial.print("Lock Status: "); Serial.print(lock_status); ;
 
      String datastring = (String)lock_status;
      Serial.print("Sending --> ");
      Serial.println(datastring);
      microgear.publish(DHTDATATOPIC,datastring);             }
    }  
}
