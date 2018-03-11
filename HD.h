/* 
 * File:   main.c
 * Author: raichu
 *
 * Created on July 2, 2011, 4:14 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <math.h>

#define PI 3.141592654

#define FRACT_MANDEL_SET 0

int WIDTH=1024, HEIGHT=868;
    

typedef struct _cplane
{
   double xMin;
   double xMax;
   double yMin;
   double yMax;
}ComplexPlane;

typedef struct _cnumb
{
   double real;
   double imm;
}ComplexNumber;


SDL_Surface *screen;
SDL_Surface *menu = NULL;
SDL_Event event;

void putpixel(int x, int y, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4);
  ptr[lineoffset + x] = color;
}

void putpixelup(int xx, int yy, int dx, int dy, int color){
    yy = yy*-1;
    putpixel(xx+dx, yy+dy, color);
}


void putpixel3d(int xx, int yy, int zz, int dx, int dy, int color){
    int xz, yz;

    if(zz==0){
        putpixelup(xx, yy, dx, dy, color);
    }
    if(zz>0){
       // xz = sqrt(pow(zz, 2)/2)*-1;
       // yz = xz;
        xz = sqrt(pow(zz, 2)/1.5)*-1;
        //xz =0;
        yz = (.25)*xz;

  //      xz=0;
  //      yz=0;

        putpixelup(xz+xx, yz+yy, dx, dy, color);
    }
    if(zz<0){
        xz = sqrt(pow(zz, 2)/2);
        yz = xz;
        putpixelup(xz+xx, yz+yy, dx, dy, color);
    }

}



double Cos(double x1){
    double y;
    y = cos(x1*PI/180);
    return y;
}

double Sin(double x1){
    double y;
    y = sin(x1*PI/180);
    return y;
}

int init(void){

    // Initialize SDL's subsystems - in this case, only video.
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  // Attempt to create a 640x480 window with 32bit pixels.
  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
SDL_putenv("SDL_VIDEO_CENTERED=center");
    SDL_WM_SetCaption( "Afractal", NULL );
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }

}



//////////////////////////////////HAWAIIAN EARRING///////////////////////////////////////


int HawaiianEarring(void) {

    int i, y2, x2, j, x, y;





    // Initialize SDL's subsystems - in this case, only video.
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  // Attempt to create a 640x480 window with 32bit pixels.
//  screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

    menu = SDL_LoadBMP("/home/raichu/NetBeansProjects5/11.fractals/images/menu.bmp");
	SDL_Rect offset;
	offset.x = 0;
	offset.y = HEIGHT-200;
    SDL_BlitSurface(menu, NULL, screen, &offset);
   SDL_putenv("SDL_VIDEO_CENTERED=center");
    SDL_WM_SetCaption( "Afractal: The Hawaiian earring.", NULL );
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }


    float m1, n1, m2, n2, m3, n3, m4, n4, l;
    int l2, R=300, dx1=320, dy1=320, dx2=320, dy2=320, dx=320, dy=320;
    int m01, n01, m02, n02, m03, n03, m04, n04;

    for(l=0; l<=360; l= l+1){
            m1 = Cos(l)*R;
            n1 = Sin(l)*R;
            m01 = (int) m1;
            n01 = (int) n1;
         //   putpixelup(m01, n01, dx1, dy, 0xffffff);
    }

    for(l2=0; l2<10; l2++){ // # of circles
        for(l=0; l<=360; l= l+.1){ // points per circle
            m1 = Cos(l)*R;
            n1 = Sin(l)*R;
            m01 = (int) m1;
            n01 = (int) n1;

            m2 = Cos(l)*R;
            n2 = Sin(l)*R;
            m02 = (int) m2;
            n02 = (int) n2;

            m3 = Cos(l)*R;
            n3 = Sin(l)*R;
            m03 = (int) m3;
            n03 = (int) n3;

            m4 = Cos(l)*R;
            n4 = Sin(l)*R;
            m04 = (int) m4;
            n04 = (int) n4;

            putpixelup(m01, n01, dx1, dy, 0xffffff);//left

            putpixelup(m02, n02, dx2, dy, 0x0000ff);//right

            putpixelup(m03, n03, dx, dy1, 0xff00ff);//top

            putpixelup(m04, n04, dx, dy2, 0xffff00);//bottom

           // printf("%d Cos(%3.0f) = %d\n", l2, l, m2);
           // printf("%d Sin(%3.0f) = %d\n", l2, l, n2);
        }

        R = R/2;
        dx1 = dx1 - R;
        dx2 = dx2 + R;
        dy1 = dy1 - R;
        dy2 = dy2 + R;
    }

    int quit = 0;

   SDL_UnlockSurface(screen);
   SDL_Flip(screen);

}



//////////////////////////////////SIERPINSKI PYRAMID///////////////////////////////////////



int SierpinskiPyramid(void) {

    int i, y2, x2, j, x, y, X,Y,Z;






    // Initialize SDL's subsystems - in this case, only video.
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  // Attempt to create a 640x480 window with 32bit pixels.
//  screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);
  screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
    menu = SDL_LoadBMP("/home/raichu/NetBeansProjects5/11.fractals/images/menu.bmp");
	SDL_Rect offset;
	offset.x = 0;
	offset.y = HEIGHT-200;
    SDL_BlitSurface(menu, NULL, screen, &offset);
   SDL_putenv("SDL_VIDEO_CENTERED=center");
    SDL_WM_SetCaption( "Afractal: Sierpisnki Pyramid. 10000000 dots.", NULL );
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }


    for(x2=640, y2=0 ; x2>0, y2<640; x2--, y2++){

        y = x2;

        putpixel(320, y, 0x0000ff);
        putpixel(y2, 320, 0x0000ff);

        // Tell SDL to update the whole screen
     //   SDL_UpdateRect(screen, 0, 0, 1024, 768);
    }

    x = sqrt(pow(100, 2)/2);

    //pyramid
    for(X=00, Y=00, Z=00; X<250, Y<250, Z<250; X++, Y++, Z++){

        putpixel3d(X, 0, 0, 320, 320, 0xff0000);

        putpixel3d(0, Y, 0, 320, 320, 0xff0000);

        putpixel3d(0, 0, Z, 320, 320, 0xff0000);

       // SDL_UpdateRect(screen, 0, 0, 640, 640);
    }
    //pyramid
    for(i=0; i<=200; i++){
        putpixel3d(200-i/2, i/1.16, 200-i/2, 320, 320, 0xffffff);
        putpixel3d(i/2    , i/1.16, i/2    , 320, 320, 0xffffff);
        putpixel3d(i/2    , i/1.16, 200-i/2, 320, 320, 0xffffff);
        putpixel3d(200-i/2, i/1.16, i/2    , 320, 320, 0xffffff);

        putpixel3d(i, 0, 200, 320, 320, 0xff0000);
        putpixel3d(200, 0, i, 320, 320, 0xff0000);
      //  SDL_UpdateRect(screen, 0, 0, 640, 640);
    }

    //Point 0
    int Px=100, Py=86, Pz=100;
    putpixel3d(Px, Py, Pz, 320, 320, 0xaaaaaa);
//    SDL_UpdateRect(screen, 0, 0, 640, 640);

    //Right upper dot 1
    int rux=200, ruy=0, ruz=0;
    putpixel3d(rux, ruy, ruz, 320, 320, 0x00ff00);
    //Right lowet dot 2
    int rlx=200, rly=0, rlz=200;
    putpixel3d(rlx, rly, rlz, 320, 320, 0x00ff00);
    //Left upper dot 3
    int lux=0, luy=0, luz=0;
    putpixel3d(lux, luy, luz, 320, 320, 0x00ff00);
    //Left lower dot 4
    int llx=0, lly=0, llz=200;
    putpixel3d(llx, lly, llz, 320, 320, 0x00ff00);
    //Upper dot 5
    int udx=100, udy=173, udz=100;
    putpixel3d(udx, udy, udz, 320, 320, 0x00ff00);
//      SDL_UpdateRect(screen, 0, 0, 640, 640);

//New dots
    int nx=0, ny=0, nz=0;


    int R;
    long int r0=0;
    while(r0<=10000000){
        r0++;
        R = rand()%5;

      //  printf("%d\n", R);

        //Left upper dot 0
        if(R==0){
            nx = (Px-lux)/2;
            ny = (Py-luy)/2;
            nz = (Pz-luz)/2;

            Px = nx;
            Py = ny;
            Pz = nz;

            putpixel3d(Px, Py, Pz, 320, 320, 0xff00ff);
           // SDL_UpdateRect(screen, 0, 0, 640, 640);
        }

        //Left lower dot 1
        if(R==1){
            nx = (Px-llx)/2;
            ny = (Py-lly)/2;
            nz = (llz-Pz)/2;

            Px = nx;
            Py = ny;
            Pz = nz + Pz;

            putpixel3d(Px, Py, Pz, 320, 320, 0xff0000);
           // SDL_UpdateRect(screen, 0, 0, 640, 640);
        }

        //Right upper dot 2
        if(R==2){
            nx = (rux-Px)/2;
            ny = (Py-ruy)/2;
            nz = (Pz-ruz)/2;

            Px = nx + Px;
            Py = ny;
            Pz = nz;

            putpixel3d(Px, Py, Pz, 320, 320, 0x00ff00);
           // SDL_UpdateRect(screen, 0, 0, 640, 640);
        }

        //Right lower dot 3
        if(R==3){
            nx = (rlx-Px)/2;
            ny = (Py-rly)/2;
            nz = (rlz-Pz)/2;

            Px = nx + Px;
            Py = ny;
            Pz = nz + Pz;

            putpixel3d(Px, Py, Pz, 320, 320, 0x0000ff);
           // SDL_UpdateRect(screen, 0, 0, 640, 640);
        }

        //Upper dot 4
        if(R==4){
            //Quadrant 2
            if((Px < 100)&&(Pz < 100)){
                nx = (udx-Px)/2;
                ny = (udy-Py)/2;
                nz = (udz-Pz)/2;

                Px = nx + Px;
                Py = ny + Py;
                Pz = nz + Pz;

                putpixel3d(Px, Py, Pz, 320, 320, 0xffff00);
               // SDL_UpdateRect(screen, 0, 0, 640, 640);
            }


            //Quadrant 3
            if((Px < 100)&&(Pz > 100)){
                nx = (udx-Px)/2;
                ny = (udy-Py)/2;
                nz = (Pz-udz)/2;

                Px = nx + Px;
                Py = ny + Py;
                Pz = nz + udz;

                putpixel3d(Px, Py, Pz, 320, 320, 0xffff00);
              //  SDL_UpdateRect(screen, 0, 0, 640, 640);
            }
            //Quadrant 4
            if((Px > 100)&&(Pz > 100)){
                nx = (Px-udx)/2;
                ny = (udy-Py)/2;
                nz = (Pz-udz)/2;

                Px = nx + udx;
                Py = ny + Py;
                Pz = nz + udz;

                putpixel3d(Px, Py, Pz, 320, 320, 0xffff00);
               // SDL_UpdateRect(screen, 0, 0, 640, 640);
            }
            //Quadrant 1
            if((Px > 100)&&(Pz < 100)){
                nx = (Px-udx)/2;
                ny = (udy-Py)/2;
                nz = (udz-Pz)/2;

                Px = nx + udx;
                Py = ny + Py;
                Pz = nz + Pz;

                putpixel3d(Px, Py, Pz, 320, 320, 0xffff00);
              //  SDL_UpdateRect(screen, 0, 0, 640, 640);
            }

        }

    }//while 100000
    SDL_Flip(screen);

 int quit = 0;

   SDL_UnlockSurface(screen);
   SDL_Flip(screen);


}



//////////////////////////////////SIERPINSKI TRIANGLE///////////////////////////////////////




int SierpinskiTriangle(void) {

    int i, y2, x2, j, x, y;





    // Initialize SDL's subsystems - in this case, only video.
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  // Attempt to create a 640x480 window with 32bit pixels.
//  screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

    menu = SDL_LoadBMP("/home/raichu/NetBeansProjects5/11.fractals/images/menu.bmp");
	SDL_Rect offset;
	offset.x = 0;
	offset.y = HEIGHT-200;
    SDL_BlitSurface(menu, NULL, screen, &offset);
   SDL_putenv("SDL_VIDEO_CENTERED=center");
    SDL_WM_SetCaption( "Afractal: Sierpinski Triangle. 1000000000 dots.", NULL );
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }


    float m, n, l;
    int m2, n2, l2;
    //Line 1, Bottom
    for(x2=0; x2<=400; x2++){
        putpixelup(x2, 0, 120, 400, 0xff0000);
    }
    //Line 2, Left
    for(l=0; l<=200; l= l + .5){
        m = (l)*1.732050808;
        m2 = (int) m;
        l2 = (int) l;
        putpixelup(l2, m2, 120, 400, 0xff0000);
    }
    //Line 3, Right
    for(l=0; l<=200; l= l + .5){
        m = l*-1.732050808 + 347;
        m2 = (int) m;
        l2 = (int) l;
        l2 = l2 + 200;
        putpixelup(l2, m2, 120, 400, 0xff0000);
    }
    //Point 0
    int bx = 200, by = 173, px=0, py=0;
    putpixelup(bx, by, 120, 400, 0xff0000);



    //Dots Coordinates
    int ldx=-1, ldy=0, rdx=400, rdy=0, udx=200, udy=347;
    //Draw Dots
    //Left Dot
    putpixelup(ldx, ldy, 120, 400, 0xffffff);

    //Right Dot
    putpixelup(rdx, rdy, 120, 400, 0xffffff);

    //Upper Dot
    putpixelup(udx, udy, 120, 400, 0xffffff);



    int R;
    long int r0=0;
    while(r0<=1000000){
        r0++;
        R = rand()%3;

        // Left Dot
        if(R==0){

            px = (bx-ldx)/2;
            py = (by-ldy)/2;
            bx = px;
            by = py;
            putpixelup(px, py, 120, 400, 0xff0000);
           // printf("%d = ", 000);
            //printf("x: %d  y:%d\n", px, py);

            //SDL_UpdateRect(screen, 0, 0, 640, 640);
        }
      //  printf("%d %ld\n", R, r0);

        //Right Dot
        if(R==1){
            px = (rdx-bx)/2;
            px = px + bx;
            py = (by-rdy)/2;
            bx = px;
            by = py;
            putpixelup(px, py, 120, 400, 0xff0000);
            //printf("%d = ", 111);
            //printf("x: %d  y:%d\n", px, py);

            //SDL_UpdateRect(screen, 0, 0, 640, 640);
        }

        //Upper Dot
        if(R==2){

            if((bx==200)&&(by<346)){
                continue;
              /*  px = bx;

                py = by/2;
                py = py + by;

                bx = px;
                by = py;

                printf("%d = ", 2202);
                printf("x: %d  y:%d\n", px, py);
                if(py<346){
                    putpixelup(px, py, 120, 400, 0xff0000);
                }*/

            }

            if(bx>200){
                px = (bx-udx)/2;
                px = px + udx;
                py = (udy-by)/2;
                py = py + by;
                bx = px;
                by = py;
                putpixelup(px, py, 120, 400, 0xff0000);
              //  printf("%d = ", 2212);
                //printf("x: %d  y:%d\n", px, py);

                //SDL_UpdateRect(screen, 0, 0, 640, 640);
            }

            if(bx<200){
                px = (udx-bx)/2;
                px = px + bx;
                py = (udy-by)/2;
                py = py + by;
                bx = px;
                by = py;
                putpixelup(px, py, 120, 400, 0xff0000);
                //printf("%d = ", 2222);
                //printf("x: %d  y:%d\n", px, py);

                //SDL_UpdateRect(screen, 0, 0, 640, 640);
            }


        }



    }
    SDL_Flip(screen);


   SDL_UnlockSurface(screen);
   SDL_Flip(screen);


}



//////////////////////////////////MANDELBROT SET///////////////////////////////////////





void computeFractalM(SDL_Surface *scrn, ComplexPlane cp, int type);

int MandelbrotSet(void)
{




   SDL_Surface *screen;
   SDL_Event event;
   ComplexPlane cp = {-2.0, 2.0, -2.0, 2.0};
   int quit = 0;

   printf("My pid is %d, kill me!\n", getpid()); //used to kill the process

   if(SDL_Init(SDL_INIT_VIDEO) < 0)
   {
      fprintf(stderr, "SDL_Init(): %s\n", SDL_GetError());
      exit(1);
   }

   atexit(SDL_Quit);

   SDL_putenv("SDL_VIDEO_CENTERED=center");
   SDL_WM_SetCaption("Afractal: Mandelbrot Set", NULL);
 //  if(!(screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE)))
  // if(!(screen = SDL_SetVideoMode(1280, 960, 8, SDL_SWSURFACE)))
   if(!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, 8, SDL_SWSURFACE)))
   {
      fprintf(stderr, "SDL_SetVideoMode(): %s\n", SDL_GetError());
      exit(1);
   }
    //screen = SDL_SetVideoMode(1024, 968, 32, SDL_SWSURFACE);

    menu = SDL_LoadBMP("/home/raichu/NetBeansProjects5/11.fractals/images/menu.bmp");
	SDL_Rect offset;
	offset.x = 0;
	offset.y = HEIGHT-200;
    SDL_BlitSurface(menu, NULL, screen, &offset);



   float cr, ci, zoom=2, mover=-1;
   int end, rep;
 
	computeFractalM(screen, cp, 0);
        SDL_Flip(screen);
   SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );

  


}

void computeFractalM(SDL_Surface *srfc, ComplexPlane cp, int type)
{
   ComplexNumber z_n, c, temp;
   uint16_t w, h, n;
   uint8_t *buffer, *line, *pixel;

   //verify surface
   printf("Surface size %d x %d, depth %d \n", srfc -> w, srfc -> h, srfc -> format -> BytesPerPixel);


   SDL_LockSurface(srfc);

   buffer = (uint8_t *)srfc -> pixels;
   line = buffer;
   //for(h = 0; h < srfc -> h; h++)
   for(h = srfc -> h; h > 0; h--)
   {
      pixel = line;
      for(w = 0; w < srfc -> w; w++)
      //for(w = srfc -> w; w > 0; w--)
      {
         //conversion from discrete screen position to continous complex numbers in the plane
         c.real    = ((double)w * ((cp.xMax - cp.xMin) / (double)srfc -> w)) + cp.xMin;
         c.imm     = ((double)h * ((cp.yMax - cp.yMin) / (double)srfc -> h)) + cp.yMin;
         z_n = c;
         for(n = 0; n < 64; n++) //--# of iterations
         {
            if(((z_n.real * z_n.real) + (z_n.imm * z_n.imm)) > 4.0)//--determing the region inside the plane
            {
               switch(srfc -> format -> BytesPerPixel)//--coloration
               {
                  case 1:
                     *pixel = n;
                     break;
                  case 3://simple coloration - do not care aboit it
                     pixel[0] = n;
                     pixel[1] = (n * n) % 256;
                     pixel[2] = (n * n * n) % 256;
                     break;
                  default://--error check
                     fprintf(stderr, "Pixel depth not yet supported: %d\n4", srfc -> format -> BytesPerPixel);
                     exit(1);
                     break;
               }//switch
               break;
            }//if

            //else
           temp.real    = (z_n.real * z_n.real) - (z_n.imm * z_n.imm) + c.real;
             //temp.real    = 1 - z_n.real + z_n.imm;
             //temp.imm     = z_n.imm * temp.real;
          temp.imm     = 2.0 * z_n.real * z_n.imm + c.imm;
            z_n = temp;
         }//for n
         pixel += srfc -> format -> BytesPerPixel;
      }//for w
      line += srfc -> pitch;
   }//for h
   SDL_UnlockSurface(srfc);
}//function




//////////////////////////////////JULIA SET///////////////////////////////////////





void computeFractalJ(SDL_Surface *scrn, ComplexPlane cp, int type, float cr, float ci);


int JuliaSet(void)
{


  // SDL_Surface *screen;
  // SDL_Event event;
   ComplexPlane cp = {-2.0, 2.0, -2.0, 2.0};
   int quit = 0;

   printf("My pid is %d, kill me!\n", getpid()); //used to kill the process

   if(SDL_Init(SDL_INIT_VIDEO) < 0)
   {
      fprintf(stderr, "SDL_Init(): %s\n", SDL_GetError());
      exit(1);
   }

   atexit(SDL_Quit);

   SDL_putenv("SDL_VIDEO_CENTERED=center");
   SDL_WM_SetCaption("Afracta: Julia Set. cr = -.8, ci = .156", NULL);
//   if(!(screen = SDL_SetVideoMode(640, 480, 8, SDL_RESIZABLE|SDL_SWSURFACE)))
   //if(!(screen = SDL_SetVideoMode(1280, 960, 8, SDL_SWSURFACE)))
   if(!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, 8, SDL_SWSURFACE)))
   {
      fprintf(stderr, "SDL_SetVideoMode(): %s\n", SDL_GetError());
      exit(1);
   }
    //screen = SDL_SetVideoMode(1024, 968, 32, SDL_SWSURFACE);

    menu = SDL_LoadBMP("/home/raichu/NetBeansProjects5/11.fractals/images/menu.bmp");
	SDL_Rect offset;
	offset.x = 0;
	offset.y = HEIGHT-200;
    SDL_BlitSurface(menu, NULL, screen, &offset);



   float cr=0, ci=-1, zoom;
   int end, rep, n;
 

	computeFractalJ(screen, cp, 0, cr, ci);
    SDL_BlitSurface(menu, NULL, screen, &offset);
        SDL_Flip(screen);
   SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );

   


}

void computeFractalJ(SDL_Surface *srfc, ComplexPlane cp, int type, float cr, float ci)
{
   ComplexNumber z_n, c, temp, c1;
   uint16_t w, h, n;
   uint8_t *buffer, *line, *pixel;

   //verify surface
 //  printf("Surface size %d x %d, depth %d \n", srfc -> w, srfc -> h, srfc -> format -> BytesPerPixel);


   SDL_LockSurface(srfc);

   /*c1.real = 0.285;
   c1.imm  = 0.01;*/
   /*c1.real = -0.835;
   c1.imm  = 0.232;*/
   /*c1.real = -0.8;
   c1.imm  = 0.156;*/
   c1.real = cr;
   c1.imm  = ci;

   buffer = (uint8_t *)srfc -> pixels;
   line = buffer;
   for(h = 0; h < srfc -> h; h++)
   {
      pixel = line;
      for(w = 0; w < srfc -> w; w++)
      {
         //conversion from discrete screen position to continous complex numbers in the plane
         c.real    = ((double)w * ((cp.xMax - cp.xMin) / (double)srfc -> w)) + cp.xMin;
         c.imm     = ((double)h * ((cp.yMax - cp.yMin) / (double)srfc -> h)) + cp.yMin;
         z_n = c;
         for(n = 0; n < 64; n++) //--??
         {
            if(((z_n.real * z_n.real) + (z_n.imm * z_n.imm)) > 4.0)//--determing the region inside the plane
            {
               switch(srfc -> format -> BytesPerPixel)//--coloration
               {
                  case 1:
                     *pixel = n;
                     break;
                  case 3://simple coloration - do not care aboit it
                     pixel[0] = n;
                     pixel[1] = (n * n) % 256;
                     pixel[2] = (n * n * n) % 256;
                     break;
                  default://--error check
                     fprintf(stderr, "Pixel depth not yet supported: %d\n4", srfc -> format -> BytesPerPixel);
                     exit(1);
                     break;
               }//switch
               break;
            }//if

            //else
           temp.real    = (z_n.real * z_n.real) - (z_n.imm * z_n.imm) + c1.real;
             //temp.real    = 1 - z_n.real + z_n.imm;
             //temp.imm     = z_n.imm * temp.real;
          temp.imm     = 2.0 * z_n.real * z_n.imm + c1.imm;
            z_n = temp;
            //SDL_UpdateRect(srfc, 0, 0, 1280, 960);
         }//for n
         
         pixel += srfc -> format -> BytesPerPixel;
      }//for w
      line += srfc -> pitch;
   }//for h
   
   SDL_UnlockSurface(srfc);
}//function




