#include "BatterySOC.h"
#include <iostream>
#include <iomanip>

int main() {
    try {
        // Create BatterySOC instance for 3S battery (3 cells in series)
        BatterySOC battery_soc(3);
        
        std::cout << "Battery State of Charge Calculator" << std::endl;
        std::cout << "Configuration: " << battery_soc.getCellsInSeries() << "S battery pack" << std::endl;
        std::cout << "====================================" << std::endl;
        
        // Test various voltage levels
        std::vector<double> test_voltages = {
            12.60, // 100% (4.20V per cell)
            12.30, // 90%  (4.10V per cell)
            12.00, // 80%  (4.00V per cell)
            11.70, // 60%  (3.90V per cell)
            11.40, // 40%  (3.80V per cell)
            11.10, // 20%  (3.70V per cell)
            10.80, // 10%  (3.60V per cell)
            10.50, // 0%   (3.50V per cell)
            13.00, // Over 100%
            10.00  // Under 0%
        };
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Total Voltage\tPer Cell\tSoC %" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        
        for (double voltage : test_voltages) {
            double voltage_per_cell = battery_soc.getVoltagePerCell(voltage);
            double soc = battery_soc.voltageToSoC(voltage);
            
            std::cout << voltage << "V\t\t" 
                      << voltage_per_cell << "V\t\t"
                      << soc << "%" << std::endl;
        }
        
        // Example with custom voltage-SoC table
        std::cout << "\n\nCustom Battery Profile Example:" << std::endl;
        std::cout << "================================" << std::endl;
        
        // Custom table for a different battery chemistry
        std::vector<BatterySOC::VoltageSocPair> custom_table = {
            {4.35, 100.0},  // High voltage Li-ion
            {4.20, 90.0},
            {4.00, 70.0},
            {3.85, 50.0},
            {3.75, 30.0},
            {3.65, 10.0},
            {3.40, 0.0}
        };
        
        BatterySOC custom_battery(custom_table, 4); // 4S battery
        
        std::cout << "Configuration: " << custom_battery.getCellsInSeries() << "S battery pack (Custom profile)" << std::endl;
        
        std::vector<double> custom_test_voltages = {
            17.40, // 100% (4.35V per cell)
            16.80, // 90%  (4.20V per cell)
            16.00, // 70%  (4.00V per cell)
            15.40, // 50%  (3.85V per cell)
            15.00, // 30%  (3.75V per cell)
            14.60, // 10%  (3.65V per cell)
            13.60  // 0%   (3.40V per cell)
        };
        
        std::cout << "Total Voltage\tPer Cell\tSoC %" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        
        for (double voltage : custom_test_voltages) {
            double voltage_per_cell = custom_battery.getVoltagePerCell(voltage);
            double soc = custom_battery.voltageToSoC(voltage);
            
            std::cout << voltage << "V\t\t" 
                      << voltage_per_cell << "V\t\t"
                      << soc << "%" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}

/*
 * Compilation:
 * g++ -o soc_example soc_example.cpp BatterySOC.cpp -std=c++11
 * 
 * Usage with INA219:
 * This BatterySOC class can be easily integrated with the INA219 library
 * to provide real-time State of Charge monitoring:
 * 
 * INA219 ina219;
 * BatterySOC battery_soc(3); // 3S battery
 * 
 * float voltage = ina219.getSupplyVoltage();
 * double soc = battery_soc.voltageToSoC(voltage);
 */
