#include <exception>
#include "UnitTest/UnitTest.h"
#include "TestLimit.h"
#include "TestPlage.h"
#include "TestChrono.h"
#include "TestxPLCron.h"

using namespace std;

int main()
{
    UnitTest unitTest;
    int ret = 0;


    try
    {
        unitTest.addTestClass(new TestLimit());
        unitTest.addTestClass(new TestPlage());
        unitTest.addTestClass(new TestChrono());
        unitTest.addTestClass(new TestxPLCron());
    }
    catch(const exception &e)
    {
        unitTest.displayError(e.what());
        ret = -1;
    }

    if(ret!=-1)
        if(!unitTest.run()) ret = 1;

	return ret;
}
