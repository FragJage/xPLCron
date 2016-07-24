#include "TestChrono.h"

using namespace std;

TestChrono::TestChrono() : TestClass("Cron", this)
{
	addTest("OnlyOneTest", &TestChrono::OnlyOneTest);
}

TestChrono::~TestChrono()
{
}

bool TestChrono::OnlyOneTest()
{
    Chrono chrono("TEST");


    chrono.SetCron("XPLFRAG-OWFS.test:temperature", "output", "20", "21:00-07:00;*;*;Lu-Ve;18", "21:30-09:00;*;*;Sa-Di;18", "20:30-21:00;1;*;*;21", "", "");
    assert(true==chrono.IsChange("20"));
    chrono.SetValue("20");
    assert(false==chrono.IsChange("20"));
    assert(true==chrono.IsChange("21"));
    assert("20"==chrono.FindValue(1200, 1, 1, 1));
    assert("18"==chrono.FindValue(300, 1, 1, 1));
    assert("18"==chrono.FindValue(2300, 1, 1, 1));
    assert("18"==chrono.FindValue(800, 1, 1, 6));
    assert("20"==chrono.FindValue(2115, 1, 1, 6));
    assert("21"==chrono.FindValue(2045, 1, 1, 6));
    return true;
}
