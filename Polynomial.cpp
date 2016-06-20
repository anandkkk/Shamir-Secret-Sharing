#include "StdAfx.h"

// cryptopp includes
#include "cryptlib.h"
#include "gfpcrypt.h"
#include "osrng.h"
#include "gf2_32.h"
// local includes
#include "CryptoPpDlogGF.h"
#include "Utils.h"

#include "pch.h"
#include "polynomi.h"
#include "secblock.h"

#include <sstream>
#include <iostream>


using namespace CryptoPP;

JNIEXPORT jlong JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_createFieldGf
  (JNIEnv *env, jobject){
	  	GF2_32* field = new GF2_32();
	  	return (jlong)field;
  }



JNIEXPORT void JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_PrepareBulkPolynomialInterpolation
(JNIEnv *env, jobject, jlong ring, jint w[], jint x[], jint n)
{
	for (jint i=0; i<n; i++)
	{
		jint t = ring.MultiplicativeIdentity();
		for (jint j=0; j<n; j++)
			if (i != j)
				t = ring.Multiply(t, ring.Subtract(x[i], x[j]));
		w[i] = ring.MultiplicativeInverse(t);
	}	
}

JNIEXPORT void JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_PrepareBulkPolynomialInterpolationAt
(JNIEnv *env, jobject, jlong ring, jint v[], jint x_position, jint x[], jint w[], jint n)
{
	jint a[2*n-1];
	jint i;

	for (i=0; i<n; i++)
		a[n-1+i] = ring.Subtract(x_position, x[i]);

	for (i=n-1; i>1; i--)
		a[i-1] = ring.Multiply(a[2*i], a[2*i-1]);

	a[0] = ring.MultiplicativeIdentity();

	for (i=0; i<n-1; i++)
	{
		std::swap(a[2*i+1], a[2*i+2]);
		a[2*i+1] = ring.Multiply(a[i], a[2*i+1]);
		a[2*i+2] = ring.Multiply(a[i], a[2*i+2]);
	}

	for (i=0; i<n; i++)
		v[i] = ring.Multiply(a[n-1+i], w[i]);
}

JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_BulkPolynomialInterpolateAt
(JNIEnv *env, jobject, jlong ring, jint y[], jint v[], jint n)
{
	jint result = ring.Identity();
	for (jint i=0; i<n; i++)
		ring.Accumulate(result, ring.Multiply(y[i], v[i]));
	return result;
}



