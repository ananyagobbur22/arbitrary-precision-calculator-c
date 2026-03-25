#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/* ================= INSERT ================= */

int insert_at_last(int data, Dlist **head, Dlist **tail)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    (*tail)->next = new;
    new->prev = *tail;
    *tail = new;

    return SUCCESS;
}

int insert_first(int data, Dlist **head, Dlist **tail)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    (*head)->prev = new;
    new->next = *head;
    *head = new;

    return SUCCESS;
}

/* ================= FREE ================= */

void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;
    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}

/* ================= COPY ================= */

void copy_list(Dlist *src, Dlist **destH, Dlist **destT)
{
    free_list(destH, destT);

    while (src)
    {
        insert_at_last(src->data, destH, destT);
        src = src->next;
    }
}

/* ================= REMOVE LEADING ZEROS ================= */

void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    while (*head && (*head)->data == 0 && (*head)->next)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

/* ================= COMPARE ================= */

int compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *t1 = head1;
    Dlist *t2 = head2;

    while (t1) { len1++; t1 = t1->next; }
    while (t2) { len2++; t2 = t2->next; }

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    while (head1 && head2)
    {
        if (head1->data > head2->data) return 1;
        if (head1->data < head2->data) return -1;
        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}

/* ================= PRINT ================= */

void print_list(Dlist *head)
{
    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

/* ================= VALIDATION ================= */

int is_number(const char *str)
{
    int i = 0;

    if (str[0] == '+' || str[0] == '-')
        i = 1;

    if (str[i] == '\0')
        return FAILURE;

    for (; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return FAILURE;

    return SUCCESS;
}

/* ================= STRING TO LIST (FIXED) ================= */

int string_to_list(const char *str,
                   Dlist **head,
                   Dlist **tail,
                   int *sign)
{
    int i = 0;
    *sign = 1;

    if (str[0] == '-')
    {
        *sign = -1;
        i = 1;
    }
    else if (str[0] == '+')
        i = 1;

    /* Insert digits */
    for (; str[i]; i++)
        insert_at_last(str[i] - '0', head, tail);

    /* REMOVE LEADING ZEROS */
    remove_leading_zeros(head, tail);

    /* If number becomes 0, sign must be positive */
    if (*head && (*head)->data == 0 && (*head)->next == NULL)
        *sign = 1;

    return SUCCESS;
}