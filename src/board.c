#include "board.h"

#include <stdlib.h>

int board_coordinates_in_range(int row, int column)
{
    return row >= 0 && row < SUDOKU_SIZE &&
           column >= 0 && column < SUDOKU_SIZE;
}

SudokuBoard *board_create(void)
{
    SudokuBoard *board = (SudokuBoard *)calloc(1, sizeof(*board));
    int *arr = (int *)calloc(SUDOKU_SIZE * SUDOKU_SIZE, sizeof(*arr));
    if (board == NULL || arr == NULL)
    {
        free(board);
        free(arr);
        board = NULL;
        arr = NULL;
        return NULL;
    }
    board->cells = arr;
    return board;
}

SudokuBoard *board_clone(const SudokuBoard *source)
{
    if (source == NULL)
    {
        return NULL;
    }
    SudokuBoard *board = (SudokuBoard *)calloc(1, sizeof(*board));
    int *arr = (int *)calloc(SUDOKU_SIZE * SUDOKU_SIZE, sizeof(*arr));
    if (board == NULL || arr == NULL)
    {
        free(board);
        free(arr);
        board = NULL;
        arr = NULL;
        return NULL;
    }
    int *source_arr = source->cells;
    if (source_arr == NULL)
    {
        free(board);
        free(arr);
        board = NULL;
        arr = NULL;
        return NULL;
    }
    for (int i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++)
    {
        arr[i] = source_arr[i];
    }
    board->cells = arr;

    return board;
}

void board_destroy(SudokuBoard **board_ptr)
{
    if (board_ptr == NULL || *board_ptr == NULL)
    {
        return;
    }
    if ((*board_ptr)->cells == NULL)
    {
        return;
    }
    free((*board_ptr)->cells);
    (*board_ptr)->cells = NULL;
    free(*board_ptr);
    *board_ptr = NULL;
}

int *board_cell(SudokuBoard *board, int row, int column)
{
    if (board == NULL)
    {
        return NULL;
    }
    if (row < 0 || column < 0 || row > 8 || column > 8)
    {
        return NULL;
    }
    int location = row * SUDOKU_SIZE + column;
    int *value = board->cells + location;
    return value;
}

const int *board_cell_const(const SudokuBoard *board, int row, int column)
{
    if (board == NULL)
    {
        return NULL;
    }
    if (row < 0 || column < 0 || row > 8 || column > 8)
    {
        return NULL;
    }
    int location = row * SUDOKU_SIZE + column;
    const int *value = board->cells + location;
    return value;
}

void board_clear(SudokuBoard *board)
{
    int *cursor;
    int *end;

    if (board == NULL || board->cells == NULL)
    {
        return;
    }

    cursor = board->cells;
    end = board->cells + SUDOKU_CELL_COUNT;

    while (cursor < end)
    {
        *cursor = SUDOKU_EMPTY;
        cursor++;
    }
}

int board_copy(SudokuBoard *destination, const SudokuBoard *source)
{
    if (destination == NULL || destination->cells == NULL ||
        source == NULL || source->cells == NULL)
    {
        return 0;
    }

    for (size_t index = 0; index < SUDOKU_CELL_COUNT; index++)
    {
        destination->cells[index] = source->cells[index];
    }

    return 1;
}

int board_equal(const SudokuBoard *first, const SudokuBoard *second)
{
    if (first == NULL || first->cells == NULL ||
        second == NULL || second->cells == NULL)
    {
        return 0;
    }

    for (size_t index = 0; index < SUDOKU_CELL_COUNT; index++)
    {
        if (first->cells[index] != second->cells[index])
        {
            return 0;
        }
    }

    return 1;
}