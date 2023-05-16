//defining the linear_size of the linear_hash linear_table and load factors (upper and lower LF)
#define LINEAR_TABLE_SIZE 100
#define LOAD_FACTOR_UP 0.75
#define LOAD_FACTOR_DOWN 0.2

//define a structure to store key-value pairs
typedef struct linear_item{
    bool deleted; //flag to know whether the place if empty or not
    char* key; //key for linear_hashing
    int ID_num; //identification number 
}LINEAR_ITEM;

//declaring global variables -> linear_hash linear_table, amount of elements and linear_size which changes throughout the run
extern LINEAR_ITEM* linear_table;
extern unsigned int linear_count;
extern unsigned int linear_size;

//linear_hash function to encrypt the key, I get index from string to put the item into has linear_table
unsigned int linear_hash(char* key){
    unsigned int linear_hashing = 0;
    for(int i = 0; i < strlen(key); i++){
        linear_hashing = linear_hashing * 31 + (int)key[i]; //using prime numbers the get the most unique index possible
    }
    return linear_hashing % linear_size; //modulo linear_size to get index which is within the bounds of the linear_table
}

void linear_insert_item(char* key, int id);

//function used to relinear_size the linear_table and rehash the elements after deletion
void rehash(int decide){
    unsigned int old_linear_size = linear_size; // saving the original linear_size because we will change it and we have to know the linear_size of previous linear_table
    LINEAR_ITEM* old_linear_table = linear_table; //set the pointer to the original linear_table 
    if(decide == 0) //this is to decide whether we will increase or decrease the linear_size of our linear_table
        linear_size *= 2; 
    else if(decide == 1)
        linear_size /= 2;
    linear_count = 0; //setting linear_count to zero because we are inserting all of the items again
    linear_table = (LINEAR_ITEM*)calloc(linear_size, sizeof(LINEAR_ITEM)); //making an bigger/smaller linear_table based on new linear_size and setting every slot to NULL
    for(int i = 0; i < old_linear_size; i++){
        if(old_linear_table[i].key != NULL && old_linear_table[i].deleted != true){ //inserting all of the linear_items from previous linear_table into our new linear_table
            linear_insert_item(old_linear_table[i].key, old_linear_table[i].ID_num);
        }
    }
    free(old_linear_table); //freeing the old linear_table because we already saved the items from it and inserted them into relinear_sized linear_table
}


//function to insert an item into the linear_hash linear_table
void linear_insert_item(char* key, int id){
    //checking the load factor, if it's too high, I am resizing the linear_table
    if(linear_count >= linear_size * LOAD_FACTOR_UP){
        rehash(0);
    }
    //getting the index of the key by using the linear_hash function
    unsigned int index = linear_hash(key);
    LINEAR_ITEM* current = &linear_table[index]; //pointer pointing to the index in linear_table I am looking for

    while(current->key != NULL || current->deleted == true){
        if(strcmp(key, current->key) == 0){
            printf("You are inserting duplicate key !");
            return;
        }
        index = (index + 1) % linear_size; //linear probing - changing the index
        current = &linear_table[index]; //setting the pointer to the new index
    }

    //we found the empty slot so we will allocate memory and insert the item into the linear_table
    current->key = (char*)malloc(strlen(key) + 1);
    strcpy(current->key, key);
    current->ID_num = id;
    current->deleted = false;
    linear_count++;
}


void linear_search_item(char* key){
    int linear_counter = 0; //counter to know that we overcame the size of the table and we don't get stuck in infinite loop
    unsigned int index = linear_hash(key);//hashing the key value
    LINEAR_ITEM* current = &linear_table[index]; //pointing the node at the index in the linear table
    while(linear_counter < linear_size && current->key != NULL){ //iterating through the table
        if(strcmp(key, current->key) == 0 && current->deleted == false){ //if the key is equal to the key of the current node and the item is not flag as deleted, we found it and can print it 
            printf("Key %s has been found on index: %d.\n", current->key, index); //searching was successful
            return;
        }
        index = (index + 1) % linear_size; //if not we use linear probing to go through the table
        current = &linear_table[index]; //poiting the pointer to the new index in the table
        linear_counter++; //incrementing the counter
    }
    printf("key not found !\n");
}

// Function to print the contents of the linear_hash linear_table
void print_linear_table(){
    for(int i = 0; i < linear_size; i++){ //we go through the entire table
        LINEAR_ITEM* curr = &linear_table[i]; //set the pointer to point at the current index
        if(curr->key == NULL || curr->deleted == true){ //if it is deleted or NULL we print it as empty spot
            printf("%d -> ---\n", i);
        } else{
            printf("%d -> %s\n", i, curr->key); //in other case we print its index and key value
        }
}
}

void linear_delete_item(char* key){
    int linear_counter = 0; //counter so we don't overcome the table
    unsigned int index = linear_hash(key);  //getting the index of the key to delete
    LINEAR_ITEM* del_linear_item = &linear_table[index]; //pointing the pointer at the index of the table

    while(linear_counter < linear_size && del_linear_item->key != NULL){ //check the amount of iterations and whether the place is not empty
        if(strcmp(key, del_linear_item->key) == 0 && del_linear_item->deleted == false){ //if we found the matching key and it is not already deleted we delete it
            del_linear_item->deleted = true; //set it as deleted
            del_linear_item->key = NULL; // I set it to NULL but I dont have to because I also check if the item is deleted, it is just in case
            del_linear_item->ID_num = -1; //set ID to be -1
            linear_count--;  //decrement the amount of items that are located in the table
        }
        linear_counter++; //increment counter
        index = (index + 1) % linear_size; //linear probing
        del_linear_item = &linear_table[index]; //update the pointer
    }
    if(linear_count <= linear_size * LOAD_FACTOR_DOWN){ //amount of items is lower than load factor, we have to make the table smaller
        rehash(1);
    }
}