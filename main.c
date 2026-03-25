#include <stdio.h>
#include <string.h>
#include "apc.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./apc <num1> <operator> <num2>\n");
        return FAILURE;
    }

    if (is_number(argv[1]) == FAILURE || is_number(argv[3]) == FAILURE)
    {
        printf("Invalid number\n");
        return FAILURE;
    }

    Dlist *h1 = NULL, *t1 = NULL;
    Dlist *h2 = NULL, *t2 = NULL;
    Dlist *hR = NULL, *tR = NULL;

    int sign1, sign2;

    string_to_list(argv[1], &h1, &t1, &sign1);
    string_to_list(argv[3], &h2, &t2, &sign2);

    char op = argv[2][0];

    /* ---------------- ADDITION ---------------- */

    if (op == '+')
    {
        if (sign1 == sign2)
        {
            addition(&t1, &t2, &hR, &tR);

            /* Print sign only if result not zero */
            if (sign1 == -1 &&
                !(hR->data == 0 && hR->next == NULL))
                printf("-");
        }
        else
        {
            int flag = 0;
            subtraction(&h1, &t1, &h2, &t2, &hR, &tR, &flag);

            if (flag && !(hR->data == 0 && hR->next == NULL))
                printf("-");
        }

        print_list(hR);
    }

    /* ---------------- SUBTRACTION ---------------- */

    else if (op == '-')
    {
        if (sign1 != sign2)
        {
            addition(&t1, &t2, &hR, &tR);

            if (sign1 == -1 && !(hR->data == 0 && hR->next == NULL))
                printf("-");
        }
        else
        {
            int flag = 0;
            subtraction(&h1, &t1, &h2, &t2,
                        &hR, &tR, &flag);

            if (flag &&
                !(hR->data == 0 && hR->next == NULL))
                printf("-");
        }

        print_list(hR);
    }

    /* ---------------- MULTIPLICATION ---------------- */

    else if (op == '*')
    {
        multiplication(h1, t1, h2, t2, &hR, &tR);

        if ((sign1 * sign2 == -1) &&
            !(hR->data == 0 && hR->next == NULL))
            printf("-");

        print_list(hR);
    }

    /* ---------------- DIVISION ---------------- */


    else if (op == '/')
{
    if (division(&h1, &t1, &h2, &t2, &hR, &tR) == FAILURE)
        return FAILURE;

    printf("Quotient: ");

    /* Print negative sign only if quotient is not zero */
    if ((sign1 * sign2 == -1) && !(h1->data == 0 && h1->next == NULL))
        printf("-");

    print_list(h1);
}

    else
    {
        printf("Operator not implemented\n");
        return FAILURE;
    }

    return SUCCESS;
}
