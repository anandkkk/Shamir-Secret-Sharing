package edu.biu.scapi.primitives.dlog;
import edu.biu.scapi.primitives.dlog.CryptoPpDlogGF;

public class Polynomial extends CryptoPpDlogGF{

	//private int x[],y[];
	//private int n,x_position;
	private native int[] PrepareBulkPolynomialInterpolation(long ring,int x[], int n);
	private native int[] PrepareBulkPolynomialInterpolationAt(long ring,int x_position,int x[],int w[],int n);
	private native int BulkPolynomialInterpolateAt(long ring,int y[],int v[],int n);
	

	static {
		System.loadLibrary("CryptoPPJavaInterface");
	}



	public Polynomial(){
		super();
	}

	public int doInterpolation(int x[],int y[], int n, int x_position)
	{
		
		System.out.println("In Interpolation");
	
		int[] w = PrepareBulkPolynomialInterpolation(pointerToField,x,n);
		for(int i=0;i<n;i++){
			System.out.println("w["+i+"] = "+w[i]);
		}
		int[] v = PrepareBulkPolynomialInterpolationAt(pointerToField,x_position,x,w,n);
		for(int i=0;i<n;i++){
			System.out.println("v["+i+"] = "+v[i]);
		}
		return BulkPolynomialInterpolateAt(pointerToField,y,v,n);
	}

}
