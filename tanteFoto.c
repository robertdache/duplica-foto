#include <stdio.h>
#include <errno.h>

#define COPIE 10
#define BLOCCO 4096

int main(int n,char* arg[]){
    if(n!=2){
        perror("arguments");
        return 1;
    }
    FILE* fp = fopen(arg[1],"r");
    if(!fp){
        perror("fopen");
        return 1;
    }
    FILE *arrF[COPIE];
    for(int i = 0; i<COPIE;i++){
        char nome[128];
         sprintf(nome,"foto%d.jpg",i);
        arrF[i] = fopen(nome,"w");

        if(!arrF[i]){
            perror("fopen");
            return 1;
        }
    }
    size_t byte_letti;
    char buff[BLOCCO];

    while((byte_letti = fread(buff,1,BLOCCO,fp))>0 ){
        for(int i = 0; i<COPIE;i++){
            fwrite(buff,1,byte_letti,arrF[i]);
        }
    }
    fclose(fp);
    for(int i = 0; i<COPIE; i++){
        fclose(arrF[i]);
    }

    return 0;
}