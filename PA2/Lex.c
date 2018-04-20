/** Mengdi Wei
  * ID:1538074
  * PA2
  * Lex.c can use insertion sort to make the words in  lexicographic order.
  */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 1000
	  
	int main ( int argc, char* argv[]) {
		 FILE *in, *out;
     
 	   if( argc != 3 ){
      		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(EXIT_FAILURE);
   	}


   	in = fopen(argv[1], "r");
   	if( in==NULL ){
      		printf("Unable to read from file %s\n", argv[1]);
      		exit(EXIT_FAILURE);
   	}

    
   	out = fopen(argv[2], "w");
   	
   	if( out==NULL ){
      		printf("Unable to write to file %s\n", argv[2]);
      		exit(EXIT_FAILURE);
   	}
   	
     char word [MAX_LEN ] ;
        int number = 0;
   	 while ( fgets(word, MAX_LEN , in) != NULL) {
   	 	  number++;
   	 }
   	 char* strs[MAX_LEN];
   	 rewind(in);
     
	   int n = 0;
	  
	    
	  while(  fgets(word,MAX_LEN , in) != NULL) {
	  	int j = strlen(word)+1;
		  strs[n] = malloc( sizeof(char)*j );
		  
      strcpy(strs[n], word );
      n++;
 	  }
 	  
 	  
 	  //These is insertionsort
 	  List list = newList();
	  append(list, 0);
	    for (int i = 1; i<n; i++) {
	    	char* arr = strs[i];
	    if (strcmp(arr, strs[back(list)])>0) {
	  		append (list, i);
	  		continue;
	  	}

	  	 	if (strcmp(arr, strs[front(list)])<0) {
	  		prepend (list, i);
	  		continue;
	  	}
	 
	  	moveFront(list);
	  	
	  	 while (index(list)!=-1) {
	  	 	 if (strcmp(arr, strs[get(list)])<0) {
	  	 	 	 insertBefore(list, i);
	  	 	 	 break;
	  	 	 	} 
	  	 	 	moveNext(list);
	  	 	 	}
	  	   
	  	 	 
	  	 }
	  
	  moveFront(list);
	   while (index(list)>=0) {
	   	int n = get(list);
	   	fprintf(out, "%s \n", strs[n]);
	   	 moveNext(list);
	   }
	     
   	   fclose(in);
       fclose(out);
	     freeList(&list);//free the list
	     for(int i = 0; i<number; i++){
		   free(strs[i]);
	     }//free the char*
	      
	    return(0);
	
	}