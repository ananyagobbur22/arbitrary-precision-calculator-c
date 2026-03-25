#ifndef APC_H
#define APC_H

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
} Dlist;

/* List functions */
int insert_at_last(int data, Dlist **head, Dlist **tail);
int insert_first(int data, Dlist **head, Dlist **tail);
void free_list(Dlist **head, Dlist **tail);
void copy_list(Dlist *src, Dlist **destH, Dlist **destT);
void remove_leading_zeros(Dlist **head, Dlist **tail);
int compare(Dlist *head1, Dlist *head2);
void print_list(Dlist *head);

/* Validation & Conversion */
int is_number(const char *str);
int string_to_list(const char *str,
                   Dlist **head,
                   Dlist **tail,
                   int *sign);

/* Operations */
int addition(Dlist **tail1, Dlist **tail2,
             Dlist **headR, Dlist **tailR);

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR,
                int *flag);

int multiplication(Dlist *head1, Dlist *tail1,
                   Dlist *head2, Dlist *tail2,
                   Dlist **headR, Dlist **tailR);

int division(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR);

#endif
