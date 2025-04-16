//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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
			// removeAllItems(&ll);
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

int insertSortedLL(LinkedList *ll, int item)
{
	// item으로 입력받은 값으로 노드를 하나 만들기
	// 그 노드를 linkedlist에 넣자 -> 포인터로 연결해서 넣는건가...?
	// 입력받은값이 이미 linkedlist에 존재하면 -1을 리턴
	// 존재하지 않으면 삽입하는데 삽입하고 그때의 인덱스값을 리턴
	
	//새로운 노드 기본 설정
	ListNode* newNode;
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->item = item;
	newNode->next = NULL;
	
	ListNode* nextNode;			//변수 생성(다음 노드를 가리키는 것)
	ListNode* nowNode;			//변수 생성(현재 노드를 가리키는 것)

	int index = 0;

	if (ll==NULL)
		return -1;

	if (ll->head==NULL){
		ll->head = newNode;
		ll->size+=1;
		return index;
	}else if(item < ll->head->item){
		newNode->next = ll->head;
		ll->head = newNode;
	}else{
		nextNode = ll->head;
	}

	while(item >nextNode->item && nextNode->next != NULL){
		nowNode = nextNode;
		nextNode = nextNode->next;
		index +=1;
	}

	if(item < nextNode -> item){
		nowNode->next = newNode;
		newNode->next = nextNode;
		ll->size+=1;
		return index;
	} else if(item ==nextNode->item){
		return -1;
	}else{
		nextNode->next = newNode;
		ll->size+=1;
		return index;
	}
	

}

/*
소영님 코드
int insertSortedLL(LinkedList *ll, int item)
{
    //현재 LinkedList의 크기가 0이면 LinkedList가 비어있다는 뜻이므로 그냥 넣기
    if(ll->size==0){
        insertNode(ll, 0, item);
        return 0; //첫 번째 인덱스에 넣었으므로 인덱스 0을 리턴
    }
    //크기가 0이 아니면 item이 이미 존재하는지 찾기
    int i;
    for(i=0; i<ll->size; ++i){
        ListNode* found_node = findNode(ll, i);
        if(found_node->item == item){ //이미 존재하면 -1 리턴
            printf("already exist");
            return -1;
        }
        if(found_node->item > item){ //item보다 큰 값을 발견하면 해당 값의 앞에 item을 삽입하기
            insertNode(ll, i, item);
            printf("inserted %d in %d", item, i);
            return i; //삽입한 인덱스 리턴			
        }
		else if(found_node->next ==NULL ){
			insertNode(ll,i+1,item);
			printf("inserted %d in %d", item, i);
			return i+1 ;
		}
    }
    return -1;
}
*/

// 기윤님코드
/*
int insertSortedLL(LinkedList *ll, int item)
{
  ListNode* newNode;
  newNode = (ListNode*)malloc(sizeof(ListNode));
  newNode -> item = item;
  newNode -> next = NULL;
  ListNode* nextNode;
  ListNode* nowNode;
  nextNode = (ListNode*)malloc(sizeof(ListNode));
  nowNode = (ListNode*)malloc(sizeof(ListNode));
  int index = 0;
  if (ll -> head == NULL) {
    ll -> head = newNode;
    ll -> size += 1;
    return index;
  } else {
    nextNode = ll -> head;
  }
  while (item > nextNode -> item && nextNode -> next != NULL) {
    nowNode = nextNode;
    nextNode = nextNode -> next;
    index += 1;
  }
  if (item == nextNode -> item) {
    return -1;
  } else if (item < nextNode -> item) {
    nowNode -> next = newNode;
    newNode -> next = nextNode;
    ll -> size += 1;
    return index;
  } else {
    nextNode -> next = newNode;
    return index;
  }
}
*/
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

// k번째 인덱스의 값이 있는지 없는지 알려주는 함수
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
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
