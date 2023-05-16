#define CHAIN_TABLE_SIZE 100
#define LOAD_FACTOR_UP 0.75
#define LOAD_FACTOR_DOWN 0.2

typedef struct chaining_item{ //defining the type, which is the struct I called chaining_item t
    int id; //it contains integer id
    char *key; //the key that will be hashed to get the index
    struct chaining_item *following; //and pointer to the next node in the cluster
}CHAINING_ITEM;


extern CHAINING_ITEM** chaining_table; 
extern unsigned int chain_size;
extern unsigned int chain_count;


unsigned int chain_hash(char *key){ //hashing function 
    unsigned int sum = 0; //counting the sum which I will divide with the size of the table to get the index onto which I will place the inserted item
    for(int i = 0; i < strlen(key); i++){ 
        sum = 31 * sum + key[i]; //I use 31 * sum because it is prime number and this formula will help me reduce the amount of collisions in my program (I add the ASCII value of the character each time)
    }
    return sum % chain_size; //getting the index after finishing counting the sum 
    
}


void print_chaining_table(){
    for(int i = 0; i < chain_size; i++){ //for loop which will iterate until the size of the table is reached
        if(chaining_table[i] == NULL){ //if the place is empty I print --- to visualise empty space
            printf("%d -> ---\n", i);
        } else{
            CHAINING_ITEM* curr = chaining_table[i]; //if it is not null I create  pointer to point to the first node in the bucket
            printf("%d -> %s", i,curr->key); //I print the index and the key of the item
            curr = curr->following; //after this I set the current node to the next item in the cluster
            while(curr != NULL){ //and as long it is not equal to NULL there is new item that I will visualise
                printf("->%s", curr->key);
                curr = curr->following; //this will cause that I go through the whole linked list until it is not equal to NULL
            }
            printf("\n");
        }
}
}

void chain_insert_item(char* key, int id) {
    if (chain_count >= (int) (chain_size * LOAD_FACTOR_UP)) { //if the amount of items is bigger than the load factor I resize the table
        chain_size *= 2; //I multiply it by 2
        // creating a rechain_sized chaining_table, because we overcame our load factor
        CHAINING_ITEM **resized_chaining_table = (CHAINING_ITEM **)calloc(chain_size, sizeof(CHAINING_ITEM*)); //allocate new table to with the new size
        // copying the data from chaining_table into our rechain_sized chaining_table
        for(int i = 0; i < (chain_size / 2); i++){ // with the for loop I reinsert all of the key in the table so it will be faster
            CHAINING_ITEM* curr = chaining_table[i]; //I set the pointer to the item on the given index (given from for loop)
            while (curr != NULL) { //here I go through the linked list and reinsert all of the items until it is equal to NULL -> no other following nodes
                unsigned int index = chain_hash(curr->key); //getting the index for the node
                CHAINING_ITEM* curr_next = curr->following; //pointer to the next node -> that follows our node
                curr->following = resized_chaining_table[index]; //adding the current chaining_item to the front of the linked list
                resized_chaining_table[index] = curr; //updating the head of the linked list in the new chaining_table
                curr = curr_next; //moving the next chaining_item into another iteration of the loop from original chaining_table
            }
        }
        free(chaining_table); //free the original table
        chaining_table = resized_chaining_table; //point the pointer that used to point at original table to point at new table
    }

    CHAINING_ITEM* new_chaining_item = (CHAINING_ITEM *)malloc(sizeof(CHAINING_ITEM)); //memory for the new item that will be inserted into the table
    new_chaining_item->following = NULL; //we set the following node as NULL
    new_chaining_item->id = id; 
    new_chaining_item->key = (char *)malloc(strlen(key) + 1); //allocate the memory for the key
    strcpy(new_chaining_item->key, key); //copy the key using method from string library
    unsigned int index = chain_hash(key);

    if (chaining_table[index] == NULL) { //if place is empty put it here
        chaining_table[index] = new_chaining_item;
    } else {
        CHAINING_ITEM* curr = chaining_table[index]; //if place is not empty, create pointer to point at the beginning of the linked list
        while (curr != NULL) { //iterate until empty place is found
            if (strcmp(curr->key, key) == 0) { //if the keys are duplicated free the item and return
                // Duplicate key found, free the new chaining_item and return
                free(new_chaining_item->key);
                free(new_chaining_item);
                return;
            }
            curr = curr->following; //go to the next item
        }
        // No duplicate found, add the new chaining_item to the chain
        curr = chaining_table[index]; //again pointing at the beggining
        while (curr->following != NULL) { //until empty place is found, go through the linked list
            curr = curr->following;
        }
        curr->following = new_chaining_item;
    }
    chain_count++; //if the item is succesfuly added we have to enlargen the amount of items inserted
}

void chain_search_item(char *name){
    int index = chain_hash(name); //getting the index with the hash function
    CHAINING_ITEM *curr = chaining_table[index];
    if(curr == NULL) //empty spot in the table, there are no items to go through
        printf("Error! %s is not located in the chaining_table!\n", name);
    else{
        while(curr != NULL){ //there is a linked list
            if(strcmp(curr->key, name) == 0){ //iterating until the key and curr->key aren't equal
                printf("%s is located on the index: %d. Their ID is: %d\n", curr->key, index, curr->id);
                return;
        }
            curr = curr->following;
        }
         printf("Error! %s is not located in the chaining_table!\n", name); //the key was not located in the linked list
    }
}


void chain_delete_item(char *name){
    unsigned int index = chain_hash(name); //getting index 
    if(chaining_table[index] == NULL) //empty spot, we don't have to delete anything (item is not located in the table)
        return;

    CHAINING_ITEM* curr = chaining_table[index]; //two pointers - one pointing on the current node 
    CHAINING_ITEM* prev = NULL; //second one will point on the previous so we can delete item by skipping it in the linked list


    while(strcmp(curr->key, name) != 0){ //looking for the equal key in the linked list
        prev = curr; //previous will save the item by pointing at it
        curr = curr->following; //current node
    }
    if(prev == NULL) //if previous is NULL our item is first in the linked list and we just skip it and set the next node as the first one
        chaining_table[index] = curr->following;
    else
        prev->following = curr->following; //in another case we just skip to the next item like this prev->curr->another = prev->another

    free(curr->key);
    free(curr); //deallocate memory for the key and node itself

    chain_count--; //after successful deletion we must decrement the amount of inserted nodes

    if(chain_count < (int) chain_size * LOAD_FACTOR_DOWN){ //if the amount of nodes inserted is lower than the load factor we resize the table
        chain_size /= 2; //devide the size by two
        //creating a resized_chaining_table, because we overcame our load factor
        CHAINING_ITEM** resized_chaining_table = (CHAINING_ITEM**)calloc(chain_size, sizeof(CHAINING_ITEM*));
        //copying the data from chaining_table into our rechain_sized chaining_table
        for(int i = 0; i < (chain_size * 2); i++){
            CHAINING_ITEM* curr = chaining_table[i]; //point current node at the index in the table
            while(curr != NULL){
                unsigned int index = chain_hash(curr->key);
                CHAINING_ITEM* curr_next = curr->following; //save the pointer to the next chaining_item in the original linked list
                curr->following = resized_chaining_table[index]; //adding the current chaining_item to the front of the linked list
                resized_chaining_table[index] = curr; //updating the head of the linked list in the new chaining_table
                curr = curr_next; //moving the next chaining_item into another iteration of the loop from original chaining_table
            }
        }
        free(chaining_table); //freeing the old original chaining_table 
        chaining_table = resized_chaining_table; //setting pointer at the beggining of the new rechain_sized chaining_table 
    }
}