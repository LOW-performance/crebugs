#include "ChessApp.h"

void ChessApp::initializeBoard() {
    // Place pawns
    for (int i = 0; i < 8; ++i) {
        board[i][1] = new Pawn(WHITE, i, 1);
        board[i][6] = new Pawn(BLACK, i, 6);
    }
    // Place rooks
    board[0][0] = new Rook(WHITE, 0, 0);
    board[7][0] = new Rook(WHITE, 7, 0);
    board[0][7] = new Rook(BLACK, 0, 7);
    board[7][7] = new Rook(BLACK, 7, 7);

    // Place knights
    board[1][0] = new Knight(WHITE, 1, 0);
    board[6][0] = new Knight(WHITE, 6, 0);
    board[1][7] = new Knight(BLACK, 1, 7);
    board[6][7] = new Knight(BLACK, 6, 7);

    // Place bishops
    board[2][0] = new Bishop(WHITE, 2, 0);
    board[5][0] = new Bishop(WHITE, 5, 0);
    board[2][7] = new Bishop(BLACK, 2, 7);
    board[5][7] = new Bishop(BLACK, 5, 7);

    // Place queens
    board[3][0] = new Queen(WHITE, 3, 0);
    board[3][7] = new Queen(BLACK, 3, 7);

    // Place kings
    board[4][0] = new King(WHITE, 4, 0);
    board[4][7] = new King(BLACK, 4, 7);
}

void ChessApp::paint() {
    drawBoard();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr) {
                board[i][j]->draw(50, (winWidth - 8 * 50) / 2, (winHeight - 8 * 50) / 2);
            }
        }
    }
    if (selectedPiece != nullptr) {
        highlightPossibleMoves(*selectedPiece);
    }

    // Display "Check" message if any player is in check
    if (isWhiteInCheck) {
        wout << setpos(winWidth / 2 - 70, winHeight - 18 * (winHeight / 20)) << TEXT("White is in Check!");
    }
    if (isBlackInCheck) {
        wout << setpos(winWidth / 2 - 70, winHeight - 2 * (winHeight / 20)) << TEXT("Black is in Check!");
    }

    // Display "Game Over" message if the game is over
    if (gameOver) {
        setTextColor(red);
        wout << setpos(winWidth / 2 - 50, winHeight / 2) << TEXT("Game Over!");
    }
}

void ChessApp::drawBoard() {
    int grid = 50;
    int offsetX = (winWidth - 8 * grid) / 2;
    int offsetY = (winHeight - 8 * grid) / 2;

    setPen(blue, solidLine);
    for (int y = 0; y <= 8; ++y)
        line(offsetX, offsetY + y * grid, offsetX + 8 * grid, offsetY + y * grid);
    for (int x = 0; x <= 8; ++x)
        line(offsetX + x * grid, offsetY, offsetX + x * grid, offsetY + 8 * grid);
}

void ChessApp::highlightPossibleMoves(const ChessPiece& piece) {
    int grid = 50;
    int offsetX = (winWidth - 8 * grid) / 2;
    int offsetY = (winHeight - 8 * grid) / 2;
    std::vector<std::pair<int, int>> moves = piece.getPossibleMoves(board);
    for (const auto& move : moves) {
        int moveX = move.first * grid + offsetX;
        int moveY = move.second * grid + offsetY;
        if (board[move.first][move.second] != nullptr && board[move.first][move.second]->getColor() != piece.getColor()) {
            setPen(red, solidLine, 2); // Red color for capturing moves
        }
        else {
            setPen(blue, solidLine, 2); // Blue color for regular moves
        }
        rectangle(moveX, moveY, grid, grid);
    }
}

void ChessApp::mouseDown(int x, int y) {
    if (gameOver) return; // Prevent moves if the game is over

    int grid = 50;
    int offsetX = (winWidth - 8 * grid) / 2;
    int offsetY = (winHeight - 8 * grid) / 2;
    int boardX = (x - offsetX) / grid;
    int boardY = (y - offsetY) / grid;

    if (boardX < 0 || boardX >= 8 || boardY < 0 || boardY >= 8) return;

    if (selectedPiece == nullptr && board[boardX][boardY] != nullptr && board[boardX][boardY]->getColor() == currentTurn) {  // Select piece
        selectedPiece = board[boardX][boardY];
    }
    else if (selectedPiece != nullptr) {  // Move piece
        if (isValidMove(selectedPiece->getPosition().first, selectedPiece->getPosition().second, boardX, boardY)) {
            movePiece(selectedPiece->getPosition().first, selectedPiece->getPosition().second, boardX, boardY);

            isWhiteInCheck = isInCheck(WHITE);
            isBlackInCheck = isInCheck(BLACK);

            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE; // Change turn
        }
        selectedPiece = nullptr;  // Reset selection
    }
    clearAndUpdate();
}

bool ChessApp::isValidMove(int startX, int startY, int endX, int endY) {
    if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false;
    if (board[endX][endY] != nullptr && board[endX][endY]->getColor() == board[startX][startY]->getColor()) return false;

    // Ensure the move is in the list of possible moves
    std::vector<std::pair<int, int>> moves = board[startX][startY]->getPossibleMoves(board);
    for (const auto& move : moves) {
        if (move.first == endX && move.second == endY) {
            return true;
        }
    }
    return false;
}

void ChessApp::movePiece(int startX, int startY, int endX, int endY) {
    // Capture the piece if there is one
    if (board[endX][endY] != nullptr) {
        if (board[endX][endY]->getType() == KING) {
            gameOver = true; // End the game if a king is captured
        }
        delete board[endX][endY];
    }
    board[endX][endY] = board[startX][startY];
    board[endX][endY]->setPosition(endX, endY);
    board[startX][startY] = nullptr;
}

bool ChessApp::isInCheck(PieceColor color) {
    int kingX = -1, kingY = -1;
    // Find the king's position
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getType() == KING && board[i][j]->getColor() == color) {
                kingX = i;
                kingY = j;
                break;
            }
        }
        if (kingX != -1) break;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->getColor() != color) {
                std::vector<std::pair<int, int>> moves = board[i][j]->getPossibleMoves(board);
                for (const auto& move : moves) {
                    if (move.first == kingX && move.second == kingY) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int mainLAF() {
    ChessApp app(TEXT("Chess Game"), 500, 500, 150, 150);
    app.run();
    return 0;
}

int main() {
    mainLAF();
}
