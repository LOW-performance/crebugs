#ifndef CHESSAPP_H
#define CHESSAPP_H

#include "ChessPieces.h"
#include <vector>
#include <cstring> // memset 사용을 위해 추가
#include "pclaf.h"

class ChessApp : public Application {
    ChessPiece* board[8][8];  // 체스판
    ChessPiece* selectedPiece; // 선택된 체스말
    PieceColor currentTurn; // 현재 턴
    int winWidth, winHeight;
    int mouseX, mouseY;

    // Check status
    bool isWhiteInCheck;
    bool isBlackInCheck;

    // Game over flag
    bool gameOver;

public:
    ChessApp(const TCHAR* apName, int width, int height, int x, int y)
        : Application(apName, width, height, x, y), selectedPiece(nullptr), currentTurn(BLACK), winWidth(width), winHeight(height), mouseX(-1), mouseY(-1), isWhiteInCheck(false), isBlackInCheck(false), gameOver(false) {
        memset(board, 0, sizeof(board));
        initializeBoard();
    }

    ~ChessApp() {
        // 체스말 객체 해제
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete board[i][j];
            }
        }
    }

    void initializeBoard();
    void paint() override;
    void drawBoard();
    void highlightPossibleMoves(const ChessPiece& piece);

    void mouseDown(int x, int y) override;

    bool isValidMove(int startX, int startY, int endX, int endY);
    void movePiece(int startX, int startY, int endX, int endY);
    bool isInCheck(PieceColor color);
};

#endif
