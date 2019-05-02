/******************************************************************************
 * Projeto 1 IAED1819: proj1.c                                                *
 * Neste projeto, tenciona-se criar um sistema de reserva de salas, com o     *
 * qual se deve interagir atraves de comandos definidos no enunciado do       *
 * projeto.                                                                   *
 *                                                                            *
 * Este ficheiro contem o codigo do modelo do sistema de reserva de salas     *
 * proposto pelo enunciado to projeto 1 de IAED-2018/2019. Documentacao para  *
 * cada funcao pode ser encontrada no header proj1.h, bem como as estruturas  *
 * Time, Event, e RoomEventPair e respitivas documentacoes.                   *
 *                                                                            *
 * Projeto de: Pedro Godinho - 93608 - LETI                                   *
 *                                                                            *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj1.h"


/* A tabela onde serao gravados todos os eventos. */
Event eventTable[MAXROOMS][MAXEVENTS];


void initializeTable()
{
    int iroom, ievent;
    /* Fazer cada evento da sala nulo */
    for (iroom = 0; iroom < MAXROOMS; iroom++)
        for (ievent = 0; ievent < MAXEVENTS; ievent++)
            nullEvent(iroom, ievent);
}


void nullEvent(int iroom, int ievent)
{
    int iparticip;

    strncpy(eventTable[iroom][ievent].description, "", MAX);
    eventTable[iroom][ievent].startTime.year = -1;
    eventTable[iroom][ievent].startTime.month = -1;
    eventTable[iroom][ievent].startTime.day = -1;
    eventTable[iroom][ievent].startTime.h = -1;
    eventTable[iroom][ievent].startTime.m = -1;
    eventTable[iroom][ievent].duration = -1;
    eventTable[iroom][ievent].room = -1;
    strncpy(eventTable[iroom][ievent].host, "", MAX);
    for (iparticip = 0; iparticip < MAXPARTICIP; iparticip++)
    {
        strncpy(eventTable[iroom][ievent].participants[iparticip], "", MAX);
    }
}


void printEvent(Event event)
{
    int iparticip; 
    printf("%s %02d%02d%02d %02d%02d %d Sala%d %s\n*", 
            event.description, 
            event.startTime.day,
            event.startTime.month,
            event.startTime.year,
            event.startTime.h,
            event.startTime.m,
            event.duration, 
            event.room, 
            event.host);
    for (iparticip = 0; iparticip < MAXPARTICIP; iparticip++)
    {
        /* Escrever cada evento apenas se este nao e nulo */
        /* nota sobre strcmp: strcmp retorna 0 quando as strings sao iguais. 
         * Em vez de usar !strcmp(), usamos != 0
         * Desta forma, a leitura fica simplificada:
         * strcmp(a,b) == 0  <- verdadeiro se as strings forem iguais
         * strcmp(a,b) != 0 <- verdadeiro se as strings forem diferentes */
        if (strcmp(event.participants[iparticip], "") != 0)
            printf(" %s", event.participants[iparticip]);
    }
    printf("\n");
}


int readStrUntilNextChar(char c, char str[MAX])
{
    char current;
    int len;
    /* adicionar cada char a string ate encontrar EOF, \n, ou o caracter de separacao */
    for (len = 0; (current = getchar()) != c && current != EOF && current != '\n'; len++)
        str[len] = current;
    str[len] = '\0'; /* adiciona-se ainda o null-character no fim da string */
    return current == EOF || current == '\n';
}


Time inputsToTime(int date, int h)
{
    Time t;
    t.year = date % 10000; /* ultimos 4 digitos */
    t.month = date / 10000 % 100; /* tirando o ano, ultimos 2 digitos*/
    t.day = date / 1000000; /* primeiros 2 digitos */
    t.h = h / 100; /* 2 primeiros digitos */
    t.m = h % 100; /* 2 ultimos digitos */
    return t;
}


int timeToMinutes(Time time)
{
    return time.h * 60 + time.m;
}


int doEventDatesConflict(Event event1, Event event2)
{
    /* se as datas coincidem, verificar se um evento comeca durante o tempo do outro */
    return (event1.startTime.year == event2.startTime.year && 
            event1.startTime.month == event2.startTime.month && 
            event1.startTime.day == event2.startTime.day &&   /* Verificacao das datas */
            ((timeToMinutes(event1.startTime) >= timeToMinutes(event2.startTime) && /* verificar se 1 inicia durante o outro */
              timeToMinutes(event1.startTime) < timeToMinutes(event2.startTime) + event2.duration) || 
             (timeToMinutes(event2.startTime) >= timeToMinutes(event1.startTime) &&  /* e vice versa */
              timeToMinutes(event2.startTime) < timeToMinutes(event1.startTime) + event1.duration)));
}


void eventBubbleSort(Event events[MAXROOMS * MAXEVENTS], int len)
{
    int current;

    /* Usamos uma variavel para verificar se foi feita uma troca, para acelerar o algoritmo 
     * Caso nao tenha sido feita nenhuma troca, sabe-se que a lista ja esta ordenada. */
    int swapped = 0;
    int comp1, comp2; /* variaveis para comparar */
    while (len >= 2)
    {
        swapped = 0;
        for (current = 0; current < len - 1; current++)
        {
            /* Calcular o ano e comparar */
            comp1 = events[current].startTime.year;
            comp2 = events[current+1].startTime.year;
            if (comp1 > comp2) /* Se o ano do primeiro for maior, trocar e avancar para a proxima iteracao */
            {
                swapped = 1;
                swapInEventArray(events, current, current+1);
                continue;
            } /* Se o ano do primeiro for menor, esta ordenado, logo podemos saltar para a proxima iteracao */
            else if (comp1 < comp2)
                continue;
            /* Se forem iguais, nao podemos concluir nada e temos de comparar com mais detalhe */
            /* A logica mantem-se igual daqui em frente */

            /* mes */
            comp1 = events[current].startTime.month;
            comp2 = events[current+1].startTime.month;
            if (comp1 > comp2)
            {
                swapped = 1;
                swapInEventArray(events, current, current+1);
                continue;
            }
            else if (comp1 < comp2)
                continue;

            /* dia */
            comp1 = events[current].startTime.day;
            comp2 = events[current+1].startTime.day;
            if (comp1 > comp2)
            {
                swapped = 1;
                swapInEventArray(events, current, current+1);
                continue;
            }
            else if (comp1 < comp2)
                continue;

            /* hora */
            if (timeToMinutes(events[current].startTime) > timeToMinutes(events[current+1].startTime))
            {
                swapped = 1;
                swapInEventArray(events, current, current+1);
                continue;
            }
            else if(timeToMinutes(events[current].startTime) < timeToMinutes(events[current+1].startTime))
                continue;

            /* Por convencao, se os eventos sao ao mesmo tempo, comparam-se as salas*/
            if (events[current].room > events[current+1].room)
            {
                swapped = 1;
                swapInEventArray(events, current, current+1);
            }
        }
        if (!swapped) /* Se corremos um loop inteiro sem haver alteracoes, a lista esta ordenada */
            break;
        len--;
    }
}


void swapInEventArray(Event events[MAXROOMS * MAXEVENTS], int i, int j)
{
    Event temp = events[i];
    events[i] = events[j];
    events[j] = temp;
}


RoomEventPair findEventByDescription(char description[MAX])
{
    int iroom, ievent;
    RoomEventPair pair;
    pair.room = -1;
    pair.event = -1;
    /* Iterar todos os eventos ate encontrar um cuja descricao seja a desejada */
    for (iroom = 0; iroom < MAXROOMS; iroom++)
    {
        for (ievent = 0; ievent < MAXEVENTS; ievent++)
        {
            if (strcmp(eventTable[iroom][ievent].description, description) == 0)
            {
                pair.room = iroom;
                pair.event = ievent;
                return pair;
            }
        }
    }
    /* Se nenhum evento com a descricao for encontrado, o return sera -1, -1 */
    return pair;
}


int isEventValidInTable(Event event, char errorMsg[])
{
    int iroom, ievent, i, j;
    int foundConflict = 0; 

    /* iterar cada sala e evento para procurar eventos incompativeis */
    for (iroom = 0; iroom < MAXROOMS; iroom++)
    {
        for (ievent = 0; ievent < MAXEVENTS; ievent++)
        {
            /* Se os eventos forem ao mesmo tempo e nao forem o mesmo... */
            if (doEventDatesConflict(eventTable[iroom][ievent], event) &&
                    strcmp(eventTable[iroom][ievent].description, event.description) != 0)
            {
                /* e se forem na mesma sala, causar erro e sair */
                if (iroom == event.room)
                {
                    printf("%s Sala%d ocupada.\n", errorMsg, event.room);
                    return 0;
                }
                else /* se forem ao mesmo tempo mas numa sala diference... */
                {
                    /* Verificar se os eventos tem o mesmo host */
                    if (strcmp(event.host, eventTable[iroom][ievent].host) == 0)
                    {
                        foundConflict = 1;
                        printf("%s Participante %s tem um evento sobreposto.\n", errorMsg, event.host);
                    }
                    /* iterar os participantes de ambos os eventos para procurar participantes em comum */
                    for (i = 0; i < MAXPARTICIP; i++)
                    {
                        for (j = 0; j < MAXPARTICIP; j++)
                        {
                            /* verificar se os participantes tem o mesmo nome (e nao e um participante nulo) */
                            if (strcmp(eventTable[iroom][ievent].participants[i], event.participants[j]) == 0 &&
                                    strcmp(event.participants[j], "") != 0)
                            {
                                foundConflict = 1;
                                printf("%s Participante %s tem um evento sobreposto.\n", errorMsg, event.participants[j]);
                            }
                        }
                        if (strcmp(eventTable[iroom][ievent].host, event.participants[i]) == 0)
                        {
                            foundConflict = 1;
                            printf("%s Participante %s tem um evento sobreposto.\n", errorMsg, event.participants[i]);
                        }
                        /* Verificar tambem se o host participa num dos outros eventos */
                        if (strcmp(event.host, eventTable[iroom][ievent].participants[i]) == 0)
                        {
                            foundConflict = 1;
                            printf("%s Participante %s tem um evento sobreposto.\n", errorMsg, event.host);
                        }
                    }
                }
            }
        }
    }
    if (foundConflict) 
        return 0;
    return 1;
}


void addEvent()
{
    /* evento para o qual ler os parametros */
    Event event;
    int date, time;
    int moreParticipants = 1; /* 1 se ainda houver mais participantes a adicionar */
    int i;
    char errorMsg[MAX+27] = "Impossivel agendar evento ", tmp[MAX];

    /* Ler cada parametro */
    readStrUntilNextChar(':', event.description);
    readStrUntilNextChar(':', tmp);
    date = atoi(tmp);
    readStrUntilNextChar(':', tmp);
    time = atoi(tmp);
    readStrUntilNextChar(':', tmp);
    event.duration = atoi(tmp);
    readStrUntilNextChar(':', tmp);
    event.room = atoi(tmp);
    readStrUntilNextChar(':', event.host);
    /* ler os 3 participantes, colocando uma string vazia no caso de serem menos do que o maximo */
    for (i = 0; i < MAXPARTICIP; i++)
    {
        if (moreParticipants)
            moreParticipants = !readStrUntilNextChar(':', event.participants[i]);
        else
            strncpy(event.participants[i], "", MAX);
    }

    event.startTime = inputsToTime(date, time);

    /* Formatar a mensagem de erro */
    strcat(errorMsg, event.description);
    strcat(errorMsg, ".");
    /* Nao havendo error, procurar um evento nao nulo na sala escolhida onde escrever o novo evento */
    if (isEventValidInTable(event, errorMsg))
    {
        for (i = 0; i < MAXEVENTS; i++)
        {
            if (eventTable[event.room][i].room == -1)
            {
                eventTable[event.room][i] = event;
                return;
            }
        }
    }
    else
        return;
    printf("Impossivel agendar evento %s. Maximo de %d eventos atingido.\n", event.description, MAXEVENTS);
}


void listEvents()
{
    Event events[MAXROOMS * MAXEVENTS]; /* variavel onde alisar os eventos para colocar no bubblesort*/
    int len = 0; /* array com o numero de eventos */
    int iroom, ievent;

    /* alisa-se os elementos para a array events, ignorando tambem eventos nulos */
    for (iroom = 0; iroom < MAXROOMS; iroom++)
    {
        for (ievent = 0; ievent < MAXEVENTS; ievent++)
        {
            if (eventTable[iroom][ievent].room != -1)
            {
                events[len] = eventTable[iroom][ievent];
                len++;
            }
        }
    }
    eventBubbleSort(events, len);

    /* mostrar a lista de eventos */
    for (ievent = 0; ievent < len; ievent++)
    {
        printEvent(events[ievent]);
    }
}


void listEventsInRoom()
{
    /* le a sala a listar */
    char tmp[MAX];
    int room;
    int ievent, len = 0;
    Event events[MAXEVENTS];

    readStrUntilNextChar(':', tmp);
    room = atoi(tmp);

    /* criar uma array com apenas os eventos nao nulos */
    for (ievent = 0; ievent < MAXEVENTS; ievent++)
    {
        if (eventTable[room][ievent].room != -1)
        {
            events[len] = eventTable[room][ievent];
            len++;
        }
    }
    /* ordena os elementos dessa lista e imprime-os formatados */
    eventBubbleSort(events, len);
    for (ievent = 0; ievent < len; ievent++)
    {
        printEvent(events[ievent]);
    }

}


void deleteEvent()
{
    char description[MAX];
    /* encontrar o evento com a descricao atraves da funcao auxiliar */
    RoomEventPair pair;
    int iroom, ievent;

    /* le a descricao do evento a apagar */
    readStrUntilNextChar(':', description);
    pair = findEventByDescription(description);
    iroom = pair.room;
    ievent = pair.event;

    /* se o evento nao for encontrado, devolver um erro */
    if (iroom == -1)
    {
        printf("Evento %s inexistente.\n", description);
        return;
    }
    
    nullEvent(iroom, ievent);
}


void changeStartTime()
{
    char description[MAX], errorMsg[MAX] = "Impossivel agendar evento ", tmp[MAX];
    int startTime;
    Time time;
    RoomEventPair pair;
    int iroom, ievent;
    Event event;

    readStrUntilNextChar(':', description);
    readStrUntilNextChar(':', tmp);
    startTime = atoi(tmp);
    pair = findEventByDescription(description);
    iroom = pair.room;
    ievent = pair.event;
    time.h = inputsToTime(0, startTime).h;
    time.m = inputsToTime(0, startTime).m;

    /* se o evento nao for encontrado, devolver um erro */
    if (iroom == -1)
    {
        printf("Evento %s inexistente.\n", description);
        return;
    }
    
    event = eventTable[iroom][ievent];

    event.startTime.h = time.h;
    event.startTime.m = time.m;

    /* Formatar a mensagem de erro */
    strcat(errorMsg, event.description);
    strcat(errorMsg, ".");
    if (isEventValidInTable(event, errorMsg))
    {
        eventTable[iroom][ievent].startTime.h = time.h;
        eventTable[iroom][ievent].startTime.m = time.m;
    }
}

void changeDuration()
{
    char description[MAX], errorMsg[MAX] = "Impossivel agendar evento ", tmp[MAX];
    int duration;
    RoomEventPair pair;
    int iroom, ievent;
    Event event;

    readStrUntilNextChar(':', description);
    readStrUntilNextChar(':', tmp);
    duration = atoi(tmp);
    pair = findEventByDescription(description);
    iroom = pair.room;
    ievent = pair.event;

    /* se o evento nao for encontrado, devolver um erro */
    if (iroom == -1)
    {
        printf("Evento %s inexistente.\n", description);
        return;
    }
    
    event = eventTable[iroom][ievent];

    event.duration = duration;
    /* Formatar a mensagem de erro */
    strcat(errorMsg, event.description);
    strcat(errorMsg, ".");
    if (isEventValidInTable(event, errorMsg))
    {
        eventTable[iroom][ievent].duration = duration;
    }
}


void changeRoom()
{
    char description[MAX], errorMsg[MAX] = "Impossivel agendar evento ", tmp[MAX];
    int room;
    RoomEventPair pair;
    int iroom, ievent;
    Event event;

    readStrUntilNextChar(':', description);
    readStrUntilNextChar(':', tmp);
    room = atoi(tmp);
    pair = findEventByDescription(description);
    iroom = pair.room;
    ievent = pair.event;

    /* se o evento nao for encontrado, devolver um erro */
    if (iroom == -1)
    {
        printf("Evento %s inexistente.\n", description);
        return;
    }
    
    event = eventTable[iroom][ievent];

    event.room = room;
    /* Formatar a mensagem de erro */
    strcat(errorMsg, event.description);
    strcat(errorMsg, ".");
    if (isEventValidInTable(event, errorMsg))
    {
        nullEvent(iroom, ievent);

        for (ievent = 0; ievent < MAXEVENTS; ievent++)
        {
            if (eventTable[room][ievent].room == -1)
            {
                eventTable[room][ievent] = event;
                return;
            }
        } 
    }
}


void addParticipant()
{
    char description[MAX];
    char participant[MAX];
    char errorMsg[MAX] = "Impossivel adicionar participante.";
    RoomEventPair pair;
    int iroom, ievent, iparticip, whereToAdd = -1;
    Event event;

    /* ler os parametros */
    readStrUntilNextChar(':', description);
    readStrUntilNextChar('\n', participant);
    
    /* encontrar o evento */
    pair = findEventByDescription(description);
    iroom = pair.room;
    ievent = pair.event;

    if (iroom == -1)
    {
        printf("Evento %s inexistente.\n", description);
        return;
    }

    event = eventTable[iroom][ievent];

    /* verificar que o participane nao esta no evento e procurar um lugar vago para o participante */
    for (iparticip = 0; iparticip < MAXPARTICIP; iparticip++)
    {
        if (strcmp(event.participants[iparticip], participant) == 0)
            return;
        if (strcmp(event.participants[iparticip], "") == 0 && whereToAdd == -1)
            whereToAdd = iparticip;
    }

    /* verificar se foi encontrado um lugar de participante vago */
    if (whereToAdd == -1)
    {
        printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n", 
                event.description);
        return;
    }

    /* adicionar o participante e verificar se o evento e valido antes de aplicar as mudancas na table*/
    strncpy(event.participants[whereToAdd], participant, MAX);
    if (isEventValidInTable(event, errorMsg))
        eventTable[iroom][ievent] = event;
}


void removeParticipant()
{
    char description[MAX]; 
    char participant[MAX];
    RoomEventPair pair;
    Event event;
    int iroom, ievent, iparticip, participLoc = -1, participCount = 0;

    /* ler os parametros */
    readStrUntilNextChar(':', description);
    readStrUntilNextChar('\n', participant);
    pair = findEventByDescription(description);
    iroom = pair.room;
    ievent = pair.event;

    if (iroom == -1)
    {
        printf("Evento %s inexistente.\n", description);
        return;
    }

    event = eventTable[iroom][ievent];
    for (iparticip = 0; iparticip < MAXPARTICIP; iparticip++)
    {
        if (strcmp(event.participants[iparticip], participant) == 0)
            participLoc = iparticip;
        if (strcmp(event.participants[iparticip], "") != 0)
            participCount++;
    }

    if (participCount == 1 && participLoc != -1)
    {
        printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", 
                participant, event.description);
        return;
    }
    if (participLoc != -1)
    {
        for (iparticip = participLoc; iparticip < MAXPARTICIP -1; iparticip++)
        {
            strncpy(event.participants[iparticip], event.participants[iparticip + 1], MAX);
        }
        strncpy(event.participants[MAXPARTICIP - 1], "", MAX);
        eventTable[iroom][ievent] = event;
    }
}

