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
function figurefunc[11];
int COOKIES[13][27];

void print_figure(int *x, int *y, int dots, int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    for(int i=0; i<dots; i++){
        x[i] += origin_x;
        y[i] += origin_y;
    }
    struct color white = {255,255,255,1.0};
    fill_polygon(x,y,dots,white,layer);
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
    print_segment(false,false,false,false,true,false,false,origin_x,origin_y,layer);
}


void initialize_funcarray(void){
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
    figurefunc[10] = print_comma;
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
}

void apply_figure(int figure,int x,int y, struct color layer[HEIGHT][WIDTH]){
    initialize_funcarray();
    figurefunc[figure](x,y,layer);
}

void print_number(long num, struct color layer[HEIGHT][WIDTH]){
    clear_layer(layer);
    int pos = 28;
    for(int i=0; i<12; i++){
        if(i%3==0 && i!=0){
            figurefunc[10](pos,252,layer);
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

}