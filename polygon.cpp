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
  //p.block(f, 0, 0, 800, 600, 0, 0, 0);
    struct termios old_tio, new_tio;

  unsigned char c;

    /* get the terminal settings for stdin */
  tcgetattr(STDIN_FILENO,&old_tio);

  /* we want to keep the old setting to restore them a the end */
  new_tio=old_tio;

  /* disable canonical mode (buffered i/o) and local echo */
  new_tio.c_lflag &= ~ICANON;
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
  //muka senyum
  // kurva atas
  int x[4] = {184, 174, 401, 404};
  int y[4] = {236, 100, 100, 236};
  // muka kanan
  int x1[4] = {183, 177, 258, 292};
  int y1[4] = {236, 296, 401, 410};
  // muka kiri
  int x2[4] = {292, 327, 410, 405};
  int y2[4] = {410, 412, 296, 232};
  // mulut atas
  int x3[4] = {246, 256, 329, 340};
  int y3[4] = {332, 320, 321, 332};
  // mulut bawah
  int x4[4] = {246, 262, 331, 340};
  int y4[4] = {332, 374, 365, 332};
  // mata kiri
  int x5[4] = {306, 314, 348, 352};
  int y5[4] = {234, 193, 193, 234};
  // mata kanan
  int x6[4] = {230, 236, 274, 276};
  int y6[4] = {234, 193, 193, 234};
  // hidung
  int x7[4] = {266, 273, 310, 319};
  int y7[4] = {283, 255, 256, 283};
  // hidung
  int x8[4] = {273, 275, 288, 288};
  int y8[4] = {283, 276, 276, 283};
  // hidung
  int x9[4] = {298, 300, 312, 314};
  int y9[4] = {283, 276, 276, 283};
  
  //muka nangis
  //mulut bawah
  int x10[4] = {246, 258, 322, 340};
  int y10[4] = {352, 335, 335, 352};
  //mulut atas
  int x11[4] = {246, 254, 329, 340};
  int y11[4] = {352, 310, 310, 352};
  //air mata kanan
  int x12[4] = {233, 224, 224, 225};
  int y12[4] = {222, 232, 260, 260};
  //air mata kiri
  int x13[4] = {233, 203, 203, 225};
  int y13[4] = {222, 232, 260, 260};
  //mata kiri
  int x14[4] = {304, 310, 345, 350};
  int y14[4] = {196, 221, 221, 196};
  //mata kanan
  int x15[4] = {236, 241, 276, 281};
  int y15[4] = {196, 221, 221, 196};
  
  //muka marah
  //alis kanan
  int x16[4] = {238, 253, 290, 288};
  int y16[4] = {171, 163, 176, 192};
  //alis kanan bawah
  int x17[4] = {238, 255, 278, 288};
  int y17[4] = {171, 172, 182, 192};
  //mata kanan atas
  int x18[4] = {258, 258, 286, 285};
  int y18[4] = {202, 184, 184, 202};
  //mata kanan bawah
  int x19[4] = {258, 258, 286, 285};
  int y19[4] = {202, 221, 221, 202};
  //alis bawah kiri
  int x20[4] = {304, 314, 338, 355};
  int y20[4] = {190, 180, 170, 170};
  //alis atas kiri
  int x21[4] = {304, 302, 339, 355};
  int y21[4] = {190, 175, 162, 170};
  //mata kiri atas
  int x22[4] = {305, 305, 332, 332};
  int y22[4] = {202, 184, 184, 202};
  //mata kiri bawah
  int x23[4] = {305, 305, 332, 332};
  int y23[4] = {202, 221, 220, 202};
  //mulut bawah
  int x24[4] = {246, 258, 322, 340};
  int y24[4] = {352, 335, 335, 352};
  //mulut atas
  int x25[4] = {246, 254, 328, 340};
  int y25[4] = {352, 310, 311, 352};
  
  //muka kaget
  //alis kanan atas
  int x26[4] = {232, 239, 274, 284};
  int y26[4] = {189, 172, 158, 170};
  //alis kanan bawah
  int x27[4] = {232, 246, 270, 284};
  int y27[4] = {189, 178, 170, 170};
  //alis kiri atas
  int x28[4] = {302, 311, 347, 356};
  int y28[4] = {170, 157, 172, 189};
  //alis kiri bawah
  int x29[4] = {302, 316, 340, 356};
  int y29[4] = {170, 170, 178, 189};
  //mulut atas
  int x30[4] = {246, 255, 329, 340};
  int y30[4] = {350, 320, 321, 350};
  //mulut bawah
  int x31[4] = {246, 259, 323, 340};
  int y31[4] = {350, 368, 367, 350};
  
  //muka merem (tidur)
  //mulut atas
  int x32[4] = {246, 255, 328, 340};
  int y32[4] = {352, 344, 344, 351};
  //mulut bawah
  int x33[4] = {246, 258, 323, 340};
  int y33[4] = {352, 360, 360, 351};
  //alis kanan bawah
  int x34[4] = {232, 246, 270, 284};
  int y34[4] = {189, 177, 170, 170};
  //alis kanan atas
  int x35[4] = {232, 239, 274, 284};
  int y35[4] = {189, 172, 158, 170};
  //alis kiri atas;
  int x36[4] = {301, 307, 345, 356};
  int y36[4] = {179, 164, 168, 181};
  //alis kiri bawah;
  int x37[4] = {301, 314, 340, 356};
  int y37[4] = {179, 174, 174, 181};
  //mata kanan;
  int x38[4] = {246, 246, 283, 283};
  int y38[4] = {202, 210, 211, 202};
  //mata kiri
  int x39[4] = {305, 305, 342, 342};
  int y39[4] = {202, 211, 211, 202};

  p.block(f, 100, 100, 350, 400, 0, 0, 0);
  do{
    c=getchar();
    if(c == 'a'){
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);

      // mulut atas
      bezier(x3, y3, f);
      // mulut bawah
      bezier(x4, y4, f);
      // mata kiri
      bezier(x5, y5, f);
      // mata kanan
      bezier(x6, y6, f);
    } else if(c == 's'){
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);

      //mulut bawah
      bezier(x10, y10, f);
      //mulut atas
      bezier(x11, y11, f);
      //air mata kanan
      bezier(x12, y12, f);
      //air mata kiri
      bezier(x13, y13, f);
      //mata kiri
      bezier(x14, y14, f);
      //mata kanan
      bezier(x15, y15, f);
    } else if(c == 'm'){
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);
      //alis kanan
      bezier(x16, y16, f);
      //alis kanan bawah
      bezier(x17, y17, f);
      //mata kanan atas
      bezier(x18, y18, f);
      //mata kanan bawah
      bezier(x19, y19, f);
      //alis kiri bawah
      bezier(x20, y20, f);
      //alis kiri atas
      bezier(x21, y21, f);
      //mata kiri atas
      bezier(x22, y22, f);
      //mata kiri bawah
      bezier(x23, y23, f);
      //mulut bawah
      bezier(x24, y24, f);
      //mulut atas
      bezier(x25, y25, f);
    } else if(c == 'k'){
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);
      //mata kanan atas
      bezier(x18, y18, f);
      //mata kanan bawah
      bezier(x19, y19, f);
      //mata kiri atas
      bezier(x22, y22, f);
      //mata kiri bawah
      bezier(x23, y23, f);
      //alis kanan atas
      bezier(x26, y26, f);
      //alis kanan bawah
      bezier(x27, y27, f);
      //alis kiri atas
      bezier(x28, y28, f);
      //alis kiri bawah
      bezier(x29, y29, f);
      //mulut atas
      bezier(x30, y30, f);
      //mulut bawah
      bezier(x31, y31, f);
    } else if(c == 't'){
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);
      //mulut atas
      bezier(x32, y32, f);
      //mulut bawah
      bezier(x33, y33, f);
      //alis kanan bawah
      bezier(x34, y34, f);
      //alis kanan atas
      bezier(x35, y35, f);
      //alis kiri atas
      bezier(x36, y36, f);
      //alis kiri bawah
      bezier(x37, y37, f);
      //mata kanan
      bezier(x38, y38, f);
      //mata kiri
      bezier(x39, y39, f);
    }
    else if(c == 'h'){

      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);
      //mulut atas
      bezier(x32, y32, f);
      //mulut bawah
      bezier(x33, y33, f);
      //alis kanan bawah
      bezier(x34, y34, f);
      //alis kanan atas
      bezier(x35, y35, f);
      //alis kiri atas
      bezier(x36, y36, f);
      //alis kiri bawah
      bezier(x37, y37, f);
      //mata kanan
      bezier(x38, y38, f);
      //mata kiri
      bezier(x39, y39, f);
      usleep(100000);
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);
      //mata kanan atas
      bezier(x18, y18, f);
      //mata kanan bawah
      bezier(x19, y19, f);
      //mata kiri atas
      bezier(x22, y22, f);
      //mata kiri bawah
      bezier(x23, y23, f);
      //alis kanan atas
      bezier(x26, y26, f);
      //alis kanan bawah
      bezier(x27, y27, f);
      //alis kiri atas
      bezier(x28, y28, f);
      //alis kiri bawah
      bezier(x29, y29, f);
      //mulut atas
      bezier(x30, y30, f);
      //mulut bawah
      bezier(x31, y31, f);
      usleep(100000);
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);
      //alis kanan
      bezier(x16, y16, f);
      //alis kanan bawah
      bezier(x17, y17, f);
      //mata kanan atas
      bezier(x18, y18, f);
      //mata kanan bawah
      bezier(x19, y19, f);
      //alis kiri bawah
      bezier(x20, y20, f);
      //alis kiri atas
      bezier(x21, y21, f);
      //mata kiri atas
      bezier(x22, y22, f);
      //mata kiri bawah
      bezier(x23, y23, f);
      //mulut bawah
      bezier(x24, y24, f);
      //mulut atas
      bezier(x25, y25, f);
      usleep(100000);
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);

      //mulut bawah
      bezier(x10, y10, f);
      //mulut atas
      bezier(x11, y11, f);
      //air mata kanan
      bezier(x12, y12, f);
      //air mata kiri
      bezier(x13, y13, f);
      //mata kiri
      bezier(x14, y14, f);
      //mata kanan
      bezier(x15, y15, f);

      usleep(100000);
      p.block(f, 100, 100, 350, 400, 0, 0, 0);
      bezier(x, y, f);      
      bezier(x1, y1, f);  
      bezier(x2, y2, f);
      bezier(x7, y7, f);
      bezier(x8, y8, f);
      bezier(x9, y9, f);

      // mulut atas
      bezier(x3, y3, f);
      // mulut bawah
      bezier(x4, y4, f);
      // mata kiri
      bezier(x5, y5, f);
      // mata kanan
      bezier(x6, y6, f);
    }
  } while(c!='q');
  
  return 0;
}
