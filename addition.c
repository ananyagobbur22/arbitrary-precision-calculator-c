#include "apc.h"
#include <stdio.h>
int addition(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    int carry = 0;

    while (t1 != NULL || t2 != NULL)
    {
        int sum = carry;

        if (t1 != NULL)
        {
            sum += t1->data;
            t1 = t1->prev;
        }

        if (t2 != NULL)
        {
            sum += t2->data;
            t2 = t2->prev;
        }

        int digit = sum % 10;
        carry = sum / 10;

        insert_first(digit, headR, tailR);
    }

    /* If carry remains */
    if (carry != 0)
    {
        insert_first(carry, headR, tailR);
    }

    return SUCCESS;
}
