# Lecture 11 Notes

Dec 23

## free

It is our responsibility to disallocate the memory on Heap as computer will not handle it.

    int* ptr = 1;
    free(ptr);

However, free a pointer doesn't mean "destroy this pointer". It is actually set this pointer point to nowhere. You can again let it point to something else!

Hence, we can say free a memory chunck rather than free a pointer, which means, if you have two pointers points to the same memory chunck. You just need to free either pointer.

Additionally, you must free the memory chunck from the begin.

    free(ptr) //fine
    free(ptr+1) //Oh no!

You should always remeber to free the memory chunck on Heap after you think you are done with that data. It is quite often you need to use malloc in one function and then free the memory chunck in the main.
