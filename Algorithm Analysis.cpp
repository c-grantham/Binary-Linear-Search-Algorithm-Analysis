/*
* File: DSA Project.cpp
* Author: Cal Grantham & Aaron Guzman
* Date: 11/10/23
*
* Description: This program implements a binary search and linear search algorithm
* that searches for a random key in a randomly generated array of a
* size provided by the user. The algorithms run five times through
* unique arrays and elapsed time for each trial is reported. The
* average search time and number of comparisons made is reported for
* each algorithm as well as the sorting time for the binary search arrays.
*/
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;

int linearSearch(int arr[], int x, int n, int &linearComparisons);
int binarySearch(int arr[], int start, int end, int x, int &binaryComparisons);
int main() {
    int linearComparisons = 0;
    int binaryComparisons = 0;
    int size = 0;
    double totalLinearElapsed = 0;
    double totalBinaryElapsed = 0;
    double totalSortingElapsed = 0;

    // prompt for array size
    cout << "Please enter array size: ";
    cin >> size;

    // **LINEAR SEARCH SECTION**
    cout << "********************************************\n";
    cout << "Linear Search: \n---------------\nInput Size = " << size << endl;

    for (int i = 0; i < 5; i++) {
        // create array with given size and fill with random numbers
        int *arr = new int[size];
        srand(time(0));

        for (int i = 0; i < size; i++) {
            int num = rand() % (3 * size * 2 + 1) - (3 * size);
            arr[i] = num;
    }
        // generate worst case value for key
        int key = (size * 3) + 1;

        // call linearSearch and track elapsed time
        const auto startLinear{chrono::steady_clock::now()};
        const auto LS{linearSearch(arr, key, size, linearComparisons)};
        const auto endLinear{chrono::steady_clock::now()};
        const chrono::duration<double> elapsedLinear{endLinear - startLinear};
        totalLinearElapsed += elapsedLinear.count();
        cout << fixed << setprecision(8);
        cout << " Elapsed Search Time for Run #" << i+1 << ": " <<
        elapsedLinear.count() << endl;
        delete[] arr;
    }

    cout << endl << "Average Search Time: " << totalLinearElapsed / 5.0 << endl;
    cout << defaultfloat;
    cout << "Number of Comparisons Made: " << linearComparisons << endl;

    // **BINARY SEARCH SECTION**

    cout << "********************************************\n";
    cout << "Binary Search: \n---------------\nInput Size = " << size << endl;

    for (int i = 0; i < 5; i++) {
        // create array with given size and fill with random numbers
        int *arr = new int[size];
        srand(time(0));

        for (int i = 0; i < size; i++) {
            int num = rand() % (3 * size * 2 + 1) - (3 * size);
            arr[i] = num;
        }

        // generate worst case value for key
        int key = (size * 3) + 1;

        // sort the array and track elapsed time
        const auto startSort{chrono::steady_clock::now()};
        sort(arr, arr + size);
        const auto endSort{chrono::steady_clock::now()};
        const chrono::duration<double> elapsedSort{endSort - startSort};
        totalSortingElapsed += elapsedSort.count();

        // call binarySearch and track elapsed time
        const auto startBinary{chrono::steady_clock::now()};
        const auto BS{binarySearch(arr, 0, size-1, key, binaryComparisons)};
        const auto endBinary{chrono::steady_clock::now()};
        const chrono::duration<double> elapsedBinary{endBinary - startBinary};
        totalBinaryElapsed += elapsedBinary.count();

        cout << fixed << setprecision(8);
        cout << " Elapsed Search Time for Run #" << i+1 << ": " <<
        elapsedBinary.count() << endl;

        delete[] arr;
    }

    cout << endl << "Average Search Time: " << totalBinaryElapsed / 5.0 << endl;
    cout << "Average Sorting Time: " << totalSortingElapsed / 5.0 << endl;
    cout << defaultfloat;
    cout << "Number of Comparisons Made: " << binaryComparisons;

    return 0;
    }

    /*
    linearSearch - searches linearly through an array of size n for a key value x
    @param arr[] - array of integers generated randomly outside of the function
    @param x - the "key", integer value generated randomly out of the function@param n - integer value size of the array, provided by user
    @param linearComparisons - integer value passed by reference to track the number of
    comparisons
    @return i - the integer value index of the array where x is found, otherwise return -1
    */
    int linearSearch(int arr[], int x, int n, int &linearComparisons) {
        for (int i = 0; i < n; i++) {
            linearComparisons++;
            if (arr[i] == x) {
                return i;
            }
        }
        return -1;
    }

    /*
    binarySearch - searches through an array of size n for a key value x
    @param arr[] - array of integers generated randomly outside of the function
    @param start - integer of the first index in the array
    @param end - integer of the last index in the array
    @param x - the "key", integer value generated randomly out of the function
    @param binaryComparisons - integer value passed by reference to track the number of comparisons
    @return - the integer value index of the array where x is found, otherwise return -1.
    */
    int binarySearch(int arr[], int start, int end, int x, int &binaryComparisons) {
        binaryComparisons++;
        if (start > end) {
            return -1;
        }
        else {
            int mid = ((start + end)/2);
            binaryComparisons++;
            if (x == arr[mid]) {
                return mid;
            }
            else {
                binaryComparisons++;
                if (x < arr[mid]) {
                    return binarySearch(arr, start, (mid-1), x, binaryComparisons);
                }
                else {
                    return binarySearch(arr, (mid+1), end, x, binaryComparisons);
                }
            }
        }
    }
