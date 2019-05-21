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

void lerJogo(short int escolha, short int numJogo, char operacao){
  char caminhoJogo[100];

  if (escolha) {
    sprintf(caminhoJogo, "joojos/facil/%d.txt", numJogo);
  }
  else if (escolha == 2) {
    sprintf(caminhoJogo, "joojos/medio/%d.txt", numJogo);
  }
  else{
    sprintf(caminhoJogo, "joojos/dificil/%d.txt", numJogo);
  }


  FILE* arquivo = fopen(caminhoJogo, operacao);
  fclose(arquivo);
}

void removerJogo() {
  return;
}

void jogoFacil(){
  lerJogo(1, numAleatorio(), "r");
}

void jogoMedio(){
  lerJogo(2, numAleatorio(), "r");
}

void jogoDificil(){
  lerJogo(3, numAleatorio(), "r");
}

void menuTipoJogo(){
  int escolha;
  puts("Opções:\n1 - Jogo Fácil\n2 - Jogo Médio\n3 - Jogo Difícil\n\n0 - Sair\n");

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

void menu() {
  int escolha;
  puts("Opções:\n1 - Inserir Jogo\n2 - Listar Jogos\n3 - Remover Jogo\n4 - Alterar Jogo Gravado\n5 - Buscar Jogo Gravado\n\n0 - Sair\n");

  scanf("%i", &escolha);

  switch (escolha) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      removerJogo(); break;
    case 4:
      break;
    case 5:
      break;
  }
}

int main(int argc, char const *argv[]) {
  menu();
  return 0;
}
