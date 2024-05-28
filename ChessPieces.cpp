#include "ChessPieces.h"

std::vector<std::pair<int, int>> King::getPossibleMoves(ChessPiece* board[8][8]) const {
    std::vector<std::pair<int, int>> moves;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                if (board[newX][newY] == nullptr || board[newX][newY]->getColor() != color) {
                    moves.push_back({ newX, newY });
                }
            }
        }
    }
    return moves;
}

void King::draw(int grid, int offsetX, int offsetY) const {
    int pieceX = x * grid + offsetX + grid / 2;
    int pieceY = y * grid + offsetY + grid / 2;

    if (color == WHITE) {
        setPen(gray, solidLine, 2);
        setTextColor(gray);
    }
    else {
        setPen(black, solidLine, 2);
        setTextColor(black);
    }

    circle(Point{ pieceX, pieceY }, grid / 3);
    wout << setpos(pieceX - 10, pieceY - 10) << TEXT("K");
}

std::vector<std::pair<int, int>> Queen::getPossibleMoves(ChessPiece* board[8][8]) const {
    std::vector<std::pair<int, int>> moves;
    // Rook-like moves
    for (int i = x + 1; i < 8; ++i) {
        if (board[i][y] == nullptr) {
            moves.push_back({ i, y });
        }
        else {
            if (board[i][y]->getColor() != color) moves.push_back({ i, y });
            break;
        }
    }
    for (int i = x - 1; i >= 0; --i) {
        if (board[i][y] == nullptr) {
            moves.push_back({ i, y });
        }
        else {
            if (board[i][y]->getColor() != color) moves.push_back({ i, y });
            break;
        }
    }
    for (int i = y + 1; i < 8; ++i) {
        if (board[x][i] == nullptr) {
            moves.push_back({ x, i });
        }
        else {
            if (board[x][i]->getColor() != color) moves.push_back({ x, i });
            break;
        }
    }
    for (int i = y - 1; i >= 0; --i) {
        if (board[x][i] == nullptr) {
            moves.push_back({ x, i });
        }
        else {
            if (board[x][i]->getColor() != color) moves.push_back({ x, i });
            break;
        }
    }
    // Bishop-like moves
    for (int i = 1; i < 8; ++i) {
        if (x + i < 8 && y + i < 8) {
            if (board[x + i][y + i] == nullptr) {
                moves.push_back({ x + i, y + i });
            }
            else {
                if (board[x + i][y + i]->getColor() != color) moves.push_back({ x + i, y + i });
                break;
            }
        }
    }
    for (int i = 1; i < 8; ++i) {
        if (x - i >= 0 && y - i >= 0) {
            if (board[x - i][y - i] == nullptr) {
                moves.push_back({ x - i, y - i });
            }
            else {
                if (board[x - i][y - i]->getColor() != color) moves.push_back({ x - i, y - i });
                break;
            }
        }
    }
    for (int i = 1; i < 8; ++i) {
        if (x + i < 8 && y - i >= 0) {
            if (board[x + i][y - i] == nullptr) {
                moves.push_back({ x + i, y - i });
            }
            else {
                if (board[x + i][y - i]->getColor() != color) moves.push_back({ x + i, y - i });
                break;
            }
        }
    }
    for (int i = 1; i < 8; ++i) {
        if (x - i >= 0 && y + i < 8) {
            if (board[x - i][y + i] == nullptr) {
                moves.push_back({ x - i, y + i });
            }
            else {
                if (board[x - i][y + i]->getColor() != color) moves.push_back({ x - i, y + i });
                break;
            }
        }
    }
    return moves;
}

void Queen::draw(int grid, int offsetX, int offsetY) const {
    int pieceX = x * grid + offsetX + grid / 2;
    int pieceY = y * grid + offsetY + grid / 2;

    if (color == WHITE) {
        setPen(gray, solidLine, 2);
        setTextColor(gray);
    }
    else {
        setPen(black, solidLine, 2);
        setTextColor(black);
    }

    circle(Point{ pieceX, pieceY }, grid / 3);
    wout << setpos(pieceX - 10, pieceY - 10) << TEXT("Q");
}

std::vector<std::pair<int, int>> Rook::getPossibleMoves(ChessPiece* board[8][8]) const {
    std::vector<std::pair<int, int>> moves;
    // Rook movement (straight lines)
    for (int i = x + 1; i < 8; ++i) {
        if (board[i][y] == nullptr) {
            moves.push_back({ i, y });
        }
        else {
            if (board[i][y]->getColor() != color) moves.push_back({ i, y });
            break;
        }
    }
    for (int i = x - 1; i >= 0; --i) {
        if (board[i][y] == nullptr) {
            moves.push_back({ i, y });
        }
        else {
            if (board[i][y]->getColor() != color) moves.push_back({ i, y });
            break;
        }
    }
    for (int i = y + 1; i < 8; ++i) {
        if (board[x][i] == nullptr) {
            moves.push_back({ x, i });
        }
        else {
            if (board[x][i]->getColor() != color) moves.push_back({ x, i });
            break;
        }
    }
    for (int i = y - 1; i >= 0; --i) {
        if (board[x][i] == nullptr) {
            moves.push_back({ x, i });
        }
        else {
            if (board[x][i]->getColor() != color) moves.push_back({ x, i });
            break;
        }
    }
    return moves;
}

void Rook::draw(int grid, int offsetX, int offsetY) const {
    int pieceX = x * grid + offsetX + grid / 2;
    int pieceY = y * grid + offsetY + grid / 2;

    if (color == WHITE) {
        setPen(gray, solidLine, 2);
        setTextColor(gray);
    }
    else {
        setPen(black, solidLine, 2);
        setTextColor(black);
    }

    circle(Point{ pieceX, pieceY }, grid / 3);
    wout << setpos(pieceX - 10, pieceY - 10) << TEXT("R");
}

std::vector<std::pair<int, int>> Bishop::getPossibleMoves(ChessPiece* board[8][8]) const {
    std::vector<std::pair<int, int>> moves;
    // Bishop movement (diagonals)
    for (int i = 1; i < 8; ++i) {
        if (x + i < 8 && y + i < 8) {
            if (board[x + i][y + i] == nullptr) {
                moves.push_back({ x + i, y + i });
            }
            else {
                if (board[x + i][y + i]->getColor() != color) moves.push_back({ x + i, y + i });
                break;
            }
        }
    }
    for (int i = 1; i < 8; ++i) {
        if (x - i >= 0 && y - i >= 0) {
            if (board[x - i][y - i] == nullptr) {
                moves.push_back({ x - i, y - i });
            }
            else {
                if (board[x - i][y - i]->getColor() != color) moves.push_back({ x - i, y - i });
                break;
            }
        }
    }
    for (int i = 1; i < 8; ++i) {
        if (x + i < 8 && y - i >= 0) {
            if (board[x + i][y - i] == nullptr) {
                moves.push_back({ x + i, y - i });
            }
            else {
                if (board[x + i][y - i]->getColor() != color) moves.push_back({ x + i, y - i });
                break;
            }
        }
    }
    for (int i = 1; i < 8; ++i) {
        if (x - i >= 0 && y + i < 8) {
            if (board[x - i][y + i] == nullptr) {
                moves.push_back({ x - i, y + i });
            }
            else {
                if (board[x - i][y + i]->getColor() != color) moves.push_back({ x - i, y + i });
                break;
            }
        }
    }
    return moves;
}

void Bishop::draw(int grid, int offsetX, int offsetY) const {
    int pieceX = x * grid + offsetX + grid / 2;
    int pieceY = y * grid + offsetY + grid / 2;

    if (color == WHITE) {
        setPen(gray, solidLine, 2);
        setTextColor(gray);
    }
    else {
        setPen(black, solidLine, 2);
        setTextColor(black);
    }

    circle(Point{ pieceX, pieceY }, grid / 3);
    wout << setpos(pieceX - 10, pieceY - 10) << TEXT("B");
}

std::vector<std::pair<int, int>> Knight::getPossibleMoves(ChessPiece* board[8][8]) const {
    std::vector<std::pair<int, int>> moves;
    // Knight movement (L shape)
    int knightMoves[8][2] = { {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1} };
    for (auto& move : knightMoves) {
        int newX = x + move[0];
        int newY = y + move[1];
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            if (board[newX][newY] == nullptr || board[newX][newY]->getColor() != color) {
                moves.push_back({ newX, newY });
            }
        }
    }
    return moves;
}

void Knight::draw(int grid, int offsetX, int offsetY) const {
    int pieceX = x * grid + offsetX + grid / 2;
    int pieceY = y * grid + offsetY + grid / 2;

    if (color == WHITE) {
        setPen(gray, solidLine, 2);
        setTextColor(gray);
    }
    else {
        setPen(black, solidLine, 2);
        setTextColor(black);
    }

    circle(Point{ pieceX, pieceY }, grid / 3);
    wout << setpos(pieceX - 10, pieceY - 10) << TEXT("N");
}

std::vector<std::pair<int, int>> Pawn::getPossibleMoves(ChessPiece* board[8][8]) const {
    std::vector<std::pair<int, int>> moves;
    int direction = (color == WHITE) ? 1 : -1;
    int startRow = (color == WHITE) ? 1 : 6;

    if (y + direction >= 0 && y + direction < 8 && board[x][y + direction] == nullptr) {
        moves.push_back({ x, y + direction });
    }
    if (y == startRow && board[x][y + direction] == nullptr && board[x][y + 2 * direction] == nullptr) {
        moves.push_back({ x, y + 2 * direction });
    }
    if (x + 1 < 8 && y + direction >= 0 && y + direction < 8 && board[x + 1][y + direction] != nullptr && board[x + 1][y + direction]->getColor() != color) {
        moves.push_back({ x + 1, y + direction });
    }
    if (x - 1 >= 0 && y + direction >= 0 && y + direction < 8 && board[x - 1][y + direction] != nullptr && board[x - 1][y + direction]->getColor() != color) {
        moves.push_back({ x - 1, y + direction });
    }
    return moves;
}

void Pawn::draw(int grid, int offsetX, int offsetY) const {
    int pieceX = x * grid + offsetX + grid / 2;
    int pieceY = y * grid + offsetY + grid / 2;

    if (color == WHITE) {
        setPen(gray, solidLine, 2);
        setTextColor(gray);
    }
    else {
        setPen(black, solidLine, 2);
        setTextColor(black);
    }

    circle(Point{ pieceX, pieceY }, grid / 3);
    wout << setpos(pieceX - 10, pieceY - 10) << TEXT("P");
}
