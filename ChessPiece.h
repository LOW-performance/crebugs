#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <vector>
#include <utility> // for std::pair
#include "pclaf.h"

enum PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };
enum PieceColor { WHITE, BLACK };

class ChessPiece {
protected:
    PieceType type;
    PieceColor color;
    int x, y;

public:
    ChessPiece(PieceType t, PieceColor c, int xPos, int yPos)
        : type(t), color(c), x(xPos), y(yPos) {}

    virtual ~ChessPiece() = default;

    PieceColor getColor() const { return color; }
    PieceType getType() const { return type; }
    std::pair<int, int> getPosition() const { return { x, y }; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }

    virtual std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const = 0;
    virtual void draw(int grid, int offsetX, int offsetY) const = 0;
};

class King : public ChessPiece {
public:
    King(PieceColor c, int xPos, int yPos) : ChessPiece(KING, c, xPos, yPos) {}

    std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const override;
    void draw(int grid, int offsetX, int offsetY) const override;
};

class Queen : public ChessPiece {
public:
    Queen(PieceColor c, int xPos, int yPos) : ChessPiece(QUEEN, c, xPos, yPos) {}

    std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const override;
    void draw(int grid, int offsetX, int offsetY) const override;
};

class Rook : public ChessPiece {
public:
    Rook(PieceColor c, int xPos, int yPos) : ChessPiece(ROOK, c, xPos, yPos) {}

    std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const override;
    void draw(int grid, int offsetX, int offsetY) const override;
};

class Bishop : public ChessPiece {
public:
    Bishop(PieceColor c, int xPos, int yPos) : ChessPiece(BISHOP, c, xPos, yPos) {}

    std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const override;
    void draw(int grid, int offsetX, int offsetY) const override;
};

class Knight : public ChessPiece {
public:
    Knight(PieceColor c, int xPos, int yPos) : ChessPiece(KNIGHT, c, xPos, yPos) {}

    std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const override;
    void draw(int grid, int offsetX, int offsetY) const override;
};

class Pawn : public ChessPiece {
public:
    Pawn(PieceColor c, int xPos, int yPos) : ChessPiece(PAWN, c, xPos, yPos) {}

    std::vector<std::pair<int, int>> getPossibleMoves(ChessPiece* board[8][8]) const override;
    void draw(int grid, int offsetX, int offsetY) const override;
};

#endif
