#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

uint Check_Status = 0;
const char *ssid = "FuRuS_AP";
const char *password = "12345678";
IPAddress ip(192, 168, 1, 1);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  // initialize pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   
  // Mode Point d'accès
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));

  // Routes du serveur web
  server.on("/", HTTP_GET, handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);

  server.begin();
}

void loop() {

  if(Check_Status == 0)
  {
    server.handleClient();
  }
  else
  {
    //add you code here
  }
}


bool checkInternetConnection() {
  WiFiClient client;
  HTTPClient http;
  const char *websiteToCheck = "http://www.google.com";
  http.begin(client, websiteToCheck); 
  int httpCode = http.GET();
  http.end();
  return (httpCode == HTTP_CODE_OK);
}


void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Configuration WiFi</h1>";
  html += "<form action='/connect' method='post'>";
  html += "SSID: <input type='text' name='ssid'><br>";
  html += "Mot de passe: <input type='password' name='password'><br>";
  html += "<input type='submit' value='Submit'>";
  html += "</form></body></html>";

  server.send(200, "text/html", html);
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  WiFi.softAPdisconnect(true);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  String successMessage = "Connected to WiFi. IP Address: " + WiFi.localIP().toString();
  server.send(200, "text/plain", successMessage);
  delay(500);
  
  if (WiFi.status() == WL_CONNECTED) {
    if (checkInternetConnection()) {
      Check_Status =1;
      digitalWrite(LED_BUILTIN, LOW);  
      Serial.println("Internet detected");
    } else {
      Serial.println("No net detected");
    }
  } 
}
