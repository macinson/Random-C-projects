#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

const int X = 160;
const int Y = 44;
float A,B,C = 0;


typedef struct 
{
    int x;
    int y;
    int z;
} point;


typedef struct{
    point a;
    point b;
    point c;
} triangle;

triangle triangles[5];

int calcX(){
    return 0;
}

int calcY(){
    return 0;
}

int calcZ(){
    return 0;
}

void calcSurface(){

}

void usleep(int ms){
    struct timespec t;

    t.tv_sec = 0;
    t.tv_nsec = ms * 1000000;

    nanosleep(&t,&t);
}

int main(){
    printf("\x1b[?25l");
    printf("\x1b[2J");
    char buffer[X*Y];
    float zBuffer[X*Y*4];

    while(1){
        memset(buffer, ' ', X*Y);
        memset(zBuffer, 0, X*Y*4);
        printf("\x1b[H");
        for(int i = 0; i < sizeof(triangles)/sizeof(triangle); i++){
            calcSurface(triangles[i]);
        }

        for(int i = 0; i < X*Y; i++){
            putchar(i % X ? buffer[i] : 10);
        }
        if(kbhit()){
            if(getch() == 'w'){
                A += 0.1;
            }
        }
        usleep(1);
    }
    return 0;
}