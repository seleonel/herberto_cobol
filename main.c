//  Leon Ferreira Bellini       RA: 22.218.002-8
//  Guilherme Ormond Sampaio    RA: 22.218.007-7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  unsigned short int sudoku[9][9];
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

void gravarJogo(joojenho* ku){
  char buffer[20];
  char nomenho[20] = {0};
  char nomenhoBin[30] = {0};

  puts("Insira o nome do arquivo que desejas gravar\nMínimo 6 caracteres, máximo 14");
  // scanf("%s", nomenho);
  while ((strcmp(fgets(buffer, sizeof(buffer), stdin), "\n")))
  {
      scanf("%s", nomenho);
  };


  strcpy(nomenhoBin, nomenho);
  strcat(nomenho, ".txt");
  strcat(nomenhoBin, "Bin.txt");


  FILE* jogoPraGravar = fopen(nomenho, "w");
  FILE* jogoPraGravarBin = fopen(nomenhoBin, "wb");


  fwrite(&ku->sudoku, sizeof(ku->sudoku[0][0]), sizeof(ku->sudoku), jogoPraGravarBin);

  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      fprintf(jogoPraGravar, " %2d", ku->sudoku[i][j]);
    }
    if (i == 2 || i == 5) {
      fprintf(jogoPraGravar, "\n");
    }
  }

  fclose(jogoPraGravar);
  fclose(jogoPraGravarBin);
}

int verificaJogo(joojenho* sus){
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      if (sus->sudoku[i][j] == 0) {
        return 0;
      }
    }
  }
  return 1;
}

void inserirJogo(){
  joojenho sudosudo;
  char linha;
  int coluna, posicao, escolha, gravar;

  escolha = menuTipoJogo();
  leitura(&sudosudo, escolha, numAleatorio());

  coluna = posicao = linha = 0;

  while (1) {
    printarJogo(&sudosudo);

    puts("Insira a letra da linha e o número da coluna e o número que deseja jogar");
    scanf("%c %d %d", &linha, &coluna, &posicao);

    sudosudo.sudoku[linha-97][coluna-1] = posicao;

    if (verificaJogo(&sudosudo)) {
      verificaVitoria(&sudosudo);
      printf("Você deseja gravar o seu jogo?\n0 - Não\n1 - Sim\n");
      scanf("%d", &gravar);

      if (gravar) {
        gravarJogo(&sudosudo);
      }
      break;
    }
  }
}

void listarTipos() {
  puts("Opções:\n1 - Jogo Fácil\n2 - Jogo Médio\n3 - Jogo Difícil\n\n0 - Sair\n");
}

void lerJogo(FILE** arquivo, int escolha, int numJogo, char operacao[]){
  char caminhoJogo[100];

  if (escolha == 1) {
    sprintf(caminhoJogo, "joojos/facil/%d.txt", numJogo);
  }
  else if (escolha == 2) {
    sprintf(caminhoJogo, "joojos/medio/%d.txt", numJogo);
  }
  else{
    sprintf(caminhoJogo, "joojos/dificil/%d.txt", numJogo);
  }

  *arquivo = fopen(caminhoJogo, operacao);
}

void removerJogo() {
  int escolhaTipo, escolhaJogo;
  listarTipos();
  scanf("%d", &escolhaTipo);

  if (escolhaTipo != 0) {
    puts("Insira o número do jogo que quer excluir:");
    scanf("%d", &escolhaJogo);

    FILE* arquivo;
    lerJogo(&arquivo, escolhaTipo, escolhaJogo, "w");
    fclose(arquivo);
  }
}

void listarJogos() {
  puts("\nJogos Fáceis: ");
  system("ls joojos/facil");

  puts("\nJogos Médios: ");
  system("ls joojos/medio");

  puts("\nJogos Difíceis: ");
  system("ls joojos/dificil");
}

void leitura(joojenho* jooj, int tipo, int jogo){
  char caminho[50];
  char caminhoSolucao[50];

  switch (tipo) {
    case 1: sprintf(caminho, "joojos/facil/%d.txt", jogo);
            sprintf(caminhoSolucao, "joojos/facil/solucao.txt");
            break;
    case 2: sprintf(caminho, "joojos/medio/%d.txt", jogo);
            sprintf(caminhoSolucao, "joojos/medio/solucao.txt");
            break;
    case 3: sprintf(caminho, "joojos/dificil/%d.txt", jogo);
            sprintf(caminhoSolucao, "joojos/dificil/solucao.txt");
            break;
  }


  FILE* arquivoLeitura = fopen(caminho, "r");
  if(!arquivoLeitura)
    puts("erro");
  const char del[] = " ";
  char buffer[40];
  for(int i = 0; fgets(buffer, 40, arquivoLeitura); i++){
   char * ponteiro_str = strtok(buffer, del);
    for(int j = 0; ponteiro_str; ponteiro_str = strtok(NULL, del), j++){
       jooj->sudoku[i][j] = strtol(ponteiro_str,NULL, 10);
      }
    }
  fclose(arquivoLeitura);

  arquivoLeitura = fopen(caminhoSolucao, "r");
  if(!arquivoLeitura)
    puts("erro");
  for(int i = 0; fgets(buffer, 40, arquivoLeitura); i++){
   char * ponteiro_str = strtok(buffer, del);
    for(int j = 0; ponteiro_str; ponteiro_str = strtok(NULL, del), j++){
       jooj->solucao[i][j] = strtol(ponteiro_str,NULL, 10);
      }
    }
  fclose(arquivoLeitura);
}

int menuTipoJogo(){
  int escolha;
  listarTipos();
  scanf("%i", &escolha);

  return escolha;
}

short int menu() {
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
      break;
    default:
      printf("Opção inválida\n"); break;
  }
  return 1;
}

int main(int argc, char const *argv[]) {
  short int retorno = 1;
  while(retorno){
    retorno = menu();
  }

  return 0;
}
