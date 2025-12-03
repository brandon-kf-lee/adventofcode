/* Advent of Code
 * Solution for Day 1: Secret Entrance, Part 1
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* combo;
    if((combo = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    // Get each combination line-by-line
    char buffer[10];    
    int dial_pos = 50; 
    int answer = 0;
    while(fgets(buffer, sizeof(buffer), combo) != NULL) {
        
        // If the new combiniation starts with a number, it was most likely truncated due to an insufficient buffer size
        if(isdigit(buffer[0])) {
            fprintf(stderr, "Combination with the values \"%s\" may be longer than %ld characters and truncated! Please update buffer size.\n", buffer, sizeof(buffer));
            return 1;
        }

        // Characters after the first should be the number to rotate by
        int rotation = atoi(&buffer[1]);

        // Add/subtract modulo of rotation, add 100 to remove negatives, modulo 100 again to ensure no overrotation (from the +100)
        if(toupper(buffer[0]) == 'L') {
            dial_pos = ((dial_pos - (rotation % 100)) + 100 ) % 100;
            if(!dial_pos) answer++;
        }
        else if(toupper(buffer[0]) == 'R') {
            dial_pos = ((dial_pos + (rotation % 100)) + 100 ) % 100;
            if(!dial_pos) answer++;
        }
        else {
            fprintf(stderr, "Unknown direction \"%c\".\n", buffer[0]);
            return 1;
        }
    }

    printf("Password: %d\n", answer);

    return 0;
}