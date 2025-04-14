#include <stdio.h>

// void RecursiveReverse(ListNode **ptrHead)
// {
//     if (*ptrHead ==NULL || (*ptrHead)->next ==NULL){
//         return;
//     }
//     ListNode* rest = (*ptrHead)->next;
//     RecursiveReverse(&rest);
//     (*ptrHead) -> next -> next = *ptrHead;
//     (*ptrHead) -> next =NULL;
//     *ptrHead = rest;
// }

int main() {
  int a = 10;
  int* ptrA = &a;
  int** dPtrA = &ptrA;
}

void testRecur(int** testInt) {
  
}