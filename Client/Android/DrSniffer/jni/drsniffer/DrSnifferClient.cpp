/*
 * DrSnifferClient.cpp
 *
 *  Created on: 2014年3月9日
 *      Author: Kingsley Yau
 *      Email: Kingsleyyau@gmail.com
 */

#include "DrSnifferClient.h"

DrSnifferClient::DrSnifferClient() {
	// TODO Auto-generated constructor stub
	m_ServerAddress = ServerAddress;
	m_iServerPort = ServerPort;
}

DrSnifferClient::~DrSnifferClient() {
	// TODO Auto-generated destructor stub
}

// 保持唤醒线程
bool StartWakeThread() {
	bool bFlag = false;
	return bFlag;
}
void StopWakeThread() {

}
/*
 * 连接服务器
 */
bool DrSnifferClient::ConnectServer() {
	bool bFlag = false;
	int iRet = m_DrTcpSocket.Connect(m_ServerAddress, m_iServerPort, true);
	if(iRet > 0) {
		bFlag = true;
	}
	return bFlag;
}

/*
 * 接收服务器命令
 */
SCCMD DrSnifferClient::RecvCommand() {
	SCCMD sccmd;
	sccmd.scmdt = SinfferClientTypeNone;

	// 接收命令头
	char HeadBuffer[sizeof(SCMDH) + 1] = {'\0'};
	int iLen = m_DrTcpSocket.RecvData(HeadBuffer, sizeof(SCMDH));
	if(iLen == sizeof(SCMDH)) {
		// 接收头成功
		memcpy(&sccmd.header, HeadBuffer, sizeof(SCMDH));

		char *pBuffer = new char[sccmd.header.iLen + 1];
		memset(pBuffer, '\0', sccmd.header.iLen + 1);
		iLen = m_DrTcpSocket.RecvData(pBuffer, sccmd.header.iLen);
		if(iLen == sccmd.header.iLen) {
			// 接收类型
			memcpy(&sccmd.scmdt, pBuffer, sizeof(SCCMDT));

			// 接收参数
			sccmd.param = pBuffer + sizeof(SCCMDT);
		}
		delete[] pBuffer;
	}
	return sccmd;
}

/*
 * 发送命令到服务器
 */
bool DrSnifferClient::SendCommand(SSCMD sscmd) {
	bool bFlag = false;

	// 发送命令头
	sscmd.header.iLen = sizeof(SSCMDT) + sscmd.param.length();
	int iLen = m_DrTcpSocket.SendData((char *)&sscmd.header, sizeof(SCMDH));
	if(iLen == sizeof(SCMDH)) {
		// 类型
		char *pBuffer = new char[sscmd.header.iLen + 1];
		memset(pBuffer, '\0', sscmd.header.iLen + 1);

		char *p = pBuffer;
		memcpy(p, (char *)&sscmd.scmdt, sizeof(SSCMDT));
		p += sizeof(SSCMDT);

		// 参数
		memcpy(p, sscmd.param.c_str(), sscmd.param.length());

		// 发送类型和参数
		iLen = m_DrTcpSocket.SendData(pBuffer, sscmd.header.iLen);
		if(iLen == sscmd.header.iLen) {
			bFlag = true;
		}

		delete[] pBuffer;
	}

	return bFlag;
}
