# ESP8266_dynamicWifi

This project enables the ESP8266 board to operate as follows:

1. At startup, it acts as an Access Point (AP).
2. It connects to the ESP8266 board using a static IP address.
3. Once connected with this IP, a web page displays, allowing the input of an SSID and password.
4. After pressing the "Submit" button, the ESP8266 board acts as a client, connecting to the network with the SSID and password entered on the web page.

## Initial Setup

1. **Download the source code:**

2. **Code Configuration:**
   - To modify the parameters according to your needs to modify IPAddress.

3. **Upload the code to the ESP8266 board:**
   - Use the Arduino IDE or a similar tool to upload the code to the ESP8266 board.

## Usage

1. **Powering up the ESP8266 board:**
   - Connect the ESP8266 board to a power source.

2. **Connecting to the Access Point (AP):**
   - Search for the WiFi network with the SSID configured in the `config.h` file.
   - Connect to the WiFi network with the configured password.

3. **Accessing the configuration page:**
   - Open a web browser and navigate to the static IP address configured in the `config.h` file.

4. **Entering SSID and password:**
   - On the web page, enter the SSID and password of the network you want to connect the ESP8266 board to.

5. **Validating the information:**
   - Click the "Submit" button to submit the information.

6. **Connecting to the network:**
   - The ESP8266 board will now connect to the WiFi network with the provided information.

## Contributions
Contributions are welcome. Feel free to open an issue to report bugs or propose enhancements.

## License
This project is licensed under the [MIT License](LICENSE).
