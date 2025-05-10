#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>  // مطلوب لاستخدام std::max و std::min
using namespace std;

char board[3][3];
char currentPlayer = 'X';

enum GameState { START, PLAYING, WIN, DRAW };
GameState gameState = START;

void initBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void drawText(float x, float y, const char* text, void* font, float r = 1, float g = 1, float b = 1) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawTitleScreen() {
    glColor3f(0.2f, 0.2f, 0.5f);
    glBegin(GL_QUADS); // خلفية زرقاء غامقة
        glVertex2f(-1, -1); glVertex2f(1, -1);
        glVertex2f(1, 1); glVertex2f(-1, 1);
    glEnd();

    drawText(-0.3f, 0.4f, "TIC TAC TOE", GLUT_BITMAP_TIMES_ROMAN_24, 1, 1, 0);
    drawText(-0.45f, -0.1f, "Press SPACE to Start", GLUT_BITMAP_HELVETICA_18, 1, 1, 1);
}

void drawBackground(float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(-1, -1); glVertex2f(1, -1);
        glVertex2f(1, 1); glVertex2f(-1, 1);
    glEnd();
}

void drawGrid() {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    // عمودي
    glVertex2f(-0.33f, 1.0f); glVertex2f(-0.33f, -1.0f);
    glVertex2f(0.33f, 1.0f);  glVertex2f(0.33f, -1.0f);
    // أفقي
    glVertex2f(-1.0f, 0.33f); glVertex2f(1.0f, 0.33f);
    glVertex2f(-1.0f, -0.33f); glVertex2f(1.0f, -0.33f);
    glEnd();
}

void drawX(float cx, float cy) {
    glColor3f(0.8, 0.1, 0.1);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(cx - 0.25f, cy - 0.25f); glVertex2f(cx + 0.25f, cy + 0.25f);
    glVertex2f(cx + 0.25f, cy - 0.25f); glVertex2f(cx - 0.25f, cy + 0.25f);
    glEnd();
}

void drawO(float cx, float cy) {
    glColor3f(0.1, 0.5, 0.9);
    glLineWidth(5.0);
    float r = 0.25f;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angle = 2 * 3.14159f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

void drawSymbols() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            float cx = -0.66f + j * 0.66f;
            float cy = 0.66f - i * 0.66f;

            if (board[i][j] == 'X')
                drawX(cx, cy);
            else if (board[i][j] == 'O')
                drawO(cx, cy);
        }
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

int minimax(char board[3][3], bool isMaximizing) {
    if (checkWin('O')) return 1;
    if (checkWin('X')) return -1;
    if (checkDraw()) return 0;

    int bestScore = isMaximizing ? -10000 : 10000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isMaximizing ? 'O' : 'X';
                int score = minimax(board, !isMaximizing);
                board[i][j] = ' ';  // إرجاع الخلية فارغة

                if (isMaximizing) {
                    bestScore = std::max(score, bestScore);
                } else {
                    bestScore = std::min(score, bestScore);
                }
            }
        }
    }
    return bestScore;
}

void aiMove() {
    int bestScore = -10000;
    int bestRow = -1, bestCol = -1;

    // البحث عن أفضل خطوة باستخدام خوارزمية Minimax
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';  // وضع O مؤقتاً
                int score = minimax(board, false);
                board[i][j] = ' ';  // إرجاع الخلية فارغة

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    // وضع أفضل خطوة تم تحديدها
    board[bestRow][bestCol] = 'O';
    currentPlayer = 'X';
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameState == START) {
        drawTitleScreen();
    }
    else if (gameState == PLAYING) {
        drawBackground(0.1f, 0.1f, 0.1f);
        drawGrid();
        drawSymbols();
    }
    else if (gameState == WIN) {
        drawBackground(0.0f, 0.3f, 0.0f); // أخضر
        drawGrid();
        drawSymbols();
        string msg = string("Player ") + (currentPlayer == 'X' ? 'O' : 'X') + " Wins!";
        drawText(-0.3f, 0.0f, msg.c_str(), GLUT_BITMAP_HELVETICA_18, 1.0f, 1.0f, 0.0f);
        drawText(-0.4f, -0.3f, "Press R to Restart", GLUT_BITMAP_HELVETICA_12, 0.8f, 0.8f, 0.8f);
    }
    else if (gameState == DRAW) {
        drawBackground(0.2f, 0.2f, 0.2f);
        drawGrid();
        drawSymbols();
        drawText(-0.2f, 0.0f, "It's a Draw!", GLUT_BITMAP_HELVETICA_18, 1.0f, 1.0f, 0.0f);
        drawText(-0.4f, -0.3f, "Press R to Restart", GLUT_BITMAP_HELVETICA_12, 0.8f, 0.8f, 0.8f);
    }

    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (gameState != PLAYING || button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    float fx = (float)x / 300 - 1;
    float fy = 1 - (float)y / 300;

    int col = (fx + 1) / 0.66f;
    int row = (1 - fy) / 0.66f;

    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ' && currentPlayer == 'X') {
        board[row][col] = 'X';  // اللاعب يضع X

        if (checkWin('X')) {
            gameState = WIN;
        }
        else if (checkDraw()) {
            gameState = DRAW;
        }
        else {
            currentPlayer = 'O';  // التبديل إلى AI
            aiMove();  // دع AI يلعب
            if (checkWin('O')) {
                gameState = WIN;
            }
            else if (checkDraw()) {
                gameState = DRAW;
            }
        }

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ' && gameState == START) {
        gameState = PLAYING;
        glutPostRedisplay();
    }
    else if ((key == 'r' || key == 'R') && (gameState == WIN || gameState == DRAW)) {
        initBoard();
        currentPlayer = 'X';
        gameState = PLAYING;
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0, 0, 0, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Tic Tac Toe - OpenGL");
    init();
    initBoard();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
