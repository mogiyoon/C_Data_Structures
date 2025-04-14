//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS1(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS1(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS1(BSTNode *root)
{
	Stack* tmpStack = (Stack*)malloc(sizeof(Stack));
	BSTNode* tmpNode = root;
	push(tmpStack, root);

	//가장 먼저 나오는 노드까지 도달
	while (tmpNode->left != NULL || tmpNode->right != NULL) {
		if (tmpNode->left != NULL) {
			tmpNode = tmpNode->left;
			push(tmpStack, tmpNode);
		} else if (tmpNode->right != NULL)
		{
			tmpNode = tmpNode->right;
			push(tmpStack, tmpNode);
		}
	}

	//스택이 빌 때까지
	while (tmpStack->top != NULL) {
		tmpNode = pop(tmpStack);
		//루트노드면 출력 후 탈출 
		if (tmpStack->top == NULL) {
			printf("%d ", tmpNode->item);
			break;
		}

		//부모 노드의 오른쪽 노드일 때는 그냥 출력
		if (peek(tmpStack)->right == tmpNode) {
			printf("%d ", tmpNode->item);
		}

		//부모 노드의 왼쪽 노드일 경우 출력한 뒤
		else if (peek(tmpStack)->left == tmpNode) {
			printf("%d ", tmpNode->item);

			//부모 노드의 오른쪽 노드가 있을 경우 한 칸씩 이동하며
			while (peek(tmpStack)->right != NULL) {
				tmpNode = peek(tmpStack)->right;
				push(tmpStack, tmpNode);

				//가장 깊은 곳의 노드 찾음
				while (tmpNode->left != NULL || tmpNode->right != NULL) {
					if (tmpNode->left != NULL) {
						tmpNode = tmpNode->left;
						push(tmpStack, tmpNode);
					} else if (tmpNode->right != NULL)
					{
						tmpNode = tmpNode->right;
						push(tmpStack, tmpNode);
					}
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
