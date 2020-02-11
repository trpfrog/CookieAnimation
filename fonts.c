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

void print_zero(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,true,false,true,true,true,origin_x,origin_y,layer);
}

void print_one(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(false,false,true,false,false,true,false,origin_x,origin_y,layer);
//    int x[] = {1,3,6,6,3,3};
//    int y[] = {10,14,14,0,0,10};
//    print_figure(x,y,6,origin_x,origin_y,layer);
}

void print_two(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,false,true,true,true,false,true,origin_x,origin_y,layer);
//    int x[] = { 1, 1, 3, 6, 8, 8, 4, 3, 8, 8, 1, 1, 6, 6, 4, 4};
//    int y[] = {10,12,14,14,12, 8, 5, 2, 2, 0, 0, 4, 9, 12,12,10};
//    print_figure(x,y,16,origin_x,origin_y,layer);
}

void print_three(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,false,true,true,false,true,true,origin_x,origin_y,layer);
//    int x[] = {1,1,4,6,8,8,3,3,8,8,1,1,6,6,4,4};
//    int y[] = {10,12,14,14,12,8,3,2,2,0,0,3,8,12,12,10};
//    print_figure(x,y,16,origin_x,origin_y,layer);
}

void print_four(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(false,true,true,true,false,true,false,origin_x,origin_y,layer);
}

void print_five(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,false,true,false,true,true,origin_x,origin_y,layer);
}

void print_six(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,false,true,true,true,true,origin_x,origin_y,layer);
}

void print_seven(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,false,true,false,false,true,false,origin_x,origin_y,layer);
}

void print_eight(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,true,true,true,true,true,origin_x,origin_y,layer);
}

void print_nine(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(true,true,true,true,false,true,true,origin_x,origin_y,layer);
}

void print_comma(int origin_x, int origin_y, struct color layer[HEIGHT][WIDTH]){
    print_segment(false,false,false,false,true,false,false,origin_x,origin_y,layer);
}

void initialize_funcarray(void){
    figurefunc[0] = print_zero;
    figurefunc[1] = print_one;
    figurefunc[2] = print_two;
    figurefunc[3] = print_three;
    figurefunc[4] = print_four;
    figurefunc[5] = print_five;
    figurefunc[6] = print_six;
    figurefunc[7] = print_seven;
    figurefunc[8] = print_eight;
    figurefunc[9] = print_nine;
    figurefunc[10] = print_comma;
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