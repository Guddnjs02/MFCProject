#include "pch.h"
#include "framework.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "CNextDialog.h" // H2 대화 상자 추가
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
	, m_nAge(0)
	, m_bMale(FALSE)
	, m_nHeight(0)
	, m_nWeight(0)
	, m_strActivity(_T(""))
	, m_basalMetabolicRate(0) // 추가
	, m_activityMetabolicRate(0) // 추가
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);
	DDX_Radio(pDX, IDC_RADIO_MALE, m_bMale);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_nWeight);
	DDX_CBString(pDX, IDC_COMBO_ACTIVITY, m_strActivity);
	DDX_CBString(pDX, IDC_COMBO_GOAL, m_strGoal);
}

BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CMFCProjectDlg::OnClickedSubmit)
END_MESSAGE_MAP()

void CMFCProjectDlg::OnClickedSubmit()
{
	UpdateData(TRUE); // H1에서 입력된 데이터를 업데이트

	// H2 대화 상자 생성
	CNextDialog dlgNext(m_nWeight);

	// H1 데이터를 기반으로 계산
	dlgNext.m_basalMetabolicRate = CalculateBMR(m_nAge, m_bMale, m_nHeight, m_nWeight);
	dlgNext.m_bmi = CalculateBMI(m_nHeight, m_nWeight);
	dlgNext.m_activityMetabolicRate = CalculateActivityMetabolicRate(dlgNext.m_basalMetabolicRate, m_strActivity);
	dlgNext.m_recommendedCalories = dlgNext.m_basalMetabolicRate + dlgNext.m_activityMetabolicRate;
	CalculateNutrients(dlgNext.m_recommendedCalories, dlgNext.m_carbGrams, dlgNext.m_proteinGrams, dlgNext.m_fatGrams);

	// H2 실행
	dlgNext.DoModal();
}

int CMFCProjectDlg::CalculateBMR(int age, bool isMale, int height, int weight)
{
	if (isMale)
		return 10 * weight + 6.25 * height - 5 * age + 5; // 남성
	else
		return 10 * weight + 6.25 * height - 5 * age - 161; // 여성
}

float CMFCProjectDlg::CalculateBMI(int height, int weight)
{
	float heightInMeters = height / 100.0f; // cm → m 변환
	return weight / (heightInMeters * heightInMeters);
}

int CMFCProjectDlg::CalculateActivityMetabolicRate(int bmr, CString activityLevel)
{
	if (activityLevel == _T("아주 낮음(거의 운동하지 않음)"))
		return bmr * 0.2;
	else if (activityLevel == _T("낮음(주 1~3일 가벼운 운동)"))
		return bmr * 0.375;
	else if (activityLevel == _T("보통(주 3~5일 중간 강도 운동)"))
		return bmr * 0.55;
	else if (activityLevel == _T("높음(주 6~7일 고강도 운동)"))
		return bmr * 0.725;
	else if (activityLevel == _T("매우 높음(매일 고강도 운동 + 육체적 직업)"))
		return bmr * 0.9;
	return 0; // 예외 처리
}

void CMFCProjectDlg::CalculateNutrients(int totalCalories, int& carbs, int& protein, int& fat)
{
	carbs = (totalCalories * 0.5) / 4;  // 탄수화물: 총 칼로리의 50%, 1g = 4kcal

	// 단백질: 체중 × 1.4g (m_nWeight 사용)
	protein = static_cast<int>(m_nWeight * 1.4);

	// 지방: 총 칼로리의 20% ÷ 9
	float fatCalories = totalCalories * 0.2f; // 지방의 총 칼로리
	fat = static_cast<int>(fatCalories / 9.0f); // 지방(g)
}


void CMFCProjectDlg::OnCbnSelchangeComboGoal()
{
	UpdateData(TRUE); // UI → 변수 업데이트

	CComboBox* pComboGoal = (CComboBox*)GetDlgItem(IDC_COMBO_GOAL);
	if (!pComboGoal) return;

	int selectedIndex = pComboGoal->GetCurSel(); // 선택된 인덱스 가져오기
	CString selectedGoal;
	pComboGoal->GetLBText(selectedIndex, selectedGoal); // 선택된 텍스트 가져오기

	// 목표에 따른 칼로리 계산
	int adjustedCalories = 0;
	if (selectedGoal == _T("체중감량"))
	{
		adjustedCalories = m_basalMetabolicRate + m_activityMetabolicRate - 500; // 감량: -500kcal
	}
	else if (selectedGoal == _T("체중유지"))
	{
		adjustedCalories = m_basalMetabolicRate + m_activityMetabolicRate; // 유지: 그대로
	}
	else if (selectedGoal == _T("체중증가"))
	{
		adjustedCalories = static_cast<int>((m_basalMetabolicRate + m_activityMetabolicRate) * 1.1); // 증가: 110%
	}

	// 계산된 값을 출력하거나 저장
	CString message;
	message.Format(_T("조정된 칼로리: %d Kcal"), adjustedCalories);
	AfxMessageBox(message);
}


BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목 추가
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 대화 상자의 아이콘 설정
	SetIcon(m_hIcon, TRUE);  // 큰 아이콘
	SetIcon(m_hIcon, FALSE); // 작은 아이콘

	// TODO: 추가 초기화 작업
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_ACTIVITY);
	if (pComboBox)
	{
		pComboBox->AddString(_T("아주 낮음(거의 운동하지 않음)"));
		pComboBox->AddString(_T("낮음(주 1~3일 가벼운 운동)"));
		pComboBox->AddString(_T("보통(주 3~5일 중간 강도 운동)"));
		pComboBox->AddString(_T("높음(주 6~7일 고강도 운동)"));
		pComboBox->AddString(_T("매우 높음(매일 고강도 운동 + 육체적 직업)"));
	}

	CComboBox* pGoalComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_GOAL);
	if (pGoalComboBox)
	{
		pGoalComboBox->AddString(_T("체중 감량"));
		pGoalComboBox->AddString(_T("체중 유지"));
		pGoalComboBox->AddString(_T("체중 증가"));
	}

	return TRUE; // TRUE를 반환하면 대화 상자에 포커스가 설정되지 않음
}
