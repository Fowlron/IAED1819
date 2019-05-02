/******************************************************************************
 * Projeto 1 IAED1819: proj1.h                                                *
 * Neste projeto, tenciona-se criar um sistema de reserva de salas, com o     *
 * qual se deve interagir atraves de comandos definidos no enunciad do        *
 * projeto.                                                                   *
 *                                                                            *
 * Este ficheiro contem a declaracao das funcoes utilizadas ao longo do       *
 * projeto (primeiro as auxiliares, depois as que representam um comando do   *
 * utilizador), bem como a documentacao de cada funcao.                       *
 *                                                                            *
 * Projeto de: Pedro Godinho - 93608 - LETI                                   *
 *                                                                            *
 *****************************************************************************/

#ifndef PROJ_H_
#define PROJ_H_

/* Tamanho maximo de strings, definido para 64 para incluir a null-character */
#define MAX 64

#define MAXROOMS 11 /* O numero maximo de salas aceite (10+1 para indice 10 existir) */
#define MAXEVENTS 100 /* O numero maximo de eventos aceites por sala */
#define MAXPARTICIP 3 /* O numero maximo de participantes por evento */

/* estrutura que representa uma data e hora */
typedef struct time
{
    int year;
    int month;
    int day;
    int h;
    int m;
} Time;

/* estrutura que representa cada evento que o sistema pode manipular */
typedef struct event
{
    char description[MAX]; /* descricao unica do evento */
    Time startTime; /* momento de comeco do evento */
    int duration; /* duracao do evento em minutos */
    int room; /* a sala em que o event ocorre */
    char host[MAX]; /* responsavel pelo evento */
    char participants[MAXPARTICIP][MAX]; /* lista de participantes no evento */
} Event;

/* representa a localizacao de um evento na tabela de eventos. Usado como valor
 * valor de retorno de algumas funcoes */
typedef struct roomEventPair
{
    int room;
    int event;
} RoomEventPair;


/******************************************************************************
 *                                                                            *
 *                                  Funcoes                                   *
 *                                                                            *
 *****************************************************************************/


/******************************************************************************
 * Funcao que inicializa todos os eventos como eventos nulos.
 *****************************************************************************/
void initializeTable();


/******************************************************************************
 * Uma funcao auxiliar que faz o evento numa determinada sala nulo (todos os
 * campos numericos passam a -1 e todos as strings passam a "").
 *
 * Arguments:
 *      int iroom: the room's index
 *      int ievent: the event's index
 *****************************************************************************/
void nullEvent(int iroom, int ievent);


/******************************************************************************
 * Funcao que escreve um evento.
 *
 * Arguments:
 *      Event event: o evento a escrever
 *****************************************************************************/
void printEvent(Event event);


/******************************************************************************
 * Esta funcao le inputs ate ao proximo caracter c, ou ate encontrar \n ou EOF.
 *
 * Arguments:
 *      char c: o caracter onde para a leitura
 *      char str[]: a string onde guardar os caracteres lidos
 * 
 * Returns:
 *      int: 1 se encontrou EOF ou \n, 0 caso contrario
 *****************************************************************************/
int readStrUntilNextChar(char c, char str[]);


/******************************************************************************
 * Esta funcao transforma ints no formato ddmmyyyy e hhmm para um unico Time.
 *
 * Arguments:
 *      int date: a data (ddmmyyyy)
 *      int start: a hora de comeco (hhmm)
 *
 * Returns:
 *      Time: o tempo correspondente
 ******************************************************************************/
Time inputsToTime(int date, int start);


/******************************************************************************
 * Uma funcao auxiliar que transforma o tempo para minutos do dia, ignorando a 
 * data.
 *
 * Arguments:
 *      Time time: o tempo
 *
 * Returns:
 *      int: o tempo em minutos
 *****************************************************************************/
int timeToMinutes(Time time);


/******************************************************************************
 * Esta funcao verifica se os horarios de dois eventos estao em conflito.
 *
 * Returns:
 *      int: 1 se os horarios entram em conflito, 0 caso contrario
 *****************************************************************************/
int doEventDatesConflict(Event event1, Event event2);


/******************************************************************************
 * Esta funcao usa bubblesort para organizar uma lista de eventos por data
 * primeiro, depois por hora de comeco, depois por sala.
 * Nao ignora eventos nulos! Assume-se que a lista recebida nao contem
 * eventos invalidos. 
 *
 * Arguments:
 *      Event event[]: a array a organizar
 *      int len: o tamanho da array recebida
 *****************************************************************************/
void eventBubbleSort(Event events[], int len);


/******************************************************************************
 * Funcao auxiliar de eventBubbleSort para simplificar a troca de 2 elementos
 * de uma array de eventos.
 *
 * Arguments:
 *      Event events[][]: Os eventos onde trocar
 *****************************************************************************/
void swapInEventArray(Event events[], int i, int j);


/******************************************************************************
 * Funcao auxiliar que encontra um evento na tabela de eventos atraves da sua
 * descricao. 
 *
 * Returns:
 *      RoomEventPair: Um par com a sala e o indice do evento do evento
 *                     procurado, ou -1, -1 se este nao existir.
 *****************************************************************************/
RoomEventPair findEventByDescription(char description[MAX]);


/******************************************************************************
 * Funcao auxiliar que verifica se um evento entra em conflicto com qualquer
 * outro evento na tabela. No caso de entrar em conflict, para alem de retornar
 * 0, vai imprimir o erro no stdout, no formato "<errorMsg> <razao do erro>". 
 *
 * Arguments:
 *      Event event: o evento a verificar
 *      char errorMsg[MAX]: O principio da mensagem de erro
 *
 * Returns:
 *      int: 0 se entra em conflicto com algum evento previo, 1 caso contrario
 *****************************************************************************/
int isEventValidInTable(Event event, char errorMsg[MAX]);


/******************************************************************************
 * Todas as funcoes que se seguem leem os parametros de que precisam do buffer*
 * (quando representam comandos que precisam de parametros), fazem os prints  *
 * necessarios elas proprias, e podem alterar diretamente a variavel global   *
 * eventTable (declarada no ficheiro proj1.c).                                *
 *****************************************************************************/


/******************************************************************************
 * A principal funcao responsavel pelo comando a.
 *
 * Esta funcao le os parametros:
 *      descricao:data:inicio:duracao:sala:responsavel:participantes
 * A funcao adiciona a tabela de eventos um evento de acordo com os parametros
 * lidos.
 *
 * Obtem-se um erro caso o horario do evento a agendar se intercete com o 
 * horario de outro evento ja agendado na mesma sala, ou caso um dos
 * participantes ou o responsavel tenham algum evento sobreposto noutra sala.
 *****************************************************************************/
void addEvent();


/******************************************************************************
 * A principal funcao responsavel pelo comando l.
 * 
 * Esta funcao lista todos os eventos por ordem cronologica. Caso dois eventos
 * se iniciem ao mesmo tempo, sao listados por ordem crescente do numero da 
 * sala.
 *****************************************************************************/
void listEvents();


/******************************************************************************
 * A principal funcao responsavel pelo comando s.
 *
 * Esta funcao lista todos os eventos numa sala por ordem cronologica.
 *****************************************************************************/
void listEventsInRoom();


/******************************************************************************
 * A principal funcao responsavel pelo comando r.
 *
 * Esta funcao le os parametros:
 *      descricao
 * A funcao remove da tabela um evento com a descricao igual a dada.
 *
 * Obtem-se um erro caso nao exista nenhum evento com a descricao dada.
 *****************************************************************************/
void deleteEvent();


/******************************************************************************
 * A principal funcao responsavel pelo comando i.
 *
 * Esta funcao le os parametros:
 *      descricao:novo_inicio
 * A funcao altera o inicio do evento com a descricao dada, se este existir
 * e se este nao estiver em conflito com outros eventos ja agendados.
 *
 * Obtem-se erro case nao exista nenhum evento com a descricao dada, o horario
 * do evento a agendar se intercete com o de um ja agendado na mesma sala, ou
 * caso um dos participantes ou o responsavel tenham algum evento sobreposto
 * noutra sala. 
 *****************************************************************************/
void changeStartTime();


/******************************************************************************
 * A principal funcao responsavel pelo comando t.
 *
 * Esta funcao le os parametros:
 *      descricao:nova_duracao
 * A funcao altera a duracao do evento com a descricao dada, se este existir
 * e se este nao estiver em conflito com outros eventos ja agendados.
 *
 * Obtem-se erro case nao exista nenhum evento com a descricao dada, o horario
 * do evento a agendar se intercete com o de um ja agendado na mesma sala, ou
 * caso um dos participantes ou o responsavel tenham algum evento sobreposto
 * noutra sala. 
 *****************************************************************************/
void changeDuration();


/******************************************************************************
 * A principal funcao responsavel pelo comando m.
 *
 * Esta funcao le os parametros:
 *      descricao:nova_sala
 * A funcao altera a sala do evento com a descricao dada, se este existir
 * e se este nao estiver em conflito com outros eventos ja agendados.
 *
 * Obtem-se erro case nao exista nenhum evento com a descricao dada, o horario
 * do evento a agendar se intercete com o de um ja agendado na mesma sala, ou
 * caso um dos participantes ou o responsavel tenham algum evento sobreposto
 * noutra sala. 
 *****************************************************************************/
void changeRoom();


/******************************************************************************
 * A principal funcao responsavel pelo comando A.
 *
 * Esta funcao le os parametros:
 *      descricao:novo_participante
 * A funcao adiciona ao evento com a descricao dada um participante com o nome
 * dado, se isto nao entrar conflitos com outros eventos ja agendados, se o 
 * participante ainda nao estiver no evento, e se houver espaco para o novo
 * participante no evento.
 *
 * Obtem-se erro case nao exista nenhum evento com a descricao dada, o evento
 * ja estaja no limite de participantes, ou o participante a adicionar ja
 * esteja nalgum outro evento cujo horario nao seja compativel com o deste
 * evento. 
 *****************************************************************************/
void addParticipant();


/******************************************************************************
 * A principal funcao responsavel pelo comando R.
 *
 * Esta funcao le os parametros:
 *      descricao:participante_a_remover
 * A funcao remove o participate a remover do evento com a descricao dada,
 * case esta exista e este esteja nesse evento (sem ser o seu unico
 * participante).
 *
 * Obtem-se erro case nao exista nenhum evento com a descricao dada, ou o
 * participante a remover seja o unico participante no evento.
 *****************************************************************************/
void removeParticipant();


#endif

