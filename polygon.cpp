#include "headers.h"

polygon::polygon(std::vector<int> _points) {
   points = _points;
}

void polygon::block(framebuffer f, int startX, int startY, int height, int width, int red, int green, int blue) {
    struct fb_fix_screeninfo finfo = f.getfinfo(); 
    struct fb_var_screeninfo vinfo = f.getvinfo(); 
    char *fbp = f.getfbp();
    int location = 0;
    for (int y = startY; y < startY+height; y++) {
        for (int x = startX; x < startX+width; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = blue;       // Some bluei
                *(fbp + location + 1) = green;  // A little green
                *(fbp + location + 2) = red;    // A lot of red
                *(fbp + location + 3) = 0;      // No transparency
            } else  { //assume 16bpp
                unsigned short int t = red<<11 | green<< 5 | blue;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
    }
}

void polygon::line(framebuffer f, int x0, int y0, int x1, int y1) {
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;
    for(;;){
  	block(f, x0, y0, 1, 1, 0, 0, 0);
    	if(x0==x1 && y0==y1) break;
    	e2 = err;
    	if(e2 >-dx) { err -= dy; x0 += sx; }
   	if(e2 < dy) { err += dx; y0 += sy; }
    }
}

void polygon::draw(framebuffer f, int scale) {
   int i;
   for(i=0;i<points.size()-2;i+=2) 
	 line(f,points[i],points[i+1],points[i+2],points[i+3]);	
   line(f,points[i],points[i+1],points[0],points[1]);	
}	

void polygon::translation(int x, int y) {
   for(int i=0;i<points.size();i+=2) 
    points[i] += i%2>0?y:x;
}

void polygon::rotation(float alpha) {}
void polygon::clip(framebuffer f, int xmin, int ymin, int xmax, int ymax) {}

void bezier (int x[4], int y[4], framebuffer f)
{
    int i;
    double t;

    std::vector<int> vectorpoint;
    for (i=0; i<4; i++){
      vectorpoint.push_back(x[i]);
      vectorpoint.push_back(y[i]);
    }
    polygon p1(vectorpoint);

    for (t = 0.0; t < 1.0; t += 0.0005)
    {
      
      double xt = pow (1-t, 3) * x[0] + 3 * t * pow (1-t, 2) * x[1] + 3 * pow (t, 2) * (1-t) * x[2] + pow (t, 3) * x[3];
 
      double yt = pow (1-t, 3) * y[0] + 3 * t * pow (1-t, 2) * y[1] + 3 * pow (t, 2) * (1-t) * y[2] + pow (t, 3) * y[3];
    
    int xt1 = (int) xt;
    int yt1 = (int) yt;
    p1.block(f, xt1, yt1, 1, 1, 255, 255, 0);
    // std::cout << xt1 << std::endl;
    // std::cout << yt1 << std::endl;
    // 
    }
 

    // for (i=0; i<4; i++){
    //   p1.line(f, x[i], y[i], x[i], y[i]);
    // }
}


int main() {
   framebuffer f;
   // polygon init;
   // init.block(f,0,0,700,1366,255,255,255);
   std::vector<int> points{50,50,400,400,700,900};
   //drawBlock(f.getfinfo(), f.getvinfo(), f.getfbp(), 200, 200, 250, 250, 0,0,0);
   polygon p(points);
   //p.block(f, 0, 0, 800, 600, 255, 255, 0);
   int tesx[4] = {10, 20, 30, 100};
   int tesy[4] = {500, 200, 300, 500};

   bezier(tesx, tesy, f);

   //p.line(f, 300, 350, 100, 100);
   return 0;
}
