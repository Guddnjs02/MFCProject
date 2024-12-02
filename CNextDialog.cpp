// CNextDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCProject.h"
#include "CNextDialog.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CNextDialog, CDialogEx)

CNextDialog::CNextDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_NEXT_DIALOG, pParent)
    , m_strUserInput(_T("")) // 초기값
{
}

CNextDialog::~CNextDialog()
{
}

void CNextDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_USER_INPUT, m_strUserInput); // Edit Control 연결
}

BEGIN_MESSAGE_MAP(CNextDialog, CDialogEx)
    ON_WM_INITDIALOG()
    ON_BN_CLICKED(IDC_BUTTON_OK, &CNextDialog::OnBnClickedButtonOk)
END_MESSAGE_MAP()
 
BOOL CNextDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 초기화 작업
    SetDlgItemText(IDC_STATIC, _T("다음 화면으로 이동했습니다!"));

    return TRUE;
}

void CNextDialog::OnBnClickedButtonOk()
{
    UpdateData(TRUE);  // UI → 변수 업데이트
    CString message;
    message.Format(_T("입력된 값: %s"), m_strUserInput);
    AfxMessageBox(message);

    EndDialog(IDOK);  // 대화 상자 닫기
}
