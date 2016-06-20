#include "StdAfx.h"

// cryptopp includes
#include "cryptlib.h"
#include "gfpcrypt.h"
#include "osrng.h"
#include "gf2_32.h"
// local includes
#include "Polynomial.h"
#include "Utils.h"

#include "pch.h"
#include "polynomi.h"
#include "secblock.h"

#include <sstream>
#include <iostream>


using namespace CryptoPP;


JNIEXPORT void JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_PrepareBulkPolynomialInterpolation
(JNIEnv *env, jobject, jlong ring, jint w[], jint x[], jint n)
{
	for (jint i=0; i<n; i++)
	{
		jint t = ((GF2_32 *) ring)->MultiplicativeIdentity();
		for (jint j=0; j<n; j++)
			if (i != j)
				t = ((GF2_32 *) ring)->Multiply(t, ((GF2_32 *) ring)->Subtract(x[i], x[j]));
		w[i] = ((GF2_32 *) ring)->MultiplicativeInverse(t);
	}	
}

JNIEXPORT void JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_PrepareBulkPolynomialInterpolationAt
(JNIEnv *env, jobject, jlong ring, jint v[], jint x_position, jint x[], jint w[], jint n)
{
	unsigned int a[2*n-1];
	unsigned int i;

	for (i=0; i<n; i++)
		a[n-1+i] = ((GF2_32 *) ring)->Subtract(x_position, x[i]);

	for (i=n-1; i>1; i--)
		a[i-1] = ((GF2_32 *) ring)->Multiply(a[2*i], a[2*i-1]);

	a[0] = ((GF2_32 *) ring)->MultiplicativeIdentity();

	for (i=0; i<n-1; i++)
	{
		std::swap(a[2*i+1], a[2*i+2]);
		a[2*i+1] = ((GF2_32 *) ring)->Multiply(a[i], a[2*i+1]);
		a[2*i+2] = ((GF2_32 *) ring)->Multiply(a[i], a[2*i+2]);
	}

	for (i=0; i<n; i++)
		v[i] = ((GF2_32 *) ring)->Multiply(a[n-1+i], w[i]);
}

JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_BulkPolynomialInterpolateAt
(JNIEnv *env, jobject, jlong ring, jint y[], jint v[], jint n)
{
	unsigned int result = ((GF2_32 *) ring)->Identity();

	for (int i=0; i<n; i++)
		((GF2_32 *) ring)->Accumulate(result, ((GF2_32 *) ring)->Multiply(y[i], v[i]));

	return result;
}



