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

// defining a range node
typedef struct Range {
    struct Range* prev;
    struct Range* next;
    long long lower;
    long long upper;
} Range;

// TODO: replace all names with underscore case

// Function to create a new node with given values as data
Range* createRange(long long lower, long long upper);

void insertRange(Range** head, long long lower, long long upper);

int findID(Range** head, long long id);

// Function to insert a node at the beginning
void insertAtBeginning(Range** head, long long lower, long long upper);

// Function to insert a node at the end
void insertAtEnd(Range** head, long long lower, long long upper);

// Function to insert a node at a specified position
void insertAtPosition(Range** head, long long lower, long long upper, int position);

// Function to delete a node from the beginning
void deleteAtBeginning(Range** head);

// Function to delete a node from the end
void deleteAtEnd(Range** head);

// Function to delete a node from a specified position
void deleteAtPosition(Range** head, int position);

// Function to print the list in forward direction
void printListForward(Range* head);

// Function to print the list in reverse direction
void printListReverse(Range* head);

#endif //DLL_H
