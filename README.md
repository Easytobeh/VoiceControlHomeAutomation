# VoiceControlHomeAutomation
TITLE:                |   Arduino - Control simple home appliances with voice commands
STACK:                |   All codes are written in C++ Arduino syntax. 
MICROCNOTROLLER:      |   ATmega328 AVR
PROGRAMMING METHOD:   |   Arduino ICSP - In-CIircuit Serial Programming
PROGRAMMER:           |   Arduino UNO board
------------------------------------------------------------------------------------------------------------------------


As described by the title, this code is written for a home automation device. The function of which is to control electrical
power usage across several domestic home appliances. This is designed for the purpose of controlling 5 different Electrical Circuits
which may include loads such as Fan, Light, Television, etc.
There are two parts to this, A voice controlled part, and a Motion/Human presence controlled part which are independent of each other.
                               ------------------------------------------------------
                                                    MOTION  CONTROL 
                               ------------------------------------------------------
MOTION DETECTOR/TRANSMITTER DEVICE

This part of the circuit constitutes an aspect of the device. It is a saprate device with its onw microcontroller, hence unique source code.
It has a PIR motion sensor, LDR for determining the luminosity of the environment and a 413MHz Radio Frequency Transmitter module for sending 
a unique string of data when human presence is detected.
This data is captured by the control circuit.

CONTROL CIRCUIT

This part has it's own microcontroller and circuitry too. It has a 413MHz RF Receiver to capture signals from the MOTION DETECTOR DEVICE.
This in turn controls the relay to switch the particular load at that point.

                               ------------------------------------------------------
                                                    VOICE CONTROL
                               ------------------------------------------------------
The voice control is the elechouse voice recognition module v3.1. Checkout https://www.elechouse.com/elechouse/index.php?main_page=product_info&products_id=2254 for more details. 