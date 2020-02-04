#define WIDTH 200
#define HEIGHT 300
struct color { unsigned char r, g, b; };
void img_clear(void);
void img_write(void);
struct color mix_color(struct color c, struct color base, double opacity);
struct color get_pixel(int x, int y);
void put_pixel(struct color c, int x, int y, double opacity);
void merge_layer(int layer[HEIGHT][WIDTH][3], double opacity);