/*
 * SnifferInstaller.h
 *
 *  Created on: 2014年3月17日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#ifndef SNIFFERINSTALLER_H_
#define SNIFFERINSTALLER_H_

#include "SinfferExecuteDef.h"

#include <common/KLog.h>

/*
 * 查看Sniffer版本
 * 用于检测Sniffer是否存在
 */
static inline string GetSnifferVersion() {
	string version = "";

	string suCommand = SinfferFile;
	suCommand += " -v";

	string result = "";
	result = SystemComandExecuteWithResult(suCommand);

	string::size_type posStart = 0;
	string::size_type posEnd = string::npos;
	int iLen = 0;

	if(result.length() > 0) {
		string::size_type pos = result.find(SinfferVersionString);
		if(string::npos != pos) {
			ILog("SnifferInstaller::GetSnifferVersion()", "已经安装%s!", SinfferFile);
			pos += strlen(SinfferVersionString);
			posStart = pos;

			posEnd = result.find(' ', posStart);
			if(string::npos != posEnd) {
				iLen = posEnd - posStart;
			}
			else {
				iLen = result.length() - posStart - 1;
			}
			version = result.substr(posStart, iLen);
			ILog("SnifferInstaller::GetSnifferVersion()", "%s版本为%s", SinfferFile, version.c_str());
		}
		else {
			ILog("SnifferInstaller::GetSnifferVersion()", "还没安装%s", SinfferFile);
		}
	}
	else {
		ILog("SnifferInstaller::GetSnifferVersion()", "还没安装%s", SinfferFile);
	}

	return version;
}

/*
 * 释放AutoStartScript到指定路径
 */
static inline string ReleaseAutoStartScript(string filePath = "/sdcard/") {
	string result = "";

	if(filePath.find_last_of('/') != filePath.length() - 1) {
		filePath += "/";
	}

	filePath += AutoStartScriptFile;
	ILog("SnifferInstaller::ReleaseAutoStartScript()", "准备释放释放AutoStartScript到:%s", filePath.c_str());

	FILE* file = fopen(filePath.c_str(), "wb+");
	if(NULL != file) {
		char *p = (char *)AutoStartScript;
		int iLen = sizeof(AutoStartScript);
		ILog("SnifferInstaller::ReleaseAutoStartScript()", "文件大小:(%d)byte", iLen);
		int iWrite = 0;
		do {
			int iNeedWrite = (4096 > iLen)?iLen:4096;
			iWrite = fwrite(p, 1, iNeedWrite, file);
			if(iWrite > 0) {
				p += iWrite;
				iLen -= iWrite;
			}
		}while(iLen > 0);
		fclose(file);
		result = filePath;
		ILog("SnifferInstaller::ReleaseAutoStartScript()", "释放AutoStartScript到%s成功!", filePath.c_str());
	}
	else {
		ELog("SnifferInstaller::ReleaseAutoStartScript()", "释放AutoStartScript到%s失败!", filePath.c_str());
	}

	return result;
}

/*
 * 完整安装Sniffer
 * packageName:	安装器包名, 如com.com.drsnifferinstaller
 * filePath: 临时可写路径, 如/sdcard/
 */
static inline bool InstallSniffer(string packageName, string filePath) {
	bool bFlag = false;

	char pBuffer[2048] = {'\0'};
	string curVersion = "";
	string libPath = RelaseFilePrefix + packageName + RelaseFileLib;
	string releaseFile = "";

	ILog("SnifferInstaller::InstallSniffer()", "开始安装依赖包...");
	ILog("SnifferInstaller::InstallSniffer()", "所有依赖包安装完成!");

	// 判断是否需要安装或者升级
	ILog("SnifferInstaller::InstallSniffer()", "开始安装Sniffer, 判断是否需要安装或者升级...");
	curVersion = GetSnifferVersion();
	if(curVersion.compare(SnifferVersion) >= 0) {
		// 不需要升级
		ILog("SnifferInstaller::InstallSniffer()", "%s当前版本:(%s) 安装包版本:(%s)要新, 不需要升级!", SinfferFile, curVersion.c_str(), SnifferVersion);
		bFlag = true;
	}
	else {
		ILog("SnifferInstaller::InstallSniffer()", "开始安装Sniffer, 版本为:%s", SnifferVersion);

		// 拷贝Sniffer到系统目录
		releaseFile = libPath + SnifferInStallerFile;
		bool bFlag1 = RootExecutableFile(releaseFile, "/system/bin/", SinfferFile);
		if(bFlag1) {
			ILog("SnifferInstaller::InstallSniffer()", "安装Sniffer成功!");
			// 安装Sniffer成功, 继续释放自动启动脚本
			ILog("SnifferInstaller::InstallSniffer()", "释放自动启动脚...");
			releaseFile = ReleaseAutoStartScript(filePath);

			if(releaseFile.length() > 0) {
				// 拷贝AutoStartScript到系统目录
				bFlag = RootExecutableFile(releaseFile, "/etc/");
				if(bFlag) {
					ILog("SnifferInstaller::InstallSniffer()", "安装Sniffer自启动脚本成功!");
				}
				// 删除临时目录下AutoStartScript
				sprintf(pBuffer, "rm %s", releaseFile.c_str());
				SystemComandExecute(pBuffer);
			}
		}
		else {
			return false;
		}
	}

	if( bFlag ) {
		// 如果在运行先关闭
		int iPid = -1;
		while(-1 != (iPid = GetProcessPid(SinfferFile))) {
			ILog("SnifferInstaller::RootExecutableFile", "发现%s(PID:%d)正在运行, 先杀掉!", SinfferFile, iPid);
			sprintf(pBuffer, "kill -9 %d", iPid);
			SystemComandExecuteWithRoot(pBuffer);
		}

		ILog("SnifferInstaller::RootExecutableFile", "重新启动Sniffer...");
		SystemComandExecuteWithRoot("(sniffer &)");
//		ILog("SnifferInstaller::InstallSniffer()", "Sniffer启动成功!");
	}

	return bFlag;
}


#endif /* SNIFFERINSTALLER_H_ */