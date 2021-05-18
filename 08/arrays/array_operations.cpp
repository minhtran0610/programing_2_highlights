#include "array_operations.hh"

int greatest_v1(int* itemptr, int size) {
    int max = *itemptr;
    int* array_ptr = itemptr;
    while (array_ptr < itemptr+size) {
        if (*array_ptr > max) {
            max = *array_ptr;
        }
        ++array_ptr;
    }
    return max;
}


int greatest_v2(int* itemptr, int* endptr) {
    int max = *itemptr;
    int* array_ptr = itemptr;
    while (array_ptr != endptr) {
        if (*array_ptr > max) {
            max = *array_ptr;
        }
        ++array_ptr;
    }
    return max;
}


void copy(int* itemptr, int* endptr, int* targetptr) {
    int* array_1_ptr = itemptr;
    int* array_2_ptr = targetptr;

    while (array_1_ptr < endptr) {
        *array_2_ptr = *array_1_ptr;
        ++array_1_ptr;
        ++array_2_ptr;
    }
}


void reverse(int* leftptr, int* rightptr) {
    int* array_l_ptr = leftptr;
    int* array_r_ptr = rightptr-1;

    while (array_l_ptr < array_r_ptr) {
        int temp_right = *array_r_ptr;
        int temp_left = *array_l_ptr;
        *array_r_ptr = temp_left;
        *array_l_ptr = temp_right;

        ++array_l_ptr;
        --array_r_ptr;
    }
}
