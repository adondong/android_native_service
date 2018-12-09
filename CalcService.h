#ifndef _CALC_SERVICE_H
#define _CALC_SERVICE_H

#include <utils/Log.h>
#include "ICalcService.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)


namespace android{

	class BnCalcService : public BnInterface<ICalcService>{
		public:
			virtual status_t onTransact(uint32_t code,const Parcel & data,Parcel * reply,uint32_t flags);
	};

	class CalcService : public BnCalcService{
		private:
			bool m_calcstate;
		public:
			CalcService();
			~CalcService();
			virtual int32_t sum(int32_t x, int32_t y);
			virtual int32_t minus(int32_t x, int32_t y); 
			virtual bool sendBuffer(byte []);
            static void instantiate();
	};	

	class BpCalcService : public BpInterface<ICalcService>{
		public:
		BpCalcService(const sp<IBinder>& impl) : BpInterface<ICalcService>(impl)
		{
		}
		virtual int32_t sum(int32_t x, int32_t y)
		{
			LOGD("BpCalcService sum. %d,%d",x,y);
			Parcel data, reply;		
			data.writeInterfaceToken(ICalcService::getInterfaceDescriptor());		
			data.writeInt32(x);
			data.writeInt32(y);
			remote()->transact(CALC_SUM,data,&reply,0);
			reply.readInt32();
			int32_t sumxy = reply.readInt32();  
         	ALOGD("BpCalcService sumxy=%d",sumxy);
         	return sumxy;
		}

		virtual int32_t minus(int32_t x, int32_t y)
		{
			LOGD("BpCalcService minus.");
			Parcel data, reply;
			data.writeInterfaceToken(ICalcService::getInterfaceDescriptor());
			data.writeInt32(x);
			data.writeInt32(y);			
			remote()->transact(CALC_MINUS,data,&reply);
			int32_t mxy = reply.readInt32();
			LOGD("minuxs = %d",mxy);
			return mxy;
		}

		virtual bool sendBuffer(byte byBuffer[]){
			LOGD("BpCalcService send buffer !");
			Parcel data, reply;
			data.writeInterfaceToken(ICalcService::getInterfaceDescriptor());
			data.writeInt32Array(10,byBuffer);
			remote()->transact(SEND_BUFFER,data,&reply);
		}

		
	};
}

#endif
