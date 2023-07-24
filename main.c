#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
binary tree node structure
*/
typedef struct node
{
    char elem;
    struct node *left;
    struct node *right;
    struct node *next;

    int height;
    int bf;
} t_node;


/*
queue structure
*/
typedef struct queue
{
    t_node *rear;
    t_node *front;
} t_queue;


/*
Prototypes
*/
t_node *insertRoot(char element);
t_node *insertLeft(t_node *rootOfTheTree, char element);
t_node *insertRight(t_node *rootOfTheTree, char element);
t_node *UnbalancedTree(t_node *T);
void free_tree(t_node *node);

int getHeight(t_node * tree);
void setHeight(t_node *_node, int _height);

int getBalanceFactor(t_node *N);
void setBalanceFactor(t_node *_node, int _bf);
void updateBalanceFactor(t_node *node);

t_node* rightRotation(t_node* tree);
t_node* leftRotation(t_node* tree);

void balanceTree(t_node *root);

t_queue *initQueue();
int isEmpty(t_queue *Q);
void enqueue(t_queue *ptQ, t_node *n_elem);
t_node *dequeue(t_queue *ptQ);
void levelOrder(t_node *r);




/*
function to insert root
    parameters: element: character
*/
t_node *insertRoot(char element)
{
    t_node *root_node;

    //memory allocation for a new node
    root_node=(t_node*)malloc(sizeof(t_node));

    if(root_node==NULL)
    {
        printf("Memory allocation error\n");
    }
    else
    {
        root_node->elem = element;


        //set children to null
        root_node->left = NULL;
        root_node->right = NULL;
        root_node->next = NULL;

        //set height to 1
        root_node->height = 1;
        root_node->bf = 0;

    }
    return root_node;

}


/*
function to insert left child of the root
    parameters: root : node, element: character
*/
t_node *insertLeft(t_node *rootOfTheTree, char element)
{
    t_node *new_node;

    new_node=(t_node*)malloc(sizeof(t_node));

    if(new_node==NULL)
    {
        printf("Memory allocation error\n");
    }
    else
    {
        //check if the new value is less than the root
        if(element < rootOfTheTree->elem)
        {
            new_node->elem = element;

            //asign the left child the new node
            rootOfTheTree->left = new_node;

            new_node->left = NULL;
            new_node->right = NULL;
            new_node->next = NULL;

            new_node->height = 1;
            new_node->bf = 0;
        }

    }
    return new_node;
}


/*
function to insert right child of the root
    parameters: root : node, element: character
*/
t_node *insertRight(t_node *rootOfTheTree, char element)
{
    t_node *new_node;

    new_node=(t_node*)malloc(sizeof(t_node));

    if(new_node==NULL)
    {
        printf("Memory allocation error\n");
    }
    else
    {
        //check if the new value is greater than the root
        if(element > rootOfTheTree->elem)
        {

            new_node->elem = element;

            //asign the right child the new node
            rootOfTheTree->right = new_node;

            new_node->left = NULL;
            new_node->right = NULL;
            new_node->next = NULL;

            new_node->height = 1;
            new_node->bf = 0;
        }

    }
    return new_node;
}


/*
function to create an unbalanced binary tree
    parameter: tree: node
*/
t_node *UnbalancedTree(t_node *T)
{
    //insert all nodes
    T = insertRoot('D');
    T->left = insertLeft(T, 'C');
    T->left->left = insertLeft(T->left, 'B');
    T->left->left->left = insertLeft(T->left->left, 'A');

    return T;

}


/*
function to free a binary tree
    parameter: tree: node
*/
void free_tree(t_node *node)
{
    if(node==NULL)
    {

    }
    else
    {
        free_tree(node->left);
        free_tree(node->right);
        free(node);
    }
}


/*
function to initialize a dynamic queue
*/
t_queue *initQueue()
{
    t_queue *ptQ;
    ptQ = (t_queue*)malloc(sizeof(t_queue));
    ptQ->rear = NULL;
    ptQ->front = NULL;

    return ptQ;
}


/*
function to check if the queue is empty
    parameter: queue: queue
*/
int isEmpty(t_queue *Q)
{
    if (Q->rear == NULL && Q->front == NULL)
        return 1;
    else
        return 0;
}


/*
function to enqueue
    parameters: queue: queue, new element: node
*/
void enqueue(t_queue *ptQ, t_node *n_elem)
{
    if (isEmpty(ptQ) == 1)
    {
        //insert new element in first place
        ptQ->front = n_elem;
        ptQ->rear = n_elem;
    }
    else
    {
        //insert it after
        n_elem->next = ptQ->front;
        ptQ->front = n_elem;
    }
}


/*
function to dequeue
    parameter: queue: queue
*/
t_node *dequeue(t_queue *ptQ)
{
    t_node *current = NULL;
    t_node *previous = NULL;

    //check if the queue is empty
    if (isEmpty(ptQ) == 1)
    {
        printf("(Empty queue)\n");

    }

    else
    {
        //traversing the linked list
        current = ptQ->rear;
        if (ptQ->rear != ptQ->front)
        {
            current = ptQ->front;
            previous = current;

            //traverse until the before to last node
            while(current->next!=NULL)
            {
                previous = current;
                current=current->next;
            }
            previous->next = NULL;
            ptQ->rear = previous;
        }

        else
        {
            ptQ->rear = NULL;
            ptQ->front = NULL;
        }

    }

    return current;

}


/*
level order function
    parameter: root: node
*/
void levelOrder(t_node *r)
{
    t_queue *node_queue;

    //initialize the queue
    node_queue = initQueue();

    //traverse all the tree
    while (r != NULL)
    {
        //visit the root
        printf("%c\n", r->elem);
        printf("bf %d\n", r->bf);

        //enqueue left child
        if (r->left != NULL)
            enqueue(node_queue, r->left);

        //enqueue right child
        if (r->right != NULL)
            enqueue(node_queue,r->right);

        //dequeue visited node
        r = dequeue(node_queue);
    }


}


/*
recursive height getter
    parameter: tree: node
*/
int getHeight(t_node * tree)
{
    int righ_sub_t = 0, left_sub_t = 0;

    if (tree == NULL)
    {
        //base case
        return 0;
    }
    else
    {
        //recursion
        left_sub_t = getHeight(tree->left);
        righ_sub_t = getHeight(tree->right);

        //compare and return correct height
        if (left_sub_t < righ_sub_t)
        {
            return righ_sub_t+1;
        }

        else
        {
            return left_sub_t+1;
        }
    }

}


/*
height setter
    parameters: tree: node, height: integer
*/
void setHeight(t_node *_node, int _height)
{
    _node->height = _height;
}


/*
balance factor getter
    parameter: tree: node
*/
int getBalanceFactor(t_node *N)
{
    if (N==NULL)
        return 0;

    else if(N->left==NULL && N->right==NULL)
        return 0;

    //if left child doesn't exist
    else if(N->left==NULL)
        return (0-(N->right->height));

    //if right child doesn't exist
    else if(N->right==NULL)
        return ((N->left->height)-0);

    //formula: left subtree height - right subtree height
    else
        return((N->left->height) - (N->right->height));
}


/*
balance factor setter
    parameters: tree: node, balance factor: integer
*/
void setBalanceFactor(t_node *_node, int _bf)
{
    _node->bf = _bf;
}


/*
recursive function to update balance factor
    parameter: tree: node
*/
void updateBalanceFactor(t_node *node)
{

    if(node==NULL)
    {
        //base case
    }
    else
    {
        //recursion
        updateBalanceFactor(node->left);
        updateBalanceFactor(node->right);
        //call other setters
        setHeight(node, getHeight(node));
        setBalanceFactor(node, getBalanceFactor(node));
    }

}


/*
right rotation function
    parameter: tree: node
*/
t_node* rightRotation(t_node *tree)
{
    t_node *balance_node;
    balance_node = tree->left;

    //switch places between balance node right and current node
    tree->left = balance_node->right;
    balance_node->right = tree;

    return balance_node;

}


/*
left rotation function
    parameter: tree: node
*/
t_node *leftRotation(t_node *tree)
{
    t_node *balance_node;
    balance_node = tree->right;

    //switch places between balance node left and current node
    tree->right = balance_node->left;
    balance_node->left = tree;

    return balance_node;
}


/*
function to balance the tree
    parameter: tree: node
*/
void balanceTree(t_node *root)
{
    //check if there is a problem with balance factor
    if(root->left->bf > 1)
    {
        //balance left child of root
        root->left = rightRotation(root->left);
    }

    //update balance factor
    updateBalanceFactor(root);
    levelOrder(root);


    printf("\n");

    //check another problem with balance factor
    if(root->bf > 1)
    {
        //then balance root node
        root = rightRotation(root);
    }

    //call level order
    updateBalanceFactor(root);
    levelOrder(root);
}



/*
main function
*/
int main()
{

    t_node *BinaryTree = NULL;

    //create the tree
    BinaryTree = UnbalancedTree(BinaryTree);
    updateBalanceFactor(BinaryTree);
    levelOrder(BinaryTree);
    printf("\n");

    //balance
    balanceTree(BinaryTree);

    //free
    free_tree(BinaryTree);


    return 0;
}
