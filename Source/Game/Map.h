#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <fstream>
#include <string>
#include <iostream>
#include "vector"


#define m_size 50
#define m_length 20
#define m_width 14

namespace game_framework {
	class Map{
	public:
		Map();
		void hitice(char ice);
		void load();
		void first();
		void show();
		void back();
		void tab();
		void set_map_by_phase(); 
		void MovePenguin(int dx, int dy);
		void round();
		int* findpenguin();
		void change();									
		void display();
		void savearray();
		void choose();
		void gg();
		bool validate_phase();
		void check_to_next();
		void amice();
		void dead();
		void prip();
		void detect();
		protected:
		
	private:
		int phase = 1, sub_phase = 1;
		vector<int> armi, armj, noi, noj, ri, rj, li, lj, ui, uj, di, dj, iceposi, iceposj;
		int countice = 0, wall = 0, candect = 0;
		CMovingBitmap area,penguin,rock,ice,music,yes,no,upB,downB,rightB,leftB,gold,fire;
		bool Isicebox = false;
		void cleararray();
		void del();
		vector<vector<int>> iceposition,bgposition,goldposition;
		char map[m_width][m_length];

	};
}