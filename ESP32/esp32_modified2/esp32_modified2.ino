#include <AWS_IOT.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4     // digital pin declaration of sensor
#define DHTTYPE DHT11   // DHT 11
#define led 2

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
void Blink(int);

void setup() {
    pinMode(led, OUTPUT);
    while (status != WL_CONNECTED)
    {
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(5000);  // wait 5 seconds for connection:
    }
    Blink(200);
    Blink(200);
    delay(3000);
    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0) // Connect to AWS using Host Address and Cliend ID
    {
        Blink(300);
        delay(800);
        Blink(300);
        delay(800);
    }
    else
    {
        while(1){
            Blink(2000);
          }
    }

    delay(2000);
    dht.begin(); //Initialize the DHT11 sensor
}


void loop() {

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    int h = dht.readHumidity();
    int t = dht.readTemperature();      // Read temperature as Celsius (the default)
    //float f = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        digitalWrite(led, 0);
        delay(1000);
    }
    else
    {
        sprintf(payload,"{\"Hum\": \"%d\",\"Tem\": \"%d\"}",h,t); // Create the payload for publishing
        
        if(hornbill.publish(TOPIC_NAME,payload) == 0)   // Publish the message(Temp and humidity)
        {        
            Blink(200);   
            Blink(200);   
            temp = 0;
        }
        else
        {
            temp++;
            if (WiFi.status() != WL_CONNECTED)
            {
                  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
                  delay(4000);                 
                  if (WiFi.status() == WL_CONNECTED)
                  {
                    Blink(200);
                    Blink(200);
                    delay(3000);
                    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID) == 0) // Connect to AWS using Host Address and Cliend ID
                    {
                        Blink(300);
                        delay(800);
                        Blink(300);
                        delay(800);               
                        delay(1000);
                        temp = 10;
                    }
                  }  
              }
              if (temp > 15)
              {
                  WiFi.disconnect();
                }
                
        }
        // publish the temp and humidity every 1 seconds.
        vTaskDelay(4200 / portTICK_RATE_MS);        
    } 
}
// have to edit src file as failed connection run infinitely
void Blink(int wait)
{
  digitalWrite(led,0);
  delay(wait);
  digitalWrite(led,1);
  delay(wait);
  }
