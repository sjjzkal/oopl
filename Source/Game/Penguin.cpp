#include "stdafx.h"
#include "Penguin.h"

using namespace game_framework;

Penguin::Penguin() {
	
}

std::pair<int, int> Penguin::right() {
	return std::make_pair(0,1);
}

std::pair<int, int> Penguin::left() {
	return std::make_pair(0, -1);
}

std::pair<int, int> Penguin::up() {
	return std::make_pair(-1, 0);
}

std::pair<int, int> Penguin::down() {
	return std::make_pair(1, 0);
}