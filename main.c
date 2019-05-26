//  Leon Ferreira Bellini       RA: 22.218.002-8
//  Guilherme Ormond Sampaio    RA: 22.218.007-7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM_KU 9

typedef struct{
  unsigned short int **sudoku;
  unsigned short int solucao[9][9];
}joojenho;

unsigned short int numAleatorio(){
  time_t t;
  srand((unsigned) time(&t));
  return ((rand() % 3)+1);
}

void verificaVitoria(joojenho* ponteiro) {
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      if (ponteiro->sudoku[i][j] != ponteiro->solucao[i][j]) {
        puts("O jogo está incorreto! (errrou)");
        return;
      }
    }
  }
  puts("O jogo está correto! (yaaaay)");
}

char* menuTipoJogo(){
  int escolha;
  puts("\nOpções:\n1 - Jogo Fácil\n2 - Jogo Médio\n3 - Jogo Difícil\n");
  scanf("%d", &escolha);

  switch (escolha) {
    case 1: return "facil/";
    case 2: return "medio/";
    case 3: return "dificil/";
  }
}

void printarJogo(joojenho* sudosudo){
  puts("   1  2  3    4  5  6    7  8  9");
  for (size_t i = 0; i < 9; i++) {
    printf("%c", (97+i));
    for (size_t j = 0; j < 9; j++) {
      if (!(sudosudo->sudoku[i][j])) {
        printf("  ?");
      }
      else
        printf(" %2d", sudosudo->sudoku[i][j]);

      if (j == 2 || j == 5) {
        printf(" |" );
      }
    }
    puts("");
    if (i == 2 || i == 5) {
      puts("   --------+----------+---------");
    }
  }

  puts("");
}

void gravarJogo(joojenho* ku, char* dificuldade){
  char nomenho[40] = {0};
  char caminhoTexto[80] = "joojos/usuario/";
  char caminhoBin[80] = {0};

  strcat(caminhoTexto, dificuldade);

  puts("\nInsira o nome do arquivo que desejas gravar (inserir um nome já existente irá sobrescrever)\nMínimo 6 caracteres, máximo 14:");
  scanf(" %s", nomenho);

  strcat(caminhoTexto, nomenho);
  strcpy(caminhoBin, caminhoTexto);
  strcat(caminhoTexto, ".txt");
  strcat(caminhoBin, ".bin");

  FILE* jogoPraGravar = fopen(caminhoTexto, "w");
  FILE* jogoPraGravarBin = fopen(caminhoBin, "wb");

  fwrite(&ku->sudoku, sizeof(ku->sudoku[0][0]), sizeof(ku->sudoku), jogoPraGravarBin);

  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      fprintf(jogoPraGravar, "%d ", ku->sudoku[i][j]);
    }
    fprintf(jogoPraGravar, "\n");
  }

  fclose(jogoPraGravar);
  fclose(jogoPraGravarBin);

  puts("\nJogo gravado com sucesso!\n");
}

void jogarFora(joojenho * estrutura){
  for(int i = 0; i < TAM_KU; i++)
    free(estrutura->sudoku[i]);
  free(estrutura->sudoku);
}

void jogar(joojenho* sudosudo){
  char linha;
  int coluna, posicao;

  coluna = posicao = linha = 0;

  while (1) {
    printarJogo(sudosudo);

    puts("Insira a letra da linha e o número da coluna e o número que deseja jogar (insira \"0 0 0\" para sair e \"1 1 1\" para verificar vitória)");
    scanf(" %c %d %d", &linha, &coluna, &posicao);

    if (linha == '0' && coluna == 0 && posicao == 0)
      break;
    else if (linha == '1' && coluna == 1 && posicao == 1)
      verificaVitoria(sudosudo);
    else
      sudosudo->sudoku[linha-97][coluna-1] = posicao;
  }
}

void arquivo(joojenho* jo, char* caminho, char* caminhoSolucao){
  FILE* arquivoLeitura = fopen(caminho, "r");
  if(!arquivoLeitura)
    puts("erro");
  const char del[] = " ";
  char buffer[40];
  for(int i = 0; fgets(buffer, 40, arquivoLeitura); i++){
   char * ponteiro_str = strtok(buffer, del);
    for(int j = 0; ponteiro_str; ponteiro_str = strtok(NULL, del), j++){
       jo->sudoku[i][j] = strtol(ponteiro_str,NULL, 10);
      }
    }
  fclose(arquivoLeitura);

  arquivoLeitura = fopen(caminhoSolucao, "r");
  if(!arquivoLeitura)
    puts("erro");
  for(int i = 0; fgets(buffer, 40, arquivoLeitura); i++){
   char * ponteiro_str = strtok(buffer, del);
    for(int j = 0; ponteiro_str; ponteiro_str = strtok(NULL, del), j++){
       jo->solucao[i][j] = strtol(ponteiro_str,NULL, 10);
      }
    }
  fclose(arquivoLeitura);
}

char* leitura(joojenho* jooj, char* jogo, char caminhoTemp[50]){
  char caminho[50];
  char caminhoSolucao[50] = "joojos/solucao.txt";
  static char retorno[50] = {0};

  strcpy(caminho, caminhoTemp);

  strcat(retorno, menuTipoJogo());
  strcat(caminho, retorno);
  strcat(caminho, jogo);

  arquivo(jooj, caminho, caminhoSolucao);

  return retorno;
}

void inserirJogo(){
  joojenho sudosudo;
  char jogo[6], caminho[50];
  int gravar;

  sprintf(jogo, "%d", numAleatorio());
  strcat(jogo, ".txt");

  sudosudo.sudoku = malloc(sizeof(unsigned short int*) * TAM_KU);
  for(int i = 0; i < TAM_KU; i++)
    sudosudo.sudoku[i] = malloc(sizeof(unsigned short int) * TAM_KU);

  strcpy(caminho, leitura(&sudosudo, jogo, "joojos/"));
  printf("bugoou\n" );

  jogar(&sudosudo);

  printf("Você deseja gravar o seu jogo?\n0 - Não\n1 - Sim\n");
  scanf("%d", &gravar);

  if (gravar) {
    gravarJogo(&sudosudo, caminho);
  }
  jogarFora(&sudosudo);
}

void removerJogo() {
  char escolhaJogo[50], caminhoBin[80];
  char caminhoTexto[80] = "rm joojos/usuario/";

  strcat(caminhoTexto, menuTipoJogo());

  puts("Insira o nome do jogo que deseja excluir (sem a extensão, pois já excluirá o texto e o binário):");
  scanf(" %s", escolhaJogo);

  strcat(caminhoTexto, escolhaJogo);
  strcpy(caminhoBin, caminhoTexto);
  strcat(caminhoTexto, ".txt");
  strcat(caminhoBin, ".bin");

  system(caminhoTexto);
  system(caminhoBin);
}

void listarJogos() {
  puts("\nJogos Fáceis: ");
  system("ls joojos/usuario/facil");

  puts("\nJogos Médios: ");
  system("ls joojos/usuario/medio");

  puts("\nJogos Difíceis: ");
  system("ls joojos/usuario/dificil");
}

void editarJogo() {
  joojenho sudosudo;
  char escolhaJogo[40], caminho[50];
  int gravar;

  puts("Insira o nome do jogo que deseja editar (sem a extensão):");
  scanf(" %s", escolhaJogo);

  strcat(escolhaJogo, ".txt");

  sudosudo.sudoku = malloc(sizeof(unsigned short int*) * TAM_KU);
  for(int i = 0; i < TAM_KU; i++)
    sudosudo.sudoku[i] = malloc(sizeof(unsigned short int) * TAM_KU);

  strcpy(caminho, leitura(&sudosudo, escolhaJogo, "joojos/usuario/"));
  printf("chegou aqui\n" );
  jogar(&sudosudo);

  printf("Você deseja gravar o seu jogo?\n0 - Não\n1 - Sim\n");
  scanf("%d", &gravar);

  if (gravar) {
    gravarJogo(&sudosudo, caminho);
  }
  jogarFora(&sudosudo);
}

int main(int argc, char const *argv[]) {
  int escolha;
  puts("\nMenu:\n1 - Inserir Jogo\n2 - Listar Jogos\n3 - Remover Jogo\n4 - Alterar Jogo Gravado\n\n0 - Sair\n");
  scanf("%d", &escolha);

  switch (escolha) {
    case 0:
      return 0;
    case 1:
      inserirJogo(); break;
    case 2:
      listarJogos(); break;
    case 3:
      removerJogo(); break;
    case 4:
      editarJogo(); break;
    default:
      printf("Opção inválida\n"); break;
  }
  return 0;
}
