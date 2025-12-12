# Brandon's Advent of Code Solutions
## 02 Dec 2025: [Gift Shop](https://adventofcode.com/2025/day/2)

### Notes:
* Time Complexity: 
    * Part 1:
        * O(n) or O(n^2), though I'm not sure as its not as clear cut. I do a linear read through the text file, stopping to analyze the range after reaching a comma. There is another while loop in it, but it has a fixed bound that goes up as the numbers get bigger.
    * Part 2: 
        * O(n^4). I read w characters, then loop for x number of number length changes, then y number of possible patterns, then z number of possible patterns until the upper range is reached
* Through sheer refusal to use a string buffer, my girlfriend and I figured out a way to read in the input text using only integers and generate invalid IDs using pure math. Seen in both parts of this day's challenges.

* Part 2:
    * The undelying principles used in Part 1 & 2 are similar, but there may be small differences in Part 2 (variable names, organization, etc) due to learning from my mistakes from Part 1.
    * I finally use regex when detecting if duplicate IDs have been generated. This does use a string (char*), but my reasoning is that since I already have the generated IDs to check, I'm not unnecessarily checking every single ID in the range.


### References:
* Part 1:
    * Discussed a mathematical method to read integers from a file without a buffer with my girlfriend ([megankabe@gmail.com](mailto:megankabe@gmail.com)) <3 
    * [A very interesting way to get the number of digits a number without turning it into a string](https://stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c#:~:text=snprintf(0%2C0%2C%22%25%2Bd%22%2Cn)%2D1)
* Part 2:
    * [POSIX Regular Expressions in C](https://www.geeksforgeeks.org/c/regular-expressions-in-c/)
    * [A regex suggestion that got me close to the one I used](https://stackoverflow.com/questions/37156933/regex-finding-duplicate-numeric-values-in-a-text-file#:~:text=Try%20this%3A-,%5Cb(%5Cd%2B)%5Cb.*%5Cb%5C1%5Cb,-It%27ll%20find%20a)
    * [How to match an entire string in regex](https://stackoverflow.com/questions/4123455/how-do-i-match-an-entire-string-with-a-regex#:~:text=Copy-,%5ERed%20October%24,-By%20default%2C%20regular)
    * [Check three or more consecutive identical characters or numbers](https://www.geeksforgeeks.org/dsa/check-three-or-more-consecutive-identical-characters-or-numbers/)
    * [Regex tester](regex101.com)
    * [Problematic regular expressions (GNU grep)](https://www.gnu.org/software/grep/manual/html_node/Problematic-Expressions.html)


