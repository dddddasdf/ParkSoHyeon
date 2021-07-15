#include "pch.h"
#include "CClient.h"


void CClient::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnecting from Server"));
}

#include "MFCApplication3Dlg.h"
void CClient::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char buf[256 + 1];
	ZeroMemory(buf, sizeof(buf));
	if (Receive(buf, sizeof(buf)) > 0)
	{
		CMFCApplication3Dlg* pMain = (CMFCApplication3Dlg*)AfxGetMainWnd();
		//pMain->m_List.AddString();
	}

	CSocket::OnReceive(nErrorCode);
}

//기존 클라이언트에서 보내는 부분이랑 서버의 받는 부분 참고하기...