#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

/*
int counter(FILE *fr){
    int count = 0, i = 0;
    char c[N];
    
    while(fgets(c, N, fr) != NULL){
        if(i % 7 == 0){
            count++;
        }
        i++;
    }
    return count;
}
*/

int v(FILE **fr, unsigned long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, char **cas_merania, int **datumy){
    //kontrola, či je súbor otvorený
    if((*fr) == NULL){ 
        (*fr) = fopen("dataloger.txt", "r");
        //kontrola, či sa súbor otvoril
        if((*fr) == NULL){
            printf("Neotvoreny subor\n");
            return -1;
        }
    }

    if(*ID == NULL && *m_modul == NULL && *typ_veliciny == NULL && *hodnoty == NULL && *cas_merania == NULL && *datumy == NULL){
        char c[N];
        int i = 0;
        
        while(fgets(c, N, *fr) != NULL){
            if(i == 0)
                printf("ID cislo mer. osoby: %s",c);
            if(i == 1)
                printf("Mer. modul: %s", c);
            if(i == 2)
                printf("Typ mer. veliciny: %s", c);
            if(i == 3)
                printf("Hodnota: %s", c);
            if(i == 4)
                printf("Cas merania: %s", c);
            if(i == 5)
                printf("Datum: %s", c);
            if(i == 6){
                printf("\n");
                i -= 6;
                continue;
            }
            i++;
        }       
        return 0;
    }
}


void o(FILE *fr, unsigned long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, char **cas_merania, int **datumy){
    //kontrola, či bol súbor otvorený
    if((fr) == NULL){
        printf("Neotvoreny subor");
    }
    
    else{
        if(*ID != NULL && *m_modul != NULL && *typ_veliciny != NULL && *hodnoty != NULL && *cas_merania != NULL && *datumy != NULL){

        }
        else{

        }
    }
}

void n(FILE **fr, unsigned long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, char **cas_merania, int **datumy){
    int num;

    if((*fr) == NULL){
        printf("Neotvoreny subor");
    }
    else{
        if(*ID != NULL && *m_modul != NULL && *typ_veliciny != NULL && *hodnoty != NULL && *cas_merania != NULL && *datumy != NULL){
            free(*ID);
            free(*m_modul);
            free(*typ_veliciny);
            free(*hodnoty);
            free(*cas_merania);
            free(*datumy);
            *ID = NULL;
            *m_modul = NULL;
            *typ_veliciny = NULL;
            *hodnoty = NULL;
            *cas_merania = NULL;
            *datumy = NULL;
        } 
        
        int num = 0, i = 0;
        char c[N];
    
        while(fgets(c, N, *fr) != NULL){
            if(i % 7 == 0){
                num++;
        }
            i++;
        }
        printf("%d", num);

        *ID = malloc(num * sizeof(unsigned long long));
        *m_modul = malloc(num * sizeof(char) * 4);
        *typ_veliciny = malloc(num * sizeof(char)* 3);
        *hodnoty = malloc(num * sizeof(double));
        *cas_merania = malloc(num * sizeof(char) * 5);
        *datumy = malloc(num * sizeof(int));

        /*
        int j = 0;
        i = 0;
        
        for(i; i < num; i++){
            ID[i] = fgets(atoll(c),N, *fr);
            m_modul[i] = fgets(c,N, *fr);
            typ_veliciny[i] = fgets(c,N, *fr);
            hodnoty[i] = fgets(c,N, *fr);
            cas_merania[i] = fgets(c,N, *fr);
            datumy[i] = fgets(c,N, *fr);
            fgets(atoi(c), N, *fr);
        }
       */
    }
}








int main(){

    FILE *fr_dataloger;
    fr_dataloger = NULL;
    unsigned long long* ID = NULL; 
    char* m_modul = NULL;
    char* typ_veliciny = NULL;
    double* hodnoty = NULL;
    char* cas_merania = NULL;
    int* datumy = NULL;

    char x = getchar();

    switch(x){
        case 'v':
            v(&fr_dataloger, &ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy);
        case 'o':
            o(fr_dataloger, &ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy);
        case 'n':
            n(&fr_dataloger, &ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy);
        
        
        
        
        
        
        case 'k':
            if(ID != NULL && m_modul != NULL && typ_veliciny != NULL && hodnoty != NULL && cas_merania != NULL && datumy != NULL){
            free(ID);
            free(m_modul);
            free(typ_veliciny);
            free(hodnoty);
            free(cas_merania);
            free(datumy);
            ID = NULL;
            m_modul = NULL;
            typ_veliciny = NULL;
            hodnoty = NULL;
            cas_merania = NULL;
            datumy = NULL;
            } 
            //funkcia k skontroluje, či bol súbor otvorený, ak áno zavrie ho
            if(fr_dataloger != NULL){
            fclose(fr_dataloger);
            fr_dataloger = NULL;
            }
        }
    return 0;
}