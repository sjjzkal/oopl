#include "stdafx.h"
#include "Map.h"
using namespace game_framework;

Map::Map() {

}

void Map::show() {
	std::map<char, CMovingBitmap> bitmapMap = {
	{'m', music},
	{'y', yes},
	{'*', no},
	{'i', ice},
	{'w', rock},
	{'a', area},
	{'g', gold},
	{'p', penguin},
	{'+', upB},
	{'-', downB},
	{'{', leftB},
	{'}', rightB}};
	for (int j = 0; j < m_length; ++j) {
		for (int i = 0; i < m_width; ++i) {
			auto it = bitmapMap.find(map[i][j]);
			if (it != bitmapMap.end()) {
				it->second.SetTopLeft(j * 50, i * 50);
				it->second.ShowBitmap();
			}
			if (map[i][j] == 'f') {
				fire.SetTopLeft(j * 50, i * 50);
				fire.ShowBitmap();
			}
		}
	}
}

void Map::load() {
	ice.LoadBitmapByString({ "resources/ice.bmp" });
	area.LoadBitmapByString({ "resources/black.bmp" });
	penguin.LoadBitmapByString({ "resources/penguin.bmp","resources/RIP.bmp" });
	rock.LoadBitmapByString({ "resources/rocks.bmp" });
	music.LoadBitmapByString({ "resources/music.bmp" });
	yes.LoadBitmapByString({ "resources/yes.bmp" });
	no.LoadBitmapByString({ "resources/no.bmp" });
	upB.LoadBitmapByString({ "resources/up.bmp" });
	downB.LoadBitmapByString({ "resources/down.bmp" });
	leftB.LoadBitmapByString({ "resources/left.bmp" });
	rightB.LoadBitmapByString({ "resources/right.bmp" });
	gold.LoadBitmapByString({ "resources/gold.bmp" });
	fire.LoadBitmapByString({ "resources/FA/f0.bmp","resources/FA/f1.bmp","resources/FA/f2.bmp","resources/FA/f3.bmp","resources/FA/f2.bmp","resources/FA/f1.bmp","resources/FA/f0.bmp","resources/FA/f5.bmp","resources/FA/f6.bmp","resources/FA/f7.bmp","resources/FA/f8.bmp","resources/FA/f7.bmp","resources/FA/f6.bmp","resources/FA/f5.bmp" });
	fire.SetAnimation(200, false);
}

void Map::back() {
	if (phase > 1) phase -= 1;
	set_map_by_phase();
}

void Map::tab() {
	if (phase < 30) phase += 1;
	set_map_by_phase();
}

void Map::round() {
	std::string now = std::to_string(phase);
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 36, "微軟正黑體", RGB(255, 0, 0), 800);
	CTextDraw::Print(pDC, 425, 0, "第" + now + "關");
	CDDraw::ReleaseBackCDC();
}

void Map::del() {
	armi.clear(); armj.clear(); noi.clear(); noj.clear();ri.clear(); rj.clear(); li.clear(); lj.clear();ui.clear(); uj.clear(); di.clear(); dj.clear();bgposition.clear();iceposition.clear();
}

void Map::set_map_by_phase() {
	if (Isicebox == false) {
		std::string now = std::to_string(phase);
		if (sub_phase == 1) {
			ifstream ifs("map/map" + now + ".map");
			for (int j = 0; j < m_length; j++) {
				for (int i = 0; i < m_width; i++) {
					ifs >> map[i][j];
				}
			}
			del();
			if(penguin.GetFrameIndexOfBitmap()==1) penguin.SetFrameIndexOfBitmap(0);
			amice();
			ifs.close();
		}
	}
}

void Map::cleararray() {
	iceposition.erase(iceposition.begin() + 1, iceposition.end());
	bgposition.erase(bgposition.begin() + 1, bgposition.end());
}

void Map::hitice(char ice) {
	map[bgposition[0][0]][bgposition[0][1]] = 'a';
	if (ice == 'i' && map[iceposition[0][0]][iceposition[0][1]] == 'f'){
		countice -= 1;
		map[iceposition[0][0]][iceposition[0][1]] = 'a';
		cleararray();
	}
	else if (map[iceposition[0][0]][iceposition[0][1]] == 'i' || map[iceposition[0][0]][iceposition[0][1]] == 'p' || map[iceposition[0][0]][iceposition[0][1]] == 'g' || map[iceposition[0][0]][iceposition[0][1]] == 'y') {
		map[bgposition[0][0]][bgposition[0][1]] = ice;
		cleararray();
	}
	else {
		if (map[iceposition[0][0]][iceposition[0][1]] == 'm') change();
		map[iceposition[0][0]][iceposition[0][1]] = ice;
	}

	iceposition.erase(iceposition.begin());
	bgposition.erase(bgposition.begin());
	if (iceposition.empty()) {
		Isicebox = false;
	}
}

void Map::choose() {
	if (Isicebox) {
		if (map[bgposition[0][0]][bgposition[0][1]] == 'i') {
			hitice('i');
		}
		else if (map[bgposition[0][0]][bgposition[0][1]] == 'g') {
			hitice('g');
		}
	}
}

void Map::MovePenguin(int dx, int dy) {
	if (penguin.GetFrameIndexOfBitmap() == 1) return;
	int *pos = findpenguin();
	int newX = pos[0] + dx;
	int newY = pos[1] + dy;
	int newerX = newX + dx;
	int newerY = newY + dy;
	char nextPos = map[newX][newY];
	char newerPos = map[newerX][newerY];
	if (nextPos == 'g' || nextPos == 'i')
	{
		if (newerPos == 'w' || newerPos == 'y') {
			return;
		}
		Isicebox = true;
		while (newerPos != 'w') {
			bgposition.push_back({ newX,newY });
			if (newerPos == '+') {		
				dx = -1;
				dy = 0;		
			}
			else if (newerPos == '-') {
				dx = 1;
				dy = 0;		
			}
			else if (newerPos == '}') {
				dx = 0;
				dy = 1;	
			}
			else if (newerPos == '{') {
				dx = 0;
				dy = -1;		
			}
			newX = newerX;
			newY = newerY;
			iceposition.push_back({ newerX,newerY });
			newerX = newerX + dx;
			newerY = newerY + dy;
			newerPos = map[newerX][newerY];	
		}
	}
	else if (nextPos != 'w' && nextPos != 'f' && nextPos != 'y') {
		if (nextPos == 'm') change();
		map[pos[0]][pos[1]] = 'a';
		map[newX][newY] = 'p';
	}
}

int* Map::findpenguin() {
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_length; j++)
		{
			if (map[i][j] == 'p')
			{
				int* position = new int[2];
				position[0] = i;
				position[1] = j;
				return position;
			}
		}
	}
	return 0;
}

void Map::display() {
	for (size_t x = 0; x < armi.size(); x++) {
		if (map[armi[x]][armj[x]] == 'a') map[armi[x]][armj[x]] = 'm';
	}
	for (size_t x = 0; x < noi.size(); x++) {
		if (map[noi[x]][noj[x]] == 'a') map[noi[x]][noj[x]] = '*';
	}
	for (size_t x = 0; x < ui.size(); x++) {
		if (map[ui[x]][uj[x]] == 'a') map[ui[x]][uj[x]] = '+';
	}
	for (size_t x = 0; x < di.size(); x++) {
		if (map[di[x]][dj[x]] == 'a') map[di[x]][dj[x]] = '-';
	}
	for (size_t x = 0; x < ri.size(); x++) {
		if (map[ri[x]][rj[x]] == 'a') map[ri[x]][rj[x]] = '}';
	}
	for (size_t x = 0; x < li.size(); x++) {
		if (map[li[x]][lj[x]] == 'a') map[li[x]][lj[x]] = '{';
	}
}

void  Map::savearray() {
	for (int j = 0; j < m_length; j++) {
		for (int i = 0; i < m_width; i++) {
			if (map[i][j] == 'm') {
				armi.push_back(i);
				armj.push_back(j);
			}
			if (map[i][j] == '*') {
				noi.push_back(i);
				noj.push_back(j);
			}
			if (map[i][j] == '+') {
				ui.push_back(i);
				uj.push_back(j);
			}
			if (map[i][j] == '-') {
				di.push_back(i);
				dj.push_back(j);
			}
			if (map[i][j] == '}') {
				ri.push_back(i);
				rj.push_back(j);
			}
			if (map[i][j] == '{') {
				li.push_back(i);
				lj.push_back(j);
			}
		}
	}
}

void  Map::change() {
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_length; j++)
		{
			if (map[i][j] == 'y') map[i][j] = '*';
			else if (map[i][j] == '*')map[i][j] = 'y';
		}
	}
}

void Map::gg() {
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 36, "微軟正黑體", RGB(0, 0, 0), 800);
	if (phase == 30 && validate_phase() == 1) {
		CTextDraw::Print(pDC, 350, 300, "You have completed all levels");
		CTextDraw::Print(pDC, 350, 350, "thanks for playing!!!");
	
	}
	else if (validate_phase() == 1) {
		CTextDraw::Print(pDC, 350, 300, "Congratulations!");
		CTextDraw::Print(pDC, 300, 350, "press Enter to next phase");
	}

	else if (penguin.GetFrameIndexOfBitmap() == 1) {
		CTextDraw::Print(pDC, 350, 300, "GGs");
		CTextDraw::Print(pDC, 300, 350, "press R to restart");
	}

	CDDraw::ReleaseBackCDC();
}

bool Map::validate_phase() {
	bool check = true;
	for (int i = 0; i < m_length; i++) {
		for (int j = 0; j < m_width; j++) {
			check &= (map[j][i] != 'f');
		}
	}
	return check;
}

void Map::check_to_next() {
	if (sub_phase == 1) {
		sub_phase += validate_phase();
		if (sub_phase == 2)
		{
			sub_phase = 1;
			phase += 1;
			set_map_by_phase();
		}
	}
}

void Map::prip() {
	int *pos = findpenguin();
	if ((wall == countice) && countice != 0) {
		penguin.SetFrameIndexOfBitmap(1);
	}
}

void Map::amice() {
	countice = 0;
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_length; j++)
		{
			if (map[i][j] == 'i' || map[i][j] == 'g')
			{
				countice += 1;
			}
		}
	}
}

void Map::dead() {
	iceposi.clear();
	iceposj.clear();
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_length; j++)
		{
			if (map[i][j] == 'i')
			{
				iceposi.push_back(i);
				iceposj.push_back(j);
			}
			if (map[i][j] == 'g')
			{
				iceposi.push_back(i);
				iceposj.push_back(j);
			}
		}
	}
}

void Map::detect() {
	wall = 0;
	for (size_t x = 0; x < iceposi.size(); x++) {
		if ((map[iceposi[x]][iceposj[x] + 1] == 'w' || map[iceposi[x]][iceposj[x] + 1] == 'i' || map[iceposi[x]][iceposj[x] + 1] == 'g') && (map[iceposi[x] - 1][iceposj[x]] == 'w' || map[iceposi[x] - 1][iceposj[x]] == 'i' || map[iceposi[x] - 1][iceposj[x]] == 'g')) {
			wall += 1;
		}
		else if ((map[iceposi[x]][iceposj[x] + 1] == 'w' || map[iceposi[x]][iceposj[x] + 1] == 'i' || map[iceposi[x]][iceposj[x] + 1] == 'g') && (map[iceposi[x] + 1][iceposj[x]] == 'w' || map[iceposi[x] + 1][iceposj[x]] == 'i' || map[iceposi[x] + 1][iceposj[x]] == 'g')) {
			wall += 1;
		}
		else if ((map[iceposi[x]][iceposj[x] - 1] == 'w' || map[iceposi[x]][iceposj[x] - 1] == 'i' || map[iceposi[x]][iceposj[x] - 1] == 'g') && (map[iceposi[x] - 1][iceposj[x]] == 'w' || map[iceposi[x] - 1][iceposj[x]] == 'i' || map[iceposi[x] - 1][iceposj[x]] == 'g')) {
			wall += 1;
		}
		else if ((map[iceposi[x]][iceposj[x] - 1] == 'w' || map[iceposi[x]][iceposj[x] - 1] == 'i' || map[iceposi[x]][iceposj[x] - 1] == 'g') && (map[iceposi[x] + 1][iceposj[x]] == 'w' || map[iceposi[x] + 1][iceposj[x]] == 'i' || map[iceposi[x] + 1][iceposj[x]] == 'g')) {
			wall += 1;
		}
	}
}