#include "Plateforms/Plateforms.h"
#include "xPLCron.h"
#include "xPLLib/xPLDevice.h"
#include "xPLLib/Schemas/SchemaControl.h"


using namespace std;

xPLCron::xPLCron() : m_AdvanceConfig(&m_xPLDevice)
{
    m_Log = m_xPLDevice.GetLogHandle();

    m_AdvanceConfig.AddFormat("configname", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("output", xPL::AdvanceConfig::ParamType::DEVICE, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("type", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::CONTROLTYPE);
    m_AdvanceConfig.AddFormat("defaultvalue", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("plage1", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("plage2", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("plage3", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("plage4", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("plage5", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.SetCallBack(this);
    m_xPLDevice.AddExtension(&m_AdvanceConfig);

    m_xPLDevice.Initialisation("fragxpl", "cron", "default");
    m_xPLDevice.SetAppName("xPL Cron", "1.1.0.0");
    m_xPLDevice.SetAnswerAllMsg(true);
    m_bServicePause = false;
    m_bServiceStop = false;
}

xPLCron::~xPLCron()
{
    ConfigsDelete();
}

void xPLCron::SetValue(Chrono& chrono, const string& value)
{
    xPL::SchemaControlBasic sendCmnd;
    string moduleName;
    string deviceName;
    string deviceType;


  	LOG_ENTER;

    moduleName = chrono.GetModuleName();
    deviceName = chrono.GetDeviceName();
    deviceType = chrono.GetDeviceType();

    chrono.SetValue(value);
    sendCmnd.SetDeviceType(deviceType);
    sendCmnd.SetDeviceName(deviceName);
    sendCmnd.SetCurrent(value);

    LOG_VERBOSE(m_Log) << "Send " << value << " to " << moduleName << " device " << deviceName;
    m_xPLDevice.SendMessage(&sendCmnd, moduleName);

   	LOG_EXIT_OK;
}

void xPLCron::WakeUp(bool bForce)
{
	time_t timeNow = time((time_t*)0);
	static time_t lastRefresh = 0;
    struct tm * t;
	int hour;
    list<Chrono>::iterator it;
    list<Chrono>::const_iterator itEnd;
    string value;


	if((!bForce)&&(timeNow-lastRefresh<60)) return;
	lastRefresh = timeNow;

  	LOG_ENTER;

	//Calcul jour et heure actuel
    t = localtime(&timeNow);
	hour = t->tm_hour*100+t->tm_min;

    //Parcourir les chronos
    itEnd = m_Chronos.end();
    for(it=m_Chronos.begin(); it!=itEnd; ++it)
	{
	    value = it->FindValue(hour, t->tm_mday, t->tm_mon, t->tm_wday);

		if(it->IsChange(value))
		    SetValue(*it, value);
	}

   	LOG_EXIT_OK;
}

void xPLCron::ConfigsDelete()
{
    m_Chronos.clear();
}

void xPLCron::ConfigDelete(const std::string& configName)
{
    list<Chrono>::iterator it;

    for(it=m_Chronos.begin(); it!=m_Chronos.end(); ++it)
    {
        if(it->GetName()==configName)
        {
            m_Chronos.erase(it);
            return;
        }
    }
}

void xPLCron::ConfigChange(const std::string& configName)
{
    list<Chrono>::iterator it;
    map<string, string>* config;
    string name;
    string output;
    string type;
    string defValue;
    string plage1, plage2, plage3, plage4, plage5;
    bool bFind = false;


    config = m_AdvanceConfig.GetConfig(configName);
    name    = (*config)["configname"];
    output  = (*config)["output"];
    type    = (*config)["type"];
    defValue= (*config)["defaultvalue"];
    plage1  = (*config)["plage1"];
    plage2  = (*config)["plage2"];
    plage3  = (*config)["plage3"];
    plage4  = (*config)["plage4"];
    plage5  = (*config)["plage5"];

    for(it=m_Chronos.begin(); it!=m_Chronos.end(); ++it)
    {
        if(it->GetName()==configName)
        {
            it->SetCron(output, type, defValue, plage1, plage2, plage3, plage4, plage5);
            bFind = true;
            break;
        }
    }

    if(!bFind)
        m_Chronos.emplace_back(name, output, type, defValue, plage1, plage2, plage3, plage4, plage5);

    WakeUp(true);
}

void xPLCron::AdvanceConfigure()
{
    int i, nb;

    LOG_ENTER;

    ConfigsDelete();

    nb = m_AdvanceConfig.GetNbConfig();
    for(i=0; i<nb; i++)
    {
        std::map<std::string, std::string>* config;
        string name;
        string output;
        string type;
        string defValue;
        string plage1, plage2, plage3, plage4, plage5;


        config = m_AdvanceConfig.GetConfig(i);

        name    = (*config)["configname"];
        output  = (*config)["output"];
        type    = (*config)["type"];
        defValue= (*config)["defaultvalue"];
        plage1  = (*config)["plage1"];
        plage2  = (*config)["plage2"];
        plage3  = (*config)["plage3"];
        plage4  = (*config)["plage4"];
        plage5  = (*config)["plage5"];

        LOG_VERBOSE(m_Log) << "Create " << name <<" : "<< output <<"("<< type <<") = "<< defValue << " " << plage1 << plage2 << plage3 << plage4 << plage5;
        try
        {
            m_Chronos.emplace_back(name, output, type, defValue, plage1, plage2, plage3, plage4, plage5);
        }
        catch(string e)
        {
            LOG_WARNING(m_Log) << "Bad cron format (" << e << ")";
        }
    }

    WakeUp(true);

	LOG_EXIT_OK;
}

int xPLCron::ServiceStart(int argc, char* argv[])
{
    m_bServiceStop = false;
    if(argc > 1) m_xPLDevice.SetConfigFileName(argv[1]);
    m_xPLDevice.Open();

    while(!m_bServiceStop)
    {
        if(m_bServicePause)
            Plateforms::delay(500);
        else
        {
            m_xPLDevice.WaitRecv(500);
            WakeUp(false);
        }
    }

    m_xPLDevice.Close();
    return 0;
}

void xPLCron::ServicePause(bool bPause)
{
    m_bServicePause = bPause;
}

void xPLCron::ServiceStop()
{
    m_bServiceStop = true;
}
