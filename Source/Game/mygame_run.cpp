#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	map.set_map_by_phase();
	map.load();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
	{
		map.MovePenguin(pen.up().first,pen.up().second);
	}
	if (nChar == VK_LEFT)
	{
		map.MovePenguin(pen.left().first, pen.left().second);
	}
	if (nChar == VK_DOWN)
	{
		map.MovePenguin(pen.down().first, pen.down().second);
	}
	if (nChar == VK_RIGHT)
	{
		map.MovePenguin(pen.right().first, pen.right().second);
	}

	if (nChar == VK_ESCAPE) {
		NowMap = 1;
	}
	if (nChar == VK_BACK) {
		map.back();
	}
	if (nChar == VK_TAB) {
		map.tab();
	}
	if (nChar == 'R') {
		map.set_map_by_phase();
	}
	if (nChar == VK_RETURN) {
		map.check_to_next();
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE) {
		NowMap = 0;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	
	map.choose();
	map.savearray();
	map.display();
	map.dead();
	map.detect();
	map.prip();
	map.show();
	if (NowMap == 1) {
		map.round();
	}
	map.gg();
}
