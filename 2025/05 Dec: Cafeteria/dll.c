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
    // Check if DLL is empty
    if (*head == NULL) {
        *head = create_range(lower, upper);
        return;
    }

    // If the new range's lower is smaller than the head's, put the new node at the beginning
    if((*head)->lower >= lower){
        insert_head(head, lower, upper);
        deduplicate_range((*head), (*head)->next);
        return;
    }

    // Find the in-order place for the new node, based on lower bounds
    // Create current range and prev (starting at the head)
    range* current = create_range(lower, upper);
    range* prev = *head;

    // Navigate to after a node with a smaller lower bound and before a node with a larger or same lower bound
    while((prev->next) != NULL && 
          (prev->lower       > current->lower || 
           prev->next->lower < current->lower)) {

        prev = prev->next;
    }

    // Insert node in place
    current->next = prev->next;
    current->prev = prev;
    if (prev->next != NULL) {
        prev->next->prev = current;
    }
    prev->next = current;  

    deduplicate_range(prev, current);
}

void deduplicate_range(range* prev, range* current) {

    // Keep attempting to deduplicate as long as the end isn't reached and current's lower is above prev's lower
    while(current != NULL && prev->lower <= current->lower){
        // Absorb if current's lower is in-between the previous's bounds
        if(current->lower >= prev->lower && 
           current->lower <= prev->upper) {
            
            // Replace upper bound only if its upper is larger than previous's upper
            if(current->upper >= prev->upper) {
                prev->upper = current->upper;
            }
            // Full range is absorbed, so delete the range
            delete_range(current);

            // After current has been freed/absorbed, continue from prev
            current = prev;
        }
        // Shift two pointers to the next node, unless it's NULL
        if((current = current->next) == NULL || (prev = current->prev) == NULL) return;
    }
}

void insert_head(range** head, long long lower, long long upper) {
    range* newRange = create_range(lower, upper);

    // Check if DLL is empty
    if (*head == NULL) {
        *head = newRange;
        return;
    }
    newRange->next = *head;
    (*head)->prev = newRange;
    *head = newRange;
}

int find_id(range** head, long long id) {
    // Check if DLL is empty
    if (*head == NULL) return 0;

    range* temp = *head;
    do {
        if (id >= temp->lower && id <= temp->upper) return 1;
    } while ((temp = temp->next) != NULL);

    return 0;
}

long long range_total(range* head) {
    range* temp = head;
    long long total = 0;
    while (temp != NULL) {
        total += (temp->upper - temp->lower) + 1;
        temp = temp->next;
    }
    return total;
}

void delete_range(range* node){
    if(node == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node);
}

void delete_list(range* head) {
    range* temp = head;
    range* next;

    if(head == NULL) return;

    do {
        next = temp->next;
        free(temp);
        temp = next;
    } while(temp != NULL);
}

void print_list(range* head) {
    range* temp = head;
    printf("Forward List:\n");
    while (temp != NULL) {
        printf("(%lld-%lld) ", temp->lower, temp->upper);
        temp = temp->next;
    }
    printf("\n\n");
}
