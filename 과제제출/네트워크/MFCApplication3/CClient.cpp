#include "pch.h"
#include "CClient.h"

#pragma pack(1)
struct TEST
{
	char Buffer[256];
};
#pragma pack()

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
	int retval;

	char bufferTmp[sizeof(TEST)];
	ZeroMemory(bufferTmp, sizeof(bufferTmp));

	if (Receive(bufferTmp, sizeof(bufferTmp)) > 0)
	{
		TEST* recv_packet = (TEST*)bufferTmp;
		CMFCApplication3Dlg* pMain = (CMFCApplication3Dlg*)AfxGetMainWnd();
		CString StringTmp(recv_packet->Buffer);
		pMain->m_List.AddString(StringTmp);
	}

	CSocket::OnReceive(nErrorCode);
}

//���� Ŭ���̾�Ʈ���� ������ �κ��̶� ������ �޴� �κ� �����ϱ�...