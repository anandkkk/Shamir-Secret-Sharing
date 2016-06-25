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


JNIEXPORT jintArray JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_PrepareBulkPolynomialInterpolation
  (JNIEnv * env, jobject, jlong ring, jintArray x, jint n)
{

	int xlen = (env)->GetArrayLength(x);
	int *xarray = (env)->GetIntArrayElements(x, 0);

	const jsize length = env->GetArrayLength(x);	
	jintArray w = env->NewIntArray(length);
	jint *warr = env->GetIntArrayElements(w, 0);

	for (int i=0; i<n; i++)
	{
		int t = ((GF2_32 *) ring)->MultiplicativeIdentity();
		for (int j=0; j<n; j++)
			if (i != j)
				t = ((GF2_32 *) ring)->Multiply(t, ((GF2_32 *) ring)->Subtract(xarray[i], xarray[j]));
		warr[i] = ((GF2_32 *) ring)->MultiplicativeInverse(t);
		printf("warr[%d]%d\n",i,warr[i]);
	}
	
	env->ReleaseIntArrayElements(w, warr, n);	

	return w;	
}
JNIEXPORT jintArray JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_PrepareBulkPolynomialInterpolationAt
  (JNIEnv * env, jobject, jlong ring, jint x_position, jintArray xarray, jintArray warray, jint n)
{

	const jsize length = n;	
	jintArray v = env->NewIntArray(length);
	jint *varr = env->GetIntArrayElements(v, 0);

	int xlen = (env)->GetArrayLength(xarray);
	int *x = (env)->GetIntArrayElements(xarray, 0);

	int wlen = (env)->GetArrayLength(warray);
	int *w = (env)->GetIntArrayElements(warray, 0);


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

	for (i=0; i<n; i++){
		varr[i] = ((GF2_32 *) ring)->Multiply(a[n-1+i], w[i]);
		printf("varr[%d]%d\n",i,varr[i]);
	}
	env->ReleaseIntArrayElements(v, varr, n);	

	return v;	

}

JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_Polynomial_BulkPolynomialInterpolateAt
  (JNIEnv * env, jobject, jlong ring, jintArray yarray, jintArray varray, jint n)
{

	int vlen = (env)->GetArrayLength(varray);
	int *v = (env)->GetIntArrayElements(varray, 0); 

	int ylen = (env)->GetArrayLength(yarray);
	int *y = (env)->GetIntArrayElements(yarray, 0);


	unsigned int result = ((GF2_32 *) ring)->Identity();

	for (int i=0; i<n; i++)
		((GF2_32 *) ring)->Accumulate(result, ((GF2_32 *) ring)->Multiply(y[i], v[i]));

	return result;
}


