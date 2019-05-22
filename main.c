//  Leon Ferreira Bellini       RA: 22.218.002-8
//  Guilherme Ormond Sampaio    RA: 22.218.007-7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  unsigned short int esolha;
}joojenho;

unsigned short int numAleatorio(){
  time_t t;
  srand((unsigned) time(&t));
  return ((rand() % 3)+1);
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
  puts("\nOpções:\n1 - Inserir Jogo\n2 - Listar Jogos\n3 - Remover Jogo\n4 - Alterar Jogo Gravado\n5 - Buscar Jogo Gravado\n\n0 - Sair\n");

  scanf("%i", &escolha);

  switch (escolha) {
    case 0:
      return 0;
    case 1:
      break;
    case 2:
      listarJogos(); break;
    case 3:
      removerJogo(); break;
    case 4:
      break;
    case 5:
      break;
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
