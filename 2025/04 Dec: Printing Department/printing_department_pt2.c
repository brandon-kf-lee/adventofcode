/* Advent of Code
 * Solution for Day 4: Printing Department, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <string.h>

#define WIDTH 138                  // Width of a row of the diagram
#define PADDED_WIDTH (WIDTH + 2)   // Width after padding the row with a '.' on both ends

/* read_and_pad()
 *   Reads a line of WIDTH characters from diagram into row and pads the beginning and 
 *   end of the array with '.'  * Return: 
 * Return:
 *   void
 * Parameters: 
 *   char row[PADDED_WIDTH]: The row to write into
 *   FILE* diagram:          The diagram with proper AOC 2025 Day 4 input formatting
 */
void read_and_pad(char row[PADDED_WIDTH], FILE* diagram) {
    fread(&row[1], sizeof(char), WIDTH, diagram);
    fgetc(diagram); // Read and ignore the newline
    row[0] = row[PADDED_WIDTH - 1] = '.';
}

int main() {
    FILE* diagram;
    if((diagram = fopen("input.txt", "r+")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    int center = 1;                 // The center of the rows array to analyze neighbors from
    int neighborhood = 3;           // How many neighborhoods (including center) to analyze
    char test_char;                 // Test to see if EOF has been reached
    int rolls_removed = 0;          // Rolls removed in one run-through
    int total_rolls = 0;            // Total number of rolls removed
    char rows[3][PADDED_WIDTH];     // Any 3 of the input rows at a time
    memset(rows, '0', sizeof(char) * neighborhood * PADDED_WIDTH);
    
    char removed_rolls[WIDTH + 1];  // Holder for the rows with accessible rolls removed (+1 to accomodate a newline)
    int rolls = 0;                  // Holder for the number of roll neighbors 
    int cur_pos;                    // The current cursor position reading the diagram
    int analyzed = 0;               // The number bytes in the diagram analyzed

    // Set first row to have implicit '.'s and grab second row to start rolling row read
    memset(rows[0], '.', sizeof(char) * PADDED_WIDTH);
    read_and_pad(rows[1], diagram);

    while(1) {
        
        // If end of file, add an implicit row of '.'s to the end
        if((test_char = fgetc(diagram)) == EOF) {
            memset(rows[2], '.', sizeof(char) * PADDED_WIDTH);
        }
        // Put back the read character and read in the next row
        else {
            ungetc(test_char, diagram);
            read_and_pad(rows[2], diagram);
        }
        
        // Evaluate each set of neighbors from the center
        for(int col = 1; col < WIDTH + 1; ++col) {
            removed_rolls[col - 1] = rows[center][col];
            if(rows[center][col] == '@') {
                // Add 1 to rolls if one of the neighbors is a '@'
                rolls = (1 ? (rows[center - 1][col - 1] == '@') : 0) +  // Top left
                        (1 ? (rows[center - 1][col]     == '@') : 0) +  // Top
                        (1 ? (rows[center - 1][col + 1] == '@') : 0) +  // Top right

                        (1 ? (rows[center]    [col - 1] == '@') : 0) +  // Left
                        (1 ? (rows[center]    [col + 1] == '@') : 0) +  // Right

                        (1 ? (rows[center + 1][col - 1] == '@') : 0) +  // Bottom left
                        (1 ? (rows[center + 1][col]     == '@') : 0) +  // Bottom
                        (1 ? (rows[center + 1][col + 1] == '@') : 0);   // Bottom right
                
                if(rolls < 4) {
                    rolls_removed += 1;
                    removed_rolls[col - 1] = '.'; // Remove the roll for the next iteration
                }
            }
        }
        removed_rolls[WIDTH] = '\n';

        /* Replace the rows in the working document as its other rows are being analyzed
           Cursor should not need to seek far since the row being replaced is just above the current row
           1. Save the current cursor position
           2. Seek to where was last overwritten
           3. Write there and save the offset/bytes written to return to later
           4. Return to the current position
        */ 
        cur_pos = ftell(diagram);
        fseek(diagram, analyzed, SEEK_SET);
        analyzed += fwrite(removed_rolls, sizeof(char), sizeof(removed_rolls), diagram);
        fseek(diagram, cur_pos, SEEK_SET);
        
        // Move the bottom two rows up one to prepare for next line in
        memcpy(rows[0], rows[1], PADDED_WIDTH);
        memcpy(rows[1], rows[2], PADDED_WIDTH);

        // If EOF is reached
        if((test_char == EOF)) {
            // If no rolls were removed in this turn, analysis finished
            if(rolls_removed == 0) break;
            
            // Reset for next iteration: add up rolls removed, set cursor to the top, and pre-set the first two rows
            total_rolls += rolls_removed;
            rolls_removed = 0;
            fflush(diagram);
            fseek(diagram, 0, SEEK_SET);
            analyzed = 0;

            memset(rows[0], '.', sizeof(char) * PADDED_WIDTH);
            read_and_pad(rows[1], diagram);
        }
    }   

    printf("Total rolls: %d\n", total_rolls);
    fclose(diagram);
    return 0;
}