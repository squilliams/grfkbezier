#ifndef headers_h_
#define headers_h_

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <math.h> 
#include <iostream>
#include <termios.h>
#include <cstring>


class framebuffer {
  private:
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    char *fbp = 0;
    long int screensize = 0;
    int fbfd = 0;
    int x = 0, y = 0;
    long int location = 0;
    uint8_t* fb_ptr;
    uint8_t* framebuffer_ptr;

  public:
    framebuffer();
    char* getfbp();
    struct fb_var_screeninfo getvinfo();
    struct fb_fix_screeninfo getfinfo();
    void frameclose();
    void render();
    void clear();

};

class polygon {
     private:
	std::vector<int> points;	
	int poros[2];
     public:
	polygon(std::vector<int> _points);
	void block(framebuffer f, int startX, int startY, int height, int width, int red, int green, int blue);
	void line(framebuffer f, int x0, int y0, int x1, int y1);
	void draw(framebuffer f, int scale);
	void translation(int x, int y);
	void rotation(float alpha);
	void clip(framebuffer f, int xmin, int ymin, int xmax, int ymax);
};
#endif
