# Generic Data structures and Algorithms

The goal of this library is to implement some of the more popular data structures and algorithms is a **simple and clean** way, while also making them **generic**.

## Languages
For now the only targeted language is **C**. Might be implemented in C++ the future, but for the most part this targets C, as it doesn't have any standard DSA.

## How to use
All you have to do is include the header files of the things you want.

## How it works
In every data structure, *the size of the elements is stored*. Using that information + void pointers, pretty much everything is possible. Sadly there is no way to store the type directly (or at least I haven't found a way), so functions that return the value of an element will require you to give them the type (these are not really functions, but function-like macros, that typecast the result to your desired type).