#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "class.h"

/* Number of word pointers allocated for a new class.
   This is also the number of word pointers added to a class
   using realloc, when the class is full.
*/
static int class_increment = 0;


/* Set class_increment to size, and initialize random number generator.
   The random number generator is used to select a random word from a class.
   This function should be called exactly once, on startup.
*/
void init_class(int size) {
    class_increment = size;
    srand(time(0));
}


/* Given a pointer to the head of a linked list of Class nodes,
   print each class's signature and words.

   Do not modify this function. It will be used for marking.
*/
void print_classes(Class* cl_list) {
    int i;
    Class *cl = cl_list;
    
    while (cl) {
        printf("***Class signature: %s Num words: %d\n",
               cl->signature, cl->num_words);
        for(i = 0; i < cl->num_words; i++) {
            printf("     %s\n", cl->word_ptrs[i]);
        }
        printf("\n");
        cl = cl->next;
    }
}


/* Return a pointer to a new class whose signature is 
   a copy of str. Initialize word_ptrs to point to 
   class_increment+1 pointers, numwords to 0, 
   maxwords to class_increment, and next to NULL.
*/
Class *new_class(char *str) {
    Class *new = malloc(sizeof(Class));
    new->signature = malloc(sizeof(char) * (strlen(str)+1));
    strcpy(new->signature, str);
    new->word_ptrs = malloc(sizeof(char*)*(class_increment+1));
    new->num_words = 0;
    new->max_words = class_increment;
    new->next = NULL;
    if(!(new->signature) || !new || !(new->word_ptrs)){
        perror("malloc");
        exit(1);
    }  
    return new;
}


/* Add word to the next free slot cl->word_ptrs.
   If cl->word_ptrs is full, first use realloc to allocate class_increment
   more pointers and then add the new pointer.
*/
void add_word_to_class(Class *cl, char *word) {
    if(cl->num_words == cl->max_words){
        cl->max_words += class_increment;
	    cl->word_ptrs = realloc(cl->word_ptrs, sizeof(char*)*cl->max_words);
        if(!(cl->word_ptrs)){
	    perror("realloc");
            exit(1);
        }
    }
    (cl->word_ptrs)[cl->num_words++] = word;
}


/* Return a pointer to the class whose signature is sig;
   if there is no such class, return NULL.
   cl_list is a pointer to the head of a list of Class nodes.
*/
Class *find_class(Class *cl_list, char *sig) {
    Class *curr = cl_list;
    while(curr != NULL){
        if(strcmp(curr->signature, sig) == 0){
	    return curr;
	} else {
	    curr = curr->next;
        }
    }
    return NULL;
}


/* Return a pointer to the class in the list with the most words;
   if the list is empty, return NULL. If multiple classes have the most words,
   return a pointer to any of them.
   cl_list is a pointer to the head of a list of Class nodes.
*/
Class *find_biggest_class(Class *cl_list) {
    if (cl_list == NULL){
	return NULL;
    }
    Class *curr = cl_list;
    Class *biggest = cl_list;
    while(curr != NULL){
        if(curr->num_words > biggest->num_words){
	    biggest = curr;
	 }
	curr = curr->next;
    }
    return biggest;
}


/* Deallocate all memory rooted in the List pointed to by cl_list. */
void deallocate_classes(Class *cl_list) {
    Class *curr = cl_list;
    while(curr != NULL){
	free(curr->word_ptrs);
        free(curr->signature);
        Class *temp = curr;
        curr = temp->next;
        free(temp);
    }
}

/*Helper function: fills sig with the signature of a word
*/
void get_word_signature(char *word, char letter, char *sig){
    int len = strlen(word);
    for (int i = 0; i < len; i++){
        if (word[i] == letter){
	    sig[i] = letter;
	}
	else {
	    sig[i] = '-';
	}
    }
    sig[len] = '\0';
}

/* Generate and return a linked list of all classes using words pointed to
   by word_list, using letter to partition the words.

   Implementation tips: To decide the class in which each word belongs, you
   will need to generate the signature of each word. Create only the classes
   that have at least one word from the current word_list.
*/
Class *generate_classes(char **word_list, char letter) {
    Class *clhead = NULL;
    char sig[strlen(*word_list)+1];
    int i = 0;
    while (word_list[i] != NULL){
        get_word_signature(word_list[i], letter, sig);
	Class *cl = find_class(clhead, sig);
	if (cl == NULL){
            cl = new_class(sig);
	    cl->next = clhead;
            clhead = cl;
	}
	add_word_to_class(cl, word_list[i]);
        i++;
    }
    return clhead;
}


/* Return the signature of the class pointed to by cl. */
char *get_class_signature(Class *cl) {
    return cl->signature;
}


/* Return a pointer to word pointers, each of which
   points to a word in cl. These pointers should not be the same
   as those used by cl->word_ptrs (i.e. they should be independently malloc'd),
   because cl->word_ptrs can move during a realloc.
   As with cl->word_ptrs, the final pointer should be NULL.
*/
char **get_new_word_list(Class *cl) {
    int size = cl->num_words;
    char **new = malloc(sizeof(char*)*(size+1));
    if(!new){
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < size; i++){
        new[i] = cl->word_ptrs[i];
    }
    new[size] = NULL;
    return new;
}


/* Return a pointer to a random word from cl. 
   Use rand (man 3 rand) to generate random integers.
*/
char *get_random_word_from_class(Class *cl) {
    return (cl->word_ptrs)[rand() % cl->num_words];
}
