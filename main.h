#ifndef LOGIC
#define LOGIC

#define prec float


typedef struct body{
  prec vx;
  prec vy;
  prec fx;
  prec fy;
  prec px;
  prec py;
  prec mass;
} body;

void update(body* a, prec dt);

void resetForce(body* b);

void addForce(body* a, body* b);

prec newRand();

void init(int N, body* star);

void updateForces(int N, body* star);


#endif
