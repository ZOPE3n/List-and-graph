 /**
  *Mengdi Wei
  *ID 1538074
  *PA3
  *This is sparse, which could gernerate the resules of the whole program
  *
  **/

import java.util.*;
import java.io.*;

class Sparse{
   public static void main (String[] args) throws Exception {
  
	    	int m =0;
	    	int j= 0;
	    	int n=0;
	       Scanner in = new Scanner(new FileInputStream(args[0]));
	       
	      PrintWriter out = new PrintWriter (args[1]);
	       if (args.length!=2) {
	       	System.out.println("Usage:FileIO infile outfile ");
	     	  System.exit(1);
	      }
	      
        String first = in.nextLine();
          first.trim();
          String[] str = first.split(" ");
            m=Integer.parseInt(str[0]);
            j=Integer.parseInt(str[1]);
            n=Integer.parseInt(str[2]);
        
          int count=0;
          Matrix A = new Matrix (m);
          Matrix B = new Matrix (m);
          double x =0;
          int l =0;
         while (in.hasNextLine()) {
         	    	   count++;
     
        
         	  m=in.nextInt();
         	  l=in.nextInt();
         	  x=in.nextDouble();
      
          if(count<=j) {
         	   	A.changeEntry(m,l,x);
         	   
         	   } else {
         	   	B.changeEntry(m,l,x);
         	 }
         	 String line=  in.nextLine();
         }
         print(A,B,out);
          in.close();
         out.close();//close the scanner and printwriter
	    }
	    //this method could print all results
	    static void print (Matrix A, Matrix B, PrintWriter out) {
	      	out.print("A has "+ A.getNNZ()+" ");
	        out.println("non-zero entries: ");
	      	out.println(A);
	      	
	        out.print("B has "+ B.getNNZ()+" ");
	        out.println("non-zero entries: ");
	      	out.println(B);
	      	
	      	out.println("(1.5)*A = ");
	       out.println( A.scalarMult(1.5));
	        
	        out.println("A+B = ");
	       out.println( A.add(B));
	        
	        out.println("A+A = ");
	         out.println( A.add(A));
	        
	        out.println("B-A = ");
	        out.println( B.sub(A));
	        
	        out.println("A-A = ");
	        out.println( A.sub(A));
	        
	       out.println("Transpose(A) = ");
	        out.println( A.transpose());
	        
	       out.println("A*B = ");
	       out.println( A.mult(B));
	        
	       out.println("B*B = ");
	        out.println( B.mult(B));
	        out.close();
	      }
	
}