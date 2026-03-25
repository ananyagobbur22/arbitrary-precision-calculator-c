#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR,
                int *flag)
{
    *flag = 0;

    Dlist *h1 = *head1;
    Dlist *t1 = *tail1;
    Dlist *h2 = *head2;
    Dlist *t2 = *tail2;

    /* Determine which is larger */
    if (compare(h1, h2) < 0)
    {
        *flag = 1;

        Dlist *tempH = h1;
        Dlist *tempT = t1;

        h1 = h2;
        t1 = t2;
        h2 = tempH;
        t2 = tempT;
    }

    Dlist *ptr1 = t1;
    Dlist *ptr2 = t2;

    int borrow = 0;

    while (ptr1)
    {
        int d1 = ptr1->data - borrow;
        int d2 = (ptr2) ? ptr2->data : 0;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        insert_first(d1 - d2, headR, tailR);

        ptr1 = ptr1->prev;
        if (ptr2) ptr2 = ptr2->prev;
    }

    remove_leading_zeros(headR, tailR);

    return SUCCESS;
}
