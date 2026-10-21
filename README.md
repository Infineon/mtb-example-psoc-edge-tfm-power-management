# PSOC&trade; Edge MCU: Power management with TF-M

This is a basic code example for getting started with Power management using Trusted Firmware-M (TF-M) and FreeRTOS on PSOC&trade; Edge MCU. The example demonstrates how to initialize the TF-M non-secure (NS) interface and FreeRTOS in the CM33 NS project. The application alternates between active and DeepSleep power modes, waking and sleeping periodically. The code example is designed to work on both Edge Protect Category 2 (EPC2) and Edge Protect Category 4 (EPC4) MCUs. For more information on Edge Protect Categories, see [Infineon Edge Protect](https://www.infineon.com/promo/edge-protect).

This code example has a three project structure: CM33 secure, CM33 non-secure, and CM55 projects.

- *proj_cm33_s:* TF-M is available as source code in the *mtb_shared* directory. *proj_cm33_s* is completely built out of this TF-M library. Only *Makefile* and dependencies are present in this project directory that uses the TF-M library. On EPC2 targets, the TF-M application is executed from the external flash; on EPC4 targets, it is loaded from the external flash to the SRAM for execution

- *proj_cm33_ns:* The NSPE project which contains the TF-M interface and FreeRTOS. The CM33 NS application is executed from the external flash. The project periodically places device in DeepSleep and active power mode, cycling between sleep and wake states

- *proj_cm55:* The M55 NSPE project – while it also has the TF-M interface, it does not call the PSA APIs. It includes the required PSA interface header files and the project is ready to use PSA APIs. The CM55 project is executed from the external flash and contains FreeRTOS

On EPC4 targets, the non-secure interrupts are masked while the device is in DeepSleep, so USER BTN1 cannot wake the non-secure application directly. The example therefore ships a custom **POWER_MANAGER** application root-of-trust partition that owns the USER BTN1 interrupt inside the secure processing environment and reports the wake-up source to the non-secure application over PSA. On EPC2 targets, the non-secure application services USER BTN1 itself and the partition is not built. See the [Design and implementation](docs/design_and_implementation.md) for details.

[View this README on GitHub.](https://github.com/Infineon/mtb-example-psoc-edge-tfm-power-management)

[Provide feedback on this code example.](https://yourvoice.infineon.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyNDMzMjciLCJTcGVjIE51bWJlciI6IjAwMi00MzMyNyIsIkRvYyBUaXRsZSI6IlBTT0MmdHJhZGU7IEVkZ2UgTUNVOiBQb3dlciBtYW5hZ2VtZW50IHdpdGggVEYtTSIsInJpZCI6ImphbGRlZXBtYW5zdWtoYmhhaS5yYW1hbmlAaW5maW5lb24uY29tIiwiRG9jIHZlcnNpb24iOiIxLjAuMCIsIkRvYyBMYW5ndWFnZSI6IkVuZ2xpc2giLCJEb2MgRGl2aXNpb24iOiJNQ0QiLCJEb2MgQlUiOiJJQ1ciLCJEb2MgRmFtaWx5IjoiUFNPQyJ9)

See the [Design and implementation](docs/design_and_implementation.md) for the functional description of this code example.


## Requirements

- [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) v3.9 or later (tested with v3.9)
- Board support package (BSP) minimum required version for:
   - KIT_PSE84_EVAL_EPC2: v1.5.0 or later
   - KIT_PSE84_EVAL_EPC4: v1.5.0 or later
- Programming language: C
- Other tools: Python v3.10 or later
- Associated parts: All [PSOC&trade; Edge E84 MCU](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm/psoc-edge-e84) parts


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v14.2.1 (`GCC_ARM`) – Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.22 (`ARM`)
- IAR C/C++ Compiler v9.70.4 (`IAR`)


## Supported kits (make variable 'TARGET')

- [PSOC&trade; Edge E84 Evaluation Kit](https://www.infineon.com/KIT_PSE84_EVAL) (`KIT_PSE84_EVAL_EPC2`) – Default value of `TARGET`
- [PSOC&trade; Edge E84 Evaluation Kit](https://www.infineon.com/KIT_PSE84_EVAL) (`KIT_PSE84_EVAL_EPC4`)

## Hardware setup

This example does not use the board's default configuration.

Ensure the following jumper and pin configuration on board:

- BOOT SW must be in the LOW/OFF position
- J20 and J21 must be in the tristate/not connected (NC) position


## Software setup

See the [ModusToolbox&trade; tools package installation guide](https://www.infineon.com/ModusToolboxInstallguide) for information about installing and configuring the tools package.

Install a terminal emulator if you do not have one. Instructions in this document use [Tera Term](https://teratermproject.github.io/index-en.html).

Install the Python interpreter and add it to the top of the system path in environmental variables. This code example is tested with [Python v3.10](https://www.python.org/downloads/release/python-31020/).


## Operation

### Add the Edge Protect Bootloader

1. Add **proj_bootloader** to this code example. Follow steps 2 to 9 in the **Operation** section of the [Edge Protect Bootloader](https://github.com/Infineon/mtb-example-edge-protect-bootloader) code example's *README.md* file

   > **Note:** [Edge Protect Bootloader](https://github.com/Infineon/mtb-example-edge-protect-bootloader) *README.md* describes how to add the bootloader to **Basic Secure App**. Add it to **this** code example instead


### Program the application

See [Using the code example](docs/using_the_code_example.md) for instructions on creating a project, opening it in various supported IDEs, and performing tasks such as building, programming, and debugging the application within the respective IDEs.

**Note:** Windows has a 260 character path length limit, so for TF-M application to build successfully, ensure that *\<WorkspacePath>\\\<Application Name>* (including back slash) path is less than or equal to 32 characters.

2. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector

3. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud

4. After programming, the application starts automatically. Confirm that "PSOC Edge MCU: Secure Power Management (using TF_M)" is displayed on the UART terminal

   **Figure 1. Terminal output on program startup**

   ![](images/terminal_startup.png)

5. Application operates in two states, called **APP_STATE_ACTIVE** and **APP_STATE_IDLE**
    - When in **APP_STATE_ACTIVE**, LED1 blinks at 1 kHz. The device stays in this state for 20 seconds
    - When in **APP_STATE_IDLE**, FreeRTOS is configured to enter DeepSleep and is indicated by LED2

    By pressing USER BTN1, you can wake the device up from DeepSleep manually and eventually change the application state to **APP_STATE_ACTIVE**

    On `KIT_PSE84_EVAL_EPC2`, the device additionally leaves **APP_STATE_IDLE** automatically after 10 seconds. On `KIT_PSE84_EVAL_EPC4`, only a USER BTN1 press wakes the device, because non-secure interrupts are masked in DeepSleep and the wake-up is serviced by the secure **POWER_MANAGER** partition

   **Figure 2. Terminal output on application state switch**

   ![](images/terminal_appstate_switch.png)

<br>

## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN235935](https://www.infineon.com/AN235935) – Getting started with PSOC&trade; Edge E84 MCU on ModusToolbox&trade; software <br> AN240096 – Getting started with Trusted Firmware-M (TF-M) on PSOC&trade; Edge
Code examples  | [Using ModusToolbox&trade;](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [PSOC&trade; Edge MCU datasheet](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm#documents) <br> [PSOC&trade; Edge MCU reference manuals](https://www.infineon.com/products/microcontroller/32-bit-psoc-arm-cortex/32-bit-psoc-edge-arm#documents)
Development kits | Select your kits from the [Evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board)
Libraries  | [mtb-dsl-pse8xxgp](https://github.com/Infineon/mtb-dsl-pse8xxgp) – Device support library for PSE8XXGP <br> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port
Tools  | [ModusToolbox&trade;](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use libraries and tools enabling rapid development with Infineon MCUs for applications ranging from wireless and cloud-connected systems, edge AI/ML, embedded sense and control, to wired USB connectivity using PSOC&trade; Industrial/IoT MCUs, AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices, XMC&trade; Industrial MCUs, and EZ-USB&trade;/EZ-PD&trade; wired connectivity controllers. ModusToolbox&trade; incorporates a comprehensive set of BSPs, HAL, libraries, configuration tools, and provides support for industry-standard IDEs to fast-track your embedded application development

<br>


## Other resources

Infineon provides a wealth of data at [www.infineon.com](https://www.infineon.com) to help you select the right device, and quickly and effectively integrate it into your design.


## Document history


Document title: *CE243327* – *PSOC&trade; Edge MCU: Power management with TF-M*

 Version | Description of change
 ------- | ---------------------
 1.0.0   | New code example based on TF-M 2.3.X
<br>


All referenced product or service names and trademarks are the property of their respective owners.

The Bluetooth&reg; word mark and logos are registered trademarks owned by Bluetooth SIG, Inc., and any use of such marks by Infineon is under license.

PSOC&trade;, formerly known as PSoC&trade;, is a trademark of Infineon Technologies. Any references to PSoC&trade; in this document or others shall be deemed to refer to PSOC&trade;.

---------------------------------------------------------

(c) 2026, Infineon Technologies AG, or an affiliate of Infineon Technologies AG. All rights reserved.
This software, associated documentation and materials ("Software") is owned by Infineon Technologies AG or one of its affiliates ("Infineon") and is protected by and subject to worldwide patent protection, worldwide copyright laws, and international treaty provisions. Therefore, you may use this Software only as provided in the license agreement accompanying the software package from which you obtained this Software. If no license agreement applies, then any use, reproduction, modification, translation, or compilation of this Software is prohibited without the express written permission of Infineon.
<br>
Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A SPECIFIC USE/PURPOSE OR MERCHANTABILITY. Infineon reserves the right to make changes to the Software without notice. You are responsible for properly designing, programming, and testing the functionality and safety of your intended application of the Software, as well as complying with any legal requirements related to its use. Infineon does not guarantee that the Software will be free from intrusion, data theft or loss, or other breaches (“Security Breaches”), and Infineon shall have no liability arising out of any Security Breaches. Unless otherwise explicitly approved by Infineon, the Software may not be used in any application where a failure of the Product or any consequences of the use thereof can reasonably be expected to result in personal injury.
