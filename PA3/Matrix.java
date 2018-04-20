
/*Mengdi Wei
 *ID:1538074
 *PA3
 *This is the matrix library for the program, which contains methods to caculate matrix.
 */
import java.util.*;
import java.io.*;

class Matrix {
	 private int sum;
	 private int nzz;
	  List[] arr;
	  //Enty class
	 private class Entry {
	 	   int number;
	 	   double value;
	 	    Entry () {}
	 	    Entry (int number, double value) {
	 	    	this.number=number;
	 	    	this.value=value;
	 	    }
	 	    public String toString(){
			return ("("+number + ", " + value + ") " );
			}
	 }
	 //Matrix constuctor
	 Matrix(int n) {
	 	if ( (n<1) ) {
			throw new RuntimeException("Matrix Error: Matrix() called on invalid Matrix size");
		}
	 	  arr=new List[n];
	 	  sum=n;
	 	  nzz=0;
	 	  arr=new List[n+1];
	 	 for (int i =1; i<=sum; i++) {
	 	 	  arr[i] = new List();
	 	 }
	 }
	  //method to get size of matrix
	  int getSize() {
	  	return this.sum;
	  }
	  //get numbers of number of matrix
	  int getNNZ() {
	  	return this.nzz;
	  }
	  //determine if two matrix equals
	  public boolean equals(Object x) {
	      if (x == null) {
            return false;
        }
        Matrix M = (Matrix) x;
        if (M.size != size) {
            return false;
        }
        for (int i = 1; i <= size; i++) {
            List l1 = M.row[i];
            List l2 = row[i];

            if (l1.length() != l2.length()) {
                return false;
            }
            l1.moveFront();
            l2.moveFront();
            while (l1.cursor!=null){

                Entry e1 = (Entry) l1.get();
                Entry e2 = (Entry) l2.get();
                if (e1.col!=e2.col&&e1.value!=e2.value) {
                    return false;
                }
                l1.moveNext();
                l2.moveNext();

            }
        }

        return true;
}
	  //change entriese in a matrix
	 	void changeEntry(int i, int j, double x){
       
		if(i<1||i>getSize()||j<1||j>getSize()){
			return;
		}
		List matrix = arr[i];
		Entry entry = new Entry(j,x);
		if(matrix.front()==null){
			if(x==0)
				return;
			matrix.prepend(entry);
			nzz++;
			return;
		}
		
		Entry a = new Entry();
		matrix.moveFront();
		for(int m=1;m<=j;m++){
			if(matrix.get()==null){
				break;
			}
			a =(Entry)matrix.get();
			if(a.number>=j){
				break;
			}
			matrix.moveNext();
		}
		int val;
		if(matrix.get()==null){
			val = -1;
		}else{
			a = (Entry)matrix.get();
			val = a.number;
		}
		
		
		if(val==j){
			if(x==0){
				 matrix.delete();
				nzz--;
			}
			else{
		      a.value=entry.value;
			}
		}else{
			
			if(x==0){
				return;
			}else{
				if(val==-1){
					matrix.append(entry);
					nzz++;
				}else{
					matrix.insertBefore(entry);
					nzz++;
				}
			}
		}
	}

	  //scalar multplication for a matrix
	  Matrix scalarMult(double x) {
	  	Matrix M = new Matrix(sum);
	  	M.nzz=this.nzz;
	  	for (int i=1; i<=sum;i++) {
	  		if (arr[i].length()==0) {
	  			continue;
	  		} else {
	  			 arr[i].moveFront();
	  			 while(arr[i].index()>=0) {
	  		  	Entry ent = (Entry)arr[i].get();
	  			 Entry enty = new Entry(ent.number,ent.value*x);
	  			 M.arr[i].append(enty);

	  			 arr[i].moveNext();
	  			}
	  		}
	  	}
	  
	  	return M;
	  }
	  	  void makeZero() {
	  		for (int i=1;i<getSize();i++) {
	  			List list=arr[i];
	  			list.clear();
	  		}
	  		this.nzz=0;
	  }
	  Matrix copy() {
	  		
	  	Matrix M = new Matrix(sum);
	  	M.nzz=getNNZ();
	  	for (int i=1;i<=getSize();i++) {
	  		
	  		arr[i].moveFront();
	  		
	     while(arr[i].index() >= 0){
	     	Entry ent = (Entry)arr[i].get();
	     
	     	Entry entry = new Entry(ent.number,ent.value );
	     	M.arr[i].append(entry);
	     	arr[i].moveNext();
	  	}
	  }
	  return M;
	}
  //add two matrix
    Matrix add(Matrix M) {
    	 Matrix matrix = new Matrix(sum);
    	 	if(M.equals(this)) {
    	 		matrix=scalarMult(2.0);
    	 		return matrix;
    	 	}
    	for (int i=1; i<=sum;i++) {
    		List matrix1=this.arr[i];
    		List matrix2=M.arr[i];
    		List matrix3=matrix.arr[i];

    		    	 	matrix1.moveFront();
    		    	 	matrix2.moveFront();
    		    	 	  
    		    	 	while (matrix1.index()!=-1||matrix2.index()!=-1) {
    		    	 	
    		    	 		
    		    	 		Entry m1= (Entry)matrix1.get();
    		           Entry m2 =(Entry)matrix2.get();
    		           	if (matrix1.index()!=-1&&matrix2.index()!=-1) {
    		    	 		if (m1.number==m2.number) {
    		    	    
    		    	 		 	Entry ent = new Entry(m1.number,m1.value+m2.value);
    		    	 		 	 	 matrix.changeEntry(i,m1.number,ent.value);
    		    	 		 	matrix1.moveNext();
    		    	 		 	matrix2.moveNext();
    		    	 		
    		    	 	} else if (m1.number>m2.number) {

    		    	 		 Entry ent = new Entry(m2.number,m2.value);
    		    	 		 	 	 matrix.changeEntry(i,m2.number,ent.value);
    		    	 		 matrix2.moveNext();
    		    	 	} else if (m1.number<m2.number) {
   
    		    	 		 Entry ent = new Entry(m1.number,m1.value);
    		    	 		 	 	 matrix.changeEntry(i,m1.number,ent.value);
    		    	 		 matrix1.moveNext();
    		    	 	}
    		    	 } else if (matrix1.index()==-1&&matrix2.index()!=-1) {
    		    	 	   
    		    	 		 	Entry ent = new Entry(m2.number,m2.value);
    		    	 		 	 	 matrix.changeEntry(i,m2.number,ent.value);
    		    	 		 	 	 matrix1.moveNext();
    		    	 		 	   matrix2.moveNext();
    		    	} else if (matrix1.index()!=-1&&matrix2.index()==-1) {
    		    	 	   
    		    	 		 	Entry ent = new Entry(m1.number,m1.value);
    		    	 		 	 	 matrix.changeEntry(i,m1.number,ent.value);
    		    	 		 	 	 matrix1.moveNext();
    		    	 		 	   matrix2.moveNext();
    		    	}
    		 	 }
    	 
    }
     return matrix;
  }
    
    //transpose a matrix
    Matrix transpose() {
        Matrix M = new Matrix(sum);
        for (int i = 1; i <= sum; i++) {
            arr[i].moveFront();
            while (arr[i].index() >= 0) {
                Entry ent = (Entry) arr[i].get();
                M.changeEntry(ent.number, i, ent.value);
                 arr[i].moveNext();
            }
        }
        return M;
    }
      
      //subatract two matrix
    	 Matrix sub(Matrix M) {
    	 Matrix matrix = new Matrix(sum);
    	 	if(M.equals(this)) {
    	 		return matrix;
    	 	}
    	for (int i=1; i<=sum;i++) {
    		List matrix1=this.arr[i];
    		List matrix2=M.arr[i];
    		List matrix3=matrix.arr[i];

    		    	 	matrix1.moveFront();
    		    	 	matrix2.moveFront();
    		    	 	  
    		    	 	while (matrix1.index()!=-1||matrix2.index()!=-1) {
    		    	 	    		    	 		
    		    	 		Entry m1= (Entry)matrix1.get();
    		           Entry m2 =(Entry)matrix2.get();
    		           	if (matrix1.index()!=-1&&matrix2.index()!=-1) {
    		    	 		if (m1.number==m2.number) {
    		    	    
    		    	 		 	Entry ent = new Entry(m1.number,m1.value-m2.value);
    		    	 		 	 	 matrix.changeEntry(i,m1.number,ent.value);
    		    	 		 	matrix1.moveNext();
    		    	 		 	matrix2.moveNext();
    		    	 		
    		    	 	} else if (m1.number>m2.number) {

    		    	 		 Entry ent = new Entry(m2.number,m2.value*-1);
    		    	 		 	matrix.changeEntry(i,m2.number,ent.value);
    		    	 		 matrix2.moveNext();
    		    	 	} else if (m1.number<m2.number) {
   
    		    	 		 Entry ent = new Entry(m1.number,m1.value);
    		    	 		 	 	 matrix.changeEntry(i,m1.number,ent.value);
    		    	 		 matrix1.moveNext();
    		    	 	}
    		    	 } else if (matrix1.index()==-1&&matrix2.index()!=-1) {
    		    	 	   
    		    	 		 	Entry ent = new Entry(m2.number,m2.value);
    		   
    		    	 		 	 	 matrix.changeEntry(i,m2.number,ent.value*-1);
    		    	 		 	 	 matrix1.moveNext();
    		    	 		 	   matrix2.moveNext();
    		    	} else if (matrix1.index()!=-1&&matrix2.index()==-1) {
    		    	 	   
    		    	 		 	Entry ent = new Entry(m1.number,m1.value);
    		    	 		 	 	 matrix.changeEntry(i,m1.number,ent.value);
    		    	 		 	 	 matrix1.moveNext();
    		    	 		 	   matrix2.moveNext();
    		    	}
    		 	 }
    	 
    }
     return matrix;
  }
    //multplite two matrix
    Matrix mult(Matrix M) {
          
    	   	Matrix matrix = new Matrix(sum);
    	   	M=M.transpose();

    	   	Entry m1 = new Entry();
    	   	Entry m2 = new Entry();
    	   	
    	    for (int i=1; i<=sum;i++) {
    	    List	matrix1=this.arr[i];
    	   	List matrix3=matrix.arr[i];
    	   
    	   	Entry ent = new Entry();
    	   	
    		    	 if (matrix1.length() == 0) 
    		    	    continue; 
    		    for(int j = 1; j<=getSize(); j++) {	 	
    		    	  List matrix2=M.arr[j];
    		    	   	matrix2.moveFront();
    		    	   	matrix1.moveFront();
    		    	       if (matrix2.length() == 0)
    		                 continue;
    		             double x =0;
    		    	 	while (matrix1.index()>=0&&matrix2.index()>=0) {
    		    	 		  	 m1= (Entry)matrix1.get();
    		               m2 =(Entry)matrix2.get();
    		          
    		    	 		if (m1.number==m2.number) {
   
    		    	 		x = x+m1.value*m2.value;

    
    		    	 		 	matrix1.moveNext();
    		    	 		 	matrix2.moveNext();
    		    	 		 
    		            continue;
    		    	 	} else if (m1.number>m2.number) {
    		             matrix2.moveNext();
    		    	 	} else if (m1.number<m2.number) {
    	               matrix1.moveNext();
    		    	 	}
         }
             if (x!=0) {
    		    	matrix.changeEntry(i, j, x);
    		    	      }
           }
      }
      	 	
       return matrix;
    }

   //a from to print matrix
   public String toString() {
        Entry ent = new Entry();
        String str ="";
       if (this!=null) {
        for (int i =1; i<=getSize();i++) {
        		List matrix = this.arr[i];
        	 if (matrix.length()>0)
          	str+=i+":"+" ";
        	matrix.moveFront();
        	while (matrix.length()>0&&matrix.index()>=0) {
        		ent = (Entry)arr[i].get();
        		str+=ent.toString();
        		matrix.moveNext();
        	}
        	 if(matrix.length()>0) {
        	   	  str+="\n";
        	   }
        	   
        }
      }  
          System.out.print(str);
        	return str;	
		}
	
   	
   	
   

}