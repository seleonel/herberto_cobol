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

void printarJogo(joojenho* sudosudo){
  puts("   1  2  3    4  5  6    7  8  9");
  for (size_t i = 0; i < 9; i++) {
    printf("%c", (97+i));
    for (size_t j = 0; j < 9; j++) {
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
  int coluna, posicao;

  coluna = posicao = linha = 0;

  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      sudosudo.sudoku[i][j] = 0;
    }
  }

  while (1) {
    printarJogo(&sudosudo);

    puts("Insira a letra da linha e o número da coluna e o número que deseja jogar");
    scanf("%c %d %d", &linha, &coluna, &posicao);

    sudosudo.sudoku[linha-97][coluna-1] = posicao;

    if (verificaJogo(&sudosudo)) {
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

void jogoFacil(){
  FILE* arquivo;
  lerJogo(&arquivo, 1, numAleatorio(), "r");
  fclose(arquivo);
}

void jogoMedio(){
  FILE* arquivo;
  lerJogo(arquivo, 2, numAleatorio(), "r");
  fclose(arquivo);
}

void jogoDificil(){
  FILE* arquivo;
  lerJogo(arquivo, 3, numAleatorio(), "r");
  fclose(arquivo);
}

void menuTipoJogo(){
  int escolha;
  listarTipos();
  scanf("%i", &escolha);

  switch (escolha) {
    case 0:
      break;
    case 1:
      jogoFacil(); break;
    case 2:
      jogoMedio(); break;
    case 3:
      jogoDificil(); break;
  }
}

short int menu() {
  int escolha;
  puts("\nMenu:\n1 - Inserir Jogo\n2 - Listar Jogos\n3 - Remover Jogo\n4 - Alterar Jogo Gravado\n\n0 - Sair\n");

  scanf("%i", &escolha);

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
  while(1){
    retorno = menu();
    if (!retorno) {
      break;
    }
  }

  return 0;
}
