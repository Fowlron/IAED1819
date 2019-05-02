#include <stdio.h>

#define ALUNOS 10
#define DISCIPLINAS 5

#define DIM 80

long score_disciplina(int disciplina, int valores[ALUNOS][DISCIPLINAS])
{
    int i, score = 0;
    for (i = 0; i < ALUNOS; i++)
        score += valores[i][disciplina];
    return score;
}

long score_aluno(int aluno, int valores[ALUNOS][DISCIPLINAS])
{
    int i, score = 0;
    for (i = 0; i < DISCIPLINAS; i++)
        score += valores[aluno][i];
    return score;
}

int main()
{
    int valores[ALUNOS][DISCIPLINAS], n_inputs = 0, i, aluno, disc, a, d, v, max_n = 0, max_score = -100;
    
    scanf("%d", &n_inputs);
 
    for (aluno = 0; aluno < ALUNOS; aluno++)
    {
        for (disc = 0; disc < DISCIPLINAS; disc++)
        {
            valores[aluno][disc] = 0;
        }
    }

    for (i = 0; i < n_inputs; i++)
    {
        scanf("%d", &a);
        scanf("%d", &d);
        scanf("%d", &v);
        valores[a][d] = v;
    }
    for (i = 0; i < DISCIPLINAS; i++)
    {
        if (score_disciplina(i, valores) > max_score)
        {
            max_score = score_disciplina(i, valores);
            max_n = i;
        }
    }
    printf("%d\n", max_n);
    max_score = -100;
    for (i = 0; i < ALUNOS; i++)
    {
        if (score_aluno(i, valores) > max_score)
        {
            max_score = score_aluno(i, valores);
            max_n = i;
        }
    }
    printf("%d\n", max_n);
    return 0;
}
