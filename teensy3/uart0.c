#include "kinetis.h"

// This BAUD_DIV gives a baud of 230400.
static unsigned BAUD_DIV = 52;
static unsigned BAUD_FINE = 0x03;

void uart0_init(void) {
  // Enable UART0 clock gate.
  SIM_SCGC4 |= SIM_SCGC4_UART0;

  // UART0_TX
  PORTE_PCR20 = PORT_PCR_PE | PORT_PCR_PS | PORT_PCR_PFE | PORT_PCR_MUX(4);
  // UART0_RX
  PORTE_PCR21 = PORT_PCR_DSE | PORT_PCR_SRE | PORT_PCR_MUX(4);

  UART0_BDH = (uint8_t) (BAUD_DIV >> 8);
  UART0_BDL = (uint8_t) BAUD_DIV;
  UART0_C4 = BAUD_FINE;

  UART0_C1 = UART_C1_M | UART_C1_PE | UART_C1_ILT;

  UART0_PFIFO = 0;
  UART0_S2 |= 0x00;
  UART0_C3 |= 0x00;

  // Enable transmission only.
  UART0_C2 = UART_C2_TE;
}

void uart0_putc(uint8_t c) {
  // Wait until the transmit data buffer is empty.
  while ((UART0_S1 & UART_S1_TDRE) == 0);
  UART0_D = c;
}
