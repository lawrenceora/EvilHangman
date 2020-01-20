#ifndef CLASS_H
#define CLASS_H

struct class {
    char *signature; 	/* Class signature; e.g. ---e */
    char **word_ptrs; 	/* Words belonging to class */
    int num_words; 		/* Number of words in class */
    int max_words; 		/* Number of total pointers in word_ptrs so far */
    struct class *next; 	/* NULL means end of list */
};
typedef struct class Class; 


void init_class(int size);
void print_classes(Class* class_list);
Class *new_class(char *str);
void add_word_to_class(Class *cl, char *word);
Class *find_class(Class *cl_list, char *sig);
Class *find_biggest_class(Class *cl_list);
void deallocate_classes(Class *cl_list);
Class *generate_classes(char **word_list, char letter);
char *get_class_signature(Class *cl);
char **get_new_word_list(Class *cl);
char *get_random_word_from_class(Class *cl);

#endif
