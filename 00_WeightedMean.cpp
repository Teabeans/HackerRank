#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;


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
    return 0;
}
