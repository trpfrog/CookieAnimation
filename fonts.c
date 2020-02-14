#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "img.h"
#include "object.h"
#include "layer.h"
#include "drawtool.h"
#include "fonts.h"

typedef void (*function)(int,int,struct color [HEIGHT][WIDTH]);
function figurefunc[10];
int COOKIE_DUNKER[9][45];
int ACHIEVEMENT[6][61];
int COOKIES[13][27];

void test_print(){
   printf("HelloWorld\n");
}

void print_segment(bool top, bool upper_left, bool upper_right, bool middle, bool lower_left, bool lower_right, bool bottom, int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    struct color white = {255,255,255,1.0};
    if(top)         img_fillrect(white, origin_x+5,  origin_y+13, 6,3, layer);
    if(upper_left)  img_fillrect(white, origin_x+2  , origin_y+10, 3,5, layer);
    if(upper_right) img_fillrect(white, origin_x+8  , origin_y+10, 3,5, layer);
    if(middle)      img_fillrect(white, origin_x+5  , origin_y+7 , 6,3, layer);
    if(lower_left)  img_fillrect(white, origin_x+2  , origin_y+4 , 3,5, layer);
    if(lower_right) img_fillrect(white, origin_x+8  , origin_y+4 , 3,5, layer);
    if(bottom)      img_fillrect(white, origin_x+5,   origin_y+1 , 6,3, layer);
}

void print_0(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,true,false,true,true,true,origin_x,origin_y,layer);
}

void print_1(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(false,false,true,false,false,true,false,origin_x,origin_y,layer);
}

void print_2(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,false,true,true,true,false,true,origin_x,origin_y,layer);
}

void print_3(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,false,true,true,false,true,true,origin_x,origin_y,layer);
}

void print_4(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(false,true,true,true,false,true,false,origin_x,origin_y,layer);
}

void print_5(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,false,true,false,true,true,origin_x,origin_y,layer);
}

void print_6(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,false,true,true,true,true,origin_x,origin_y,layer);
}

void print_7(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,false,true,false,false,true,false,origin_x,origin_y,layer);
}

void print_8(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,true,true,true,true,true,origin_x,origin_y,layer);
}

void print_9(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,true,true,false,true,true,origin_x,origin_y,layer);
}

void print_comma(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    struct color white = {255,255,255,1.0};
    img_fillrect(white,origin_x+2,origin_y,2,6,layer);
}


void initialize_fonts(void){
    figurefunc[0] = print_0;
    figurefunc[1] = print_1;
    figurefunc[2] = print_2;
    figurefunc[3] = print_3;
    figurefunc[4] = print_4;
    figurefunc[5] = print_5;
    figurefunc[6] = print_6;
    figurefunc[7] = print_7;
    figurefunc[8] = print_8;
    figurefunc[9] = print_9;
    int cc[13][28] = {{26,4,7,3,16,-1,-2},
                      {27,3,7,3,16,-1,-2},
                      {27,3,7,3,16,-1,-2},
                      {27,3,26,-1,-2},
                      {2,4,5,4,5,4,3,3,1,4,1,4,3,3,5,3,2,-1,-2},
                      {1,6,3,6,3,6,2,3,2,2,3,3,2,5,3,6,-1,-2},
                      {0,8,1,3,2,3,1,3,2,3,1,3,1,3,3,3,1,3,1,3,1,2,3,2,-1,-2},
                      {0,3,3,2,1,2,4,2,1,2,4,2,1,6,4,3,1,2,3,2,1,4,3,-1,-2},
                      {0,3,6,2,4,2,1,2,4,2,1,5,5,3,1,7,2,5,1,-1,-2},
                      {0,3,6,2,4,2,1,2,4,2,1,6,4,3,1,2,9,4,-1,-2},
                      {0,3,3,2,1,3,2,3,1,3,2,3,1,3,1,3,3,3,1,3,2,2,1,2,3,2,-1,-2},
                      {1,7,2,6,3,6,2,3,2,2,3,3,2,5,2,6,1,-1,-2},
                      {2,5,4,4,5,4,2,5,1,3,1,5,2,3,5,3,2,-1,-2}};
    for(int i=0;i<13;i++){
        for(int j=0;cc[i][j]!=-2;j++){
            COOKIES[i][j] = cc[i][j];
        }
    }
    int ac[][62] = {{2,1,7,1,4,1,50,1,10,1,12,1,-1,-2},
                     {1,1,1,1,6,1,7,2,9,2,9,2,8,1,15,1,10,1,5,2,5,1,-1,-2},
                     {0,1,3,1,2,2,1,1,4,1,1,1,2,1,1,1,3,1,1,1,2,1,1,2,1,1,2,1,2,1,1,3,2,3,4,1,2,1,1,3,2,1,2,2,3,2,1,1,1,2,1,1,2,1,2,3,-1,-2},
                     {0,5,1,1,3,3,2,1,1,4,1,1,3,1,1,4,1,1,1,1,1,1,1,4,1,1,2,1,2,1,5,1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,3,2,3,4,1,1,2,1,-1,-2},
                     {0,1,3,1,1,1,3,1,2,1,1,1,1,1,5,1,1,1,2,1,4,1,1,1,1,1,1,1,4,1,2,1,2,1,5,1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,3,1,1,1,2,1,4,1,2,1,-1,-2},
                     {0,1,3,1,2,2,1,1,2,1,1,1,2,3,3,1,4,3,1,1,1,1,1,1,2,3,1,1,2,1,3,1,5,3,1,1,2,1,1,1,2,2,3,2,1,1,2,1,2,3,2,3,-1,-2}};
    for(int i=0;i<6;i++){
        for(int j=0;ac[i][j]!=-2;j++){
            ACHIEVEMENT[i][j] = ac[i][j];
        }
    }
    int cd[][46] = {{2,4,16,2,5,2,16,2,15,2,17,-1,-2},
                    {1,6,15,2,5,2,16,2,15,2,17,-1,-2},
                    {0,3,3,1,15,2,23,2,15,2,17,-1,-2},
                    {0,2,7,4,3,4,2,2,1,3,1,2,2,4,7,5,1,2,2,2,1,5,2,2,1,3,2,4,3,3,1,-1,-2},
                    {0,2,6,2,2,2,1,2,2,2,1,4,3,2,1,2,2,2,5,2,2,2,1,2,2,2,1,2,2,2,1,4,3,2,2,2,1,5,-1,-2},
                    {0,2,6,2,2,2,1,2,2,2,1,3,4,2,1,6,1,3,1,2,2,2,1,2,2,2,1,2,2,2,1,3,4,6,1,2,3,-1,-2},
                    {0,3,3,1,1,2,2,2,1,2,2,2,1,4,3,2,1,2,9,2,2,2,1,2,2,2,1,2,2,2,1,4,3,2,5,2,3,-1,-2},
                    {1,6,1,2,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,2,5,2,2,2,1,2,2,2,1,2,2,2,1,2,1,2,2,2,2,2,1,2,3,-1,-2},
                    {2,4,3,4,3,4,2,2,2,2,1,2,2,4,7,5,2,5,1,2,2,2,1,2,2,2,2,4,2,2,3,-1,-2}};
    for(int i=0;i<9;i++){
        for(int j=0;cd[i][j]!=-2;j++){
            COOKIE_DUNKER[i][j] = cd[i][j];
        }
    }
}

void print_number(long num, struct color layer[HEIGHT][WIDTH]){
    clear_layer(layer);
    int pos = 25;
    for(int i=0; i<12; i++){
        if(i%3==0 && i!=0){
            print_comma(pos,252,layer);
            pos += 6;
        }
        figurefunc[num/(long)pow(10,11-i)](pos,252,layer);
        num %= (long)pow(10,11-i);
        pos += 11;
    }
}

void print_cookies(struct color layer[HEIGHT][WIDTH]){
    struct color white = {255,255,255,1.0};
    int pos_y = 245;
    for(int i=0; i<13; i++){
        int pos_x = 73;
        for(int j=0; COOKIES[i][j]!=-1; j++){
            if(j%2==1){
                for(int k=0; k<COOKIES[i][j]; k++){
                    layer[pos_y][pos_x++] = white;
                }
            }else{
                pos_x += COOKIES[i][j];
            }
        }
        pos_y--;
    }
}

void print_achievement(struct color layer[HEIGHT][WIDTH],int t){
    struct color white = {255,255,255,1.0};
    int pos_y = t-14+6;
    for(int i=0; i<6; i++){
        int pos_x = 60;
        if(--pos_y<0) break;
        for(int j=0; ACHIEVEMENT[i][j]!=-1; j++){
            if(j%2==1){
                for(int k=0; k<ACHIEVEMENT[i][j]; k++){
                    layer[pos_y][pos_x++] = white;
                }
            }else{
                pos_x += ACHIEVEMENT[i][j];
            }
        }
    }
}


void print_cookiedunker(struct color layer[HEIGHT][WIDTH], int t){
    struct color gray = {200,200,200,1.0};
    int pos_y = t-26+9;
    for(int i=0; i<9; i++){
        int pos_x = 60;
        if(--pos_y<0) break;
        for(int j=0; COOKIE_DUNKER[i][j]!=-1; j++){
            if(j%2==1){
                for(int k=0; k<COOKIE_DUNKER[i][j]; k++){
                    layer[pos_y][pos_x++] = gray;
                }
            }else{
                pos_x += COOKIE_DUNKER[i][j];
            }
        }
    }
}