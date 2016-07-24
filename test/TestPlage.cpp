#include "TestPlage.h"

using namespace std;

TestPlage::TestPlage() : TestClass("Plage", this)
{
	addTest("Time", &TestPlage::Time);
	addTest("MonthDay", &TestPlage::MonthDay);
	addTest("Month", &TestPlage::Month);
	addTest("WeekDay", &TestPlage::WeekDay);
	addTest("Mixed", &TestPlage::Mixed);
}

TestPlage::~TestPlage()
{
}

bool TestPlage::Time()
{
    Plage plage;


    plage.SetPlage("7:15;*;*;*;5");
    assert("5"==plage.GetValue());
    assert(false==plage.Match(714,1,3,2));
    assert(true==plage.Match(715,2,4,3));
    assert(false==plage.Match(716,3,5,1));
    plage.SetPlage("7:16,08:30,12:30,16:35,23:33;*;*;*;6");
    assert(false==plage.Match(714,1,3,2));
    assert(true==plage.Match(716,2,4,3));
    assert(false==plage.Match(820,3,5,1));
    assert(true==plage.Match(830,4,6,5));
    assert(false==plage.Match(1001,1,3,2));
    assert(true==plage.Match(1230,2,4,3));
    assert(false==plage.Match(1420,3,5,1));
    assert(true==plage.Match(1635,4,6,5));
    assert(false==plage.Match(1636,1,3,2));
    assert(true==plage.Match(2333,2,4,3));
    assert(false==plage.Match(2359,3,5,1));
    plage.SetPlage("7:19-08:32,13:41-17:56;*;*;*;7");
    assert(false==plage.Match(718,1,3,2));
    assert(true==plage.Match(719,2,4,3));
    assert(true==plage.Match(802,3,5,1));
    assert(true==plage.Match(832,4,6,5));
    assert(false==plage.Match(1340,1,3,2));
    assert(true==plage.Match(1341,2,4,3));
    assert(true==plage.Match(1522,3,5,1));
    assert(true==plage.Match(1756,4,6,5));
    assert(false==plage.Match(1758,1,3,2));
    plage.SetPlage("22:00-02:00;*;*;*;7");
    assert(false==plage.Match(2130,1,3,2));
    assert(true==plage.Match(2201,2,4,3));
    assert(true==plage.Match(2359,3,5,1));
    assert(true==plage.Match(101,4,6,5));
    assert(true==plage.Match(159,2,4,3));
    assert(false==plage.Match(201,1,3,2));

    plage.SetPlage("7:15,08:30-10:00,12:30,16:35-23:33;*;*;*;8");
    assert(false==plage.Match(714,1,3,2));
    assert(true==plage.Match(715,2,4,3));
    assert(false==plage.Match(759,3,5,1));
    assert(true==plage.Match(830,4,6,5));
    assert(true==plage.Match(901,1,3,2));
    assert(true==plage.Match(1000,2,4,3));
    assert(false==plage.Match(1229,3,5,1));
    assert(true==plage.Match(1230,4,6,5));
    assert(false==plage.Match(1231,1,3,2));
    assert(false==plage.Match(1634,2,4,3));
    assert(true==plage.Match(1635,3,5,1));
    assert(true==plage.Match(2145,1,3,2));
    assert(true==plage.Match(2333,2,4,3));
    assert(false==plage.Match(2359,3,5,1));
    return true;
}

bool TestPlage::MonthDay()
{
    Plage plage;


    plage.SetPlage("*;3;*;*;15");
    assert("15"==plage.GetValue());
    assert(false==plage.Match(1234,2,4,3));
    assert(true==plage.Match(2345,3,5,1));
    assert(false==plage.Match(123,4,4,3));
    plage.SetPlage("*;3,09,14,30;*;*;16");
    assert(false==plage.Match(1234,2,4,3));
    assert(true==plage.Match(2345,3,5,1));
    assert(false==plage.Match(123,4,4,3));
    assert(false==plage.Match(835,8,5,4));
    assert(true==plage.Match(1354,9,5,1));
    assert(false==plage.Match(229,10,1,2));
    assert(false==plage.Match(835,13,5,4));
    assert(true==plage.Match(1354,14,5,1));
    assert(false==plage.Match(229,15,1,2));
    assert(false==plage.Match(1234,29,4,3));
    assert(true==plage.Match(2345,30,5,1));
    assert(false==plage.Match(123,31,4,3));
    plage.SetPlage("*;3-09,14-30;*;*;17");
    assert(false==plage.Match(1234,2,4,3));
    assert(true==plage.Match(2345,3,5,1));
    assert(true==plage.Match(123,6,4,3));
    assert(true==plage.Match(835,9,5,4));
    assert(false==plage.Match(1354,13,5,1));
    assert(true==plage.Match(229,14,1,2));
    assert(true==plage.Match(835,20,5,4));
    assert(true==plage.Match(1354,30,5,1));
    assert(false==plage.Match(229,31,1,2));
    plage.SetPlage("*;3-09,11,14-21,25;*;*;17");
    assert(false==plage.Match(1234,2,4,3));
    assert(true==plage.Match(2345,3,5,1));
    assert(true==plage.Match(123,6,4,3));
    assert(true==plage.Match(835,9,5,4));
    assert(false==plage.Match(1354,10,5,1));
    assert(true==plage.Match(229,11,1,2));
    assert(false==plage.Match(835,12,5,4));
    assert(false==plage.Match(1354,13,5,1));
    assert(true==plage.Match(229,14,1,2));
    assert(true==plage.Match(1234,17,4,3));
    assert(true==plage.Match(2345,21,5,1));
    assert(false==plage.Match(123,23,4,3));
    assert(true==plage.Match(835,25,5,4));
    assert(false==plage.Match(1354,26,5,1));
    return true;
}

bool TestPlage::Month()
{
    Plage plage;


    plage.SetPlage("*;*;2;*;15");
    assert("15"==plage.GetValue());
    assert(false==plage.Match(1230,15,1,1));
    assert(true==plage.Match(1230,15,2,1));
    assert(false==plage.Match(1230,15,3,1));
    plage.SetPlage("*;*;2,4-6,8,10-12;*;18");
    assert(false==plage.Match(1230,15,1,1));
    assert(true==plage.Match(1230,15,2,1));
    assert(false==plage.Match(1230,15,3,1));
    assert(true==plage.Match(1230,15,4,1));
    assert(true==plage.Match(1230,15,5,1));
    assert(true==plage.Match(1230,15,6,1));
    assert(false==plage.Match(1230,15,7,1));
    assert(true==plage.Match(1230,15,8,1));
    assert(false==plage.Match(1230,15,9,1));
    assert(true==plage.Match(1230,15,10,1));
    assert(true==plage.Match(1230,15,11,1));
    assert(true==plage.Match(1230,15,12,1));
    return true;
}

bool TestPlage::WeekDay()
{
    Plage plage;


    plage.SetPlage("*;*;*;Lu;25");
    assert("25"==plage.GetValue());
    assert(false==plage.Match(1230,15,1,0));
    assert(true==plage.Match(1230,15,2,1));
    assert(false==plage.Match(1230,15,3,2));
    plage.SetPlage("*;*;*;Mo,Th;26");
    assert(false==plage.Match(1230,15,1,0));
    assert(true==plage.Match(1230,15,2,1));
    assert(false==plage.Match(1230,15,3,2));
    assert(true==plage.Match(1230,15,1,4));
    assert(false==plage.Match(1230,15,3,5));
    plage.SetPlage("*;*;*;4-6;27");
    assert(false==plage.Match(1230,15,1,3));
    assert(true==plage.Match(1230,15,2,4));
    assert(true==plage.Match(1230,15,3,5));
    assert(true==plage.Match(1230,15,3,6));
    assert(false==plage.Match(1230,15,1,7));
    plage.SetPlage("*;*;*;1,Me-Ve;28");
    assert(false==plage.Match(1230,15,1,2));
    assert(true==plage.Match(1230,15,2,3));
    assert(true==plage.Match(1230,15,3,4));
    assert(true==plage.Match(1230,15,3,5));
    assert(false==plage.Match(1230,15,1,6));
    plage.SetPlage("*;*;*;Sa-Di;28");
    assert(true==plage.Match(1230,15,0,0));
    assert(false==plage.Match(1230,15,2,1));
    assert(false==plage.Match(1230,15,3,3));
    assert(false==plage.Match(1230,15,3,5));
    assert(true==plage.Match(1230,15,1,6));
    return true;
}

bool TestPlage::Mixed()
{
    Plage plage;


    plage.SetPlage("07:00-08:00,20:30-21:30;*;*;Lu,Ma,Me,Je,Ve;22");
    assert("22"==plage.GetValue());
    assert(false==plage.Match(600,15,1,2));
    assert(true==plage.Match(730,15,1,2));
    assert(false==plage.Match(1230,15,1,2));
    assert(true==plage.Match(2100,15,1,2));
    assert(false==plage.Match(2200,15,1,2));
    assert(false==plage.Match(2100,15,1,6));
    plage.SetPlage("08:00-20:30;*;*;Lu-Ve;19");
    assert(false==plage.Match(1200,15,1,0));
    assert(true==plage.Match(1200,15,1,1));
    assert(true==plage.Match(1200,15,1,3));
    assert(true==plage.Match(1200,15,1,5));
    assert(false==plage.Match(1200,15,1,6));
    plage.SetPlage("08:00-09:00,21:00-22:00;*;*;Sa,Di;22");
    assert(false==plage.Match(830,15,1,2));
    assert(true==plage.Match(830,15,1,0));
    assert(false==plage.Match(2130,15,1,3));
    assert(true==plage.Match(2130,15,1,6));
    assert(false==plage.Match(2130,15,1,7));
    plage.SetPlage("*;15-31;01-06;*;20");
    assert(false==plage.Match(830,14,2,2));
    assert(true==plage.Match(830,15,2,0));
    assert(false==plage.Match(2130,15,7,3));
    return true;
}
