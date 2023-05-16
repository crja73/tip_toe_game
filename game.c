#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

void draw_board(char board[][SIZE]);
bool is_winner(char board[][SIZE], char symbol);
void player_move(char board[][SIZE]);
void computer_move(char board[][SIZE]);
bool is_full(char board[][SIZE]);

int main() {
    char board[SIZE][SIZE] = {0};
    srand(time(0));

    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = ' ';

    while (!is_full(board) && !is_winner(board, 'X') && !is_winner(board, 'O')) {
        draw_board(board);
        player_move(board);
        if (is_winner(board, 'X')) {
            draw_board(board);
            printf("Вы выиграли!\n");
            break;
        }
        if (is_full(board)) {
            draw_board(board);
            printf("Ничья!\n");
            break;
        }
        computer_move(board);
        if (is_winner(board, 'O')) {
            draw_board(board);
            printf("Компьютер выиграл!\n");
            break;
        }
    }

    return 0;
}

void draw_board(char board[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
        if (i != SIZE - 1) {
            printf("---------------------\n");
        }
    }
    printf("\n");
}

bool is_winner(char board[][SIZE], char symbol) {
    int row, col, diag1, diag2;

    for (int i = 0; i < SIZE; ++i) {
        row = col = diag1 = diag2 = 0;
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == symbol) row++;
            if (board[j][i] == symbol) col++;
            if (board[j][j] == symbol) diag1++;
            if (board[j][SIZE - j - 1] == symbol) diag2++;
        }
        if (row == SIZE || col == SIZE || diag1 == SIZE || diag2 == SIZE)
            return true;
    }
    return false;
}

void player_move(char board[][SIZE]) {
    int row, col;
    do {
        printf("Enter the coordinates of your turn (row and column 1-%d): ", SIZE);  //Почему то не работает русский язык
        scanf("%d %d", &row, &col);
        row--;
        col--;
    } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ');

    board[row][col] = 'X';
}

void computer_move(char board[][SIZE]) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (board[row][col] != ' ');

    board[row][col] = 'O';
}

bool is_full(char board[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}