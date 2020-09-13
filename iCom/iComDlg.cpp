
// iComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iCom.h"
#include "iComDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiComDlg �Ի���




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


// CiComDlg ��Ϣ�������

BOOL CiComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_comboCom.AddString(_T("COM1")); // Ϊ��Ͽ�ؼ����б������б���
	m_comboCom.AddString(_T("COM2")); 
	m_comboCom.AddString(_T("COM3")); 
	m_comboCom.AddString(_T("COM4")); 
	m_comboCom.AddString(_T("COM5")); 
	m_comboCom.AddString(_T("COM6")); 
	m_comboCom.AddString(_T("COM7")); 
	m_comboCom.AddString(_T("COM8")); 
	m_comboCom.AddString(_T("COM9")); 
	m_comboCom.AddString(_T("COM10"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CiComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CiComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CiComDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


//void CiComDlg::OnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	MessageBox(_T("hello"));
//}


void CiComDlg::OnCbnSelchangeComboCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel;
	nSel = m_comboCom.GetCurSel();//��ȡ��Ͽ�ؼ����б����ѡ���������

	m_ctrlComm.put_CommPort(nSel+1);//ѡ�񴮿ں�(������Ϊ�б����������Ǵ�0��ʼ������(nSel+1)��Ӧ�Ĳ���������ѡ�Ĵ��ں�)
	m_ctrlComm.put_PortOpen(TRUE);//�򿪴���
	m_ctrlComm.put_RThreshold(2);//�յ������ֽ�����OnComm�¼�	
	m_ctrlComm.put_InputMode(1);//����ģʽѡΪ������	
	m_ctrlComm.put_Settings(_T("9600,n,8,1"));//���ô��ڲ����������ʣ�����żУ�飬λֹͣλ��λ����λ
	m_ctrlComm.put_InputMode(1);  // �Զ����Ʒ�ʽ��ȡ���� 
	m_ctrlComm.put_RThreshold(1); //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼� 
	m_ctrlComm.put_InputLen(0); //���õ�ǰ���������ݳ���Ϊ0 
	m_ctrlComm.get_Input();//��Ԥ���������������������  

	m_setOk = true;		//��Ǵ�������OK

}
BEGIN_EVENTSINK_MAP(CiComDlg, CDialogEx)
	ON_EVENT(CiComDlg, IDC_MSCOMM1, 1, CiComDlg::OnComm, VTS_NONE)
END_EVENTSINK_MAP()


void CiComDlg::OnComm()
{
	// TODO: �ڴ˴������Ϣ����������
	VARIANT variant_inp;   //Variant ��һ��������������ͣ����˶���String���ݼ��û����������⣬���԰����κ���������ݡ�
	COleSafeArray safearray_inp;     
	LONG len,k;    
	BYTE rxdata[2048]; //����BYTE���� An 8-bit integer that is not signed.     
	CString strtemp;     
	if(m_ctrlComm.get_CommEvent() == 2) //�¼�ֵΪ2��ʾ���ջ����������ַ�     
	{            
		//��������Ը����Լ���ͨ��Э����봦����� 
		variant_inp=m_ctrlComm.get_Input();		//��������  
		safearray_inp=variant_inp;				//VARIANT�ͱ���ת��ΪColeSafeArray�ͱ���
		len=safearray_inp.GetOneDimSize();		//�õ���Ч���ݳ���        
		for(k=0;k<len;k++)             
			safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������         
		for(k=0;k<len;k++)                    //������ת��ΪCstring�ͱ���    
		{           
			BYTE bt=*(char*)(rxdata+k);//�ַ���      
			strtemp.Format(_T("%c"),bt); //���ַ�������ʱ����strtemp���   
			m_strRXData+=strtemp; //������ձ༭���Ӧ�ַ���      
		}
	}     
	UpdateData(FALSE); //���±༭������ 
}


void CiComDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_setOk == true)	//�ж��Ƿ�򿪲���ʼ������
	{
		UpdateData(TRUE);  //��ȡ�༭������
		m_ctrlComm.put_Output(COleVariant(m_strTXData)); //��������
	} 
	else
	{
		MessageBox(_T("����ѡ��COM��"));
	}

}


void CiComDlg::OnBnClickedButtonCleanup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strRXData="";
	UpdateData(FALSE);//���±༭������ 
}
