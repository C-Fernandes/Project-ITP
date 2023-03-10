#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

#define false 0
#define true 1

char tiposDeNaipes[4][4] = {{"♥"},  // Copas
                            {"♦"},  // Ouros
                            {"♣"},  // Paus
                            {"♠"}}; // Espada

void debug(char *message)
{
  fprintf(stderr, "%s\n", message);
}

FILE *addCardFile(char vetor[], char endereco[MAX_LINE], char tipoAbertura[],
                  char caracterRemove[])
{
  FILE *file;
  char *variavel;
  file = fopen(endereco, tipoAbertura);
  if (file == NULL)
  {
    printf("Problemas ao abrir o arquivo\n");
  }

  variavel = strtok(vetor, " ");

  while (variavel != NULL && variavel[0] != ']')
  {
    fprintf(file, "%s\n", variavel);
    variavel = strtok(NULL, " ");
  }

  fclose(file);
  return file;
}

FILE *removerInfo(char info[], char endereco[], int quantCartas)
{
  int contadorRepeticoes = 0;
  char vetorCartas[quantCartas][8];
  FILE *file;
  char carta[6];
  int contador = 0;
  file = fopen(endereco, "r");

  for (int i = 0; i <= quantCartas; i++)
  {
    fscanf(file, "%s\n", carta);

    if ((strcmp(info, carta) == 0))
    {
      contadorRepeticoes++;
    }
    if ((strcmp(info, carta) != 0))
    {
      strcpy(vetorCartas[contador], carta);
      contador++;
    }
  }

  if (contadorRepeticoes > 1)
  {
    for (int i = 0; i < (contadorRepeticoes - 1); i++)
    {
      strcpy(vetorCartas[contador], info);
      contador++;
    }
  }

  fclose(file);
  file = fopen(endereco, "w");

  for (int i = 0; i < quantCartas; i++)
  {

    fprintf(file, "%s\n", vetorCartas[i]);
  }
  fclose(file);
  return file;
}

int verificarSeEhDez(char carta[])
{
  if (carta[0] == '1' && carta[1] == '0')
  {

    return true;
  }
  else
  {

    return false;
  }
}

void mudarNaipe(char carta[], char *naipeDaVez)
{
  char naipe[4];
  int ehDez;
  ehDez = verificarSeEhDez(carta);
  int i = 1;
  int valor = 5;
  int contador = 0;
  if (ehDez == true)
  {

    i = 2;
    valor = 6;
  }

  for (i; i < valor; i++)
  {
    naipe[contador] = carta[i];
    contador++;
  }
  strcpy(naipeDaVez, naipe);
}

void qualNaipe(char *naipeDaVez, int quantCartas)
{
  char naipeTeste[4];
  int qtdNaipes[] = {0, 0, 0, 0};

  FILE *arqCartas;
  char carta[6];
  int ehDez, valor, w, referencia = 4;

  for (int i = 0; i < 4; i++)
  {
    arqCartas = fopen("Arquivos/cartas.txt", "r");
    for (int k = 0; k < quantCartas; k++)
    {

      fscanf(arqCartas, "%s\n", carta);
      ehDez = verificarSeEhDez(carta);
      int ehIgual = 0;
      if (ehDez == true)
      {
        w = 2;
        valor = 6;
      }
      else
      {
        w = 1;
        valor = 5;
      }
      for (w; w < valor; w++)
      {
        naipeTeste[ehIgual] = carta[w];
        ehIgual++;
      }
      if (strcmp(naipeTeste, tiposDeNaipes[i]))
      {
        qtdNaipes[i]++;
      }
    }
    fclose(arqCartas);
  }
  int posicaoMaior = 0;

  for (int i = 0; i < (4-1); i++)
  {
    if (qtdNaipes[i] > qtdNaipes[i+1])
    {
      posicaoMaior = i ;
    }
  }

  strcpy(naipeDaVez, tiposDeNaipes[posicaoMaior]);
}

int main()
{
  FILE *arquivoCartas;

  char hand[MAX_LINE];
  char my_id[MAX_ID_SIZE];
  char cardTable[MAX_ACTION];
  char players[MAX_LINE];

  char naipeDaVez[4];
  int quantCartas = 7;
  char card[MAX_ID_SIZE];

  int verificardorNaipe;

  int ehDez = false, trocouNaipe = false;

  char endArqCartas[] = "Arquivos/cartas.txt";

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", players);
  scanf("YOU %s\n", my_id);
  scanf("HAND [ %[^\n]\n", hand);
  scanf("TABLE %s\n", cardTable);

  arquivoCartas = addCardFile(hand, "Arquivos/cartas.txt", "w\0", "]\0");

  // === PARTIDA ===

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];

  mudarNaipe(cardTable, &naipeDaVez);
  while (1)
  {
    int jogou = false;
    do
    {

      scanf("%s %s", action, complement);
      if (strcmp(complement, my_id) != 0)
      {
        if (jogou == true)
        {
          jogou = false;
        }
      }
      if (strcmp(action, "DISCARD") == 0)
      {
        trocouNaipe = false;
        jogou = true;
        strcpy(cardTable, complement);
        if ((complement[0] == 'A') || (complement[0] == 'C'))
        {
          scanf(" %s", naipeDaVez);
        }
        if ((complement[0] != 'A') && (complement[0] != 'C'))
        {
          mudarNaipe(complement, &naipeDaVez);
        }
      }
      else
      {
        mudarNaipe(cardTable, &naipeDaVez);
      }
      getchar();

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    if ((cardTable[0] == 'V' || cardTable[0] == 'C') && (jogou == true))
    {
      int quant = 0;
      if ((cardTable[0] == 'V'))
      {
        printf("BUY 2\n");
        quant = 2;
        quantCartas = quantCartas + 2;
      }
      if ((cardTable[0] == 'C'))
      {
        printf("BUY 4\n");
        quant = 4;
        quantCartas = quantCartas + 4;
      }
      for (int i = 0; i < quant; i++)
      {
        scanf("%s\n", hand);
        arquivoCartas = addCardFile(hand, endArqCartas, "a\0", NULL);
      }
    }
    else
    {

      arquivoCartas = fopen(endArqCartas, "r");
      if (arquivoCartas == NULL)
      {
        printf("Error ao abrir o arquivo\n");
      }

      ehDez = verificarSeEhDez(cardTable);

      int j = 0;

      while (j < quantCartas)
      {

        int valor = 5, i = 1;
        int testador = 0;
        char cartaTeste[6];

        fscanf(arquivoCartas, "%s\n", cartaTeste);

        if (ehDez == true)
        {
          valor = 6;
          i = 2;
          ehDez = verificarSeEhDez(cartaTeste);
        }

        if ((cartaTeste[0] == cardTable[0]) || (ehDez == true))
        {
         
          if ((cartaTeste[0] == 'A') || (cartaTeste[0] == 'C'))
          {
            qualNaipe(&naipeDaVez, quantCartas);
           

            printf("DISCARD %s %s\n", cartaTeste, naipeDaVez);
            trocouNaipe = true;
          }
          else
          {
            printf("DISCARD %s\n", cartaTeste);
            mudarNaipe(cardTable, &naipeDaVez);
          }

          strcpy(cardTable, cartaTeste);
          quantCartas--;
          removerInfo(cartaTeste, endArqCartas, quantCartas);
          j = quantCartas + quantCartas;
          break;
        }

        ehDez = verificarSeEhDez(cartaTeste);

        if (ehDez == false)
        {
          i = 1;
          valor = 5;
        }
        char naipeTeste[4];
        for (i; i < valor; i++)
        {
          naipeTeste[testador] = cartaTeste[i];
          testador++;
        }

        if (strcmp(naipeTeste, naipeDaVez) == 0)
        {
          if ((cartaTeste[0] == 'A') || (cartaTeste[0] == 'C'))
          {
            qualNaipe(&naipeDaVez, quantCartas);

            printf("DISCARD %s %s\n", cartaTeste, naipeDaVez);
            trocouNaipe = true;
          }
          else
          {
            printf("DISCARD %s\n", cartaTeste);
          }
          strcpy(cardTable, cartaTeste);

          quantCartas--;
          removerInfo(cartaTeste, endArqCartas, quantCartas);
          j = quantCartas + quantCartas;
          break;
        }
        j++;
      }
      fclose(arquivoCartas);

      if (j == quantCartas)
      {
        printf("BUY 1\n");
        scanf("%s\n", hand);
        arquivoCartas = addCardFile(hand, endArqCartas, "a\0", "]\0");
        quantCartas++;
      }
    }
  }

  return 0;
}