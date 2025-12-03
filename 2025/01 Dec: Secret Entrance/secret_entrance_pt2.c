/* Advent of Code
 * Solution for Day 1: Secret Entrance, Part 2
 * Brandon Lee
 * brandon.kf.lee@gmail.com
 */ 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    FILE* combo;
    if((combo = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "Input does not exist/cannot open! Insert an input file called input.txt in the same directory.\n");
        return 1;
    }

    // Get and calculate each combination line-by-line
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

        /* Steps: 
           1. Catch all full rotations first, no matter the direction. Truncated division by 100 should catch them all.
           2. Check to see if the remainder (rotation % 100) crosses 0, unless it started at 0. 
           3. Update dial position (like Part 1).
        */

        answer += rotation / 100;
        if(toupper(buffer[0]) == 'L') {
            if((dial_pos - (rotation % 100) <= 0) && dial_pos != 0) {                
                answer++;
            }
            dial_pos = ((dial_pos - (rotation % 100)) + 100 ) % 100;
            printf("Rotate L%d, new position: %d\n", rotation, dial_pos);
        }

        else if(toupper(buffer[0]) == 'R') {
            if((dial_pos + (rotation) % 100) >= 100 && dial_pos != 0) {
                answer++;
            }
            dial_pos = ((dial_pos + (rotation % 100)) + 100 ) % 100;
            printf("Rotate R%d, new position: %d\n", rotation, dial_pos);
        }

        else {
            fprintf(stderr, "Unknown direction \"%c\".\n", buffer[0]);
            return 1;
        }

    }
    printf("Password: %d\n", answer);

    return 0;
}