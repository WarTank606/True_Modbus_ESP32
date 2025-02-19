#include <ModbusRTU.h>

// Define RS485 RX and TX pins
#define RS485_RX 16  // ESP32 RX pin
#define RS485_TX 17  // ESP32 TX pin

// Create Modbus slave object
ModbusRTU modbus;

void setup() {
    Serial.begin(115200);    
    Serial1.begin(115200, SERIAL_8N1, RS485_RX, RS485_TX); // Initialize Serial1

    modbus.begin(&Serial1);  // Start Modbus without directional control
    modbus.slave(1);  // Set Modbus slave ID to 1
    modbus.addHreg(0, 0); // Holding Register 0 initialized to 0
    modbus.addHreg(1, 0); // Holding Register 1 initialized to 0

    Serial.println("ESP32 Modbus RTU Slave Ready");
}

void loop() {
    modbus.task(); // Process Modbus requests

    uint16_t receivedValue  = modbus.Hreg(0); // Correctly reading register value
    uint16_t modifiedValue  = receivedValue + 100; // Add 100 to received value

    // Store the updated value in Register 1
    modbus.Hreg(1,modifiedValue);
  

   // Debugging output
    Serial.print("Received from Master: ");
    Serial.println(receivedValue);
    
    Serial.print("Updated Value Sent Back: ");
    Serial.println(modifiedValue);
    Serial.println();
    Serial.println();

    delay(1000);
}
