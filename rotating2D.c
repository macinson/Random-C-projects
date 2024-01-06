#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <unistd.h>

double A = 0;
int width =160;
int height = 44;
float radius = 20;
float innerRadius = 10;
double PI = 3.14159265358979323846;
double d = 0.05;
double a = 0;

int calcX (float, float,float,float);
int calcY (float, float,float,float);

float ratioH = 0.3;
float ratioW = 0.45;



int main(){

    char table[height][width];
    char buffer[height][width];
    printf("\x1b[?25l");
    printf("\x1b[2J");
    for(int i = 0; i < height;i++){
        for(int j = 0; j < width;j++){
            if(i > height*ratioH && i < (1-ratioH)*height && j > width*ratioW && j < width*(1 - ratioW)){
                table[i][j] = '#';
            }
            // if((i-height/2)*(i-height/2) + (j-width/2)*(j-width/2) <= radius*radius && (i-height/2)*(i-height/2) + (j-width/2)*(j-width/2) > innerRadius * innerRadius){
            //     table[i][j] = '#';
            // }
            else table[i][j] = ' ';
            
        }
    }
    while(1){

        printf("\x1b[H");
        memset(buffer, ' ', width * height);
        
        for(int i = 0; i < height;i++){
            for(int j = 0; j < width;j++){
                buffer[calcX(i,j,height/2,width/2)][calcY(i,j,height/2,width/2)] = table[i][j];
            }
        }

        A = M_PI * a;
        a += d;
        if(a >= 2) a = 0;
        for(int i = 0; i < height;i++){
            for(int j = 0; j < width;j++){
                putchar((j != width-1) ? buffer[i][j] : '\n');
            }
        }

    }
    

    return 0;
}

int calcX(float x, float y, float i, float j){
    int r = (int)(x*cos(A) + y*sin(A) - j*sin(A) + i*(1-cos(A)));
    if(r >= height) r = height -1;
    if(r < 0) r = 0;
    return r;
}

int calcY(float x, float y, float i, float j){
    int r =  (int)(j + y*cos(A) - j*cos(A) - x*sin(A) + i * sin(A));
    if(r >= width) r = width -1;
    if(r < 0) r = 0;
    return r;
}