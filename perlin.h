#ifndef PERLIN_H
#define PERLIN_H

#include <stdio.h>

double perlin(double x, double y, double z);

double fade(double t);

double lerp(double t, double a, double b);

double grad(int hash, double x, double y, double z);

#endif
