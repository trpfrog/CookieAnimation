#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "img.h"
#include "layer.h"
#include "object.h"


bool is_within_colorrange(int color[3]){
    for(int i=0; i<3; i++){
        if(color[i]<0 || 255<color[i]) return false;
    }
    return true;
}

void copy_layer(int new_layer[HEIGHT][WIDTH][3], int layer[HEIGHT][WIDTH][3]){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            for(int k=0; k<3; k++){
                new_layer[i][j][k] = layer[i][j][k];
            }
        }
    }
}

void paint_layerpixel(int pixel[3], int color[3]){
    for(int i=0; i<3; i++){
        pixel[i] = color[i];
    }
}

void clear_layer(int layer[HEIGHT][WIDTH][3]){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            for(int k=0; k<3; k++){
                layer[i][j][k] = -1;
            }
        }
    }
}

void unite_layer(int lower_layer[HEIGHT][WIDTH][3],
        int upper_layer[HEIGHT][WIDTH][3], int new_layer[HEIGHT][WIDTH][3]){
    copy_layer(new_layer,lower_layer);
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(!is_within_colorrange(upper_layer[i][j])) continue;
            for(int k=0; k<3; k++){
                paint_layerpixel(new_layer[i][j],upper_layer[i][j]);
            }
        }
    }
}

void subtract_layer(int lower_layer[HEIGHT][WIDTH][3],
        int upper_layer[HEIGHT][WIDTH][3],int new_layer[HEIGHT][WIDTH][3]){
    copy_layer(new_layer,lower_layer);
    int invisible[3] = {-1,-1,-1};
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(!is_within_colorrange(upper_layer[i][j])) continue;
            for(int k=0; k<3; k++){
                paint_layerpixel(new_layer[i][j],invisible);
            }
        }
    }
}

void linear_transform(int layer[HEIGHT][WIDTH][3],
        double matrix[2][2],int origin_x, int origin_y, int new_layer[HEIGHT][WIDTH][3]){
    double a,b,c,d;
    a = matrix[0][0]; b = matrix[0][1]; c = matrix[1][0]; d = matrix[1][1];
    int x1,y1;
    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            x1 = (int)(a*(x-origin_x) + b*(y-origin_y) + origin_x);
            y1 = (int)(c*(x-origin_x) + d*(y-origin_y) + origin_y);
            if(0 <= x1 && x1 < WIDTH && 0 <= y1 && y1 < HEIGHT){
                paint_layerpixel(new_layer[y1][x1],layer[y][x]);
            }
        }
    }
}
