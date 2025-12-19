# Brandon's Advent of Code Solutions
## 06 Dec 2025: [Trash Compactor](https://adventofcode.com/2025/day/6)

### Notes:
* Time Complexity: 
    * Part 1:
        * O(n^2) to read in and sort problems (# of problems x # of operands).
        * O(n) to evaluate all of the problems.
    * Part 2:
        * O(n) to read in each line of the homework file.
        * O(n^2) to parse through every line, build up the vertical operands, and evaluate all the problems.

* I thought about rotating the entire text file by 90 degrees to read in, but I couldn't think of a simple way to do that.

* Part 2:
    * I read in every single line first so I don't have to operate on the file and could just operate within memory. I then work in columns, building up the operands of a problem set digit by digit. When the digit is built, it is added/multiplied to the problem's answer. If it encounters a column of only spaces, it is a question delimiter and the loop is reset.

### References:
* Part 2:
    * [The defaut size (# of bytes) getline allocates](https://stackoverflow.com/questions/20036074/length-of-line-in-getline-function-c)
    * [My favorite way to strip newlines off of the end of strings](https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input#:~:text=Copy-,buffer%5Bstrcspn(buffer%2C%20%22%5Cn%22)%5D%20%3D%200%3B,-If%20you%20want)