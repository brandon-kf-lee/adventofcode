/* Advent of Code
 * Doubly Linked List Implementation (Created for lists of long long integer ranges)
 *   Modified from GeeksforGeeks (https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/)
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include "./dll.h"

range* create_range(long long lower, long long upper) {
    range* newRange = (range*)malloc(sizeof(range));
    newRange->lower = lower;
    newRange->upper = upper;
    newRange->next = NULL;
    newRange->prev = NULL;
    return newRange;
}

void insert_range(range** head, long long lower, long long upper) {
    // creating new node
    range* newRange = create_range(lower, upper);

    // check if DLL is empty
    if (*head == NULL) {
        *head = newRange;
        return;
    }

    range* step = *head;

    // If the new node's lower is smaller than the head's put the new node at the beginning
    if(step->lower >= newRange->lower){
        free(newRange);
        insert_head(head, lower, upper);
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

int find_id(range** head, long long id) {
    // Check if DLL is empty
    if (*head == NULL) {
        return 0;
    }

    range* step = *head;
    while (step->next != NULL && (id < step->lower || id > step->upper)) {
        step = step->next;
    }

    // Return 0 if next node is null, otherwise, ID range found
    return (!(step->next)? 0 : 1);
}


void insert_head(range** head, long long lower, long long upper) {
    // creating new node
    range* newRange = create_range(lower, upper);

    // check if DLL is empty
    if (*head == NULL) {
        *head = newRange;
        return;
    }
    newRange->next = *head;
    (*head)->prev = newRange;
    *head = newRange;
}

void print_list(range* head) {
    range* temp = head;
    printf("Forward List:\n");
    while (temp != NULL) {
        printf("%lld-%lld\n", temp->lower, temp->upper);
        temp = temp->next;
    }
    printf("\n");
}

void delete_list(range* head) {
    range* step = head;
    range* next;

    if(head == NULL) return;

    do{
        next = step->next;
        free(step);
        step = next;
    } while(step != NULL);
}