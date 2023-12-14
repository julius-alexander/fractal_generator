#include <iostream>
#include <unordered_map>

#include "hilbert.h"
#include "turtle.h"
#include "instruction_list.h"

using namespace std;

HilbertCurve::HilbertCurve(int level, int size) : turtle(size, size) {

    unordered_map<hilbert_t, const InstructionList*> subMap;
    // Initialize rules O and E as given by problem statement and add to map
    InstructionList rhsERule;
    rhsERule.append(TURN_RIGHT);
    rhsERule.append(ODD);
    rhsERule.append(FORWARD);
    rhsERule.append(TURN_LEFT);
    rhsERule.append(EVEN);
    rhsERule.append(FORWARD);
    rhsERule.append(EVEN);
    rhsERule.append(TURN_LEFT);
    rhsERule.append(FORWARD);
    rhsERule.append(ODD);
    rhsERule.append(TURN_RIGHT);
    subMap[EVEN] = &rhsERule;

    InstructionList rhsORule;
    rhsORule.append(TURN_LEFT);
    rhsORule.append(EVEN);
    rhsORule.append(FORWARD);
    rhsORule.append(TURN_RIGHT);
    rhsORule.append(ODD);
    rhsORule.append(FORWARD);
    rhsORule.append(ODD);
    rhsORule.append(TURN_RIGHT);
    rhsORule.append(FORWARD);
    rhsORule.append(EVEN);
    rhsORule.append(TURN_LEFT);
    subMap[ODD] = &rhsORule;

    // Initial Case - Level 1 Hilbert Curve starts at symbol ODD
    InstructionList tester;
    tester.append(ODD);

    // Apply substitution rules for the given number of levels
    for (int i = 1; i <= level; i++) {
        tester.substitute(subMap);
    }

    // Prints instructions to terminal
    cout << tester << endl;

    // Calculate the distance for each forward instruction
    double dist = size;
    for (int i = 1; i <= level; i++) {
        dist /= 2.0;
    }
    tester.setDistance(dist);

    // Draw the Hilbert curve using the Turtle
    turtle.follow(tester);
}
