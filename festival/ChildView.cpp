// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Festival.h"
#include "ChildView.h"

#define OBJ 74
#define USERMOVE 7

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
: main_chk_logo(false)
, fes_user_move(0)
, fes_m_energy(0)
, chk_boy(0)
, chk_girl(0)
, chk_hip(0)
, chk_major(false)
, chk_major2(false)
, chk_start(false)
, miin_p_x(50)
, miin_p_y(240)
, miin_count(10)
, miin_to_i(0)
, miin_to_j(0)
, miin_ok_i(0)
, miin_ok_j(0)
, miin_m_pt(0)
, miin_chk_to(false)
, miin_chk_ok(false)
, miin_chk_skip(false)
, miin_time(0)
, cheer_player(3)
, cheer_ai(0)
, cheer_k(-2)
, cheer_g_Level(0)
, cheer_g_RealLevel(1)
, cheer_g_Speed(50)
, cheer_g_LimitTick(0)
, cheer_g_Score(0)
, cheer_g_Combo(0)
, cheer_g_bNext(false)
, m_menu(0)
, total_count(0)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

	if(now==MAIN)
	{
		Main_Title();
	}
	else if(now==MENU)
	{
		Main_Title();
	}
	else if(now==ABOUT)
	{
		About_OnPaint();
	}
	else if(now==HOW_F)
	{
		How_OnPaint();
	}
	else if(now==FESTIVAL)
	{
		Fes_OnPaint();
	}
	else if(now==RESULT_F)
	{
		result_OnPaint();
	}
	else if(now==HOW_C)
	{
		How_OnPaint();
	}
	else if(now==CHEER)
	{
		Cheer_OnPaint();
	}
	else if(now==RESULT_C)
	{
		result_OnPaint();
	}
	else if(now==HOW_M)
	{
		How_OnPaint();
	}
	else if(now==MIIN)
	{
		Miin_OnPaint();
	}
	else if(now==RESULT_M)
	{
		result_OnPaint();
	}
	/* 여기다가 마지막 결과값을 받아오는 부분을 그릴것.*/
	else if(now==FINISH)
	{
		result_OnPaint();
	}
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(now==MAIN)
	{
		switch(nIDEvent)
		{
		case 1:
			if(chk_start == false)
			{
				chk_start = true;
			}else
			{
				chk_start = false;
			}
			if(main_chk_logo == false)
			{
				main_chk_logo = true;
			}
			Main_Title();
			break;
		}
	}
	else if(now==MENU)
	{
		m_menu+=2;

		if(m_menu>=480)
		{
			m_menu = 0;
		}
		Main_Menu();
	}
	else if(now==ABOUT)
	{
		m_menu+=2;

		if(m_menu>=480)
		{
			m_menu = 0;
		}
		Invalidate(false);
	}
	else if(now==FESTIVAL)
	{
		switch(nIDEvent)
		{
		case 1:
			if(rect_home.PtInRect(fes_user_move))
			{
				fes_m_energy = 0;
			}
			else
			{
				if(fes_m_energy<470)
				{
					fes_m_energy +=5;
					Invalidate(false);
				}
				else
				{
					KillTimer(1);
					KillTimer(2);
					status = FGAMEOVER;
					Invalidate(false);
				}
			}
			break;
		case 2:
			if(rect_major.right>=23+5*OBJ)
			{
				chk_major = true;
			}
			if(rect_major.left<=23)
			{
				chk_major = false;
			}

			if(chk_major==true)
			{
				rect_major.left -= 2;
				rect_major.right -= 2;
			}
			else
			{
				rect_major.left += 2;
				rect_major.right += 2;
			}

			if(rect_major2.bottom>=90+5*OBJ)
			{
				chk_major2 = true;
			}
			if(rect_major2.top<=80+3*OBJ)
			{
				chk_major2 = false;
			}

			if(chk_major2==true)
			{
				rect_major2.top -= 2;
				rect_major2.bottom -= 2;
			}
			else
			{
				rect_major2.top += 2;
				rect_major2.bottom += 2;
			}
			Invalidate(false);
			break;
		}
	}
	else if(now==CHEER)
	{
		Invalidate(false);
	}
	else if(now==MIIN)
	{
		if(miin_chk_skip == false)
		{
			miin_count--;
		}
		miin_chk_skip = false;
		miin_chk_to = false;
		miin_chk_ok = false;

		switch(nIDEvent)
		{
		case 1:
			srand((unsigned)time(NULL));

			miin_to_i = rand()%2;
			miin_to_j = rand()%3;

			do
			{
				miin_ok_i = rand()%2;
				miin_ok_j = rand()%3;

			}while(miin_to_i==miin_ok_i && miin_to_j==miin_ok_j);

			miin_to.left=50+200*miin_to_j;
			miin_to.right=150+50+200*miin_to_j;
			miin_to.top=130+220*miin_to_i;
			miin_to.bottom=150+130+220*miin_to_i;

			miin_ok.left=50+200*miin_ok_j;
			miin_ok.right=150+50+200*miin_ok_j;
			miin_ok.top=130+220*miin_ok_i;
			miin_ok.bottom=150+130+220*miin_ok_i;
			break;
		}
		miin_time++;
		Invalidate(false);
	}

	CWnd::OnTimer(nIDEvent);
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	now = MAIN;
	Main_OnSize();
	Fes_OnSize();
	Miin_OnSize();
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(now==MAIN)
	{
	}
	else if(now==FESTIVAL)
	{
		if(status == FPLAY)
		{
			switch(nChar)
			{
			case VK_LEFT:
				if(fes_user_move.x <= 41)
				{
					break;
				}
				else
				{
					fes_user_move.x -= USERMOVE;
					for(int i=0;i<13;i++)
					{
						if(rect_obj[i].PtInRect(fes_user_move))
						{
							fes_user_move.x += USERMOVE;
							break;
						}
					}
					break;
				}

			case VK_RIGHT:
				if(fes_user_move.x >= 600)
				{
					break;
				}
				else
				{
					fes_user_move.x += USERMOVE;
					for(int i=0;i<13;i++)
					{
						if(rect_obj[i].PtInRect(fes_user_move))
						{
							fes_user_move.x -= USERMOVE;
							break;
						}
					}
					break;
				}

			case VK_UP:
				if(fes_user_move.y <= 100)
				{
					break;
				}
				else
				{
					fes_user_move.y -= USERMOVE;
					for(int i=0;i<13;i++)
					{
						if(rect_obj[i].PtInRect(fes_user_move))
						{
							fes_user_move.y += USERMOVE;
							break;
						}
					}
					break;
				}

			case VK_DOWN:
				if(fes_user_move.y >= 440)
				{
					break;
				}
				else
				{
					fes_user_move.y += USERMOVE;
					for(int i=0;i<13;i++)
					{
						if(rect_obj[i].PtInRect(fes_user_move))
						{
							fes_user_move.y -= USERMOVE;
							break;
						}
					}
					break;
				}

			}
		}
		if(rect_boy.PtInRect(fes_user_move))
		{
			chk_boy = 1;
		}
		if(rect_girl.PtInRect(fes_user_move))
		{
			chk_girl = 1;
		}
		if(rect_hip.PtInRect(fes_user_move))
		{
			chk_hip = 1;
		}

		if(rect_major.PtInRect(fes_user_move) || rect_major2.PtInRect(fes_user_move))
		{
			KillTimer(1);
			KillTimer(2);
			status = FGAMEOVER;
			Invalidate(false);
		}
		Fes_print();

		if(chk_boy+chk_girl+chk_hip==3 && rect_home.PtInRect(fes_user_move))
		{
			KillTimer(1);
			KillTimer(2);
			status = FWIN;
			Invalidate(false);
		}
	}
	else if(now==CHEER)
	{
		if( cheer_g_LimitTick > cheer_g_Speed*2 )
		{
			switch(nChar)
			{
			case VK_LEFT :
				cheer_player = 0;
				break;
			case VK_UP : 
				cheer_player = 1;
				break;
			case VK_RIGHT :	
				cheer_player = 2;
				break;
			}
			Invalidate(false);
		}
	}
	else if(now==MIIN)
	{
		switch(nChar)
		{
		case VK_LEFT:
			if(miin_p_x > 50 && miin_p_y == 240 ) //통로에잇을때만움직이도록
			{
				miin_p_x-=200;//플레이어의x좌표변경
			}
			break;
		case VK_RIGHT:
			if( miin_p_x < 450 && miin_p_y == 240 )//통로에잇을때만
			{
				miin_p_x+=200;//플레이어비트맵의x좌표움직임
			}
			break;
		case VK_UP:
			if( miin_p_y > 130)//플레이어의 비트맵이범위를벗어나지않도록
			{
				miin_p_y-=110;//플레이어비트맵의y좌표변경
			}
			break;
		case VK_DOWN:
			if( miin_p_y < 350 )//플레이어비트맵이범위를벗어나지않도록
			{
				miin_p_y+=110;//플레이어비트맵의y좌표변경
			}
			break;
		}//방향키눌럿을때셋타이머돌아감

		if(miin_to.PtInRect(miin_m_pt))
		{
			miin_count++;
			miin_chk_to = true;
			miin_chk_skip = true;
		}
		if(miin_ok.PtInRect(miin_m_pt))
		{
			miin_count-=2;
			miin_chk_ok = true;
			miin_chk_skip = true;
		}

		Invalidate(false);

	}


	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::Fes_OnPaint(void)
{
	if(status==FPLAY)
	{
		Fes_print();
	}
	else if(status == FGAMEOVER)
	{
		CString str;
		int count = chk_boy+chk_girl+chk_hip;
		str.Format(_T("게임오버, %d명 성공"),count);
		AfxMessageBox((LPCTSTR)str);
		now = RESULT_F;
		Invalidate(false);

	}
	else if(status == FWIN)
	{
		AfxMessageBox(_T("성공!^0^"));
		now = RESULT_F;
		Invalidate(false);
	}
}

void CChildView::Fes_print(void)
{
	CClientDC dc(this);
		
	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap fes_bg;
	CBitmap fes_char;
	CBitmap fes_vobj;
	CBitmap fes_hobj;
	CBitmap fes_home;
	CBitmap fes_boy;
	CBitmap fes_girl;
	CBitmap fes_hiphop;
	CBitmap fes_cycle;
	CBitmap fes_friend;
	CBitmap fes_call;
	CBitmap fes_energy;
	CBitmap fes_major;

	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	fes_bg.LoadBitmapW(IDB_BITMAP1);
	fes_char.LoadBitmapW(IDB_BITMAP2);
	fes_vobj.LoadBitmapW(IDB_BITMAP3);
	fes_hobj.LoadBitmapW(IDB_BITMAP4);
	fes_home.LoadBitmapW(IDB_BITMAP5);
	fes_boy.LoadBitmapW(IDB_BITMAP6);
	fes_girl.LoadBitmapW(IDB_BITMAP7);
	fes_hiphop.LoadBitmapW(IDB_BITMAP8);
	fes_cycle.LoadBitmapW(IDB_BITMAP9);
	fes_friend.LoadBitmapW(IDB_BITMAP10);
	fes_call.LoadBitmapW(IDB_BITMAP11);
	fes_energy.LoadBitmapW(IDB_BITMAP12);
	fes_major.LoadBitmapW(IDB_BITMAP13);

	fes_bg.GetBitmap(&bmpinfo); //비트맵의 정보를 불러온다

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&fes_bg);
	buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경
	
	fes_energy.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_energy);
	buffdc.StretchBlt(150,60,bmpinfo.bmWidth-fes_m_energy,bmpinfo.bmHeight,
		&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,SRCCOPY);//에너지바

	fes_home.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_home);//인미천막, 에너지회복
	buffdc.TransparentBlt(30,390,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	/****************************************장애물기준*******************************************/
	//buffdc.TransparentBlt(23,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	buffdc.TransparentBlt(23+2*OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+3*OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+4*OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+5*OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_vobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_vobj);
	buffdc.TransparentBlt(23+6*OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+7*OBJ,91,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	buffdc.TransparentBlt(23,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_vobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_vobj);
	buffdc.TransparentBlt(23+2*OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+3*OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	buffdc.TransparentBlt(23+4*OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+5*OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+6*OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+7*OBJ,91+OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	//buffdc.TransparentBlt(23,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+2*OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+3*OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+4*OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_vobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_vobj);
	buffdc.TransparentBlt(23+5*OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	
	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	buffdc.TransparentBlt(23+6*OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+7*OBJ,91+2*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	fes_vobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_vobj);
	buffdc.TransparentBlt(23,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	
	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	buffdc.TransparentBlt(23+OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+2*OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_vobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_vobj);
	buffdc.TransparentBlt(23+3*OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+4*OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	buffdc.TransparentBlt(23+5*OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+6*OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_vobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_vobj);
	buffdc.TransparentBlt(23+7*OBJ,91+3*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	//buffdc.TransparentBlt(23,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+2*OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	fes_hobj.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_hobj);
	buffdc.TransparentBlt(23+3*OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+4*OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+5*OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+6*OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	//buffdc.TransparentBlt(23+7*OBJ,91+4*OBJ,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	/*********************************************************************************************/
	
	if(chk_boy==0)
	{
		fes_boy.GetBitmap(&bmpinfo);
		memdc.SelectObject(&fes_boy);//남자연예인
		buffdc.TransparentBlt(20,95,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	}

	if(chk_girl==0)
	{
		fes_girl.GetBitmap(&bmpinfo);
		memdc.SelectObject(&fes_girl);//여자연예인
		buffdc.TransparentBlt(560,95,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	}

	if(chk_hip==0)
	{
		fes_hiphop.GetBitmap(&bmpinfo);
		memdc.SelectObject(&fes_hiphop);//래퍼
		buffdc.TransparentBlt(550,390,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	}


	fes_char.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_char);//캐릭터, 움직이는거
	buffdc.TransparentBlt(fes_user_move.x-22,fes_user_move.y-22,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));


	fes_major.GetBitmap(&bmpinfo);
	memdc.SelectObject(&fes_major);//회장 가로이동
	buffdc.TransparentBlt(rect_major.left,rect_major.top, bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	buffdc.TransparentBlt(rect_major2.left,rect_major2.top, bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&buffdc,0,0,SRCCOPY); //buffdc에 저장한 그림들을 뿌림.

	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제
}

void CChildView::Main_Title(void)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap main_logo;
	CBitmap main_bg;
	CBitmap main_start;

	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	main_logo.LoadBitmapW(IDB_BITMAP43);
	main_bg.LoadBitmapW(IDB_BITMAP14);
	main_start.LoadBitmapW(IDB_BITMAP15);

	main_bg.GetBitmap(&bmpinfo);
	//비트맵의 정보를 불러온다

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&main_bg);
	buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경

	main_logo.GetBitmap(&bmpinfo);
	memdc.SelectObject(&main_logo);

	if(main_chk_logo == false)
	{
		buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경
	
	}

	main_start.GetBitmap(&bmpinfo);
	memdc.SelectObject(&main_start);

	if(chk_start == true)
	{
		buffdc.TransparentBlt(190,390,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));
	}

	SetTimer(1,1000,NULL);

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&buffdc,0,0,SRCCOPY); //buffdc에 저장한 그림들을 뿌림.

	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제
}

void CChildView::Fes_OnSize(void)
{
	fes_m_energy = 10;

	fes_user_move.x = 52;
	fes_user_move.y = 420;
	//유저시작좌표(30,398)(52,420)(74,442)

	rect_home.left=30;
	rect_home.right=75;	
	rect_home.top=390;
	rect_home.bottom=455;

	rect_boy.left=20;
	rect_boy.right=84;	
	rect_boy.top=95;
	rect_boy.bottom=155;

	rect_girl.left=540;
	rect_girl.right=606;	
	rect_girl.top=95;
	rect_girl.bottom=161;

	rect_hip.left=550;
	rect_hip.right=616;	
	rect_hip.top=390;
	rect_hip.bottom=456;

	rect_major.left=23;
	rect_major.right=83;
	rect_major.top=100+2*OBJ;
	rect_major.bottom=100+2*OBJ+60;

	rect_major2.left=23+6*OBJ;
	rect_major2.right=83+6*OBJ;
	rect_major2.top=100+3*OBJ;
	rect_major2.bottom=100+3*OBJ+60;

	rect_obj[0].left=23+2*OBJ;
	rect_obj[0].right=23+3*OBJ;
	rect_obj[0].top=91;
	rect_obj[0].bottom=91+OBJ;

	rect_obj[1].left=23+6*OBJ;
	rect_obj[1].right=23+7*OBJ;
	rect_obj[1].top=91;
	rect_obj[1].bottom=91+OBJ;

	rect_obj[2].left=23;
	rect_obj[2].right=23+OBJ;
	rect_obj[2].top=91+OBJ;
	rect_obj[2].bottom=91+2*OBJ;

	rect_obj[3].left=23+2*OBJ;
	rect_obj[3].right=23+3*OBJ;
	rect_obj[3].top=91+OBJ;
	rect_obj[3].bottom=91+2*OBJ;

	rect_obj[4].left=23+4*OBJ;
	rect_obj[4].right=23+5*OBJ;
	rect_obj[4].top=91+OBJ;
	rect_obj[4].bottom=91+2*OBJ;

	rect_obj[5].left=23+5*OBJ;
	rect_obj[5].right=23+6*OBJ;
	rect_obj[5].top=91+2*OBJ;
	rect_obj[5].bottom=91+3*OBJ;

	rect_obj[6].left=23+6*OBJ;
	rect_obj[6].right=23+7*OBJ;
	rect_obj[6].top=91+2*OBJ;
	rect_obj[6].bottom=91+3*OBJ;

	rect_obj[7].left=23;
	rect_obj[7].right=23+OBJ;
	rect_obj[7].top=91+3*OBJ;
	rect_obj[7].bottom=91+4*OBJ;

	rect_obj[8].left=23+OBJ;
	rect_obj[8].right=23+2*OBJ;
	rect_obj[8].top=91+3*OBJ;
	rect_obj[8].bottom=91+4*OBJ;

	rect_obj[9].left=23+3*OBJ;
	rect_obj[9].right=23+4*OBJ;
	rect_obj[9].top=91+3*OBJ;
	rect_obj[9].bottom=91+4*OBJ;

	rect_obj[10].left=23+5*OBJ;
	rect_obj[10].right=23+6*OBJ;
	rect_obj[10].top=91+3*OBJ;
	rect_obj[10].bottom=91+4*OBJ;

	rect_obj[11].left=23+7*OBJ;
	rect_obj[11].right=23+8*OBJ;
	rect_obj[11].top=91+3*OBJ;
	rect_obj[11].bottom=91+4*OBJ;

	rect_obj[12].left=23+3*OBJ;
	rect_obj[12].right=23+4*OBJ;
	rect_obj[12].top=91+4*OBJ;
	rect_obj[12].bottom=91+5*OBJ;

	status = FPLAY;

	SetTimer(1,200,NULL);//에너지 점점감소
	SetTimer(2,20,NULL);// 지섭이형 움직임

}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(now==MAIN)
	{
		if(rect_start.PtInRect(point))
		{
			KillTimer(1);
			now=MENU;
			SetTimer(1,50,NULL);
			Main_Menu();
		}
	}
	else if(now==MENU)
	{
		if(rect_adventure.PtInRect(point))
		{
			KillTimer(1);
			now=HOW_F;
			Invalidate(false);
		}

		if(rect_option.PtInRect(point))
		{
			now=ABOUT;
			About_OnPaint();
		}

		if(rect_exit.PtInRect(point))
		{
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
		}
		
	}
	else if(now==ABOUT)
	{
		if(rect_back.PtInRect(point))
		{
			KillTimer(1);
			now=MENU;
			SetTimer(1,50,NULL);
			Main_Menu();
		}
	}
	else if(now==HOW_F)
	{
		now=FESTIVAL;
		Fes_OnSize();
		Invalidate(false);
	}
	else if(now==FESTIVAL)
	{
		Fes_OnPaint();
	}
	else if(now==RESULT_F)
	{
		now = HOW_C;
		//now = CHEER;
		Invalidate(false);
		Cheer_OnSize();
		
	}
	else if(now==HOW_C)
	{
		now = CHEER;
		Invalidate(false);
		Cheer_OnSize();
	}
	else if(now==RESULT_C)
	{
		now = HOW_M;
		Invalidate(false);
	}
	else if(now==HOW_M)
	{
		now = MIIN;
		Invalidate(false);
		Miin_OnSize();
	}
	else if(now==RESULT_M)
	{
		now = FINISH;
		Invalidate(false);
		/*Main_OnSize();
		ResetGame();*/
	}
	else if(now==FINISH)
	{
		now = MAIN;
		Invalidate(false);
		Main_OnSize();
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::Main_OnSize(void)
{
	rect_start.left=190;
	rect_start.right=470;
	rect_start.top=390;
	rect_start.bottom=450;

	rect_adventure.left=140;
	rect_adventure.right=520;
	rect_adventure.top=115;
	rect_adventure.bottom=160;

	rect_option.left=240;
	rect_option.right=400;
	rect_option.top=250;
	rect_option.bottom=300;

	rect_back.left=430;
	rect_back.right=600;
	rect_back.top=55;
	rect_back.bottom=70;

	rect_exit.left=270;
	rect_exit.right=380;
	rect_exit.top=380;
	rect_exit.bottom=430;
}

void CChildView::Main_Menu(void)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap menubg;
	CBitmap menu;

	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	menubg.LoadBitmapW(IDB_BITMAP44);
	menu.LoadBitmapW(IDB_BITMAP16);
	
	menubg.GetBitmap(&bmpinfo); //비트맵의 정보를 불러온다

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&menubg);

	buffdc.BitBlt(0,-m_menu,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경

	menu.GetBitmap(&bmpinfo);
	memdc.SelectObject(&menu);
	buffdc.TransparentBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&buffdc,0,0,SRCCOPY); //buffdc에 저장한 그림들을 뿌림.

	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제
}

BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest == HTCLIENT) //마우스커서위치가 클라이언트 내부에 있을때
	{
		CPoint pt;

		GetCursorPos(&pt);
		ScreenToClient(&pt);

		SetCursor(AfxGetApp()->LoadCursorW(IDC_CURSOR1)); 

		return true;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CChildView::Miin_OnPaint(void)
{
	CClientDC dc(this);

	miin_m_pt.x = miin_p_x+50;
	miin_m_pt.y = miin_p_y+50;

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;
	CDC buffdc;

	CBitmap bmpbuffer;

	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);
	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());

	BITMAP bmpinfo;

	CBitmap miin_bg;
	miin_bg.LoadBitmapW(IDB_BITMAP17); // 방 비트맵

	CBitmap miin_spew;
	miin_spew.LoadBitmapW(IDB_BITMAP18); //토한 비트맵

	CBitmap miin_good;
	miin_good.LoadBitmapW(IDB_BITMAP19); //멀쩡한 비트맵

	CBitmap miin_player;
	miin_player.LoadBitmapW(IDB_BITMAP20); // 플레이어 비트맵
	
	CBitmap miin_normal;
	miin_normal.LoadBitmapW(IDB_BITMAP21);
	
	CBitmap miin_thanks;
	miin_thanks.LoadBitmapW(IDB_BITMAP22);

	CBitmap miin_angry;
	miin_angry.LoadBitmapW(IDB_BITMAP23);


	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&miin_bg);
	miin_bg.GetBitmap(&bmpinfo);
	buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경

	CString str;
	buffdc.SetBkMode(TRANSPARENT);
	str.Format(_T("%d"),miin_count);	
	buffdc.TextOutW(200,80,str); //점수 출력

	miin_normal.GetBitmap(&bmpinfo);
	memdc.SelectObject(&miin_normal);

	srand((unsigned)time(NULL));
	int a=rand()%3;
	int b=rand()%2;
	int c=rand()%3;
	int d=rand()%2;
	buffdc.TransparentBlt(50+200*a,130+220*b,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(255,0,0));//플레이어 비트맵 
	buffdc.TransparentBlt(50+200*c,130+220*d,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(255,0,0));//플레이어 비트맵 
	
	if(miin_chk_to == true)
	{
		miin_thanks.GetBitmap(&bmpinfo);
		memdc.SelectObject(&miin_thanks);
		buffdc.TransparentBlt(50+200*miin_to_j,130+220*miin_to_i,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(255,0,0));//플레이어 비트맵 
	}
	else
	{
		miin_spew.GetBitmap(&bmpinfo);
		memdc.SelectObject(&miin_spew);
		buffdc.TransparentBlt(50+200*miin_to_j,130+220*miin_to_i,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(255,0,0));//플레이어 비트맵 
	}

	if(miin_chk_ok == true)
	{
		miin_angry.GetBitmap(&bmpinfo);
		memdc.SelectObject(&miin_angry);
		buffdc.TransparentBlt(50+200*miin_ok_j,130+220*miin_ok_i,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(255,0,0));//플레이어 비트맵 
	}
	else
	{
		miin_good.GetBitmap(&bmpinfo);
		memdc.SelectObject(&miin_good);
		buffdc.TransparentBlt(50+200*miin_ok_j,130+220*miin_ok_i,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(255,0,0));//플레이어 비트맵 
	}


	miin_player.GetBitmap(&bmpinfo);
	memdc.SelectObject(&miin_player);
	buffdc.TransparentBlt(miin_p_x,miin_p_y,100,100,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(192,192,192));//플레이어 비트맵 

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&buffdc,0,0,SRCCOPY); //buffdc에 저장한 그림들을 뿌림.

	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제

	if(miin_time>=30)
	{
		m_status = MFINISH;
		now = RESULT_M;
		KillTimer(1);
		AfxMessageBox(_T("게임끝!"));
		Invalidate(false);
	}
}

void CChildView::Miin_OnSize(void)
{
	m_status = MPLAY;

	SetTimer(1,1000,NULL);
}

void CChildView::Cheer_OnPaint(void)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap cheer_bg;
	CBitmap cheer_a_b;
	CBitmap cheer_a[3];
	CBitmap cheer_p_b;
	CBitmap cheer_p[4];
	CBitmap cheer_a_cover;

	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	cheer_bg.LoadBitmapW(IDB_BITMAP24);
	cheer_a_b.LoadBitmapW(IDB_BITMAP25);
	cheer_a[0].LoadBitmapW(IDB_BITMAP27);
	cheer_a[1].LoadBitmapW(IDB_BITMAP26);
	cheer_a[2].LoadBitmapW(IDB_BITMAP28);

	cheer_p[3].LoadBitmapW(IDB_BITMAP29);

	cheer_p[0].LoadBitmapW(IDB_BITMAP31);
	cheer_p[1].LoadBitmapW(IDB_BITMAP30);
	cheer_p[2].LoadBitmapW(IDB_BITMAP32);
	cheer_a_cover.LoadBitmapW(IDB_BITMAP33);

	cheer_bg.GetBitmap(&bmpinfo);

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&cheer_bg);
	buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경


	CString str;
	buffdc.SetBkMode(TRANSPARENT);

	str.Format(_T("%d"), cheer_g_Score );
	buffdc.TextOut(150,75,str);

	str.Format(_T("레벨 : %d"), cheer_g_RealLevel );
	buffdc.TextOut(30,110,str );

	str.Format(_T("%d콤보!! 추가점수!"), cheer_g_Combo);
	buffdc.TextOut(260,120,str );
	/***********************************기본베이스**************************************/
	cheer_a_b.GetBitmap(&bmpinfo);
	memdc.SelectObject(&cheer_a_b);
	buffdc.TransparentBlt(50,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));
	buffdc.TransparentBlt(210,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));

	cheer_p[3].GetBitmap(&bmpinfo);
	memdc.SelectObject(&cheer_p[3]);
	buffdc.TransparentBlt(370,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));
	/***********************************************************************************/


	cheer_g_LimitTick++;

	if( cheer_g_LimitTick > cheer_g_Speed*1 )
	{
		cheer_a_cover.GetBitmap(&bmpinfo);
		memdc.SelectObject(&cheer_a_cover);
		buffdc.TransparentBlt(50,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));

		cheer_a[cheer_ai].GetBitmap(&bmpinfo);
		memdc.SelectObject(&cheer_a[cheer_ai]);
		buffdc.TransparentBlt(50,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));
	}
	if( cheer_g_LimitTick > cheer_g_Speed*2 )
	{	
		cheer_a_cover.GetBitmap(&bmpinfo);
		memdc.SelectObject(&cheer_a_cover);
		buffdc.TransparentBlt(210,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));

		cheer_a[cheer_ai].GetBitmap(&bmpinfo);
		memdc.SelectObject(&cheer_a[cheer_ai]);
		buffdc.TransparentBlt(210,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));
	}

	if( cheer_g_LimitTick > cheer_g_Speed*3 )
	{
		cheer_a_cover.GetBitmap(&bmpinfo);
		memdc.SelectObject(&cheer_a_cover);
		buffdc.TransparentBlt(370,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));

		cheer_p[cheer_player].GetBitmap(&bmpinfo);
		memdc.SelectObject(&cheer_p[cheer_player]);
		buffdc.TransparentBlt(370,180,200,200,&memdc,0,0,200,200,RGB(200,200,200));
	}
	if( cheer_g_LimitTick > cheer_g_Speed*4 )
	{
		if( cheer_player != cheer_ai )
		{
			cheer_k=-2;
			cheer_g_Combo=0;
			cheer_g_LimitTick = 0;
			cheer_g_Score-=100;
			cheer_g_Level++;

			if( cheer_g_Level > 1 )
			{
				cheer_g_Speed-=2;
				cheer_g_RealLevel ++;
				cheer_g_Level = 0;
			}
		}
		else
		{
			cheer_k+=2;
			cheer_g_Score+=10+cheer_k;
			cheer_g_LimitTick = 0;
			cheer_g_Level++;
			cheer_g_Combo++;

			if( cheer_g_Level > 1 )
			{
				cheer_g_Speed-=2;
				cheer_g_RealLevel ++;
				cheer_g_Level = 0;
			}
			srand(GetTickCount());
			cheer_ai = rand()%3;
			cheer_player = 3;
		}
	}
	dc.BitBlt(0,0, rect.right, rect.bottom, &buffdc, 0,0, SRCCOPY);
	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제

	if(cheer_g_RealLevel == 21)
	{
		now = RESULT_C;
		KillTimer(1);
		AfxMessageBox(_T("치어가 종료되었습니다"));
		Invalidate(false);
		
	}
}

void CChildView::Cheer_OnSize(void)
{
	SetTimer(1,10,NULL);
}

void CChildView::result_OnPaint(void)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap result_f_a;
	CBitmap result_f_b;
	CBitmap result_f_c;
	CBitmap result_c_a;
	CBitmap result_c_b;
	CBitmap result_c_c;
	CBitmap result_m_a;
	CBitmap result_m_b;
	CBitmap result_m_c;
	CBitmap result_t_a;
	CBitmap result_t_b;
	CBitmap result_t_c;

	
	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	result_f_a.LoadBitmapW(IDB_BITMAP34);
	result_f_b.LoadBitmapW(IDB_BITMAP35);
	result_f_c.LoadBitmapW(IDB_BITMAP36);
	result_c_a.LoadBitmapW(IDB_BITMAP37);
	result_c_b.LoadBitmapW(IDB_BITMAP38);
	result_c_c.LoadBitmapW(IDB_BITMAP39);
	result_m_a.LoadBitmapW(IDB_BITMAP40);
	result_m_b.LoadBitmapW(IDB_BITMAP41);
	result_m_c.LoadBitmapW(IDB_BITMAP42);
	result_t_a.LoadBitmapW(IDB_BITMAP49);
	result_t_b.LoadBitmapW(IDB_BITMAP50);
	result_t_c.LoadBitmapW(IDB_BITMAP51);

	

	result_f_a.GetBitmap(&bmpinfo);

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&result_f_a);


	if(now==RESULT_F)
	{
		if(chk_boy+chk_girl+chk_hip==3 && status == FWIN)
		{
			result_f_a.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_f_a);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count + 5;
		}
		else if(status == FGAMEOVER && chk_boy+chk_girl+chk_hip>=2)
		{
			result_f_b.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_f_b);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count + 3;
		}
		else
		{
			result_f_c.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_f_c);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count +1;
		}
		
	}
	else if(now==RESULT_C)
	{
		if(cheer_g_Score>1500)
		{
			result_c_a.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_c_a);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count +5;
		}
		else if(cheer_g_Score>=1000 && cheer_g_Score<=1500)
		{
			result_c_b.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_c_b);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count + 3;
		}
		else
		{
			result_c_c.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_c_c);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count +1;
		}
		
	}
	else if(now==RESULT_M)
	{
		if(miin_count >= 35)
		{
			result_m_a.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_m_a);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count + 5;		
		}
		else if(miin_count >= 25 && miin_count <= 34)
		{
			result_m_b.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_m_b);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count + 3;
		}
		else
		{
			result_m_c.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_m_c);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
			total_count = total_count + 1;
		}
	}
	else if(now == FINISH)
	{
		if(total_count>=12 && total_count <=15)
		{
			result_t_a.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_t_a);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
		}
		else if(total_count>= 7 && total_count <= 11)
		{
			result_t_b.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_t_b);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
		}
		else
		{
			result_t_c.GetBitmap(&bmpinfo);
			memdc.SelectObject(&result_t_c);
			buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);
		}
		
	}

	dc.BitBlt(0,0, rect.right, rect.bottom, &buffdc, 0,0, SRCCOPY);
	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제
}

void CChildView::ResetGame(void)
{
	Main_OnSize();
	Fes_OnSize();
	Cheer_OnSize();
	Miin_OnSize();
}

void CChildView::About_OnPaint(void)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap menubg;
	CBitmap about;

	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	menubg.LoadBitmapW(IDB_BITMAP44);
	about.LoadBitmapW(IDB_BITMAP45);
	
	menubg.GetBitmap(&bmpinfo); //비트맵의 정보를 불러온다

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&menubg);

	buffdc.BitBlt(0,-m_menu,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경

	about.GetBitmap(&bmpinfo);
	memdc.SelectObject(&about);
	buffdc.TransparentBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(200,200,200));

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&buffdc,0,0,SRCCOPY); //buffdc에 저장한 그림들을 뿌림.

	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제
}

void CChildView::How_OnPaint(void)
{
	CClientDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	CDC memdc;  // 메모리 DC 2개 선언
	CDC buffdc; 

	CBitmap bmpbuffer; //도화지용 비트맵선언

	CBitmap how_f;
	CBitmap how_c;
	CBitmap how_m;
	
	memdc.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	buffdc.CreateCompatibleDC(&dc);

	bmpbuffer.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height()); //도화지생성

	BITMAP bmpinfo; //비트맵의 정보

	how_f.LoadBitmapW(IDB_BITMAP46);
	how_c.LoadBitmapW(IDB_BITMAP47);
	how_m.LoadBitmapW(IDB_BITMAP48);
	
	how_f.GetBitmap(&bmpinfo);

	CBitmap *Pbit = (CBitmap *)buffdc.SelectObject(&bmpbuffer);
	CBitmap *Pbit2 = (CBitmap *)memdc.SelectObject(&how_f);

	if(now==HOW_F)
	{
		how_f.GetBitmap(&bmpinfo);
		memdc.SelectObject(&how_f);
		buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경

	}
	else if(now==HOW_C)
	{
		how_c.GetBitmap(&bmpinfo);
		memdc.SelectObject(&how_c);
		buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경
	}
	else if(now==HOW_M)
	{
		how_m.GetBitmap(&bmpinfo);
		memdc.SelectObject(&how_m);
		buffdc.BitBlt(0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&memdc,0,0,SRCCOPY);//배경
	}
	dc.BitBlt(0,0, rect.right, rect.bottom, &buffdc, 0,0, SRCCOPY);

	buffdc.SelectObject(Pbit);
	memdc.SelectObject(Pbit2);  // 비트맵 객체 해제
}
