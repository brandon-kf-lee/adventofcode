# Brandon's Advent of Code Solutions
## 05 Dec 2025: [Cafeteria](https://adventofcode.com/2025/day/5)

### Notes:
* Time Complexity: 
    * Part 1
        * O(n^2) to read in ranges and insert them into the linked list in order.
        * O(n^2) to read in IDs and evaluate them (linked list traversal).
    * Part 2
        * O(n^2) to read in ranges, insert them into the linked list in order, and deduplicate them.

* I didn't deduplicate until Part 2 because I didn't initally see the need to. But, since both uses my dll.h functions, Part 1 will benefit from the slight speedup when evaluating IDs.
* I know that an interval tree (like using [this one](https://github.com/ekg/intervaltree) for C++) would be smarter to use and would run faster than a simple DLL, but I wanted to try implementing a simpler solution.

### References:
* Part 1:
    * [Using scanf & fscanf](https://www.geeksforgeeks.org/c/scanf-and-fscanf-in-c/)
    * [Making structs](https://www.w3schools.com/c/c_structs.php)
    * [GeeksforGeeks doubly linked list (dll) implementation](https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/)
    * According to [fscanf documentation](https://stackoverflow.com/questions/13275417/why-scanfd-does-not-consume-n-while-scanfc-does#:~:text=5%20A%20directive%20composed%20of%20white%2Dspace%20character(s)%20is%20executed%20by%20reading%20input%20up%20to%20the%20%EF%AC%81rst%20non%2Dwhite%2Dspace%20character%20(which%20remains%20unread)%2C%20or%20until%20no%20more%20characters%20can%20be%20read.%20The%20directive%20never%20fails.), it cannot determine how many white-space characters were consumed (including newline), so I ignore them there and use fgetc to consume just one (at the end of each range/id)