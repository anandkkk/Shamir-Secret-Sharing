import java.util.*;
import java.io.*;
class StringToAscii
{
static FileInputStream in = null;
static PrintWriter out = null;
static FileWriter fw=null;
static BufferedWriter bw=null;

	public static void main(String ar[]) throws IOException
	{
		
		
		String inputfile="input.txt";
		String outputfile = "output.txt";

		 try 
		 {
         		in = new FileInputStream(inputfile);
			fw = new FileWriter(outputfile, true);
			bw = new BufferedWriter(fw);
        		out = new PrintWriter(bw);

        		int counter=0; 
         		int c;
			String input="";
         		while ((c = in.read()) != -1) 
			{
				do
				{
					input+=Character.valueOf((char)c);
					counter++;
				}while(counter<8 && (c = in.read()) != -1);
				System.out.println("input read : "+input);
            			
				long secret=createSecretKeyFromFile(input);
	
				System.out.println("Key generated : "+secret);
				System.out.println("Secret Sharing...");
				System.out.println("Secret Recovered : "+secret);
			
				createFileFromSecretKey(secret);

				input="";
				counter=0;	
			
				System.out.println("--------------------*--*-------------------");			
				
			}

			
      		}
		finally 
		{
         		if (in != null) 
			{
        	    		in.close();
       		  	}
         		if (out != null)
			{
            			out.close();
         		}
      		}



		

		

		
		
		//System.out.println("input file matches output file : "+);
	}

	static long createSecretKeyFromFile(String input)
	{
		ArrayList<String> bin_arr = convertStringToBinary(input);
		System.out.println("String to binary : "+bin_arr);		

		long decimal = convertBinaryToDecimal(bin_arr);
		System.out.println("Binary to decimal : "+decimal);

		return decimal;
	}

	static void createFileFromSecretKey(long decimal)
	{
		ArrayList<String> bin_arr = convertDecimalToBinary(decimal);
		System.out.println("Decimal to binary : "+bin_arr);

		String output = convertBinaryToString(bin_arr);
		System.out.println("Binary to String : "+output);
	
		out.print(output);
			
	}

	static ArrayList<String> convertStringToBinary(String input)
	{
		byte[] bytes = input.getBytes();
		StringBuilder binary = new StringBuilder();
		ArrayList<String> bin_arr = new ArrayList<String>();
	
		 for (byte b : bytes)
		 {
		     int val = b;
		     for (int i = 0; i < 8; i++)
		     {
			binary.append((val & 128) == 0 ? 0 : 1);
			val <<= 1;
		     }
		     bin_arr.add(binary.toString());
		     binary.setLength(0);	
		 }
		 return bin_arr;
	}

	static long convertBinaryToDecimal(ArrayList<String> bin_arr)
	{
		String binary="";	
		for(String s : bin_arr)
		 	binary+=s;
		return (Long.parseLong(binary.toString(),2));
	}


	static ArrayList<String> convertDecimalToBinary(long decimal)
	{
		String binary = Long.toBinaryString(decimal);

		int counter=0;
		String temp="",rev;
		ArrayList<String> bin_arr = new ArrayList<String>();
		int i=binary.length()-1;
		while(i>=0)
		{
			do
			{
				temp+=binary.charAt(i);
				counter++;
				i--;
			}while(counter<8 && i>=0);

			rev=reverse(temp);
			bin_arr.add(rev);
			temp="";
			counter=0;
		}
		Collections.reverse(bin_arr);
		return bin_arr;
	}


	static String convertBinaryToString(ArrayList<String> bin_arr)
	{
		String output="";
		for(String s : bin_arr)
		{
			int temp = Integer.parseInt(s,2);
			output+=Character.toString((char)temp);
		}
		return output;
	}

	static String reverse(String input)
	{
		String output="";
		for(int i=input.length()-1;i>=0;i--)
			output+=input.charAt(i);
		return output;
	}
}



