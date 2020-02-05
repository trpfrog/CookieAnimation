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
