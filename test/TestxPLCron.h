#include <cassert>
#include <thread>
#include "xPLLib/Schemas/SchemaObject.h"
#include "Plateforms/Plateforms.h"
#include "UnitTest/UnitTest.h"
#ifdef WIN32
    #include "Thread/mingw.thread.h"
#else
    #include <thread>
#endif
#include "../src/xPLCron.h"
#include "ControlSockMock.h"
#include "TimeMock.h"


class TestxPLCron : public TestClass<TestxPLCron>
{
public:
    TestxPLCron();
    ~TestxPLCron();
    static void ThreadStart(xPLCron* pxPLDev);
    bool Start();
    bool StdConfig();
    bool SetAdvConfig();
    bool Cron();
    bool GetAdvConfig();
    bool ModifyAdvConfig();
    bool Stop();
    bool ReStart();
    bool DelAdvConfig();
    bool ReStop();
    xPLCron xPLDev;
};
