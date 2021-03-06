#include <stdlib.h>
#include <math.h>

/**
 * @brief Another name for flaot
 */
#define prec float

/**
 * @brief Just an abbreviation
 */
#define PI 3.14159265359

prec gdt = 0.0001;
/**
 * @brief All the needed values for a star
 */
typedef struct body {
  prec vx;
  prec vy;
  prec fx;
  prec fy;
  prec px;
  prec py;
  prec mass;
} body;

/**
 * @brief updates a star 
 *
 * Updates the acceleration, the force and the position of a star. 
 *  
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

/**
 * @brief resets the force of a star
 *
 * Needed to not continously adding all forces 
 */
void resetForce(body* b) 
{
  b->fx = 0.0;
  b->fy = 0.0;
}

/**
 * @brief AddForce adds two stars together.
 * 
 * By multiplying the force and delta x and delta y the new force of the star is calculated. 
 */
void addForce(body* a, body* b)
{

  prec delta_x = b->px - a->px;
  prec delta_y = b->py - a->px;
  prec distance = sqrt(( delta_x * delta_x) + (delta_y * delta_y));
  prec force = (a->mass * b->mass)/ (distance * distance);

  a->fx += force * delta_x;
  a->fy += force * delta_y;
  
}
/**
 * @brief Returns a random number
 *
 */
prec newRand() 
{//srand(time(0));
  prec r = (prec)((double)rand()/(double)RAND_MAX);
  return r;
}



/**
 * @brief Initializes the stars.
 *
 * Initializes the velocity, point X, point Y and the mass of the stars by a random function. 
 */
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

/**
 * @brief updateForces updates the forces of all the stars. 
 */
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

