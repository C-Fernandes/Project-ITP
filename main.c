

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

#define false 0
#define true 1

char tiposDeNaipes[4][4] = {{"♥"}, {"♦"}, {"♣"}, {"♠"}};

void debug(char *message) { fprintf(stderr, "%s\n", message); }

FILE *addCardFile(char vetor[], char endereco[MAX_LINE], char tipoAbertura[],
                  char caracterRemove[])
{
  printf("entrou em addCardFile\n");

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
  printf("entrou em removerInfo\n");
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
  printf("entrou em verificarSeEhDez\n");
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
  printf("Entrou no mudar naipe\n");
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

// FUNÇÃO PARA VERIFICAR QUAL O MELHOR NAIPE PARA JOGAR:
void qualNaipe(char *naipeDaVez, int quantCartas)
{
  printf("entrou na função qualNaipe()\n");
  //  Melhor naipe a se jogar
  int qtdNaipes[] = {0, 0, 0, 0}; // vetor para verificar quantidade de cartas de cada naipe

  // Verificando quantas cartas de cada naipe o bot tem:

  FILE *arqCartas;
  char carta[6];
  int ehDez, valor, w, referencia = 4;

  for (int i = 0; i < 4; i++)
  {
    arqCartas = fopen("Arquivos/cartas.txt", "r");
    if (quantCartas == NULL)
    {
      printf("Error ao abrir arqCartas\n");
    }
    // printf("Entrou no primeiro for\n");

    // printf("NaipeDaVez: %s\n", tiposDeNaipes[i]);
    for (int k = 0; k < quantCartas; k++)
    {

      fscanf(arqCartas, "%s\n", carta);
      // printf("PrimeiraCarta: %s\n", carta);
      ehDez = verificarSeEhDez(carta);
      int ehIgual = 0;
      if (ehDez == true)
      {
        // printf("É dez\n");
        w = 2;
        valor = 6;
        referencia = 3;
      }
      else
      {
        // printf("Não é dez\n");
        w = 1;
        valor = 5;
        referencia = 4;
      }
      for (w; w < valor; w++)
      {
        if (tiposDeNaipes[i][ehIgual] == carta[w])
        {

          ehIgual++;
          // printf("É igual: %d\n", ehIgual);
        }
      }
      if (ehIgual == referencia)
      {
        qtdNaipes[i]++;
        // printf("Quant naipes[i] = %d\n", qtdNaipes[i]);
      }
    }
    fclose(arqCartas);
  }

  // printf("pASSOU AQUI\n");
  //  Comparando valores para saber qual dos naipes tem mais cartas:
  int posicaoMaior = 0;
  for (int i = 1; i < 4; i++)
  {
    if (qtdNaipes[i] < qtdNaipes[i - 1])
    {
      posicaoMaior = i - 1;
    }
    else
    {
      posicaoMaior = i;
    }
  }
  //  atribuindo char do naipe escolhido para a variavel melhorNaipe

  strcpy(naipeDaVez, tiposDeNaipes[posicaoMaior]);
}
int verificarNaipe(char carta[], char naipe[])
{
  printf("Entrou na função verificar naipe\n");
  int ehDez = verificarSeEhDez(carta);
  int i = 1, valor = 5, contador = 0;
  char naipeTeste[5];
  if (ehDez == true)
  {
    i = 2;
    valor = 6;
  }

  for (i; i < valor; i++)
  {
    // printf("Começou a comparaação\n");
    naipeTeste[contador] = carta[i];
    contador++;
    // printf("contador: %d\n", contador);
  }
  printf("%s\n", naipeTeste);
  printf("%s\n", naipe);
  // printf("Chegou aqui\n");
  printf("Naipe teste: %s | naipe : %s\n", naipeTeste, naipe);
  if (strcmp(naipeTeste, naipe) == 0)
  {
    printf("retornou TRUE\n");
    return true;
  }

  printf("retornou FALSE\n");
  return false;
}
int verificarSeTemCouV(int quantCartas, char *cartaTeste, char naipeDaVez[])
{
  printf("Entrou em verificar se é c ou v\n");
  FILE *arqcartas;
  char carta[6];
  arqcartas = fopen("Arquivos/cartas.txt", "r");
  printf("\nVerificar se é C\n\n");
  for (int i = 0; i < quantCartas; i++)
  {

    fscanf(arqcartas, "%s\n", carta);
    printf("Carta: %s\n", carta);
    if (carta[0] == 'C')
    {
      int teste = verificarNaipe(carta, naipeDaVez);
      if (teste)
      {
        printf("Entrou nos dois if\n");
        strcpy(cartaTeste, carta);
        return 1;
      }
    }
  }
  fclose(arqcartas);
  arqcartas = fopen("Arquivos/cartas.txt", "r");
  printf("\nVerificar se é v\n\n");
  for (int i = 0; i < quantCartas; i++)
  {

    fscanf(arqcartas, "%s\n", carta);
    printf("Carta: %s\n", carta);
    if (carta[0] == 'V')
    {
      int teste = verificarNaipe(carta, naipeDaVez);
      if (teste)
      {
        printf("Entrou nos dois if\n");
        strcpy(cartaTeste, carta);
        return 2;
      }
    }
  }
  fclose(arqcartas);
  printf("saindo de verificar se tem C ou V\n");

  return false;
}

int main()
{
  FILE *arquivoCartas, *arquivoCartasPlayers;

  char hand[MAX_LINE];
  char my_id[MAX_ID_SIZE];
  char cardTable[MAX_ACTION];
  char players[MAX_LINE];

  char naipeDaVez[4];
  int quantCartas = 7;
  char card[MAX_ID_SIZE];

  int quantRodadas = 0;
  int verificardorNaipe;

  int ehDez = false, jaFoiComprado = false, trocouNaipe = false;

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

      quantRodadas++;
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
        printf("If Discard, Trocou naipe = false\n");
        jogou = true;
        strcpy(cardTable, complement);
        jaFoiComprado == false;
        if ((complement[0] == 'A') || (complement[0] == 'C'))
        {

          scanf(" %s", naipeDaVez);
          printf("Pegou naipe\n");
        }
        if ((complement[0] != 'A') && (complement[0] != 'C'))
        {
          printf("Entrou no segundo if\n");
          mudarNaipe(complement, &naipeDaVez);
          printf("Mudou naipe\n");
        }
      }
      else
      {
        if (strcmp(action, "TURN") != 0)
        {
          if (trocouNaipe == false)
          {
            printf("Entrou nos if depois do else");
            printf("Trocou naipe false\n");
            mudarNaipe(cardTable, &naipeDaVez);
            printf("Mudou naipe\n");
          }
        }
      }

      getchar();

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    // agora é a vez do seu bot jogar
    debug("----- MINHA VEZ -----");

    debug("Teste debug\n");

    if ((cardTable[0] == 'V') && (jogou == true))
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

      printf("Entrou no else\n");

      arquivoCartas = fopen(endArqCartas, "r");
      if (arquivoCartas == NULL)
      {
        printf("Error ao abrir o arquivo\n");
      }
      printf("Abriu o arquivo\n");

      printf("Passou da função ehDez\n");
      printf("É dez: %d\n", ehDez);
      int j = 0;
      char cartaTeste[6];
      printf("Quant Cartas: %d\n", quantCartas);
      int temCouV = verificarSeTemCouV(quantCartas, cartaTeste, naipeDaVez);
      printf("Retorno função: %d", temCouV);
      if (temCouV == 1)
      {

        qualNaipe(&naipeDaVez, quantCartas);
        printf("DISCARD %s %s\n", cartaTeste, naipeDaVez);
        quantCartas--;
        removerInfo(cartaTeste, endArqCartas, quantCartas);
        trocouNaipe == true;
      }
      if (temCouV == 2)
      {
        printf("DISCARD %s\n", cartaTeste);
        quantCartas--;
        removerInfo(cartaTeste, endArqCartas, quantCartas);
      }
      else
      {
        arquivoCartas = fopen(endArqCartas, "r");
        if (arquivoCartas == NULL)
        {
          printf("Error ao abrir o arquivo\n");
        }
        while (j < quantCartas)
        {

          printf("Entrou no while\n");
          int valor = 5, i = 1;

          int testador = 0;

          fscanf(arquivoCartas, "%s\n", cartaTeste);
          ehDez = verificarSeEhDez(cardTable);

          if (ehDez == true)
          {
            printf("É dez: %d\n", ehDez);
            valor = 6;
            i = 2;
            ehDez = verificarSeEhDez(cartaTeste);
            printf("É dez depois da função: %d\n", ehDez);
          }

          printf("Carta teste: %c || cardTable: %c\n", cartaTeste[0], cardTable[0]);
          if (((cartaTeste[0] == cardTable[0])) || (ehDez == true))
          {

            printf("Entrou na fução if\n");
            printf("Carta teste [0]: %c\n", cartaTeste[0]);
            debug("Passou do printf");
            if ((cartaTeste[0] == 'A'))
            {
              debug("Entrou aqui");
              printf("DISCARD %s %s\n", cartaTeste, naipeDaVez);
              trocouNaipe == true;
              printf("Trocou naipe = true\n");
            }
            else
            {
              printf("DISCARD %s\n", cartaTeste);
              mudarNaipe(cardTable, &naipeDaVez);
            }

            printf("Cardtable antes da função: %s\n", cardTable);
            strcpy(cardTable, cartaTeste);

            printf("Cardtable depois da função: %s\n", cardTable);
            quantCartas--;
            removerInfo(cartaTeste, endArqCartas, quantCartas);
            j = quantCartas + quantCartas;
            break;
          }
          printf("Carta teste: %s || Naipe da vez: %s\n", cartaTeste, naipeDaVez);

          int verificacao = verificarNaipe(cartaTeste, naipeDaVez);

          if (verificacao == true)
          {
            printf("Carta teste [0]: %c\n", cartaTeste[0]);

            if (cartaTeste[0] == 'A')
            {
              printf("Entrou aqui\n");
              qualNaipe(&naipeDaVez, quantCartas);
              printf("DISCARD %s %s\n", cartaTeste, naipeDaVez);
              trocouNaipe = true;
              printf("Trocou naipe = true\n");
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
          printf("Valor j: %d\n", j);
          printf("Passou daqui\n");
          if (j == quantCartas){
            printf("BUY 1\n");
            scanf("%s\n", hand);
            arquivoCartas = addCardFile(hand, endArqCartas, "a\0", "]\0");
            quantCartas++;

            printf("Passou no ultimo if %d\n", quantCartas);
            break;
          }
          printf("Passou do if\n");
        }
        fclose(arquivoCartas);
      }
    }
  }
  return 0;
}