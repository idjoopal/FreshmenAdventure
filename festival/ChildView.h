// ChildView.h : CChildView Ŭ������ �������̽�
//


#pragma once
#include "atltypes.h"
#include "afxwin.h"




// CChildView â
enum Now {MAIN, MENU, ABOUT, HOW_F,FESTIVAL,RESULT_F , HOW_C,CHEER,RESULT_C,  HOW_M,MIIN,RESULT_M, FINISH};
//����ؾ��� ����

enum Status {FPLAY, FGAMEOVER, FWIN};//���� ����
enum Cheer_Status {CPLAY, CFINISH};//ġ�����
enum Miin_Status {MPLAY, MFINISH};//�����ǹ����
class CChildView : public CWnd
{
// �����Դϴ�.
public:
	CChildView();

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildView();

	// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
/****************************���� �� ����κ�***************************/
	void Main_OnSize(void);
	void Main_Menu(void);
	void Main_Title(void);
	Now now;
	CRect rect_start;
	CRect rect_adventure;
	CRect rect_exit;
	bool main_chk_logo;
/****************************1����, ����***************************/
	void Fes_print(void);
	void Fes_OnPaint(void);
	void Fes_OnSize(void);
	Status status;
	CPoint fes_user_move;
	CRect rect_home;
	CRect rect_boy;
	CRect rect_girl;
	CRect rect_hip;
	CRect rect_obj[14];
	CRect rect_major;
	CRect rect_major2;
	int fes_m_energy;
	int chk_boy;
	int chk_girl;
	int chk_hip;
	bool chk_major;
	bool chk_major2;
	bool chk_start;
/****************************2����, ġ��***************************/
	void Cheer_OnPaint(void);
	void Cheer_OnSize(void);
	Cheer_Status c_status;
	int cheer_player;
	int cheer_ai;
	int cheer_k;
	int cheer_g_Level;
	int cheer_g_RealLevel;
	int cheer_g_Speed;
	int cheer_g_LimitTick;
	int	cheer_g_Score;
	int cheer_g_Combo;
	bool cheer_g_bNext;
/****************************3����, ��Ǯ��***************************/
	void Miin_OnPaint(void);
	void Miin_OnSize(void);
	Miin_Status m_status;
	int miin_p_x;
	int miin_p_y;
	int miin_count;
	int miin_to_i;
	int miin_to_j;
	int miin_ok_i;
	int miin_ok_j;
	int miin_time;
	CRect miin_to;
	CRect miin_ok;
	CPoint miin_m_pt;
	bool miin_chk_to;
	bool miin_chk_ok;
	bool miin_chk_skip;
/****************************�� ���� �� �����***************************/
	void result_OnPaint(void);
	void ResetGame(void);
	
	CRect rect_option;
	int m_menu;
	void About_OnPaint(void);
	CRect rect_back;
	void How_OnPaint(void);
	int total_count;
};

