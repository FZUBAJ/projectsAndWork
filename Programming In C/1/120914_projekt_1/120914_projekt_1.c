#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define N 20

//funkcia zistí počet záznamov v textovom súbore
void getsize(FILE **fr, int* p_size){
        (*fr) = fopen("dataloger.txt", "r");
        int i = 0;
        char c[N];
        while(fgets(c, N, *fr) != NULL){
            if(i % 7 == 0){
                (*p_size)++;
        } i++;}
        fclose(*fr);
        *fr = NULL;
}


int v(FILE **fr, long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, int **cas_merania, int **datumy, int size){
    //kontrola, či je súbor otvorený
    if((*fr) == NULL){ 
        (*fr) = fopen("dataloger.txt", "r");
        //kontrola, či sa súbor otvoril
        if((*fr) == NULL){
            printf("Neotvoreny subor\n");
            return -1;
        }
    }

    if(*ID != NULL && *m_modul != NULL && *typ_veliciny != NULL && *hodnoty != NULL && *cas_merania != NULL && *datumy != NULL){
        rewind(*fr);
        for(int i = 0, m = 0, v = 0; i < size; i++, m = i * 3, v = i * 2){
            if((*ID)[i] == 0){}
            else{
                printf("ID cislo mer. osoby: %llu\n", (*ID)[i]);
            }
            
            if((*m_modul)[m] == 0){continue;}
            else{
                printf("Mer. modul: %c%c%c\n", (*m_modul)[m],(*m_modul)[m+1],(*m_modul)[m+2]);
            }
            
            if((*typ_veliciny)[v] == 0){}
            else{
                printf("Typ veliciny: %c%c\n", (*typ_veliciny)[v],(*typ_veliciny)[v+1]);
            }
            if((*hodnoty)[i] == 0){}
            else{
                printf("Hodnoty: %lf\n", (*hodnoty)[i]);
            }
            
            if((*cas_merania)[i] == 0){}
            else{printf("Cas merania: %04d\n", (*cas_merania)[i]);}
            
            if((*datumy)[i] == 0){}
            else{printf("Datum: %d\n", (*datumy)[i]);}
            
            printf("\n");
        }
    }
    // výpis ak neexistujú polia
    else{
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
    }   
        return 0;
}

//deklarujem n pred o, pretoze pouzivam n v o
void n(FILE **fr, long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, int **cas_merania, int **datumy, int size);

void o(FILE **fr, long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, int **cas_merania, int **datumy, int size){
    //kontrola, či bol súbor otvorený
    if((*fr) == NULL){
        printf("Neotvoreny subor\n");
    }
    
    else{
        //ak polia nie su vytvorene
        char mer_modul[4], typ_mer_vel[3];
        scanf("%s %s", mer_modul, typ_mer_vel);
        if(*ID == NULL && *m_modul == NULL && *typ_veliciny == NULL && *hodnoty == NULL && *cas_merania == NULL && *datumy == NULL){
            //volam n funkciu na vytvorenie poli, na konci funkcie dealokujem tieto polia
            n(fr, ID, m_modul, typ_veliciny, hodnoty, cas_merania, datumy, size);
            //vytvaram nove polia, aby som nenarusil povodne
            int new_size = 0;
            char* m_modul_sort = NULL;
            char* typ_mer_vel_sort = NULL;
            double* hodnoty_sort = NULL;
            int* cas_merania_sort = NULL;
            int* datumy_sort = NULL;

            //toto vyzera velmi zaujimavo, ale funguje to
            //kedze pouzivam 1D polia, musim sa s tym takto hrat
            for(int z = 0, i = 0, j = 0, x = 0, y = 0; z < size; z++){
                i = 0, y = 0;
                if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                    i++;
                    j++;
                    if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                        i++;
                        j++;
                        if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                            j -= 2;
                            i ++;
                            if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                x++;
                                y++;
                                if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                    y++;
                                    x--;
                                    //new size je velkost novych poli
                                    new_size++;
                                }
                            }
                        }
                    }
                }
            
            }
            //alokacia novych poli
            m_modul_sort = (char *)malloc(new_size * sizeof(char) * 3);
            typ_mer_vel_sort = (char *)malloc(new_size * sizeof(char) * 2);
            hodnoty_sort = (double *)malloc(new_size * sizeof(double));
            cas_merania_sort = (int *)malloc(new_size * sizeof(int));
            datumy_sort = (int *)malloc(new_size * sizeof(int));


            int index = 0;

            for(int z = 0, i = 0, j = 0, x = 0, y = 0; z < size; z++){
            i = 0, y = 0;
            if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                i++;
                j++;
                if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                    i++;
                    j++;
                    if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                        j -= 2;
                        i ++;
                        if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                            x++;
                            y++;
                            if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                y++;
                                x--;
                                //naplnam polia hodnotami
                                (hodnoty_sort)[index] = (*hodnoty)[z];
                                (cas_merania_sort)[index] = (*cas_merania)[z];
                                (datumy_sort)[index] = (*datumy)[z];
                                    
                                for(int q = z * 3,p = index * 3; p < 3 + (index * 3); p++, q++){
                                    (m_modul_sort)[p] = ((*m_modul)[q]);}

                                for(int q = z * 2, p = index * 2; p < 2 + (index * 2); p++, q++){
                                    (typ_mer_vel_sort)[p] = ((*typ_veliciny)[q]);}
                                    
                                index++;
                            }
                        }
                    }
                }
            }
            
            }
        //docasne premenne, kde ukladam hodnoty pocas sortovania
        int temp1, temp2;
        double temp3;
         for (int i = 0; i < new_size; ++i){
 
            for (int j = i + 1; j < new_size; ++j){
                //nasobim 10000 a scitam, aby som mohol porovnat
                if (((cas_merania_sort)[i] + ((datumy_sort)[i]) * 10000) > (cas_merania_sort[j] + (datumy_sort[j] * 10000))){
 
                    temp1 =  cas_merania_sort[i];
                    cas_merania_sort[i] = cas_merania_sort[j];
                    cas_merania_sort[j] = temp1;

                    temp2 =  datumy_sort[i];
                    datumy_sort[i] = datumy_sort[j];
                    datumy_sort[j] = temp2;

                    temp3 =  hodnoty_sort[i];
                    hodnoty_sort[i] = hodnoty_sort[j];
                    hodnoty_sort[j] = temp3;
 
                }
 
            }
            
         }    
        //print hodnot
        for(int i = 0, y = 0; i < new_size;i++){
            printf("%c%c%c %c%c %d %04d %lf\n", m_modul_sort[y],  m_modul_sort[y+1], m_modul_sort[y+2], typ_mer_vel_sort[y], typ_mer_vel_sort[y+1], datumy_sort[i], cas_merania_sort[i], hodnoty_sort[i]);
        }
        //uvolnenie poli, pretoze by si program myslel, ze funkcia n bola zavolana
        free(*ID);
        free(*m_modul);
        free(*typ_veliciny);
        free(*hodnoty);
        free(*cas_merania);
        free(*datumy);
        free(m_modul_sort);
        free(typ_mer_vel_sort);
        free(datumy_sort);
        free(hodnoty_sort);
        free(cas_merania_sort);

        *ID = NULL; 
        *m_modul = NULL;
        *typ_veliciny = NULL; 
        *hodnoty = NULL; 
        *cas_merania = NULL;
        *datumy = NULL;
        m_modul_sort = NULL;
        typ_mer_vel_sort = NULL;
        datumy_sort = NULL;
        hodnoty_sort = NULL;
        cas_merania_sort = NULL;

        }
        //polia uz su vytvorene, v podstate to iste, len bez volania funkcie n 
        else{
            int new_size = 0;
            char* m_modul_sort = NULL;
            char* typ_mer_vel_sort = NULL;
            double* hodnoty_sort = NULL;
            int* cas_merania_sort = NULL;
            int* datumy_sort = NULL;

            for(int z = 0, i = 0, j = 0, x = 0, y = 0; z < size; z++){
                i = 0, y = 0;
                if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                    i++;
                    j++;
                    if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                        i++;
                        j++;
                        if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                            j -= 2;
                            i ++;
                            if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                x++;
                                y++;
                                if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                    y++;
                                    x--;
                                    new_size++;
                                }
                            }
                        }
                    }
                }
            
            }

            m_modul_sort = (char *)malloc(new_size * sizeof(char) * 3);
            typ_mer_vel_sort = (char *)malloc(new_size * sizeof(char) * 2);
            hodnoty_sort = (double *)malloc(new_size * sizeof(double));
            cas_merania_sort = (int *)malloc(new_size * sizeof(int));
            datumy_sort = (int *)malloc(new_size * sizeof(int));


            int index = 0;

            for(int z = 0, i = 0, j = 0, x = 0, y = 0; z < size; z++){
            i = 0, y = 0;
            if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                i++;
                j++;
                if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                    i++;
                    j++;
                    if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                        j -= 2;
                        i ++;
                        if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                            x++;
                            y++;
                            if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                y++;
                                x--;

                                (hodnoty_sort)[index] = (*hodnoty)[z];
                                (cas_merania_sort)[index] = (*cas_merania)[z];
                                (datumy_sort)[index] = (*datumy)[z];
                                    
                                for(int q = z * 3,p = index * 3; p < 3 + (index * 3); p++, q++){
                                    (m_modul_sort)[p] = ((*m_modul)[q]);}

                                for(int q = z * 2, p = index * 2; p < 2 + (index * 2); p++, q++){
                                    (typ_mer_vel_sort)[p] = ((*typ_veliciny)[q]);}
                                    
                                index++;
                            }
                        }
                    }
                }
            }
            
            }
        
        int temp1, temp2;
        double temp3;
         for (int i = 0; i < new_size; ++i){
 
            for (int j = i + 1; j < new_size; ++j){
 
                if (((cas_merania_sort)[i] + ((datumy_sort)[i]) * 10000) > (cas_merania_sort[j] + (datumy_sort[j] * 10000))){
 
                    temp1 =  cas_merania_sort[i];
                    cas_merania_sort[i] = cas_merania_sort[j];
                    cas_merania_sort[j] = temp1;

                    temp2 =  datumy_sort[i];
                    datumy_sort[i] = datumy_sort[j];
                    datumy_sort[j] = temp2;

                    temp3 =  hodnoty_sort[i];
                    hodnoty_sort[i] = hodnoty_sort[j];
                    hodnoty_sort[j] = temp3;
 
                }
 
            }
            
         }    
        
        for(int i = 0, y = 0; i < new_size;i++){
            printf("%c%c%c %c%c %d %04d %lf\n", m_modul_sort[y],  m_modul_sort[y+1], m_modul_sort[y+2], typ_mer_vel_sort[y], typ_mer_vel_sort[y+1], datumy_sort[i], cas_merania_sort[i], hodnoty_sort[i]);
        }

        free(m_modul_sort);
        free(typ_mer_vel_sort);
        free(datumy_sort);
        free(hodnoty_sort);
        free(cas_merania_sort);

        m_modul_sort = NULL;
        typ_mer_vel_sort = NULL;
        datumy_sort = NULL;
        hodnoty_sort = NULL;
        cas_merania_sort = NULL;
 
        }

    }
}

void n(FILE **fr, long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, int **cas_merania, int **datumy, int size){

    if((*fr) == NULL){
        printf("Neotvoreny subor\n");
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
    //alokujem polia, je tam * 3 lebo robim jednorozmerne polia
    (*ID) = (long long *)malloc(size * sizeof(long long));
    (*m_modul) = (char *)malloc(size * (sizeof(char) * 3));
    (*typ_veliciny) = (char *)malloc(size * sizeof(char)* 2);
    (*hodnoty) = (double *)malloc(size * sizeof(double));
    (*cas_merania) = (int *)malloc(size * sizeof(int));
    (*datumy) = (int *)malloc(size * sizeof(int));

    rewind(*fr);
    char c[N];
    int i = 0;
    //naplnam polia hodnotami
    while(!feof(*fr)){
        fgets(c, N, *fr);
        (*ID)[i] = atoll(c); 
        //for cykly, lebo jednorozmerne pole a z jedneho riadku mam 3 miesta v poliach
        fgets(c, N, *fr);
        for(int x = i * 3; x < 3 + (i * 3); x++){
            (*m_modul)[x] = c[x % 3];
        }
        
        fgets(c, N, *fr);
        for(int x = i * 2; x < 2 + (i * 2); x++){
            (*typ_veliciny)[x] = c[x % 2];
        } 
            
        fgets(c, N, *fr);
        (*hodnoty)[i] = atof(c);

        fgets(c, N, *fr);
        (*cas_merania)[i] = atoi(c);

        fgets(c, N, *fr);
        (*datumy)[i] = atoi(c);

        fgets(c, N, *fr);
        i++;
    }    
    }
}

void c (FILE **fr){
    if(*fr == NULL){
        printf("Neotvoreny subor\n");
    }
    else{
        //ak sa stane chyba bool sa zmeni na true a nevyprintuje sa sprava o bezchybnosti vstupu
        bool chyba_ID = false, chyba_mer_modul = false, chyba_mer_vel = false, chyba_hodnoty = false, chyba_cas_mer = false, chyba_datum = false;
        char c[N];
        rewind(*fr);

        while(!feof(*fr)){
    
        //IDcko
        fgets(c,N,*fr);
        //odcitavam -2 lebo v strlen su zahrnute dva znaky naviac pred '\0' a to '\n' a '\r'
        if((strlen(c)-2) != 10 || (atoll(c)) % 11 != 0){
            chyba_ID = true; 
        }
    
        //mer. modul
    
        fgets(c,N,*fr);
        if(strlen(c) - 2 != 3){
            chyba_mer_modul = true;
        }
        //kontrola ci je prvy znak velke pismeno z intervalu <A,Z>
        if(c[0] < 65 || c[0] > 90){
            chyba_mer_modul = true;
        }
    
        //kontrola ci je cislo od 0 do 9 - reprezentovane ASCII tabulkou znakov
        if(((48 <= c[1]) && (c[1] <= 57)) && ((48 <= c[2]) && (c[2]) <= 57)){
        }
        else{
            chyba_mer_modul = true;
        }
    

        //typ meracej veliciny
        fgets(c,N,*fr);
        if((strlen(c)) - 2 != 2){
            chyba_mer_vel = true;
            }
        //kontrolujem ci obsahuje meracia velicina to co ma
        if((c[0] != 'R') && (c[0] != 'U') && (c[0] != 'A')){
            chyba_mer_vel = true;
            }
        if((c[1] != '1') && (c[1] != '2') && (c[0] != '4')){
            chyba_mer_vel = true;
            }
    
    
        //hodnota
        fgets(c,N,*fr);
        int bodka = 0,i,x = strlen(c) - 2;
        //kontrolujem ci vsetky znaky stringu su ciselne, jedina vynimka je bodka (moze byt len jedna)
        for(i = 0; i < x; i++){
            if(c[i] == '.' || isdigit(c[i])){
                if(c[i] == '.'){
                    bodka++;
                }
            }
            else{chyba_hodnoty = true;}
            
            if(bodka == 1 || bodka == 0){}
            else{chyba_hodnoty = true;}
        }
    


    
        //cas merania
        fgets(c,N,*fr);
        if((strlen(c)) - 2 != 4){chyba_cas_mer = true;}
        
        //kontrola ci je prvy charakter <0,2>, a ak je dva, tak ci je druhy charakter mensi alebo rovny 3
        if((48 <= c[0]) && ((c[0]) <= 50)){   
            if(c[0] == 50){
                if(48 <= (c[1]) && (c[1]) < 52){
                }
                else{
                    chyba_cas_mer = true;
                }
            }
        }
        else{chyba_cas_mer = true;}
        
        //kontrola ci je druhy charakter cislo <0,9>, ak by tam bolo napr. 2520 tak napise chybu uz v predoslej ulohe
        if((48 <= c[1]) && ((c[1]) <= 57)){}
        else{chyba_cas_mer = true;}
        
        //kontrola ci je treti charakter <0,5>
        if((48 <= c[2]) && (c[2] <= 53)){}
        else{chyba_cas_mer = true;}
        
        //kontrola, ci je na konci <0,9>
        if((48 <= c[3]) && (c[3] <= 57)){}
        else{chyba_cas_mer = true;}
        
        //datum

        fgets(c,N,*fr);
        
        if(strlen(c) - 2 != 8){
            chyba_datum = true;
        }

        int rok = atoi(c) / 10000;
        int mesiac = (atoi(c) / 100) % 100;
        int den = atoi(c) % 100;

        if(rok >= 0 && rok < 10000){}
        else{chyba_datum = true;}
        
        if((1 <= mesiac) && (mesiac <= 12)){}
        else{chyba_datum = true;}
        
        if((1 <= den) && (den <= 31)){}
        else{chyba_datum = true;}
        
        //kontrola februara a prestupneho roka
        if(mesiac == 2){
            if(rok % 4 == 0){
                if(den <= 29){}
                else{chyba_datum = true;}

            }
            else{
                if(den <= 28){}
                else{ chyba_datum = true;}
            }
        }

    fgets(c, N, *fr);
    }
    
    if(chyba_ID == false && chyba_cas_mer == false && chyba_datum == false && chyba_hodnoty == false && chyba_mer_modul == false && chyba_mer_vel == false){
        printf("Data su korektne.\n");
    }
    //ak sa zmeni bool na true tak sa printne nieco z tohto, zalezi na tom aka chyba
    else if (chyba_ID == true){printf("Nekorektne zadany vstup: ID cislo mer. osoby.\n");}
    else if (chyba_mer_modul == true){printf("Nekorektne zadany vstup: Mer. modul.\n");}
    else if (chyba_mer_vel == true){printf("Nekorektne zadany vstup: Typ. mer veliciny.\n");}
    else if (chyba_hodnoty == true){printf("Nekorektne zadany vstup: Hodnota. \n");}
    else if (chyba_cas_mer == true){printf("Nekorektne zadany vstup: Cas merania.\n");}
    else if (chyba_datum == true){printf("Nekorektne zadany vstup: Datum.\n");}
    }
}

void z(long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, int **cas_merania, int **datumy, int size){
    long long delete;
    int vymazane = 0;
    
    if(*ID == NULL){
        printf("Polia nie su vytvorene.\n");
    }
    else{
        scanf("%lld", &delete);
        //mazem takym sposobom, ze zmenim zaznam na nulovu hodnotu a potom to je osetrene aj v ostatnych funkciach, napr. vo v sa neprintnu vymazane zaznamy
        for(int i = 0; i < size; i++){
            if((*ID)[i] == delete){
                (*ID)[i] = 0;
                
                for(int j = i * 3; j < (i*3) + 3; j++){
                (*m_modul)[j] = 0;
                }

                for(int x = i * 2; x < (i*2) + 2; x++){
                (*typ_veliciny)[x] = 0;
                }

                (*hodnoty)[i] = 0;
                (*cas_merania)[i] = 0;
                (*datumy)[i] = 0;
                vymazane++;
            }
        }
    }
    printf("Vymazalo sa: %d zaznamov!\n", vymazane);
}

void h(char **typ_veliciny, double **hodnoty, int size){
    
    char z_typ_mer[3];
    char c[N];
    int interval1 = 0, interval2 = 0, interval3 = 0, interval4 = 0, interval5 = 0, interval6 = 0, interval7 = 0;
    
    if(*typ_veliciny == NULL){
        printf("Polia nie su vytvorene.\n");
    }

    else {
    scanf("%s", z_typ_mer);
    
    for(int x = 0,i = 0; x < size; x++,i += 2){
        if(((z_typ_mer)[0] == (*typ_veliciny)[i]) && ((z_typ_mer)[1]) == ((*typ_veliciny)[i+1])){
            if((*typ_veliciny)[i] != 0){
            if((0.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 5.0){interval1 ++;}
            if((5.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 10.0){interval2 ++;}
            if((15.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 20.0){interval3 ++;}
            if((40.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 45.0){interval4 ++;}
            if((45.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 50.0){interval5 ++;}
            if((50.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 55.0){interval6 ++;}
            if((150.0 < (*hodnoty)[x]) && ((*hodnoty)[x]) <= 155.0){interval7 ++;}
            }
        }
    }

    printf("\t%s\t\t\tpocetnost\n", z_typ_mer);
    printf("   (  0.0-   5.0>\t\t   %d\n", interval1);
    printf("   (  5.0-  10.0>\t\t   %d\n", interval2);
    printf("   ( 15.0-  20.0>\t\t   %d\n", interval3);
    printf("   ( 40.0-  45.0>\t\t   %d\n", interval4);
    printf("   ( 45.0-  50.0>\t\t   %d\n", interval5);
    printf("   ( 50.0-  55.0>\t\t   %d\n", interval6);
    printf("   (150.0- 155.0>\t\t   %d\n", interval7);



    }
}

void r(int **cas_merania, int size){
    //vytvorenie noveho dynamickeho pola, v ktorom usporiadam hodnoty
    int* usporiadane_casy = NULL;
    int i = 0, temp;
    char c[N];

    //check ci su polia vytvorene
    if(*cas_merania == NULL){
        printf("Polia nie su vytvorene.\n");
    }

    //alokacia pola, ktore sortnem
    else{
    usporiadane_casy = (int *)malloc(size * sizeof(int));

    //"nakopirovanie" jedneho pola do druheho
    for(i = 0; i < size; i++){
        (usporiadane_casy)[i] = (*cas_merania)[i];
    }
    
    //sortovanie pola od najmensiego casu
    for (i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j){
                if ((usporiadane_casy)[i] > usporiadane_casy[j]){
                    temp =  usporiadane_casy[i];
                    usporiadane_casy[i] = usporiadane_casy[j];
                    usporiadane_casy[j] = temp;
                }
 
            }
 
        }

    //finalny for cyklus
    int hodina, minuta, predosly_cas = 0, predosla_hodina = 0;
    for(i = 0; i < size; i++){
       if((usporiadane_casy[i]) != predosly_cas){
            hodina = (usporiadane_casy)[i]/100;
            minuta = (usporiadane_casy)[i]%100;
            if(hodina != 0 && hodina != predosla_hodina){
                printf("\n");
                printf("%02d:%02d", hodina, minuta);
            }
            if(hodina != 0 && hodina == predosla_hodina){
                printf(",");
                printf("%02d", minuta);
            }
       }
        
        predosly_cas = (usporiadane_casy)[i];
        //hodinu zistujem delenim 100 a % ziskavam minuty
        predosla_hodina = ((usporiadane_casy)[i]) / 100;
    } printf("\n");
    //uvolnenie pola, ktore som vytvoril
    free(usporiadane_casy);
    usporiadane_casy = NULL;
    }
}

void s(long long **ID, char **m_modul, char **typ_veliciny, double **hodnoty, int **cas_merania, int **datumy, int size){
    //velmi podobne ako funkcia o, iba na konci pisem do suboru
    if(*ID == NULL){
        printf("Polia nie su vytvorene.\n");
    }
    else{
        char mer_modul[4], typ_mer_vel[3];
        scanf("%s %s", mer_modul, typ_mer_vel);

    int new_size = 0;
        char* m_modul_sort = NULL;
        char* typ_mer_vel_sort = NULL;
        double* hodnoty_sort = NULL;
        int* cas_merania_sort = NULL;
        int* datumy_sort = NULL;

            for(int z = 0, i = 0, j = 0, x = 0, y = 0; z < size; z++){
                i = 0, y = 0;
                if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                    i++;
                    j++;
                    if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                        i++;
                        j++;
                        if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                            j -= 2;
                            i ++;
                            if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                x++;
                                y++;
                                if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                    y++;
                                    x--;
                                    new_size++;
                                }
                            }
                        }
                    }
                }
            
            }
            //ak sa nenachadza zvoleny mer. modul alebo mer. velicina vypise sa toto
            if(new_size == 0){
                printf("Pre dany vstup neexistuju zaznamy.\n");
            }

            else{
            //ak ano alokujem opät polia
            m_modul_sort = (char *)malloc(new_size * sizeof(char) * 3);
            typ_mer_vel_sort = (char *)malloc(new_size * sizeof(char) * 2);
            hodnoty_sort = (double *)malloc(new_size * sizeof(double));
            cas_merania_sort = (int *)malloc(new_size * sizeof(int));
            datumy_sort = (int *)malloc(new_size * sizeof(int));


            int index = 0;

            for(int z = 0, i = 0, j = 0, x = 0, y = 0; z < size; z++){
            i = 0, y = 0;
            if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                i++;
                j++;
                if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                    i++;
                    j++;
                    if((mer_modul[j]) == ((*m_modul)[i + (z * 3)])){
                        j -= 2;
                        i ++;
                        if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                            x++;
                            y++;
                            if((typ_mer_vel[x]) == ((*typ_veliciny)[y + (z * 2)])){
                                y++;
                                x--;

                                (hodnoty_sort)[index] = (*hodnoty)[z];
                                (cas_merania_sort)[index] = (*cas_merania)[z];
                                (datumy_sort)[index] = (*datumy)[z];
                                    
                                for(int q = z * 3,p = index * 3; p < 3 + (index * 3); p++, q++){
                                    (m_modul_sort)[p] = ((*m_modul)[q]);}

                                for(int q = z * 2, p = index * 2; p < 2 + (index * 2); p++, q++){
                                    (typ_mer_vel_sort)[p] = ((*typ_veliciny)[q]);}
                                    
                                index++;
                            }
                        }
                    }
                }
            }
            
            }
        
        int temp1, temp2;
        double temp3;
         for (int i = 0; i < new_size; ++i){
 
            for (int j = i + 1; j < new_size; ++j){
 
                if (((cas_merania_sort)[i] + ((datumy_sort)[i]) * 10000) > (cas_merania_sort[j] + (datumy_sort[j] * 10000))){
 
                    temp1 =  cas_merania_sort[i];
                    cas_merania_sort[i] = cas_merania_sort[j];
                    cas_merania_sort[j] = temp1;

                    temp2 =  datumy_sort[i];
                    datumy_sort[i] = datumy_sort[j];
                    datumy_sort[j] = temp2;

                    temp3 =  hodnoty_sort[i];
                    hodnoty_sort[i] = hodnoty_sort[j];
                    hodnoty_sort[j] = temp3;
 
                }
            }
        }
            
    
        //vytvorenie suboru
        FILE *fw = fopen("vystup_S.txt", "w");
        
        //keby sa nepodari otvorit subor
        if(fw == NULL){
            printf("Nepodarilo sa vytvoriť súbor.\n");
        }

        else{
        for(int i = 0; i < new_size; i++){
            fprintf(fw,"%d%04d %.07lf\n", datumy_sort[i], cas_merania_sort[i], hodnoty_sort[i]);
        }

        printf("Pre dany vstup je vytvoreny txt subor.\n");
        //zatvorenie suboru
        fclose(fw);
        //uvolnenie poli
        free(m_modul_sort);
        free(typ_mer_vel_sort);
        free(datumy_sort);
        free(hodnoty_sort);
        free(cas_merania_sort);

        m_modul_sort = NULL;
        typ_mer_vel_sort = NULL;
        datumy_sort = NULL;
        hodnoty_sort = NULL;
        cas_merania_sort = NULL;
            }
        }
    }
}

int main(){

    FILE *fr_dataloger;
    fr_dataloger = NULL;
    
    long long* ID = NULL; 
    char* m_modul = NULL;
    char* typ_veliciny = NULL;
    double* hodnoty = NULL;
    int* cas_merania = NULL;
    int* datumy = NULL;
    int size = 0;
    char x;
    bool start = true;
    
    getsize(&fr_dataloger, &size);
    
    while(start){
        
        scanf(" %c", &x);
        
        switch(x){
            
            case 'v':{
                v(&fr_dataloger, &ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy, size);
            }    
                break;
            
            case 'o':{
                o(&fr_dataloger, &ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy, size);
            }
                break;
            
            case 'n':{
                n(&fr_dataloger, &ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy, size);
            }    
                break;
            
            case 'c':{
                c(&fr_dataloger);
            }   break;
            
            case 'z':{
                z(&ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy, size);
            }   break;

            case 'h':{
                h(&typ_veliciny, &hodnoty, size);
            }   break;
            
            case 'r':{
                r(&cas_merania, size);
            }   break;
            
            case 's':{
                s(&ID, &m_modul, &typ_veliciny, &hodnoty, &cas_merania, &datumy, size);
            }   break;
        
            case 'k':{
                if(ID != NULL && m_modul != NULL && typ_veliciny != NULL && hodnoty != NULL && cas_merania != NULL && datumy != NULL){
                    //uvolnujem takto lebo iba 1D polia
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
                start = false;
            }
                break;
            
            default:
            {
                    printf("Nespravny znak.\n");
            } 
                break;
        }
    }
    return 0;
}
