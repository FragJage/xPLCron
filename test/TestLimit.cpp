#include "TestLimit.h"

using namespace std;

TestLimit::TestLimit() : TestClass("Limit", this)
{
	addTest("ValueAll", &TestLimit::ValueAll);
	addTest("SimpleValue", &TestLimit::SimpleValue);
	addTest("Range", &TestLimit::Range);
	addTest("Time", &TestLimit::Time);
	addTest("TimeRange", &TestLimit::TimeRange);
	addTest("Day", &TestLimit::Day);
	addTest("DayRange", &TestLimit::DayRange);
}

TestLimit::~TestLimit()
{
}

bool TestLimit::ValueAll()
{
    Limit limit;

    limit.SetLimit("*");
    assert(true==limit.Match(0));
    assert(true==limit.Match(5));
    assert(true==limit.Match(15));
    assert(true==limit.Match(30));
    return true;
}

bool TestLimit::SimpleValue()
{
    Limit limit;

    limit.SetLimit("2");
    assert(false==limit.Match(0));
    assert(true==limit.Match(2));
    assert(false==limit.Match(4));

    limit.SetLimit("15");
    assert(false==limit.Match(10));
    assert(true==limit.Match(15));
    assert(false==limit.Match(24));
    return true;
}

bool TestLimit::Range()
{
    Limit limit;

    limit.SetLimit("2-5");
    assert(false==limit.Match(0));
    assert(true==limit.Match(2));
    assert(true==limit.Match(4));
    assert(true==limit.Match(5));
    assert(false==limit.Match(6));

    limit.SetLimit("12-15");
    assert(false==limit.Match(9));
    assert(true==limit.Match(12));
    assert(true==limit.Match(14));
    assert(true==limit.Match(15));
    assert(false==limit.Match(16));
    return true;
}

bool TestLimit::Time()
{
    Limit limit;

    limit.SetLimitTime("15:36");
    assert(false==limit.Match(1201));
    assert(true==limit.Match(1536));
    assert(false==limit.Match(2336));
    return true;
}

bool TestLimit::TimeRange()
{
    Limit limit;

    limit.SetLimitTime("02:34-5:12");
    assert(false==limit.Match(230));
    assert(true==limit.Match(234));
    assert(true==limit.Match(452));
    assert(true==limit.Match(512));
    assert(false==limit.Match(645));
    return true;
}

bool TestLimit::Day()
{
    Limit limit;

    limit.SetLimitDay("Lu");
    assert(false==limit.Match(0));
    assert(true==limit.Match(1));
    assert(false==limit.Match(2));
    return true;
}

bool TestLimit::DayRange()
{
    Limit limit;

    limit.SetLimitDay("Mo-We");
    assert(false==limit.Match(0));
    assert(true==limit.Match(1));
    assert(true==limit.Match(2));
    assert(true==limit.Match(3));
    assert(false==limit.Match(4));

    limit.SetLimitDay("4-6");
    assert(false==limit.Match(0));
    assert(true==limit.Match(4));
    assert(true==limit.Match(5));
    assert(true==limit.Match(6));
    assert(false==limit.Match(7));
    return true;
}
