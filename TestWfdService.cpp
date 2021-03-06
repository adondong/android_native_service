#include <stdio.h>
#include <utils/Log.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <WfdService.h>
//#include "CalcService.h"
//using namespace std;
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
//#define DATA_LEN 100

/*
namespace android
{
	const String16 WFD_DESCRIPTOR("com.nforetek.IWfdService");
	class IWfdService : public IInterface{

		public:
		//	DECLARE_META_INTERFACE(CalcService);			
			virtual bool sendBuffer(uint8_t byBuffer[],size_t size,int64_t timeUs) = 0;
		protected:
			enum{
				SEND_BUFFER = IBinder :: FIRST_CALL_TRANSACTION	+ 0,				
			};
		
	};

	//IMPLEMENT_META_INTERFACE(ICalcService,"com.test.ICalcService");
	class BpWfdService : public BpInterface<IWfdService>{
		public:
		BpWfdService(const sp<IBinder>& impl) : BpInterface<IWfdService>(impl)
		{
		}

		virtual bool sendBuffer(uint8_t byBuffer [],int32_t size,int64_t time)
		{
			LOGD("BpCalcService send buffer ");
			Parcel data, reply;
			data.writeInterfaceToken(WFD_DESCRIPTOR);
		//	data.writeInt32Array(DATA_LEN,&byBuffer);
			//data.writeCString(byBuffer);
			data.writeInt32(size);
			void* dest = data.writeInplace(size);
			memcpy(dest,byBuffer,size);
			data.writeInt64(time);
	//		data.setData(byBuffer,DATA_LEN);
			remote()->transact(SEND_BUFFER,data,&reply);
			reply.readInt32();
			int32_t result = reply.readInt32();
			return result;
		}

		
	};
}

*/

//IMPLEMENT_META_INTERFACE(CalcService,"com.test.ICalcService");

using namespace android;
int main()
{
	
	sp<IServiceManager> sm = defaultServiceManager();
	sp<BpWfdService> client;
    sp<IBinder> b = sm->getService(String16("wfdservice")); //Context.MCU_SERVICE
    
    if (b == NULL)
    {
    ALOGW("Can't find binder service \"com.test.CalcService\"");
    return -1;
    }
	client = new BpWfdService(b);
	//int32_t sum = client->sum(12,2);
	//LOGD("calc sum %d",sum);
	size_t size = 3100000;
	uint8_t arr[size];
	for(size_t j=0;j<size;j++){
		arr[j]=j+1;
	}
	client->sendBuffer(arr,size,2222222222);
	int i = 0;
	while(1)
	{
		scanf("%d",&i);
		if(i)
		{
			break;
		}
	}
	return 0;
}

