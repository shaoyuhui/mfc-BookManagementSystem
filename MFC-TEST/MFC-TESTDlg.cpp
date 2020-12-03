
// MFC-TESTDlg.cpp : 实现文件
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

// CMFCTESTDlg 对话框




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


// CMFCTESTDlg 消息处理程序

BOOL CMFCTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//列表头	InsertColumn在列表视图控件中插入新列。
	m_list.InsertColumn(0, TEXT("书名"), 0, 230);//列号，地址，对齐方式，列宽
	m_list.InsertColumn(1, TEXT("作者"), 0, 160);
	m_list.InsertColumn(2, TEXT("出版社"), 0, 120);
	m_list.InsertColumn(3, TEXT("出版时间"), 0, 90);
	m_list.InsertColumn(4, TEXT("售价"), 0, 60);
	
	//一开始先显示所有数据
	//连接数据库
	if (!ConnectDB())
	{
		AfxMessageBox(TEXT("连接数据库失败"));
		return FALSE;
	}
	//查询数据
	SelectDB();
	//获取数据;
	GetDataFromDB();
	//显示数据
	ShowInfo();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTESTDlg::OnPaint()
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
HCURSOR CMFCTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//查询
void CMFCTESTDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	SelectDB();				//查询
	GetDataFromDB();        //获取数据
	ShowInfo();				//显示数据
}

//删除
void CMFCTESTDlg::OnBnClickedBtnDel()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteDB();
}

//显示所有数据
void CMFCTESTDlg::OnBnClickedBtnShowAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_queryBook.Empty();	//清空条件后就是select * from book 显示所有了
	m_queryAuthor.Empty();
	m_priceMax = 0;
	m_priceMin = 0;
	UpdateData(FALSE);
	SelectDB();
	GetDataFromDB();
	ShowInfo();
}

//添加
void CMFCTESTDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	InsertDB();				   //插入数据
	OnBnClickedBtnShowAll();   //添加纪录后显示出来
	//添加完后清空编辑框
	m_addBook.Empty();
	m_addAuthor.Empty();
	m_addPublisher.Empty();
	m_addTime.Empty();
	m_addPrice = 0;
	UpdateData(FALSE);
}

//连接MYSQL数据库
BOOL CMFCTESTDlg::ConnectDB()
{
	//初始化数据库
	mysql_init(&m_mysql);
	//设置数据库编码格式
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	if (!mysql_real_connect(&m_mysql, HOST, USER, PASSW, DBNAME, PORT, NULL, 0))
		return FALSE;
	return TRUE;
}

//显示数据
void CMFCTESTDlg::ShowInfo()
{
	m_list.DeleteAllItems();//删除所有项
	for (int i = 0;i<m_res->row_count;i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());//m_data[i][0]:每i行的第i个元素
		for (int j = 0;j < int(m_mysql.field_count - 1);j++)//mysql_field_count()：返回最近查询的结果列的数量。*警告：解决此警告的一种方法是在比较和类型时转换这两种类型 signed 之一 unsigned 。
				m_list.SetItemText(iCount, j + 1,m_data[i][static_cast<__int64>(j) + 1].c_str());//*警告：在调用运算符 "operator" 之前将值强制转换为更大的类型，以避免溢出
	}
}

//查询数据
BOOL CMFCTESTDlg::SelectDB()
{
	UpdateData(TRUE);
	ClearData();
	CString query;
	//条件全部为空则查询所有书籍
	if (m_queryBook.IsEmpty() && m_queryAuthor.IsEmpty() && !m_priceMin && !m_priceMax)
		query.Format(TEXT("select * from book"));
	else if (!m_priceMin && !m_priceMax)//价格范围为空
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
	//查询数据
	if (mysql_query(&m_mysql, query))
		return FALSE;
	//获取结果集
	m_res = mysql_store_result(&m_mysql);
	return TRUE;
}

//插入数据
BOOL CMFCTESTDlg::InsertDB()
{
	UpdateData(TRUE);
	if (m_addBook.IsEmpty())
	{
		AfxMessageBox(TEXT("书名不能为空!"));
		return FALSE;
	}
	CString query;
	query.Format(TEXT("insert into book values('%s','%s','%s','%s',%.2f);"), m_addBook, m_addAuthor, m_addPublisher, m_addTime, m_addPrice);
	if (mysql_query(&m_mysql, query))
	{
		AfxMessageBox(TEXT("插入数据失败！"));
		return FALSE;
	}
	return TRUE;
}

//删除数据
BOOL CMFCTESTDlg::DeleteDB()
{
	UpdateData(TRUE);
	int iCount = m_list.GetItemCount();//列表的里面的条目数量, 横着的行
	std::vector<std::string> row[100];//vector是一个能够存放任意类型的动态数组。
	int j = 0;
	//可以多选然后删除
	for (int i = iCount; i >= 0; i--)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)//返回值：指定列表视图项的状态标志。
		{
			CString bookName;
			bookName = m_list.GetItemText(i, 0);
			CString query;
			query.Format(TEXT("delete from book where bookName='%s';"), bookName);
			if (mysql_query(&m_mysql, query))
			{
				AfxMessageBox(TEXT("删除数据失败！"));
				return FALSE;
			}
			//要先删除数据库的记录后才能删除列表中的项，否则GetItemText会返回空
			m_list.DeleteItem(i);//删除列表中的项
		}
	}
	return TRUE;
}

//从数据库获取数据
void CMFCTESTDlg::GetDataFromDB()
{
	//获取记录
	int i = 0;
	while (m_row = mysql_fetch_row(m_res))
	//检索一个结果集合的下一行。当在mysql_store_result()之后使用时，如果没有更多的行可检索时，mysql_fetch_row()返回NULL。
	{
		m_data[i].push_back(m_row[0]);//字符串之后插入一个字符。
		m_data[i].push_back(m_row[1]);
		m_data[i].push_back(m_row[2]);
		m_data[i].push_back(m_row[3]);
		m_data[i].push_back(m_row[4]);
		m_data[i++].push_back(m_row[5]);
	}
}

//清空数据
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

	// TODO: 在此处添加消息处理程序代码
	//释放结果集
	mysql_free_result(m_res);
	//关闭数据库
	mysql_close(&m_mysql);
}
