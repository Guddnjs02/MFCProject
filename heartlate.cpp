// heartlate.cpp: 구현 파일
//

#include "pch.h"
#include "MFCProject.h"
#include "afxdialogex.h"
#include "heartlate.h"
#include "afxwin.h"

// heartlate 대화 상자

IMPLEMENT_DYNAMIC(heartlate, CDialogEx)

heartlate::heartlate(int weight, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_heartrate, pParent), m_nWeight(weight) // 초기화
{
	CString debugMessage;
	debugMessage.Format(_T("초기화된 몸무게: %d kg"), m_nWeight);
	AfxMessageBox(debugMessage);
}

heartlate::~heartlate()
{
}

void heartlate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(heartlate, CDialogEx)
	ON_BN_CLICKED(IDC_KCAL_BUTTON, &heartlate::OnBnClickedKcalButton)
	ON_CBN_SELCHANGE(IDC_COMBO1, &heartlate::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_EXERCISE_COMBO, &heartlate::OnCbnSelchangeExerciseCombo)
	ON_EN_CHANGE(IDC_input_kcal, &heartlate::OnEnChangeinputkcal)
END_MESSAGE_MAP()


// heartlate 메시지 처리기


void heartlate::OnBnClickedKcalButton()
{
	CString debugMessage;
	debugMessage.Format(_T("현재 몸무게: %d kg"), m_nWeight);
	AfxMessageBox(debugMessage);

	int weight = m_nWeight;
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int selectedIndex = pCombo->GetCurSel();

	// 입력된 목표 칼로리 가져오기
	CString strKcal;
	GetDlgItemText(IDC_input_kcal, strKcal);

	if (strKcal.IsEmpty()) return;

	int targetKcal = _ttoi(strKcal);
	if (targetKcal <= 0) return;

	// 운동별 기준 칼로리 (70kg 기준, 30분)
	int baseCalories = 0;
	switch (selectedIndex) {
	case 0:  // 걷기
		baseCalories = 120;
		break;
	case 1:  // 달리기
		baseCalories = 280;
		break;
	case 2:  // 자전거
		baseCalories = 240;
		break;
	case 3:  // 수영
		baseCalories = 300;
		break;
	case 4:  // 등산
		baseCalories = 250;
		break;
	case 5:  // 줄넘기
		baseCalories = 280;
		break;
	case 6:  // 스쿼트
		baseCalories = 200;
		break;
	case 7:  // 계단
		baseCalories = 260;
		break;
	case 8:  // 복싱
		baseCalories = 270;
		break;
	case 9:  // 스쿼시
		baseCalories = 300;
		break;
	case 10: // 에어로빅
		baseCalories = 210;
		break;
	case 11: // 요가
		baseCalories = 150;
		break;
	default:
		baseCalories = 120;
	}

	// 현재 체중에 맞는 1분당 칼로리 소모량 계산
	double caloriesPerMinute = ((baseCalories / 30.0) * m_nWeight) / 70.0;

	// 목표 칼로리 달성을 위한 필요 시간(분) 계산
	double requiredMinutes = targetKcal / caloriesPerMinute;

	// 시간과 분으로 변환
	int minutes = static_cast<int>(requiredMinutes);

	// 결과 메시지 표시
	CString exerciseType;
	pCombo->GetLBText(selectedIndex, exerciseType);
	CString message;

	
	message.Format(_T("목표 칼로리 %d kcal 소모를 위해\n[%s] 운동을 %d분 해야 합니다."),
			targetKcal, exerciseType, minutes);
	

	AfxMessageBox(message);
}



void heartlate::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void heartlate::OnCbnSelchangeExerciseCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void heartlate::OnEnChangeinputkcal()
{
	// 입력된 목표 칼로리 가져오기
	CString strKcal;
	GetDlgItemText(IDC_input_kcal, strKcal);

}

BOOL heartlate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 콤보박스 초기화
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO1);

	// 콤보박스에 운동 목록 추가
	pCombo->AddString(_T("걷기"));
	pCombo->AddString(_T("달리기"));
	pCombo->AddString(_T("자전거"));
	pCombo->AddString(_T("수영"));
	pCombo->AddString(_T("등산"));
	pCombo->AddString(_T("줄넘기"));
	pCombo->AddString(_T("스쿼트"));
	pCombo->AddString(_T("계단"));
	pCombo->AddString(_T("복싱"));
	pCombo->AddString(_T("스쿼시"));
	pCombo->AddString(_T("에어로빅"));
	pCombo->AddString(_T("요가"));

	// 기본값 선택
	pCombo->SetCurSel(0);

	return TRUE;
}