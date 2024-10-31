// STM32L432KC_SPI.c
// TODO: <YOUR NAME>
// TODO: <YOUR EMAIL>
// TODO: <DATE>
// TODO: <SHORT DESCRIPTION OF WHAT THIS FILE DOES>

#include "STM32L432KC_SPI.h"

void initSPI(int br, int cpol, int cpha) {
  // enable SPI
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  // change baud rate
  SPI1->CR1 |= (0b111 << SPI_CR1_BR_Pos);

  // set CPOL and CPHA
  SPI1->CR1 |= _VAL2FLD(SPI_CR1_CPHA, cpha);
  SPI1->CR1 |= _VAL2FLD(SPI_CR1_CPOL, cpol);

  SPI1->CR1 |= _VAL2FLD(SPI_CR1_LSBFIRST, 0b0);
  SPI1->CR1 |= _VAL2FLD(SPI_CR1_CRCEN, 0b0);

  SPI1->CR1 |= _VAL2FLD(SPI_CR1_SSM, 0b1);
  SPI1->CR1 |= _VAL2FLD(SPI_CR1_SSI, 0b1);


  // mcu is master
  SPI1->CR1 |= _VAL2FLD(SPI_CR1_MSTR, 0b1);

  SPI1->CR2 |= (0b0111 << SPI_CR2_DS_Pos);
  SPI1->CR2 |= _VAL2FLD(SPI_CR2_SSOE, 0b1);
  SPI1->CR2 |= _VAL2FLD(SPI_CR2_FRF, 0b0);
  SPI1->CR2 |= _VAL2FLD(SPI_CR2_FRXTH, 0b1);

  SPI1->CR1 |= SPI_CR1_SPE;

  
}

char spiSendReceive(char send) {
  
  
  while(!(SPI1->SR & SPI_SR_TXE)); // wait while its not empty
  

  volatile uint8_t* ptrDR = (volatile uint8_t*)&SPI1->DR;
  *ptrDR = send;

  while(!(SPI1->SR & SPI_SR_RXNE)); // wait while it is empty

  return SPI1->DR;
}