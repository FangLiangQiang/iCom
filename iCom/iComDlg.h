
// iComDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CiComDlg �Ի���
class CiComDlg : public CDialogEx
{
// ����
public:
	CiComDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ICOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	afx_msg void OnClickedButton1();
	CComboBox m_comboCom;
	afx_msg void OnCbnSelchangeComboCom();
	CMscomm1 m_ctrlComm;
private:
	bool m_setOk;
public:
	CString m_strTXData;
	CString m_strRXData;
	DECLARE_EVENTSINK_MAP()
	void OnComm();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonCleanup();
};
