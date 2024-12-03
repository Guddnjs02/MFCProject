#include "pch.h"
#include "MFCProject.h"
#include "CNextDialog.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CNextDialog, CDialogEx)

CNextDialog::CNextDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BODY_CARE_RESULT, pParent)
	, m_basalMetabolicRate(0)
	, m_activityMetabolicRate(0)
	, m_recommendedCalories(0)
	, m_bmi(0.0f)
	, m_carbGrams(0)
	, m_proteinGrams(0)
	, m_fatGrams(0)
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

