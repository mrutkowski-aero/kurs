/*****************************************************************************
Concatenated UDFs for Atmospheric Boundary Layer PN-EN-1991-1-4:2008 profiles
******************************************************************************/
#include "udf.h"
/* #include "math.h" */

/* Define roughness constant - Cs  */
DEFINE_PROFILE(roughness_constant_Cs,thread,index)
{
	real x[ND_ND];				/* wektor wspolrzednych [x,y,z] */
 	face_t f;				/* face thread */
	real ex;
	real y;
 	real z;					/* wysokosc nad powierzchnia ziemi */

	begin_f_loop(f,thread)
	{
		F_CENTROID(x,f,thread);
		ex = x[0];
		y = x[1];
		z = x[2];
		if((fabs(x[0]) < 180.0) && (fabs(x[1]) < 180.0))
			F_PROFILE(f,thread,index) = 15.3; // wewnatrz osiedla ks
		else
			F_PROFILE(f,thread,index) = 61.2; // na zewnatrz osiedla
	}
	end_f_loop(f,thread)
}