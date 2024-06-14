#include "vector"
#define m_length 20
#define m_width 14
#define place 1

namespace game_framework {
	class Penguin {
	public:
		Penguin();
		std::pair<int,int> up();
		std::pair<int, int> down();
		std::pair<int, int> left();
		std::pair<int, int> right();
	protected:

	private:
	};
}