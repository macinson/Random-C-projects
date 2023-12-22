#include <stdio.h>
#include <math.h>
#include <string.h>

float A = 0;
int width =160;
int height = 44;

int calcX (float, float,float,float);
int calcY (float, float,float,float);

float ratioH = 0.4;
float ratioW = 0.4;



int main(){

    char table[height][width];
    char buffer[height][width];

    for(int i = 0; i < height;i++){
        for(int j = 0; j < width;j++){
            if(i > height*ratioH && i < (1-ratioH)*height && j > width*ratioW && j < width*(1 - ratioW)){
                table[i][j] = 'x';
            }else if(j == width-1) table[i][j] = 10;
            else table[i][j] = ' ';
            
        }
    }
    while(1){
        memset(buffer, ' ', width * height);
        for(int i = 0; i < height;i++){
            for(int j = 0; j < width;j++){
            buffer[calcX(i,j,height/2,width/2)][calcY(i,j,height/2,width/2)] = table[i][j];
            }
        }
        A += 0.1;
        printf("\x1b[H");
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
    return r;
}

int calcY(float x, float y, float i, float j){
    int r =  (int)(j + y*cos(A) - j*cos(A) - x*sin(A) + i * sin(A));
    return r;
}