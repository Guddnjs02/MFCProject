#include "pch.h"
#include "MFCProject.h"
#include "CNextDialog.h"
#include "afxdialogex.h"
#include "heartlate.h"
#include "MFCProjectDlg.h"

IMPLEMENT_DYNAMIC(CNextDialog, CDialogEx)

CNextDialog::CNextDialog(int weight, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_BODY_CARE_RESULT, pParent)
	, m_basalMetabolicRate(0)
	, m_activityMetabolicRate(0)
	, m_recommendedCalories(0)
	, m_bmi(0.0f)
	, m_carbGrams(0)
	, m_proteinGrams(0)
	, m_fatGrams(0)
    , m_nWeight(weight)
{
}

CNextDialog::~CNextDialog()
{
}

void CNextDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNextDialog, CDialogEx)
    ON_STN_CLICKED(IDC_STATIC_CARBOHYDRATES, &CNextDialog::OnStnClickedStaticCarbohydrates)
    ON_BN_CLICKED(IDOK, &CNextDialog::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_BACK, &CNextDialog::OnBnClickedButtonBack)
END_MESSAGE_MAP()

BOOL CNextDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 데이터 표시를 위한 문자열
    CString strBasalRate, strActivityRate, strRecommendedCalories, strBMI;
    CString strCarb, strProtein, strFat;

    // 신체 정보 분석 값 설정
    strBasalRate.Format(_T("%d Kcal"), m_basalMetabolicRate);
    strActivityRate.Format(_T("%d Kcal"), m_activityMetabolicRate);
    strRecommendedCalories.Format(_T("%d Kcal"), m_recommendedCalories);
    strBMI.Format(_T("%.2f"), m_bmi);

    SetDlgItemText(IDC_STATIC_BASAL_METABOLIC_RATE_VALUE, strBasalRate);
    SetDlgItemText(IDC_STATIC_ACTIVITY_METABOLIC_RATE_VALUE, strActivityRate);
    SetDlgItemText(IDC_STATIC_RECOMMENDED_CALORIES_VALUE, strRecommendedCalories);
    SetDlgItemText(IDC_STATIC_BMI_VALUE, strBMI);

    // 권장 영양소 분배 값 설정
    strCarb.Format(_T("%d g"), m_carbGrams);
    strProtein.Format(_T("%d g"), m_proteinGrams);
    strFat.Format(_T("%d g"), m_fatGrams);

    SetDlgItemText(IDC_STATIC_CARBOHYDRATES_VALUE, strCarb);
    SetDlgItemText(IDC_STATIC_PROTEIN_VALUE, strProtein);
    SetDlgItemText(IDC_STATIC_FAT_VALUE, strFat);

    return TRUE;
}



void CNextDialog::OnStnClickedStaticCarbohydrates()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CNextDialog::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
     // heartlate 대화상자 객체 생성 - 실제 몸무게 값을 생성자에 전달
    heartlate dlg(m_nWeight);
    dlg.DoModal();  // 대화상자 표시

    CDialogEx::OnOK();
}

void CNextDialog::OnBnClickedButtonBack()
{
    // 현재 H2 대화 상자 닫기
    EndDialog(IDCANCEL); // H2를 종료

    // H1(MFCProjectDlg) 대화 상자를 다시 실행
    CMFCProjectDlg dlgPrev; // H1 객체 생성
    dlgPrev.DoModal(); // H1 대화 상자 표시
}

