#include <cassert>
#include "UnitTest/UnitTest.h"
#include "../src/Chrono.h"

using namespace std;

class TestChrono : public TestClass<TestChrono>
{
public:
    TestChrono();
    ~TestChrono();

    bool OnlyOneTest();
};
