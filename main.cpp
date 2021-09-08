//
// Created by Robin Seo.
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int totalPassed = 0;
int totalTests = 0;

template <typename T> string isOK(const T& got, const T& expected) {
    ++totalTests;
    if (got == expected) {
        ++totalPassed;
        return "OK: ";
    }
    cout << "    Got   " << got << "\n expected " << expected << endl;
    return "ERR: ";
}

void test02() {
    SkipList skipList(3);
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(),
                 string("Level: 2 -- -2147483648, 2147483647, \n"
                        "Level: 1 -- -2147483648, 2147483647, \n"
                        "Level: 0 -- -2147483648, 2147483647, \n"))
        .c_str()
         << "Empty SkipList of Depth=3" << endl;
    srand(100);
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    //skipList.remove(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 2 -- -2147483648, 25, 30, 2147483647, \n"
                     "Level: 1 -- -2147483648, 25, 30, 2147483647, \n"
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "SkipList of Depth=3 with 10, 30, 5, 25" << endl;
    cout << isOK(skipList.contains(10), true)
         << "Contains 10" << endl;
    cout << isOK(skipList.contains(30), true)
         << "Contains 30" << endl;
    cout << isOK(skipList.contains(71), false)
         << "Does not contain 71" << endl;
    cout<< "done\n";
}

void test01() {
    SkipList skipList;
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(),
                 string("Level: 0 -- -2147483648, 2147483647, \n"))
         << "Empty SkipList" << endl;
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    skipList.add(25);
    skipList.add(25);

    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "Added 10, 30, 5, 25," << endl;
    cout << "done" <<endl;
}

void test04() {
    SkipList skipList(3);
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(),
                 string("Level: 2 -- -2147483648, 2147483647, \n"
                        "Level: 1 -- -2147483648, 2147483647, \n"
                        "Level: 0 -- -2147483648, 2147483647, \n"))
        .c_str()
         << "Empty SkipList of Depth=3" << endl;
    skipList.add(10);
    skipList.add(20);
    skipList.add(4);
    skipList.add(2);
    skipList.add(1);
    skipList.add(5313);
    skipList.add(5313);
    skipList.add(1);
    skipList.remove(2);

    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 2 -- -2147483648, 4, 10, 2147483647, \n"
                     "Level: 1 -- -2147483648, 4, 10, 2147483647, \n"
                     "Level: 0 -- -2147483648, 1, 4, 10, 20, 5313, 2147483647, \n"))
         << "SkipList of Depth=3 with 10, 20, 4, 2, 1, 5313" << endl;
    cout << isOK(skipList.contains(5313), true)
         << "Contains 5313" << endl;
    cout << isOK(skipList.contains(10), true)
         << "Contains 10" << endl;
    cout << isOK(skipList.contains(5), false)
         << "Does not contain 5" << endl;
    cout << "done" <<endl;

}
int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    //NOLINTNEXTLINE
    srand(424242);
    test01();
    test02();
    test04();
    cout << "Passed: " << totalPassed << "/" << totalTests << endl;
    return 0;
}