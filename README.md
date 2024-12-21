# MiniWeatherStation-ESP32
ESP32 based Weather Station

This project is a simple and interactive weather station based on the ESP32 microcontroller. It allows users to input the name of a city, fetches real-time weather data using a weather API, and displays the following information on an I2C LCD screen:  
- Temperature
- Humidity
- Weather Description



### **Features:**
- Prompts the user to enter a city name.
- Retrieves weather data in real-time from a JSON response via the OpenWeather API.
- Parses and decodes the JSON data to extract essential weather metrics.
- Displays the weather details neatly on a 16x2 I2C LCD screen.

---

### **Technologies Used:**
- **ESP32**: Microcontroller for handling inputs, processing data, and displaying outputs.  
- **OpenWeather API**: For fetching real-time weather data.  
- **Arduino IDE & Libraries**: Used to program the ESP32.  

---

### **Getting Started:**
1. Set up the ESP32 development board with an I2C LCD display.
2. Obtain an API key from the OpenWeatherMap service.
3. Clone this repository and upload the code to your ESP32.
4. Enter a city name when prompted, and view the weather details displayed on the LCD screen.

---

### **Future Enhancements:**
- Adding icons for more weather types, like rain or snow, on the LCD screen.
- Integrating features like historical weather data or forecast capabilities.
- Supporting additional sensors for expanded environmental monitoring.

---
