/* Advent of Code
 * Solution for Day 5: Cafeteria, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dll.h"

int main() {
    FILE* inventory;
    if((inventory = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char test_char;
    long long lower, upper, id;
    int total_fresh = 0;
    range* head = NULL;

    // Build list of ranges
    while(1) {
        // If a '\n' newline is detected, must be the end of the ranges section
        if((test_char = fgetc(inventory)) == '\n'){
            break;
        }
        ungetc(test_char, inventory);
        
        fscanf(inventory, "%lld-%lld", &lower, &upper);
        fgetc(inventory); // Ignore the newline at the end of each range 
        insert_range(&head, lower, upper);
        print_list(head);
    }

    // Evaluate IDs
    while(1) {
        // If EOF is detected (or extraneous '\n'), must be the end of the item section
        if((test_char = fgetc(inventory)) == EOF || test_char == '\n'){
            break;
        }
        ungetc(test_char, inventory);
        
        fscanf(inventory, "%lld", &id);
        fgetc(inventory); // Ignore the newline at the end of each id 
        total_fresh += find_id(&head, id);

        printf("%lld: %d\n", id, find_id(&head, id));
    }
   
    printf("Fresh ingredients: %d\n", total_fresh);
    printf("Total fresh ingredients %lld\n", range_total(head));
    fclose(inventory);
    delete_list(head);
    return 0;
}