#pragma once
#include "afxdialogex.h"


// heartlate 대화 상자

class heartlate : public CDialogEx
{
	DECLARE_DYNAMIC(heartlate)

public:
	heartlate(int weight, CWnd* pParent = nullptr);   // 몸무게를 받는 생성자
	virtual ~heartlate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_heartrate };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	int m_nWeight; // 몸무게를 저장할 멤버 변수

public:
	afx_msg void OnBnClickedKcalButton();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeExerciseCombo();
	afx_msg void OnEnChangeinputkcal();
	afx_msg void OnStnClickedStaticImage();
};
