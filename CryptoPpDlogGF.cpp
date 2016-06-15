#include "StdAfx.h"

// cryptopp includes
#include "cryptlib.h"
#include "gfpcrypt.h"
#include "osrng.h"
#include "gf2_32.h"
// local includes
#include "CryptoPpDlogGF.h"
#include "Utils.h"

using namespace CryptoPP;

/* function createDlogZp : This function creates a Dlog group over Zp and returns a pointer to the created Dlog.
 * param p				 : field size (prime)
 * param q				 : order of the group
 * param g				 : generator of the group
 * return			     : A pointer to the created Dlog.
 */

 JNIEXPORT jlong JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_createFieldGf
  (JNIEnv *env, jobject){
	  	GF2_32* field = new GF2_32();
	  	return (jlong)field;
  }

JNIEXPORT jlong JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_createFieldGfWithModulus
  (JNIEnv *, jobject, jint modulus){
	  	GF2_32* field = new GF2_32((unsigned int)modulus);
	  	return (jlong)field;
  }

  JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_add
  (JNIEnv *env, jobject, jlong field, jint element1, jint element2){
	  	unsigned int gf1element = element1;
	  	unsigned int gf2element = element2;
  	return (jint)((GF2_32 *) field)->Add(gf1element,gf2element); 
  }

  JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_multiply
  (JNIEnv *, jobject, jlong field, jint element1, jint element2){
	  	unsigned int gf1element = element1;
	  	unsigned int gf2element = element2;
  	return (jint)((GF2_32 *) field)->Multiply(gf1element,gf2element); 
  }

  JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_multiplicativeInverse
  (JNIEnv *, jobject, jlong field, jint element){
  	  	unsigned int gfelement = element;
	return (jint)((GF2_32 *) field)->MultiplicativeInverse(gfelement); 	
  }

  JNIEXPORT jint JNICALL Java_edu_biu_scapi_primitives_dlog_CryptoPpDlogGF_divide
  (JNIEnv *, jobject, jlong field, jint element1, jint element2){
  	  	unsigned int gf1element = element1;
	  	unsigned int gf2element = element2;
  	return (jint)((GF2_32 *) field)->Divide(gf1element,gf2element);
  }