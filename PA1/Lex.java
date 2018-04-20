/** Mengdi Wei
  * Id: 1538074
  * This is Lex.java which deal with the input
  * output and the insertionsort method
  */

import java.util.*;
import java.io.*;

public class Lex{
	
	 String[] strs;
	 List list = new List();
	 
	public static void main(String args[]) throws Exception {
	   Lex exe=new Lex();
	   exe.Exe(args);
	 }
	  
	   void Exe (String args[]) throws Exception {
	  
	     String str;
	     int count = 0;
	     if (args.length!=2) {
	     	System.out.println("Usage:FileIO infile outfile ");
	     	System.exit(1);
	     }
	     Scanner scan = new Scanner(new FileInputStream(args[0]));
	     Scanner in = new Scanner(new FileInputStream(args[0]));
	     FileWriter out = new FileWriter (args[1]);
	     strs = new String[numbers(count,scan)];
	     int i =0;
	      while(in.hasNextLine()) {
	      	str=in.nextLine();
	      	strs[i]=str;
	        i++;
	      }
	      sort(list);
	     while (list.front!=null) {
	     	 out.write(strs[list.front()]);
	     	 out.write("\n");
	     	 list.front=list.front.next;
	     }
	     in.close();
	     scan.close();
	     out.close();
	   }
	   
	   //sort method can use insertion sort to make the lexicographic oder for the elements in the list 
	   void sort(List list) {
	  	 // System.out.println();
        int n = strs.length;
        list.append(0);
        String key;
        for (int i=1; i<n; i++) {
        	  
            key = strs[i];
            if (key.compareTo(strs[list.back()])>0) { 	
            	  list.append(i);
            	  continue;
            	  
            }  if (key.compareTo(strs[list.front()])<0) {
             	  list.prepend(i);
             	  continue;
             } 
             list.moveFront(); 
            while (list.index()!=-1 ) {
            	 if (key.compareTo(strs[list.get()])<0) {
            	 list.insertBefore(i);
            	 break;
            	} else {
            	list.moveNext();
             }
            }
            
           
        }
    }

    //numbers method can count how many lines in this file
	  int numbers (int count, Scanner scan) {
	  	while(scan.hasNextLine()) {
	  		 count++;
	  		// System.out.println(count);
	  		 String str = scan.nextLine();
	  	}
	  	return count;
	  }
	}

