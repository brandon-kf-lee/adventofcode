/* Advent of Code
 * Solution for Day 5: Cafeteria, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./dll.h"

/* read_range()
 *   Reads a line formatted %lld-%lld into lower and upper
 * Return:
 *   void
 * Parameters: 
 *   long long* lower: Item range lower bound
 *   long long* upper: Item range lower bound
 *   FILE* inventory:  The inventory sheet with proper AOC 2025 Day 5 input formatting
 */
void read_range(long long* lower, long long* upper, FILE* inventory) {
    fscanf(inventory, "%lld-%lld", lower, upper);
    fgetc(inventory); // Ignore the newline at the end of each range 
}

/* read_id()
 *   Reads a line formatted %lld into id
 * Return:
 *   void
 * Parameters: 
 *   long long* id: Item id
 *   FILE* inventory:  The inventory sheet with proper AOC 2025 Day 5 input formatting
 */
void read_id(long long* id, FILE* inventory) {
    fscanf(inventory, "%lld", id);
    fgetc(inventory); // Ignore the newline at the end of each id 
}

int main() {
    FILE* inventory;
    if((inventory = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char test_char;
    long long lower, upper;
    long long id;
    int fresh = 0;
    Range* head = NULL;

    // Build list of ranges
    while(1) {
        
        // If a '\n' newline is detected, must be the end of the ranges section
        if((test_char = fgetc(inventory)) == '\n'){
            break;
        }
        ungetc(test_char, inventory);
        
        read_range(&lower, &upper, inventory);
        insertRange(&head, lower, upper);


    }

    printListForward(head);

    while(1) {
        
        // If EOF is detected (or extraneous '\n'), must be the end of the item section
        if((test_char = fgetc(inventory)) == EOF || test_char == '\n'){
            break;
        }
        ungetc(test_char, inventory);
        
        read_id(&id, inventory);
        printf("%lld: ", id);

        printf("%d \n", findID(&head, id));
        fresh += findID(&head, id);
    }
   
    printf("Fresh ingredients: %d\n", fresh);
    fclose(inventory);
    return 0;
}