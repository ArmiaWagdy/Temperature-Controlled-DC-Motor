/****************************************************************************************************
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
 
****************************************************************************************************/

#include <mega16.h>
#include <delay.h>
#include <stdio.h>

#define TEST_MODE 0

#if TEST_MODE
    #define ADC_VREF_TYPE 0x60   //VREF = AVCC and LEFT Adjusted
#else
    #define ADC_VREF_TYPE 0xC0   //VREF = INTERNAL and RIGHT Adjusted
#endif


/*******************************Declaring Functions*******************************/


void control_motor(unsigned int);

void control_motor_POT(unsigned int);

void adc_init(void);

unsigned char read_adc(unsigned char);

void usart_init(void);

/**********************************************************************************/


/**************************************Main****************************************/


void main(void)
{

    usart_init();                        
    adc_init();                                                
    DDRB.3 = 1;


    while (1)
        {        
#if !TEST_MODE
        unsigned int Temperature = read_adc(1);             //Read ADC Channel number 1 (PA1)
        Temperature >>= 1;                                  //Divide the reading by 2 to get the temperature
        printf("Temperature = ");                           //Print the temperature value of the hyper terminal
        printf("%u",Temperature);
        printf("C \n");
        delay_ms(2000);                                     //Wait 2 sec to read the temperature again
        control_motor(Temperature);                         //Control the motor using the Temperature value
#else   
        unsigned int Reading = read_adc(1);                 //Read ADC Channel number 1 (PA1)
        printf("Reading = ");                               //Print the reading
        printf("%d",Reading);
        printf("\n");              
        control_motor_POT(Reading);                         //Control the motor using the Reading value
        delay_ms(100);                                      //Wait 100ms to see the change in motor speed
#endif
        };
}


/**********************************************************************************/

/**************************Definition of functions********************************/

void control_motor(unsigned int temp)
{
   if(temp  >= 10 && temp < 25)
   {
      //Motor speed on level 1
      printf("Motor speed level is 1 \n");
      TCCR0 = 0x73;        //Phase correct PWM, Inverted, N = 64        
      OCR0 = 127;          //50% Duty cycle
   }
   else if(temp  >= 25 && temp < 30)
   {  
      //Motor speed on level 2
      printf("Motor speed level is 2 \n");
      TCCR0 = 0x73;        //Phase correct PWM, Inverted, N = 64
      OCR0 = 192;          //75% Duty cycle
   }
   else if(temp  >= 30)
   {                        
      //Motor speed on level 3         
      printf("Motor speed level is 3 \n");
      TCCR0 = 0x73;        //Phase correct PWM, Inverted, N = 64
      OCR0 = 255;          //100% Duty cycle
   } 
}
/**********************************************************************/

void adc_init(void)
{
    // ADC initialization
    // ADC Clock frequency: 57.600 kHz
    // ADC Voltage Reference: Int., cap. on AREF
    // ADC Auto Trigger Source: ADC Stopped
    // Only the 8 most significant bits of
    // the AD conversion result are used
    ADMUX=ADC_VREF_TYPE & 0xff;
    ADCSRA=0x87;
}

/**********************************************************************/

unsigned char read_adc(unsigned char adc_input)
{   
    ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);                           
     // Start the AD conversion
    ADCSRA|=0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;                               
#if TEST_MODE
    return ADCH;
#else
    return ADCW;
#endif
}

/**********************************************************************/

void usart_init(void)
{
    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud Rate: 9600    
    UCSRA=0x00;
    UCSRB=0x18;
    UCSRC=0x86;
    UBRRH=0x00;
    UBRRL=0x2F;
}

/**********************************************************************/

void control_motor_POT(unsigned int pot)
{
    printf("Testing --");                 
    TCCR0 = 0x73;            //Phase correct PWM, Inverted, N = 64
    OCR0  = pot;
}

/************************************************************************/