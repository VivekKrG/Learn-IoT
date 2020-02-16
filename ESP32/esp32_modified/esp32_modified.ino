#include <AWS_IOT.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4        // digital pin declaration of sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

AWS_IOT hornbill;   // AWS_IOT instance

char WIFI_SSID[]="mywifi";        //dlink-2D92
char WIFI_PASSWORD[]="98769876";  //  faecd91976

char HOST_ADDRESS[]="admigwosk81v3-ats.iot.ap-south-1.amazonaws.com";
char CLIENT_ID[] = "vivekthingpolicy"; // policy name
char TOPIC_NAME[]= "mqtt";        // Subscribe to this topic to get data


int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];

int temp = 0;


void setup() {
    
    Serial.begin(115200);
    delay(2000);
    
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(WIFI_SSID);
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(5000);  // wait 5 seconds for connection:
    }

    Serial.println("Connected to wifi");

    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0) // Connect to AWS using Host Address and Cliend ID
    {
        Serial.println("Connected to AWS");
        delay(1000);
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);
    dht.begin(); //Initialize the DHT11 sensor
}


void loop() {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();      // Read temperature as Celsius (the default)
    float f = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println("Failed to read from DHT sensor!");
        delay(1000);
    }
    else
    {
        sprintf(payload,"Humidity:%f  Temperature:%f'C",h,t); // Create the payload for publishing
        
        if(hornbill.publish(TOPIC_NAME,payload) == 0)   // Publish the message(Temp and humidity)
        {        
            Serial.print("Publish Message:");   
            Serial.println(payload);
            temp = 0;
        }
        else
        {
            Serial.println("Publish failed"); 
            temp++;
            if (WiFi.status() != WL_CONNECTED)
            {
                  Serial.print("Attempting to connect to SSID: ");
                  Serial.println(WIFI_SSID);
                  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
                  delay(4000);                 
                  if (WiFi.status() == WL_CONNECTED)
                  {
                    Serial.println("***Connected***");
                    Serial.println("Trying to connect to AWS");
                   if(hornbill.connect(HOST_ADDRESS,CLIENT_ID) == 0) // Connect to AWS using Host Address and Cliend ID
                    {
                        Serial.println("Connected to AWS");                
                        delay(1000);
                        temp = 10;
                    }
                  }  
              }
              if (temp > 15)
              {
                  Serial.println(":***Refreshing The Connection***");
                  WiFi.disconnect();
                }
                
        }
        // publish the temp and humidity every 1 seconds.
        vTaskDelay(1000 / portTICK_RATE_MS);        
    } 
}
// have to edit src file as failed connection run infinitely
