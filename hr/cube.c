#include <stdio.h>
#include <stdlib.h>

typedef struct cubeData_t
{
    int a;
    int b;
    int c;
    int Volume;
} cubeData_t;

static
void findVolume(cubeData_t *cubeData)
{
    printf("Cube sides a = %d; b = %d; c = %d;\n", cubeData->a, cubeData->b, cubeData->c);

    return;
}

int main() {
    cubeData_t cube;
    cube.a = 4;
    cube.b = 5;
    cube.c = 10;

    findVolume(&cube);

    if (cube.Volume != (cube.a * cube.b * cube.c))
    {
        printf("Failed to calculate the volume!");
        return -1;
    }

    printf("Volume: %d\n", cube.Volume);

    return 0;
}
