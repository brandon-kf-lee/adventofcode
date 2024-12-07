# Brandon's Advent of Code Solutions
## 01 Dec 2024: [Historian Hysteria](https://adventofcode.com/2024/day/1)

### Notes:

### References:
* Although I didn't use this in my implementation, I found this [very, very elegant way](https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input#:~:text=functions%2C%20strcspn()%3A-,buffer%5Bstrcspn(buffer%2C%20%22%5Cn%22)%5D%20%3D%200%3B,-If%20you%20want) to strip a newline character from a string buffer: `buffer[strcspn(buffer, "\n")] = 0;` It searches through buffer and finds the index of the first instance of the character `"\n"`.
* Refamiliarised myself with how insertion sorting worked and made my own insert_sequential() function.
* [man7 (fopen)](https://man7.org/linux/man-pages/man3/fopen.3.html)
* [cppreference (fgets)](https://en.cppreference.com/w/c/io/fgets)
* [geeksforgeeks (strok + examples)](https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/)
* [geeksforgeeks (count number of lines in a file)](https://www.geeksforgeeks.org/c-program-count-number-lines-file/)