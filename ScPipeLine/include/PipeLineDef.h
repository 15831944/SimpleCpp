
#ifndef PIPELINE_H
#define PIPELINE_H
/*
* �ܵ���ˮ�߿⣬������һ���������ݣ���װ��ͬ��filter
*/
#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

#define debug(format, ...)	do{ \
	char szMsg[4096];\
	memset(szMsg, 0, sizeof(szMsg));\
	sprintf(szMsg, format, __VA_ARGS__);\
	OutputDebugStringA(szMsg);  \
}while (0);

namespace PipeLine{
// 	typedef long long int64;
// 	typedef long long int64_t;
}
#endif