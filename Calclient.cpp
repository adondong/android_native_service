#include <stdio.h>
#include <utils/Log.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

namespace android
{
	const String16 WIFI_DESCRIPTOR("com.test.ICalcService");
	class ICalcService : public IInterface{

		public:
		//	DECLARE_META_INTERFACE(CalcService)			
			virtual bool sendBuffer(uint8_t byBuffer[],int32_t size,int64_t time) = 0;
		protected:
			enum{
				SEND_BUFFER = IBinder :: FIRST_CALL_TRANSACTION,					
			};
		
	};

	class BpCalcService : public BpInterface<ICalcService>{
		public:
		BpCalcService(const sp<IBinder>& impl) : BpInterface<ICalcService>(impl)
		{
		}		

		virtual bool sendBuffer(uint8_t byBuffer [],int32_t size,int64_t time)
		{
			LOGD("BpCalcService send buffer ");
			Parcel data, reply;
			data.writeInterfaceToken(WIFI_DESCRIPTOR);
			data.writeInt32(size);
			void* dest = data.writeInplace(size);
			memcpy(dest,byBuffer,size);
			data.writeInt64(time);
			remote()->transact(SEND_BUFFER,data,&reply);
			reply.readInt32();
			int32_t result = reply.readInt32();			
			return result;
		}

		
	};
}

using namespace android;
int main()
{
	
	sp<IServiceManager> sm = defaultServiceManager();
	sp<BpCalcService> client;
    sp<IBinder> b = sm->getService(String16("CalcService"));
    
    if (b == NULL)
    {
    ALOGW("Can't find binder service \"com.test.CalcService\"");
    return -1;
    }
	client = new BpCalcService(b);
	int size = 101;
	uint8_t arr[size];
	for(int j=0;j<size;j++){
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

