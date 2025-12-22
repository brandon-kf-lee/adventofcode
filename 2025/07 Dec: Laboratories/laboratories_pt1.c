/* Advent of Code
 * Solution for Day 7: Laboratories, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE* diagram;
    if((diagram = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char* prev = NULL;    // Previous line (to track where the beam is coming from)
    char* line = NULL;    // Line being analyzed
    size_t line_len = 0;  // True line length, ignoring newlines and null terminators
    int split_n = 0;      // Num times a beam hits a splitter
    
    // Get the first line and strip newline
    line_len = getline(&line, &line_len, diagram) - 1;
    line[strcspn(line, "\n")] = 0;

    // Set space for prev, copy the current line in, and shrink line to fit exact size of a one line
    prev = malloc(line_len);
    strncpy(prev, line, line_len);
    if(reallocarray(line, line_len, sizeof(char)) == NULL) {
        fprintf(stderr, "Unable to shrink 'line'.\n");
        return 1;
    }

    // Main loop: read in a new line until EOF and analyze for splitters
    // Scan 2 extra characters (newline & null terminator)
    while(fgets(line, (int)(line_len) + 2, diagram)) {
        line[strcspn(line, "\n")] = 0;

        for(int i = 0; i < line_len; ++i) {
            // Analyzing the previous line
            switch(prev[i]) {
                // If 'S', below must be a beam
                case 'S':
                    line[i] = '|';
                    break;
                
                // If '|', below must be another beam, unless it is a splitter
                case '|':
                    if(prev[i] == '|' && line[i] != '^') {
                        line[i] = '|';
                    }
                    break;

            }

            // Analyzing the current line
            switch(line[i]) {
                // If the splitter has a beam coming into it, generate beams to both sides
                case '^':
                    if(prev[i] == '|') {
                        line[i + 1] = line[i - 1] = '|';
                        ++split_n;
                    }
                    break;
            }
        }
        strncpy(prev, line, line_len);
    }
        
    printf("Split beam #: %d\n", split_n);
    fclose(diagram);
    free(prev);
    free(line);
    return 0;
}