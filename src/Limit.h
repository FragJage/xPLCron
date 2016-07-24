#ifndef FRAG_LIMIT_H
#define FRAG_LIMIT_H

#include<string>
#include<list>

class Limit
{
    public:
        Limit();
        ~Limit();
        void SetLimit(const std::string& plage);
        void SetLimitTime(const std::string& plage);
        void SetLimitDay(const std::string& plage);
        bool Match(int value);

    private:
        void SetLimitFunc(const std::string& plage, int (*convFunct)(const std::string&));
        static int StrToInt(const std::string& value);
        static int TimeToInt(const std::string& value);
        static int DayToInt(const std::string& value);

        int m_Min;
        int m_Max;
        bool m_All;
};

#endif // FRAG_LIMIT_H
