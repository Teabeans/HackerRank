//-----------------------------------------------------------------------------|
// Authorship
//-----------------------------------------------------------------------------|
//
// Tim Lum (https://github.com/Teabeans)
// twhlum@gmail.com
// Created:  2018.06.27
// Modified: 2018.06.27
//

//-----------------------------------------------------------------------------|
// File Description
//-----------------------------------------------------------------------------|
//
// This file is the solution to HackerRank's 'Day 0: Weighted Mean' challenge:
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
// This software is published under the MIT License
// https://en.wikipedia.org/wiki/MIT_License
/*
MIT License
Copyright (c) 2018 Timothy W. Lum (twhlum@gmail.com)
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

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       INCLUDE STATEMENTS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       NAMESPACE DECLARATIONS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

using namespace std;



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       METHOD DECLARATIONS
//
//-------|---------|---------|---------|---------|---------|---------|---------|

// None for this class



//-------|---------|---------|---------|---------|---------|---------|---------|
//
//       PROGRAM DRIVER
//
//-------|---------|---------|---------|---------|---------|---------|---------|

int main() {
    bool debug = false;
    // Set numeric display of cout
    cout << fixed;
    cout << setprecision(1);
    // Acquire the number of elements
    int numElements;
    cin >> numElements;
    if (debug) {
        cout << "NumElements: " << numElements;
    }
    int weight[numElements];
    int values[numElements];
    int tempVal;
    // Load arrays
    for ( int i = 0 ; i < numElements ; i++ ) {
        cin >> tempVal;
        values[i] = tempVal;
    }
    for ( int i = 0 ; i < numElements ; i++ ) {
        cin >> tempVal;
        weight[i] = tempVal;
    }
    // Arrays loaded
    if (debug) {
        for ( int i = 0 ; i < numElements ; i++ ) {
            cout << "(" << values[i] << "," << weight[i] << ")";
        }
    }

    // Calculate mean
    float totalVal = 0.0;
    float totalWgt = 0.0;
    for (int i = 0 ; i < numElements ; i++ ) {
        totalVal += (weight[i] * values[i]);
        totalWgt +=  weight[i];
    }
    float wgtAvg = (totalVal / totalWgt);
    cout << wgtAvg << endl;

    // Clear data
    numElements = 0;
    tempVal = 0;
    for ( int i = 0 ; i < numElements ; i++ ) {
        weight[i] = 0;
        values[i] = 0;
    }
    totalVal = 0.0;
    totalWgt = 0.0;
    wgtAvg   = 0.0;

    return 0;
} // Closing main()
