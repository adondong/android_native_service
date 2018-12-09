#include "ICalcService.h"
#include "CalcService.h"
using namespace android;

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

int main(int argc, char **argv)
{
	sp<ProcessState> proc(ProcessState::self());
	sp<IServiceManager> sm = defaultServiceManager();
	LOGD("CalcService:%p",sm.get());
	android::CalcService::instantiate();
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
		
}
