#include "INA219.h"
#include "BatterySOC.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

int main() {

try{
    // Create INA219 instance
    // Using I2C bus 1 (default for Raspberry Pi) and default address 0x40
    INA219 ina219(1, 0x41);
    // Create BatterySOC instance for 3S battery (3 cells in series)
    BatterySOC battery_soc(3);
    
    // Initialize with 0.1 ohm shunt resistor and 3.2A max current
    if (!ina219.begin(0.1f, 3.2f)) {
        std::cerr << "Failed to initialize INA219: " << ina219.getLastError() << std::endl;
        return -1;
    }
    
    std::cout << "INA219 initialized successfully!" << std::endl;
    std::cout << "Reading power consumption data..." << std::endl;
    std::cout << std::endl;
    
    // Print header
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Time\t\tBus V\tVoltage per cell V\tSoC \%" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    
    // Read data continuously
    for (int i = 0; i < 100; ++i) {
        float bus_voltage = ina219.getBusVoltage();
        double voltage_per_cell = battery_soc.getVoltagePerCell(bus_voltage);
	double soc = battery_soc.voltageToSoC(bus_voltage);
	
        // Print readings
        std::cout << i << "\t\t" 
                  << bus_voltage << "\t"
                  << voltage_per_cell << "\t\t"
                  << soc << std::endl;
        
        // Wait 1 second before next reading
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

} catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

/*
 * Compilation instructions:
 * 
 * To compile this example on Raspberry Pi:
 * g++ -o ina219_example example.cpp INA219.cpp -std=c++11
 * 
 * To run:
 * sudo ./ina219_example
 * 
 * Note: Root privileges are required to access I2C devices on Raspberry Pi
 * 
 * Wiring connections for INA219 to Raspberry Pi 4B:
 * - VCC  -> 3.3V (Pin 1)
 * - GND  -> Ground (Pin 6)
 * - SCL  -> GPIO3/SCL (Pin 5)
 * - SDA  -> GPIO2/SDA (Pin 3)
 * 
 * The INA219 should be connected in series with the power supply
 * to measure current flowing through your load.
 */
