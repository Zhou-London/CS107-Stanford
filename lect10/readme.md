# Lecture 10 Notes

Dec 23 2024

## Memory Chunk of Array

Array is a memory chunck, memory chunck is not allowed to be assigned to each other

    int a1 = {1,2,3};
    int a2 = {1,2,3,4};
    
    a1 = a2 //error!

## Array as Parameter


When Array is declared, you can use sizeof() to get the size of array, i.e. how many elements does it have.


When Array is passed into a function as a parameter. The value passed to the function is actually a pointer pointed to the first element. Hence using sizeof() on it only returns the size of this pointer, which is 8 byte.


Therefore, sizeof() can not return the size of an array as parameter.

## Array and Pointers


Array becomes Pointers when array is passed as parameters.


As Array is just a memory chunck, &arr doesn't mean anything, while &ptr returns the address of the pointer.

## Pointers Offset

Pointer stores the memory address, the address can be modified

    int* num = {1,2,3}
    //num points to the first element
    //num + 1 points to the second element

opertion "[]" is actually an offset

    char* str = "...";
    str[0] //*(str + 0)
    str[1] //*(str + 1)

## Stack

Stack is a memroy segment. It stores functions' local variable. Stack grow bigger when new function calls. Every time a new function is called, a new chunck is allocated for that funcion. Every time a function is finished, its memroy chunck is disallocated.


When new chunck is allocated, the Stack grows downwards. When that chunck is disallocated, the Stack shrinks upwards.


Recursion takes place on Stack too. Each general cases will create one more chunck.


While "chunck" is not a formal name, "Stack Frame" stands for these "chuncks"


Stack overflow takes place when there are too many stack frame growing downwards so that it achieves other segments of memory rather than Stack segment.

## Create String on Stack

Every stack frame will be disallocated once the function is finished. Hence, if you declare a string on one stack frame, that string will be disallocated too. And that string will not be available to the higher stack frame.


One way to solve this problem, is to declare that string in main function, then the string will be allocated in main function's frame, which is the last frame to be disallocated. But this is not always possible because you have to know the length of the string first, so that you can use char[] to assign it.

## Heap

Heap is another segment of memory which stores the value and won't clean the function frame automatically. In the other word, it is your responsibility to clean the function frame. 


Heap grows upwards and shrinks downwards, which is quite the opposite to the stack.


The heap is dynamic memory – memory that can be allocated, resized, and freed during program
runtime.

## malloc

Everytime and anywhere malloc is called, it assigns a chunck of memory on Heap for that data.


Even if the function frame on Stack is disallocated, the data on Heap is still available. Using malloc and Heap we are able to create data that will not be disallocated automatically.


Use a pointer to store the address returned by malloc.


Malloc’s argument is the number of bytes to allocate, not # of elements.


Arrays other than strings don’t have special terminating elements/values.

## calloc

Comparing with malloc, calloc will also set every data to 0.

    int *scores = calloc(20, sizeof(int));

    //Just the same as
    int *scores = malloc(20 * sizeof(int));
    for(int i = 0; i < 20; i++){

## strdup

strdup() provides a easy way to allocate memory for a string on Heap.

    char* h = strdup("Hello World!");

    //Just the same as malloc + strcpy
