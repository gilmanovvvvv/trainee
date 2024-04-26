#include <iostream>

int main() {
    int int_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int* int_pointer = int_array;

    std::cout << "4th element: " << *(int_pointer + 3) << std::endl;

    return 0;
}
