#include <stdio.h>
#include <string.h>

#define LENGTH 32
#define false 0
#define true 1

// Checks that the char array is 32 bits long
// and only has 0 and 1 in it.
int
check (char *bits)
{
  if (strlen (bits) != LENGTH)
    {
      return false;
    }
  for (int i = 0; i < LENGTH; i++)
    {
      if (bits[i] != '0' && bits[i] != '1')
	{
	  return false;
	}
    }
  return true;
}

// We will take the bitstring as a command line argument.
int
main (int argc, char **argv)
{
  // Make sure we have at least one argument.
  if (argc < 2)
    {
      fprintf (stderr, "No argument found\n");
      return -1;
    }
  // Get a pointer to the argument.
  char *instruction = argv[1];
  if (!check (instruction))
    {
      fprintf (stderr, "Invalid bit string\n");
      return -2;
    }
  printf ("Binary: %s\n", instruction);

  // Dictionary for registers
  char *REG[32] = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
  };

  // Convert number string to int
  unsigned int num = 0;
  int multiplier = 1;
  for (int i = strlen (instruction) - 1; i >= 0; i--)
    {
      if (instruction[i] == '1')
	{
	  num += multiplier;
	}
      multiplier *= 2;
    }

  printf ("Decimal: %d\n", num);

  //Check OP Code
  unsigned int opCode = num >> 26;
  printf ("OP: %d\n", opCode);

  if (opCode == 0)
    {
      // If OP = 000000
      // Get FUNC code
      unsigned int funcCode = num << 26;	// use unsigned to avoid negative number
      funcCode = funcCode >> 26;
      printf ("FUNC: %d\n", funcCode);
      switch (funcCode)
	{
	  // ADD
	case 32:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get third register
	    unsigned int tReg = num << 16;
	    tReg = tReg >> 27;
	    char *thirdReg = REG[tReg];

	    printf ("add %s %s %s\n", thirdReg, firstReg, secondReg);
	    break;
	  }
	  // SUB
	case 34:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get third register
	    unsigned int tReg = num << 16;
	    tReg = tReg >> 27;
	    char *thirdReg = REG[tReg];

	    printf ("sub %s %s %s\n", thirdReg, firstReg, secondReg);
	    break;
	  }
	  // SLT
	case 42:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get third register
	    unsigned int tReg = num << 16;
	    tReg = tReg >> 27;
	    char *thirdReg = REG[tReg];

	    printf ("slt %s %s %s\n", thirdReg, firstReg, secondReg);
	    break;
	  }
	  // JR
	case 8:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    printf ("jr %s\n", firstReg);
	    break;
	  }
	  // SLL
	case 0:
	  {
	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get third register
	    unsigned int tReg = num << 16;
	    tReg = tReg >> 27;
	    char *thirdReg = REG[tReg];

	    // Get shift number
	    unsigned int shiftNum = num << 21;
	    shiftNum = shiftNum >> 27;

	    printf ("sll %s %s %d\n", thirdReg, secondReg, shiftNum);
	    break;
	  }
	  // SRL
	case 2:
	  {
	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get third register
	    unsigned int tReg = num << 16;
	    tReg = tReg >> 27;
	    char *thirdReg = REG[tReg];

	    // Get shift number
	    unsigned int shiftNum = num << 21;
	    shiftNum = shiftNum >> 27;

	    printf ("srl %s %s %d\n", thirdReg, secondReg, shiftNum);
	    break;
	  }
	default:
	  {
	    printf ("This instruction is not recognized.\n");
	    break;
	  }
	}

    }
  else
    {
      // If OP code is not 0
      switch (opCode)
	{
	  // ADDI
	case 8:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get Immediate
	    unsigned int imm = num << 16;
	    imm = imm >> 16;

	    printf ("addi %s %s %d\n", firstReg, secondReg, imm);
	    break;
	  }
	  // BEQ
	case 4:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get offset
	    unsigned int offset = num << 16;
	    offset = offset >> 16;

	    printf ("beq %s %s %d\n", firstReg, secondReg, offset);
	    break;
	  }
	  // BNE
	case 5:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get offset
	    unsigned int offset = num << 16;
	    offset = offset >> 16;

	    printf ("bne %s %s %d\n", firstReg, secondReg, offset);
	    break;
	  }
	  // J
	case 2:
	  {
	    // Get address
	    unsigned int address = num << 6;
	    address = address >> 4;
	    address += 0XF0000000;

	    printf ("j 0X%08x\n", address);
	    break;
	  }
	  // LW
	case 35:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;

	    char *secondReg = REG[sReg];

	    // Get offset
	    unsigned int offset = num << 16;
	    offset = offset >> 16;
	    printf ("lw %s %d(%s)\n", secondReg, offset, firstReg);
	    break;
	  }
	  // SW
	case 43:
	  {
	    // Get first register
	    unsigned int fReg = num << 6;
	    fReg = fReg >> 27;
	    char *firstReg = REG[fReg];

	    // Get second register
	    unsigned int sReg = num << 11;
	    sReg = sReg >> 27;
	    char *secondReg = REG[sReg];

	    // Get offset
	    unsigned int offset = num << 16;
	    offset = offset >> 16;

	    printf ("sw %s %d(%s)\n", secondReg, offset, firstReg);
	    break;
	    break;
	  }
	default:
	  {
	    printf ("This instruction is not recognized.");
	    break;
	  }
	}
    }
  return 0;
}
