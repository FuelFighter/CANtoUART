# CANtoUART

Transmits all CAN messages to and from chosen UART. If you want to send custom CAN-messages use a standard serial-reader like Termite, Putty or Arduino(built-in), and send a message on the form [110:2:CAFE]\n, 110 is the hexadecimal ID, 2 is the length of the data in number of bytes, CA is the value of the first byte, FE is the value of the second byte. The ID can range from 000 to 7FF. The length from 1 to 8. The data values from 00 to FFFFFFFFFFFFFFFF, but must always be 2xLength.

Works with both UART0 (USB) and UART1 (HEADER). 
