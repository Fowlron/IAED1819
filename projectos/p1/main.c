/*****************************************************************************
 * Projeto 1 IAED1819: main.c                                                *
 * Neste projeto, tenciona-se criar um sistema de reserva de salas,com o     *
 * qual se deve interagir atraves de comandos definidos no enunciado do      *
 * projeto.                                                                  *
 *                                                                           *
 * Este ficheiro contem as funcoes main() e mainLoop(), responsaveis pelo    *
 * inicio do programa e pelo loop principal no qual o utilizador insere os   *
 * varios comandos.                                                          *
 *                                                                           *
 * Projeto de: Pedro Godinho - 93608 - LETI                                  *
 *                                                                           *
 ****************************************************************************/

#include <stdio.h>
#include "proj1.h"

/*****************************************************************************
 * Funcao responsavel pelo loop principal do programa. A cada interacao, o
 * utilizador pode dar um comando, sendo a funcao respetiva chamada.
 ****************************************************************************/
void mainLoop()
{
    int running = 1;
    char command;
    /* Loop principal, em que se recebe cada comando */
    while (running)
    {
        /* ler cada comando */
        command = getchar();
        /* remover ' ' do input buffer */
        getchar(); 
        switch (command)
        {
            case EOF:
                running = 0;
                break;
            case 'x':
                running = 0;
                break;
            case 'a':
                addEvent();
                break;
            case 'l':
                listEvents();
                break;
            case 's':
                listEventsInRoom();
                break;
            case 'r':
                deleteEvent();
                break;
            case 'i':
                changeStartTime();
                break;
            case 't':
                changeDuration();
                break;
            case 'm':
                changeRoom();
                break;
            case 'A':
                addParticipant();
                break;
            case 'R':
                removeParticipant();
                break;
        }
    }
}


/* Ponto de inicio do programa */
int main()
{
    /* inicializa-se a tabela para uma tabela de eventos nulos */
    initializeTable();
    /* inicia-se o programa */
    mainLoop();

    return 0;
}

