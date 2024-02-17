#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int Y = 160;
int X = 60;
float A, B, C = 0;
char buffer[160 * 60];
float zBuffer[160 * 60 * 4];
int R = 15;
int r = 10;

int calcX(int x, int y, int z)
{
    return cos(C) * (x * cos(B) - sin(B) * (z * cos(A) - y * sin(A))) + sin(C) * (y * cos(A) + z * sin(A));
}

int calcY(int x, int y, int z)
{
    return cos(C) * (y * cos(A) + z * sin(A)) - sin(C) * (x * cos(B) - sin(B) * (z * cos(A) - y * sin(A)));
}

float calcZ(int x, int y, int z)
{
    return (float)x * sin(B) + cos(B) * (z * cos(A) - y * sin(A));
}

void calcDonut(int cx, int cy, char c)
{
    float cz1 = sqrt(r * r - (R - sqrt(cx * cx + cy * cy)) * (R - sqrt(cx * cx + cy * cy)));
    float cz2 = -sqrt(r * r - (R - sqrt(cx * cx + cy * cy)) * (R - sqrt(cx * cx + cy * cy)));
    int x1 = calcX(cx, cy, cz1);
    int x2 = calcX(cx, cy, cz2);
    int y1 = calcY(cx, cy, cz1);
    int y2 = calcY(cx, cy, cz2);
    float z1 = calcZ(cx, cy, cz1);
    float z2 = calcZ(cx, cy, cz2);

    x1 += X / 2;
    y1 += Y / 2;
    x2 += X / 2;
    y2 += Y / 2;

    bool calc1 = true;
    bool calc2 = true;
    if (x1 < 0 || y1 < 0 || x1 >= X || y1 >= Y)
        calc1 = false;
    if (x2 < 0 || y2 < 0 || x2 >= X || y2 >= Y)
        calc2 = false;
    if (calc1 && z1 < zBuffer[x1 * Y + y1] || buffer[x1 * Y + y1] == ' ')
    {
        buffer[x1 * Y + y1] = c;
        zBuffer[x1 * Y + y1] = z1;
    }

    if (calc2 && z2 < zBuffer[x2 * Y + y2] || buffer[x2 * Y + y2] == ' ')
    {
        buffer[x2 * Y + y2] = c;
        zBuffer[x2 * Y + y2] = z2;
    }
}

float distance(int x, int y)
{
    return sqrt(x * x + y * y);
}

void usleep(int ms)
{
    struct timespec t;

    t.tv_sec = 0;
    t.tv_nsec = ms * 1000000;

    nanosleep(&t, &t);
}

int main()
{
    printf("\x1b[?25l");
    printf("\x1b[2J");

    while (1)
    {
        memset(buffer, ' ', X * Y);
        memset(zBuffer, 0, X * Y * 4);
        printf("\x1b[H");

        for (int i = -R - r; i <= R + r; i++)
        {
            for (int j = -R - r; j <= R + r; j++)
            {
                if(distance(i,j) > (float)(R+r) || distance(i,j) < R-r) continue;
                if(distance(i,j) > R + (float)2*r/3) calcDonut(i,j,'.');
                else if(distance(i,j) > R + (float)r/3) calcDonut(i,j,'*');
                else if(distance(i,j) > R - (float)r/3) calcDonut(i,j,'#');
                else if(distance(i,j) > R - (float)2*r/3) calcDonut(i,j,'*');
                else if(distance(i,j) >= (float)R - r) calcDonut(i,j,'.');
            }
        }

        for (int i = 0; i < X * Y; i++)
        {
            putchar(i % Y ? buffer[i] : 10);
        }
        usleep(1);
        A -= 0.1;
        //B -= 0.1;
        //C += 0.1;
    }
    return 0;
}