#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include "graphics.hpp"
#include <vector>
#include <map>

class Window
{
public:
	Window(int X,int Y);
	void event_loop();
	bool InitFromFEN(std::string sFen);
	void drawBoard();
private:
	std::pair<int, int> getIndexFromPos(int x, int y);
	
	std::vector<std::pair<int, int>> getPossibleMoves();
private:
	int _maxX, _maxY, _tileSize;
	genv::canvas _bg;
	bool _quit;
	std::map<char, genv::canvas> _pieces;
	// map containig the game state
	std::map<char, std::vector<std::vector<bool>>> mBoard;
	std::map<char, bool[8][8]> bitBoard;
	// coordinates of the selected piece
	std::pair<int, int> selected;
	bool bWhiteTurns;
};

#endif // !WINDOW_HPP_INCLUDED

