
// iComDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CiComDlg 对话框
class CiComDlg : public CDialogEx
{
// 构造
public:
	CiComDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ICOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
