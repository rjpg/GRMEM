//d3.h
#include "fstream.h"
struct vec3
	{
	float x, y, z;
	vec3(double xx, double yy, double zz)
		{
		x=xx;y=yy;z=zz;
		}
	vec3 ()
		{
		x=0;
		y=0;
		z=0;
		}
	};

istream &operator >>(istream &ff, vec3 &p);

vec3 operator + (vec3 &u, vec3 &v);
vec3 operator - (vec3 &u, vec3 &v);
vec3 operator * (double c, vec3 &v);

vec3 &operator +=(vec3 &u, vec3 &v);
vec3 &operator -=(vec3 &u, vec3 &v);
vec3 &operator *=(vec3 &u, double c);

void coeff (double rho, double theta, double phi);
void eyecoord (vec3 &pw, vec3 &pe);
void perspective (vec3 &a, float *px, float *py);

double dotproduct (vec3 &a, vec3 &b);
double abs (vec3 &v);
vec3 crossproduct (vec3 &a, vec3 &b);




