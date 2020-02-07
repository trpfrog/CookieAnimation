#include <stdbool.h>
#define WIDTH 200
#define HEIGHT 300
struct color { unsigned char r, g, b; double a; };
void img_clear(void);
void img_write(void);
struct color mix_color(struct color c, struct color base);
struct color get_pixel(int x, int y);
void put_pixel(struct color c, int x, int y);
void merge_layer(struct color layer[HEIGHT][WIDTH]);
bool color_equal(struct color c, struct color d);
void print_color(struct color c);