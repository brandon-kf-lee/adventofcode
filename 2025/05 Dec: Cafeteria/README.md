# Brandon's Advent of Code Solutions
## 05 Dec 2025: [Cafeteria](https://adventofcode.com/2025/day/5)

### Notes:
* Time Complexity: 
    * Part 1
        * O(n^2) to read in ranges and insert them into the linked list in order.
        * O(n) to evaluate IDs.

* To save time and reduce code complexity, I'm not going to deduplicate the ranges. The program works just as well without it.
* I know that an interval tree (like using [this one](https://github.com/ekg/intervaltree) for C++) would be smarter to use and would run faster than a simple DLL, but I wanted to try implementing a simpler solution.

### References:
* Part 1:
    * [Using scanf & fscanf](https://www.geeksforgeeks.org/c/scanf-and-fscanf-in-c/)
    * [Making structs](https://www.w3schools.com/c/c_structs.php)
    * [GeeksforGeeks doubly linked list (dll) implementation](https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/)