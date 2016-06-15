package edu.biu.scapi.primitives.dlog;
import edu.biu.scapi.primitives.dlog.GF2m;

/**
 * This class implements a field over Galois Field with 32 bit utilizing Crypto++'s implementation.
 * It uses JNI technology to call Crypto++'s native code.
 */

public class CryptoPpDlogGF implements GF2m {

	private long pointerToField = 0; // pointer to the native field for the GF 32 functionality */

	private native long createFieldGf();
	private native long createFieldGfWithModulus(int modulus);
	private native int add(long field,int element1, int element2);
	private native int multiply(long field,int element1, int element2);
	private native int multiplicativeInverse(long field,int element);
	private native int divide(long field,int element1, int element2);
	

	public CryptoPpDlogGF() {
		// Default Modulus - 0x0000008D => x^32 + x^7 + x^3 + x^2 + 1
		pointerToField = createFieldGf();
	}

	public CryptoPpDlogGF(int modulus) throws Exception {
		// Validate if modulus is irreducible
		// First Check is 1 must be present
		if(modulus%2==0){
			throw new Exception();
		}
		pointerToField = createFieldGfWithModulus(modulus);
	}
	
	public int getPrime(){
		//Galois Field of type 2^32 hence prime number used is 2
		return 2;	
	}
	
	public int getExponent(){
		//Current Implementation is for 32 bits
		return 32;	
	}
	
	public int getOrder(){
		return 32;
	}

	public int getIrreducibleModulus(){
		//Default Modulus
		return 139;
	}


	public String getFieldType(){
		return "Galois Field - GF(2^32)";
	}

	public int add(int element1, int element2) throws Exception{
			int result = add(pointerToField, element1, element2);	
			return result;
	}

	public int subtract(int element1, int element2) throws Exception{
			// Since Mod2 on polynomial addition is same as addition using the same function
			int result = add(pointerToField, element1, element2);	
			return result;
	}

	public int multiply(int element1, int element2) throws Exception{
			int result = multiply(pointerToField, element1, element2);	
			return result;
	}

	public int divide(int element1, int element2) throws Exception{
			int result = divide(pointerToField, element1, element2);	
			return result;
	}

	public int multiplicativeInverse(int element) throws Exception{
			int result = multiplicativeInverse(pointerToField, element);	
			return result;
	}

	public int additiveInverse(int element) throws Exception{
			return element;
	}

	public int additiveIdentity() throws Exception{	
			return 0;
	}
	
	public int multiplicativeIdentity() throws Exception{	
			return 1;
	}

// upload CryptoPP library
	static {
		System.loadLibrary("CryptoPPJavaInterface");
	}
	
}
