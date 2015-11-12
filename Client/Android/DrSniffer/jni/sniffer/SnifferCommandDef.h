/*
 * SnifferCommandDef.h
 *
 *  Created on: 2014年3月6日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#ifndef SNIFFERCOMMANDDEF_H_
#define SNIFFERCOMMANDDEF_H_

#pragma pack(1)

#include <string>
using namespace std;

/*
 * 命令类型
 */
typedef enum SnifferCommandType {
	SinfferTypeNone,
	SinfferTypeVersion,
	SinfferTypeVersionResult,
	SinfferTypeStart,
	SinfferTypeStop,
	ExcuteCommand,
	ExcuteCommandResult,
	SnifferTypeClientInfo,
	SnifferTypeClientInfoResult,
} SCMDT;

/*
 * 公用命令头
 */
typedef struct SnifferCommandHedaer {
	SCMDT scmdt;		// 类型
	int len;			// 参数长度
	int seq;			// 请求号
	bool bNew;			// 主动发起请求
} SCMDH;

/*
 * 命令
 */
typedef struct SnifferCommand {
	SCMDH header;			// 命令头
	char param[1024];		// 参数
} SCMD;

/*
 * Json协议定义
 */
#define PHONE_INFO_BRAND "phone_info_brand"
#define PHONE_INFO_MODEL "phone_info_model"
#define PHONE_INFO_NUMBER "phone_info_number"

#endif /* SNIFFERCOMMANDDEF_H_ */