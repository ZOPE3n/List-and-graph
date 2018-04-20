/**Mengdi Wei
  *ID: 1538074
  *PA3
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
	public int length () {
		return this.lengths;
	}
	 //return front's element
	public Object front() {
   if(length()!=0)
		return front.item;
		else 
		return null;
	}
	 //return back's element
	public Object back() {
    if (length()!=0)
		return back.item;
		else
		return null;
	}
	 //return cursor's element
   public Object get() {
   if (length()!=0&&index()>=0)
   	return cursor.item;
   	else 
   	return null;
   }
    //return index
    public int index() {
     	return this.index;
    }
    //equals method which can test if two list equals or not
    boolean equals(List Left) {
    	Node m = Left.front;
    	Node n = this.front;
    	if (Left.length()!=this.length()) {
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
    	this.cursor=null;
    	lengths=0;
    	index=-1;
    }
    //move the cursor to the front
    void moveFront() {
    	if (length()!=0) {
    		index=0;
    		cursor=front;
    	} 
     return;
    }
    //move the cursor to the back
    void moveBack() {
      if (length()!=0) {
    		index=length()-1;
    		cursor=back;
    	}
    	return;
    }
    //move the cursor previous
    void movePrev() {
    	Node m=new Node();
    	if (index>0) {
    	 cursor=cursor.pre;
    	 index--;
    	} else
    	  index=-1;
    	return;
    }
    //move the curosr next
    void moveNext() {
    	 	if (index!=-1&&index<length()-1) {
    	 cursor=cursor.next;
    	
    	 index++;
    	} else 
    	  index=-1;
    	return;
    }
    //prepend a node to the list
	void prepend (Object item) {
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
	 void append (Object item) {
	 	Node value=new Node(item);
	 		if (length()==0) {
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
	 void insertBefore(Object item) {
	 			if( lengths <= 0 || index< 0){
				throw new RuntimeException( "List Error: insertAfter called on an empty list.");
			} else {
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
	 }
	 	 return;
	 }
	  //insert after the node
	 void insertAfter (Object item) {
	 		if( lengths <= 0 || index < 0){
				throw new RuntimeException( "List Error: insertAfter called on an empty list.");
			}
			else if(index >= lengths ){
				throw new RuntimeException("List Error: insertAfter called on an index off the end of the list");
			} else {
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
	 	 }
	 	  return;
	 }
	 //delete the front element
	 void deleteFront() {
	 	  if (length()==1) {
	 	  this.front = null;
			lengths--;
			if(index!=-1)
			index--;
	 	  } else if (length()>1) {
		
	 		front=front.next;
	 			if(front!=null)
				front.pre= null;
				
	   	lengths--;
	   		if(index!=-1)
				index--;
	 }
	}

	 //delete the back element
	 void deleteBack() {

		if(length()==1){
			if(index==length()-1){
				cursor=null;
				index=-1;
			}
			lengths--;
    
		} else if (length()>1) {
       back=back.pre;
        if(index==length()-1){
				cursor=null;
				index=-1;
			}
       if(back!=null)
				back.next = null;
        lengths--;
     
      }
    
	 	}
	 	    

	  //delete the cursor element
	  void delete () {

	  
	  	if(length()>0&&index()>=0){
	  			Node right=new Node();
	  	Node left=new Node();	
	  		right=cursor.next;
	  		left=cursor.pre;
	  		if (right!=null) {
	  			right.pre=left;
	  		} else {
	  			back=left;
	  		}
	  	 if(left!=null){
				   left.next = right;
		    	}else{
				front=right;
			  }
	  		cursor=null;
	  		index=-1;
	  		lengths--;
	  	}
 }
   
    public String toString() {
    	
     StringBuffer sb = new StringBuffer();
		     Node i = this.front;
		
	    while( i!=null ){
		    sb.append(i.toString());
		    if(i.next!=null)
		    	sb.append(" ");
		      i = i.next;
		}
		return new String(sb);
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
  class Node {
   Object item;
	Node next;
  Node front, pre;
	Node cursor, back;
  Node(){}
  Node (Object item) {
  	pre=next=front=cursor=back=null;
  	this.item=item;
  }
  public String toString() {
  	return item.toString();
  }
}
 }
 


