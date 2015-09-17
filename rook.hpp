#pragma once

#include "piece.hpp"
#include "position.hpp"
#include <string>

using std::string;

class Rook: public Piece{
  public: 
	Rook(char color, int x, int y);//constructor
	virtual bool isValidMove(Piece** board, Position destiny);
	virtual void moveTo(Position destiny);
	virtual string toString()const;
}