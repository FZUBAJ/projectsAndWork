//this is the AVL_node struct - it contains AVL_key - which will help us to find it in tree, height to find out whether it is balanced, left and right child and id -> AVL_key I am storing inside the AVL_node
typedef struct AVL_node{
    int AVL_key; //the key AVL_key
    long AVL_id;
    int height;
    struct AVL_node *left, *right; //left and right child
} AVL_NODE;

//calculating height of AVL_node - height is the furthest distance between AVL_node and a leaf in tree
int height(AVL_NODE *AVL_node){
    if(AVL_node == NULL)
        return 0;
    else
        return AVL_node->height;
}

//simple method/funtion to calculate the maximum number
int max(int x, int y){
    return (x > y) ? x : y;
}

//getting the balance factor of the AVL_node (calculate the difference between left and right subtree to get a balance factor)
//if the factor is higher than -1 and smaller than 1, we dont have to rotate the tree
int get_balance(AVL_NODE *AVL_node){
    if(AVL_node == NULL)
        return 0;
    else {
        int balance_f = height(AVL_node->left) - height(AVL_node->right); //getting the balance factor
        return balance_f;
    }
}
//successor = the AVL_node with smallest key AVL_key -> iterating through the tree to find the AVL_node with the lowest AVL_key
AVL_NODE *successor(AVL_NODE *AVL_node){
    AVL_NODE *current = AVL_node->right; //checking the right subtree
    //iterating through the tree, looking for the smallest AVL_node, after we find it we use it in the delete function
    while(current->left != NULL){
        current = current->left;
    }
    return current;
}

//function to create a AVL_node with a type of NODE
//in the AVL_node there is right and left child linked and also there is the key AVL_key and height of the AVL_node
AVL_NODE *AVL_create_node(int AVL_key){
    AVL_NODE *AVL_node = (AVL_NODE *)malloc(sizeof(AVL_NODE));
    AVL_node->AVL_key = AVL_key; //key AVL_key
    AVL_node->height = 1; //setting height
    AVL_node->left = NULL; //linking to left subtree
    AVL_node->right = NULL;//linking to the right subtree
    return AVL_node;
}

//single rotations
//left rotation
AVL_NODE *rotate_L(AVL_NODE *n){
    AVL_NODE *m = n->right;
    AVL_NODE *tmp = m->left;
    m->left = n;
    n->right = tmp;
    //updating the height of the nodes
    n->height = max(height(n->left), height(n->right)) + 1; //updating the height after the rotation
    m->height = max(height(m->left), height(m->right)) + 1;
    return m;
}

//right rotation
AVL_NODE *rotate_R(AVL_NODE *n){
    AVL_NODE *m = n->left;
    AVL_NODE *tmp = m->right;
    m->right = n;
    n->left = tmp;
    //updating the height of the nodes
    n->height = max(height(n->left), height(n->right)) + 1; //updating the height after the rotation
    m->height = max(height(m->left), height(m->right)) + 1;
    return m;
}

//inserting a new AVL_node into the AVL binary tree
AVL_NODE *AVL_insert_node(AVL_NODE *AVL_node, int AVL_key){
    //with the help of recursive function we will find the right place which is empty and insert our AVL_node
    if(AVL_node == NULL){ //the tree is empty, the new AVL_node becomes a AVL_root of our tree
        return (AVL_create_node(AVL_key));
    }
    //recursive function, depending on the key AVL_key we will find in which subtree, the AVL_node should be placed
    if(AVL_key < AVL_node->AVL_key){
        AVL_node->left = AVL_insert_node(AVL_node->left, AVL_key);
    } else if (AVL_key > AVL_node->AVL_key){
        AVL_node->right = AVL_insert_node(AVL_node->right, AVL_key); //recursively going through the tree, looking for right place
    } else {
        return AVL_node; //if the key AVL_key of AVL_node is not smaller/bigger, they are equal and we are inserting duplicate
    }

    AVL_node->height = max(height(AVL_node->left),height(AVL_node->right)) + 1; //height update and getting balance factor
    int balance_num = get_balance(AVL_node); //getting the balance factor of the AVL_node

    if(balance_num > 1){ //if the balance factor is out of the interval of <-1,1>, we need to rebalance our tree and make rotations
        //left-right situation
        if(AVL_key > AVL_node->left->AVL_key){
            AVL_node->left = rotate_L(AVL_node->left);
            return rotate_R(AVL_node);
        }
        //left-left situation
        else if(AVL_key < AVL_node->left->AVL_key){
            return rotate_R(AVL_node);
        }
    }
    if(balance_num < -1){
        //right-right situation
        if(AVL_key > AVL_node->right->AVL_key){
            return rotate_L(AVL_node);
        }
        //right-left situation
        else if(AVL_key < AVL_node->right->AVL_key){
            AVL_node->right = rotate_R(AVL_node->right);
            return rotate_L(AVL_node);
        }
    }
    return AVL_node;
}

AVL_NODE *AVL_delete_node(AVL_NODE *AVL_root, int AVL_key){
    if(AVL_root == NULL) //checking if the AVL_node is empty, this is because we use recursion and it may occur that the key
        return AVL_root; //to be deleted might not be in the tree so we have to check each time

    if(AVL_key < AVL_root->AVL_key) //recursion to find the right key
        AVL_root->left = AVL_delete_node(AVL_root->left, AVL_key);
    else if(AVL_key > AVL_root->AVL_key)
        AVL_root->right = AVL_delete_node(AVL_root->right, AVL_key);

    else {                                                       // if the AVL_root is not NULL and the key is nor smaller nor bigger, they must be equal
        if ((AVL_root->left == NULL) || (AVL_root->right == NULL)) {      //first case, the tree has at most 1 children (easier deletion)
            AVL_NODE *tmp = NULL;

            if (AVL_root->left != NULL) //check whether the AVL_node has left child
                tmp = AVL_root->left;
            else if (AVL_root->right != NULL) //check whether the AVL_node has right child
                tmp = AVL_root->right;

            if (tmp == NULL) { //AVL_node has 0 children
                tmp = AVL_root; //we set the tmp to the AVL_root, set the AVL_root to NULL and free the tmp
                AVL_root = NULL; //we dont have to do anything, just rebalance because this will change ballance factor of other nodes
            } else //in this case AVL_node to delete has one children (left or right, we set the tmp equal to it before)
                *AVL_root = *tmp;  //we just skip the deleted AVL_node and the deleted AVL_node's parent will become the parent of deleted AVL_node's child AVL_node
            //it goes like this parent -> node_delete -> child ===> parent -> child
            free(tmp);

        } else { //in this case there are two children nodes
            AVL_NODE *tmp = successor(AVL_root); //for this code we use successor, the smallest AVL_key
            AVL_root->AVL_key = tmp->AVL_key; //we put the successor into the position, where the deleted key used to be
            AVL_root->right = AVL_delete_node(AVL_root->right, tmp->AVL_key); //after this, we have to delete the successor from its original position
        }
    }
        if(AVL_root == NULL) //checking in case
            return AVL_root;

        //getting the balance factor and updating the height
        AVL_root->height = max(height(AVL_root->left), height(AVL_root->right)) + 1;
        int balance_num = get_balance(AVL_root);

        //if the balance factor is out of range <-1,1>, then we do rotations to rebalance the AVL tree
        if(balance_num > 1){
            //left-left situation
            if(get_balance(AVL_root->left) >= 0)
                return rotate_R(AVL_root);
            //left-right situation
            if(get_balance(AVL_root->left) < 0){
                AVL_root->left = rotate_L(AVL_root->left);
                return rotate_R(AVL_root);
            }
        }
        if(balance_num < -1){
            //right-right situation
            if(get_balance(AVL_root->right) <= 0)
                return rotate_L(AVL_root);
            //right-left situation
            if(get_balance(AVL_root->right) > 0){
                AVL_root->right = rotate_R(AVL_root->right);
                return rotate_L(AVL_root);
            }
        }
    return AVL_root;
}

//searching for a AVL_node with a given AVL_key
AVL_NODE *AVL_search_node(AVL_NODE *AVL_node, int AVL_key){
    while(AVL_node != NULL){ // dont have to check whether AVL_node is null because it is in while loop
        if(AVL_key < AVL_node->AVL_key) //iterating through the subtrees and moving based on the key AVL_key
            AVL_node = AVL_node->left;  //if key AVL_key is smaller than in the current AVL_node we go left, if not we go right
        else if(AVL_key > AVL_node->AVL_key)
            AVL_node = AVL_node->right;
        else if(AVL_key == AVL_node->AVL_key) //if the key AVL_keys are equal, we return the AVL_node we have been searching for
            return AVL_node;
    }
    printf("--- ERROR: key AVL_node not found ---\n");
    return NULL;
}




