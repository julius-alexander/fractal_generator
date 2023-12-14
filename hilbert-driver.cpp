#include <iostream>
#include <unordered_map>
#include <cstring>
using namespace std;

#include "hilbert.h"

const int HILBERT_LEVEL = 3;
const int IMAGE_SIZE = 5000;
const string OUTPUT_FILE = "hilbert.bmp";

int main() {
    HilbertCurve curve(HILBERT_LEVEL, IMAGE_SIZE);
    curve.writeToFile(OUTPUT_FILE);
    cout << "Success!\n";
    return 0;
}

// Settings for different curves:

// Hilbert Curve:
//      distance /= 2.0
//      x = y = 0.0
//      O -> 
//      E ->

// Peano Curve:
//      distance /= 4.5
//      x = width * 0.25;
//      y = width * 0.75;
//      F -> F R F L F L F L F R F R F R F L F