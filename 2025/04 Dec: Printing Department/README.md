# Brandon's Advent of Code Solutions
## 04 Dec 2025: [Printing Department](https://adventofcode.com/2025/day/4)

### Notes:
* Time Complexity: 
    * O(n^2). Read the file one line at a time, and within each line read evaluate all of a given roll of paper's neighbors.
* Part 1: 
    * The file reading works on a rolling basis. I start it with an implied row of '.'s at the top, the first row at the middle, and the second row at the bottom. As each neighborhood gets evaluated, the middle and bottom rows get shifted up, a new line is read into the bottom, and the process is repeated until EOF. In the iteration before EOF, the bottom row is replaced with an implied row of '.'s.

    * For the implementation of the rolling read's shifting, I decided to use memcpy instead of reading the files again. If I understand it correctly, since the data is already in memory, it would be faster to move it within memory than to reorient using fseek and read the same line again using fread.

    * Padding of '.' is added around the border of the diagram to ensure no out-of-bound accesses when analyzing neighbors.

* Part 2:
    * Because the solution updates the row in the input file after it analyzes it, you can see the rolls of paper being removed in each iteration. As long as you can find a way to view the input file being changed as the program runs, that is.

### References:
* Part 1:
    * [Different ways to read files](https://stackoverflow.com/questions/34695410/is-there-a-good-alternative-to-fgets)
    
