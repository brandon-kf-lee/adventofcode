# Brandon's Advent of Code Solutions
## 03 Dec 2025: [Lobby](https://adventofcode.com/2025/day/3)

### Notes:
* Time Complexity: 
    * Part 1:
        * O(n). Reading the file one character at a time with no loops looking backwards.
    * Part 2:
        * O(n^2). Read the file one character at a time, and look back to the beginning of the current bank to see if a digit can be replaced.
* This is my fastest finish by far, <24 hours. I attribute my quick finish to an easier prompt and planning out the algorithm on paper before coding. 

* Part 2: This code is more general than Part 1; you can change the values of the define statements at the top to get to the same answer in Part 1. The main idea is that reading from left to right, if there is a new battery with a joltage that is bigger than the previous battery in its place, the joltage it contributes to the bank's total joltage must also be bigger than any number that might come after it. Up to the limit where there are batteries left to turn on.

### References:
* Part 1:
    * [How to properly use memset on an integer array](https://stackoverflow.com/questions/17288859/using-memset-for-integer-array-in-c)
    