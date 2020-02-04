#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "object.h"

void draw_background(void){
    //頼んだ つまみより
}

void bake_cookie(void){

}

void bake_background_cookie(void){

}

//template_function
void img_fillcircle(struct color c, int x, int y, double r) {
    int imin = x - r - 1, imax = x + r + 1;
    int jmin = y - r - 1, jmax = y + r + 1;
    int i, j;
    for(j = jmin; j <= jmax; ++j) {
        for(i = imin; i <= imax; ++i) {
            if((x-i)*(x-i) + (y-j)*(y-j) <= r*r) put_pixel(c, i, j, 1.0);
        }
    }
}

void fill_polygon(int x[], int y[], int dots, struct color c, double opacity){
    int x_max = 0; int x_min = WIDTH-1;
    int y_max = 0; int y_min = HEIGHT-1;
    for(int i=0; i<dots; i++){
        if (x_max < x[i]) x_max = x[i];
        if (x_min > x[i]) x_min = x[i];
        if (y_max < x[i]) y_max = y[i];
        if (y_min > y[i]) y_min = y[i];
    }

    int layer[HEIGHT][WIDTH][3];
    int invisible[3] = {-1,-1,-1};
    int marker[3]    = {-2,-2,-2};
    int ignore[3]    = {-3,-3,-3};
    int color[3]     = {c.r,c.g,c.b};

    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            for(int k=0; k<3; k++){
                layer[i][j][k] = invisible[k];
            }
        }
    }

    //枠を描く
    int x0, x1, x2, y0, y1, y2;
    for(int i=0; i<dots; i++){
        x1 = x[i%dots]; x2 = x[(i+1)%dots];
        y1 = y[i%dots]; y2 = y[(i+1)%dots];
        if(x1 > x2){
            int temp_x,  temp_y;
            temp_x = x1; temp_y = y1;
            x1 = x2;     y1 = y2;
            x2 = temp_x; y2 = temp_y;
        }
        if(WIDTH <= x1 || x1 == x2) continue;
        double m = (y1-y2)/(double)(x1-x2);

        int draw_y;
        for(int j = x1; j<=x2; j++){
            draw_y = (int)(m*(j-x1)+y1);
            if(draw_y<0 || HEIGHT<=draw_y || j<0) continue;
            for(int b=0; b<3; b++){
                layer[draw_y][j][b] = marker[b];
            }
        }
    }

    //無視する頂点に印をつける
    for(int i=0; i<dots; i++){
        x0 = x[(i-1)%dots];
        x1 = x[i%dots];
        x2 = x[(i+1)%dots];
        if((x0 < x1 && x1 < x2)||(x2 < x1 && x1 < x0)) continue;
        if(x0==x1||x1==x2){
            for(int j=0; j<2; j++){
                if(x[(i+j-1)%dots]==x[(i+j)%dots]){
                    y0 = y[(i+j-1)%dots];
                    y1 = y[(i+j)%dots];
                    if(y0 > y1){
                        int temp_y;
                        temp_y = y1;
                        y1 = y2;
                        y2 = temp_y;
                    }
                    for(int draw_y = y0; draw_y <= y1; draw_y++){
                        for(int b=0; b<3; b++){
                            layer[draw_y][x1][b] = ignore[b];
                        }
                    }
                }
            }
        }
        for(int b=0; b<3; b++){
            layer[y[i]][x[i]][b] = ignore[b];
        }
    }

    //縦のスキャンラインで塗る
    for(int draw_x = x_min; draw_x <= x_max; draw_x++){
        int *brush;
        brush = invisible;
        for(int draw_y = y_min; draw_y <= y_max; draw_y++){
            if(layer[draw_y][draw_x][0]==ignore[0]) continue;
            if(layer[draw_y][draw_x][0]==marker[0]){
                brush = ((brush[0] == color[0] &&
                          brush[1] == color[1] &&
                          brush[2] == color[2]) ? invisible : color);
                continue;
            }
            for(int b=0; b<3; b++){
                layer[draw_y][draw_x][b] = brush[b];
            }
        }
    }

    //枠線と頂点を塗る
    for(int draw_x = x_min; draw_x <= x_max; draw_x++){
        for(int draw_y = y_min; draw_y <= y_max; draw_y++) {
            if (layer[draw_y][draw_x][0] != ignore[0] && layer[draw_y][draw_x][0] != marker[0]) continue;
            for(int b=0; b<3; b++){
                layer[draw_y][draw_x][b] = color[b];
            }
        }
    }
    merge_layer(layer,opacity);
}