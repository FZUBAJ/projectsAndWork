#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "AVL.c"
#include "SPLAY.c"
#include "OPEN.c"
#include "CHAINING.c"

CHAINING_ITEM** chaining_table; 
unsigned int chain_size = CHAIN_TABLE_SIZE;
unsigned int chain_count = 0;

LINEAR_ITEM* linear_table;
unsigned int linear_count = 0;
unsigned int linear_size = LINEAR_TABLE_SIZE;

int main(){
    clock_t start, end;

    FILE* file = fopen("numbers.txt", "r");
    


    AVL_NODE* root_node_avl = NULL, *search_node_avl = NULL;
    SPLAY_NODE* root_node_splay = NULL;

    linear_table = (LINEAR_ITEM*)calloc(linear_size, sizeof(LINEAR_ITEM));
    chaining_table = (CHAINING_ITEM**)calloc(CHAIN_TABLE_SIZE, sizeof(CHAINING_ITEM*));


    if(file == NULL){
        printf("FILE NOT FOUND! \n");
        return 0;
    }

    printf("---- TESTING STARTS ----\n\n\n");
    printf("---- CHOOSE THE TYPE OF THE DATA STRUCTURE ----\n");
    printf("(1) LINEAR PROBING\n");
    printf("(2) SEPARATE CHAINING\n");
    printf("(3) AVL TREE\n");
    printf("(4) SPLAY TREE\n");

    int choice;
    scanf(" %d", &choice);

    switch(choice){
        case 1:
            printf("YOU CHOSE: LINEAR PROBING\n\n\n");
            printf("--- CHOOSE WHICH FUNCTION YOU WANT TO TEST --- \n");
            printf("(1) INSERT\n(2) SEARCH\n(3) DELETE\n");
            int choice_linear;
            scanf(" %d", &choice_linear);
            
            int amount_linear;
            switch(choice_linear){
                case 1:
                    printf("YOU CHOSE: INSERT\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO INSERT ? (MAXIMUM: 1 000 000)\n");
                    scanf("%d", &amount_linear);
                    if(amount_linear > 1000000){
                        printf("TOO MANY NODES! RUN THE CODE AGAIN.\n");
                        break;
                    }
                    
                    start = clock();
                    for(int i = 0; i < amount_linear; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        linear_insert_item(key, i);
                    }
                    end = clock();
                    printf("TIME OF INSERTION: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                
                case 2:
                    printf("YOU CHOSE: SEARCH\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO SEARCH ? (MAXIMUM: 1 000 000)\n");
                    scanf("%d", &amount_linear);
                    if(amount_linear > 1000000){
                        printf("TOO MANY NODES !\n");
                        break;
                    }
                    //first we have to insert
                    for(int i = 0; i < amount_linear; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        linear_insert_item(key, i);
                    }
                   start = clock();
                   for(int i = 0; i < amount_linear; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        linear_search_item(key);
                   }
                   end = clock();
                    printf("TIME OF SEARCH: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 3:
                    printf("YOU CHOSE: DELETE\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO DELETE ? (MAXIMUM: 1 000 000)\n");
                    scanf("%d", &amount_linear);
                    if(amount_linear > 1000000){
                        printf("TOO MANY NODES !\n");
                        break;
                    }
                    
                    //insert first
                    for(int i = 0; i < amount_linear; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        linear_insert_item(key, i);
                    }
                   start = clock();
                   for(int i = 0; i < amount_linear; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        chain_delete_item(key);
                   }
                   end = clock();
                    printf("TIME OF DELETION: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                default:
                    printf("INVALID CHOICE ! TRY AGAIN\n");
                    break;
            }
            break;
        
        case 2:
            printf("YOU CHOSE: SEPARATE CHAINING\n\n\n");
            printf("--- CHOOSE FUNCTION YOU WANT TO TEST --- \n");
            printf("(1) INSERT\n(2) SEARCH\n(3) DELETE\n");

            int choice_chain;
            scanf("%d", &choice_chain);
            int amount_chain;

            switch(choice_chain){
                case 1:
                    printf("YOU CHOSE: INSERT\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO INSERT ? (MAXIMUM: 1 000 000)\n");
                    scanf("%d", &amount_chain);
                    if(amount_chain > 1000000){
                        printf("TOO MANY NODES !\n");
                        break;
                    }
                    
                    start = clock();
                    for(int i = 0; i < amount_chain; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        chain_insert_item(key, i);
                    }
                    end = clock();
                    printf("TIME OF INSERTION: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 2:
                    printf("YOU CHOSE: SEARCH\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO SEARCH ? (MAXIMUM: 1 000 000)\n");
                    scanf("%d", &amount_chain);
                    if(amount_chain > 1000000){
                        printf("TOO MANY NODES !\n");
                        break;
                    }
                    
                    for(int i = 0; i < amount_chain; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        chain_insert_item(key, i);
                    }
                    
                    start = clock();
                    for(int i = 0; i < amount_chain; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        chain_search_item(key);
                    }
                    end = clock();
                    printf("TIME OF SEARCH: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 3:
                    printf("YOU CHOSE: DELETE\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO DELETE ? (MAXIMUM: 1 000 000)\n");
                    scanf("%d", &amount_chain);
                    if(amount_chain > 1000000){
                        printf("TOO MANY NODES !\n");
                        break;
                    }
                    //insertion first
                    for(int i = 0; i < amount_chain; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        chain_insert_item(key, i);
                    }
                    
                    start = clock();
                    for(int i = 0; i < amount_chain; i++){
                        char* key = (char*)malloc(8 * sizeof(char));
                        sprintf(key, "%d", i);
                        chain_delete_item(key);
                    }
                    end = clock();
                    printf("TIME OF DELETION: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                
                default:
                    printf("INVALID CHOICE !\n");
                    break;
            }
            break;
        
        case 3:
            printf("YOU CHOSE: AVL TREE\n\n\n");
            printf("--- CHOOSE FUNCTION YOU WANT TO TEST --- \n");
            printf("(1) INSERT\n(2) SEARCH\n(3) DELETE\n");
            
            int choice_avl;
            scanf("%d", &choice_avl);
            
            int amount_avl = 0;
            switch(choice_avl){
                case 1:
                    printf("YOU CHOSE: INSERT\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO INSERT ? MAXIMAL AMOUNT = 1 000 000\n");
                    scanf("%d", &amount_avl);

                    if(amount_avl > 1000000){
                        printf("TOO MANY NODES !\n");
                    }

                    start = clock();
                    for(int i = 0; i < amount_avl; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_avl = AVL_insert_node(root_node_avl,number);
                    }
                    end = clock();
                    printf("TIME OF INSERTION: %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 2: 
                    printf("YOU CHOSE: SEARCH\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO SEARCH ? MAXIMAL AMOUNT = 1 000 000\n");
                    scanf("%d", &amount_avl);

                    if(amount_avl > 1000000){
                        printf("TOO MANY NODES !\n");
                    }

                    for(int i = 0; i < amount_avl; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_avl = AVL_insert_node(root_node_avl,number);
                    }
                    
                    rewind(file);
                    
                    start = clock();
                    for(int i = 0; i < amount_avl; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        search_node_avl = AVL_search_node(root_node_avl,number);
                        printf("SEARCHED NODE: %d\n", search_node_avl->AVL_key);
                    }
                    end = clock();
                    printf("TIME OF SEARCH: %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 3:
                    printf("YOU CHOSE: DELETE\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO DELETE ? MAXIMAL AMOUNT = 1 000 000\n");
                    scanf("%d", &amount_avl);

                    if(amount_avl > 1000000){
                        printf("TOO MANY NODES !\n");
                    }

                    
                    for(int i = 0; i < amount_avl; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_avl = AVL_insert_node(root_node_avl,number);
                    }
                    
                    rewind(file);
                    
                    start = clock();
                    for(int i = 0; i < amount_avl; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_avl = AVL_delete_node(root_node_avl,number);
                    }
                    end = clock();
                    printf("TIME OF DELETION: %f seconds\n", (double)(end-start)/CLOCKS_PER_SEC);
                    break;
                default:
                    printf("INVALID CHOICE !\n");
                    break;
            }
            

            break;
        
        case 4:
            printf("YOU CHOSE: SPLAY TREE\n\n\n");
            printf("--- CHOOSE FUNCTION YOU WANT TO TEST --- \n");
            printf("(1) INSERT\n(2) SEARCH\n(3) DELETE\n");

            int choice_splay;
            scanf("%d", &choice_splay);
            
            int amount_splay = 0;
            switch(choice_splay){
                case 1:
                    printf("YOU CHOSE: INSERT\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO INSERT ? MAXIMAL AMOUNT = 1 000 000\n");
                    scanf("%d", &amount_splay);

                    if(amount_splay > 1000000){
                        printf("TOO MANY NODES !\n");
                    }

                    start = clock();
                    for(int i = 0; i < amount_splay; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_splay = SPLAY_insert_node(root_node_splay,number);
                    }
                    end = clock();
                    printf("TIME OF INSERTION: %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 2: 
                    printf("YOU CHOSE: SEARCH\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO SEARCH ? MAXIMAL AMOUNT = 1 000 000\n");
                    scanf("%d", &amount_splay);

                    if(amount_splay > 1000000){
                        printf("TOO MANY NODES !\n");
                    }

                    
                    for(int i = 0; i < amount_splay; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_splay = SPLAY_insert_node(root_node_splay,number);
                    }
                    
                    rewind(file);
                    
                    start = clock();
                    for(int i = 0; i < amount_splay; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_splay = SPLAY_search_node(root_node_splay,number);
                        printf("SEARCHED NODE: %d\n", root_node_splay->SPLAY_key);
                    }
                    end = clock();
                    printf("TIME OF SEARCH: %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
                    break;
                case 3:
                    printf("YOU CHOSE: DELETE\n\n\n");
                    printf("HOW MANY NODES DO YOU WANT TO DELETE ? MAXIMAL AMOUNT = 1 000 000\n");
                    scanf("%d", &amount_splay);

                    if(amount_splay > 1000000){
                        printf("TOO MANY NODES !\n");
                    }

                    
                    for(int i = 0; i < amount_splay; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_splay = SPLAY_insert_node(root_node_splay,number);
                    }
                    
                    rewind(file);
                    
                    start = clock();
                    for(int i = 0; i < amount_splay; i++){
                        int number;
                        fscanf(file, "%d", &number);
                        root_node_splay = SPLAY_delete_node(root_node_splay,number);
                    }
                    end = clock();
                    printf("TIME OF DELETION: %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
                    break;
                default:
                    printf("INVALID CHOICE !\n");
                    break;
            }
            break;
        
        default:
            printf("INVALID CHOICE !\n");
            break;
    }





    free(linear_table);
    free(chaining_table);
    root_node_avl = NULL;
    root_node_splay = NULL;
    search_node_avl = NULL;
    linear_table = NULL;
    chaining_table = NULL;
    fclose(file);
    return 0;
}