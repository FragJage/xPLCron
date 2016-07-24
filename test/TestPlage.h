#include <cassert>
#include "UnitTest/UnitTest.h"
#include "../src/Plage.h"

using namespace std;

class TestPlage : public TestClass<TestPlage>
{
public:
    TestPlage();
    ~TestPlage();

    bool Time();
    bool MonthDay();
    bool Month();
    bool WeekDay();
    bool Mixed();
};
