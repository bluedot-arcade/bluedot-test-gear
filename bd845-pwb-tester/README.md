<p align="right">
    <a name="readme-top"></a>
    <a href="/LICENSE.txt"><img src="https://img.shields.io/badge/license-MIT-green" /></a> <a href=""><img src="https://img.shields.io/badge/version-0.0.1-red" /></a> 
</p>
<br><br>
<p align="center">
    <h1 align="center">BD845-PWB Tester</h1>
    <p align="center">This repository contains the source code and the design files of the BD845-PWB Tester.</p>
    <p align="center"><strong><a href="https://github.com/bluedot-arcade/bd845-pwb-board">Go to board repository</a></strong></p>
    <p align="center"><strong><a href="https://docs.bluedotarcade.com/boards/bd845-pwb">Explore the docs</a></strong></p>
    <br><br>
</p>

## About the project

The BD845-PWB Tester is a test gear specifically designed to automate the [BD845-PWB] board physical tests. 

It is based on an Arduino Mega (or any compatible board). An additional hat is provided to avoid a flying wires setup and speed up the testing procedure.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Test procedure

This section describes the steps required to perform the tests.

### 1. Build and upload test program to the Arduino Mega

This project uses PlatformIO to build and upload the project. Only the PlatformIO Core CLI is required but consider installing the PlatformIO IDE for a better user experience.

The following is the recommended way to build and upload the firmware.

1. [Install PlatformIO Core.][PlatformIO Core Docs]

2. Clone the repository.
    ```bash
    git clone https://github.com/bluedot-arcade/bluedot-test-gear
    ```

3. Navigate to the root of the project.
   ```bash
    cd bluedot-test-gear/bd845-pwb-tester
    ```

4. Build the project. Binaries will be created inside the `.pio` folder.
    ```bash
    platformio run
    ```
    
5. Upload the project to the Arduino Mega.
    ```bash
    platformio run --target upload
    ```

If you prefer using the Arduino IDE the full code is contained in `src/main.cpp`. Just rename it to `main.ino`.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### 2. Set up test gear

Wire the Arduino Mega to the BD845-PWB. This does not require any additional components other than wires for direct connection of the pins.

Alternatively you can use the provided hat.

The following is the Arduino Mega <-> BD845-PWB pins mapping table.

| Arduino Mega Pin | BD845-PWB Pin | | Arduino Mega Pin | BD845-PWB Pin |
| ---------------- | ------------- |-| ---------------- | ------------- |
| A0               | U_OUT         |-| D37              | L_S1          |
| A1               | D_OUT         |-| D36              | L_S2          |
| A2               | L_OUT         |-| D35              | L_S3          |
| A3               | R_OUT         |-| D34              | L_S4          |
| A4               | C_OUT         |-| D33              | R_S1          |
| A8               | FL1           |-| D32              | R_S2          |
| A9               | FL2           |-| D31              | R_S3          |
| A10              | FL3           |-| D30              | R_S4          |
| A11              | FL4           |-| D53              | C_S1          |
| A12              | FL5           |-| D52              | C_S2          |
| A13              | TEST          |-| D51              | C_S3          |
| D22              | U_S1          |-| D50              | C_S4          |
| D23              | U_S2          |-| D49              | U_LIGHT       |
| D24              | U_S3          |-| D48              | D_LIGHT       |
| D25              | U_S4          |-| D47              | L_LIGHT       |
| D26              | D_S1          |-| D46              | R_LIGHT       |
| D27              | D_S2          |-| D45              | C_LIGHT       |
| D28              | D_S3          |-|
| D29              | D_S4          |-|

The full pinout for the BD845-PWB can be found in the [docs][BD845-PWB Docs].

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### 3. Run test routines

Test routines can be run using a serial monitor from a computer.

1. Connect the Arduino Mega to a computer with a USB cable.
2. Connect the BD845-PWB power connector to a +12V supply.
3. On the computer open the serial monitor, open the Arduino Mega serial port and set the baud rate to 115200. A menu with all test routines will be printed.
   
    ```bash
    *** BD845-PWB Test Routines ***

    Select option:
    1. Test inputs
    2. Test lights external
    3. Test lights press mode
    4. Test debounce
    5. Test legacy
    ```
4. Select the routine to run by writing the corresponding number to the serial monitor.
5. "TEST SUCCESSFUL" will be printed on success. Otherwise "TEST FAILED" will be printed and the built-in LED on Arduino Mega will light up.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Hat board

The [/hat](hat/) folder contains the project files for an hat board that simplifies the connection between the Arduino Mega and the BD845-PWB board, speeding up testing without the use of stray wires.

It also comes with additional LED indicators for test status and light driver tests.

![BD845-PWB-Tester-Hat](/bd845-pwb-tester/hat/images/bd845-pwb-tester-hat-v1.0.0.png)

## License

Distributed under the MIT License. See [LICENSE.txt] for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[LICENSE.txt]: /LICENSE.txt
[PlatformIO Core Docs]: https://dohttps://docs.bluedotarcade.com/boards/bd845-pwbcs.platformio.org/en/latest/core/index.html
[PlatformIO Docs]: https://docs.platformio.org/
[BD845-PWB]: https://github.com/bluedot-arcade/bd845-pwb-board
[BD845-PWB Docs]: https://docs.bluedotarcade.com/boards/bd845-pwb