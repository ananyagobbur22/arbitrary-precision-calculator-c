#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    remove_leading_zeros(head1, tail1);
    remove_leading_zeros(head2, tail2);

    /* Division by zero */
    if ((*head2)->data == 0 && (*head2)->next == NULL)
    {
        printf("Division by zero not allowed\n");
        return FAILURE;
    }

    /* dividend < divisor */
    if (compare(*head1, *head2) < 0)
    {
        free_list(head1, tail1);
        insert_first(0, head1, tail1);

        copy_list(*head1, headR, tailR);
        return SUCCESS;
    }

    Dlist *tempH = NULL, *tempT = NULL;
    copy_list(*head1, &tempH, &tempT);

    free_list(head1, tail1);

    int count = 0;
    int flag;

    while (compare(tempH, *head2) >= 0)
    {
        Dlist *remH = NULL, *remT = NULL;

        subtraction(&tempH, &tempT,
                    head2, tail2,
                    &remH, &remT, &flag);

        free_list(&tempH, &tempT);
        copy_list(remH, &tempH, &tempT);

        free_list(&remH, &remT);

        count++;
    }

    /* Build quotient */
    if (count == 0)
    {
        insert_first(0, head1, tail1);
    }
    else
    {
        while (count)
        {
            insert_first(count % 10, head1, tail1);
            count /= 10;
        }
    }

    /* Remove leading zeros in quotient */
    remove_leading_zeros(head1, tail1);

    /* Remainder */
    copy_list(tempH, headR, tailR);

    free_list(&tempH, &tempT);

    return SUCCESS;
}
