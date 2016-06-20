package edu.biu.scapi.primitives.dlog;
import edu.biu.scapi.primitives.dlog.GF2m;

class Polynomial {

/*

x[], y[] are points arrays
n : # of points
x_position : x coordinate at which we want to find y

 */
	int x[],y[],w[],v[];
	int n,x_position;
	
	private native long createFieldGf();
	private native void PrepareBulkPolynomialInterpolation(CryptoPpDlogGF ring,int w[], int x[], unsigned int n);
	private native void PrepareBulkPolynomialInterpolationAt(CryptoPpDlogGF ring, int v[], int x_position, int x[], int w[], unsigned int n);
	private native int BulkPolynomialInterpolateAt(CryptoPpDlogGF ring,int y[], int v[], unsigned int n);
	

	static {
		System.loadLibrary("CryptoPPJavaInterface");
	}


	public int doInterpolation(int X[],int Y[], int N, int X_Position)
	{
		CryptoPpDlogGF ring = new CryptoPpDlogGF();
		
		n=N;
		x_position = X_Position;
		x=new int[n];		
		x=X;
		y=new int[n];		
		y=Y;
		w=new int[n];		
		v=new int[n];		

		PrepareBulkPolynomialInterpolation(ring,w,x,n);
		PrepareBulkPolynomialInterpolationAt(ring,v,x_position,x,w,n);
		return BulkPolynomialInterpolateAt(ring,y,v,n);
	}

}
