#include <stdbool.h>
bool is_within_colorrange(int color[3]);
void copy_layer(int new_layer[HEIGHT][WIDTH][3], int layer[HEIGHT][WIDTH][3]);
void paint_layerpixel(int pixel[3], int color[3]);
void clear_layer(int layer[HEIGHT][WIDTH][3]);
void unite_layer(int lower_layer[HEIGHT][WIDTH][3], int upper_layer[HEIGHT][WIDTH][3], int new_layer[HEIGHT][WIDTH][3]);
void subtract_layer(int lower_layer[HEIGHT][WIDTH][3], int upper_layer[HEIGHT][WIDTH][3], int new_layer[HEIGHT][WIDTH][3]);
