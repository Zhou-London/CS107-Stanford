# Lecture 12

Jan 9 Zhouzhou

## Vulnerability, Disclosure

Vulnerability stands for bugs such as use-after-free. These bugs are called undefined behaviour and may cause serious problem. To fix and avoid such vulnerability, users should disclose them as soon as possible and this is called full disclosure. Responsible disclosure is another kind where users contact the maker privately and fix the bug. 

## Partiality

Partiality enables maker to give preferential treatment to some people, such as a membership. Inpartiality is quite the opposite, for that it treats every user equally. There are lots of degree of Partiality such as Partial Cosmopolitanism, Universial Care and Impartial Benevolence. 

## Generics

Generic code is such code can be used repeatly without re-implementation just like we write function and call function in C. Pointers is heavily used for Generic code in C.

## Generic Swap

Write a function that can swap two value. Obviously we need pass pointer to this function so first let's declare the function like this.

    void swap_int(int* a, int* b)

After that we use a temp value to store either variable.

    int tmp = *a;

Then we modify the first value to be the second value.

    *a = *b;

And we modify the second value to be the first value. We are done!

    *b = tmp;

What if we want to swap two strings? As we are modifying the string, we should pass the string as pointers, while string is char* so we need char**

    void swap_string(char** a, char** b)
    {
        char* tmp = *a;
        *a = *b;
        *b = tmp;
    }

These slides are actually teaching you why you need a temp value to swap value. Swaping is quite offen in some sorting algorithms. And we can then write a generic psuedocode

    void swap(pointer to data1, pointer to data2)
    {
        store a copy of either data1 or data2 (let's say data1);
        copy data2 to data1;
        copy temp to data2;
    }

And it is possible to translate such psuedocode to actual C code. If we don't care what exactly the data type is, we can use void*.

    void swap(void* data1ptr, void* data2ptr)

As we don't know the exact data type, we should pass the size of this data to the function.

    void swap(void* data1ptr, void* data2ptr, size_t nbytes)

Now we know the size of data type, so we are able to assign memory chunck for temp value. We can easily have done it using char[] as each character uses one byte.

    char temp[nbytes];

And then temp definitely have enough byte to store either data1 or data2! But how can we assign data1 or data2 to temp? Using assignments?

    temp = *data1ptr; //This is totally wrong as "void" can not be assigned to "char*"

## memcpy

The way we do this is to use memcpy(). memcpy() takes three argument, pointer to data1, pointer to data2 and nbytes. It will copy the first nbytes from data2 to data1. Mention that the argument have to be the pointer to data 1 and data2 rather than the data itself, as the real address of the data should be accessed.

    memcpy(temp, data1ptr, nbytes); //temp = *data1ptr if non-generic

Then copy data2 to data1

    memcpy(data1ptr, data2ptr, nbytes);

Finally copy temp to data2

    memcpy(data2ptr, temp, nbytes);

Let's compose the function

    void swap(void* data1ptr, void* data2ptr, size_t nbytes)
    {
        char temp[nbytes];
        memcpy(temp, data1ptr, nbytes);
        memcpy(data1ptr, data2ptr, nbytes);
        memcpy(data2ptr, temp,nbytes);
    }

Now we can use this function for any data type!

    int x = 2;
    int y = 5;
    swap(&x, &y, sizeof(x));

Note that void* doesn't have any check. So the memory could go wrong. Always be careful with memry manipulation like memcpy().
