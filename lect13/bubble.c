/* CS107
 * Lecture Example: Generics9
 *
 * This file shows how to implement a generic
 * bubble sort function that uses function pointers.
 */
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This function swaps the values of two integers
 * pointed to by p and q. */
void swap_int(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

/* This is a more generic bubble sort function to sort an array of ints
 * in any order.  It uses a function parameter to let the caller tell us
 * when two elements should be swapped.
 */
void bubble_sort_int_generic(int *arr, size_t n, int (*cmp_fn)(int, int)) {
    while (true) {
        bool swapped = false;
        
        for (size_t i = 1; i < n; i++) {
            if (cmp_fn(arr[i - 1], arr[i]) > 0) {
                swapped = true;
                int tmp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = tmp;
            }
        }
        
        if (!swapped) {
            return;
        }
    }
}

int sort_ascending(int first_num, int second_num) {
    if (first_num == second_num) return 0;
    else if (first_num > second_num) return 1;
    return -1;
}

int sort_descending(int first_num, int second_num) {
    if (first_num == second_num) return 0;
    else if (first_num < second_num) return 1;
    return -1;
}

int sort_odd_then_even(int first_num, int second_num) {
    bool first_is_even = first_num % 2 == 0;
    bool second_is_even = second_num % 2 == 0;
    if (!first_is_even && second_is_even) return -1;
    else if (first_is_even && !second_is_even) return 1;
    return 0;
}

void test_sort() {
    int nums[] = {4, 2, 12, -5, 56, 14};
    int nums_count = sizeof(nums) / sizeof(nums[0]);
    
    printf("Initial numbers: \n");    
    for (int i = 0; i < nums_count; i++) {
        printf("%d  ", nums[i]);
    }
    printf("\n");

    // Ascending order
    bubble_sort_int_generic(nums, nums_count, sort_ascending);
    printf("Sorted in ascending order: \n");    
    for (int i = 0; i < nums_count; i++) {
        printf("%d  ", nums[i]);
    }
    printf("\n");

    // Descending order
    bubble_sort_int_generic(nums, nums_count, sort_descending);
    printf("Sorted in descending order: \n");    
    for (int i = 0; i < nums_count; i++) {
        printf("%d  ", nums[i]);
    }
    printf("\n");

    // Odd-then-even order
    bubble_sort_int_generic(nums, nums_count, sort_odd_then_even);
    printf("Sorted in odd-then-even order: \n");    
    for (int i = 0; i < nums_count; i++) {
        printf("%d  ", nums[i]);
    }

    printf("\n");
}


int main(int argc, char *argv[]) {
    test_sort();
    return 0;
}