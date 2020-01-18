#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Shrey";  // Enter SSID here
const char* password = "Shrey@123";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(8000);

uint8_t LED1pin = D6;
bool LED1status = LOW;

uint8_t LED2pin = D7;
bool LED2status = LOW;


uint8_t LED3pin = D5;
bool LED3status = LOW;

int color[3];

void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  
  server.on("/", handle_OnConnect);
  server.on("/off",off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
 /*
  if(LED1status)
  {
  analogWrite(LED1pin,255);
  analogWrite(LED2pin,0);
  analogWrite(LED3pin,0);
    
    }
  else
  {

  analogWrite(LED1pin,0);
  analogWrite(LED2pin,0);
  analogWrite(LED3pin,0);
    
}
  
  if(LED2status)
  {

  analogWrite(LED1pin,0);
  analogWrite(LED2pin,255);
  analogWrite(LED3pin,0);
    
}
  else
  {
  
  analogWrite(LED1pin,0);
  analogWrite(LED2pin,0);
  analogWrite(LED3pin,0);
    }

  
  if(LED3status)
  {


  analogWrite(LED1pin,0);
  analogWrite(LED2pin,0);
  analogWrite(LED3pin,255);
    }
  else
  {
  
  analogWrite(LED1pin,0);
  analogWrite(LED2pin,0);
  analogWrite(LED3pin,0);
    }
    */

    if(LED1status){
  analogWrite(LED1pin,color[0]);
  analogWrite(LED2pin,color[1]);
  analogWrite(LED3pin,color[2]);
    }else{
  analogWrite(LED1pin,0);
  analogWrite(LED2pin,0);
  analogWrite(LED3pin,0);
       
      }
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  LED3status=LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
 server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status)); 
}

void off(){
  LED1status=LOW;
 server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status)); 

  }

void handle_NotFound(){
  LED1status = HIGH;
  String s = server.uri();
  int i =0;
  char buf[sizeof(s)];
    s.toCharArray(buf, sizeof(buf));
    char *p = buf;
    char *str;
    while ((str = strtok_r(p, ",", &p)) != NULL){ // delimiter is the semicolon
      String c = str;
      if(c.startsWith("/")){
        c =  c.substring(1);
      }
      color[i] = c.toInt();
      i++;
  }
  Serial.println(color[0]);
  
  server.send(200, "text/plain","Hello" );
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

 if(led3stat)
  {ptr +="<p>LED3 Status: ON</p><a class=\"button button-off\" href=\"/led3off\">OFF</a>\n";}
  else
  {ptr +="<p>LED3 Status: OFF</p><a class=\"button button-on\" href=\"/led3on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
