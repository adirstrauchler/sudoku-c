#include "history.h"

#include <stdint.h>
#include <stdlib.h>

#define INITIAL_HISTORY_CAPACITY 8U

void history_init(MoveHistory *history)
{
    if (history == NULL)
    {
        return;
    }

    history->items = NULL;
    history->count = 0;
    history->capacity = 0;
}

int history_push(MoveHistory *history, Move move)
{
    if (history == NULL)
    {
        return 0;
    }
    if (history->capacity == 0 && history->items == 0)
    {
        Move *arr = (Move *)malloc(sizeof(*arr));
        if (arr == NULL)
        {

            return 0;
        }
        arr[0] = move;
        history->items = arr;
        history->capacity = 1;
        history->count = 1;
        return 1;
    }
    else
    {
        if ((*history).count < (*history).capacity)
        {
            (*history).items[(*history).count] = move;
            (*history).count = (*history).count + 1;
            return 1;
        }
        else
        {

            int size = sizeof(*(*history).items);
            Move *temp = (Move *)realloc((*history).items, (*history).capacity * size + size);
            if (temp == NULL)
            {

                return 0;
            }

            (*history).items = temp;
            (*history).capacity = (*history).capacity + 1;
            (*history).items[(*history).count] = move;
            (*history).count = (*history).count + 1;
            return 1;
        }
    }
}

int history_pop(MoveHistory *history, Move *result)
{
    if (history == NULL)
    {
        return 0;
    }
    if ((*history).count == 0)
    {
        return 0;
    }
    *result = (*history).items[(*history).count - 1];
    (*history).count--;
    return 1;
}

void history_clear(MoveHistory *history)
{
    if (history == NULL)
    {
        return;
    }

    history->count = 0;
}

void history_destroy(MoveHistory *history)
{
    if (history == NULL)
    {
        return;
    }
    Move *move_ptr = history->items;
    free(move_ptr);
    history->items = NULL;
    history->count = 0;
    history->capacity = 0;
}
