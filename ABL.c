/*****************************************************************************
Concatenated UDFs for Atmospheric Boundary Layer PN-EN-1991-1-4:2008 profiles
******************************************************************************/
#include "udf.h"
/* #include "math.h" */

/* stale  */
#define CMU 0.09			/* Stala Cmu - z modelu turbulencji k-epsilon */
#define ZMIN 10.0			/* IV kategoria terenu wg PN-EN-1991-1-4:2008 */
#define ZMAX 500.0			/* IV kategoria terenu wg PN-EN-1991-1-4:2008 */
#define Z0 1.0				/* IV kategoria terenu wg PN-EN-1991-1-4:2008 */
#define ZREF 10.0			/* Wysokosc refencyjna */
#define ALFA 0.24			/* IV kategoria terenu wg PN-EN-1991-1-4:2008 */
#define VREF 4.0			/* Predkosc referencyjna na z = 10m */
#define CO 1.0				/* Wspolczynnik orografii - przyjeto 1.0 */
#define CSEASON 1.0			/* Wspolczynnik sezonowy - przyjeto 1.0 */
#define CDIR 1.0			/* Wspolczynnik kierunkowy */
#define XCHAR 15.0			/* Wymiar charakterystyczny budynku */
#define VISC 1.7894e-05			/* Lepkosc molekularna m^2/s */

/*  profile for x-velocity  */

DEFINE_PROFILE(x_velocity,thread,index)
{
 	real z;					/* wysokosc nad powierzchnia ziemi */
	real Vfree;				/* predkosc bazowa po wspolczynnikach korekcyjnych */
	real x[ND_ND];				/* wektor wspolrzednych [x,y,z] */
 	face_t f;				/* face thread */

	Vfree = CO*CSEASON*CDIR*VREF;

	begin_f_loop(f,thread)
    	{
      		F_CENTROID(x,f,thread);
      		z = x[2];

      		if (z <= ZMAX)
		{
         		F_PROFILE(f,thread,index) = Vfree*pow(z/ZREF,ALFA);
		}
      		else
         		F_PROFILE(f,thread,index) = Vfree*pow(ZMAX/ZREF,ALFA);
    	}
	end_f_loop(f,t)
}

/*  profile for turbulent kinetic energy (TKE) - k PER BLOCKEN */

DEFINE_PROFILE(k_profile,thread,index)
{
 	real z;					/* wysokosc nad powierzchnia ziemi */
	real Vfree;				/* predkosc bazowa po wspolczynnikach korekcyjnych */
	real x[ND_ND];				/* wektor wspolrzednych [x,y,z] */
 	face_t f;				/* face thread */

	Vfree = CO*CSEASON*CDIR*VREF;

	begin_f_loop(f,thread)
    	{
      		F_CENTROID(x,f,thread);
      		z = x[2];

      		if (z <= ZMAX)
		{
			if (z <= ZMIN)
				F_PROFILE(f,thread,index) = 1.0*pow(Vfree*1.0/log(ZMIN/Z0),2.0);
			else
         			F_PROFILE(f,thread,index) = 1.0*pow(Vfree*pow(z/ZREF,ALFA)*1.0/log(z/Z0),2.0);
		}
      		else
         		F_PROFILE(f,thread,index) = 1.0*pow(Vfree*pow(ZMAX/ZREF,ALFA)*1.0/log(ZMAX/Z0),2.0);
    	}
	end_f_loop(f,t)
}

/* profile for specific dissipation rate - epsilon PER BLOCKEN */

DEFINE_PROFILE(epsilon_profile,thread,index)
{
 	real z;					/* wysokosc nad powierzchnia ziemi */
	real Vfree;				/* predkosc bazowa po wspolczynnikach korekcyjnych */
	real kmin,k,kmax;			/* wartosci TKE */
	real lscale;				/* skala dlugosci turbulencji, przyjeto 10% XCHAR */
	real x[ND_ND];				/* wektor wspolrzednych [x,y,z] */
 	face_t f;				/* face thread */

	Vfree = CO*CSEASON*CDIR*VREF;
	kmin = 1.0*pow(Vfree*1.0/log(ZMIN/Z0),2.0);
	kmax = 1.0*pow(Vfree*pow(ZMAX/ZREF,ALFA)*1.0/log(ZMAX/Z0),2.0);
	lscale = 0.1*XCHAR;

	begin_f_loop(f,thread)
    	{
      		F_CENTROID(x,f,thread);
      		z = x[2];

      		if (z <= ZMAX)
		{
			if (z <= ZMIN)

				F_PROFILE(f,thread,index) = pow(CMU,0.5)*kmin*(ALFA*1/ZREF*VREF);
			else
         			F_PROFILE(f,thread,index) = pow(CMU,0.5)*kmin*(ALFA*1/ZREF*VREF*pow(z/ZREF,ALFA-1.0));
		}
      		else
			F_PROFILE(f,thread,index) = pow(CMU,0.5)*kmax*(ALFA*1/ZREF*VREF*pow(ZMAX/ZREF,ALFA-1.0));
    	}
	end_f_loop(f,t)
}