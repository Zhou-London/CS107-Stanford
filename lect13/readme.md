# Lect13 Function Pointers

Jan 9 Zhouzhou

## Void* Pitfalls

void* Pitfalls stand for the memory manipulation with wrong bytes. For instance, you copy a int to a int but only with 2bytes rather than 4 bytes, which would cause strange value.

    int x = 0xffffffff;
    int y = 0xeeeeeeee;
    swap(&x, &y, sizeof(short)); //short rather than long

    //Now x is 0xffffeeee! y is 0xeeeeffff

## memset()

memset is a function that sets a specified number of bytes starting at an address to a certain value. The second argument is a byte and can be of any value. The function will set the first n bytes of first argument to be the value of second argument.

    int counts[5];
    memset(counts, 0 ,3);
    memset(counts + 3, 0xff, 4);

## swap end

How can we write a function that swap the head and end of an array? Note that an array of int is actually a pointer to int. As we have pointer, we can easily manipulate it.

    void swap_ends_int(int *arr, size_t nelems)
    {
        int tmp = arr[0];
        arr[0] = arr[nelems - 1];
        arr[nelems - 1] = tmp;
    }

Remember our swap() function? we can use that, but the parameter should be change. We need the pointer to the head and to the end and arr is originally a pointer to the head. So we can add nelems - 1 to get the pointer to the end.

    void swap_ends_int(int *arr, size_t nelems)
    {
        swap(arr, arr + nelems - 1, sizeof(*arr));
    }

But how can we modify it to be generic style? Like this? Definitely NOT! As we passed arr as a "void *", we can not use sizeof to get its bytes. Secondly, pointer arithmetic can not be applied on void*, so we can not say arr + nelems - 1 for "void *arr" (for int*, each "+1" stands for 8 bytes, for char*, each "+1" stands for 1 byte, for void*, C can not do that)

    void swap_ends(void *arr, size_t nelems)
    {
        swap(arr, arr + nelems - 1, sizeof(*arr));
    }

So let's modify it, we need to know the bytes of the a single element in arr and we can just add one more parameter. But the problem of pointer arithmetic is not yet sloved.

    void swap_ends(void *arr, size_t nelems, size_t nbytes)
    {
        swap(arr, arr + nelems - 1, nbytes);
    }

So if C can not determine how many bytes should it move for a void*, let's determine it for him! If you passed a int, each step should be sizeof(int), if short, then sizeof(short)...But hey, arr is still a void*, which means pointer arithmetic is still not allowed even if you handle the bytes offset on your own...

    void swap_ends(void *arr, size_t nelems, size_t nbytes)
    {
        swap(arr, arr + (nelems - 1) * nbytes, nbytes);
    }

As you handle the bytes offset on your own, rather than let C depends the pointer arithmetic, you can just tell C not to worry about the void*, just treat it as bytes. So which data type use 1 byte for each element? Of course char! Let's cast arr into char* so C will no longer error anymore!

    void swap_ends(void *arr, size_t nelems, size_t nbytes)
    {
        swap(arr, (char *)arr + (nelems - 1) * nbytes, nbytes);
    }

## Bubble sort

I bet you have learned algorithm so here is a simple code for Bubble sort of Integer

    void bubble_sort_int(int* arr, size_t n)
    {
        while(true){
            bool swapped = false;
            for(size_t i = 1; i < n; i++){
                if(arr[i - 1] > arr[i]){
                    swapped = true;
                    int tmp = arr[i - 1];
                    arr[i-1] = arr[i];
                    arr[i] = tmp;
                }
            }
            if(!swapped){
                return;
            }
        }
    }

Let's try to modify this function, so that it can sort the array to be either ascending or descending order. The key between ascending and descending is how we determine that these two elements should be swapped. So we can first write this as a function. Now we use should_swap to determine whether elements should be swapped, but we haven't implemented this function, which means this function should be either declared somewhere else or...this function is passed in as a parameter!

    if(should_swap(arr[i - 1], arr[i])){
        swapped = true;
        int tmp = arr[i - 1];
        arr[i-1] = arr[i];
        arr[i] = tmp;
    }

## Function Pointers

We need Function Pointers to pass a function as a parameter. A function pointer can be declared like this. "bool" stands for the return type, "(int, int)" for it takes two int as parameter.

    bool (*should_swap)(int, int)

And here is the general declartion

    [return type] (*[name])([parameters])

Now we can implement the bubble sort function in this way

    //somewhere outside the main function...
    void bubble_sort_int(int *arr, size_t n, bool (*should_swap)(int, int)){
        while(true){
            bool swapped = false;
            for(size_t i = 1; i < n; i++){
                if(should_swap(arr[i - 1], arr[i])){
                    int tmp = arr[i-1];
                    arr[i-1] = arr[i];
                    arr[i] = tmp;
                    swapped = true;
                }
            }
            if(!swapped){
                return;
            }
        }
    }

To use this function, we should pass in another function that can determine "whether you should swap" as a parameter.

    //somewhere...
    bool sort_ascending(int f, int s)
    {
        return f > s;
    }

    //inside main function
    int num[] = {2,4,5,3,7,423,64};
    bubble_sort_int(num, sizeof(num)/sizeof(num[0]),sort_ascending);

## Pass function vs Pass variable

Passing a variable as a parameter allows us to pass data around our program, while passing a function as a parameter allows us to pass logic around our program. In generic program, we can ask caller to pass in the logic he wants as we don't exactly know what he wants.

## Generic Bubble Sort

Now let's try to make the bubble_sort_int to be generic. We need to modify the pointer type to be void* while passing the bytes of one element as a new parameter. I know you have mentioned that in should_swap we still use "(int ,int)" which is not generic. We will get back to it later.

    void bubble_sort(void* arr, size_t n, size_t elem_size_bytes, bool (*should_swap)(int, int))

Now just focus on the swap part. How can we swap void* values? Well of course we can use the swap() function we wrote before. But swap() function will need pointer, which means you need to use pointer arithmetic to access to nth element, while pointer arithmetic is not working for void* values.

    swap(arr + i - 1, arr + i, elem_size_bytes); //Error, no pointer arithmetic for void*

## Locating nth element

As we mentioned in last lecture the way to locate the last element

    void swap_ends(void* arr, size_t nelems, size_t elem_bytes){
        swap(arr, (char *)arr + (nelems - 1) * elem_bytes, elem_bytes);
    }

So if we want to access ith value, just simply modify "(nelems - 1)" to be "i"

    void ith_elem = (char *)arr + i * elem_bytes;

Now we can improve the bubble sort function and everything is working perfectly except the should_swap function!

    void bubble_sort(void* arr, size_t n, size_t elem_size_bytes, bool (*should_swap)(int,int)){
        while(true){
            bool swapped = false;
            for(size_t i = 1; i < n; i++){
                void *p_prev_elem = (char *)arr + (i - 1) * elem_bytes;
                void *p_curr_elem = (char *)arr + (i) * elem_bytes;
                if(should_swap(*p_prev_elem, *p_curr_elem)){
                    swap(p_prev_elem, p_curr_elem, elem_size_bytes);
                    swapped = true;
                }
            }
            if(!swapped){
                return;
            }
        }
    }

## Final

We can simply modify the declartion of should_swap to

    bool (*should_swap)(void *, void *)

So now, function should_swap() must take pointers rather than actual values

    if(should_swap(p_prev_elem, p_curr_elem))

And now we are done! Everything works and this is generic functions and function pointers! Amazing journey! Let's recap the whole function

    void bubble_sort(void* arr, size_t n, size_t elem_size_bytes, bool (*should_swap)(void *,void *)){
        while(true){
            bool swapped = false;
            for(size_t i = 1; i < n; i++){
                void *p_prev_elem = (char *)arr + (i - 1) * elem_bytes;
                void *p_curr_elem = (char *)arr + (i) * elem_bytes;
                if(should_swap(p_prev_elem, p_curr_elem)){
                    swap(p_prev_elem, p_curr_elem, elem_size_bytes);
                    swapped = true;
                }
            }
            if(!swapped){
                return;
            }
        }
    }