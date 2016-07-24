#include <cassert>
#include "UnitTest/UnitTest.h"
#include "../src/Limit.h"

using namespace std;

class TestLimit : public TestClass<TestLimit>
{
public:
    TestLimit();
    ~TestLimit();

    bool ValueAll();
    bool SimpleValue();
    bool Range();
    bool Time();
    bool TimeRange();
    bool Day();
    bool DayRange();
};
