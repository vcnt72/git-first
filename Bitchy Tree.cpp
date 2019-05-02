#include<stdio.h>
#include<stdlib.h>
/*
BST (Binary Search Tree)
---
Rule :
-node pertama disebut root
-setiap node bisa punya 2 anak (kiri/kanan)
-nilai yang lebih besar selalu ada di kanan
-nilai yang lebih kecil selalu ada di kiri
*/
struct node{
	int n;
	struct node *left, *right;
}*root;

struct node *createNode(int n){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->n=n;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

void printPreOrder(struct node *curr){
	if(curr!= NULL){
		printf("%d ",curr->n);
		printPreOrder(curr->left);
		printPreOrder(curr->right);
	}
}
//
//void printTree(struct node *curr, int lvl){
//	if(curr != NULL){
//		printTree(curr->right, lvl+1);
//		for(int i=0; i<lvl; i++){
//			printf("\t");
//		}
//		printf("%d\n", curr->n);
//		printTree(curr->left, lvl+1);
//	}
//
//}

struct node *anakKiriMax(struct node *c){
	if(c!=NULL){ 
		c=c->left;
		while(c->right!=NULL){
			c=c->right; // geser sampe mentok
		}
		return c;
	}
}

struct node *deleteNode(struct node *curr, int n){
	if(curr!=NULL){
		if(n > curr->n){// jika n lebih besar
			curr->right= deleteNode(curr->right,n); 
		}
		else if(n < curr->n){
			curr->left= deleteNode(curr->left,n);
		}
		else if(curr->n==n){
			if(curr->left==NULL && curr->right==NULL){
				free(curr);
				curr=NULL;
			}
			else if(curr->left!=NULL && curr->right==NULL){
				struct node *temp= curr->left;
				free(curr);
				return temp;
			}
			else if(curr->right!=NULL && curr->left==NULL){
				struct node *temp= curr->right;
				free(curr);
				return temp;
			}
			else if(curr->left!=NULL && curr->right!=NULL){
				struct node *temp=anakKiriMax(curr);
				curr->n= temp->n;
				curr->left = deleteNode(curr->left, curr->n);
			}
		}
		return curr;
	}	
}

struct node *insert(struct node *curr, int n){
	if(curr==NULL){//jika tidak ada data
		return createNode(n);
	}
	else if(n > curr->n){// jika n lebih besar
		curr->right= insert(curr->right,n); // disambungkan linknya
	}
	else if(n < curr->n){
		curr->left= insert(curr->left,n);
	}
	return curr;
}

int main(){
	root = insert(root, 8);
	root = insert(root, 4);
	root = insert(root, 12);
	root = insert(root, 2);
	root = insert(root, 6);
	root = insert(root, 3);
	root = insert(root, 10);
	root = insert(root, 11);
	printPreOrder(root);
	printf("\n");
//	printTree(root,0);
	root = deleteNode(root,12);
	printf("\n--------\n");
//	printTree(root,0);
	return 0;
}
