#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
uint Check_Status = 0;
const char *ssid = "FuRuS_AP";
const char *password = "12345678";
IPAddress ip(192, 168, 1, 1);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

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

  if(!Check_Status)
  {
    server.handleClient();
  }
  else
  {
    //add you code here
  }
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

  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Check_Status =1;
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  String successMessage = "Connected to WiFi. IP Address: " + WiFi.localIP().toString();
  server.send(200, "text/plain", successMessage);
  delay(500);
  ESP.reset();  // Redémarrage pour effectuer la connexion au réseau WiFi
}
