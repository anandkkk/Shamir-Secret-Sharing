package edu.biu.scapi.primitives.dlog;

/**
 * This class implements a field over Galois Field with 32 bit utilizing Crypto++'s implementation.
 * It uses JNI technology to call Crypto++'s native code.
 */

public interface Field {

	//Finite field is always of the type p^n

	// The prime order of the field
	public int getPrime();

	// Exponent of the field
	public int getExponent();

	// Order of the field would be p^n
	public int getOrder();
	
	//Field Type
	public String getFieldType();
	public int add(int element1, int element2) throws Exception;
	public int subtract(int element1, int element2) throws Exception;
	public int multiply(int element1, int element2) throws Exception;
	public int divide(int element1, int element2) throws Exception;
	public int additiveInverse(int element) throws Exception;
	public int multiplicativeInverse(int element) throws Exception;
	public int additiveIdentity() throws Exception;
	public int multiplicativeIdentity() throws Exception;
}
