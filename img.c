#include <stdio.h>
#include <stdlib.h>
#include "img.h"
#include "object.h"

static unsigned char buf[HEIGHT][WIDTH][3];
static int filecnt = 0;
static char fname[100];

//template_function
void img_clear(void) {
    int i, j;
    for(j = 0; j < HEIGHT; ++j) {
        for(i = 0; i < WIDTH; ++i) {
            buf[j][i][0] = buf[j][i][1] = buf[j][i][2] = 255;
        }
    }
}

//template_function
void img_write(void) {
    sprintf(fname, "img%04d.ppm", ++filecnt);
    FILE *f = fopen(fname, "wb");
    if(f == NULL) { fprintf(stderr, "can't open %s\n", fname); exit(1); }
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    fwrite(buf, sizeof(buf), 1, f);
    fclose(f);
}

struct color mix_color(struct color c, struct color base, double opacity){
    c.r = base.r*(1-opacity)+c.r*opacity;
    c.g = base.g*(1-opacity)+c.g*opacity;
    c.b = base.b*(1-opacity)+c.b*opacity;
    return c;
}

struct color get_pixel(int x, int y){
    struct color temp = {buf[HEIGHT-y-1][x][0],
                         buf[HEIGHT-y-1][x][1],
                         buf[HEIGHT-y-1][x][2]};
    return temp;
}

void put_pixel(struct color c, int x, int y, double opacity) {
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    if(opacity != 1.0) c = mix_color(c,get_pixel(x,y),opacity);
    buf[HEIGHT-y-1][x][0] = c.r;
    buf[HEIGHT-y-1][x][1] = c.g;
    buf[HEIGHT-y-1][x][2] = c.b;
}

void merge_layer(int layer[HEIGHT][WIDTH][3], double opacity){
    struct color c;
    for(int x=0; x<WIDTH; x++){
        for(int y=0; y<HEIGHT; y++){
            if(layer[y][x][0]<0 || layer[y][x][1]<0 || layer[y][x][2]<0) continue;
            c.r = layer[y][x][0]; c.g = layer[y][x][1]; c.b = layer[y][x][2];
            put_pixel(c,x,y,opacity);
        }
    }
}