
// GreedySnakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GreedySnake.h"
#include "GreedySnakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// CGreedySnakeDlg 对话框



CGreedySnakeDlg::CGreedySnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GREEDYSNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreedySnakeDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT2, m_difficult);
    DDX_Control(pDX, IDC_EDIT1, m_score);
    DDX_Control(pDX, IDC_EDIT3, m_score1);
    DDX_Control(pDX, IDC_EDIT4, m_score2);
    DDX_Control(pDX, IDC_EDIT5, m_goal);
}

BEGIN_MESSAGE_MAP(CGreedySnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_COMMAND(ID_32771, &CGreedySnakeDlg::OnStart)
    ON_WM_TIMER()
    ON_COMMAND(ID_32772, &CGreedySnakeDlg::OnPause)
    ON_COMMAND(ID_32773, &CGreedySnakeDlg::OnContinue)
    ON_COMMAND(ID_32774, &CGreedySnakeDlg::OnAuto)
    ON_COMMAND(ID_32775, &CGreedySnakeDlg::OnExit)
    ON_COMMAND(ID_32776, &CGreedySnakeDlg::OnSignle)
    ON_COMMAND(ID_32777, &CGreedySnakeDlg::OnDouble)
    ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()


// CGreedySnakeDlg 消息处理程序

BOOL CGreedySnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CWnd* pWnd = GetDlgItem(IDC_GAMEREA);
    pWnd->SetWindowPos(NULL, 0, 0, GAMEAREA_WIDTH, GAMEAREA_HEIGHT, SWP_NOZORDER | SWP_NOMOVE);//设置游戏区域大小

    //初始化
    m_nScore = 0;
    CString strDifficult;
    strDifficult.Format(_T("%d"), m_nScore / 3);
    m_difficult.SetWindowText(strDifficult);

    CString strScore;
    strScore.Format(_T("%d"), m_nScore);
    m_score.SetWindowText(strScore);

    CString strGoal;
    strGoal.Format(_T("%d"), MAX_FOOD_GOAL);
    m_goal.SetWindowText(strGoal);

    m_bIsSignle = TRUE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGreedySnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGreedySnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGreedySnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGreedySnakeDlg::OnStart()
{
    // TODO: 在此添加命令处理程序代码
    m_Snake1.Init(10);
    m_nScore = 0;
    m_Snake1.m_DirectionChangeInterval = 200;
    m_bAuto = FALSE;
    //四个Edit控件初始化
    //初始化难度
    CString strDifficult;
    strDifficult.Format(_T("%d"), m_nScore / 3);
    m_difficult.SetWindowText(strDifficult);

    //初始化分数
    CString strScore;
    strScore.Format(_T("%d"), m_nScore);
    m_score.SetWindowText(strScore);
    m_Food = m_Snake1.GenerateFood();//生成食物时会检查是否有蛇身碰撞

    m_nScore1 = 0;
    m_nScore2 = 0;
    m_Snake2.m_DirectionChangeInterval = 200;
    CString strScore1;
    strScore1.Format(_T("%d"), m_nScore1);
    m_score1.SetWindowText(strScore1);

    CString strScore2;
    strScore2.Format(_T("%d"), m_nScore2);
    m_score2.SetWindowText(strScore2);

    if (!m_bIsSignle)
    {
        m_Snake2.Init(15);
        m_Food = m_Snake1.GenerateFood(m_Snake2);//生成食物时会检查是否有蛇身碰撞
    }
    SetTimer(1, m_Snake1.m_DirectionChangeInterval, NULL);//设置定时器，每隔1000ms刷新一次界面
    DrawSnakeAndFood();
}


void CGreedySnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (m_bAuto)
    {
        m_Snake1.AutoDirectionChange(m_Food);
    }
    BOOL bRet1 = m_Snake1.Move(m_Food);
    BOOL bRet2 = TRUE;
    if (!m_bIsSignle)
    {
        bRet2 = m_Snake2.Move(m_Food);
    }
    //判断游戏是否结束  
    if (!bRet1)
    {
        OnPause();//先暂停游戏

        if (m_bIsSignle)//后根据胜利者显示提示信息
        {
            MessageBox(_T("游戏结束!"), _T("提示"), MB_OK);
        }
        else
        {
            MessageBox(_T("游戏结束,玩家2获胜!"), _T("提示"), MB_OK);
        }
        return;
    }
    else if(!m_bIsSignle && !bRet2)
    {
        OnPause();

        MessageBox(_T("游戏结束,玩家1获胜!"), _T("提示"), MB_OK);
        return;
    }
    else if(bRet1 && bRet2)//移动成功，并且吃到了食物
    {
        if (m_bIsSignle && m_Snake1.IsGrow())
        {
            m_nScore += 1;
            m_Food = m_Snake1.GenerateFood();
            if (m_nScore % 3 == 0)
            {
                if (m_nScore / 3 < 6)
                {
                    CString strDifficult;
                    strDifficult.Format(_T("%d"), m_nScore / 3);
                    m_difficult.SetWindowText(strDifficult);
                    m_Snake1.m_DirectionChangeInterval -= m_nScore / 3 * 10;
                    SetTimer(1, m_Snake1.m_DirectionChangeInterval, NULL);//更改定时器间隔（移动速度）
                }
            }
            //初始化分数
            CString strScore;
            strScore.Format(_T("%d"), m_nScore);
            m_score.SetWindowText(strScore);
        }
        else if(!m_bIsSignle && (m_Snake1.IsGrow() || m_Snake2.IsGrow()))
        {
            if (m_Snake1.IsGrow())
            {
                m_nScore1++;
                if (m_nScore1 >= MAX_FOOD_GOAL)
                {
                    OnPause();
                    MessageBox(_T("游戏结束,玩家1率先吃到目标数食物，获胜!"), _T("提示"), MB_OK);
                }
            }
            else 
            {
                m_nScore2++;
                if (m_nScore2 >= MAX_FOOD_GOAL)
                {
                    OnPause();
                    MessageBox(_T("游戏结束,玩家2率先吃到目标数食物，获胜!"), _T("提示"), MB_OK);
                }
            }
            CString strScore1;
            strScore1.Format(_T("%d"), m_nScore1);
            m_score1.SetWindowText(strScore1);

            CString strScore2;
            strScore2.Format(_T("%d"), m_nScore2);
            m_score2.SetWindowText(strScore2);
            m_Food = m_Snake1.GenerateFood(m_Snake2);
        }
    }
  
    DrawSnakeAndFood();

    CDialogEx::OnTimer(nIDEvent);
}

void CGreedySnakeDlg::DrawSnakeAndFood()
{
    CWnd* pWnd = GetDlgItem(IDC_GAMEREA);
    pWnd->Invalidate();
    pWnd->UpdateWindow();
    CDC* pDC = pWnd->GetDC();
    //TODO: 增加蛇的绘制
    m_Snake1.Draw(pDC,RGB(0,255,0));
    if (!m_bIsSignle)
    {
        m_Snake2.Draw(pDC, RGB(0, 0, 255));
    }
    //TODO: 增加食物的绘制
    int left = m_Food.x * SNAKE_BODYSIZE;
    int top = m_Food.y * SNAKE_BODYSIZE;
    int right = left + SNAKE_BODYSIZE;
    int bottom = top + SNAKE_BODYSIZE;
    CBrush brush(RGB(255, 0, 0));
    pDC->SelectObject(&brush);
    pDC->Rectangle(left, top, right, bottom);
    DeleteObject(brush);

    pWnd->ReleaseDC(pDC);

}

BOOL CGreedySnakeDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    //禁用方向键的默认行为
    if (pMsg->message == WM_KEYDOWN)
    {
        UINT nChar = pMsg->wParam;
        DWORD currentTime = ::GetTickCount();
        if (currentTime - m_Snake1.m_LastDirectionChangeTime > m_Snake1.m_DirectionChangeInterval) //限制方向更新频率（时间阈值）
        {
            switch (nChar)
            {
            case VK_LEFT:
                m_Snake1.SetDirection(LEFT);
                break;
            case VK_RIGHT:
                m_Snake1.SetDirection(RIGHT);
                break;
            case VK_UP:
                m_Snake1.SetDirection(UP);
                break;
            case VK_DOWN:
                m_Snake1.SetDirection(DOWN);
                break;
            }
            m_Snake1.m_LastDirectionChangeTime = currentTime;
        }
        if (!m_bIsSignle && currentTime - m_Snake2.m_LastDirectionChangeTime > m_Snake2.m_DirectionChangeInterval) //限制方向更新频率（时间阈值）
        {
            switch (nChar)
            {
            case 'A':
            case 'a':
                m_Snake2.SetDirection(LEFT);
                break;
            case 'D':
            case 'd':
                m_Snake2.SetDirection(RIGHT);
                break;
            case 'W':
            case 'w':
                m_Snake2.SetDirection(UP);
                break;
            case 'S':
            case's':
                m_Snake2.SetDirection(DOWN);
                break;
            }
            m_Snake2.m_LastDirectionChangeTime = currentTime;
        }
    }
    return CDialogEx::PreTranslateMessage(pMsg);
}



void CGreedySnakeDlg::OnPause()
{
    // TODO: 在此添加命令处理程序代码
    KillTimer(1);
}


void CGreedySnakeDlg::OnContinue()
{
    // TODO: 在此添加命令处理程序代码
    SetTimer(1, m_Snake1.m_DirectionChangeInterval, NULL);
}


void CGreedySnakeDlg::OnAuto()
{
    // TODO: 在此添加命令处理程序代码
    m_bAuto = !m_bAuto;
}


void CGreedySnakeDlg::OnExit()
{
    // TODO: 在此添加命令处理程序代码
    exit(0);
}


void CGreedySnakeDlg::OnSignle()
{
    // TODO: 在此添加命令处理程序代码
    m_bIsSignle = !m_bIsSignle;
}

void CGreedySnakeDlg::OnDouble()
{
    // TODO: 在此添加命令处理程序代码
    m_bIsSignle = !m_bIsSignle;

}

void CGreedySnakeDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

    // TODO: 在此处添加消息处理程序代码
    if (nIndex == 1)
    {
        if (m_bIsSignle)
        {
            pPopupMenu->CheckMenuItem(ID_32776, MF_CHECKED);
            pPopupMenu->CheckMenuItem(ID_32777, MF_UNCHECKED);
        }
        else
        {
            pPopupMenu->CheckMenuItem(ID_32776, MF_UNCHECKED);
            pPopupMenu->CheckMenuItem(ID_32777, MF_CHECKED);
        }
    }
}
