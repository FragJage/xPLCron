#ifndef FRAG_CHRONO_H
#define FRAG_CHRONO_H

#include<list>
#include "xPLLib/Schemas/SchemaControl.h"
#include "Plage.h"


class Chrono
{
    public:
        Chrono(const std::string& name);
        Chrono(const std::string& name, const std::string& device, const std::string& type, const std::string& defaultValue, const std::string& plage1, const std::string& plage2, const std::string& plage3, const std::string& plage4, const std::string& plage5);
        ~Chrono();

        std::string GetName();
        std::string GetModuleName();
        std::string GetDeviceName();
        std::string GetDeviceType();
        void SetCron(const std::string& device, const std::string& type, const std::string& defaultValue, const std::string& plage1, const std::string& plage2, const std::string& plage3, const std::string& plage4, const std::string& plage5);
        std::string FindValue(int hour, int day, int month, int dayOfWeek);
        bool IsChange(const std::string& value);
        void SetValue(const std::string& value);

    private:
        bool m_Init;
        std::string m_Name;
        std::string m_DefaultValue;
        std::string m_CurrentValue;
        std::string m_CanonicDevice;
        std::string m_DeviceName;
        std::string m_ModuleName;
        std::string m_DeviceType;
        std::list<Plage> m_Plages;
};

#endif // FRAG_CHRONO_H
