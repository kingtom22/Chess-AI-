#include "window.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace genv;
using namespace std;

bool load_pieces(std::map<char, genv::canvas>& pieces)
{
	canvas piece;
	piece.transparent(true);
	string sDir = "C:\\Users\\Tamás\\source\\repos\\SDL_TTF_Widgets_kit\\SDL_GraphicsKit\\pieces\\";
	if (piece.load(sDir + "white_queen.bmp")) pieces['Q'] = piece;
	else return false;
	if (piece.load(sDir + "white_king.bmp")) pieces['K'] = piece;
	else return false;
	if (piece.load(sDir + "white_pawn.bmp")) pieces['P'] = piece;
	else return false;
	if (piece.load(sDir + "white_knight.bmp")) pieces['N'] = piece;
	else return false;
	if (piece.load(sDir + "white_bishop.bmp")) pieces['B'] = piece;
	else return false;
	if (piece.load(sDir + "white_rook.bmp")) pieces['R'] = piece;
	else return false;
	if (piece.load(sDir + "black_queen.bmp")) pieces['q'] = piece;
	else return false;
	if (piece.load(sDir + "black_king.bmp")) pieces['k'] = piece;
	else return false;
	if (piece.load(sDir + "black_pawn.bmp")) pieces['p'] = piece;
	else return false;
	if (piece.load(sDir + "black_knight.bmp")) pieces['n'] = piece;
	else return false;
	if (piece.load(sDir + "black_bishop.bmp")) pieces['b'] = piece;
	else return false;
	if (piece.load(sDir + "black_rook.bmp")) pieces['r'] = piece;
	else return false;
}

Window::Window(int X, int Y)
{
	_maxX = X;
	_maxY = Y;
	_tileSize = Y / 8;
	_quit = false;
	selected = pair<int, int>(-1, -1);
	_bg.open(X, Y);
	bool white = true;
	for (size_t i = 0; i < _tileSize * 8; i += _tileSize)
	{
		for (size_t j = 0; j < _tileSize * 8; j += _tileSize)
		{
			if (white)
			{
				_bg << color(White);
				white = false;
			}
			else
			{
				_bg << color(Black);
				white = true;
			}
			_bg << move_to(i, j) << box(_tileSize, _tileSize);
		}
		if (white) white = false;
		else white = true;
	}
	if (!load_pieces(_pieces))
		cout << "could not load all pieces!" << endl;
	if (!InitFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"))
		cout << "could not init the board" << endl;
	drawBoard();
	gout << refresh;
}

void Window::event_loop()
{
	event ev;
	while (gin >> ev && !_quit) {
		if (ev.keycode == key_escape)
			_quit = true;
		if (ev.type == ev_mouse && ev.button == btn_left)
		{
			// handle board click
			if (ev.pos_x < 8 * _tileSize)
			{
				std::pair<int,int> clicked = getIndexFromPos(ev.pos_x, ev.pos_y);
				cout << clicked.first << " " << clicked.second << endl;
				selected = clicked;
			}
			// draw board
			drawBoard();
			gout << refresh;
		}
	}
}

bool Window::InitFromFEN(std::string sFen)
{
	int num_spaces = 0;
	int num_rows = 1;
	for (size_t i = 0; i < sFen.length(); i++)
	{
		if (sFen[i] == ' ') ++num_spaces;
		else if (sFen[i] == '/') ++num_rows;
	}

	if (num_spaces != 5 || num_rows != 8)
		return false;

	vector<vector<bool>> vEmpty;
	vector<bool> emptyRow;
	emptyRow.resize(8);
	for (size_t i = 0; i < 8; i++)
		vEmpty.push_back(emptyRow);

	mBoard['p'] = vEmpty;
	mBoard['n'] = vEmpty;
	mBoard['b'] = vEmpty;
	mBoard['r'] = vEmpty;
	mBoard['k'] = vEmpty;
	mBoard['q'] = vEmpty;
	mBoard['P'] = vEmpty;
	mBoard['N'] = vEmpty;
	mBoard['B'] = vEmpty;
	mBoard['K'] = vEmpty;
	mBoard['R'] = vEmpty;
	mBoard['K'] = vEmpty;
	mBoard['Q'] = vEmpty;

	unsigned ColCount = 7;
	unsigned RowCount = 7;
	size_t pos = 0;
	for (; sFen[pos] != ' '; pos++)
	{
		if (isdigit(sFen[pos]))
		{
			char num = sFen[pos];
			ColCount -= atoi(&num);
		}
		else if (sFen[pos] == '/')
		{
			RowCount--;
			ColCount = 7;
		}
		else if (isalpha(sFen[pos]))
		{
			vector<vector<bool>> matrPiece = mBoard[sFen[pos]];
			matrPiece[RowCount][ColCount] = true;
			mBoard[sFen[pos]] = matrPiece;
			ColCount--;
		}
	}
	pos++;
	if (sFen[pos] == 'w')
		bWhiteTurns = true;
	else
		bWhiteTurns = false;

	return true;
}

void Window::drawBoard()
{
	gout << stamp(_bg, 0, 0);
	if (selected.first != -1)
		gout << move_to(selected.first * _tileSize, selected.second * _tileSize) << color(Red) << box(_tileSize, _tileSize);
	for (auto piece : mBoard)
	{
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				if (piece.second[i][j])
				{
					gout << stamp(_pieces[piece.first], i * _tileSize, j * _tileSize);
				}
			}
		}
	}
}

std::pair<int, int> Window::getIndexFromPos(int x, int y)
{
	return std::pair<int, int>(x / _tileSize, y / _tileSize);
}
