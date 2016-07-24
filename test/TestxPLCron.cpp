#include "TestxPLCron.h"

using namespace std;

TestxPLCron::TestxPLCron() : TestClass("xPLCron", this)
{
	addTest("Start", &TestxPLCron::Start);
	addTest("StdConfig", &TestxPLCron::StdConfig);
	addTest("SetAdvConfig", &TestxPLCron::SetAdvConfig);
	addTest("Cron", &TestxPLCron::Cron);
	addTest("GetAdvConfig", &TestxPLCron::GetAdvConfig);
	addTest("ModifyAdvConfig", &TestxPLCron::ModifyAdvConfig);
	addTest("Stop", &TestxPLCron::Stop);
	addTest("ReStart", &TestxPLCron::ReStart);
	addTest("DelAdvConfig", &TestxPLCron::DelAdvConfig);
	addTest("ReStop", &TestxPLCron::ReStop);
}

TestxPLCron::~TestxPLCron()
{
}

void TestxPLCron::ThreadStart(xPLCron* pxPLDev)
{
    char exeName[] = "test";
    char confName[] = "config";
    char* argv[2];

    argv[0]= exeName;
    argv[1]= confName;
    pxPLDev->ServiceStart(2, argv);
}

bool TestxPLCron::Start()
{
    string msg;
    xPL::SchemaObject sch;

    remove("config");
    SetMockTime(2000, 1, 1, 12, 30, 0);

    thread integrationTest(ThreadStart, &xPLDev);
    integrationTest.detach();

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("xPL Cron"==sch.GetValue("appname"));

    return true;
}

bool TestxPLCron::StdConfig()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::SchemaObject schCfg(xPL::SchemaObject::cmnd, "config", "response");

    schCfg.SetValue("interval", "30");
    schCfg.SetValue("newconf", "test");
    msg = schCfg.ToMessage("fragxpl-test.default", "fragxpl-cron.default");
    ControlSockMock::SetNextRecv(msg);

    msg = ControlSockMock::GetLastSend(10);     //Pass Hbeat message
    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("30"==sch.GetValue("interval"));
    assert("fragxpl-cron.test"==sch.GetSource());

    return true;
}

bool TestxPLCron::SetAdvConfig()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::SchemaObject schSensor(xPL::ISchema::trig, "sensor", "basic");
    xPL::SchemaObject schAdvCfg(xPL::ISchema::cmnd, "advanceconfig", "request");

    schAdvCfg.SetValue("configname", "testdevice");
    schAdvCfg.SetValue("output", "fragxpl-owfs.default:lamp");
    schAdvCfg.SetValue("type", "Output");
    schAdvCfg.SetValue("defaultvalue", "Low");
    schAdvCfg.SetValue("plage1", "22:00-23:00;*;*;Lu-Ve;High");
    schAdvCfg.SetValue("plage2", "21:15-21:59;1-15;1-3;*;High");
    schAdvCfg.SetValue("plage3", "21:05-21:50;16-31;10-12;*;High");
    schAdvCfg.SetValue("plage4", "");
    schAdvCfg.SetValue("plage5", "");
    msg = schAdvCfg.ToMessage("fragxpl-test.default", "fragxpl-cron.test");
    ControlSockMock::SetNextRecv(msg);

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("control"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("output"==sch.GetValue("type"));
    assert("lamp"==sch.GetValue("device"));
    assert("low"==sch.GetValue("current"));

    return true;
}

bool TestxPLCron::Cron()
{
    string msg;
    xPL::SchemaObject sch;

    SetMockTime(2016, 7, 20, 22, 30, 0);
    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("control"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("lamp"==sch.GetValue("device"));
    assert("high"==sch.GetValue("current"));

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("hbeat"==sch.GetClass());
    assert("app"==sch.GetType());
    assert("xPL Cron"==sch.GetValue("appname"));

    return true;
}

bool TestxPLCron::GetAdvConfig()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::SchemaObject schAdvCfg(xPL::ISchema::cmnd, "advanceconfig", "current");

    schAdvCfg.SetValue("command", "request");
    schAdvCfg.SetValue("configname", "testdevice");
    msg = schAdvCfg.ToMessage("fragxpl-test.default", "fragxpl-cron.test");
    ControlSockMock::SetNextRecv(msg);

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("testdevice"==sch.GetValue("configname"));
    assert("fragxpl-owfs.default:lamp"==sch.GetValue("output"));
    assert("Low"==sch.GetValue("defaultvalue"));
    assert("22:00-23:00;*;*;Lu-Ve;High"==sch.GetValue("plage1"));
    assert("21:15-21:59;1-15;1-3;*;High"==sch.GetValue("plage2"));

    return true;
}

bool TestxPLCron::ModifyAdvConfig()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::SchemaObject schAdvCfgReq(xPL::ISchema::cmnd, "advanceconfig", "request");
    xPL::SchemaObject schAdvCfgCur(xPL::ISchema::cmnd, "advanceconfig", "current");

    schAdvCfgReq.SetValue("configname", "testdevice");
    schAdvCfgReq.SetValue("output", "fragxpl-owfs.default:lamp");
    schAdvCfgReq.SetValue("type", "output");
    schAdvCfgReq.SetValue("defaultvalue", "LOW");
    schAdvCfgReq.SetValue("plage1", "22:00-23:00;*;*;Lu-Ve;HIGH");
    schAdvCfgReq.SetValue("plage2", "21:15-21:59;1-15;1-3;*;HIGH");
    schAdvCfgReq.SetValue("plage3", "21:05-21:50;16-31;10-12;*;HIGH");
    schAdvCfgReq.SetValue("plage4", "20:00-20:15;2;2;*;HIGH");
    schAdvCfgReq.SetValue("plage5", "");
    msg = schAdvCfgReq.ToMessage("fragxpl-test.default", "fragxpl-cron.test");
    ControlSockMock::SetNextRecv(msg);
    msg = ControlSockMock::GetLastSend(10);     //Pass request state of device fragxpl-owfs.default:lamp

    schAdvCfgCur.SetValue("command", "request");
    schAdvCfgCur.SetValue("configname", "testdevice");
    msg = schAdvCfgCur.ToMessage("fragxpl-test.default", "fragxpl-cron.test");
    ControlSockMock::SetNextRecv(msg);

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("testdevice"==sch.GetValue("configname"));
    assert("fragxpl-owfs.default:lamp"==sch.GetValue("output"));
    assert("21:05-21:50;16-31;10-12;*;HIGH"==sch.GetValue("plage3"));
    assert("20:00-20:15;2;2;*;HIGH"==sch.GetValue("plage4"));

    return true;
}

bool TestxPLCron::Stop()
{
    string msg;
    xPL::SchemaObject sch;

    xPLDev.ServicePause(true);
    Plateforms::delay(800);
    xPLDev.ServicePause(false);
    xPLDev.ServiceStop();

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("hbeat"==sch.GetClass());
    assert("end"==sch.GetType());
    Plateforms::delay(200);
    return true;
}

bool TestxPLCron::ReStart()
{
    string msg;

    thread integrationTest(ThreadStart, &xPLDev);
    integrationTest.detach();

    msg = ControlSockMock::GetLastSend(10);     //Pass hbeat message
    msg = ControlSockMock::GetLastSend(10);     //Pass request current lamp
    return true;
}

bool TestxPLCron::DelAdvConfig()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::SchemaObject schAdvCfg(xPL::ISchema::cmnd, "advanceconfig", "current");

    schAdvCfg.SetValue("command", "delete");
    schAdvCfg.SetValue("configname", "testdevice");
    msg = schAdvCfg.ToMessage("fragxpl-test.default", "fragxpl-cron.test");
    ControlSockMock::SetNextRecv(msg);
    Plateforms::delay(500);

    schAdvCfg.ClearValues();
    schAdvCfg.SetValue("command", "delete");
    msg = schAdvCfg.ToMessage("fragxpl-test.default", "fragxpl-cron.test");
    ControlSockMock::SetNextRecv(msg);
    Plateforms::delay(500);

    msg = ControlSockMock::GetLastSend(10); //Pass message1
    msg = ControlSockMock::GetLastSend(10); //Pass message2
    msg = ControlSockMock::GetLastSend(10); //Pass message3

    return true;
}

bool TestxPLCron::ReStop()
{
    string msg;
    xPL::SchemaObject sch;

    xPLDev.ServiceStop();

    msg = ControlSockMock::GetLastSend(10);
    sch.Parse(msg);
    assert("hbeat"==sch.GetClass());
    assert("end"==sch.GetType());
    Plateforms::delay(200);

    remove("config");
    return true;
}

