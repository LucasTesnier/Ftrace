/*
** EPITECH PROJECT, 2022
** Project
** File description:
** ftrace_recus
*/

static void toto(void)
{
    static int tutu = 0;

    tutu++;
    if (tutu != 3)
        toto();
    else
        return;
}

int main(void)
{
    toto();
}