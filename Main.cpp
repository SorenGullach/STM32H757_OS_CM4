
#include <MemoryDefs.h>
#include <StartupSemafor.h>

#include <../STM32H757_OS/SharedData/SharedData.h>

#include <PWR.h>
#include <stdio.h>
#include <stdint.h>
	
hwPWR PWRControl;
hwHSEMControl HSEMControl;

// this class receives notifications when CM7 have made something
class HSEMTest : hwHSEMControl
{
public:
	HSEMTest()
		: hwHSEMControl(1, &InterCommunication) // register shared object(s) to get notified from
	{
	}
	
	virtual void ModifiedNotified(hwHSEMBase *data) override
	{
		if (data == &InterCommunication)
		{
			Printf("CM4 Notification\n");
			bool access = false;
			while (!access) access = InterCommunication.Take(0);
			if (access)
			{
				Printf("CM4 CounterCM7 = %ld\n", InterCommunication.CounterCM7);
				InterCommunication.CounterCM4 = InterCommunication.CounterCM7;
				InterCommunication.Release(0, true);
			}
			else
				Printf("CM4 failed\n");

			
		}
	}
 
};

int main()
{
	Printf("Waiting for CM7\n");
	WaitForCM7();
	Printf("CM7 released CM4\n");

	// init HW
	Printf("HW Init CM4\n");
	hwHSEMControl::Init(); // powerup HSEM
	
	Printf("HW Init done CM4\n");
	
	HSEMTest Test;
	
	uint32_t var = 3;
	
	Printf("Running %lu\n", var);
	while (1)
	{
		var++;
	}
}

