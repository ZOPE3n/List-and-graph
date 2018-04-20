/**Mengdi Wei
  *ID: 1538074
  *This is the list, which provides 
  * a libarry of methods.
  */

import java.util.*;
import java.io.*;
  
 class List {
	Node front;
	Node cursor, back;
	int lengths =0;
	int index;
  //This is the constructor
	public List() {
	 this.front=null;
	 this.cursor=this.back=null;
	 lengths=0;
	 index=-1;
	}
  //return list's length
	public Object length () {
		return this.lengths;
	}
	 //return front's element
	public Object front() {
		return front.item;
	}
	 //return back's element
	public Object back() {
		return back.item;
	}
	 //return cursor's element
   public Object get() {
   	return cursor.item;
   }
    //return index
    public Object index() {
     	return this.index;
    }
    //equals method which can test if two list equals or not
    boolean equals(List Left) {
    	Node m = Left.front;
    	Node n = this.front;
    	if (Left.length()!=this.length()) {
    		//System.out.println(Left.length()+"   "+this.length());
    		return false;
    	} else {
    		while ((m!=null)&&(n!=null)) {
    			if (m.item!=n.item) {
    			 
    			 return false;
    			} else {
    			 m=m.next;
    			 n=n.next;
    			  }
    		}
    			 return true;
    	}
    }
    //reset the list
    void clear () {
    	this.front=this.back=null;
    	lengths=0;
    	index=-1;
    }
    //move the cursor to the front
    void moveFront() {
    	if (front!=null) {
    		index=0;
    		cursor=front;
    	} 
     return;
    }
    //move the cursor to the back
    void moveBack() {
      if (front!=null) {
    		index=length()-1;
    		cursor=back;
    	}
    	return;
    }
    //move the cursor previous
    void movePrev() {
    	Node m=new Node();
    	if (index>=0&&index<=length()-1) {
    	 cursor=cursor.pre;
    	 index--;
    	} else
    	  index=-1;
    	return;
    }
    //move the curosr next
    void moveNext() {
    	 	if (index>=0&&index<length()-1) {
    	 cursor=cursor.next;
    	
    	 index++;
    	} else 
    	  index=-1;
    	return;
    }
    //prepend a node to the list
	void prepend (int item) {
		Node value=new Node(item);
		if (length()==0) {
			this.front=this.back=value;
			lengths++;
		} else {
			 this.front.pre=value;
			 value.next=front;
			 this.front=value;
			 lengths++;
			 index++;
		}
		return;
	}
	//append a node to the list
	 void append (int item) {
	 	Node value=new Node(item);
	 		if (length()<=0) {
			this.front=this.back=value;
			lengths++;
		} else {
			  this.back.next=value;
			  value.pre=back;
			  this.back=value;
			  lengths++;
		}
		return;
	 }
	 //insertBefore the node
	 void insertBefore(int item) {
	 	Node value=new Node(item);
	 	if (index==0)
	 	    prepend(item);
	 	 else {
	 	 	  value.pre=cursor.pre;
	 	 	  value.next=cursor;
	 	 	  cursor.pre.next=value;
	 	 	  cursor.pre=value;
	 	 	  lengths++;
	 	 	  index++;
	 	 }
	 	 return;
	 }
	  //insert after the node
	 void insertAfter (int item) {
	 Node value=new Node(item);
	 	if (index==length()-1)
	 	    append(item);
	 	 else {
	 	 	  value.next=cursor.next;
	 	 	  cursor.next=value;
	 	 	  value.pre=cursor;
	 	 	  cursor=value;
	 	 	  lengths++;
	 	 }
	 	  return;
	 }
	 //delete the front element
	 void deleteFront() {
	 	if (front!=null) {
	 		front=front.next;
	 		lengths--;
	 	} 
	 	return;
	 }
	 //delete the back element
	 void deleteBack() {
	 	if (front!=null) {
       back=back.pre;
       lengths--;
	 	}
	 }
	  //delete the cursor element
	  void delete () {
	  	Node right=new Node();
	  	Node left=new Node();
	  	if (index>=0) {
	  		right=cursor.next;
	  		left=cursor.pre;
	  	  left.next=right;
	  	  right.pre=left;
	  	  cursor.pre=left;
	  	  cursor.next=right;
	  		cursor=null;
	  		index=-1;
	  		lengths--;
	  	}
	  }
   
    public String toString() {
      	Node i=front;
     
      	String word2="";
    	 while (i!=null) {
    	 	
    	 	 word2= word2+i.toString()+" ";
    	 	 i=i.next;
    	 }
    	 return word2;
    }
    //copy this list
    List copy() {
      List copyList=new List();
      Node i=this.front;
      while (i!=null) {
      	copyList.append(i.item);
      	i=i.next;
      }
      return copyList;
    }
  
 }
 
class Node {
   Object item;
	Node next;
  Node front, pre;
	Node cursor, back;
  Node(){}
  Node (int item) {
  	pre=next=front=cursor=back=null;
  	this.item=item;
  }
  public String toString() {
  	return Integer.toString(item);
  }
}

