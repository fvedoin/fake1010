//Alunos: Felipe Cechin Mello e Fernando Vedoin Garcia. Jogo de tabuleiro que gera peças aleatórias a serem colocadas no mesmo com o objetivo de completar linhas e colunas para ganhar pontos. 
#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const int LARGURA_TELA = 560;
const int ALTURA_TELA = 640;

FILE *maior_pontuacao;

float posicao_inicial_quadrado_x[10][10],posicao_inicial_quadrado_y[10][10];
float posicao_final_quadrado_x[10][10],posicao_final_quadrado_y[10][10];
float posicao_inicial_peca1_x[5][5],posicao_inicial_peca1_y[5][5];
float posicao_final_peca1_x[5][5],posicao_final_peca1_y[5][5];
float posicao_inicial_peca2_x[5][5],posicao_inicial_peca2_y[5][5];
float posicao_final_peca2_x[5][5],posicao_final_peca2_y[5][5];
float posicao_inicial_peca3_x[5][5],posicao_inicial_peca3_y[5][5];
float posicao_final_peca3_x[5][5],posicao_final_peca3_y[5][5];
float posicao_encerrar_jogo_x[2]={0.0,0.0},posicao_encerrar_jogo_y[2]={0.0,0.0};
float posicao_pontuacao_jogo_x[2]={0.0,0.0},posicao_pontuacao_jogo_y[2]={0.0,0.0};
float posicao_recorde_jogo_x[2]={0.0,0.0},posicao_recorde_jogo_y[2]={0.0,0.0};
float posicao_ajuda_jogo_x[2]={0.0,0.0},posicao_ajuda_jogo_y[2]={0.0,0.0};
float posicao_sem_mov_jogo_x[2]={0.0,0.0},posicao_sem_mov_jogo_y[2]={0.0,0.0};
float x_clicado;
float y_clicado;

char texto[100];
char texto_pontuacao[100];
char texto_recorde[100];
char texto_sem_movimentos[100];
char texto_ajuda[100];
char texto_ajuda2[100];
char texto_ajuda3[100];
char linha[100];
char texto_titulo[11];

int linha_matriz_clicada = -1;
int coluna_matriz_clicada = -1;
int peca_clicada = 0;
int indice_peca = 0;
int soma_pontos = 0;
int maior_pontuacao_atual = 0;
int c1 = 0;
int c2 = 0;
int c3 = 0;
int cor_cada_quadrado_tabuleiro[10][10];

bool clicou_em_alguma_peca = false;
bool encerrar_jogo = false;
bool selecionou_peca = false;
bool sem_movimentos = false;

bool verifica_se_peca_cabe_no_tabuleiro_generica(int p[5][5],int m[10][10],int linha_m,
                                                 int coluna_m,int primeiro_quadrado_peca_linha,
                                                 int primeiro_quadrado_peca_coluna,
                                                 bool completar_tabuleiro, int cor_peca);

// função auxiliar usada por main, definida abaixo
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5]);
bool verifica_jogada(int peca, int linha, int coluna, int m[10][10],int p1[5][5],int p2[5][5],int p3[5][5]);

bool verifica_peca_zerada(int p[5][5])
{
  int aux = 0;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if (p[i][j] != 0){
        aux++;
      }
    }
  }
  if (aux == 0){
    return true;
  }else{
    return false;
  }
}

bool pontol(int l, int m[10][10])
{
  int sl = 0;
  for (int i = 0; i < 10; i++){
    sl = sl + m[i][l];
  }
  if(sl == 10){
    return true;
  }else{
    return false;
  }
}
bool pontoc(int c, int m[10][10])
{
  int sc = 0;
  for (int i = 0; i < 10; i++){
    sc = sc + m[c][i];
  }
  if(sc == 10){
    return true;
  }else{
    return false;
  }
}

//Retorna o numero de quadrados preenchidos de cada peca
int quantidade_quadrados(int peca_clicada, int p1[5][5], int p2[5][5], int p3[5][5])
{
  int num_quadrados = 0;
  switch(peca_clicada){
    case 1:
      for (int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          if (p1[i][j] == 1){
            num_quadrados++;
          }
        }
      }
      break;
    case 2:
      for (int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          if (p2[i][j] == 1){
            num_quadrados++;
          }
        }
      }
      break;
    case 3:
      for (int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          if (p3[i][j] == 1){
            num_quadrados++;
          }
        }
      }
      break;
  }
  return num_quadrados;
}

//Seta as posicoes de uma peca com valor 0
void zerar_peca(int peca_clicada, int p1[5][5], int p2[5][5], int p3[5][5])
{
  switch(peca_clicada){
    case 1:
      for (int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          p1[i][j] = 0;
        }
      }
      break;
    case 2:
      for (int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          p2[i][j] = 0;
        }
      }
      break;
    case 3:
      for (int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
          p3[i][j] = 0;
        }
      }
      break;
  }
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

//Completa a matriz da peca com 1 baseada na linha e coluna
void completa_com_um(int p[5][5],int i,int j) 
{
  p[i][j] = 1;
}

void peca_aleatoria(int p[5][5]) {
  int tipo_de_peca = rand()%6;
  int formato;
  switch(tipo_de_peca) {
    case 0:
      completa_com_um(p,0,0);
      break;
    case 1:
      formato = rand()%2;
      if (formato == 0) {
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
      } else {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
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
      } else if (formato == 2){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,1,1);
      } else {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,0,1);
      }
      break;
    case 3:
      formato = rand()%3;
      if (formato == 0) {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,0,1);
        completa_com_um(p,1,1);
      } else if (formato == 1){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,0,2);
        completa_com_um(p,0,3);
      } else {
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        completa_com_um(p,3,0);
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
      } else if (formato == 1){
        completa_com_um(p,0,0);
        completa_com_um(p,0,1);
        completa_com_um(p,0,2);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
      } else if (formato == 2){
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        completa_com_um(p,2,1);
        completa_com_um(p,2,2);
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
      }else if(formato == 5){
        completa_com_um(p,0,0);
        completa_com_um(p,1,0);
        completa_com_um(p,2,0);
        completa_com_um(p,3,0);
        completa_com_um(p,4,0);
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
      break;
  }
}

int retorna_cor_peca() 
{
  int cor = (rand()%9)+1;
  while (cor == 8 || cor == 5) {
    cor = (rand()%9)+1;
  }
  return cor;
}

// A função principal
int main(void)
{
  // inicializa a tela gráfica
  tela_inicio(LARGURA_TELA, ALTURA_TELA, "JOGO FAKE1010!");

  // o tabuleiro e as peças
  int m[10][10];
  int p1[5][5];
  int p2[5][5];
  int p3[5][5];

  int i, j;
  for (i=0; i<10; i++) {
    for (j=0; j<10; j++) {
      m[i][j] = 0;
      cor_cada_quadrado_tabuleiro[i][j] = 0;
    }
  }
  //Abre o arquivo para leitura e escrita do recorde.
  maior_pontuacao = fopen("maior_pontuacao.txt","ab+");

  if(maior_pontuacao != NULL){
    while(fgets(linha, 100, maior_pontuacao) != NULL){
      //Funcao atoi transforma um char para um int.
      maior_pontuacao_atual = atoi(linha);
      break;
    }
  }

  fclose(maior_pontuacao);

  for (i=0; i<5; i++) {
    for (j=0; j<5; j++) {
      p1[i][j] = 0;
      p2[i][j] = 0;
      p3[i][j] = 0;
    }
  }

  srand(time(NULL));
  c1 = retorna_cor_peca();
  c2 = retorna_cor_peca();
  c3 = retorna_cor_peca();
  peca_aleatoria(p1);
  peca_aleatoria(p2);
  peca_aleatoria(p3);

  while (true) {
    desenha_tela(m, p1, p2, p3);
    if (encerrar_jogo) {
      break;
    }
  }

  tela_fim();

  return 0;
}

void encontra_posicao_principal(float x, float y, float posicao_inicial_quadrado_x[10][10], float posicao_inicial_quadrado_y[10][10],
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

//Troca os valores das variaveis com ponteiro.
void encontra_primeiro_quadrado_peca(int posicao_quadrado[5][5],int *linha,int *coluna)
{
  int i,j;
  bool parou = false;
  for (i=0;i<5;i++) {
    for (j=0;j<5;j++) {
      if (posicao_quadrado[j][i]==1) {
        *linha = i;
        *coluna = j;
        parou = true;
        break;
      }
    }
    if (parou) {
      break;
    }
  }
}

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

void zerar_todas_matrizes_pecas()
{
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
}

//Retorna o número maior que 1 que identifica a peca
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

void atualizar_recorde(int pontuacao)
{
  if (pontuacao>maior_pontuacao_atual) {
    maior_pontuacao_atual = pontuacao;
    maior_pontuacao = fopen ("maior_pontuacao.txt", "w");
    fprintf(maior_pontuacao, "%d",maior_pontuacao_atual);
    fclose(maior_pontuacao);
  }
}

//Subtrai o x do rato quando a peca for selecionada
int retorna_subtracao_x_rato(int p[5][5])
{
  int subtracao = 0;
  if (indice_todas_pecas(p) == 5) {
    subtracao = 50;
  } else if (indice_todas_pecas(p) == 15) {
    subtracao = 80;
  }else{
    subtracao = 10;
  }
  return subtracao;
}

//Verifica se o usuario clicou no X da tela
bool retorna_encerramento_jogo(float x,float y) 
{
  if (x>posicao_encerrar_jogo_x[0] && x<posicao_encerrar_jogo_x[1]
      && y>posicao_encerrar_jogo_y[0] && y<posicao_encerrar_jogo_y[1]) {
    return true;
  }
  return false;
}

// funções auxiliares usadas por desenha_tela, definidas abaixo
void desenha_principal(int m[10][10], float x_ini, float y_ini, float lado);
void desenha_peca(int p[5][5], float x_ini, float y_ini, float lado,float posicao_inicial_peca_x[5][5],float posicao_inicial_peca_y[5][5],
                  float posicao_final_peca_x[5][5],float posicao_final_peca_y[5][5], int cor);
void desenha_pecas(int p1[5][5], int p2[5][5], int p3[5][5]);

// função que desenha uma tela
void desenha_tela(int m[10][10], int p1[5][5], int p2[5][5], int p3[5][5])
{
  tela_inicia_desenho();

  desenha_principal(m, LARGURA_TELA*0.2, ALTURA_TELA*0.2, LARGURA_TELA*0.6/10);
  desenha_pecas(p1, p2, p3);

  //Seta as coordenadas e constroi o botao de encerramento do jogo
  posicao_encerrar_jogo_x[0] = LARGURA_TELA*0.95;
  posicao_encerrar_jogo_x[1] = LARGURA_TELA;
  posicao_encerrar_jogo_y[0] = ALTURA_TELA*0.005;
  posicao_encerrar_jogo_y[1] = ALTURA_TELA*0.06;
  tela_retangulo(posicao_encerrar_jogo_x[0],posicao_encerrar_jogo_y[0],posicao_encerrar_jogo_x[1]
                 ,posicao_encerrar_jogo_y[1],2,branco,vermelho);
  sprintf(texto,"X");
  tela_texto_dir(posicao_encerrar_jogo_x[0]+2,posicao_encerrar_jogo_y[0]+2,30,branco,texto);


  //Seta as coordenadas e constroi o painel da pontuacao do jogo
  posicao_pontuacao_jogo_x[0] = 1;
  posicao_pontuacao_jogo_x[1] = 200;
  posicao_pontuacao_jogo_y[0] = ALTURA_TELA*0.005;
  posicao_pontuacao_jogo_y[1] = ALTURA_TELA*0.04;
  tela_retangulo(posicao_pontuacao_jogo_x[0],posicao_pontuacao_jogo_y[0],posicao_pontuacao_jogo_x[1]
                 ,posicao_pontuacao_jogo_y[1],2,branco,verde);
  sprintf(texto_pontuacao,"Pontuacao: %d", soma_pontos);
  tela_texto_dir(posicao_pontuacao_jogo_x[0]+2,posicao_pontuacao_jogo_y[0]+2,12,preto,texto_pontuacao);

  //Seta as coordenadas e constroi o painel da maior pontuacao
  posicao_recorde_jogo_x[0] = 1;
  posicao_recorde_jogo_x[1] = 200;
  posicao_recorde_jogo_y[0] = ALTURA_TELA*0.05;
  posicao_recorde_jogo_y[1] = ALTURA_TELA*0.085;
  tela_retangulo(posicao_recorde_jogo_x[0],posicao_recorde_jogo_y[0],posicao_recorde_jogo_x[1]
                 ,posicao_recorde_jogo_y[1],2,branco,amarelo);
  sprintf(texto_recorde,"Recorde atual: %d", maior_pontuacao_atual);
  tela_texto_dir(posicao_recorde_jogo_x[0]+2,posicao_recorde_jogo_y[0]+2,12,preto,texto_recorde);

  //Seta as coordenadas e constroi o painel de ajuda
  posicao_ajuda_jogo_x[0] = 205;
  posicao_ajuda_jogo_x[1] = LARGURA_TELA*0.93;
  posicao_ajuda_jogo_y[0] = ALTURA_TELA*0.005;
  posicao_ajuda_jogo_y[1] = ALTURA_TELA*0.085;
  tela_retangulo(posicao_ajuda_jogo_x[0],posicao_ajuda_jogo_y[0],posicao_ajuda_jogo_x[1]
                 ,posicao_ajuda_jogo_y[1],2,branco,azul);
  sprintf(texto_ajuda,"Selecione e arraste as pecas para preencher");
  sprintf(texto_ajuda2,"linhas ou colunas do tabuleiro.");
  sprintf(texto_ajuda3,"Faca a maior pontuacao possivel!");
  tela_texto_dir(posicao_ajuda_jogo_x[0]+2,posicao_ajuda_jogo_y[0]+2,12,branco,texto_ajuda);
  tela_texto_dir(posicao_ajuda_jogo_x[0]+2,posicao_ajuda_jogo_y[0]+16,12,branco,texto_ajuda2);
  tela_texto_dir(posicao_ajuda_jogo_x[0]+2,posicao_ajuda_jogo_y[0]+30,12,branco,texto_ajuda3);

  sprintf(texto_titulo,"FAKE 1010!");
  tela_texto_dir(LARGURA_TELA*0.3,ALTURA_TELA*0.1,40,branco,texto_titulo);

  //Verifica se nao ha movimentos possiveis com as novas pecas geradas aleatoriamente
  if (sem_movimentos) {
    zerar_todas_matrizes_pecas();
    posicao_sem_mov_jogo_x[0] = LARGURA_TELA*0.13;
    posicao_sem_mov_jogo_x[1] = LARGURA_TELA*0.9;
    posicao_sem_mov_jogo_y[0] = ALTURA_TELA*0.41;
    posicao_sem_mov_jogo_y[1] = ALTURA_TELA*0.47;
    tela_retangulo(posicao_sem_mov_jogo_x[0],posicao_sem_mov_jogo_y[0],posicao_sem_mov_jogo_x[1]
                   ,posicao_sem_mov_jogo_y[1],2,branco,vermelho);
    sprintf(texto_sem_movimentos,"Sem movimentos possiveis!");
    tela_texto_dir(posicao_sem_mov_jogo_x[0]+4,posicao_sem_mov_jogo_y[0]+2,30,branco,texto_sem_movimentos);
  }

  if (tela_rato_clicado()) {
    peca_clicada = retorna_numero_peca(tela_rato_x(),tela_rato_y());
    encerrar_jogo = retorna_encerramento_jogo(tela_rato_x(),tela_rato_y());
  }


  //Se o usuario clicou em alguma peca, ele podera arrasta-la para o tabuleiro
  if (tela_rato_apertado() && (peca_clicada==1 || peca_clicada==2 || peca_clicada==3)) {
    x_clicado = tela_rato_x();
    y_clicado = tela_rato_y();
    encontra_posicao_principal(x_clicado,y_clicado, posicao_inicial_quadrado_x, posicao_inicial_quadrado_y,
    posicao_final_quadrado_x, posicao_final_quadrado_y,&linha_matriz_clicada,&coluna_matriz_clicada);
    if (peca_clicada == 1){
      int subtracao = retorna_subtracao_x_rato(p1);
      desenha_peca(p1, x_clicado-subtracao, y_clicado-10, LARGURA_TELA*0.6/10,posicao_inicial_peca1_x,posicao_inicial_peca1_y,
        posicao_final_peca1_x,posicao_final_peca1_y, c1);
    } else if (peca_clicada == 2){
      int subtracao = retorna_subtracao_x_rato(p2);
      desenha_peca(p2, x_clicado-subtracao, y_clicado-10, LARGURA_TELA*0.6/10,posicao_inicial_peca2_x,posicao_inicial_peca2_y,
        posicao_final_peca2_x,posicao_final_peca2_y, c2);
    } else if (peca_clicada == 3){
      int subtracao = retorna_subtracao_x_rato(p3);
      desenha_peca(p3, x_clicado-subtracao, y_clicado-10, LARGURA_TELA*0.6/10,posicao_inicial_peca3_x,posicao_inicial_peca3_y,
        posicao_final_peca3_x,posicao_final_peca3_y, c3);
    }
    tela_circulo(x_clicado,y_clicado, 4, 1, preto, transparente);
    if (linha_matriz_clicada != -1 && coluna_matriz_clicada != -1){
        selecionou_peca = true;
    }
  }else{
    tela_circulo(tela_rato_x(), tela_rato_y(), 3, 1, marrom, transparente);
    if (selecionou_peca && linha_matriz_clicada != -1 && coluna_matriz_clicada != -1) {
      if(verifica_jogada(peca_clicada, linha_matriz_clicada, coluna_matriz_clicada, m,p1,p2,p3)) {
        soma_pontos = soma_pontos + quantidade_quadrados(peca_clicada, p1, p2, p3);
        atualizar_recorde(soma_pontos);
        zerar_peca(peca_clicada,p1,p2,p3);
        bool mov_possivel1 = false, mov_possivel2 = false, mov_possivel3 = false;
        int primeiro_quadrado_peca_linha, primeiro_quadrado_peca_coluna;
        int qp1 = quantidade_quadrados(1, p1, p2, p3), qp2 = quantidade_quadrados(2, p1, p2, p3), qp3 = quantidade_quadrados(3, p1, p2, p3);
        if (!(qp1 == 0 && qp2 == 0 && qp3 == 0)) {
          for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
              if (qp1 > 0){
                encontra_primeiro_quadrado_peca(p1,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
                if(verifica_se_peca_cabe_no_tabuleiro_generica(p1,m,j,i,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,false,0)){
                  mov_possivel1 = true;
                }
              }
              if (qp2 > 0){
                encontra_primeiro_quadrado_peca(p2,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
                if(verifica_se_peca_cabe_no_tabuleiro_generica(p2,m,j,i,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,false,0)){
                  mov_possivel2 = true;
                }
              }
              if (qp3 > 0){
                encontra_primeiro_quadrado_peca(p3,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
                if(verifica_se_peca_cabe_no_tabuleiro_generica(p3,m,j,i,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,false,0)){
                  mov_possivel3 = true;
                }
              }
            }
          }
          if(!(mov_possivel1 || mov_possivel2 || mov_possivel3)){
            sem_movimentos = true;
          }
        }
        if (verifica_peca_zerada(p1) && verifica_peca_zerada(p2) && verifica_peca_zerada(p3)){
          peca_aleatoria(p1);
          peca_aleatoria(p2);
          peca_aleatoria(p3);
          c1 = retorna_cor_peca();
          c2 = retorna_cor_peca();
          c3 = retorna_cor_peca();
          desenha_pecas(p1, p2, p3);
          mov_possivel1 = false, mov_possivel2 = false, mov_possivel3 = false;
          int primeiro_quadrado_peca_linha, primeiro_quadrado_peca_coluna;
          for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
              encontra_primeiro_quadrado_peca(p1,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
              if(verifica_se_peca_cabe_no_tabuleiro_generica(p1,m,j,i,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,false,0)){
                mov_possivel1 = true;
              }
              encontra_primeiro_quadrado_peca(p2,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
              if(verifica_se_peca_cabe_no_tabuleiro_generica(p2,m,j,i,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,false,0)){
                mov_possivel2 = true;
              }
              encontra_primeiro_quadrado_peca(p3,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
              if(verifica_se_peca_cabe_no_tabuleiro_generica(p3,m,j,i,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,false,0)){
                mov_possivel3 = true;
              }
            }
          }
          if(!(mov_possivel1 || mov_possivel2 || mov_possivel3)){
            sem_movimentos = true;
          }
        }
      }
    }
    selecionou_peca = false;
    peca_clicada = 0;
  }
  tela_termina_desenho();
}

// Desenha o tabuleiro principal
// Ele é formado por uma matrix 10x10, com os valores 0 representando posições
// livres.
void desenha_principal(int m[10][10], float x_ini, float y_ini, float lado)
{
  int i, j; 
  for (i=0; i < 10; i++) {
    for (j=0; j < 10; j++) {
      posicao_inicial_quadrado_x[i][j] = x_ini + i*lado;
      posicao_inicial_quadrado_y[i][j] = y_ini + j*lado;
      posicao_final_quadrado_x[i][j] = x_ini + (i+1)*lado;
      posicao_final_quadrado_y[i][j] = y_ini + (j+1)*lado;
      tela_retangulo(posicao_inicial_quadrado_x[i][j], posicao_inicial_quadrado_y[i][j],
                     posicao_final_quadrado_x[i][j], posicao_final_quadrado_y[i][j],
                     2, branco, cor_cada_quadrado_tabuleiro[i][j]);
    }
  }
}

// Desenha uma peça
// a peça é definida em uma matriz 5x5, nas posições com valor != 0
void desenha_peca(int p[5][5], float x_ini, float y_ini, float lado,float posicao_inicial_peca_x[5][5],float posicao_inicial_peca_y[5][5],
                  float posicao_final_peca_x[5][5],float posicao_final_peca_y[5][5], int cor)
{
  int i, j;
  zerar_matriz(posicao_inicial_peca_x);
  zerar_matriz(posicao_inicial_peca_y);
  zerar_matriz(posicao_final_peca_x);
  zerar_matriz(posicao_final_peca_y);
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
                     1, branco, cor);
    }
  }
}  


// Desenha as 3 peças embaixo do tabuleiro principal
void desenha_pecas(int p1[5][5], int p2[5][5], int p3[5][5])
{
  desenha_peca(p1, 0.1*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5,posicao_inicial_peca1_x,posicao_inicial_peca1_y,
               posicao_final_peca1_x,posicao_final_peca1_y, c1);
  desenha_peca(p2, 0.4*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5,posicao_inicial_peca2_x,posicao_inicial_peca2_y,
               posicao_final_peca2_x,posicao_final_peca2_y, c2);
  desenha_peca(p3, 0.7*LARGURA_TELA, 0.8*ALTURA_TELA, 0.2*LARGURA_TELA/5,posicao_inicial_peca3_x,posicao_inicial_peca3_y,
               posicao_final_peca3_x,posicao_final_peca3_y, c3);
}

bool verifica_se_peca_cabe_no_tabuleiro_generica(int p[5][5],int m[10][10],int linha_m,
                                                 int coluna_m,int primeiro_quadrado_peca_linha,
                                                 int primeiro_quadrado_peca_coluna,
                                                 bool completar_tabuleiro, int cor_peca)
{
  //Se a coluna e linha que o usuario quer colocar a peca estiver preenchida, retorna falso
  if (m[coluna_m][linha_m]!=0) {
    return false;
  }

  int i,j,conta_quadrados_peca = 0,k=0;
  int variacao_coluna = 0,variacao_linha = 0;

  for (i=0;i<5;i++) {
    for (j=0;j<5;j++) {
      if (p[i][j] == 1) {
        conta_quadrados_peca++;
      }
    }
  }

  if (conta_quadrados_peca==0) {
    return false;
  }

  int indice_linha[conta_quadrados_peca],indice_coluna[conta_quadrados_peca];
  int posicao_linhas_preenchidas[conta_quadrados_peca];
  int posicao_colunas_preenchidas[conta_quadrados_peca];

  //Coloca nos vetores as linhas e colunas da peca que estao preenchidas com 1
  for (i=0;i<5;i++) {
    for (j=0;j<5;j++) {
      if (p[i][j] == 1) {
        posicao_linhas_preenchidas[k] = j;
        posicao_colunas_preenchidas[k] = i;
        k++;
      }
    }
  }

  k = 0;
  while(k<conta_quadrados_peca) {
    //Calcula a variacao da linha e da coluna baseada no primeiro quadrado preenchido da peca
    // e coloca nos vetores
    variacao_linha = posicao_linhas_preenchidas[k] - primeiro_quadrado_peca_linha;
    variacao_coluna = posicao_colunas_preenchidas[k] - primeiro_quadrado_peca_coluna;
    indice_linha[k] = 0;
    indice_coluna[k] = 0;
    if (variacao_linha!=0) {
      indice_linha[k] = linha_m + variacao_linha;
    } else if (variacao_linha==0) {
      indice_linha[k] = linha_m;
    }
    if (variacao_coluna!=0) {
      indice_coluna[k] = coluna_m + variacao_coluna;
    } else if (variacao_coluna==0) {
      indice_coluna[k] = coluna_m;
    }
    if (indice_coluna[k]>=0 && indice_coluna[k]<10 && indice_linha[k]>=0 && indice_linha[k]<10) {
      if (m[indice_coluna[k]][indice_linha[k]]!=0) {
        return false;
      }
    } else {
      return false;
    }
    k++;
  }

  //Se o parametro for true, preenche o tabuleiro com a peca
  if (completar_tabuleiro) {
    int copia_tabuleiro[10][10];
    for (int i=0;i<10;i++) {
      for (int j=0;j<10;j++) {
        copia_tabuleiro[i][j] = m[i][j];
      }
    }
    for (i=0;i<conta_quadrados_peca;i++) {
      copia_tabuleiro[indice_coluna[i]][indice_linha[i]] = 1;
    }
    int cont = 0;
    int linhas_fechadas[10], colunas_fechadas[10];
    for (int i = 0; i < 10; i++){
      linhas_fechadas[i] = 0;
      colunas_fechadas[i] = 0;
    }
    for (int i = 0; i < 10; i++){
      if(pontol(i, copia_tabuleiro)){
        cont++;
        soma_pontos = soma_pontos + 10;
        linhas_fechadas[i] = 1;
      }
      if(pontoc(i, copia_tabuleiro)){
        cont++;
        soma_pontos = soma_pontos + 10;
        colunas_fechadas[i] = 1;
      }
    }
    if (cont>1) {
      soma_pontos = soma_pontos + (10*(cont-1));
    }
    for (int i = 0; i < 10; i++){
      if(linhas_fechadas[i] == 1){
        for (int k = 0; k < 10; k++){
          m[k][i] = 0;
          cor_cada_quadrado_tabuleiro[k][i] = 0;
        }
      }
      if (colunas_fechadas[i] == 1){
        for (int k = 0; k < 10; k++){
          m[i][k] = 0;
          cor_cada_quadrado_tabuleiro[i][k] = 0;
        }
      }
    }
    for (int i = 0; i < conta_quadrados_peca; i++){
      for (int j=0;j<10;j++) {
        if (linhas_fechadas[j] == 1) {
          if (indice_linha[i] == j) {
            indice_linha[i] = -1;
          }
        }
        if (colunas_fechadas[j] == 1) {
          if (indice_coluna[i] == j) {
            indice_coluna[i] = -1;
          }
        }
      }
    }
    for (i=0;i<conta_quadrados_peca;i++) {
      if (indice_coluna[i]!=-1 && indice_linha[i]!=-1) {
        m[indice_coluna[i]][indice_linha[i]] = 1;
        cor_cada_quadrado_tabuleiro[indice_coluna[i]][indice_linha[i]] = cor_peca;
      }
    }
  }
  return true;
}

bool verifica_jogada(int peca, int linha, int coluna, int m[10][10],int p1[5][5],int p2[5][5],int p3[5][5])
{
  int primeiro_quadrado_peca_linha;
  int primeiro_quadrado_peca_coluna;
  if(peca == 1){
    encontra_primeiro_quadrado_peca(p1,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
    if (verifica_se_peca_cabe_no_tabuleiro_generica(p1,m,linha,coluna,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,true,c1)) {
      return true;
    }
  }else if(peca == 2){
    encontra_primeiro_quadrado_peca(p2,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
    if (verifica_se_peca_cabe_no_tabuleiro_generica(p2,m,linha,coluna,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,true,c2)) {
      return true;
    }
  }else if(peca == 3){
    encontra_primeiro_quadrado_peca(p3,&primeiro_quadrado_peca_linha,&primeiro_quadrado_peca_coluna);
    if (verifica_se_peca_cabe_no_tabuleiro_generica(p3,m,linha,coluna,primeiro_quadrado_peca_linha,primeiro_quadrado_peca_coluna,true,c3)) {
      return true;
    }
  }
  return false;
}