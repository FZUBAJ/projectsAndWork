#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER 50

typedef struct entry{ //definujem si strukturu
   long long id_num;
   char person_name[30];
   char m_modul[6];
   char type_of_m[6];
   double val;
   int time;
   int date;
   struct entry *next;
}ENTRY;

int get_size(FILE* fr){ //funkcia get_size zistuje pocet zaznamov, pomocou pocitania poctu $$$
    int size;
    char line [BUFFER];
    rewind(fr); //pointer na zaciatok suboru
    while(!(feof(fr))){
        fgets(line, BUFFER, fr);
        if(strcmp(line, "$$$\r\n") == 0){
            size++;
        }
    }   
    return size; //vracia velkost
}

void delete(ENTRY **node){ //prejdem cez cely linked list a uvolnim pamat v kazdom prvku
    ENTRY* temp;
    while((*node) != NULL){
        temp = (*node);
        *node = (*node)->next;
        free(temp);
        temp = NULL;
    }
}

void swapping_nods(ENTRY** tmp1, ENTRY** tmp2){ //funkcia na vymenu dat dvoch nodes, vzdy pomocna premenna kde ulozim data
    long long ID = (*tmp2)->id_num;
    (*tmp2)->id_num = (*tmp1)->id_num;
    (*tmp1)->id_num = ID;

    char name[50];
    strcpy(name, (*tmp2)->person_name);
    strcpy((*tmp2)->person_name, (*tmp1)->person_name);
    strcpy((*tmp1)->person_name, name);    
    char modul[10];
    strcpy(modul, (*tmp2)->m_modul);
    strcpy((*tmp2)->m_modul, (*tmp1)->m_modul);
    strcpy((*tmp1)->m_modul, modul);

    char typ[10];
    strcpy(typ, (*tmp2)->type_of_m);
    strcpy((*tmp2)->type_of_m, (*tmp1)->type_of_m);
    strcpy((*tmp1)->type_of_m, typ);

    double val = (*tmp2)->val;
    (*tmp2)->val = (*tmp1)->val;
    (*tmp1)->val = val;

    int time = (*tmp2)->time;
    (*tmp2)->time = (*tmp1)->time;
    (*tmp1)->time = time;

    int date = (*tmp2)->date;
    (*tmp2)->date = (*tmp1)->date;
    (*tmp1)->date = date;
}

void new_node(ENTRY** node){ //vytvorenie noveho prvku spajaneho zoznamu, vzdy naskenujem vstup a ulozim do prvku
    char line[BUFFER];
    
    printf("Zadaj ID cislo mer. osoby: \n");
    scanf("%lld", &((*node)->id_num));
                
    printf("Zadaj meno osoby: \n");
    getchar();
    fgets(line, BUFFER, stdin);
    line[strcspn(line, "\n")] = 0; //toto mi odstrani \n\r zo stringu 
    strcpy((*node)->person_name, line);
               
    printf("Zadaj mer. modul: \n");
    char meraci[30];
    scanf("%s", meraci);
    strcpy((*node)->m_modul, meraci);
                
    printf("Zadaj typ mer. veliciny: \n");
    char typ[30];
    scanf("%s", typ);
    strcpy((*node)->type_of_m, typ);
                
    printf("Zadaj hodnotu: \n");
    scanf("%lf", &(*node)->val);
                
    printf("Zadaj cas merania: \n");
    scanf("%d", &((*node)->time));
                
    printf("Zadaj datum merania: \n");
    scanf("%d", &((*node)->date));
}

void n(FILE **fr, ENTRY **head, ENTRY **new, ENTRY **temp, int size)
{
    char line[BUFFER];
    rewind(*fr);
    
    if((*head) != NULL){
        delete(head);
    }
    
    for(int i = 0; i < size; i++){
        (*temp) = (ENTRY*)malloc(sizeof(ENTRY));
        
        fgets(line, BUFFER, *fr); ///$$$ prvý riadok, ktorý nechcem
        fgets(line, BUFFER, *fr);
        (*temp)->id_num = atoll(line);
        fgets(line, BUFFER, *fr);
        line[strcspn(line, "\n")] = 0;
        strcpy((*temp)->person_name,line);
        fgets(line, BUFFER, *fr);
        line[strcspn(line, "\n")] = 0;
        strcpy((*temp)->m_modul,line);
        fgets(line, BUFFER, *fr);
        line[strcspn(line, "\n")] = 0;
        strcpy((*temp)->type_of_m,line);
        fgets(line, BUFFER, *fr);
        (*temp)->val = atof(line);
        fgets(line, BUFFER, *fr);
        (*temp)->time = atoi(line);
        fgets(line, BUFFER, *fr);
        (*temp)->date = atoi(line);
        (*temp)->next = NULL;
                
        if((*head) == NULL){
            (*head) = (*temp);
        }
        else{
            (*new) = (*head);
            while((*new)->next != NULL){
                (*new) = (*new)->next;  
            }
                (*new)->next = (*temp);
        }
    }   
    printf("Nacitalo sa %d zaznamov.\n", size);  
}

void v(ENTRY *head, ENTRY *new){ 
    int counter = 1; //pocitam zaznamy
    new = head; //new na head, aby som nestratil povodnu adresu prveho prvku zoznamu
    if(head == NULL){}
    else{
    while(new != NULL){   //printovanie celeho zoznamu
        printf("%d: \n", counter);
        printf("ID cislo mer. osoby: %lld\n", (new)->id_num);
        printf("Meno osoby: %s\n", (new)->person_name);
        printf("Mer. modul: %s\n", (new)->m_modul);
        printf("Typ mer. veliciny: %s\n", (new)->type_of_m);
        printf("Hodnota: %lf\n", (new)->val);
        printf("Cas merania: %04d\n", (new)->time);
        printf("Datum: %d\n", (new)->date);
        printf("\n");
        (new) = (new)->next;
        counter++;
        }
    }
}

void z(ENTRY **head)
{
    if(*head == NULL){}
    else {
    ENTRY* tmp1 = (*head);
    long long id;
    printf("Zadaj ID, ktore chces vymazat:\n");
    scanf("%lld", &id);
    while(tmp1->next != NULL){
        if(tmp1->id_num == id){
            if(tmp1 == (*head)){
                printf("Zaznam pre ID: %lld bol vymazany pre modul %s\n", id, tmp1->m_modul);
                (*head) = (*head)->next; //ak je to head, iba posunieme na dalsi prvok, a vymazeme
                free(tmp1);
                tmp1 = *head;
            }
            else{
                ENTRY* tmp2 = *head;
                while(tmp2->next != tmp1){ //ak to je dalej, tak sa dostaneme pred ziadany prvok, a namiesto tmp1 dame za tmp2 tmp1->next
                    tmp2 = tmp2->next;
                }
                tmp2->next = tmp1->next; //uvolnime pamat a tmp1 teda bude rovne tmp2->next
                free(tmp1);
                tmp1 = tmp2->next;
                if(tmp1 == NULL){ //check ak to bude na konci
                    tmp2->next = NULL;
                }
            printf("Zaznam pre ID: %lld bol vymazany pre modul %s\n", id, tmp1->m_modul);
            }
        } else
        tmp1 = tmp1->next;
        }
        
        if(tmp1->id_num == id){ //v pripade ze mazeme posledny prvok zoznamu, tak iba uvolnime tmp1 a tmp2->next (prvok pred tmp1) ukazuje na NULL
            printf("Zaznam pre ID: %lld bol vymazany pre modul %s\n", id, tmp1->m_modul);
            ENTRY* tmp2 = *head;
            while(tmp2->next != tmp1){
                tmp2 = tmp2->next;
            }
            tmp2->next = NULL;
            free(tmp1);
        }
    }
}

void h(ENTRY **head){
    ENTRY* temp = *head;
    int counter = 1;
    char mer_modul[6];
    scanf("%s", mer_modul);
    
    if(*head == NULL){}
    else{
    while(temp != 0){ //porovnam vstup a nacitane data, z nejakeho dovodu mi strcmp nefungoval tak takto
        if((temp->m_modul)[0] == mer_modul[0] && (temp->m_modul)[1] == mer_modul[1] && (temp->m_modul)[2] == mer_modul[2]){
            printf("%d: \n", counter);
            printf("ID cislo mer. osoby: %lld\n", (temp)->id_num);
            printf("Meno osoby: %s\n", (temp)->person_name);
            printf("Mer. modul: %s\n", (temp)->m_modul);
            printf("Typ mer. veliciny: %s\n", (temp)->type_of_m);
            printf("Hodnota: %lf\n", (temp)->val);
            printf("Cas merania: %04d\n", (temp)->time);
            printf("Datum: %d\n", (temp)->date);
            printf("\n");
            counter++;
            temp = temp->next;
        }
        else{
            temp = temp->next;
        }
    }
}
}

void u(ENTRY **head){
    if(*head == NULL){
        printf("Chyba\n");
    }
    else{
    ENTRY* tmp1 = NULL, * tmp2 = NULL;
    for(tmp1 = (*head); tmp1 != NULL; tmp1 = tmp1->next){ //for cyklom prejdem až na koniec zoznamu a porovnavam prvky medzi sebou
        for(tmp2 = (*head); tmp2 != NULL; tmp2 = tmp2->next){
            if(((tmp1->date)*10000) + (tmp1->time) < ((tmp2->date)*10000) + (tmp2->time)) //pre jednoduchsie sortovanie nasobim a scitam
            {
                swapping_nods(&tmp1, &tmp2); //opat funkcia na vymenu dat
            }
        }
    }
    printf("Spajany zoznam bol usporiadany.\n");
    }
}

void r(ENTRY **head){
    if(*head == NULL){}
    else{
        ENTRY* tmp1 = *head, * tmp2 = *head;
        int c1,c2;
        scanf("%d %d", &c1, &c2);
        if(c1 < 0 || c2 < 0){}
        else{
            if(c1 == 1){    //toto tu ani nemusi byt ale preistotu
                tmp1 = *head;
            }
            if(c2 == 1){
                tmp2 = *head;
            }
            for(int i = 1; i < c1; i++){ //for cyklus k žiadaným pozíciám, int i = 1 lebo neindexujeme od 0 ale 1
                tmp1 = tmp1->next;
            }
            for(int i = 1; i < c2; i++){
                tmp2 = tmp2->next;
            }
            swapping_nods(&tmp1, &tmp2); //využijem funkciu a vymenim data a pointre v prvkoch
        }
    }
}

void p(ENTRY **head, FILE* fr){
    if(*head == NULL){}
    else{
        ENTRY* tmp1 = *head,* tmp2 = NULL;
        int c = 0, size = get_size(fr);
        char line[BUFFER];
        
        while(c <= 0){
            printf("Zadajte poziciu: ");
            scanf("%d", &c);
        }

        if(c == 1){ //ak je c prvy prvok, musim prvy posunut
            tmp2 = (ENTRY*)malloc(sizeof(ENTRY));
            tmp2->next = tmp1;
            *head = tmp2;
            new_node(&tmp2);
        }
        else{
            if(c > size + 1){ //ak bude velkost vacsia ako pocet zaznamov + 1 (to je ten novovzniknuty), tak pozicia bude posledna
                c = size + 1;
            }
            tmp1 = *head, tmp2 = *head; //for cyklami sa dostanem na prvky tmp1 a tmp2, alokujem tmp3, tmp1 je prvok na pozicii pred c
            for(int i= 1; i < c-1; i++){ //tmp2 je nasledujuci, tmp3 bude ukazovat na tmp2 a na tmp3 bude ukazovat tmp1
                  tmp1 = tmp1->next;
            }
            for(int i = 1; i < c; i++){
                tmp2 = tmp2->next;
            }
            ENTRY* tmp3 = (ENTRY*)malloc(sizeof(ENTRY));
            new_node(&tmp3);
            tmp1->next = tmp3;
            tmp3->next = tmp2;
        }
    }
}

int main(){
    FILE *fr = fopen("dataloger_V2.txt", "r"); //otvorim subor
    char x;
    int size = get_size(fr); //velkost zoznamu
    bool start = true;
    ENTRY *head = NULL, *new = NULL, *temp = NULL; 

    while(start)
    {
        scanf(" %c", &x);
        switch (x) {
            case 'n':{
                n(&fr, &head, &new, &temp, size);
            }    break;

            case 'v':{
                v(head, new);
            }    break;

            case 'z':{
                z(&head);
            }    break;

            case 'u':{
                u(&head);
            }  break;

            case 'p':{
                p(&head, fr);
            }   break;

            case 'h':{
                h(&head);
            }    break;

            case 'r':{
                r(&head);
            }    break;

            case 'k':{
                start = false; //toto ukonci while loop
                if(head != NULL){
                    delete(&head); //vymazem prvky zaznamu
                    head = NULL;
                }
                fclose(fr);
            }   break;

            default:{
                printf("Neznamy prikaz !\n");
            }    break;
        }
    }
    return 0;
}