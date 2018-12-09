#define LOG_TAG "CalcService"
#include "CalcService.h"
#include <utils/Log.h>

namespace android{
	

	IMPLEMENT_META_INTERFACE(CalcService,"com.test.ICalcService");

	status_t BnCalcService::onTransact(uint32_t code,const Parcel & data,Parcel * reply,uint32_t flags)
	{
		LOGD("onTransact received request.");
		reply->writeInt32(0);
		switch(code)
		{
			case CALC_SUM:
			{
				LOGD("calc sum");
				CHECK_INTERFACE(ICalcService,data,reply);
				int32_t x = data.readInt32();
				int32_t y = data.readInt32();				
				int32_t sumxy = sum(x,y);				
				reply->writeInt32(sumxy);
				Parcel a;
				size_t parcel_position;
				parcel_position = a.dataPosition();
				a.writeInt32(5);
				a.setDataPosition(parcel_position);				
				return NO_ERROR;
			}
			case CALC_MINUS:
			{
				LOGD("calc minus");
				CHECK_INTERFACE(ICalcService,data,reply);
				int32_t x = data.readInt32();
				int32_t y = data.readInt32();
				int32_t minusxy = minus(x,y);
				reply->writeInt32(minusxy);
				return NO_ERROR;
					
			}
			case CALC_PAUSE:
			{
				LOGD("calc pause");
				CHECK_INTERFACE(ICalcService,data,reply);
				bool b = data.readInt32();
				bool b1 = pause(b);
				reply->writeInt32(b1);
				return NO_ERROR;
			}
			case CALC_START:
			{
				LOGD("calc start");
				CHECK_INTERFACE(ICalcService,data,reply);
				start();
				reply->writeInt32(true);
				return NO_ERROR;
			}
			case CALC_GET_STATE:
			{
				LOGD("calc pause");
				CHECK_INTERFACE(ICalcService,data,reply);				
				reply->writeInt32(getcalcstate());
				return NO_ERROR;
			}
			default:
			{
				return BBinder::onTransact(code,data,reply,flags);
			}
		}
	}
	CalcService::CalcService()
	{
		LOGD("constructor of CalcService.");
		m_calcstate = true;
	}

	CalcService::~ CalcService()
	{
		LOGD("destruct of CalcService");		
	}
	int32_t CalcService::sum(int32_t x, int32_t y)
	{
		return (x+y);
	}
	int32_t CalcService::minus(int32_t x, int32_t y)
	{
		return (x-y);
	}

	bool CalcService::start()
	{
		m_calcstate = true;
		return true;
	}

	bool CalcService::pause(bool b)
	{
		m_calcstate = false;
		return true;
	}

	bool CalcService::getcalcstate()
	{
		return m_calcstate;
	}

	void CalcService::instantiate()
	{
		LOGD("CalcService instantiate."); 
		LOGD("CalcService:ServiceManager: start\n");
		defaultServiceManager()->addService(String16("calcservice"),new android::CalcService());
	}
		

	

}
