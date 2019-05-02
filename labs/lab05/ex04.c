#include <stdio.h>

#define MAXDIM 100

int ganha(int dim, char tab[MAXDIM][MAXDIM], char jogador)
{
    int row, col, row_offset, col_offset, check_row, check_col;

    for (row = 0; row < dim; row++)
    {
        for (col = 0; col < dim; col++)
        {
            /* Verificar se e do jogador que se quer */
            if (tab[row][col] == jogador)
            {
                /*printf("First found at %d %d\n", row, col);*/
                /* andar numa direcao */
                for (row_offset = -1; row_offset <= 1; row_offset++)
                {
                    for (col_offset = -1; col_offset <= 1; col_offset++)
                    {
                        /* Fazer offset do sitio a verificar*/
                        check_row = row + row_offset;
                        check_col = col + col_offset;
                        /* Se a variavel for uma coordenada valida e tambem tiver um char correto */
                        if ((row_offset != 0 || col_offset != 0) && check_row >= 0 && check_col >= 0 && check_row < dim && check_col < dim && tab[check_row][check_col] == jogador)
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    int D, N, i, row, col;
    char tab[MAXDIM][MAXDIM];
    char p;
    scanf("%d %d", &D, &N);

    for (row = 0; row < MAXDIM; row++)
        for (col = 0; col < MAXDIM; col++)
            tab[row][col] = '?';

    for (i = 0; i < N; i++)
    {
        scanf("%d %d %c", &row, &col, &p);
        tab[row][col] = p;
    }

    if (ganha(D, tab, 'x'))
        printf("x\n");
    else if (ganha(D, tab, 'o'))
        printf("o\n");
    else
        printf("?\n");


    return 0;
}
