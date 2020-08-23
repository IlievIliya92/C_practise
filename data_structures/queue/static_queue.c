/*
INSERT
1. Initialize front=0 rear = –1
2. Input the value to be inserted and assign to variable “data”
3. If (rear >= SIZE)
(a) Display “Queue overflow”
(b) Exit

4. Else
(a) Rear = rear + 1
5. Q[rear] = data
6. Exit

REMOVE
1. If (rear< front)
(a) Front = 0, rear = –1
(b) Display “The queue is empty”
(c) Exit

2. Else
(a) Data = Q[front]
3. Front = front +1
4. Exit

*/

/******************************** INCLUDE FILES *******************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/********************************** DEFINES ***********************************/
#define QUEUE_SIZE      100
#define QUEUE_EMPTY     (-1)

/********************************* TYPEDEFS ***********************************/
typedef struct queue_t {
    int storage[QUEUE_SIZE];
    int front;
    int rear;
} _queue_t, *_queue_tPtr;

/******************************* LOCAL FUNCTIONS ******************************/
static void queue_init(_queue_tPtr queue)
{
    queue->rear = QUEUE_EMPTY;
    queue->front = 0;
    memset(queue->storage, 0x0, QUEUE_SIZE);

    return;
}

static bool queue_insert(_queue_tPtr queue, int data)
{
    bool ret = false;

    if (queue->rear >= QUEUE_SIZE)
    {
        fprintf(stderr, "[%s] The queue is in overflow condition! \n", __func__);
        ret = false;
    }
    else
    {
        /* Insert new data in the queue */
        queue->storage[++queue->rear] = data;
        ret = true;
    }

    return ret;
}

static bool queue_remove(_queue_tPtr queue, int *data)
{
    bool ret = false;

    if (queue->rear < queue->front)
    {
        fprintf(stderr, "[%s] The queue is empty! \n", __func__);
        ret = false;
    }
    else
    {
        /* Get the the data from the queue */
        *data = queue->storage[queue->front++];
        ret = true;
    }

    return ret;
}

static bool queue_traverse(_queue_tPtr queue)
{
    bool ret = false;

    if (queue->rear < queue->front)
    {
        fprintf(stderr, "[%s] The queue is empty! \n", __func__);
        ret = false;
    }
    else
    {
        /* traverse the queue */
        for (int i = queue->rear; i > queue->front; i--)
            fprintf(stdout, "[%s] idx: %d val: %d\n", __func__, i, queue->storage[i]);

        ret = true;
    }

    return ret;
}


/********************************* MAIN ***********************************/
int main(int argc, char *argv[])
{
    _queue_t queue;
    int dataOut = 0;
    int i = 0;

    queue_init(&queue);

    for (i = 0; i < QUEUE_SIZE; i++)
        queue_insert(&queue, i);

    queue_traverse(&queue);

    for (i = 0; i < QUEUE_SIZE; i++)
    {
        queue_remove(&queue, &dataOut);
        fprintf(stdout, "[%s] %d\n", __func__, dataOut);
    }

    return 0;
}
