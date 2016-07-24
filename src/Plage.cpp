#include <stdexcept>
#include "Plage.h"

using namespace std;

Plage::Plage()
{
}

Plage::Plage(const string& plage)
{
    SetPlage(plage);
}

void Plage::SetPlage(const std::string& plage)
{
    size_t posDeb;
    size_t posFin;

    /* Ex : 07:00-08:00,20:30-21:30;*;*;Lu,Ma,Me,Je,Ve;22			*/
    /*		08:00-20:30;*;*;Lu-Ve;19								*/
    /*		08:00-09:00,21:00-22:00;*;*;Sa,Di;22					*/
    /*		09:00-21:00;*;*;Sa,Di;19								*/
    /*		09:00-21:00;*;*;*;20									*/
    /*		09:00-10:00,20:00-21:00;*;*;Lu-Ma,Je-Ve;20				*/
    /*		23:59;31;12;*;20				                        */
    /*		*;15-31;01-06;*;20				                        */

    posDeb = 0;
    posFin = plage.find(";");
    if(posFin==string::npos) throw logic_error("Invalid range, no ; for time");
    m_Time = ParseLimits(plage.substr(posDeb,posFin-posDeb), TIME);

    posDeb = posFin+1;
    posFin = plage.find(";", posDeb);
    if(posFin==string::npos) throw logic_error("Invalid range, no ; for day of month");
    m_DayOfMonth = ParseLimits(plage.substr(posDeb,posFin-posDeb), STANDARD);

    posDeb = posFin+1;
    posFin = plage.find(";", posDeb);
    if(posFin==string::npos) throw logic_error("Invalid range, no ; for month");
    m_Month = ParseLimits(plage.substr(posDeb,posFin-posDeb), STANDARD);

    posDeb = posFin+1;
    posFin = plage.find(";", posDeb);
    if(posFin==string::npos) throw logic_error("Invalid range, no ; for day of week");
    m_DayOfWeek = ParseLimits(plage.substr(posDeb,posFin-posDeb), DAY);

    m_Value = plage.substr(posFin+1);
}

Plage::~Plage()
{
}

string Plage::GetValue()
{
    return m_Value;
}

bool Plage::Match(int hour, int day, int month, int dayOfWeek)
{
    if(!MatchLimits(m_Time, hour)) return false;
    if(!MatchLimits(m_DayOfMonth, day)) return false;
    if(!MatchLimits(m_Month, month)) return false;
    if(!MatchLimits(m_DayOfWeek, dayOfWeek)) return false;
    return true;
}

bool Plage::MatchLimits(list<Limit> limits, int value)
{
    list<Limit>::iterator it;
    list<Limit>::const_iterator itEnd;

    itEnd = limits.end();
    for(it=limits.begin(); it!=itEnd; ++it)
    {
        if(it->Match(value)) return true;
    }
    return false;
}

list<Limit> Plage::ParseLimits(const string& plage, LimitKind limitKind)
{
    size_t posDeb;
    size_t posFin;
    list<Limit> limits;
    Limit limit;
    string strLimit;


    posDeb = 0;
    do
    {
        posFin = plage.find(",", posDeb);

        if(posFin==string::npos)
        {
            strLimit = plage.substr(posDeb);
        }
        else
        {
            strLimit = plage.substr(posDeb, posFin-posDeb);
            posDeb=posFin+1;
        }

        switch(limitKind)
        {
            case STANDARD :
                limit.SetLimit(strLimit);
                break;
            case TIME :
                limit.SetLimitTime(strLimit);
                break;
            case DAY :
                limit.SetLimitDay(strLimit);
                break;
        }
        limits.push_back(limit);
    } while(posFin!=string::npos);

    return limits;
}
