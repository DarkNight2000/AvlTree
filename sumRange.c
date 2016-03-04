#include<stdio.h>
#include<stdlib.h>

/* Author Mike Zhang(zhang.4660) */

/* build up AVL tree */
struct Node {

        long long key;
        long long height;
        long long sum;
        
        struct Node *left;
        struct Node *right;
};
 
 
/* calculate the height of tree */
long long height(struct Node *N){

    	if (N == NULL){
		return 0;
        }
        return N->height;
}
 
/* report the larger value of two number */
long long max(long long a, long long b){
        return (a > b)? a : b;
}
 
/* allocates memeory for a new node */
struct Node* createNode(long long data){

        struct Node* node = (struct Node*) malloc(sizeof(struct Node));
        
        node->key = data;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;  
        
        return node;
}
 
/* right rotate 2 nodes */
struct Node* rightRotate(struct Node *y){
        struct Node *x = y->left;
    	struct Node *T2 = x->right;
 
    	/* right rotate */
    	x->right = y;
    	y->left = T2;
 
    	/* Update heights */
    	y->height = max(height(y->left), height(y->right)) + 1;
    	x->height = max(height(x->left), height(x->right)) + 1;
 
    	return x;
}
 
/* left rotate 2 nodes */
struct Node* leftRotate(struct Node *x){
	struct Node *y = x->right;
	struct Node *T2 = y->left;
	 
   	/* left rotate */
	y->left = x;
	x->right = T2;
	 
    	/* Update heights */
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;
	 
	return y;
}
 
/* balance the tree height */
long long getBalance(struct Node *N){
    	if (N == NULL){
    		return 0;
        }
    	return height(N->left) - height(N->right);
}

/* insert node into the binary search tree */
struct Node* insert(struct Node *node, long long data){
        
        /* insert the node into the binary search tree */
        if (node == NULL){
        	return(createNode(data));
 	}
	if (data < (node->key)){
        	node->left = insert(node->left, data);

    	}else{
        	node->right = insert(node->right, data);

 	}
 

    	/* update height of node */
	node->height = max(height(node->left), height(node->right)) + 1;
	 
	/* check whether this node is unbalanced */
	long long balance = getBalance(node);
	 
	/* there are 4 cases for unbalanced node */
	 
	/* case 1:Left Left */
	if (balance > 1 && data < node->left->key)
		return rightRotate(node);
	 
	/* case 2:Right Right */
        if (balance < -1 && data > node->right->key)
		return leftRotate(node);
	 
	/* case 3: Left Right */
	if (balance > 1 && data > node->left->key){
	
		node->left =  leftRotate(node->left);
		return rightRotate(node);
	}
 
	/* case 4: Right Left */
    	if (balance < -1 && data < node->right->key){
    	
        	node->right = rightRotate(node->right);
        	return leftRotate(node);
    	}
 
    	/* return the (unchanged) node pointer */
    	return node;
}
 
/* printout the binary search tree in preorder */
void preOrder(struct Node *root){

    	if(root != NULL){
        	printf("%d ", root->key);
        	preOrder(root->left);
        	preOrder(root->right);
    	}
}

/* printout the binary search tree in inorder */
void inOrder(struct Node *root){

    	if(root != NULL){

        	inOrder(root->left);
        	printf("%d ", root->key);
        	inOrder(root->right);
    	}
}

/* printout the binary search tree in postorder */
void postOrder(struct Node *root){

    	if(root != NULL){

        	postOrder(root->left);
        	postOrder(root->right);
        	printf("%d ", root->key);
    	}
}

long long sumTree(struct Node *node){

	if(node != NULL) {
	
	/* store the root value */
		node->sum = node->key + sumTree(node->left) + sumTree(node->right);
	}else{
		return 0;
		
	}
	return node->sum;

}

/* compute the sum value of node that is less than or equal to k */
long long countLessThan(struct Node *n, long long min){
	long long result = 0;
	if(n != NULL){
		if(n->key < min){
			result = result + n->key;
			if(n->left != NULL){
				result = result + n->left->sum;
			}
			if(n->right != NULL){
				result = result + countLessThan(n->right, min);
			}
		}else{
			if(n->left != NULL){
				result = result + countLessThan(n->left, min);
			}
		}
	}

	return result;
}

/* compute the sum value of node that is less than or equal to k */
long long countGreaterThan(struct Node *n, long long max){
	long long result = 0;
	if(n != NULL){
		if(n->key > max){
			result = result + n->key;
			if(n->right != NULL){
				result = result + n->right->sum;
			}
			if(n->left != NULL){
				result = result + countGreaterThan(n->left, max);
			}
		}else{
			if(n->right != NULL){
				result = result + countGreaterThan(n->right, max);
			}
		}
	}

	return result;
}

/* compute the range value */
long long rangeCompute(struct Node *n, long long min, long long max){
    long long result = 0;

    if(n != NULL){
        result = n->sum - (countGreaterThan(n, max) + countLessThan(n, min));
    }    
    return result;
}
 
/* import the dataX and rangeX file to do calculation */

int main(int argc, char**argv){

	long long element;
	long long min = 0;
	long long max = 0;
	long long sum = 0;
	
        struct Node *root = (struct Node*)NULL; //construct the head node 
	
	/* read the array from file dataX */
	
	FILE *data  = fopen(argv[1], "r"); 
	
	if (data == NULL) {
  		fprintf(stderr, "Can't open input file in.list!\n");
 		return 1;
	}
	
	
	while(fscanf(data, "%Ld", &element)!= EOF){
		root = insert(root, element);
	}
	fclose(data);
	
	/* print out the binary search tree in 3 different orders :*/
	printf("Preorder traversal of the AVL tree is \n");
	preOrder(root);
	
	printf("\n\nInorder traversal of the AVL tree is \n");
	inOrder(root);
	
	printf("\n\nPostorder traversal of the AVL tree is \n");
	postOrder(root);
	
	/* assign value to the sum in the tree */
	sumTree(root);
	
	
	/*printf("\nThe sum of root %Ld\n", root->sum);
	printf("\nThe sum of root left child %Ld\n", root->left->sum);
	printf("\nThe sum of root right child %Ld\n", root->right->sum);*/
	/* read the range min and max value from the file rangeX */
	
	printf("\n");
	
	FILE *range = fopen(argv[2], "r");
	if (range == NULL) {
  		fprintf(stderr, "Can't open input file in.list!\n");
 		return 1;
	}
	while(fscanf(range, "%Ld %Ld", &min, &max)!= EOF){
		sum = rangeCompute(root, min, max);
		printf("Range[%Ld, %Ld]. Sum: %Ld.\n", min, max, sum);
		
	}
	
	fclose(range);
	/* free memory for the binary tree */
	free(root);
	return 0; 

}
