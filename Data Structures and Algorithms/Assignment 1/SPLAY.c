typedef struct SPLAY_node{ //defining the struct for the one node of the tree with id as the stored value and key which is used for the rotations and splaying
    int SPLAY_key;
    int splay_id;
    struct SPLAY_node *left, *right; //links to left and right child of the node
}SPLAY_NODE;

SPLAY_NODE *SPLAY_create_node(int value){ //function to allocate the memory for the node and to insert values inside the node
    SPLAY_NODE *node = (SPLAY_NODE*)malloc(sizeof(SPLAY_NODE));
    node->SPLAY_key = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//zig is the left rotation (int the splay tree its called zig)
SPLAY_NODE *zig(SPLAY_NODE *n){ //left rotation function used for splaying the tree so it can be used in other functions
    SPLAY_NODE *m = n->right;
    SPLAY_NODE *tmp = m->left;
    m->left = n;
    n->right = tmp;
    return m;
}

//zag is the right rotation (in the splay tree its called zag)
SPLAY_NODE *zag(SPLAY_NODE *n){ //right rotation function, these are similar as in AVL tree implementation
    SPLAY_NODE *m = n->left;
    SPLAY_NODE *tmp = m->right;
    m->right = n;
    n->left = tmp;
    return m;
}

//splaying function is the most important in the splay tree
//it performs all of the rotations based on what situation happens
//in remaining functions, splay function if called to rotate the nodes

SPLAY_NODE *splaying(SPLAY_NODE *SPLAY_root, int SPLAY_key){
    if(SPLAY_root == NULL || SPLAY_root->SPLAY_key == SPLAY_key) //root is NULL which means tree is empty
        return SPLAY_root; //or root already contains the key and we return it back

    SPLAY_NODE tmp, *left_maximal = &tmp, *right_minimal = &tmp; //temporary pointer is created, and also maximum value in the left subtree and minimal value in the right subtree
    tmp.left = NULL; //children of tmp are pointing at NULL
    tmp.right = NULL;

    while(1){ //iterating throgh the tree until it is exhausted or until we find the key
        if(SPLAY_key < SPLAY_root->SPLAY_key){//key is smaller than the roots key
            if(SPLAY_root->left == NULL) //left child is null we can break the loop 
                break;
            
            if(SPLAY_key < SPLAY_root->left->SPLAY_key){  //key is smaller than left child's key
                SPLAY_root = zag(SPLAY_root); //we perform zag (right) rotation
                if(SPLAY_root->left == NULL) //if the left child is NULL we break the loop
                    break;
            }
            right_minimal->left = SPLAY_root; //the new root is set as right minimal node's left child
            right_minimal = SPLAY_root; //we set right minimal as the splay root
            SPLAY_root = SPLAY_root->left; //and we set the splay root to equal to its right child
        }
        else if(SPLAY_key > SPLAY_root->SPLAY_key){//key is bigger than the roots key
            if (SPLAY_root->right == NULL) //right child has to be NULL
                break;
    
            if(SPLAY_key > SPLAY_root->right->SPLAY_key){
                SPLAY_root = zig(SPLAY_root); //key is larger than the right child's key so we perform zig rotation
                if(SPLAY_root->right == NULL) //right child is NULL so we break the loop
                    break;
                
            }
            left_maximal->right = SPLAY_root; //the new root is set as left maximal node's right child
            left_maximal = SPLAY_root; //we set left maximal as the splay root
            SPLAY_root = SPLAY_root->right; //and we set the splay root to equal to its right child
        }
        else{
            break; //the tree gets exhausted or the root is equal to the key and we splayed the tree
        }
    }

    left_maximal->right = SPLAY_root->left; //rearranging the tree, left child of root's node is the new maximal value in left subtree
    right_minimal->left = SPLAY_root->right; //rearranging the tree, right child of root's node is the new minimal value in right subtree
    SPLAY_root->left = tmp.right; // we set the children as the temporary right and left node
    SPLAY_root->right = tmp.left;

    return SPLAY_root; //new root is returned
}



SPLAY_NODE *SPLAY_insert_node(SPLAY_NODE *node, int value){
    if(node == NULL){ //empty tree, inserted node will become the root of the tree
        node = SPLAY_create_node(value);
        return node; //returning the new root
    }
    node = splaying(node, value); // we splay the tree 
    if(value == node->SPLAY_key) //key is already located in our tree 
        return node; //return the new root which is the key we were inserting but already is in the tree
    else if(value < node->SPLAY_key){ //value is smaller than current key
        SPLAY_NODE* new_root = SPLAY_create_node(value); //we create new node
        new_root->left = node->left; //we set the left child of current root to be the left child of the new root
        new_root->right = node; //right child will be the current root because it is larger
        node->left = NULL; //current root will have no left child, because it has been assigned to be the left child of the new root
        node = new_root; //new root 
        return node; //we return the new root
    }
    else if(value > node->SPLAY_key){ //key is larger than the key stored in the current root
        SPLAY_NODE* new_root = SPLAY_create_node(value); //create new node with given value
        new_root->right = node->right; //we set roots right child to be the right child of the new node
        new_root->left = node; //left child of new root is the current root because its key is smaller
        node->right = NULL; //right child of current root which is now left child of new root is NULL
        node = new_root; //set the new root
        return node; //return new root
    }
    return node; //returning root node
}

SPLAY_NODE* SPLAY_delete_node(SPLAY_NODE *root, int value){
    SPLAY_NODE* tmp = NULL; //temporary node that we will use to delete
    if(root == NULL) //empty tree, we just return NULL
        return NULL;

    root = splaying(root, value); //splaying the tree to get the node to delete into the root node

    if(value != root->SPLAY_key){ //key is not equal to the root's key so the node is not located in the tree
        printf("key not located in the tree"); //send warning
        return root; //return the new root but don't delete anything
    }
    if(root->left == NULL){  //root is the node to delete and its left child is NULL
        tmp = root; //we set the temporary as the root and we just set the root as the right child
        root = root->right; //we dont have to do anything with left subtree because it is NULL
    }else{
        tmp = root; //we set tmp as the root
        root = splaying(root->left, value); //we splay the value to delete into the left subtree
        root->right = tmp->right; //we save the right subtree into the new root as the right child
    }
    free(tmp); //deallocate the memory for temporary node
    return root; //we return the new root node
}


SPLAY_NODE *SPLAY_search_node(SPLAY_NODE *root_node, int value){
    if(root_node == NULL) //empty tree return NULL
        return NULL;
    else if(root_node->SPLAY_key == value) //the root contains the value we are looking for
        return root_node; //just return it
    root_node = splaying(root_node, value); //splay the tree to get the searched node into root
    if(root_node->SPLAY_key != value){ //if it isn't located in the tree
        printf("key not found!"); //we send warning and return NULL 
        return NULL;
    }
    return root_node; //if it is found we return new root
}


