#include <sstream>
#include <stdlib.h>
#include <stdexcept>
#include "Limit.h"
#include "StringTools/StringTools.h"

using namespace std;

Limit::Limit()
{
    m_All = false;
    m_Min = 0;
    m_Max = 0;
}

Limit::~Limit()
{
}

int Limit::StrToInt(const string& value)
{
    return atoi(value.c_str());
}

int Limit::TimeToInt(const string& value)
{
    size_t pos;
    string tmp;

    pos = value.find(":");
    if(pos == string::npos) throw logic_error("Unable to find ':' in the time range (expected hh:mm)");
    tmp = value.substr(0, pos)+value.substr(pos+1);
    return atoi(tmp.c_str());
}

int Limit::DayToInt(const string& value)
{
    if(StringTools::IsEqualCaseInsensitive(value, "0")) return 0;
    if(StringTools::IsEqualCaseInsensitive(value, "Di")) return 0;
    if(StringTools::IsEqualCaseInsensitive(value, "Su")) return 0;
    if(StringTools::IsEqualCaseInsensitive(value, "1")) return 1;
    if(StringTools::IsEqualCaseInsensitive(value, "Lu")) return 1;
    if(StringTools::IsEqualCaseInsensitive(value, "Mo")) return 1;
    if(StringTools::IsEqualCaseInsensitive(value, "2")) return 2;
    if(StringTools::IsEqualCaseInsensitive(value, "Ma")) return 2;
    if(StringTools::IsEqualCaseInsensitive(value, "Tu")) return 2;
    if(StringTools::IsEqualCaseInsensitive(value, "3")) return 3;
    if(StringTools::IsEqualCaseInsensitive(value, "Me")) return 3;
    if(StringTools::IsEqualCaseInsensitive(value, "We")) return 3;
    if(StringTools::IsEqualCaseInsensitive(value, "4")) return 4;
    if(StringTools::IsEqualCaseInsensitive(value, "Je")) return 4;
    if(StringTools::IsEqualCaseInsensitive(value, "Th")) return 4;
    if(StringTools::IsEqualCaseInsensitive(value, "5")) return 5;
    if(StringTools::IsEqualCaseInsensitive(value, "Ve")) return 5;
    if(StringTools::IsEqualCaseInsensitive(value, "Fr")) return 5;
    if(StringTools::IsEqualCaseInsensitive(value, "6")) return 6;
    if(StringTools::IsEqualCaseInsensitive(value, "Sa")) return 6;
    if(StringTools::IsEqualCaseInsensitive(value, "7")) return 0;

    ostringstream oss;
    oss << "unknown day '" << value << "' (expected Mo,Tu,We,Th,Fr,Sa,Su,Lu,Ma,Me,Je,Ve,Sa,Di,0,1,2,3,4,5,6,7=0)";

    throw logic_error(oss.str());
}

void Limit::SetLimit(const string& plage)
{
    SetLimitFunc(plage, &Limit::StrToInt);
}

void Limit::SetLimitTime(const string& plage)
{
    SetLimitFunc(plage, &Limit::TimeToInt);
}

void Limit::SetLimitDay(const string& plage)
{
    SetLimitFunc(plage, &Limit::DayToInt);
}

void Limit::SetLimitFunc(const string& plage, int (*convFunct)(const string&))
{
    size_t pos;

    if(plage=="*")
    {
        m_All = true;
        return;
    }

    m_All = false;
    pos = plage.find("-");
    if(pos==string::npos)
    {
        m_Min = convFunct(plage.c_str());
        m_Max = m_Min;
        return;
    }

    m_Min = convFunct(plage.substr(0, pos).c_str());
    m_Max = convFunct(plage.substr(pos+1).c_str());
}

bool Limit::Match(int value)
{
    if(m_All) return true;
    if(m_Max>=m_Min)        //Lu-Me, ou 11:00-12:00
    {
        if(value<m_Min) return false;
        if(value>m_Max) return false;
    }
    else                    //Sa-Lu, ou 22:00-02:00
    {
        if((value<m_Min)&&(value>m_Max)) return false;
    }

    return true;
}
