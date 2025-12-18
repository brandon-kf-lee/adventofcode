#ifndef DLL_H
#define DLL_H

/* Advent of Code
 * Doubly Linked List Header File
 *   Modified from GeeksforGeeks (https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/)
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>

// Range node definition
typedef struct range {
    struct range* prev;
    struct range* next;
    long long lower;
    long long upper;
} range;

// Create a new range node with given values as data
range* create_range(long long lower, long long upper);

// Insert range in order (based on lower bound)
void insert_range(range** head, long long lower, long long upper);

// Absorb any neighbor's that have overlapping ranges
void deduplicate_range(range* step, range* current);

// Insert a node at the beginning (head)
void insert_head(range** head, long long lower, long long upper);

// Find potential ID within range
int find_id(range** head, long long id);

// Sum the total valid IDs within all the ranges
long long range_total(range* head);

// Delete a range node
void delete_range(range* node);

// Free all dynamic memory allocated by list
void delete_list(range* head);

// Print the list in forward direction
void print_list(range* head);

#endif //DLL_H
