# Membrane Motor System

## Setup

### IDE

- Download and install **VS Code** from https://code.visualstudio.com/Download
- Open VS Code and install the **PlatformIO IDE** extension via View->Extensions.
- If you are on Windows, you'll need to **enable long paths support**:
  
    - Run **git bash** and enter the following command:
    ```
    git config --global core.longpaths true
    ```
    - Run **regedit** (open the Start menu and type regedit).
    - Navigate to the following key: `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem`
    - Double-click on the **`LongPathsEnabled`** value.
    - In the value’s properties window, change the value **from 0 to 1** in the “Value data” box and then click OK.
    - Restart your PC.
    - For more information: https://www.howtogeek.com/266621/how-to-make-windows-10-accept-file-paths-over-260-characters

- In VS Code, open the cloned repository via File->Open Folder... The first run will take some time since PlatformIO needs to download and install dependencies such as the Arduino and Raspberry Pi Pico frameworks.

### Drivers

*(Optional)* This is required if you're having trouble uploading to the Pico board from VS Code.

- Download and install Arduino IDE https://www.arduino.cc/en/software
- Choose `Tools->Board->Boards Manager...`
- Install the `Arduino Mbed OS RP2040 Boards` package
- Plug in a Raspberry Pi Pico board to a USB port while **holding the BOOTSEL switch** to enter bootloading mode.
- Select the `File->Examples->01.Basics->Blink` sketch
- Select the correct board type via `Tools->Board->Arduino Mbed OS RP2040 Boards->Raspberry Pi Pico`
- Click `Upload`

You should see the built-in LED blinking on the Pico board.

## Building And Running

This system is managed by a **master** board and one or more **slave** boards. To compile and run the project on the Raspberry Pi Pico boards, you'll need to perform the following steps:

- Switch your PlatformIO project environment by clicking on `Default (membrane-motor-system)` at the bottom of the editor and selecting the `env:master_stepper_motor_pico` environment.
- Plug in your **master** Raspberry Pi Pico board to a USB port while **holding the BOOTSEL switch** to enter bootloading mode.
- Click on the `PlatformIO: Upload` button at the bottom of the editor to build and upload the code to the Pico.
- Repeat the previous steps for the **slave** boards using the `env:slave_stepper_motor_pico` environment. Make sure you unplug the master Pico to avoid uploading to the wrong board.

## Documentation
### Input Management

Master or slave inputs can be added/modified/removed with the following code:
```
boardController.addDigitalInput(pin, input_code);
```
where `pin` is the *logical* pin number on the Pico (`GPxx`) and `input_code` is the code to be mapped, generally defined in the `InputCode` enum in `input.h`. New input codes can be added in this enum type.

Reading inputs is done in the corresponding board (master/slave) controller `void update(const EventData& data)` method.

### Serial Communication

Communication is handled via serial data packets. Data can be transmitted with the following code:
```
sendData(serial_code, value);
```
where `serial_code` is the data code and `value` is the actual data value to be sent. New serial codes can be added in the `SerialCode` enum defined in `serial_code.h`.

Receiving data is done in the slave controller `void update(const EventData& data)` method.
