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
        printf("empty, inserted:  (%lld-%lld)\n", (*head)->lower, (*head)->upper);
        return;
    }

    // If the new node's lower is smaller than the head's, put the new node at the beginning
    if((*head)->lower >= lower){
        insert_head(head, lower, upper);
        printf("new head, inserted: (%lld-%lld)\n", (*head)->lower, (*head)->upper);
        deduplicate_range((*head), (*head)->next);
        return;
    }

    // Create new node and step
    range* newRange = create_range(lower, upper);
    range* step = *head;

    printf("testing: (%lld-%lld)\n", newRange->lower, newRange->upper);
    printf("head: (%lld-%lld)\n", step->lower, step->upper);

    // Find the place for newRange until NULL is reached
    while((step->next) != NULL) {
        
        printf("  evaluating: (%lld-%lld) (%lld-%lld) \n", step->lower, step->upper, step->next->lower, step->next->upper);
        // After a node with a smaller lower bound, before a node with a larger or same lower bound
        printf("  %lld >= %lld (%d) && %lld <= %lld (%d) : (%s)\n", step->lower, newRange->lower, step->lower <= newRange->lower, step->next->lower, newRange->lower, step->next->lower >= newRange->lower, (step->lower <= newRange->lower && step->next->lower >= newRange->lower) ? "found it" : "not here");
        
        if(step->lower       <= newRange->lower && 
           step->next->lower >= newRange->lower) {
            break;
        }
        step = step->next;
    }

    printf("inserting after:  (%lld-%lld)\n", step->lower, step->upper);

    // Insert node in place
    newRange->next = step->next;
    newRange->prev = step;
    if (step->next != NULL) {
        step->next->prev = newRange;
    }
    step->next = newRange;  

    deduplicate_range(step, newRange);


}

void deduplicate_range(range* step, range* current) {
    //range* current = newRange;
    //

    // deduplicate if lower bound == prev upper bound
    
    //printf("inserted: (%lld-%lld)\n", current->lower, current->upper);

    while(current != NULL && step->lower <= current->lower){
        printf("  absorb (%lld-%lld) into (%lld-%lld)?\n", current->lower, current->upper, step->lower, step->upper);
        // Lower is in-between the previous's bounds
        if(current->lower >= step->lower && 
           current->lower <= step->upper) {
            
            printf("    absorbing\n");
            // Replace upper bound only if its upper is larger than previous's upper
            if(current->upper >= step->upper) {
                step->upper = current->upper;
            }
            // Full range is absorbed, so delete the range
            free_range(current);

            // After current has been freed/absorbed, continue from step
            current = step;
        }
        // Shift to next node, unless it's NULL
        if((current = current->next) == NULL || (step = current->prev) == NULL) return;
    }
}

void free_range(range* node){
    if(node == NULL) return;
    
    // printf("node's prev: %x\n", node->prev);
    // printf("node's next: %x\n\n", node->next);

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node);
}

int find_id(range** head, long long id) {
    // Check if DLL is empty
    if (*head == NULL) {
        return 0;
    }

    range* step = *head;
    do
    {
        if (id >= step->lower && id <= step->upper) return 1;


    } while ((step = step->next) != NULL);

    return 0;
    

    // while (step->next != NULL && 
    //       (id < step->lower || 
    //        id > step->upper)) {
    //     step = step->next;
    // }

    // // Return 0 if next node is null, otherwise, ID range found
    // return (!(step->next)? 0 : 1);
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
        printf("(%lld-%lld) ", temp->lower, temp->upper);
        temp = temp->next;
    }
    printf("\n\n");
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