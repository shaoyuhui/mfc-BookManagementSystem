
// MFC-TESTDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <vector>
#include <string>


// CMFCTESTDlg �Ի���
class CMFCTESTDlg : public CDialogEx
{
// ����
public:
	CMFCTESTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	MYSQL m_mysql;			  //���ݿ�ṹ
	MYSQL_RES* m_res;         //��ѯ�ķ��ؽ����
	MYSQL_ROW m_row;          //��ȡÿһ����¼
	std::vector<std::string> m_data[100];  //������ݿ��¼�����Ϊ100��//vector�Ǳ�ʾ���Ըı��С�����������������(��̬���䣩
	int m_iRow;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_queryBook;
	CString m_queryAuthor;
	float m_priceMin;
	float m_priceMax;
	CString m_addBook;
	CString m_addAuthor;
	CString m_addPublisher;
	CString m_addTime;
	float m_addPrice;
	BOOL ConnectDB();		//����MYSQL���ݿ�
	BOOL SelectDB();		//��ѯ����
	BOOL InsertDB();		//��������
	BOOL DeleteDB();        //ɾ������
	void GetDataFromDB();   //�����ݿ��ȡ����
	void ShowInfo();        //��ʾ����
	void ClearData();       //�������
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnShowAll();
	afx_msg void OnBnClickedBtnAdd();
	CListCtrl m_list;
	afx_msg void OnDestroy();
};
