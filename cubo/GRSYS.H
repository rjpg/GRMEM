// grsys.h
extern float x_min, x_max, y_min, y_max,
	x_center, y_center, r_max,
	density;
extern int ingraphicsmode,//1:graph 2:text
	x__max, y__max, ncolors,
	foregrcolor, backgrcolor;

void initgr (char *hpgfile=0);
void endgr();
void to_text();
void move (float x, float y);
void draw (float x, float y);
void errmess (char *s);
int get_maxcolor (void);
void set_color (int color);
void setbackgroundcolor (int color);
void putpixel (int x, int y);
void horline (int xleft, int xright, int y);
void draw_line (int x1, int y1, int x2, int y2);
int ix(float x), iy(float y);
void text (float x, float y,char *s,char color);
void set_rgb_palette (int colornr, int R, int G, int B);
void shaded_colors (void);


