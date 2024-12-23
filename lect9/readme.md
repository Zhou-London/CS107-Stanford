# Lecture 9 Notes

Dec 23 2024

## Read-Only String

When declaring strings using "=", the memory is read only, for it is allocated from data segement.

    char *myString = "Hello world";

Such string is not allowed to modify

    myString[0] = 'h'; //error!

    strcpy(myString, "hi"); //error!

## char[] and char*

char[] allocates chuncks of memory, hence char[] is not allowed to assign value.

char* returns a pointer to char, hence char* is allowed to assign value.

## Double pointer

char** is a pointer to string. char*[] is a pointer to a list of string.

When you need to modify a char*, use char** as parameter to that function.
