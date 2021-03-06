/*
 * DownloadClientFileTask.cpp
 *
 *  Created on: 2015-11-25
 *      Author: Max
 */

#include "DownloadClientFileTask.h"

DownloadClientFileTask::DownloadClientFileTask() {
	// TODO Auto-generated constructor stub
	mClientId = 0;
	mUrl = "";
	mFilePath = "";
}

DownloadClientFileTask::~DownloadClientFileTask() {
	// TODO Auto-generated destructor stub
}

void DownloadClientFileTask::GetSendCmd(SCMD* scmd, int seq) {
	Json::FastWriter writer;
	Json::Value rootSend;
	string result = "";

	rootSend[URL] = mUrl;
	rootSend[FILEPATH] = mFilePath;

	result = writer.write(rootSend);

	scmd->header.scmdt = SnifferDownloadFile;
	scmd->header.bNew = true;
	scmd->header.seq = seq;
	scmd->header.len = (int)result.length();
	memcpy(scmd->param, result.c_str(), scmd->header.len);
}

bool DownloadClientFileTask::GetReturnData(SCMD* scmd, char* buffer, int& len) {
	bool bFlag = false;

	if( buffer != NULL ) {
		switch( mPtType ) {
		case HTML: {
			string result = "<html><head><title>客户端管理页面</title><meta http-equiv='Content-Type' content='text/html; charset=utf-8' /></head><body>";
			result += "<pre>";

			char Download[512];

		    Json::Reader reader;
		    Json::Value rootRecv;
		    reader.parse(scmd->param, rootRecv);

		    bool bFlag = false;
		    if( rootRecv[COMMON_RET].isInt() ) {
		    	bFlag = (0 == rootRecv[COMMON_RET].asInt())?false:true;
		    }
		    result += bFlag?"下载成功":"下载失败";
		    result += ",";

		    result += "已下载到: ";
		    if( rootRecv[FILEPATH].isString() ) {
		    	result += rootRecv[FILEPATH].asString();
		    }

		    result += "</pre>";
		    result += "</body></html>";

			snprintf(
					buffer,
					MAX_BUFFER_LEN - 1,
					"%s",
					result.c_str()
					);

			len = strlen(buffer);

		}break;
		case JSON:{
			memcpy(buffer, scmd->param, scmd->header.len);
			len = scmd->header.len;
		}break;
		}

		bFlag = true;
	}

	return bFlag;
}

void DownloadClientFileTask::SetClientId(int clientId) {
	mClientId = clientId;
}

void DownloadClientFileTask::SetUrl(const string& url) {
	mUrl = url;
}

void DownloadClientFileTask::SetFilePath(const string& filePath) {
	mFilePath = filePath;
}
