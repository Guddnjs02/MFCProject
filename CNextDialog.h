#pragma once

// CNextDialog 대화 상자
class CNextDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNextDialog)

public:
	CNextDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNextDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEXT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	// 대화 상자 초기화
	virtual BOOL OnInitDialog();

	// 버튼 핸들러
	afx_msg void OnBnClickedButtonOk();

	// 멤버 변수
	CString m_strUserInput;  // 사용자 입력 데이터
};
