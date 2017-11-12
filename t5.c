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
#include <string.h>

int indice_peca = 0;
bool selecionou_peca = false;
const int LARGURA_TELA = 560;
const int ALTURA_TELA = 640;

float posicao_inicial_quadrado_x[10][10],posicao_inicial_quadrado_y[10][10];
float posicao_final_quadrado_x[10][10],posicao_final_quadrado_y[10][10];

float posicao_inicial_peca1_x[5][5],posicao_inicial_peca1_y[5][5];
float posicao_final_peca1_x[5][5],posicao_final_peca1_y[5][5];

float posicao_inicial_peca2_x[5][5],posicao_inicial_peca2_y[5][5];
float posicao_final_peca2_x[5][5],posicao_final_peca2_y[5][5];

float posicao_inicial_peca3_x[5][5],posicao_inicial_peca3_y[5][5];
float posicao_final_peca3_x[5][5],posicao_final_peca3_y[5][5];



float x_clicado;
float y_clicado;
char texto[100];
char texto2[100];
int linha_matriz = -1;
int coluna_matriz = -1;
int linha_matriz_clicada = 0;
int coluna_matriz_clicada = 0;
int peca_clicada = 0;
bool clicou_em_alguma_peca = false;

// função auxiliar usada por main, definida abaixo
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5]);

// A função principal
int main(void)
{
  // inicializa a tela gráfica
  tela_inicio(LARGURA_TELA, ALTURA_TELA, "Allegro5PNC");

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

void retorna_posicao_principal(float x, float y, float posicao_inicial_quadrado_x[10][10], float posicao_inicial_quadrado_y[10][10],
                               float posicao_final_quadrado_x[10][10], float posicao_final_quadrado_y[10][10],int *linha,int *coluna)
{
  int i,j;
  bool parar = false;
  *linha = -1;
  *coluna = -1;
  for (i=0;i<10;i++) {
    for (j=0; j < 10; j++) {
      if (x > posicao_inicial_quadrado_x[i][j] && x < posicao_final_quadrado_x[i][j] && y > posicao_inicial_quadrado_y[i][j] && y < posicao_final_quadrado_y[i][j]){
        *linha = j;
        *coluna = i;
        parar = true;
        break;
      }
    }
    if (parar) {
      break;
    } 
  }
}

int retorna_numero_peca(float x, float y)
{
  int i,j;
  for (i=0;i<5;i++) {
    for (j=0; j < 5; j++) {
      if (x > posicao_inicial_peca1_x[i][j] && x < posicao_final_peca1_x[i][j] 
          && y > posicao_inicial_peca1_y[i][j] && y < posicao_final_peca1_y[i][j]
          && posicao_inicial_peca1_y[i][j]!=0){
        return 1;
      }
      if (x > posicao_inicial_peca2_x[i][j] && x < posicao_final_peca2_x[i][j] 
          && y > posicao_inicial_peca2_y[i][j] && y < posicao_final_peca2_y[i][j]
          && posicao_inicial_peca2_y[i][j]!=0){
        return 2;
      }
      if (x > posicao_inicial_peca3_x[i][j] && x < posicao_final_peca3_x[i][j] 
          && y > posicao_inicial_peca3_y[i][j] && y < posicao_final_peca3_y[i][j]
          && posicao_inicial_peca3_y[i][j]!=0){
        return 3;
      }
    }
  }
  return 0;
}

void zerar_matriz(float matriz[5][5])
{
  int i,j;
  for (i=0;i<5;i++) {
    for (j=0; j < 5; j++) {
      matriz[i][j] = 0;
    }
  }
}


// funções auxiliares usadas por desenha_tela, definidas abaixo
void desenha_principal(int m[10][10], float x_ini, float y_ini, float lado);
void desenha_peca(int p[5][5], float x_ini, float y_ini, float lado,float posicao_inicial_peca_x[5][5],float posicao_inicial_peca_y[5][5],
                  float posicao_final_peca_x[5][5],float posicao_final_peca_y[5][5]);
void desenha_pecas(int p1[5][5], int p2[5][5], int p3[5][5]);


// função que desenha uma tela
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5])
{
  tela_inicia_desenho();

  zerar_matriz(posicao_inicial_peca1_x);
  zerar_matriz(posicao_inicial_peca1_y);
  zerar_matriz(posicao_final_peca1_x);
  zerar_matriz(posicao_final_peca1_y);
  zerar_matriz(posicao_inicial_peca2_x);
  zerar_matriz(posicao_inicial_peca2_y);
  zerar_matriz(posicao_final_peca2_x);
  zerar_matriz(posicao_final_peca2_y);
  zerar_matriz(posicao_inicial_peca3_x);
  zerar_matriz(posicao_inicial_peca3_y);
  zerar_matriz(posicao_final_peca3_x);
  zerar_matriz(posicao_final_peca3_y);

  desenha_principal(m, LARGURA_TELA*0.1, ALTURA_TELA*0.05, LARGURA_TELA*0.8/10);
  desenha_pecas(p1, p2, p3);

  if (tela_rato_clicado()) {
    tela_circulo(tela_rato_x(), tela_rato_y(), 5, 2, amarelo, transparente);
    peca_clicada = retorna_numero_peca(tela_rato_x(),tela_rato_y());
  }

  if (tela_rato_apertado() && (peca_clicada==1 || peca_clicada==2 || peca_clicada==3)) {
    x_clicado = tela_rato_x();
    y_clicado = tela_rato_y();
    retorna_posicao_principal(x_clicado,y_clicado, posicao_inicial_quadrado_x, posicao_inicial_quadrado_y,
    posicao_final_quadrado_x, posicao_final_quadrado_y,&linha_matriz_clicada,&coluna_matriz_clicada);
    if (peca_clicada == 1){
      desenha_peca(p1, x_clicado-10, y_clicado-10, LARGURA_TELA*0.8/10,posicao_inicial_peca1_x,posicao_inicial_peca1_y,
        posicao_final_peca1_x,posicao_final_peca1_y);
      tela_circulo(tela_rato_x(), tela_rato_y(), 4, 1, amarelo, transparente);
    } else if (peca_clicada == 2){
      desenha_peca(p2, x_clicado-55, y_clicado-55, LARGURA_TELA*0.8/10,posicao_inicial_peca2_x,posicao_inicial_peca2_y,
        posicao_final_peca2_x,posicao_final_peca2_y);
      tela_circulo(tela_rato_x(), tela_rato_y(), 4, 1, amarelo, transparente);
    } else if (peca_clicada == 3){
      desenha_peca(p3, x_clicado-100, y_clicado-100, LARGURA_TELA*0.8/10,posicao_inicial_peca3_x,posicao_inicial_peca3_y,
        posicao_final_peca3_x,posicao_final_peca3_y);
      tela_circulo(tela_rato_x(), tela_rato_y(), 4, 1, amarelo, transparente);
    }
    if (linha_matriz_clicada != -1 && coluna_matriz_clicada != -1){
        retorna_posicao_principal(tela_rato_x(),tela_rato_y(), posicao_inicial_quadrado_x, posicao_inicial_quadrado_y,
        posicao_final_quadrado_x, posicao_final_quadrado_y,&linha_matriz,&coluna_matriz);
        selecionou_peca = true;
      }
  }else{
    tela_circulo(tela_rato_x(), tela_rato_y(), 3, 1, marrom, transparente);
    if (selecionou_peca){
      // verifica_jogada(peca_clicada, linha_matriz, coluna_matriz);
      m[coluna_matriz][linha_matriz] = 1;
    }
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
      posicao_inicial_quadrado_x[i][j] = x_ini + i*lado;
      posicao_inicial_quadrado_y[i][j] = y_ini + j*lado;
      posicao_final_quadrado_x[i][j] = x_ini + (i+1)*lado;
      posicao_final_quadrado_y[i][j] = y_ini + (j+1)*lado;
      tela_retangulo(posicao_inicial_quadrado_x[i][j], posicao_inicial_quadrado_y[i][j],
                     posicao_final_quadrado_x[i][j], posicao_final_quadrado_y[i][j],
                     2, branco, cor);
    }
  }
}

// Desenha uma peça
// a peça é definida em uma matriz 5x5, nas posições com valor != 0
void desenha_peca(int p[5][5], float x_ini, float y_ini, float lado,float posicao_inicial_peca_x[5][5],float posicao_inicial_peca_y[5][5],
                  float posicao_final_peca_x[5][5],float posicao_final_peca_y[5][5])
{
  int i, j;
  for (i=0; i < 5; i++) {
    for (j=0; j < 5; j++) {
      // ignora posições que circundam a peça
      if (p[i][j] == 0) {
          continue;
      }
      posicao_inicial_peca_x[i][j] = x_ini + i*lado;
      posicao_inicial_peca_y[i][j] = y_ini + j*lado;
      posicao_final_peca_x[i][j] = x_ini + (i+1)*lado;
      posicao_final_peca_y[i][j] = y_ini + (j+1)*lado;
      tela_retangulo(posicao_inicial_peca_x[i][j], posicao_inicial_peca_y[i][j],
                     posicao_final_peca_x[i][j], posicao_final_peca_y[i][j],
                     1, branco, azul);
    }
  }
}  


// Desenha as 3 peças embaixo do tabuleiro principal
void desenha_pecas(int p1[5][5], int p2[5][5], int p3[5][5])
{
  desenha_peca(p1, 0.1*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5,posicao_inicial_peca1_x,posicao_inicial_peca1_y,
               posicao_final_peca1_x,posicao_final_peca1_y);
  desenha_peca(p2, 0.4*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5,posicao_inicial_peca2_x,posicao_inicial_peca2_y,
               posicao_final_peca2_x,posicao_final_peca2_y);
  desenha_peca(p3, 0.7*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5,posicao_inicial_peca3_x,posicao_inicial_peca3_y,
               posicao_final_peca3_x,posicao_final_peca3_y);
}