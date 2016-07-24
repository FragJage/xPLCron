#ifndef FRAG_PLAGE_H
#define FRAG_PLAGE_H

#include<list>
#include "Limit.h"

class Plage
{
    public:
        Plage();
        Plage(const std::string& plage);
        ~Plage();
        void SetPlage(const std::string& plage);
        std::string GetValue();
        bool Match(int hour, int day, int month, int dayOfWeek);

    private:
        enum LimitKind {STANDARD, DAY, TIME};
        std::list<Limit> ParseLimits(const std::string& plage, LimitKind limitKind);
        bool MatchLimits(std::list<Limit> limits, int value);
        std::string m_Value;
        std::list<Limit> m_Time;
        std::list<Limit> m_DayOfMonth;
        std::list<Limit> m_Month;
        std::list<Limit> m_DayOfWeek;
};

#endif // FRAG_PLAGE_H
