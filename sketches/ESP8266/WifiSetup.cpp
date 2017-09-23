
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SimpleDHT.h>

const int pinDHT22= 5;
const int donePin= 12;
const int modePin= 14;
const int clientLedPin= 2;
const int configLedPin= 4;

SimpleDHT22 dht22;

char ssid[] = "///SSID///";
char pwd[]="///PWD///";
const int CLIENTMODE = 0;
const int APMODE = 1;

int runMode =0;
int wifiStatus;

ESP8266WebServer server(80);
String configPage;

void setup() {
 Serial.begin(115200);

 configPins();
 delay(500);
 runMode= readMode();
 if (runMode == CLIENTMODE){
    wifiStatus= connectWifi(ssid, pwd);
    if (wifiStatus!=WL_CONNECTED){
    runMode=APMODE;
    setMode(runMode);
    }
 }
 if (runMode == APMODE){
    startAP();
  }
}

void loop() {
  if (runMode==APMODE){
    server.handleClient();
  }
  if(runMode==CLIENTMODE){
    logData();
    digitalWrite(donePin,HIGH);
    delay(1000);
    digitalWrite(donePin,LOW);
    delay(5000);
  }
}


/////////////////
// Config Mode //
void startAP(){
    uint8_t macAddr[6];
    char apName[8];
     Serial.println("Scanning starts...");
    int n = WiFi.scanNetworks();
    Serial.print(n);
    Serial.println(" network(s) found");
    configPage= makeConfigPage(n);
    
    WiFi.macAddress(macAddr);  
    sprintf(apName, "ESP-%02x%02x",macAddr[0], macAddr[1]);
   
    WiFi.softAP(apName);
    Serial.printf("MAC address = %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
   
    server.on("/", serveHome);
    server.on("/set_wifi", setWifi);
    server.begin();
    Serial.println("Server started.");
}

void serveHome(){
  server.send(200, "text/html", configPage); 
  }

void setWifi(){
  String newSsid= server.arg("ssid");
  int slen = newSsid.length() +1;
  char cSsid[slen];

  Serial.print("ssid chosen: ");
  Serial.print(newSsid);
  Serial.print("Password: ");
  Serial.print(pwd);
  String newPwd= server.arg("pwd");
  int pwdLen = newPwd.length()+1;
  char cPwd[pwdLen];

  newSsid.toCharArray(cSsid, slen);
  newPwd.toCharArray(cPwd, pwdLen);
  
  server.send(200, "text/plain", "Trying to connect to "+newSsid);
  digitalWrite(configLedPin,LOW);
  runMode= CLIENTMODE;
  connectWifi(cSsid, cPwd);
}

String makeConfigPage(int n){
  String ssid;
  String s ="<!DOCTYPE HTML><html><body>";
  int i;
  
  if (n==0){
    s+= "<p>Sorry, no Wifi connection found. Please try again later..</p>";
    return s;
  }
  
  s+="<p>Select a wifi</p>";
  s+="<form  method=\"POST\" action=\"/set_wifi\"><select name=\"ssid\">";
  for (i=0;i<n;i++){
    ssid=WiFi.SSID(i);
  s+="<option value=\""+ ssid +"\">"+ssid+"</option>";
  }
  s+="</select>";
  s+="<label>Password: </label>";
  s+="<input name=\"pwd\" type=\"password\" /> <button type=\"submit\">Save</button></form>";
  s+="</body></html>";
  return s;
}


/////////////////
// Client mode //
int connectWifi(char s[], char p[] ){
  int tTot=0;
  bool success=WiFi.status() == WL_CONNECTED;
  WiFi.begin(s,  p);
  while(tTot<10000 && !success){
    ledConnecting(clientLedPin);
    tTot=tTot+200;
    success=WiFi.status() == WL_CONNECTED;
    Serial.println('.');
    }
  if(success){ 
    Serial.println();
    digitalWrite(clientLedPin,HIGH);
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
  } 
  else{
    Serial.println("Could not connect");
  }
  return WiFi.status();
}


///////////
// Utils //
void ledConnecting(int pin){
  digitalWrite(pin,HIGH);
  delay(100);
  digitalWrite(pin,LOW);
  delay(100);
}
int readMode(){
  int configMode= digitalRead(modePin);
  setMode(configMode);
  Serial.print("Mode Selected: ");
  Serial.println(configMode);
  return configMode;
  }

void setMode(int modeValue){
  digitalWrite(clientLedPin, !modeValue);
  digitalWrite(configLedPin, modeValue);
}

void configPins(){
  pinMode(donePin, OUTPUT);
  pinMode(modePin, INPUT);
  pinMode(clientLedPin, OUTPUT);
  pinMode(configLedPin, OUTPUT);
  digitalWrite(donePin, LOW);
  digitalWrite(configLedPin, LOW);
  digitalWrite(clientLedPin, LOW);
}


////////////////////////////////
// Data reading and handling ///
void logData(){
 Serial.println("=================================");
  Serial.println("Sample DHT22...");
  
  // read without samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.print((float)humidity); Serial.println(" RH%");
  
  // DHT22 sampling rate is 0.5HZ.
  

}


