
// iComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iCom.h"
#include "iComDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiComDlg 对话框




CiComDlg::CiComDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CiComDlg::IDD, pParent)
	, m_setOk(false)
	, m_strTXData(_T(""))
	, m_strRXData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CiComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM, m_comboCom);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
}

BEGIN_MESSAGE_MAP(CiComDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CiComDlg::OnBnClickedOk)
//	ON_BN_CLICKED(IDC_BUTTON1, &CiComDlg::OnClickedButton1)
ON_CBN_SELCHANGE(IDC_COMBO_COM, &CiComDlg::OnCbnSelchangeComboCom)
ON_BN_CLICKED(IDC_BUTTON_SEND, &CiComDlg::OnBnClickedButtonSend)
ON_BN_CLICKED(IDC_BUTTON_CLEANUP, &CiComDlg::OnBnClickedButtonCleanup)
END_MESSAGE_MAP()


// CiComDlg 消息处理程序

BOOL CiComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_comboCom.AddString(_T("COM1")); // 为组合框控件的列表框添加列表项
	m_comboCom.AddString(_T("COM2")); 
	m_comboCom.AddString(_T("COM3")); 
	m_comboCom.AddString(_T("COM4")); 
	m_comboCom.AddString(_T("COM5")); 
	m_comboCom.AddString(_T("COM6")); 
	m_comboCom.AddString(_T("COM7")); 
	m_comboCom.AddString(_T("COM8")); 
	m_comboCom.AddString(_T("COM9")); 
	m_comboCom.AddString(_T("COM10"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CiComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CiComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CiComDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


//void CiComDlg::OnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	MessageBox(_T("hello"));
//}


void CiComDlg::OnCbnSelchangeComboCom()
{
	// TODO: 在此添加控件通知处理程序代码
	int nSel;
	nSel = m_comboCom.GetCurSel();//获取组合框控件的列表框中选中项的索引

	m_ctrlComm.put_CommPort(nSel+1);//选择串口号(这里因为列表框的索引号是从0开始，所以(nSel+1)对应的才是我们所选的串口号)
	m_ctrlComm.put_PortOpen(TRUE);//打开串口
	m_ctrlComm.put_RThreshold(2);//收到两个字节引发OnComm事件	
	m_ctrlComm.put_InputMode(1);//输入模式选为二进制	
	m_ctrlComm.put_Settings(_T("9600,n,8,1"));//设置串口参数，波特率，无奇偶校验，位停止位，位数据位
	m_ctrlComm.put_InputMode(1);  // 以二进制方式检取数据 
	m_ctrlComm.put_RThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件 
	m_ctrlComm.put_InputLen(0); //设置当前接收区数据长度为0 
	m_ctrlComm.get_Input();//先预读缓冲区以清除残留数据  

	m_setOk = true;		//标记串口设置OK

}
BEGIN_EVENTSINK_MAP(CiComDlg, CDialogEx)
	ON_EVENT(CiComDlg, IDC_MSCOMM1, 1, CiComDlg::OnComm, VTS_NONE)
END_EVENTSINK_MAP()


void CiComDlg::OnComm()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;   //Variant 是一种特殊的数据类型，除了定长String数据及用户定义类型外，可以包含任何种类的数据。
	COleSafeArray safearray_inp;     
	LONG len,k;    
	BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integer that is not signed.     
	CString strtemp;     
	if(m_ctrlComm.get_CommEvent() == 2) //事件值为2表示接收缓冲区内有字符     
	{            
		//以下你可以根据自己的通信协议加入处理代码 
		variant_inp=m_ctrlComm.get_Input();		//读缓冲区  
		safearray_inp=variant_inp;				//VARIANT型变量转换为ColeSafeArray型变量
		len=safearray_inp.GetOneDimSize();		//得到有效数据长度        
		for(k=0;k<len;k++)             
			safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组         
		for(k=0;k<len;k++)                    //将数组转换为Cstring型变量    
		{           
			BYTE bt=*(char*)(rxdata+k);//字符型      
			strtemp.Format(_T("%c"),bt); //将字符送入临时变量strtemp存放   
			m_strRXData+=strtemp; //加入接收编辑框对应字符串      
		}
	}     
	UpdateData(FALSE); //更新编辑框内容 
}


void CiComDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_setOk == true)	//判断是否打开并初始化串口
	{
		UpdateData(TRUE);  //读取编辑框内容
		m_ctrlComm.put_Output(COleVariant(m_strTXData)); //发送数据
	} 
	else
	{
		MessageBox(_T("请先选择COM口"));
	}

}


void CiComDlg::OnBnClickedButtonCleanup()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strRXData="";
	UpdateData(FALSE);//更新编辑框内容 
}
