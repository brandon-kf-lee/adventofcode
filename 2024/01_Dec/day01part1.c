/* Advent of Code
 * Solution for Day 1 Part 1: Historian Hysteria
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int max_line = 20; /* The maximum number of characters to read in per line */
const char* delimiter = "   "; /* The delimiter that separates the two location ID pairs */

void insert_sequential(int* arr, int val, int size, int num_sorted);

int main(int argc, char* argv[]){

    /* Error check input file name */
    if(argc < 2){
        fprintf(stderr, "Missing input file. \nUsage: ./day01 <input text file name>\n");
        exit(EXIT_FAILURE);
    }

    /* Open file into input, w/ error checking */
    FILE* input;
    if((input = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /* Read through the file once to determine how many location ID pairs there are */
    int num_pairs = 1; /* Start at 1 in case the last pair does not have a newline */
    char c;
    while((c = (char)getc(input)) != EOF){
        if(c == '\n'){
            ++num_pairs;
        }
    }
    rewind(input);

    /* Initialise a zero list after determining the number of pairs */
    int left_list[num_pairs];
    int right_list[num_pairs];
    memset(left_list, -1, num_pairs * sizeof(int));
    memset(right_list, -1, num_pairs * sizeof(int));

    /* Read through the file and populate the left and right lists, sorting as you go */
    char line[max_line];
    for(int lines_read = 0; lines_read < num_pairs; ++lines_read){
        fgets(line, max_line, input);
        insert_sequential(left_list, atoi(strtok(line, "   ")), num_pairs, lines_read);
        insert_sequential(right_list, atoi(strtok(NULL, "\n")), num_pairs, lines_read);
    }

    int tot_distance = 0;
    for(int i = 0; i < num_pairs; ++i){
        tot_distance += abs(left_list[i] - right_list[i]);
        printf("left: %d, right: %d\n", left_list[i], right_list[i]);
    }
    printf("Total distance: %d\n", tot_distance);

    exit(EXIT_SUCCESS);
}

void insert_sequential(int* arr, int val, int size, int num_sorted){    
    /* Find the location (cur_pos) to insert new value */
    int cur_pos;
    for(cur_pos = 0; cur_pos < size; ++cur_pos){
        /* If the new value is smaller than what's at the current position, shift everything larger rightward to make room for the new value */
        if(val < arr[cur_pos]){
            // printf("val < arr[cur_pos], shifting.\n");
            /* Shift everything rightward from cur_pos to the end of the sorted array */
            for(int shamt = 0; shamt < num_sorted - cur_pos; ++shamt){
                arr[num_sorted - shamt] = arr[num_sorted - shamt - 1];
            }
            break;
        }
        /* If at the end of the sorted array, it must be the largest number */
        else if(arr[cur_pos] == -1){
            // printf("Inserting at end.\n");
            break;
        }
    }
    arr[cur_pos] = val;


    // printf("Array now: ");
    // for(int k = 0; k < size; ++k){
    //     printf("%d, ", arr[k]);
    // }
    // printf("\n");
    return;
}