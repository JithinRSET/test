#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int sum=0;
struct Node {
    char e_id[5];
	int data;
	struct Node *left, *right;
};
typedef struct Node Node;

Node* newNode(int data, char *id)
{
	Node* node = (Node*)malloc(sizeof(Node));
	strcpy(node->e_id, id);
	node->data = data;
	node->left = node->right = NULL;
	return (node);
}

// function to return the index of close parenthesis
int findIndex(char* str, int si, int ei)
{
    int x=0;
	if (si > ei)
		return -1;


	for (int i = si; i <= ei; i++) {
		// if open parenthesis, push it
		if (str[i] == '(')
			x++;

		// if close parenthesis
		else if (str[i] == ')') {
			if (x>0) {
				x--;

				// if stack is empty, this is
				// the required index
				if (x==0)
					return i;
			}
		}
	}
	// if not found return -1
	return -1;
}

// function to construct tree from string
Node* treeFromString(char* str, int si, int ei)
{
    int x=0,y=1,z=si,w;
    char id[5];
	// Base case
	if (si > ei)
		return NULL;

    for(int i=0;i<4;i++){
        id[i]=str[si];
        si++;
    }
    id[4]='\0'; z=si;
    while(isdigit(str[si])){
        si++;
    }
    w=si;
    while(w!=z){
        w--;
        x=x+(y*(str[w] - '0'));
        y=y*10;
        //printf("*%d*",x);
    }
    si--;

    //( 1 ( 2 ( 4 ( 8 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 5 ( ) ( ) ) ) ( 3 ( 6 ( 10 ( ) ( ) ) ( ) ) ( ) ) )
	// new root
	//printf("**%d**",x);
	Node* root = newNode(x,id);
	int index = -1;

	// if next char is '(' find the index of
	// its complement ')'
	if (si + 1 <= ei && str[si + 1] == '(')
		index = findIndex(str, si + 1, ei );

	// if index found
	if (index != -1) {

		// call for left subtree
		root->left = treeFromString(str, si + 2, index - 1);

		// call for right subtree
		root->right
			= treeFromString(str, index + 2, ei - 1);
	}
	return root;
}
void print_employees(Node* root){
    if(root != NULL){
        print_employees(root->left);
        print_employees(root->right);
        printf("%s ",root->e_id);
    }
}

int find_employees(Node* tree)
{
    int lsum = 0, rsum = 0;
    if(tree->left==NULL && tree->right==NULL)
        return tree->data;
    
    if(tree->left != NULL){
        lsum = find_employees(tree->left);
    }
    if(tree->right != NULL){
        rsum = find_employees(tree->right);
    }
    
    if((lsum+rsum) == (tree->data))
        printf("%s ",tree->e_id);
        
        return(lsum+rsum+tree->data);
    
}

// int findMax(struct Node* root)
// {
//     // Base case
//     if (root == NULL)
//         return INT_MIN;

//     // Return maximum of 3 values:
//     // 1) Root's data 2) Max in Left Subtree
//     // 3) Max in right subtree
//     int res = root->data;
//     int lres = findMax(root->left);
//     int rres = findMax(root->right);
//     if (lres > res)
//         res = lres;
//     if (rres > res)
//         res = rres;
//     return res;
// }

// void find_employees(Node* root){
//     while(root != NULL){
//         if(findMax(root->left)<root->data && findMax(root->right)<root->data){
//             printf("%s ",root->e_id);
//         }
//         find_employees(root->left);
//         find_employees(root->right);

//     }

// }

int main()
{
	char str[1000];
	gets(str);
	int len=strlen(str),i,j,num;
	if(len<=2) return 0;
	int k;
	for(i=0;i<len;i++){
        if(str[i]==' '){
            for(j=i;j<len;j++){
                str[j]=str[j+1];
            }
            len--;
        }
	}
	//puts(str); printf("\n");
	Node* root = treeFromString(str, 1, len - 2);
	print_employees(root);
	printf("\n");
	num = find_employees(root);
	return 0;
}

