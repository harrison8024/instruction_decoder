# Instruction Decoder
### Description
This program is designed to decode binary code into MIPS assembly language. 
### Supported instruction code:
* add, addi, sub, beq, bne, slt, j, jr, sll, srl, lw, sw.
* All 32 registers are supported.
* Offset numbers will be in decimal.
* Jump address is in hexadeciamal.
### Compile and Run
```
gcc -o instruction_decoder instruction_decoder.c
./instruction_decoder XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```
* The X's are 32 digits of binary number