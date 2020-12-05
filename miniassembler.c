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
   uiInstr = 0x52800000;
   uiInstr |= uiReg;/*instruction*/

   uiImmed <<= 5;/*shift left by 5 to get to correct location*/
   /* 0000 0000 0001 1111 1111 1111 1110 0000 */
   /*    0    0    1    f   f    f    e    0  */
   uiImmed &= 0x001fffe0;/*mask by using &=*/
   uiInstr |= uiImmed;/*or this to the instruction*/

   return uiInstr;
}

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
                                unsigned int uiToReg)
{
   unsigned int uiInstr;
   unsigned int uiDispLo;
   unsigned int mask;
   /*instruction before implementing uiReg, uiImmed*/
   uiInstr = 0x39000000;
   /*uiDispLo = 0x1;
   uiDispLo <<= 9;
   uiInstr |= uiDispLo;*/

   uiInstr |= uiFromReg;
   uiToReg <<= 5;
   uiInstr |= uiToReg;

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
   offset &= 0x03ffffff;  
   /*or offset with instruction*/

   uiInstr |= offset;
   return uiInstr;
}

unsigned int MiniAssembler_bl(unsigned long ulAddr,
                             unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int offset;

   /*instruction before implementing params*/
   uiInstr=0x94000000;
   /*calculate and apply offset*/
   offset=ulAddr-ulAddrOfThisInstr;
   /*get rid of the last two bits*/
   offset=offset >> 2;
   offset &= 0x03ffffff;  
   /*or offset with instruction*/

   uiInstr |= offset;
   return uiInstr;
                                
}