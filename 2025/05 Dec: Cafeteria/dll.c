/* Advent of Code
 * Doubly Linked List Implementation (Created for lists of long long integer ranges)
 *   Modified from GeeksforGeeks (https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/)
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include "./dll.h"

Range* createRange(long long lower, long long upper)
{
    Range* newRange = (Range*)malloc(sizeof(Range));
    newRange->lower = lower;
    newRange->upper = upper;
    newRange->next = NULL;
    newRange->prev = NULL;
    return newRange;
}

void insertRange(Range** head, long long lower, long long upper) {
    // creating new node
    Range* newRange = createRange(lower, upper);

    // check if DLL is empty
    if (*head == NULL) {
        *head = newRange;
        return;
    }

    Range* step = *head;

    // If the new node's lower is smaller than the head's put the new node at the beginning
    if(step->lower >= newRange->lower){
        free(newRange);
        insertAtBeginning(head, lower, upper);
        return;
    }

    // Find the place for newRange: after a node with a smaller lower bound, before a node with a larger lower bound
    while (step->next != NULL && 
           (step->lower >= newRange->lower || 
           step->next->lower <= newRange->lower)) {
           
        step = step->next;
    }

    // Insert node in place
    newRange->next = step->next;
    newRange->prev = step;
    if (step->next != NULL) {
        step->next->prev = newRange;
    }
    step->next = newRange;

}

int findID(Range** head, long long id) {
    // Check if DLL is empty
    if (*head == NULL) {
        return 0;
    }

    Range* step = *head;
    while (step->next != NULL && (id < step->lower || id > step->upper)) {
        step = step->next;
    }

    // Return 0 if next node is null, otherwise, ID range found
    return (!(step->next)? 0 : 1);
}


void insertAtBeginning(Range** head, long long lower, long long upper)
{
    // creating new node
    Range* newRange = createRange(lower, upper);

    // check if DLL is empty
    if (*head == NULL) {
        *head = newRange;
        return;
    }
    newRange->next = *head;
    (*head)->prev = newRange;
    *head = newRange;
}

void insertAtEnd(Range** head, long long lower, long long upper)
{
    // creating new node
    Range* newRange = createRange(lower, upper);

    // check if DLL is empty
    if (*head == NULL) {
        *head = newRange;
        return;
    }

    Range* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newRange;
    newRange->prev = temp;
}

void insertAtPosition(Range** head, long long lower, long long upper, int position)
{
    if (position < 1) {
        fprintf(stderr, "Position should be >= 1.\n");
        return;
    }

    // if we are inserting at head
    if (position == 1) {
        insertAtBeginning(head, lower, upper);
        return;
    }
    Range* newRange = createRange(lower, upper);
    Range* temp = *head;
    for (int i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(
            "Position greater than the number of nodes.\n");
        return;
    }
    newRange->next = temp->next;
    newRange->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newRange;
    }
    temp->next = newRange;
}

void deleteAtBeginning(Range** head)
{
    // checking if the DLL is empty
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }
    Range* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void deleteAtEnd(Range** head)
{
    // checking if DLL is empty
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    Range* temp = *head;
    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

void deleteAtPosition(Range** head, int position)
{
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }
    Range* temp = *head;
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }
    for (int i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position is greater than the number of "
               "nodes.\n");
        return;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    free(temp);
}

void printListForward(Range* head)
{
    Range* temp = head;
    printf("Forward List:\n");
    while (temp != NULL) {
        printf("%lld-%lld\n", temp->lower, temp->upper);
        temp = temp->next;
    }
    printf("\n");
}

void printListReverse(Range* head)
{
    Range* temp = head;
    if (temp == NULL) {
        printf("The list is empty.\n");
        return;
    }
    // Move to the end of the list
    while (temp->next != NULL) {
        temp = temp->next;
    }
    // Traverse backwards
    printf("Reverse List:\n");
    while (temp != NULL) {
        printf("%lld-%lld\n", temp->lower, temp->upper);
        temp = temp->prev;
    }
    printf("\n");
}