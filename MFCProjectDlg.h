#pragma once

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
	afx_msg void OnCbnSelchangeComboGoal();
	DECLARE_MESSAGE_MAP()

private:
	// 계산 함수
	int CalculateBMR(int age, bool isMale, int height, int weight); // BMR 계산
	float CalculateBMI(int height, int weight); // BMI 계산
	int CalculateActivityMetabolicRate(int bmr, CString activityLevel); // 활동대사량 계산
	void CalculateNutrients(int totalCalories, int& carbs, int& protein, int& fat);


public:
	// 멤버 변수
	int m_nAge;
	BOOL m_bMale;
	int m_nHeight;
	int m_nWeight;
	CString m_strActivity;
	CString m_strGoal;
	// 대사량 관련 변수
	int m_basalMetabolicRate;   // 기초대사량
	int m_activityMetabolicRate; // 활동대사량

	// 메시지 핸들러
	afx_msg void OnStnClickedStaticAge();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEditAge();
	afx_msg void OnBnClickedRadioMale();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedSubmit();
	afx_msg void OnCbnSelchangeComboActivity();
};
