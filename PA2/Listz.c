#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
} ListObj;

typedef ListObj* List;

// Constructors-Destructors ---------------------------------------------------
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next=N->prev= NULL;
    return(N);   
}


void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
}
 

List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->cursor=L->front = L->back = NULL;
    L->length = 0;
    return(L);
}

void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL) { 
        while(length(*pL)>0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -----------------------------------------------------------


int front(List L) {
    if (L==NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);     
    }
    if(L->front==NULL ){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }
    return(L->front->data);
}

   

int back(List L) {
    if (L==NULL) {
       printf("List Error: calling back() on NULL List reference\n");
       exit(1);
    }
    if(L->front==NULL ){
       printf("List Error: calling back() on an empty List\n");
       exit(1);
    }
    return(L->back->data);
}


int length (List L) {

    if (L==NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return L->length;
}
int index(List L) {
    if (L==NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(1);
    }
    if(L->front==NULL ){
        printf("List Error: calling index() on an empty List\n");
        return -1;
        exit(1);
    }
    if (L->cursor==L->front) {
        return 0;
    }
    if (L->cursor==L->back) {
        return length(L)-1;
    }
    if (L->cursor!=NULL) {
        Node current =L->front;
        int i = 0; 
        while (current!=NULL&&current->data!=L->cursor->data) {
            current=current->next;
            i++;
        }
        return i; 
    }
    else {
        return -1;
    }
}

int equals(List A, List B) {
    if (length(A)!=length(B)) {
        return 0;
    }
    Node i = A->front;
    Node j = B->front;
    while (i!=NULL&&j!=NULL) {
        if (i->data!=j->data) {
            return 0;
        }
        else {
            i=i->next; 
            j=j->next;
        }
    }
    return 1;
}
int get(List L) {
    if (length(L)>0 && index(L)>=0) {
        return (L->cursor)->data;
    }
    return -10101010;
}
        	 


// Manipulation procedures ----------------------------------------------------

void clear (List L) {
    if (L==NULL){
        printf("List Error: calling clear(List L) on NULL List reference\n");
        exit(1);
    }
    if (length(L)==0 ){
        exit(1);
    }
    while (length(L)>0) {
        deleteFront(L);
    }
    L->length=0;
}
    
     



void moveFront(List L) {
    if (L==NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if (L->front!=NULL) {
        L->cursor=L->front;
    }
    return;
}


void moveBack(List L) {
    if (L==NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if (L->back!=NULL) {
        L->cursor=L->back;
    }
    return;
}

void movePrev(List L) {

    if (L==NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor!=NULL) {
        L->cursor=(L->cursor)->prev;
    }
    return;
}




void moveNext(List L) {
    if (L==NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor!=NULL) {
        L->cursor=L->cursor->next;
    } 
    return;
}




void prepend(List L, int data) {
    if (L==NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    Node current = newNode(data);
    if (length(L)==0) {
        L->front=L->back=current;
    }
    else {
        (L->front)->prev=current;
        current->next=L->front;
        L->front=current;
    }
    L->length++;
    return;
}     
         



void append(List L, int data) {
    if (L==NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node current = newNode(data);
    if (length(L)==0) {
        L->front=L->back=current;
    }
    else {
        (L->back)->next=current;
        current->prev=L->back;
        L->back=current;
    }
    L->length++;
    return;

}   

void insertBefore(List L, int data){
    if (L==NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if(length(L)==0 ){
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(1);
    }
    Node current = newNode(data);
    if (index(L)==0) {
        append(L,data);
    }
    else {
        current->prev=(L->cursor)->prev;
        current->next=(L->cursor);
        (current->prev)->next=current;
        (L->cursor)->prev=current;
    }
    L->length++;
}

void insertAfter(List L, int data){
    if (L==NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if(L->length==0 ){
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(1);
    }
    Node current = newNode(data);
    if (index(L)==0) {
        append(L,data);
    }
    else {
        current->next=(L->cursor)->next;
        current->prev=(L->cursor);
        (current->next)->prev=current;
        (L->cursor)->next=current;
    }
    L->length++;
}    


void deleteFront(List L){
    if (L==NULL){
        printf("List Error: calling deleteFront(List L) on NULL List reference\n");         
        exit(1);
    }
    if (length(L)==0 ){
        printf("List Error: calling deleteFront on an empty List\n");
        exit(1);   
    }
    Node N = L->front;
    if(length(L)>1 ) { 
        L->front = L->front->next;
        L->front->prev=NULL; 
    }
    else{ 
        L->front = L->back = NULL; 
    }
    freeNode(&N);
    L->length--;
}




void deleteBack(List L){
    Node N = NULL;
    if (L==NULL){
        printf("List Error: calling deleteBack(List L) on NULL List reference\n");
        exit(1);
    }
    if (length(L)==0 ){
        printf("List Error: calling deleteBack on an empty List\n");
        exit(1);
    }
    N = L->back;
    if(length(L)>1 ) {
        L->back = L->back->prev;
        L->back->next=NULL;
    }
    else{
        L->back = L->front = NULL;
    }
    freeNode(&N);
    L->length--;
}   



/*void delete(List L) {
    if (L!=NULL) {
        while (length(L)!=0) {
            deleteBack(L);
        }
        free(L);
    }
}
*/
        
    
void delete(List L) {   
    if (L==NULL){
        printf("List Error: calling delete(List L) on NULL List reference\n");
        exit(1);
    }   
     
    if(length(L)>0&&index(L)>=0){
        (L->cursor->prev)->next=L->cursor->next;
        (L->cursor->next)->prev=L->cursor->prev;
        L->length--;
    }
    Node N = L->cursor;
    freeNode(&N);
    return;
}





// Other operations -----------------------------------------------------------


void printList(FILE* out, List L){
    if (L==NULL){
        printf("List Error: calling printList(List L) on NULL List reference\n");
        exit(1);
    }
    Node N = L->front;
    while (N!=NULL) {
        fprintf(out, "%d ", N->data);
        N=N->next;
    }
    moveFront(L);
    moveNext(L);
    
    return;        
}


List copyList(List L){
    
    List cp = newList();
    Node current = L->front;
    while(current!=NULL) {
        append(cp, current->data);
        current=current->next;
    }
    return cp;
}





