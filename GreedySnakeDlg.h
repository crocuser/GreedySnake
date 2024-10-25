
// GreedySnakeDlg.h: 头文件
//

#pragma once
#include "Snake.h"

#define MAX_FOOD_GOAL 5
// CGreedySnakeDlg 对话框
class CGreedySnakeDlg : public CDialogEx
{
// 构造
public:
	CGreedySnakeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GREEDYSNAKE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnPause();
    afx_msg void OnContinue();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStart();
    Snake m_Snake1;
    Snake m_Snake2;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    void DrawSnakeAndFood();
    CPoint m_Food;
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    CEdit m_difficult;
    CEdit m_score;
    int m_nScore;
    afx_msg void OnAuto();
    BOOL m_bAuto;
    afx_msg void OnExit();
    BOOL m_bIsSignle;
    afx_msg void OnSignle();
    afx_msg void OnDouble();
    afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
    CEdit m_score1;
    CEdit m_score2;
    CEdit m_goal;
    int m_nScore1;
    int m_nScore2;
};
