#include <iostream>
#include <exception>
#include "xPLCron.h"

int main(int argc, char* argv[])
{
  int res = 0;

  try
  {
    xPLCron xPLDev;

  	Service* pService = Service::Create("xPLCron", "Cron for xPL protocol", &xPLDev);
  	res = pService->Start(argc, argv);
  	Service::Destroy();
  }
  catch(const exception &e)
  {
      std::cout << e.what();
  }
	return res;
}
