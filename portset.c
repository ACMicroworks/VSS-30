
#define MCU atmega328p
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/* Library Includes */
#include <avr/io.h>
#include <stdio.h>

/* Function Prototypes */
void init (unsigned int); // USART Initialization
void ser_tx (char); // Serial Transmission (Single Character)

int
main (int argc, char *argv[])
{
  init(MYUBRR);

  for (;;)
    {
      ser_tx('a');
      ser_tx('b');
      ser_tx('c');
    }
  
  return 0;
}

/* USART Definitions */
#define TXEN 0x08
#define RXEN 0x10

/* USART Initialization */
void
init (unsigned int ubrr)
{  
  /* Set the Baud Rate */
  UBRR0H = (unsigned char) (ubrr >> 8);
  UBRR0L = (unsigned char) ubrr;
  
  /* Clear the Baud Rate Transmission Speed Doubler */
  UCSR0A &= ~(1 << U2X0);
  
  /* Enable the Transmitter and Receiver */
  UCSR0B |= TXEN;
  UCSR0B |= RXEN;

  /* Enable Transmitter and Receiver Interrupts */
  //  UCSR0B |= (1 << RXCIE0);
  //  UCSR0B |= (1 << TXCIE0);
  
  /* Set Asynchronous USART */
  UCSR0C |= (1 << UMSEL01);
  UCSR0C |= (1 << UMSEL00);

  /* Frame Formatting (Clock Polarity = 0 for Asynchronous USART) */
  UCSR0C &= !(1 << UCPOL0);
  
  /* Frame Formatting (Parity = None) */
  UCSR0C |= (1 << UPM01);
  UCSR0C |= (1 << UPM00);

  /* Frame Formatting (Stop Bit = 1) */
  UCSR0C &= !(1 << USBS0);

  /* Frame Formatting (Data Bits = 8) */
  UCSR0C |= (1 << UCSZ01);
  UCSR0C |= (1 << UCSZ00);
    
  /* Enable Data Register Empty Interrupt */
  //  UCSR0B |= (1 << UDRIE0);
}

/* Serial Transmission (Single Character) */
void
ser_tx (char c)
{
  while (!(UCSR0A & (1 << UDRE0)))
    ;
      
  UDR0 = c;
}
