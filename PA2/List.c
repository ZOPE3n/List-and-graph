/** Mengdi Wei
  * ID:1538074
  * PA2
  * List.c is the library for the lex.c
  */

#include<stdio.h>
#include<stdlib.h>

#include "List.h"
// structs
typedef struct NodeObj {
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
    Node front;
    Node back;
    Node curr;
    int cursorIndex;
    int length;
} ListObj;

// Constructors-Deconstructors
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);
}

void freeNode(Node* pN) {
    if(pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->curr = NULL;
    L->cursorIndex = -1;
    L->length = 0;
    return(L);
}

void freeList(List* pL) {
    if(pL!=NULL && *pL!=NULL){
    Node fl = (*pL)->front;
    while(fl!=NULL){
        Node curr = fl;
        fl = fl->next;
        free(curr);
    }
    free(*pL);
    *pL = NULL;
  }
}

/*
-   Access functions
*/
// Returns the number of elements in this List.
int length(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: length() called on null List reference\n");
        exit(1);
    }
    return L->length;
}

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1
int index(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: index() called on null List reference\n");
        exit(1);
    }
    if(L->length == 0) return -1;
    return L->cursorIndex;
}

// Returns front element (pre: length() > 0).
int front(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: front() called on null List reference\n");
        exit(1);
    }
    if(L->length == 0) {
        fprintf(stderr, "List error: front() called on empty List\n");
        exit(1);
    }
    return L->front->data;
}

// Returns back element (pre: length() > 0).
int back(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: back() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: back() called on empty List\n");
        exit(1);
    }
    return L->back->data;
}

// Returns cursor element (pre: length() > 0).
int get(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: get() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: get() called on empty list\n");
        exit(1);
    }
    if(L->cursorIndex == -1) {
        fprintf(stderr, "List error: get() called on undefined cursor\n");
        exit(1);
    }
    return L->curr->data;
}

// Returns true if this List and L are the same integer sequence;
// the cursor is ignored in both lists.
int equals(List A, List B) {
    if(A == NULL || B == NULL) {
        fprintf(stderr, "List error: equals() called on null List reference ");
        fprintf(stderr, "One or more of your Lists may be null.\n");
        exit(1);
    }
    if(A->length != B->length) return 0;
    Node tmp1 = A->front;
    Node tmp2 = B->front;
    while(tmp1 != NULL && tmp2 != NULL) {
        if(tmp1->data != tmp2->data) return 0;
        else {
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
    }
    return 1;
}

/*
-   Manipulation functions
*/
// Resets this List to its original empty state.
void clear(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: clear() called on null List reference\n");
        exit(1);
    }
    Node tmp = L->front;
    while(tmp != NULL) {
        Node currTmp = tmp;
        tmp = tmp->next;
        free(currTmp);
    }
    L->front = L->back = L->curr = NULL;
    L->cursorIndex = -1;
    L->length = 0;
}

// If List is non-empty, places the cursor under the front element;
// otherwise does nothing.
void moveFront(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: moveFront() called on null List reference\n");
        exit(1);
    }
    if(L->length > 0) {
        L->curr = L->front;
        L->cursorIndex = 0;
    }
}

// If List is non-empty, places the cursor under the back element;
// otherwise does nothing.
void moveBack(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: moveBack() called on null List reference\n");
        exit(1);
    }
    if(L->length > 0) {
        L->curr = L->back;
        L->cursorIndex = L->length - 1;
    }
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: movePrev() called on null List reference\n");
        exit(1);
    }
    if(L->curr == L->front) {
        L->curr = NULL;
        L->cursorIndex = -1;
    } else {
        L->curr = L->curr->prev;
        L->cursorIndex--;
    }
}

// If cursor is defined and not at back, moves cursor one step toward
// front of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: moveBack() called on null List reference\n");
        exit(1);
    }
    if(L->curr == L->back) {
        L->curr = NULL;
        L->cursorIndex = -1;
    } else {
        L->curr = L->curr->next;
        L->cursorIndex++;
    }
}

// Insert new element into this List. If List is non-empty, insertion
// takes place before the front element.
void prepend(List L, int data) {
    if(L == NULL) {
        fprintf(stderr, "List error: prepend() called on null List reference\n");
        exit(1);
    }
    Node tmp = newNode(data);
    tmp->next = L->front;
    tmp->prev = NULL;
    if(L->front == NULL)
        L->back = tmp;
    else
        L->front->prev = tmp;
    L->front = tmp;
    L->length++;
}

// Insert new element into this List. If List is non-empty, insertion
// takes place after the last element.
void append(List L, int data) {
    if(L == NULL) {
        fprintf(stderr, "List error: append() called on null List reference\n");
        exit(1);
    }
    Node tmp = newNode(data);
    tmp->prev = L->back;
    tmp->next = NULL;
    if(L->back == NULL)
        L->front = tmp;
    else
        L->back->next = tmp;
    L->back = tmp;
    L->length++;
}

// Insert new element before cursor (pre: length() > 0, index() > 0).
void insertBefore(List L, int data) {
    if(L == NULL) {
        fprintf(stderr, "List error: insertBefore() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: insertBefore() called on empty List\n");
        exit(1);
    }
    if(L->curr == NULL) {
        fprintf(stderr, "List error: insertBefore() called on undefined cursor\n");
        exit(1);
    }
    if(L->curr == L->front) {
        prepend(L, data);
        return;
    }
    if(!(length(L) > 0 && index(L) >= 0)) return;
    Node tmp = newNode(data);
    tmp->prev = L->curr->prev;
    tmp->next = L->curr;
    if(L->curr->prev != NULL)
        L->curr->prev->next = tmp;
    else
        L->front = tmp;
    L->curr->prev = tmp;
    L->length++;
}

// Insert new element after cursor (pre: length() > 0, index() > 0).
void insertAfter(List L, int data) {
    if(L == NULL) {
        fprintf(stderr, "List error: insertAfter() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: insertAfter() called on empty List\n");
        exit(1);
    }
    if(L->curr == NULL) {
        fprintf(stderr, "List error: insertAfter() called on undefined cursor\n");
        exit(1);
    }
    if(L->curr == L->back) {
        append(L, data);
        return;
    }
    Node tmp = newNode(data);
    tmp->prev = L->curr;
    tmp->next = L->curr->next;
    if(L->curr->next != NULL)
        L->curr->next->prev = tmp;
    L->curr->next = tmp;
    L->length++;
}

// Deletes the front element (pre: length() > 0).
void deleteFront(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: deleteFront() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: deleteFront() called on empty List\n");
        exit(1);
    }
    Node tmp = L->front;
    if(length(L) > 1) L->front = L->front->next;
    else L->front = L->back = NULL;
    L->length--;
    freeNode(&tmp);
}

// Deletes the back element (pre: length() > 0).
void deleteBack(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: deleteBack() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: deleteBack() called on empty List\n");
        exit(1);
    }
    if(L->curr == L->back) {
        L->curr = NULL;
        L->cursorIndex = -1;
    }
    Node tmp = L->back;
    L->back = L->back->prev;
    L->back->next = NULL;
    L->length--;
    freeNode(&tmp);
}

// Deletes the cursor element, making cursor undefined (pre: length() > 0,
// index() > 0).
void delete(List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: delete() called on null List reference\n");
        exit(1);
    }
    if(L->length <= 0) {
        fprintf(stderr, "List error: delete() called on empty List\n");
        exit(1);
    }
    if(L->curr == NULL) {
        fprintf(stderr, "List error: delete() called on undefined cursor");
        exit(1);
    }
    if(L->curr == L->back) {
        deleteBack(L);
        return;
    }
    else if(L->curr == L->front) {
        deleteFront(L);
        return;
    }
    L->curr->prev->next = L->curr->next;
    L->curr->next->prev = L->curr->prev;
    L->curr = NULL;
    L->cursorIndex = -1;
    L->length--;
}

/*
-   Other methods
*/
// Overrides Object's toString method. Returns a String representation of
// this List consisting of a space separated sequence of integers, with
// front on the left.
void printList(FILE* out, List L) {
    if(L == NULL) {
        fprintf(stderr, "List error: printList() called on null List reference\n");
        exit(1);
    }
    Node tmp = L->front;
    int i = 0;
    while(tmp != NULL) {
        if(i != 0) fprintf(out, " %d", tmp->data);
        else fprintf(out, "%d", tmp->data);
        tmp = tmp->next;
        i++;
    }
}

// Returns a new List representing the same integer sequence as this List.
// The cursor in the new list is undefined, regardless of the state of the
// cursor in this List. The List is unchanged.
List copyList(List L) {
    List copiedList = newList();
    Node tmp = L->front;
    while(tmp != NULL) {
        append(copiedList, tmp->data);
        tmp = tmp->next;
    }
    return copiedList;
}