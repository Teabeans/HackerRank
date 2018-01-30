//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum (https://github.com/Teabeans)
// twhlum@gmail.com
// Created:  2018.01.26
// Modified: 2018.01.26
//

//-----------------------------------------------------------------------------|
// File Description
//-----------------------------------------------------------------------------|
//
// This file is the solution to HackerRank's 'Day 0: Mean Median, and Mode'
// challenge:
//
// https://www.hackerrank.com/challenges/s10-basic-statistics/problem
//

//-----------------------------------------------------------------------------|
// Package Files
//-----------------------------------------------------------------------------|
//
// Driver.cpp - The driver of this program
//

//-----------------------------------------------------------------------------|
// Acknowledgements
//-----------------------------------------------------------------------------|
//
// Template author:
// Tim Lum (twhlum@gmail.com)
//

//-----------------------------------------------------------------------------|
// License
//-----------------------------------------------------------------------------|
//
// This software is published under the The 2-Clause BSD License
// https://en.wikipedia.org/wiki/BSD_licenses
/*
MIT License
Copyright (c) 2017 Timothy W. Lum (twhlum@gmail.com)
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//

//-----------------------------------------------------------------------------|
// Special Instructions
//-----------------------------------------------------------------------------|
//
// To load a text file as cin input in Visual Studios:
// 1. Go to the top menu bar => Debug => <ProjectName> Properties => Debugging => Command Arguments =>
// 2. "< <Filepath>/<Filename>.txt" ie. "< /Sudoku.txt"
// ie. < /Sudoku.txt

//-----------------------------------------------------------------------------|
// Index
//-----------------------------------------------------------------------------|



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       INCLUDE STATEMENTS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
template <class typeT>
void initialize(typeT tgtArray[], int numDigits);

template <class typeT>
void obliviate(typeT tgtArray[], int numDigits);

void quicksort(int numArray[], int low, int high);

int findPivot(const int numArray[], int low, int high);

void sortArray(int numArray[], const int numDigits);

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PUBLIC METHODS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (+) = Public -----------------------|
// #calcMean(int, int[])
//-------------------------------------|
// Desc:    Calculates the mean of an integer array
// Params:  const int arg1 - The size of the array
//          const int[] arg2 - The array to find the mean of
// PreCons: The array must be fully loaded
//          A partially loaded array will yield erroneous results
// PosCons: None
// RetVal:  double - The calculated mean of the array
// MetCall: NULL
double const calcMean(const int numDigits, const int numArray[]) {
   // Generate a temporary storage array
   double* avgArray = new double[numDigits];
   initialize(avgArray, numDigits);
   // Load the average of every element to the storage array
   // TBN: To avoid the chance of int overflow confounding the results,
   //      every element is averaged on its own first.
   double tempAvg = 0;
   double doubDigits = numDigits;
   for (int i = 0 ; i < numDigits ; i++) {
      // TBN: Perform non-int arithmetic, else the decimals are lost
      tempAvg = numArray[i] / doubDigits;
      avgArray[i] = tempAvg;
   }

   // Sum the shards
   double mean = 0;
   for (int i = 0 ; i < numDigits ; i++) {
      mean += avgArray[i];
   }

   // Clear memory that was used
   obliviate(avgArray, numDigits);
   delete avgArray;

   // Return the mean
   return (mean);
} // Closing calcMean()

// (+) = Public -----------------------|
// #calcMedian(int, int[])
//-------------------------------------|
// Desc:    Calculates the median of an integer array
// Params:  const int arg1 - The size of the array
//          const int[] arg2 - The array to find the median of
// PreCons: The array may not be sorted
//          A partially loaded array may yield erroneous results
//          The median shall be found between [0] and [arg1] of the original sequence
// PosCons: The order of the passed array shall be maintained
// RetVal:  int - The calculated median of the array
// MetCall: NULL
double calcMedian(const int numDigits, const int numArray[]) {
   int* arrayToSort = new int[numDigits];
   // Copy values across
   for (int i = 0 ; i < numDigits ; i++) {
      arrayToSort[i] = numArray[i];
   }

   // Sort the working array
   sortArray(arrayToSort, numDigits);

   double median = 0;
   if (numDigits % 2 == 0) {
      median = (numArray[numDigits/2] + numArray[ (numDigits/2) + 1]) / 2.0;
   }
   else {
      median = (numArray[numDigits/2]) + 0.0;
   }

   obliviate(arrayToSort, numDigits);
   delete arrayToSort;
   return (median);
} // Closing calcMedian()

// (+) = Public -----------------------|
// #calcMode(int, int[])
//-------------------------------------|
// Desc:    Calculates the mode of an integer array
// Params:  const int arg1 - The size of the array
//          const int[] arg2 - The array to find the mode of
// PreCons: The array may not be sorted
//          A partially loaded array may yield erroneous results
//          In the case of a tie, the mode shall be the smallest value
// PosCons: The order of the passed array shall be maintained
// RetVal:  int - The calculated mode of the array
// MetCall: NULL
int const calcMode(const int numDigits, const int numArray[]) {
   int* arrayToSort = new int[numDigits];
   // Copy values across
   for (int i = 0 ; i < numDigits ; i++) {
      arrayToSort[i] = numArray[i];
   }

   // Sort the working array
   sortArray(arrayToSort, numDigits);

   int mode = arrayToSort[0];
   int maxOccur = 1;
   int currVal = mode;
   int currOccur = 1;
   // Perform comparisons to find the mode:
   for (int i = 1 ; i <= numDigits ; i++) {
      // If it's the same number as the last check...
      if (numArray[i] == currVal) {
         // Increment
         currOccur++;
         // And if it exceeds the maxOccurence...
         if (currOccur > maxOccur) {
            // Refresh the mode and the max count
            maxOccur = currOccur;
            mode = currVal;
         }
      }
      // The index we're looking at does not match the current value
      else {
         currVal = numArray[i];
         currOccur = 1;
      }
   }
   obliviate(arrayToSort, numDigits);
   delete arrayToSort;
   return (mode);
} // Closing calcMode()

// (+) = Public -----------------------|
// #initialize(int[], int)
//-------------------------------------|
// Desc:    Initializes an array (sets all values to 0)
// Params:  const int[] arg1 - The target array to initialize
//          const int[] arg2 - The number of elements in the array
// PreCons: The array size must be greater than or equal to arg2
// PosCons: The number of elements initialized equals arg2
// RetVal:  None
// MetCall: None
template <class typeT>
void initialize(typeT tgtArray[], int numDigits) {
   for (int i = 0 ; i < numDigits ; i++) {
      tgtArray[i] = 0;
   }
}
// (+) = Public -----------------------|
// #obliviate(int, int[])
//-------------------------------------|
// Desc:    Clears the memory of an array
// Params:  const <T>[] arg1 - The array to clear
//          const int arg2 - The size of the array
// PreCons: To fully clear, arg1 must be the size of the array
// PosCons: The target array has been cleared
// RetVal:  None
// MetCall: None
template <class typeT>
void obliviate(typeT tgtArray[], int numDigits) {
   // Clear the array values
   for (int i = 0 ; i < numDigits ; i++) {
      tgtArray[i] = NULL;
   }
} // Closing obliviate()

// (+) = Public -----------------------|
// #loadArray(int[])
//-------------------------------------|
// Desc:    Loads an array
// Params:  int[] arg1 - The array to load
//          int arg2 - The number of elements to attempt to load
// PreCons: The number of elements must be less than or equal to the array size
// PosCons: The next arg2 elements have been loaded to the target array
// RetVal:  None
// MetCall: None
void loadArray(int tgtArray[], const int numElements) {
   for (int i = 0 ; i < numElements ; i++ ) {
      std::cin >> tgtArray[i];
   }
} // Closing loadArray()

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PRIVATE METHODS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// (-) = Private ----------------------|
// #initialize(int[], int)
//-------------------------------------|
// Desc:    NULL
// Params:  int[] arg1 - The array to initialize
//          int arg2 - The number of elements in the array
// PreCons: The array size must be greater than or equal to arg2
// PosCons: The first arg2 elements have been initialized to '0'
// RetVal:  None
// MetCall: None
void initialize (int tgtArray[], const int numDigits) {
   for (int i = 0 ; i < numDigits ; i++ ) {
      tgtArray[i] = 0;
   }
} // Closing initialize()

// (-) = Private ----------------------|
// #sortArray(int[])
//-------------------------------------|
// Desc:    Sorts an int array
// Params:  int[] arg1 - The array to sort
//          int arg2 - The number of elements in the array
// PreCons: The array size must be greater than or equal to arg2
// PosCons: The first arg2 elements have been sorted
// RetVal:  None
// MetCall: quicksort(int[], int, int)
void sortArray(int numArray[], const int numDigits) {
   // Call the recursive quicksort() algorithm
   quicksort(numArray, 0, numDigits-1);
} // Closing sortArray()

// (-) = Private ----------------------|
// #quickSort(int[], int, int)
//-------------------------------------|
// Desc:    Recursive helper to sortArray()
//          Terminology follows Wikipedia convention (https://en.wikipedia.org/wiki/Quicksort)
// Params:  int[] arg1 - The array to sort
//          int arg2 - The subarray low index
//          int arg3 - The subarray high index
// PreCons: NULL
// PosCons: Pivot has been moved to the appropriate index for this pass
//          Values less than the pivot are at array indices less than the pivot
//          Values greater than the pivot are at array indices higher than the pivot
// RetVal:  NULL
// MetCall: NULL
void quicksort(int numArray[], int low, int high) {
   // Base case - A subarray of size 1 is sorted by definition
   if (low >= high) {
      return;
   }

   // Visit
   // Step 1: Find the Mo3 pivot (is it low, middle, or high?
   int pivotLocation = findPivot(numArray, low, high);
   //                     \ /
   // +-----+-----+-----+-----+-----+-----+-----+-----+
   // |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
   // +-----+-----+-----+-----+-----+-----+-----+-----+

   // Step 2: Move the pivot out of the way (to the end of the array
   //                     \ /
   // +-----+-----+-----+-----+-----+-----+-----+-----+
   // |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
   // +-----+-----+-----+-----+-----+-----+-----+-----+
   int temp = numArray[pivotLocation];
   numArray[pivotLocation] = numArray[high];
   numArray[high] = temp;
   //                     \ /
   // +-----+-----+-----+-----+-----+-----+-----+-----+
   // |  0  |  1  |  2  |  7  |  4  |  5  |  6  |  3  |
   // +-----+-----+-----+-----+-----+-----+-----+-----+


   // Step 3: Compare and swap
   // For every index in the subarray, compare
   int pivot = low;
   //                     \ /
   // +-L:0-+-----+-----+-----+-----+-----+-----+-H:7-+
   // |  0  |  1  |  2  |  7  |  4  |  5  |  6  |  3  |
   // +-----+-----+-----+-----+-----+-----+-----+-----+
// / \   *

   for (int i = low ; i < high ; i++) {
      // If the number at the comparison index is less than the pivot...
      if (numArray[i] < numArray[high]) {
         // Swap back to the wall
         int temp = numArray[pivot];
         numArray[pivot] = numArray[i];
         numArray[i] = temp;
         // Move the swap index (the wall) up
         pivot++;
      }
   } // Closing for loop - All comparisons complete.

   // Step 4: Place the pivot
   //                     \7/
   // +-L:0-+-----+-----+-----+-----+-----+-----+-H:7-+
   // |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
   // +-----+-----+-----+-----+-----+-----+-----+-----+
   //                / \                     *
   temp = numArray[pivot];
   numArray[pivot] = numArray[high];
   numArray[high] = temp;

   // Recur left
   quicksort(numArray, low, (pivot - 1));
   // Recur right
   quicksort(numArray, (pivot + 1), high);
}

// (-) = Private ----------------------|
// #findPivot(int[], int, int)
// ------------------------------------|
// Desc:    Finds a pivot value from a subarray using the median-of-three approach
// Params:  int[] arg1 - The array to select a pivot from
//          int arg2 - The low bound of the sample
//          int arg3 - The high bound of the sample
// PreCons: arg2 must be greater than or equal to 0.
//          arg3 must be less than or equal to the maximum index of arg1.
// PosCons: None
// RetVal:  int - The selected pivot index
// MetCall: None
int findPivot(const int numArray[], int low, int high) {
   // Set the middle index
   int mid = (low+high)/2;
   // All possible relationship combinations:
   // 1 1 1
   // 1 1 2
   // 1 1 3 - Same as 1 1 2
   // 1 2 1
   // 1 2 2
   // 1 2 3
   // 1 3 1 - Same as 1 2 1
   // 1 3 2
   // 1 3 3 - Same as 1 2 2
   // 2 1 1
   // 2 1 2
   // 2 1 3
   // 2 2 1
   // 2 2 2 - Same as 1 1 1
   // 2 2 3 - Same as 1 1 2
   // 2 3 1
   // 2 3 2 - Same as 1 2 1
   // 2 3 3 - Same as 1 2 2
   // 3 1 1 - Same as 2 1 2
   // 3 1 2
   // 3 1 3 - Same as 2 1 2
   // 3 2 1
   // 3 2 2 - Same as 2 1 1
   // 3 2 3 - Same as 2 1 2
   // 3 3 1 - Same as 2 2 1
   // 3 3 2 - Same as 2 2 1
   // 3 3 3 - Same as 1 1 1
   // Begin comparisons by looking for duplicates (the duplicate is the return)
   if (numArray[low] == numArray[mid] || numArray[mid] == numArray[high]) {
      // 1* 1* 1*
      // 1* 1* 2
      // 1  2* 2*
      // 2  1* 1*
      // 2* 2* 1
      return (mid);
   } // Adjacent > or < comparisons are guaranteed to work
   if (numArray[low] == numArray[high]) {
      // 1* 2  1*
      // 2* 1  2*
      return (high);
   }
   // Equality comparisons complete: set guaranteed not to contain duplicates
   if (numArray[low] < numArray[mid] && numArray[low] < numArray[high]) {
      // 1  2* 3
      // 1  3  2*
      return ((numArray[mid] < numArray[high]) ? mid : high);
   }
   if (numArray[low] > numArray[mid] && numArray[low] > numArray[high]) {
      // 3  2* 1
      // 3  1  2*
      return ((numArray[mid] > numArray[high]) ? mid : high);
   }
   // 2* 3  1
   // 2* 1  3
   return (low);
} // closing selectPivot()

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PROGRAM DRIVER
//
//-------|---------|---------|---------|---------|---------|---------|---------|

int main() {
   // Set the precision formatting
   std::cout.precision(1);

   // Extract the first 'int' from the input stream
   int numDigits;
   std::cin >> numDigits;
   
   // Allocate an array of the appropriate size
   int* numArray = new int[numDigits];

   // Zero out the array
   initialize(numArray, numDigits);

   // Load the array
   loadArray(numArray, numDigits);

   // Calculate the mean
   double mean = calcMean(numDigits, numArray);
   std::cout << "Mean : " << std::fixed << mean << std::endl;

   // Calculate the median
   double median = calcMedian(numDigits, numArray);
   std::cout << "Median : " << std::fixed << median << std::endl;

   // Calculate the mode
   int mode = calcMode(numDigits, numArray);
   std::cout << "Mode : " << mode << std::endl;

   // Deallocate the array
   obliviate(numArray, numDigits);
   delete numArray;

   return 0;
}
