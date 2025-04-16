//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 틀린 코드 : 마지막 부분에 노드를 삽입하는 로직이 없음
// int insertSortedLL(LinkedList *ll, int item)
// {
// 	//현재 LinkedList의 크기가 0이면 LinkedList가 비어있다는 뜻이므로 그냥 넣기
// 	if(ll->size==0){
// 		insertNode(ll, 0, item);
// 		return 0; //첫 번째 인덱스에 넣었으므로 인덱스 0을 리턴
// 	}
// 	//크기가 0이 아니면 item이 이미 존재하는지 찾기
// 	int i;
// 	for(i=0; i<ll->size; ++i){
// 		ListNode* found_node = findNode(ll, i);
// 		if(found_node->item == item){ //이미 존재하면 -1 리턴
// 			printf("already exist");
// 			return -1;
// 		}
// 		if(found_node->item > item){ //item보다 큰 값을 발견하면 해당 값의 앞에 item을 삽입하기
// 			insertNode(ll, i, item);
// 			printf("inserted %d in %d", item, i);
// 			return i; //삽입한 인덱스 리턴
// 		}
// 	}
// 	return -1;
// }

// 맞는 코드 : 구현되어있는 함수를 사용했음
// int insertSortedLL(LinkedList *ll, int item)
// {
// 	//현재 LinkedList의 크기가 0이면 LinkedList가 비어있다는 뜻이므로 그냥 넣기
// 	if(ll->size==0){
// 		insertNode(ll, 0, item);
// 		return 0; //첫 번째 인덱스에 넣었으므로 인덱스 0을 리턴
// 	}
// 	//크기가 0이 아니면 item이 이미 존재하는지 찾기
// 	int i;
// 	for(i=0; i<ll->size; ++i){
// 		ListNode* found_node = findNode(ll, i);
// 		if(found_node->item == item){ //이미 존재하면 -1 리턴
// 			printf("already exist");
// 			return -1;
// 		}
// 		if(found_node->item > item){ //item보다 큰 값을 발견하면 해당 값의 앞에 item을 삽입하기
// 			insertNode(ll, i, item);
// 			printf("inserted %d in %d", item, i);
// 			return i; //삽입한 인덱스 리턴
// 		} else if(found_node->next==NULL){
// 			insertNode(ll, i+1, item);
// 			return i+1;
// 		}
// 	}
// 	return -1;
// }

int insertSortedLL(LinkedList *ll, int item){
	//create a new node in memory for a linked list and let newNode point to it.
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->item = item;
	newNode->next = NULL;

	if(ll->head==NULL){
		ll->head = newNode;
		ll->size++;
		return 0;
	}

	if(ll->head->item > item){
		newNode->next = ll->head;
		ll->head = newNode;
		ll->size++;
		return 0;
	}

	ListNode* cur = ll->head;
	ListNode* prev = NULL;
	int index = 0;
	while(cur->next != NULL && cur->item < item){
		prev = cur;
		cur = cur->next;
		index++;
	}
	if(cur->item == item){
		return -1;
	}
	if(cur->next!=NULL){
		prev->next = newNode;
		newNode->next = cur;
		ll->size++;
		return index;
	}
	cur->next = newNode;
	ll->size++;
	return index;

}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){
	//연결리스트 안에 있는 index번째의 노드를 찾아서 리턴하는 함수

	ListNode *temp;

	//head노드가 가리키는 값이 없거나, 인덱스값이 음수거나, 인덱스값이 현재 연결리스트 사이즈보다 클 경우 
	if (ll == NULL || index < 0 || index >= ll->size) 
		return NULL;

	//첫 번째 노드를 temp에 저장
	temp = ll->head;

	//첫 번째 노드가 없거나 인덱스가 음수일 때
	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){ 
		temp = temp->next; //다음 노드를 찾기
		if (temp == NULL) //다음 노드가 없음
			return NULL;
		index--; //인덱스 크기 만큼 첫 번째 노드에서 다음 노드로 가기
	}

	return temp; //index번째의 노드를 리턴
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
