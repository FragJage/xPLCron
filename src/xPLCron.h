#ifndef XPLCRON_H
#define XPLCRON_H

#include<list>
#include "Service/Service.h"
#include "xPLLib/xPLDevCfg.h"
#include "xPLLib/Extensions/AdvanceConfig.h"
#include "Chrono.h"

class xPLCron : public Service::IService, public xPL::AdvanceConfig::ICallBack
{
    public:
        xPLCron();
        ~xPLCron();

        void AdvanceConfigure();
        void ConfigChange(const std::string& device);
        void ConfigDelete(const std::string& device);
        void ConfigsDelete();

        void WakeUp(bool bForce);

		int ServiceStart(int argc, char* argv[]);
		void ServicePause(bool bPause);
		void ServiceStop();

    private:
        std::string GetValue();
        void SetValue(Chrono& chrono, const std::string& value);

        SimpleLog* m_Log;
        xPL::xPLDevCfg m_xPLDevice;
        xPL::AdvanceConfig m_AdvanceConfig;
        bool m_bServicePause;
        bool m_bServiceStop;
        std::list<Chrono> m_Chronos;
};

#endif // XPLCRON_H
