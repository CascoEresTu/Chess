#pragma once 
#include "piece.hpp"
#include "position.hpp"

class King: public Piece{
	public:
		King(char color, int x , int y);
		virtual bool isValidMove(Piece*** board, Position destiny);
		virtual bool moveTo(Piece*** board, Position destiny);
		virtual string toString()const;

};