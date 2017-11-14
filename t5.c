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
#include <stdlib.h>
#include <time.h>

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
int linha_matriz_clicada = -1;
int coluna_matriz_clicada = -1;
int peca_clicada = 0;
bool clicou_em_alguma_peca = false;

// função auxiliar usada por main, definida abaixo
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5]);
bool verifica_jogada(int peca, int linha, int coluna, int m[10][10],int p1[5][5],int p2[5][5],int p3[5][5]);


void zerar_matriz(float matriz[5][5])
{
  int i,j;
  for (i=0;i<5;i++) {
    for (j=0; j < 5; j++) {
      matriz[i][j] = 0;
    }
  }
}

void completa_com_um(int p[5][5],int i,int j) 
{
  p[i][j] = 1;
}

void completa_com_um_tabuleiro(int m[10][10],int i,int j)
{
  m[i][j] = 1;
}

void peca_aleatoria(int p[5][5]) {
  int tipo_de_peca = rand()%6;
  int formato;
  switch(tipo_de_peca) {
    case 0:
      completa_com_um(p,0,0);
      p[1][2] = 2;
      break;
    case 1:
      formato = rand()%2;
      if (formato == 0) {
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        p[1][2] = 3;
      } else {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        p[1][2] = 4;
      }
      break;
    case 2:
      formato = rand()%4;
      if (formato == 0) {
        completa_com_um(p,0,1);
        completa_com_um(p,1,1);
        completa_com_um(p,1,0);
        p[1][2] = 5;
      } else if (formato == 1){
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,1,1);
        p[1][2] = 6;
      } else if (formato == 2){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,1,1);
        p[1][2] = 7;
      } else {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,0,1);
        p[1][2] = 8;
      }
      break;
    case 3:
      formato = rand()%3;
      if (formato == 0) {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,0,1);
        completa_com_um(p,1,1);
        p[1][2] = 9;
      } else if (formato == 1){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,0,2);
        completa_com_um(p,0,3);
        p[1][2] = 10;
      } else {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        completa_com_um(p,3,0);
        p[1][2] = 11;
      }
      break;
    case 4:
      formato = rand()%6;
      if (formato == 0) {
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,0,2);
        completa_com_um(p,1,2);
        completa_com_um(p,2,2);
        p[1][3] = 12;
      } else if (formato == 1){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,0,2);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        p[1][2] = 13;
      } else if (formato == 2){
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        completa_com_um(p,2,1);
        completa_com_um(p,2,2);
        p[1][2] = 14;
      } else if (formato == 3){
        completa_com_um(p,0,2);
        completa_com_um(p,1,2);
        completa_com_um(p,2,2);
        completa_com_um(p,2,1);
        completa_com_um(p,2,0);
        p[1][3] = 15;
      } else if(formato == 4){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,0,2);
        completa_com_um(p,0,3);
        completa_com_um(p,0,4);
        p[1][2] = 16;
      }else if(formato == 5){
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        completa_com_um(p,3,0);
        completa_com_um(p,4,0);
        p[1][2] = 17;
      }
      break;
    case 5:
      completa_com_um(p,0,0);
      completa_com_um(p,1,0);
      completa_com_um(p,0,1);
      completa_com_um(p,1,1);
      completa_com_um(p,0,2);
      completa_com_um(p,2,0);
      completa_com_um(p,2,2);
      completa_com_um(p,2,1);
      completa_com_um(p,1,2);
      p[1][3] = 18;
      break;
  }
}

// A função principal
int main(void)
{
  // inicializa a tela gráfica
  tela_inicio(LARGURA_TELA, ALTURA_TELA, "Allegro5");

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

  srand(time(NULL));
  peca_aleatoria(p1);
  peca_aleatoria(p2);
  peca_aleatoria(p3);

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

// void encontra_primeiro_quadrado_peca(int posicao_quadrado[5][5],int *linha,int *coluna)
// {
//   int i,j;
//   bool parou = false;
//   for (i=0;i<5;i++) {
//     for (j=0;j<5;j++) {
//       if (posicao_quadrado[i][j]==1) {
//         *linha = j;
//         *coluna = i;
//         parou = true;
//         break;
//       }
//     }
//     if (parou) {
//       break;
//     }
//   }
// }

int retorna_numero_peca(float x, float y)
{
  int i,j;
  for (i=0;i<5;i++) {
    for (j=0;j<5;j++) {
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


int indice_todas_pecas(int p[5][5])
{
  int i,j;
  for(i=0;i<5;i++) {
    for(j=0;j<5;j++) {
      if (p[i][j]>1) {
        return p[i][j];
      }
    }
  }
  return 0;
}

int retorna_subtracao_x_rato(int p[5][5])
{
  int subtracao = 0;
  if (indice_todas_pecas(p) == 5) {
    subtracao = 50;
  } else if (indice_todas_pecas(p) == 15) {
    subtracao = 100;
  }
  return subtracao;
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

  desenha_principal(m, LARGURA_TELA*0.1, ALTURA_TELA*0.05, LARGURA_TELA*0.8/10);
  desenha_pecas(p1, p2, p3);

  if (tela_rato_clicado()) {
    peca_clicada = retorna_numero_peca(tela_rato_x(),tela_rato_y());
  }

  if (tela_rato_apertado() && (peca_clicada==1 || peca_clicada==2 || peca_clicada==3)) {
    x_clicado = tela_rato_x();
    y_clicado = tela_rato_y();
    retorna_posicao_principal(x_clicado,y_clicado, posicao_inicial_quadrado_x, posicao_inicial_quadrado_y,
    posicao_final_quadrado_x, posicao_final_quadrado_y,&linha_matriz_clicada,&coluna_matriz_clicada);
    if (peca_clicada == 1){
      int subtracao = retorna_subtracao_x_rato(p1);
      desenha_peca(p1, x_clicado-subtracao, y_clicado, LARGURA_TELA*0.8/10,posicao_inicial_peca1_x,posicao_inicial_peca1_y,
        posicao_final_peca1_x,posicao_final_peca1_y);
    } else if (peca_clicada == 2){
      int subtracao = retorna_subtracao_x_rato(p2);
      desenha_peca(p2, x_clicado-subtracao, y_clicado, LARGURA_TELA*0.8/10,posicao_inicial_peca2_x,posicao_inicial_peca2_y,
        posicao_final_peca2_x,posicao_final_peca2_y);
    } else if (peca_clicada == 3){
      int subtracao = retorna_subtracao_x_rato(p3);
      desenha_peca(p3, x_clicado-subtracao, y_clicado, LARGURA_TELA*0.8/10,posicao_inicial_peca3_x,posicao_inicial_peca3_y,
        posicao_final_peca3_x,posicao_final_peca3_y);
    }
    tela_circulo(x_clicado,y_clicado, 4, 1, amarelo, transparente);
    if (linha_matriz_clicada != -1 && coluna_matriz_clicada != -1){
        selecionou_peca = true;
    }
  }else{
    tela_circulo(tela_rato_x(), tela_rato_y(), 3, 1, marrom, transparente);
    if (selecionou_peca && linha_matriz_clicada != -1 && coluna_matriz_clicada != -1){
      if(verifica_jogada(peca_clicada, linha_matriz_clicada, coluna_matriz_clicada, m,p1,p2,p3)){
        
      }
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
      if (p[i][j] == 0 || p[i][j]>1) {
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

bool verifica_se_peca_cabe_no_tabuleiro(int indice_peca,int m[10][10],int linha,int coluna)
{
  switch(indice_peca) {
    case 2:
      if (m[coluna][linha] == 0){
        completa_com_um_tabuleiro(m,coluna,linha);
        return true;
      }
      break;
    case 3:
      if (linha+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          return true;
        }
      }
      break;
    case 4:
      if (coluna+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          return true;
        }
      }
      break;
    case 5:
      if (coluna-1>=0 && linha+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna-1][linha+1] == 0
            && m[coluna][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna-1,linha+1);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          return true;
        }
      }
      break;
    case 6:
      if (coluna+1<10 && linha+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna+1][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha+1);
          return true;
        }
      }
      break;
    case 7:
      if (coluna+1<10 && linha+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna+1][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna+1,linha+1);
          return true;
        }
      }
      break;
    case 8:
      if (coluna+1<10 && linha+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          return true;
        }
      }
      break;
    case 9:
      if (coluna+1<10 && linha+1<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna+1][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna+1,linha+1);
          return true;
        }
      }
      break;
    case 10:
      if (linha+1<10 && linha+2<10 && linha+3<10) {
        if (m[coluna][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna][linha+2] == 0
            && m[coluna][linha+3] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna,linha+2);
          completa_com_um_tabuleiro(m,coluna,linha+3);
          return true;
        }
      }
      break;
    case 11:
      if (coluna+1<10 && coluna+2<10 && coluna+3<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna+2][linha] == 0
            && m[coluna+3][linha] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna+2,linha);
          completa_com_um_tabuleiro(m,coluna+3,linha);
          return true;
        }
      }
      break;
    case 12:
      if (coluna+1<10 && coluna+2<10 && linha+1<10 && linha+2<10) {
        if (m[coluna][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna][linha+2] == 0
            && m[coluna+1][linha+2] == 0
            && m[coluna+2][linha+2] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna,linha+2);
          completa_com_um_tabuleiro(m,coluna+1,linha+2);
          completa_com_um_tabuleiro(m,coluna+2,linha+2);
          return true;
        }
      }
      break;
    case 13:
      if (coluna+1<10 && coluna+2<10 && linha+1<10 && linha+2<10) {
        if (m[coluna][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna][linha+2] == 0
            && m[coluna+1][linha] == 0
            && m[coluna+2][linha] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna,linha+2);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna+2,linha);
          return true;
        }
      }
      break;
    case 14:
      if (coluna+1<10 && coluna+2<10 && linha+1<10 && linha+2<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna+2][linha] == 0
            && m[coluna+2][linha+1] == 0
            && m[coluna+2][linha+2] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna+2,linha);
          completa_com_um_tabuleiro(m,coluna+2,linha+1);
          completa_com_um_tabuleiro(m,coluna+2,linha+2);
          return true;
        }
      }
      break;
    case 15:
      if (coluna-2>=0 && coluna-1>=0 && linha+1<10 && linha+2<10) {
        if (m[coluna][linha] == 0
            && m[coluna-2][linha+2] == 0
            && m[coluna-1][linha+2] == 0
            && m[coluna][linha+2] == 0
            && m[coluna][linha+1] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna-2,linha+2);
          completa_com_um_tabuleiro(m,coluna-1,linha+2);
          completa_com_um_tabuleiro(m,coluna,linha+2);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          return true;
        }
      }
      break;
    case 16:
      if (linha+1<10 && linha+2<10 && linha+3<10 && linha+4<10) {
        if (m[coluna][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna][linha+2] == 0
            && m[coluna][linha+3] == 0
            && m[coluna][linha+4] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna,linha+2);
          completa_com_um_tabuleiro(m,coluna,linha+3);
          completa_com_um_tabuleiro(m,coluna,linha+4);
          return true;
        }
      }
      break;
    case 17:
      if (coluna+1<10 && coluna+2<10 && coluna+3<10 && coluna+4<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna+2][linha] == 0
            && m[coluna+3][linha] == 0
            && m[coluna+4][linha] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna+2,linha);
          completa_com_um_tabuleiro(m,coluna+3,linha);
          completa_com_um_tabuleiro(m,coluna+4,linha);
          return true;
        }
      }
      break;
    case 18:
      if (coluna+1<10 && coluna+2<10 && linha+1<10 && linha+2<10) {
        if (m[coluna][linha] == 0
            && m[coluna+1][linha] == 0
            && m[coluna][linha+1] == 0
            && m[coluna+1][linha+1] == 0
            && m[coluna][linha+2] == 0
            && m[coluna+2][linha] == 0
            && m[coluna+2][linha+2] == 0
            && m[coluna+2][linha+1] == 0
            && m[coluna+1][linha+2] == 0) {
          completa_com_um_tabuleiro(m,coluna,linha);
          completa_com_um_tabuleiro(m,coluna+1,linha);
          completa_com_um_tabuleiro(m,coluna,linha+1);
          completa_com_um_tabuleiro(m,coluna+1,linha+1);
          completa_com_um_tabuleiro(m,coluna,linha+2);
          completa_com_um_tabuleiro(m,coluna+2,linha);
          completa_com_um_tabuleiro(m,coluna+2,linha+2);
          completa_com_um_tabuleiro(m,coluna+2,linha+1);
          completa_com_um_tabuleiro(m,coluna+1,linha+2);
          return true;
        }
      }
      break;
  }
  return false;
}

bool verifica_jogada(int peca, int linha, int coluna, int m[10][10],int p1[5][5],int p2[5][5],int p3[5][5])
{
  switch(peca) {
    case 1:
      return verifica_se_peca_cabe_no_tabuleiro(indice_todas_pecas(p1),m,linha,coluna);
      break;
    case 2:
      return verifica_se_peca_cabe_no_tabuleiro(indice_todas_pecas(p2),m,linha,coluna);
      break;
    case 3:
      return verifica_se_peca_cabe_no_tabuleiro(indice_todas_pecas(p3),m,linha,coluna);
      break;
  }
  return false;
}