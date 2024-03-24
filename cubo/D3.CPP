//d3.cpp
#include <math.h>
#include <fstream.h>
#include "d3.h"

istream &operator >> (istream &ff, vec3 &P)
	{
	return ff >> P.x >> P.y >> P.z;
	}

vec3 operator + (vec3 &u, vec3 &v)
	{
	return vec3 (u.x + v.x, u.y + v.y, u.z + v.z);
	}

vec3 operator - (vec3 &u, vec3 &v)
	{
	return vec3 (u.x - v.x, u.y - v.y, u.z - v.z);
	}

vec3 operator * (double c, vec3 &v)
	{
	return vec3 (c*v.x, c*v.y, c*v.z);
	}

vec3 &operator += (vec3 &u, vec3 &v)
	{
	u.x += v.x; u.y +=v.y; u.z+=v.z;
	return u;
	}

vec3 &operator-=(vec3 &u, vec3 &v)
	{
	u.x -= v.x; u.y -=v.y; u.z-=v.z;
	return u;
	}


vec3 &operator*=(vec3 &v, double c)
	{
	v.x *= c; v.y *= c; v.z*= c;
	return v;
	}

static double v11, v12, v13, v21, v22, v23, v32, v33, v43;

void coeff (double rho, double theta, double phi)
	{
	double costh, sinth, cosph, sinph;
	costh = cos(theta); sinth = sin(theta);
	cosph = cos(phi); sinph = sin(phi);
	v11=-sinth; v12= -cosph*costh; v13= -sinph*costh;
	v21= costh; v22= -cosph*sinth; v23= -sinph*sinth;
		    v32= sinph;        v33= -cosph;
				       v43= rho;

	}

void eyecoord (vec3 &pw, vec3 &pe)
	{
	pe.x = v11 * pw.x + v21 * pw.y;
	pe.y = v12 * pw.x + v22 * pw.y + v32 * pw.z;
	pe.z = v13 * pw.x + v23 * pw.y + v33 * pw.z + v43;
	}

void perspective (vec3 &p, float *px, float *py)
	{
	vec3 pe;
	eyecoord (p,pe);
	*px = pe.x/pe.z;
	*py = pe.y/pe.z;
	}

double dotproduct (vec3 &a, vec3 &b)
	{
	return a.x * b.x + a.y * b.y + a.z * b.z;
	}

double abs (vec3 &v)
	{
	return sqrt (v.x * v.x + v.y * v.y * v.z * v.z);
	}

vec3 crossproduct (vec3 &a, vec3 &b)
	{
	return vec3(a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x);
	}





























































