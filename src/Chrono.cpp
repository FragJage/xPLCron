#include <stdexcept>
#include "Chrono.h"

using namespace std;

Chrono::Chrono(const string& name)
{
    m_Name = name;
    m_Init = false;
}

Chrono::Chrono(const string& name, const string& device, const string& type, const string& defaultValue, const string& plage1, const string& plage2, const string& plage3, const string& plage4, const string& plage5)
{
    m_Name = name;
    m_Init = false;
    SetCron(device, type, defaultValue, plage1, plage2, plage3, plage4, plage5);
}

Chrono::~Chrono()
{
    m_Plages.clear();
}

string Chrono::GetName()
{
    return m_Name;
}

std::string Chrono::GetModuleName()
{
    return m_ModuleName;
}

std::string Chrono::GetDeviceName()
{
    return m_DeviceName;
}

std::string Chrono::GetDeviceType()
{
    return m_DeviceType;
}

string Chrono::FindValue(int hour, int day, int month, int dayOfWeek)
{
    list<Plage>::iterator it;
    list<Plage>::const_iterator itEnd;

    itEnd = m_Plages.end();
    for(it=m_Plages.begin(); it!=itEnd; ++it)
    {
        if(it->Match(hour, day, month, dayOfWeek)) return it->GetValue();
    }
    return m_DefaultValue;
}

bool Chrono::IsChange(const string& value)
{
    if(!m_Init) return true;
    if(value!=m_CurrentValue) return true;

    return false;
}

void Chrono::SetValue(const string& value)
{
    m_Init = true;
    m_CurrentValue = value;
}

void Chrono::SetCron(const string& device, const string& type, const string& defaultValue, const string& plage1, const string& plage2, const string& plage3, const string& plage4, const string& plage5)
{
    size_t pos;


    m_DefaultValue = defaultValue;

    m_CanonicDevice = device;
    pos = m_CanonicDevice.find(":");
    if(pos==string::npos) throw logic_error("The device name must be in the form vendor-module.instance:device");
    m_ModuleName = m_CanonicDevice.substr(0, pos);
    m_DeviceName = m_CanonicDevice.substr(pos+1);
    m_DeviceType = type;
    m_Init = false;

    if(plage1!="") m_Plages.emplace_back(plage1);
    if(plage2!="") m_Plages.emplace_back(plage2);
    if(plage3!="") m_Plages.emplace_back(plage3);
    if(plage4!="") m_Plages.emplace_back(plage4);
    if(plage5!="") m_Plages.emplace_back(plage5);
}
