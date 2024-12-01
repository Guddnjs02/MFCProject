// MFCProjectDlg.h: 헤더 파일
//

#pragma once


// CMFCProjectDlg 대화 상자
class CMFCProjectDlg : public CDialogEx
{
	// 생성입니다.
public:
	CMFCProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// 사용자 정의 멤버 변수
public:
	// 나이
	int m_nAge;

	// 성별
	int m_bMale; // 라디오 버튼의 첫 번째 항목과 연결 (0: 남자, 1: 여자)

	// 키와 몸무게
	int m_nHeight;  // 키
	int m_nWeight;  // 몸무게

	// 운동 빈도수 (콤보 박스)
	CString m_strActivity;

	// 메시지 핸들러
	afx_msg void OnStnClickedStaticAge();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEditAge();
	afx_msg void OnBnClickedRadioMale();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedSubmit();
	afx_msg void OnCbnSelchangeComboActivity();
};
