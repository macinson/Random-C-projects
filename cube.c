#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Y = 160;
int X = 60;
float A, B, C = 0;
char buffer[160*60];
float zBuffer[160*60*4];
int w = 12;

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
    return (float) x * sin(B) + cos(B) * (z * cos(A) - y * sin(A));
}

void calcSurface(int cx, int cy, int cz, char c){
    int x = calcX(cx,cy,cz);
    int y = calcY(cx,cy,cz);
    float z = calcZ(cx,cy,cz);

    x += X/2;
    y += Y/2;

    if(x < 0 || y < 0|| x >= X || y >= Y) return;

    if(z < zBuffer[x*Y + y] || buffer[x*Y + y] == ' '){
        buffer[x*Y + y] = c;
        zBuffer[x*Y + y] = z;
    }

}


void usleep(int ms){
    struct timespec t;

    t.tv_sec = 0;
    t.tv_nsec = ms * 1000000;

    nanosleep(&t,&t);
}

int main()
{

    printf("\x1b[?25l");
    printf("\x1b[2J");

    while(1){
        memset(buffer, ' ', X*Y);
        memset(zBuffer, 0, X*Y*4);
        printf("\x1b[H");
        for(int i = -w; i < w; i++){
            for(int j = -w; j < w; j++){
                calcSurface(i,j,-w,'#');
                calcSurface(i,j,w,'@');
                calcSurface(w,j,i,'<');
                calcSurface(-w,j,i,'*');
                calcSurface(i,-w,j,'\"');
                calcSurface(i,w,j,',');
            }
        }

        for(int i = 0; i < X*Y; i++){
            putchar(i % Y ? buffer[i] : 10);
        }
        usleep(1);
        A -= 0.1;
        B -= 0.1;
        C += 0.1;
    }
    return 0;
}