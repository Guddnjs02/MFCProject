#pragma once

class CNextDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNextDialog)

public:
	CNextDialog(int weight, CWnd* pParent = nullptr);
	virtual ~CNextDialog();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BODY_CARE_RESULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	int m_nWeight; // 몸무게 멤버 변수 추가


public:
	// 멤버 변수
	int m_basalMetabolicRate;   // 기초대사량
	int m_activityMetabolicRate; // 활동대사량
	int m_recommendedCalories;  // 권장 섭취칼로리
	float m_bmi;                // BMI
	int m_carbGrams;            // 탄수화물
	int m_proteinGrams;         // 단백질
	int m_fatGrams;             // 지방

	// 메시지 핸들러
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticCarbohydrates();
	afx_msg void OnBnClickedOk();
};
