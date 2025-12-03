# Brandon's Advent of Code Solutions
## 01 Dec 2025: [Secret Entrance](https://adventofcode.com/2025/day/1)

### Notes:
* Time complexity: 
    * O(n), one linear read of the file. Dial is rotated and password is calculated in-line.
* Part 2 took me three days to figure out, but I'm proud to say that I figured it out myself, and I think my solution is relatively elegant. 
    * Steps:
        1. Catch all full rotations first, no matter the direction. Truncated division by 100 should catch them all.
        2. Check to see if the remainder (rotation % 100) crosses 0, unless it started at 0. 
        3. Update dial position (like Part 1).


### References:
* Part 1
    * Various man pages.
    * [W3Schools (File Reading)](https://www.w3schools.com/c/c_files_read.php)
* Part 2
    * [Reddit user dantose's test cases](https://www.reddit.com/r/adventofcode/comments/1pbnu0f/comment/nrrtmqr/)
    * [ResetEra forum user ElFly's solution to Part 2](https://www.resetera.com/threads/advent-of-code-2025-when-you-wish-upon-a.1368820/#:~:text=michael%3F%20a%20million%3F-,SPOILER%3A%20PART%202,-actually%20half%20a)
        * Used solely to check solutions to prevent timing out the site due to excessive answer submissions 