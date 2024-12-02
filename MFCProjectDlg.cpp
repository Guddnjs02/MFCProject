
// MFCProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCProjectDlg 대화 상자



CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
	, m_nAge(0)
	, m_bMale(FALSE)
	, m_nHeight(0)
	, m_nWeight(0)
	, m_strActivity(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// 나이
	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);

	// 성별 (라디오 버튼 그룹)
	DDX_Radio(pDX, IDC_RADIO_MALE, m_bMale);

	// 키와 몸무게
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_nWeight);

	// 운동 빈도수 (콤보 박스)
	DDX_CBString(pDX, IDC_COMBO_ACTIVITY, m_strActivity);
}


BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC_AGE, &CMFCProjectDlg::OnStnClickedStaticAge)
	ON_EN_CHANGE(IDC_EDIT_AGE, &CMFCProjectDlg::OnEnChangeEditAge)
	ON_BN_CLICKED(IDOK, &CMFCProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CMFCProjectDlg::OnClickedSubmit)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTIVITY, &CMFCProjectDlg::OnCbnSelchangeComboActivity)
END_MESSAGE_MAP()



// CMFCProjectDlg 메시지 처리기

BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 콤보 상자에 항목 추가
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_ACTIVITY); // 콤보 상자 가져오기
	if (pComboBox)
	{
		pComboBox->AddString(_T("아주 낮음(거의 운동하지 않음)"));
		pComboBox->AddString(_T("낮음(주 1~3일 가벼운 운동)"));
		pComboBox->AddString(_T("보통(주 3~5일 중간 강도 운동)"));
		pComboBox->AddString(_T("높음(주 6~7일 고강도 운동)"));
		pComboBox->AddString(_T("매우 높음(매일 고강도 운동 + 육체적 직업)"));
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CMFCProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCProjectDlg::OnStnClickedStaticAge()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCProjectDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCProjectDlg::OnEnChangeEditAge()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCProjectDlg::OnBnClickedRadioMale()
{
	UpdateData(TRUE); // UI → 변수로 데이터 가져오기

	CString strMessage;

	if (m_bMale == 0) // m_bMale이 0이면 남자
		strMessage = _T("성별: 남자");
	else if (m_bMale == 1) // m_bMale이 1이면 여자
		strMessage = _T("성별: 여자");

	AfxMessageBox(strMessage); // 메시지 출력
}




void CMFCProjectDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CMFCProjectDlg::OnClickedSubmit()
{
	UpdateData(TRUE); // UI → 변수로 데이터 가져오기

	CString strMessage;

	// 성별 판별
	if (m_bMale == 0) // 0: 남자
	{
		strMessage = _T("성별: 남자");
	}
	else if (m_bMale == 1) // 1: 여자
	{
		strMessage = _T("성별: 여자");
	}

	// 메시지 출력
	AfxMessageBox(strMessage);
}





void CMFCProjectDlg::OnCbnSelchangeComboActivity()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
