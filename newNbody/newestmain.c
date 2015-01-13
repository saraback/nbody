
/**
 * @file main.c
 * @brief Main and only file for Nbody 
 *
 * @author Linnea Dahl 
 * @author Sara Back 
 *  
 * @bug No known bugs
 * 
 */ 



#include <math.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "main.h"


#ifdef ANIMATE
#include <X11/Xlib.h>
#include <X11/Xutil.h>



#define X_SIZE 800
#define Y_SIZE 800
#endif


static prec gdt = 0.0001;


/*
typedef struct body {
  prec vx;
  prec vy;
  prec fx;
  prec fy;
  prec px;
  prec py;
  prec mass;
} body;
*/


void update(body* a, prec dt)
{
 prec accX = a->fx / a->mass;
 prec accY = a->fy / a->mass;

 a->vx += accX * dt;
 a->vy += accY * dt;

 a->px += a->vx * dt + ((accX * dt * dt)/2); 
 a->py += a->vy * dt + ((accY * dt * dt)/2);  
}

 void resetForce(body* b) 
{
  b->fx = 0.0;
  b->fy = 0.0;
}


 void addForce(body* a, body* b)
{

  prec delta_x = b->px - a->px;
  prec delta_y = b->py - a->px;
  prec distance = (( delta_x * delta_x) + (delta_y * delta_y));
  prec force = (a->mass * b->mass)/ (distance * distance);

  a->fx += force * delta_x;
  a->fy += force * delta_y;
  
}

prec newRand() 
{//srand(time(0));
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}




void init(int N, body* star) //gives all stars their starting values
{ 
  for ( int k=0; k<N; k++){
     star[k].vx = newRand() * 300 - 150;
  star[k].vy = newRand() * 300 - 150;
  star[k].px = newRand() * 250 + 250;
  star[k].py = newRand() * 250 + 250;
  star[k].mass = newRand() * 500;
  }
}

 void updateForces(int N, body* star)
{
  for (int i = 0; i < N; i++) {
    resetForce( &star[i] );
        
    for (int j = 0; j < N; j++)
      {
        if (&star[i] != &star[j]) {
          addForce(&star[i], &star[j]);
        }        
      }
    update(&star[i], gdt);  
  } 
}

// Manually copy coordinates from stars into points (to be drawn).
// Look at the manual file for XPoint to see which 
// format XPoint accepts its coordinates in.
#ifdef ANIMATE
void copyToXBuffer(body* star, XPoint* points, int N)
{for (int i = 0; i < N; i++){
    points[i].x = star[i].px;
    points[i].y = star[i].py;
  }
}
#endif

/**
 * @brief The main function 
 */

/*
int main(int argc, char* argv[]) {

  int N = 200;
  int iter = 1000;

  if(argc == 3 && isdigit(atoi(argv[1])) && isdigit(atoi(argv[2])))
    {
      N = atoi(argv[1]);
      iter = atoi(argv[2]);
    }
  
  struct body* star = malloc(sizeof(body) * N);

   init( N, star);
  

  

#ifdef ANIMATE
  XPoint* points = malloc(sizeof(XPoint)*N);
  Display* disp;
  Window window, rootwin;
  int screen;

  disp = XOpenDisplay(NULL);
  screen = DefaultScreen(disp);
  rootwin = RootWindow(disp,screen);
  window = XCreateSimpleWindow(disp,rootwin,
                               0,0,X_SIZE,Y_SIZE,1,0,0);
  GC gc = XCreateGC(disp, window, 0, 0);
  XSetForeground(disp, gc, WhitePixel(disp, screen));
  XSetBackground(disp, gc, BlackPixel(disp, screen));
  XMapWindow(disp,window);

  XClearWindow(disp,window);	
	
  copyToXBuffer(star, points, N);
  XDrawPoints(disp, window, gc, points, N, 0);

  XFlush(disp);

#endif

  clock_t start = clock();
  for(int i = 0; i < iter; i++)
    { 
      updateForces(N, star);

#ifdef ANIMATE
      copyToXBuffer(star, points, N);
      XDrawPoints(disp, window, gc, points, N, CoordModeOrigin);
      XClearWindow(disp,window);	
#endif
    }
  free(star); 
  clock_t stop = clock();
  float diff = (float)(stop - start)/CLOCKS_PER_SEC;
  printf("Total: %lf seconds\n",diff);
  printf("Bodies: %d\n",N);
  printf("Iterations: %d\n", iter);

#ifdef ANIMATE
  XCloseDisplay(disp);
#endif

  return 0;
}
*/
