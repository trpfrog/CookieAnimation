#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "img.h"
#include "object.h"
#include "layer.h"
#include "drawtool.h"

int max(int i, int j){
    return i > j ? i : j;
}

int min(int i, int j){
    return i < j ? i : j;
}

//template_function
void img_fillcircle(struct color c, int x, int y, double r, struct color layer[HEIGHT][WIDTH]) {
    int imin = max((int)(x - r - 1), 0), imax = min((int)(x + r + 1),WIDTH-1);
    int jmin = max((int)(y - r - 1), 0), jmax = min((int)(y + r + 1),HEIGHT-1);
    int i, j;
    for(j = jmin; j <= jmax; ++j) {
        for(i = imin; i <= imax; ++i) {
            if((x-i)*(x-i) + (y-j)*(y-j) <= r*r){
                layer[j][i] = mix_color(c,layer[j][i]);
            }
        }
    }
}

//template_function
void img_fillrect(struct color c, double x, double y, double w, double h, struct color layer[HEIGHT][WIDTH]){
    int imin = max((int)(x - w / 2),0), imax = min((int)(x + w / 2),WIDTH-1);
    int jmin = max((int)(y - h / 2),0), jmax = min((int)(y + h / 2),HEIGHT-1);
    int i, j;
    for (j = jmin; j <= jmax; ++j){
        for (i = imin; i <= imax; ++i){
            layer[j][i] = mix_color(c,layer[j][i]);
        }
    }
}

void fill_polygon(int x[], int y[], int dots, struct color c, struct color layer[HEIGHT][WIDTH]){
    int x_max = 0; int x_min = WIDTH-1;
    int y_max = 0; int y_min = HEIGHT-1;
    for(int i=0; i<dots; i++){
        if (x_max < x[i]) x_max = x[i];
        if (x_min > x[i]) x_min = x[i];
        if (y_max < y[i]) y_max = y[i];
        if (y_min > y[i]) y_min = y[i];
    }

    double invisible = -1.0;
    double marker    = -2.0;
    double ignore    = -3.0;

    for(int i=y_min; i<=y_max; i++){
        for(int j=x_min; j<=x_max; j++){
            layer[i][j].a = invisible;
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
            layer[draw_y][j].a = marker;
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
                        layer[draw_y][x1].a = ignore;
                    }
                }
            }
        }
        layer[y[i]][x[i]].a = ignore;
    }

    //縦のスキャンラインで塗る
    for(int draw_x = x_min; draw_x <= x_max; draw_x++){
        struct color brush;
        struct color invisible_brush = {c.r,c.g,c.b,-1.0};
        brush = invisible_brush;
        for(int draw_y = y_min; draw_y <= y_max; draw_y++){
            if(layer[draw_y][draw_x].a==ignore){
                continue;
            }else if(layer[draw_y][draw_x].a==marker){
                brush = (color_equal(brush,c) ? invisible_brush : c);
                continue;
            }
            layer[draw_y][draw_x] = mix_color(layer[draw_y][draw_x],brush); //バグが起きるならmix_colorはやめて直接代入にした方が良さそう
        }
    }

    //枠線と頂点を塗る
    for(int draw_x = x_min; draw_x <= x_max; draw_x++){
        for(int draw_y = y_min; draw_y <= y_max; draw_y++) {
            if (layer[draw_y][draw_x].a == ignore || layer[draw_y][draw_x].a == marker){
                layer[draw_y][draw_x] = mix_color(layer[draw_y][draw_x],c);
            }
        }
    }
}