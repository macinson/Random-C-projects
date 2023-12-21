#include <stdio.h>
#include <math.h>

float A = 0.5;
int width =160;
int height = 44;

int calcX (int, int,int,int);
int calcY (int, int,int,int);

float ratioH = 0.25;
float ratioW = 0.25;



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
        // for(int i = 0; i < height;i++){
        //     for(int j = 0; j < width;j++){
        //     buffer[calcY(i,j,width/2,height/2)][calcX(i,j,width/2,height/2)] = table[i][j];
        //     }
        // }

        // for(int i = 0; i < height;i++){
        //     for(int j = 0; j < width;j++){
        //     table[i][j] = buffer[i][j];
        //     }
        // }
        printf("\x1b[H");
        for(int i = 0; i < height;i++){
            for(int j = 0; j < width;j++){
                putchar((j != width-1) ? table[i][j] : '\n');
            }
        }
    }
    

    return 0;
}

int calcX(int x, int y, int i, int j){
    return (int)(x*sin(A) + y*cos(A) - j*cos(A) + i*(j-sin(A)));
}

int calcY(int x, int y, int i, int j){
    return (int)(j*sin(A) +j+ x*cos(A) - y*sin(A) - i*cos(A));
}