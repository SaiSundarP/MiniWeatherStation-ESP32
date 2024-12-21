#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define ARDUINOJSON_DEPRECATION_NOTICE 0

// Wi-Fi credentials
const char* ssid = "Wokwi-GUEST";        // Wi-Fi SSID
const char* password = ""; // Wi-Fi password

// Weather API details
const char* apiKey = "weather-api-key";   
const char* server = "http://api.openweathermap.org/data/2.5/weather";

String city = ""; // Dynamic city input
LiquidCrystal_I2C lcd(0x27, 16, 2);    // I2C address for LCD
byte thunder[8] = {
  0b00001,
  0b00110,
  0b11111,
  0b00100,
  0b11111,
  0b01110,
  0b01100,
  0b01000
};

byte cloud[8] = {
  0b00000,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};
// Connect to Wi-Fi
void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  lcd.print("Connecting to Wi-Fi");
  int i=0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.setCursor(i,1);
    lcd.print(".");
    i++;
    delay(500);
  }
  Serial.println("\nConnected to Wi-Fi!");
  lcd.clear();
  lcd.print("Connected to Wi-Fi!");
}

// Fetch weather data
void getWeatherData(const String& city) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?q=" + city + "&appid=" + apiKey;
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode == 200) { // Check for the HTTP response
      String payload = http.getString();
      StaticJsonDocument<1024> doc;
      deserializeJson(doc, payload);

      float temperature = doc["main"]["temp"];
      int humidity = doc["main"]["humidity"];
      const char* weather = doc["weather"][0]["description"];

      // Display on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(temperature-273);
      lcd.print(" C");
      lcd.setCursor(0, 1);
      lcd.print("Hum: ");
      lcd.print(humidity);
      lcd.print("% ");
      lcd.print(weather);
    } else {
      Serial.println("Error in fetching data");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Failed to");
      lcd.setCursor(0, 1);
      lcd.print("fetch data!");
    }
    http.end();
  }
}
void scrollFromRight(String ch, int row) {
    int strLength = ch.length();
    for (int pos = 16; pos >= 0; pos--) { // Loop from off-screen right to off-screen left
        lcd.clear();                                // Clear screen for each frame
        lcd.setCursor(max(0, pos), row);           // Set the position where the string starts
        int startIdx = max(0, -pos);               // Adjust start index of the substring to display
        lcd.print(ch.substring(startIdx));         // Print the part of the string visible
        delay(500);                                // Adjust speed of scrolling
    }
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  scrollFromRight("Weather Station!",0);
  lcd.createChar(0, thunder); // Load thunder symbol into slot 0
  lcd.createChar(1, cloud);   // Load cloud symbol into slot 1
  lcd.setCursor(5, 1);
  lcd.write(byte(0)); 
  lcd.setCursor(11, 1);
  lcd.write(byte(1));
  delay(6780);
  lcd.clear();
  connectToWiFi();

  // Prompt user for city input
  Serial.println("Enter city name:");
  while (city == "") {
    if (Serial.available() > 0) {
      city = Serial.readStringUntil('\n');
      city.trim(); // Remove leading/trailing spaces
      Serial.print("City set to: ");
      Serial.println(city);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("City: ");
  lcd.setCursor(0, 1);
  lcd.print(city);
  delay(2000); // Display city confirmation
}

void loop() {
  if (!city.isEmpty()) {
    getWeatherData(city);
  }
  delay(60000); // Update every minute
}
