/*
    "COMPRE 4"   : C = CORINGA
    "COMPRE 2"   : V = VALETE
    "VOLTA"      : D = DAMA
    "PULA A VEZ" : R = REI
    "MUDE A COR" : A = ÀS (muda o naipe)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Constantes para as strings a serem lidas */
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

#define false 0
#define true 1

char tiposDeNaipes[4][4] = {{"♥"}, {"♦"}, {"♣"}, {"♠"}};

void debug(char *message) { fprintf(stderr, "%s\n", message); }

FILE *addCardFile(char vetor[], char endereco[MAX_LINE], char tipoAbertura[],
                  char caracterRemove[]) {
  // printf("entrou em addCardFile\n");
  // printf("%s\n", vetor);
  FILE *file;
  char *variavel;
  // printf("Antes de abrir arquivo");
  file = fopen(endereco, tipoAbertura);
  // printf("abriu o arquivo\n");
  if (file == NULL) {
    printf("Problemas ao abrir o arquivo\n");
  }

  variavel = strtok(vetor, " ");

  while (variavel != NULL && variavel[0] != ']') {
    fprintf(file, "%s\n", variavel);

    variavel = strtok(NULL, " ");
  }
  // printf("Saiu do while\n");

  fclose(file);
  return file;
}

FILE *removerInfo(char info[], char endereco[], int quantCartas) {
  // printf("entrou em removerInfo\n");
  char vetorCartas[quantCartas][8];
  FILE *file;
  char carta[8];
  int contador = 0;
  file = fopen(endereco, "r");

  for (int i = 0; i <= quantCartas; i++) {
    fscanf(file, "%s\n", carta);
    if (strcmp(info, carta) != 0) {
      strcpy(vetorCartas[contador], carta);
      contador++;
    }
  }
  fclose(file);
  file = fopen(endereco, "w");

  for (int i = 0; i < quantCartas; i++) {
    fprintf(file, "%s\n", vetorCartas[i]);
    // printf("Adicionou: %s\n", vetorCartas[i]);
  }
  fclose(file);
  return file;
}

int verificarSeEhDez(char carta[]) {
  // printf("entrou em verificarSeEhDez\n");
  if (carta[1] == 0 && carta[0] == 1) {
    return true;
  } else {
    return false;
  }
  // printf("saiu de verificarSeEhDez");
}

void mudarNaipe(char carta[], char *naipeDaVez) {
  // printf("Entrou no mudar naipe\n");
  char naipe[4];
  int ehDez = false;
  ehDez = verificarSeEhDez(carta);
  int i = 1;
  int valor = 5;
  int contador = 0;
  if (ehDez == true) {
    i = 2;
    valor = 6;
  }

  for (i; i < valor; i++) {
    naipe[contador] = carta[i];
    contador++;
  }
  strcpy(naipeDaVez, naipe);
  // printf("Sainda naipe função: %s\n", naipeDaVez);
}

// FUNÇÃO PARA VERIFICAR QUAL O MELHOR NAIPE PARA JOGAR:
char *qualNaipe(char *naipeDaVez, char **hand, int quantCartas) {
  char melhorNaipe[4]; // Melhor naipe a se jogar
  int qtdNaipes[] = {0, 0, 0, 0}; // vetor para verificar quantidade de cartas de cada naipe

  // Verificando quantas cartas de cada naipe o bot tem:
  int i = 0;
  while (i < 4) {
    for (int j = 0; j < quantCartas; j++) {
      int ehIgual = 0;
      for (int k = 0; k < 4; k++) {
        if (strcmp(&hand[j][k], &naipeDaVez[k]) == 0) {
          ehIgual++;
        }
        if (ehIgual == 4) {
          qtdNaipes[i]++;
        }
      }
    }
  }

  // Comparando valores para saber qual dos naipes tem mais cartas:
  int posicaoMaior = 0;
  for (int i = 1; i < 4; i++) {
    if (qtdNaipes[i] > qtdNaipes[i - 1]) {
      posicaoMaior = i;
    }
  }

  // atribuindo char do naipe escolhido para a variavel melhorNaipe
  for (int i = 0; i < 4; i++) {
    melhorNaipe[i] = tiposDeNaipes[posicaoMaior][i];
  }

  return melhorNaipe;
}

int main() {
  FILE *arquivoCartas, *arquivoCartasPlayers;

  char hand[MAX_LINE];
  char my_id[MAX_ID_SIZE];
  char cardTable[MAX_ACTION];
  char players[MAX_LINE];

  char naipeDaVez[4];
  int quantCartas = 7;
  char card[MAX_ID_SIZE];

  int quantRodadas = 0;

  int ehDez = false, jaFoiComprado = false;

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
  while (1) {
    int jogou = false;
    do {

      quantRodadas++;
      scanf("%s %s", action, complement);

      if (strcmp(action, "DISCARD") == 0) {
        jogou = true;
        strcpy(cardTable, complement);
        jaFoiComprado == false;
        if ((complement[0] == 'A') || (complement[0] == 'C')) {

          scanf("%s", naipeDaVez);
          // printf("Naipe: %s\n", naipeDaVez);
        }
        if ((complement[0] != 'A') && (complement[0] != 'C')) {
          // printf("Entrou no segundo if\n");
          mudarNaipe(complement, &naipeDaVez);

          // printf("Naipe diferente:  %s\n", naipeDaVez);
        }
      } else {
        if (strcmp(action, "TURN") != 0) {
          // printf("Entrou no else antes do mudarNaipe\n");
          mudarNaipe(cardTable, &naipeDaVez);
        }
      }
      if (strcmp(action, "") == 0) {
        quantRodadas = 0;
      }
      getchar();

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));

    // agora é a vez do seu bot jogar
    debug("----- MINHA VEZ -----");

    if ((cardTable[0] == 'V' || cardTable[0] == 'C')) {
      int quant = 0;
      if ((cardTable[0] == 'V') && (jogou == true)) {
        printf("BUY 2\n");
        quant = 2;
        quantCartas = quantCartas + 2;
        jogou = false;
      }
      if ((cardTable[0] == 'C') && (jogou == true)) {
        printf("BUY 4\n");
        quant = 4;
        quantCartas = quantCartas + 4;
        jogou = false;
      }
      for (int i = 0; i < quant; i++) {
        scanf("%s\n", hand);
        arquivoCartas = addCardFile(hand, endArqCartas, "a\0", NULL);
      }
    } else {

      // printf("Entrou no else\n");

      arquivoCartas = fopen(endArqCartas, "r");
      if (arquivoCartas == NULL) {
        printf("Error ao abrir o arquivo\n");
      }
      // printf("Abriu o arquivo\n");
      ehDez = verificarSeEhDez(cardTable);
      // printf("Passou da função ehDez\n");
      // printf("É dez: %d\n", ehDez);
      int j = 0;
      // printf("Quant Cartas: %d\n", quantCartas);
      while (j < quantCartas) {
        // printf("Entrou no while\n");
        int valor = 5, i = 1;

        int testador = 0;
        char cartaTeste[6];
        // printf("Passa aqui\n");

        fscanf(arquivoCartas, "%s\n", cartaTeste);
        // printf("Depois do fscanf\n");
        if (ehDez == true) {

          // printf("É dez: %d\n", ehDez);
          ehDez = verificarSeEhDez(cartaTeste);
          // printf("É dez depois da função: %d\n", ehDez);
        }

        // printf("Carta teste: %c || cardTable: %c\n", cartaTeste[0],
        // cardTable[0]);
        if (((cartaTeste[0] == cardTable[0]) && cartaTeste[1] != '0') ||
            (ehDez == true)) {

          // printf("Entrou na fução if\n");
          // printf("Carta teste [0]: %c\n", cartaTeste[0]);
          // debug("Passou do printf");
          if ((cartaTeste[0] == 'A') || (cartaTeste[0] == 'C')) {
            debug("Entrou aqui");
            char simbolo[] = "♥";
            printf("DISCARD %s %s\n", cartaTeste, simbolo);
          } else {
            printf("DISCARD %s\n", cartaTeste);
          }

          // printf("Cardtable antes da função: %s\n", cardTable);
          strcpy(cardTable, cartaTeste);
          mudarNaipe(cardTable, &naipeDaVez);
          // printf("Cardtable depois da função: %s\n", cardTable);
          quantCartas--;
          removerInfo(cartaTeste, endArqCartas, quantCartas);
          j = quantCartas + 1;
          break;
        }
        // printf("Carta teste: %s || Naipe da vez: %s\n", cartaTeste,
        // naipeDaVez);
        for (i; i < valor; i++) {
          if (cartaTeste[i] == naipeDaVez[testador]) {
            testador++;
          }
          // printf("Testador: %d\n", testador);
        }

        if (testador == 4) {
          // printf("Carta teste [0]: %c\n", cartaTeste[0]);

          if ((cartaTeste[0] == 'A') || (cartaTeste[0] == 'C')) {
            // printf("Entrou aqui\n");

            char simbolo[] = "♥";
            printf("DISCARD %s %s\n", cartaTeste, simbolo);
          } else if ((cartaTeste[0] != 'A') && (cartaTeste[0] != 'C')) {
            printf("DISCARD %s\n", cartaTeste);
          }
          strcpy(cardTable, cartaTeste);

          quantCartas--;
          removerInfo(cartaTeste, endArqCartas, quantCartas);
          j = quantCartas + 1;
          break;
        }
        j++;
        //  printf("Valor j: %d\n", j);
      }

      fclose(arquivoCartas);
      if (j == quantCartas) {
        printf("BUY 1\n");
        scanf("%s\n", hand);
        // printf("Hand: %s\n", hand);
        arquivoCartas = addCardFile(hand, endArqCartas, "a\0", "]\0");
        quantCartas++;
        // printf("Passou no ultimo if %d\n", quantCartas);
      }
    }
  }

  return 0;
}