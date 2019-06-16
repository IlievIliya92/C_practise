/**********
filename:
            mrusna_tragediq.c
**********/

/********** INCLUDES **********/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/********** DEFINES **********/
#define ON              1
#define OFF             0
#define TMR_PERIOD      1000 /* Time between switching lights */

enum states {
    ST0, // 000
    ST1, // 001
    ST2, // 010
    ST3, // 011
    ST4, // 100
    NUMBER_OF_STATES //number of states  = 5
};

enum lights {
    A, // 000
    B, // 001
    C, // 010
    NUMBER_OF_LIGHTS //number of lights  = 3
};

enum lights_states {
    GREEN, // 000
    YELLOW, // 001
    RED, // 010
    NUMBER_OF_LIGHTS_STATES //number of lights  = 3
};

/********** TYPEDEFS **********/
typedef struct traffic_light {
    int state;
    int lights[NUMBER_OF_LIGHTS][NUMBER_OF_LIGHTS_STATES];
     /* 3 traffic lights with three lights on each */
         /* A - [0]  [0]
                     [1]
                     [2]
            B - [1]  [0]
                     [1]
                     [2]
            C - [2]  [0]
                     [1]
                     [2]
         */
    int sensor;
} traffic_light, *traffic_light_ptr;

/********** STATIC PROTOTYPES **********/
static void timer(void *ctx, int period);
static void init_traffic_light_fsm(void *ctx);
static void traffic_light_fsm_core(void *ctx);
static void traffic_light_green(void *ctx, int light);
static void traffic_light_red(void *ctx, int light);
static void traffic_light_yellow(void *ctx, int light);
static void print_lights(void *ctx);

int main ()
{
    int ret = 0;
    traffic_light_ptr traffic_light_fsm = NULL;

    traffic_light_fsm = (traffic_light_ptr)malloc(sizeof(traffic_light));
    if (traffic_light_fsm == NULL) {
        perror("Failed to allocate memory!");
        ret = -1;
        goto exit;
    }

    /* Uncomment one of the scennarios to test */

    /*SCENARIO I - there is a car on A  */
    /* There is a car on A so sensor = 1 */
    traffic_light_fsm->sensor = 1;

    /*SCENARIO II - there is no car on A  */
    //traffic_light_fsm->sensor = 0;

    init_traffic_light_fsm(traffic_light_fsm);

    /* Infinite loop */
    for (;;)
    {
        traffic_light_fsm_core(traffic_light_fsm);
        print_lights(traffic_light_fsm);
    }

exit:
    return ret;
}

static void init_traffic_light_fsm(void *ctx)
{
    printf(
    "                                      /   A   / \n"
    "_____________________________________/   ,   /____________\n"
    "        B                                                  \n"
    "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _         \n"
    "           _____                                     C         \n"
    "_______< Plovdiv|_____________________________________________\n"
    "          || \n\n\n");
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    /* Initialize the state machine to state 0 */
    traffic_light_fsm->state = ST0;

    /* Initialize the traffic lights */
    traffic_light_red(traffic_light_fsm, A);
    traffic_light_green(traffic_light_fsm, B);
    traffic_light_green(traffic_light_fsm, C);

    return;
}

static void traffic_light_fsm_core(void *ctx)
{
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    switch (traffic_light_fsm->state)
    {
        case ST0:
            traffic_light_red(traffic_light_fsm, A);
            traffic_light_green(traffic_light_fsm, B);
            traffic_light_green(traffic_light_fsm, C);
            if (1 == traffic_light_fsm->sensor)
                timer(traffic_light_fsm, TMR_PERIOD);
            else
                traffic_light_fsm->state = ST0;
            break;
        case ST1:
            traffic_light_red(traffic_light_fsm, A);
            traffic_light_green(traffic_light_fsm, B);
            traffic_light_green(traffic_light_fsm, C);
            timer(traffic_light_fsm, TMR_PERIOD);
            break;
        case ST2:
            traffic_light_red(traffic_light_fsm, A);
            traffic_light_yellow(traffic_light_fsm, B);
            traffic_light_yellow(traffic_light_fsm, C);
            timer(traffic_light_fsm, TMR_PERIOD);
            break;
        case ST3:
            traffic_light_green(traffic_light_fsm, A);
            traffic_light_red(traffic_light_fsm, B);
            traffic_light_red(traffic_light_fsm, C);
            timer(traffic_light_fsm, TMR_PERIOD);
            break;
        case ST4:
            traffic_light_yellow(traffic_light_fsm, A);
            traffic_light_red(traffic_light_fsm, B);
            traffic_light_red(traffic_light_fsm, C);
            timer(traffic_light_fsm, TMR_PERIOD);
            break;

        default:
            printf("You shouldn't be here");
            break;
    }

    return;
}

static void traffic_light_green(void *ctx, int light)
{
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    traffic_light_fsm->lights[light][GREEN] = ON;
    traffic_light_fsm->lights[light][YELLOW] = OFF;
    traffic_light_fsm->lights[light][RED] = OFF;

    return;
}

static void traffic_light_yellow(void *ctx, int light)
{
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    traffic_light_fsm->lights[light][GREEN] = OFF;
    traffic_light_fsm->lights[light][YELLOW] = ON;
    traffic_light_fsm->lights[light][RED] = OFF;

    return;
}

static void traffic_light_red(void *ctx, int light)
{
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    traffic_light_fsm->lights[light][GREEN] = OFF;
    traffic_light_fsm->lights[light][YELLOW] = OFF;
    traffic_light_fsm->lights[light][RED] = ON;

    return;
}

static void print_lights(void *ctx)
{
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    printf("\rA|G[%d] Y[%d] R[%d]| B|G[%d] Y[%d] R[%d]|  C|G[%d] Y[%d] R[%d]|",
                                traffic_light_fsm->lights[A][GREEN],
                                traffic_light_fsm->lights[A][YELLOW],
                                traffic_light_fsm->lights[A][RED],
                                traffic_light_fsm->lights[B][GREEN],
                                traffic_light_fsm->lights[B][YELLOW],
                                traffic_light_fsm->lights[B][RED],
                                traffic_light_fsm->lights[C][GREEN],
                                traffic_light_fsm->lights[C][YELLOW],
                                traffic_light_fsm->lights[C][RED]);

    fflush(stdout);

    return;
}

static void timer(void *ctx, int period)
{
    traffic_light *traffic_light_fsm = (traffic_light *)ctx;

    int msec = 0;
    clock_t before = clock();
    int iterations = 0;

    do {
      clock_t difference = clock() - before;
      msec = difference * 1000 / CLOCKS_PER_SEC;
      iterations++;
    } while ( msec < period );

    traffic_light_fsm->state++;
    if (traffic_light_fsm->state == NUMBER_OF_STATES)
        traffic_light_fsm->state = ST0;

    return;
}
