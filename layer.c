#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "layer.h"
#include "object.h"
#include "drawtool.h"

bool is_valid_alpha(struct color c){
    return 0 <= c.a && c.a <= 1;
}

void copy_layer(struct color new_layer[HEIGHT][WIDTH], struct color layer[HEIGHT][WIDTH]){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            new_layer[i][j] = layer[i][j];
        }
    }
}

void clear_layer(struct color layer[HEIGHT][WIDTH]){
    struct color invisible = {0,0,0,0.0};
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            layer[i][j] = invisible;
        }
    }
}

void unite_layer(struct color lower_layer[HEIGHT][WIDTH], struct color upper_layer[HEIGHT][WIDTH]){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            lower_layer[i][j] = lower_layer[i][j].a > 0 ? mix_color(upper_layer[i][j],lower_layer[i][j]) : upper_layer[i][j];
        }
    }
}

void subtract_layer(struct color lower_layer[HEIGHT][WIDTH], struct color upper_layer[HEIGHT][WIDTH]){
    struct color invisible = {0,0,0,0.0};
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(upper_layer[i][j].a<=0) continue;
            lower_layer[i][j] = invisible;
        }
    }
}

void linear_transform(struct color layer[HEIGHT][WIDTH], double matrix[2][2],int origin_x, int origin_y){
    struct color new_layer[HEIGHT][WIDTH];
    clear_layer(new_layer);
    double a,b,c,d;
    a = matrix[0][0]; b = matrix[0][1]; c = matrix[1][0]; d = matrix[1][1];
    int x1,y1;
    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            x1 = (int)round(a*(x-origin_x) + b*(y-origin_y) + origin_x);
            y1 = (int)round(c*(x-origin_x) + d*(y-origin_y) + origin_y);
            if(0 <= x1 && x1 < WIDTH && 0 <= y1 && y1 < HEIGHT){
                new_layer[y1][x1] = layer[y][x];
            }
        }
    }
    clear_layer(layer);
    copy_layer(layer,new_layer);
}

void fill_painted_pixel(struct color layer[HEIGHT][WIDTH], struct color c){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(!is_valid_alpha(layer[i][j])) continue;
            layer[i][j] = c;
        }
    }
}

void rotate_layer(struct color layer[HEIGHT][WIDTH], double degree, int center_x, int center_y){
    double t = 3.14159265359/180.0*degree;
    double matrix[2][2] = {{cos(t),-sin(t)},
                           {sin(t), cos(t)}};
    linear_transform(layer,matrix,center_x,center_y);
}