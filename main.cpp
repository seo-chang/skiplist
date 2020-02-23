//
// Created by <Name> on <Date>.
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int totalPassed = 0;
int totalTests = 0;

template <typename T> string isOK(const T& got, const T& expected) {
    ++totalTests;
    string result;

    if (got == expected) {
        ++totalPassed;
        result = "OK: ";
    } else {
        cout << "    Got   " << got << "\n expected " << expected << endl;
        result = "ERR: ";
    }

    return result;
}

void test02() {
    SkipList skipList(3);
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 2 -- -2147483648, 2147483647, \n"
                                  "Level: 1 -- -2147483648, 2147483647, \n"
                                  "Level: 0 -- -2147483648, 2147483647, \n"))
                .c_str()
         << "Empty SkipList of Depth=3" << endl;
    srand(100);
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 2 -- -2147483648, 25, 2147483647, \n"
                     "Level: 1 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
    cout << isOK(skipList.contains(10), true) << "Contains 10" << endl;
    cout << isOK(skipList.contains(30), true) << "Contains 30" << endl;
    cout << isOK(skipList.contains(71), false) << "Does not contain 71" << endl;
}

void test01() {
    SkipList skipList;
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 0 -- -2147483648, 2147483647, \n"))
         << "Empty SkipList" << endl;
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "Added 10, 30, 5, 25," << endl;
}

int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    // NOLINTNEXTLINE
    srand(424242);
    test01();
    test02();
    cout << "Passed: " << totalPassed << "/" << totalTests << endl;
    return 0;
}