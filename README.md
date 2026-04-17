# Agin

## Overview
Agin is a comprehensive string manipulation library for the C programming language. It provides a dynamic string structure and a wide variety of functions to simplify text processing tasks. C developers can use Agin for memory management and utility functions that expand upon the standard library.

## Features
The library includes numerous functions for string manipulation. Core capabilities include:
* Creation and memory management
* Appending and inserting characters or strings
* Examining string content and properties
* Case conversion and formatting
* Trimming and replacing text
* Slicing and concatenating strings

## Function Reference

### Memory Management
* `create`: Creates a new string object.
* `destroy`: Frees the memory of one or more string objects.
* `copyTo`: Copies character arrays to a string.

### Modification
* `insertChars`, `insertCharsAt`: Inserts character arrays.
* `insertChar`: Appends a single character.
* `insertString`, `insertStringAt`: Inserts another string object.
* `pop`: Removes and returns the last character.
* `leftTrim`, `rightTrim`, `trim`: Removes whitespace from the string.
* `capitalize`, `toLowerCase`, `toUpperCase`: Alters the case of the string.
* `reverse`: Reverses the characters in the string.
* `replace`, `replaceAll`, `replaceCharAtIndex`: Replaces characters or substrings.
* `concat`, `join`: Combines multiple string objects.
* `zfill`: Pads the string with zeros.
* `repeat`: Repeats characters a specified number of times.

### Inspection
* `println`: Prints the string with a newline.
* `lengthOf`: Returns the length of the string.
* `isEmpty`: Checks if the string has no characters.
* `contains`: Checks if the string includes a specific substring.
* `isLowerCased`, `isUpperCased`: Checks the case of the string.
* `isEqual`: Compares two string objects.
* `startsWith`, `endsWith`: Checks the boundaries of the string.
* `indexOf`, `lastIndexOf`, `findChar`: Locates characters within the string.
* `countOccurence`, `countChars`: Counts substrings or characters.
* `charAt`: Returns the character at a specific index.
* `isWhiteSpace`: Identifies whitespace characters.

### Utility
* `slice`: Extracts a portion of the string.
* `toNumber`: Converts the string to a numeric value.
* `getASCIILetters`, `getPunctuations`: Generates specific character sets.

## Disadvantages
* The main disadvantage of this library is that its not memory efficient and uses optimized algorithms
* The library is built around traditional and some modified(for strings) algorithms 


## Usage
Include the header file in your C program:

```c
#include "src/agin.h"

int main() {
    String *greet = create("Hello World");
    println(greet);
    destroy(1, greet);
    return 0;
}
```

## Compilation
Compile your C files along with the library source files.

```sh
gcc main.c src/agin.c -o program
```
