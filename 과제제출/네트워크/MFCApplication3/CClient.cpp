#include "pch.h"
#include "CClient.h"


void CClient::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR: Disconnecting from Server"));
}

#include "MFCApplication3Dlg.h"
void CClient::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	char buf[256 + 1];
	ZeroMemory(buf, sizeof(buf));
	if (Receive(buf, sizeof(buf)) > 0)
	{
		CMFCApplication3Dlg* pMain = (CMFCApplication3Dlg*)AfxGetMainWnd();
		//pMain->m_List.AddString();
	}

	CSocket::OnReceive(nErrorCode);
}

//���� Ŭ���̾�Ʈ���� ������ �κ��̶� ������ �޴� �κ� �����ϱ�...