Temperature-Controlled-DC-Motor
===============================

Project Description: This project aims at controlling a fan according to the 
temperature of surrounding area.

There are two modes for the operation of this project:

(1) TEST_MODE
    This mode is used to test the driver circuit of the motor.
    In this mode a potentiometer is connected to pin ADC1 which is (PA1) and of course
    the other two pins on VCC and GND as usual.
    When you change the resistance value using the POT the motor speed will change gradually.
    If the motor speed changes rightly according to the pot. You can now switch to the 
    other mode.
    
(2) Normal_mode (!TEST_MODE)
    In this mode you will remove the POT from youe circuit and connect your LM35 
    temperature sensor to ADC Channed number '1' which is PA1. (refer to datasheet 
    for the connection of sensor).
    The speed of DC_Motor must change with temperature now as follow:
    If temperature >= 10 and temperature < 25 : The motor will turn on with the lowest speed.
    If temperature >= 25 and temperature < 30 : The motor will turn on with the medium speed.
    If temperature >= 30 : The motor will turn on with the highest speed.
    
    
Pre-condition: I assumed in this project that the lowest temperature value is 10 degrees celsius.
               (As the temperature USUALLY didn't reach a value beyond 10 degree celisus in EGYPT).
               
N.B: The datasheets of components used, flow chart of the program and the driver circuit of the DC FAN
     is attached in the project folder.               