#ifndef _ICALC_SERVICE_H
#define _ICALC_SERVICE_H

#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>


namespace android{

 
	class ICalcService : public IInterface{

		public:
			DECLARE_META_INTERFACE(CalcService);
			virtual int32_t sum(int32_t x, int32_t y) = 0;
			virtual int32_t minus(int32_t x, int32_t y) = 0;
			virtual bool sendBuffer(byte byBuffer[]) = 0;
		protected:
			enum{
				CALC_SUM = IBinder :: FIRST_CALL_TRANSACTION,
					CALC_MINUS,
					SEND_BUFFER
			};
		
	};

}
#endif
