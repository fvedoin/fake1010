// Laboratório I de Programação
//
// Programa de exemplo para o trabalho 5
//
// Necessita os arquivos t5.c (este), tela.h, tela.c e DejaVuSans.ttf
// Necessita ter instalado a biblioteca allegro5
//
// para compilar este programa, use este comando:
// gcc -Wall -o t5 t5.c tela.c -lallegro_font -lallegro_color -lallegro_ttf -lallegro_primitives -lallegro
//


#include "tela.h"

#include <stdio.h>
#include <stdbool.h>

const int LARGURA_TELA = 560;
const int ALTURA_TELA = 640;

// função auxiliar usada por main, definida abaixo
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5]);

// A função principal
int main(void)
{
  // inicializa a tela gráfica
  tela_inicio(LARGURA_TELA, ALTURA_TELA, "tsinc");

  // o tabuleiro e as peças
  int m[10][10];
  int p1[5][5];
  int p2[5][5];
  int p3[5][5];

  // poe uns valores no tabuleiro e nas peças, para demo
  int i, j;
  for (i=0; i<10; i++) {
    for (j=0; j<10; j++) {
      m[i][j] = 0;
    }
  }
  m[5][5] = 1;
  m[5][6] = 1;
  m[5][7] = 1;

  for (i=0; i<5; i++) {
    for (j=0; j<5; j++) {
      p1[i][j] = 0;
      p2[i][j] = 0;
      p3[i][j] = 0;
    }
  }
  p1[0][0] = 1;
  p1[0][1] = 1;
  p1[0][2] = 1;
  p2[1][1] = p2[2][1] = p2[3][1] = p2[3][2] = p2[3][3] = 1;
  p3[2][2] = 1;

  while (true) {
    desenha_tela(m, p1, p2, p3);
  }

  tela_fim();

  return 0;
}



// funções auxiliares usadas por desenha_tela, definidas abaixo
void desenha_principal(int m[10][10], float x_ini, float y_ini, float lado);
void desenha_peca(int p[5][5], float x_ini, float y_ini, float lado);
void desenha_pecas(int p1[5][5], int p2[5][5], int p3[5][5]);


// função que desenha uma tela
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5])
{
  tela_inicia_desenho();
  float largura_matriz_principal = LARGURA_TELA*0.8/10; //isso eh igual a 44.8
  desenha_principal(m, LARGURA_TELA*0.1, ALTURA_TELA*0.05, largura_matriz_principal);
  desenha_pecas(p1, p2, p3);
  float largura_quadrado_matriz = largura_matriz_principal/10; //isso eh igual a 4.48
  if (tela_rato_apertado()) {
    char texto[20];
    sprintf(texto, "oi %f--%f",largura_quadrado_matriz,largura_quadrado_matriz*10);
    tela_texto(tela_rato_x(),tela_rato_y(),10,amarelo,texto);
    tela_circulo(tela_rato_x(), tela_rato_y(), 5, 2, amarelo, transparente);;
  } else {
    tela_circulo(tela_rato_x(), tela_rato_y(), 3, 1, marrom, transparente);
  }
  tela_termina_desenho();
}



// Desenha o tabuleiro principal
// Ele é formado por uma matrix 10x10, com os valores 0 representando posições
// livres.
void desenha_principal(int m[10][10], float x_ini, float y_ini, float lado)
{
  int cor;
  int i, j;
  for (i=0; i < 10; i++) {
    for (j=0; j < 10; j++) {
      // Se houver peça, colorir a célula da matriz
      // No jogo real, as células podem cores variadas
      if (m[i][j] == 0) {
        cor = transparente;
      } else {
        cor = azul;
      }
      tela_retangulo(x_ini + i*lado, y_ini + j*lado,
                     x_ini + (i+1)*lado, y_ini + (j+1)*lado,
                     2, branco, cor);
    }
  }
}

// Desenha uma peça
// a peça é definida em uma matriz 5x5, nas posições com valor != 0
void desenha_peca(int p[5][5], float x_ini, float y_ini, float lado)
{
  int i, j;
  for (i=0; i < 5; i++) {
    for (j=0; j < 5; j++) {
      // ignora posições que circundam a peça
      if (p[i][j] == 0) {
          continue;
      }
      tela_retangulo(x_ini + i*lado, y_ini + j*lado,
                     x_ini + (i+1)*lado, y_ini + (j+1)*lado,
                     1, branco, azul);
    }
  }
}

// Desenha as 3 peças embaixo do tabuleiro principal
void desenha_pecas(int p1[5][5], int p2[5][5], int p3[5][5])
{
  desenha_peca(p1, 0.1*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5);
  desenha_peca(p2, 0.4*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5);
  desenha_peca(p3, 0.7*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5);
}
