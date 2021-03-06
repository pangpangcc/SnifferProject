/*
 * SnifferCommandDef.h
 *
 *  Created on: 2014年3月6日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#ifndef SNIFFERCOMMANDDEF_H_
#define SNIFFERCOMMANDDEF_H_

#pragma pack(push,1)

#define MAX_PARAM_LEN 4096

/*
 * 命令类型
 */
typedef enum SnifferCommandType {
	SinfferTypeNone = 0,
	SinfferTypeStart,
	SinfferTypeStop,
	ExcuteCommand,
	SnifferTypeClientInfo,
	SnifferListDir,
	SnifferUploadFile,
	SnifferDownloadFile,
	SnifferCheckUpdate,
	SnifferScreenCapUpdate,
} SCMDT;

/*
 * 公用命令头
 */
typedef struct SnifferCommandHedaer {
	SnifferCommandHedaer() {
		scmdt = SinfferTypeNone;
		len = 0;
		seq = 0;
		bNew = false;
	}

	SnifferCommandHedaer(const SnifferCommandHedaer& item) {
		scmdt = item.scmdt;
		len = item.len;
		seq = item.seq;
		bNew = item.bNew;
	}

	SnifferCommandHedaer operator=(const SnifferCommandHedaer& item) {
		scmdt = item.scmdt;
		len = item.len;
		seq = item.seq;
		bNew = item.bNew;
		return *this;
	}

	SCMDT scmdt;		// 类型
	int len;			// 参数长度
	int seq;			// 请求号
	bool bNew;			// 主动发起请求
} SCMDH;

/*
 * 命令
 */
typedef struct SnifferCommand {
	SCMDH header;					// 命令头
	char param[MAX_PARAM_LEN];		// 参数
} SCMD;

typedef enum ProtocolType {
	HTML,
	JSON,
} PROTOCOLTYPE;

/**
 * 所有服务公共定义
 */

#define COMMON_PROTOCOL_TYPE			"TYPE"
#define COMMON_PROTOCOL_TYPE_JSON		"JSON"
#define URL								"URL"
#define FILENAME						"FILENAME"
#define FILEPATH						"FILEPATH"

/*
 * 客户端服务协议定义
 */
#define COMMON_RET						"RET"
#define COMMON_TOTAL 					"TOTAL"
#define COMMON_PAGE_INDEX 				"PAGEINDEX"
#define COMMON_PAGE_SIZE 				"PAGESIZE"

/**
 * 管理者服务器协议定义
 */
/**
 * 重新加载配置
 */
#define RELOAD					"RELOAD"

/**
 * 获取在线列表
 */
#define GET_CLIENT_LIST			"GET_CLIENT_LIST"
#define CLIENT_LIST				"CLIENT_LIST"
#define CLIENT_ID				"CLIENT_ID"

/**
 * 获取在线详细信息
 */
#define GET_CLIENT_INFO			"GET_CLIENT_INFO"
#define CLIENT_INFO				"CLIENT_INFO"
#define DEVICE_ID				"DEVICE_ID"
#define VERSION					"VERSION"
#define CWD 					"CWD"
#define PHONE_INFO_BRAND 		"PHONE_INFO_BRAND"
#define PHONE_INFO_MODEL 		"PHONE_INFO_MODEL"
#define PHONE_INFO_ABI 			"PHONE_INFO_ABI"
#define PHONE_INFO_NUMBER 		"PHONE_INFO_NUMBER"
#define IS_ROOT 				"IS_ROOT"

/**
 * 执行客户端命令
 */
#define SET_CLIENT_CMD			"SET_CLIENT_CMD"
#define COMMAND					"COMMAND"

/**
 * 获取客户端目录
 */
#define GET_CLIENT_DIR			"GET_CLIENT_DIR"
#define DIRECTORY				"DIRECTORY"
#define FILE_LIST				"FILE_LIST"
#define D_NAME					"N"
#define D_TYPE					"T"
#define D_SIZE					"S"
#define D_MODE					"M"

/**
 * 上传客户端文件到服务器
 */
#define UPLOAD_CLIENT_FILE		"UPLOAD_CLIENT_FILE"

/*
 * 文件服务器协议
 */
#define FILEPATH_LOWER			"filepath"
#define UPLOAD_SERVER_FILE		"upload.cgi"
#define UPLOAD_FILE_LOWER		"upload_file"
#define UPLOAD_DIR_LOWER		"upload_dir"
#define DEVICE_ID_LOWER			"device_id"


#define DOWN_SERVER_FILE		"download.cgi"
#define DOWN_SERVER_ADDRESS		"SERVER_ADDRESS"

/**
 * 下载文件到客户端
 */
#define DOWNLOAD_CLIENT_FILE	"DOWNLOAD_CLIENT_FILE"

/**
 * 踢掉客户端
 */
#define KICK_CLIENT				"KICK_CLIENT"

/**
 * 更新客户端
 */
#define UPDATE_CLIENT					"UPDATE_CLIENT"
#define CLIENT_UPDATE_URL				"URL"
#define CLIENT_UPDATE_VERSION			"VERSION"

/**
 * 客户端截屏
 */
#define SCREENCAP_CLIENT				"SCREENCAP_CLIENT"
#define CLIENT_SCREENCAP_URL			"URL"

#pragma pack(pop)

#endif /* SNIFFERCOMMANDDEF_H_ */
