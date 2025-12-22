/* Advent of Code
 * Solution for Day 7: Laboratories, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE* diagram;
    if((diagram = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    char* curr = NULL;        // Current line being analyzed (as char)
    long long* line = NULL;   // Current line after analysis (converted to int to track where the number of worlds a beam may come from)
    long long* prev = NULL;   // Holder for previous line
 
    size_t line_len = 0;      // True line length, ignoring newlines, null terminators, and padding
    size_t line_len_pad;      // Padded line length, for a zero on each end
    long long timelines = 0;  // Total number of different timelines 
    
    // Get the first line and set respective line lengths
    line_len = getline(&curr, &line_len, diagram) - 1;
    line_len_pad = line_len + 2;

    // 0 out prev and line, set "S" to the first beam (coming from the root world)
    prev = calloc(line_len_pad, sizeof(long long));
    line = calloc(line_len_pad, sizeof(long long));
    prev[strcspn(curr, "S") + 1] = 1; // + 1 to start analysis with padding at the beginning

    // Main loop: read in a new line until EOF and analyze for splitters
    // Scan 2 extra characters (newline & null terminator)
    while(fgets(curr, (int)(line_len) + 2, diagram)) {

        int pad = 0;  // For padding, to set the index for accessing prev and line one after the start
        for(int i = 0; i < line_len; ++i) {
            pad = i + 1;

            // Set line to the number of beams coming from above, unless above is a splitter
            line[pad] = (curr[i] == '^') ? 0 : prev[pad];

            // If left is a splitter, add the number of worlds' beams going into that splitter
            // If right is a splitter, add the number of worlds' beams going into that splitter
            if(curr[i - 1] == '^') line[pad] += prev[pad - 1];
            if(curr[i + 1] == '^') line[pad] += prev[pad + 1];
        }

        // Copy finished line into prev for next analysis
        memcpy(prev, line, sizeof(long long) * line_len_pad);
    }
        
    for(int i = 0; i < line_len_pad; ++i) timelines += line[i];

    printf("Timelines: %lld\n", timelines);
    fclose(diagram);
    free(curr);
    free(line);
    free(prev);
    return 0;
}