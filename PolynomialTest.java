import edu.biu.scapi.primitives.dlog.*;
import java.util.*;

class PolynomialTest{
	public static void main(String args[]) throws Exception{
		Polynomial object = new Polynomial();
		int x[] = {1,2,3,4,5};
		int y[] = {6,2,4,1,3};
		int n=x.length;
		int x_position =13;
		System.out.println(object.doInterpolation(x,y,n,x_position));
		 
}
}
