
// MFC-TESTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC-TEST.h"
#include "MFC-TESTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define HOST	"localhost"
#define USER	"root"
#define PASSW	"1234"
#define DBNAME  "book"
#define PORT    3306

// CMFCTESTDlg �Ի���




CMFCTESTDlg::CMFCTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
	, m_queryBook(_T(""))
	, m_queryAuthor(_T(""))
	, m_addBook(_T(""))
	, m_addAuthor(_T(""))
	, m_addPublisher(_T(""))
	, m_addTime(_T(""))
	, m_priceMin(0)
	, m_priceMax(0)
	, m_addPrice(0)
	,m_iRow(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BOOKNAME, m_queryBook);
	DDX_Text(pDX, IDC_EDIT_ANTHOR, m_queryAuthor);
	DDX_Text(pDX, IDC_EDIT_PRICEMIN, m_priceMin);
	DDX_Text(pDX, IDC_EDIT_PRICE_MAX, m_priceMax);
	DDX_Text(pDX, IDC_EDIT_BOOKNAME1, m_addBook);
	DDX_Text(pDX, IDC_EDIT_ANTHOR1, m_addAuthor);
	DDX_Text(pDX, IDC_EDIT_PBULISHER1, m_addPublisher);
	DDX_Text(pDX, IDC_EDIT_TIME1, m_addTime);
	DDX_Text(pDX, IDC_EDIT_PRICE1, m_addPrice);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CMFCTESTDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_QUERY, &CMFCTESTDlg::OnBnClickedBtnQuery)
	ON_BN_CLICKED(IDC_BTN_DEL, &CMFCTESTDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_QUERY3, &CMFCTESTDlg::OnBnClickedBtnShowAll)
	ON_BN_CLICKED(IDC_BTN_ADD, &CMFCTESTDlg::OnBnClickedBtnAdd)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCTESTDlg ��Ϣ�������

BOOL CMFCTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//�б�ͷ	InsertColumn���б���ͼ�ؼ��в������С�
	m_list.InsertColumn(0, TEXT("����"), 0, 230);//�кţ���ַ�����뷽ʽ���п�
	m_list.InsertColumn(1, TEXT("����"), 0, 160);
	m_list.InsertColumn(2, TEXT("������"), 0, 120);
	m_list.InsertColumn(3, TEXT("����ʱ��"), 0, 90);
	m_list.InsertColumn(4, TEXT("�ۼ�"), 0, 60);
	
	//һ��ʼ����ʾ��������
	//�������ݿ�
	if (!ConnectDB())
	{
		AfxMessageBox(TEXT("�������ݿ�ʧ��"));
		return FALSE;
	}
	//��ѯ����
	SelectDB();
	//��ȡ����;
	GetDataFromDB();
	//��ʾ����
	ShowInfo();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCTESTDlg::OnPaint()
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
HCURSOR CMFCTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ѯ
void CMFCTESTDlg::OnBnClickedBtnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SelectDB();				//��ѯ
	GetDataFromDB();        //��ȡ����
	ShowInfo();				//��ʾ����
}

//ɾ��
void CMFCTESTDlg::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DeleteDB();
}

//��ʾ��������
void CMFCTESTDlg::OnBnClickedBtnShowAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_queryBook.Empty();	//������������select * from book ��ʾ������
	m_queryAuthor.Empty();
	m_priceMax = 0;
	m_priceMin = 0;
	UpdateData(FALSE);
	SelectDB();
	GetDataFromDB();
	ShowInfo();
}

//���
void CMFCTESTDlg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	InsertDB();				   //��������
	OnBnClickedBtnShowAll();   //��Ӽ�¼����ʾ����
	//��������ձ༭��
	m_addBook.Empty();
	m_addAuthor.Empty();
	m_addPublisher.Empty();
	m_addTime.Empty();
	m_addPrice = 0;
	UpdateData(FALSE);
}

//����MYSQL���ݿ�
BOOL CMFCTESTDlg::ConnectDB()
{
	//��ʼ�����ݿ�
	mysql_init(&m_mysql);
	//�������ݿ�����ʽ
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	if (!mysql_real_connect(&m_mysql, HOST, USER, PASSW, DBNAME, PORT, NULL, 0))
		return FALSE;
	return TRUE;
}

//��ʾ����
void CMFCTESTDlg::ShowInfo()
{
	m_list.DeleteAllItems();//ɾ��������
	for (int i = 0;i<m_res->row_count;i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());//m_data[i][0]:ÿi�еĵ�i��Ԫ��
		for (int j = 0;j < int(m_mysql.field_count - 1);j++)//mysql_field_count()�����������ѯ�Ľ���е�������*���棺����˾����һ�ַ������ڱȽϺ�����ʱת������������ signed ֮һ unsigned ��
				m_list.SetItemText(iCount, j + 1,m_data[i][static_cast<__int64>(j) + 1].c_str());//*���棺�ڵ�������� "operator" ֮ǰ��ֵǿ��ת��Ϊ��������ͣ��Ա������
	}
}

//��ѯ����
BOOL CMFCTESTDlg::SelectDB()
{
	UpdateData(TRUE);
	ClearData();
	CString query;
	//����ȫ��Ϊ�����ѯ�����鼮
	if (m_queryBook.IsEmpty() && m_queryAuthor.IsEmpty() && !m_priceMin && !m_priceMax)
		query.Format(TEXT("select * from book"));
	else if (!m_priceMin && !m_priceMax)//�۸�ΧΪ��
	{
		CString sBook,sAuthor;
		if (!m_queryBook.IsEmpty())
		{
			sBook.AppendChar('%');
			m_queryBook.AppendChar('%');
			sBook.Append(m_queryBook);
		}
		if (!m_queryAuthor.IsEmpty())
		{
			sAuthor.AppendChar('%');
			m_queryAuthor.AppendChar('%');
			sAuthor.Append(m_queryAuthor);
		}
		query.Format(TEXT("select * from book where bookName  like  '%s' or author like '%s';"), sBook, sAuthor);
	}
	else if (m_priceMin && !m_priceMax) 
		query.Format(TEXT("select * from book where price >= %f;"), m_priceMin);
	else if (!m_priceMin && m_priceMax)
		query.Format(TEXT("select * from book where price <= %f;"), m_priceMax);
	else if (m_priceMin && m_priceMax)
		query.Format(TEXT("select * from book where price >= %f and price <=%f;"), m_priceMin,m_priceMax);
	//��ѯ����
	if (mysql_query(&m_mysql, query))
		return FALSE;
	//��ȡ�����
	m_res = mysql_store_result(&m_mysql);
	return TRUE;
}

//��������
BOOL CMFCTESTDlg::InsertDB()
{
	UpdateData(TRUE);
	if (m_addBook.IsEmpty())
	{
		AfxMessageBox(TEXT("��������Ϊ��!"));
		return FALSE;
	}
	CString query;
	query.Format(TEXT("insert into book values('%s','%s','%s','%s',%.2f);"), m_addBook, m_addAuthor, m_addPublisher, m_addTime, m_addPrice);
	if (mysql_query(&m_mysql, query))
	{
		AfxMessageBox(TEXT("��������ʧ�ܣ�"));
		return FALSE;
	}
	return TRUE;
}

//ɾ������
BOOL CMFCTESTDlg::DeleteDB()
{
	UpdateData(TRUE);
	int iCount = m_list.GetItemCount();//�б���������Ŀ����, ���ŵ���
	std::vector<std::string> row[100];//vector��һ���ܹ�����������͵Ķ�̬���顣
	int j = 0;
	//���Զ�ѡȻ��ɾ��
	for (int i = iCount; i >= 0; i--)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)//����ֵ��ָ���б���ͼ���״̬��־��
		{
			CString bookName;
			bookName = m_list.GetItemText(i, 0);
			CString query;
			query.Format(TEXT("delete from book where bookName='%s';"), bookName);
			if (mysql_query(&m_mysql, query))
			{
				AfxMessageBox(TEXT("ɾ������ʧ�ܣ�"));
				return FALSE;
			}
			//Ҫ��ɾ�����ݿ�ļ�¼�����ɾ���б��е������GetItemText�᷵�ؿ�
			m_list.DeleteItem(i);//ɾ���б��е���
		}
	}
	return TRUE;
}

//�����ݿ��ȡ����
void CMFCTESTDlg::GetDataFromDB()
{
	//��ȡ��¼
	int i = 0;
	while (m_row = mysql_fetch_row(m_res))
	//����һ��������ϵ���һ�С�����mysql_store_result()֮��ʹ��ʱ�����û�и�����пɼ���ʱ��mysql_fetch_row()����NULL��
	{
		m_data[i].push_back(m_row[0]);//�ַ���֮�����һ���ַ���
		m_data[i].push_back(m_row[1]);
		m_data[i].push_back(m_row[2]);
		m_data[i].push_back(m_row[3]);
		m_data[i].push_back(m_row[4]);
		m_data[i++].push_back(m_row[5]);
	}
}

//�������
void CMFCTESTDlg::ClearData()
{
	int i = 0;
	while (!m_data[i].empty())
	{
		m_data[i++].clear();
	}
}

void CMFCTESTDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	//�ͷŽ����
	mysql_free_result(m_res);
	//�ر����ݿ�
	mysql_close(&m_mysql);
}
