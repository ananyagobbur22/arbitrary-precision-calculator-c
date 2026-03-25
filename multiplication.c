#include "apc.h"
#include <stdio.h>

int multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    remove_leading_zeros(&head1, &tail1);
    remove_leading_zeros(&head2, &tail2);

    /* If any number is zero */
    if ((head1->data == 0 && head1->next == NULL) ||
        (head2->data == 0 && head2->next == NULL))
    {
        insert_first(0, headR, tailR);
        return SUCCESS;
    }

    Dlist *resultH = NULL, *resultT = NULL;

    Dlist *t2 = tail2;
    int shift = 0;

    while (t2)
    {
        Dlist *partialH = NULL, *partialT = NULL;
        Dlist *t1 = tail1;

        int carry = 0;

        /* Multiply single digit */
        while (t1)
        {
            int prod = t1->data * t2->data + carry;
            carry = prod / 10;
            prod %= 10;

            insert_first(prod, &partialH, &partialT);
            t1 = t1->prev;
        }

        if (carry)
            insert_first(carry, &partialH, &partialT);

        /* Add shifting zeros */
        for (int i = 0; i < shift; i++)
            insert_at_last(0, &partialH, &partialT);

        /* Add partial result to total result */
        if (resultH == NULL)
        {
            copy_list(partialH, &resultH, &resultT);
        }
        else
        {
            Dlist *tempH = NULL, *tempT = NULL;
            copy_list(resultH, &tempH, &tempT);

            free_list(&resultH, &resultT);
            resultH = NULL;
            resultT = NULL;

            addition(&tempT, &partialT, &resultH, &resultT);

            free_list(&tempH, &tempT);
        }

        free_list(&partialH, &partialT);

        t2 = t2->prev;
        shift++;
    }

    remove_leading_zeros(&resultH, &resultT);

    copy_list(resultH, headR, tailR);
    free_list(&resultH, &resultT);

    return SUCCESS;
}