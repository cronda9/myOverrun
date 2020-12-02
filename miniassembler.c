/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero and ???                                        */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;
   unsigned int uiDispLo;
   unsigned int uiDispHi;
         
   uiInstr = 0x10000000;
   
   uiInstr |= uiReg;
    
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   uiDispLo = uiDisp & 0x3;
   uiDispLo = uiDispLo << 29;
   uiInstr |= uiDispLo;
   
   uiDispHi = uiDisp >> 2;
   uiDispHi = uiDispHi << 5;
   uiDispHi &= 0x00ffffe0;
   uiInstr |= uiDispHi;
   
   return uiInstr;
}

unsigned int MiniAssembler_mov(unsigned int uiReg, unsigned int uiImmed)
{
   unsigned int uiInstr;
   /*instruction before implementing uiReg, uiImmed*/
   uiInstr=0x5280000;
   uiInstr |= uiReg;/*instruction*/

   uiImmed <<= 5;/*shift left by 5 to get to correct location*/
   uiImmed &= 0x001fffe0;/*mask by using &=*/
   uiInstr |= uiImmed;/*or this to the instruction*/

   return uiInstr;
}

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
                                unsigned int uiToReg)
{
   unsigned int uiInstr;

   return uiInstr;
}

unsigned int MiniAssembler_b(unsigned long ulAddr,
                             unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int offset;

   /*instruction before implementing params*/
   uiInstr=0x14000000;
   /*calculate and apply offset*/
   offset=ulAddr-ulAddrOfThisInstr;
   /*get rid of the last two bits*/
   offset=offset >> 2;
   /*mask*/
   /*0001 0011 1111 11111 1111 1111 1111 1111 */
   /*1     3   f    f      f    f    f     f*/
   offset &= 0x03ffffff;  
   /*or offset with instruction*/

   uiInstr |= offset;
   return uiInstr;
}
