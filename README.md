# DES Instrument Cluster

This project is a documentation of the fulfilment of the project requirements as requested from SEA:ME [[DES_Instrument-Cluster]](https://github.com/SEA-ME/DES_Instrument-Cluster). 

## Directory Structure

```
.
├── Arduino
│   ├── LM363_BasicSketch
│   └── SpeedSensor_CAN
├── Cluster-app
│   ├── design
│   │   └── asset
│   └── src
│       └── module
├── Controller
└── Documentation
```

## Getting Started

### Prerequisites

- For Speed Sensor Side:
  * Himalaya Uno Rev 3 (or any Microcontroller Development Board of your choice e.g. Arduino Uno)
  * LM363 Optocoupler Speed Sensor
  * Keyestudio CAN Shield for Arduino Uno
  * Arduino IDE
  * TimerOne and CAN library from the Arduino IDE Library Manager
- For Instrument Cluster Side:
  * Raspberry Pi 4B
  * SeedStudio CAN HAT for Raspberry Pi
  * QT dependencies
  * 7 inch LCD Display (either HDMI or DSI will do)
 
## Architecture

![System Architecture](.github/Architecture.drawio.png)

### Installation

1. **Arduino Setup**
   - If not previously available, download the TimerOne and CAN library 
   - Compile and Upload the Arduino code from `Arduino/SpeedSensor_CAN/SpeedSensor_CAN.ino` to your device using the Arduino IDE

2. **InstrumentCluster App Setup**
	- The target architecture of our Rasberry-Pi is **'aarch64(arm64)-linux'**.
	- If you are already in using of aarch64-linux with Debian, **you don't need anything more than compiler and QT Framework!** Otherwise, there are two options for setting up your build envrionment - **CMake** with sysroot(in case of different OS) and cross-compile toolchain (in case of different architecture), and the **Docker**.
	- Docker
		- Thanks to Dockrfile, we can share indentical docker image with any of you for build. So we will stick around the Docker way.<p></p>
		1. Move the **Dockerfile** and **makefile** (and **toolchain** in case of Intel/AMD) following your architecture (Intel/AMD: x86, ARM/AppleSilicon: no specific suffix) to the Cluster-app directory.
		2. Type make
		```sh
		make
		```
		3. Connect to Rasberry Pi via ssh and run the app (the app name and path is "~/appIC" as default). **Please be sure that the can interface has set  and shared memory between pi controller and this app is valid.** 
		```sh
		~/appIC
	- CMake
		- If you choose to use the CMake, you must be aware of - what filesystem is and so why the sysroot is needed, what cmake and cross-compie toolchain does.. I attached a useful link for build with CMake. [[Cross-Compile Qt 6]](https://wiki.qt.io/Cross-Compile_Qt_6_for_Raspberry_Pi) - Although it's about installation of the Qt6 with cross-compile, you can reach out the whole concept of the cmake cross-compile.

3. **Systemd Service**
   - Copy `Service/*.service` files to `/etc/systemd/system/`.
   - Enable and start the each service:
     ```sh
     sudo systemctl enable <module.service>
     sudo systemctl start <module.service>
     ```

### Usage

- On boot, the systemd service will start the CAN interface, script for robot control, and the instrument cluster app.
- Arduino firmware will continuously read sensor data and send messages over CAN bus.

## Contributing

Pull requests are welcome! If you have suggestions for improvements, please open an issue or contact the maintainers.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Authors

- [SkySom13](https://github.com/SkySom13)
- [jojeongmin304](https://github.com/jojeongmin304)
- [smwkbgmn](https://github.com/smwkbgmn)

---

*For questions or support, open an issue in this repository.*
