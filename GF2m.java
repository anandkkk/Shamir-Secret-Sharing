package edu.biu.scapi.primitives.dlog;

/**
 * This class implements a field over Galois Field with 32 bit utilizing Crypto++'s implementation.
 * It uses JNI technology to call Crypto++'s native code.
 */

public interface GF2m extends GF{
	public int getIrreducibleModulus();
}
