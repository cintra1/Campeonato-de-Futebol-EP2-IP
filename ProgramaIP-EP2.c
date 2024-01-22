/******************************************************************/
/**  ACH 2001 - Introdução à Programação                         **/
/**  EACH-USP - Primeiro Semestre de 2023                        **/
/**  ACH 2001 - Marcos L. Chaim                                  **/
/**                                                              **/
/**  Segundo Exercício-Programa                                  **/
/**                                                              **/
/**  Mateus Freitas Cintra - 14597677                            **/
/**                                                              **/
/**  16/07/2023                                                  **/
/******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38
#define NumeroMaxJogos NumeroMaxTimes * NumeroMaxRodadas

typedef struct auxtime {
  int PontosGanhos;
  int GolsMarcados;
  int GolsSofridos;
  int SaldoDeGols;
  int Vitorias;
  int Empates;  
  int Derrotas; 
  float GolAverage;
  char nome[31];
} time;

typedef struct auxjogo {
  char local[30];
  char visitante[30];
  int golslocal;
  int golsvisitante;
} jogo;

void lenometime(char * s) {
  int i;
  s[0] = '\0';
  char c;
  c = getchar();
  for(i = 0; c != ',' && i < 30;++i)
    {
      // if(c == '\n')
      //   continue;
      s[i] = c;
      c = getchar();
    }
  s[i] = '\0';
  //printf("%s\n",s);
}

int encontratime(time *timescampeonato, char *nome, int notimes) {
  int i;
  for (i = 0; i < notimes; ++i) {
    if (strcmp(timescampeonato[i].nome, nome) == 0) {
      return i;
    }
  }
  return -1;
}

int crialistatimes(time *timescampeonato, jogo *dadosjogos, int numerojogos) {
  int i, notimes = 0;
  for (i = 0; i < numerojogos; i++) {
    int pos_local = encontratime(timescampeonato, dadosjogos[i].local, notimes);
    int pos_visitante = encontratime(timescampeonato, dadosjogos[i].visitante, notimes);

    if (pos_local == -1) {
      strncpy(timescampeonato[notimes].nome, dadosjogos[i].local, 30);
      timescampeonato[notimes].nome[30] = '\0';
      timescampeonato[notimes].PontosGanhos = 0;
      timescampeonato[notimes].GolsMarcados = 0;
      timescampeonato[notimes].GolsSofridos = 0;
      timescampeonato[notimes].SaldoDeGols = 0;
      timescampeonato[notimes].Vitorias = 0;
      timescampeonato[notimes].Empates = 0;
      timescampeonato[notimes].Derrotas = 0;
      timescampeonato[notimes].GolAverage = 0;
      notimes++;
    }

    if (pos_visitante == -1 && notimes < NumeroMaxTimes && strcmp(dadosjogos[i].local, dadosjogos[i].visitante) != 0) {
      strncpy(timescampeonato[notimes].nome, dadosjogos[i].visitante, 30);
      timescampeonato[notimes].nome[30] = '\0';
      timescampeonato[notimes].PontosGanhos = 0;
      timescampeonato[notimes].GolsMarcados = 0;
      timescampeonato[notimes].GolsSofridos = 0;
      timescampeonato[notimes].SaldoDeGols = 0;
      timescampeonato[notimes].Vitorias = 0;
      timescampeonato[notimes].Empates = 0;
      timescampeonato[notimes].Derrotas = 0;
      timescampeonato[notimes].GolAverage = 0;
      notimes++;
    }
  }
  return notimes;
}

void computadadostimes(time *timescampeonato, int notimes, jogo *dadosjogos, int numerojogos) {
  int i;
  for (i = 0; i < numerojogos; ++i) {
    int pos_local = encontratime(timescampeonato, dadosjogos[i].local, notimes);
    int pos_visitante = encontratime(timescampeonato, dadosjogos[i].visitante, notimes);

    if (pos_local != -1 && pos_visitante != -1) {
      timescampeonato[pos_local].GolsMarcados += dadosjogos[i].golslocal;
      timescampeonato[pos_local].GolsSofridos += dadosjogos[i].golsvisitante;
      timescampeonato[pos_local].SaldoDeGols += (dadosjogos[i].golslocal - dadosjogos[i].golsvisitante);
      timescampeonato[pos_visitante].GolsMarcados += dadosjogos[i].golsvisitante;
      timescampeonato[pos_visitante].GolsSofridos += dadosjogos[i].golslocal;
      timescampeonato[pos_visitante].SaldoDeGols += (dadosjogos[i].golsvisitante - dadosjogos[i].golslocal);

      if (dadosjogos[i].golslocal > dadosjogos[i].golsvisitante) {
  timescampeonato[pos_local].PontosGanhos += 3;
  timescampeonato[pos_local].Vitorias++;
  timescampeonato[pos_visitante].Derrotas++;
} else if (dadosjogos[i].golslocal < dadosjogos[i].golsvisitante) {
  timescampeonato[pos_visitante].PontosGanhos += 3;
  timescampeonato[pos_visitante].Vitorias++;
  timescampeonato[pos_local].Derrotas++;
} else {
  timescampeonato[pos_local].PontosGanhos += 1;
  timescampeonato[pos_local].Empates++;
  timescampeonato[pos_visitante].PontosGanhos += 1;
  timescampeonato[pos_visitante].Empates++;
}

    }
  }

  for (i = 0; i < notimes; ++i) {
    int num_jogos = 0;
    for (int j = 0; j < numerojogos; ++j) {
      if (strcmp(timescampeonato[i].nome, dadosjogos[j].local) == 0 || strcmp(timescampeonato[i].nome, dadosjogos[j].visitante) == 0) {
        num_jogos++;
      }
    }
    timescampeonato[i].Derrotas = num_jogos - timescampeonato[i].Vitorias - timescampeonato[i].Empates;
  }

  for (i = 0; i < notimes; ++i) {
    if (timescampeonato[i].GolsSofridos != 0)
      timescampeonato[i].GolAverage = (float)timescampeonato[i].GolsMarcados / timescampeonato[i].GolsSofridos;
    else
      timescampeonato[i].GolAverage = timescampeonato[i].GolsMarcados;
  }
}

void imprimeclassificacao(time *timescampeonato, int notimes) {
  int i, j;
  time temp;

  for (i = 0; i < notimes - 1; ++i) {
    for (j = 0; j < notimes - i - 1; ++j) {
      if (timescampeonato[j].PontosGanhos < timescampeonato[j + 1].PontosGanhos ||
          (timescampeonato[j].PontosGanhos == timescampeonato[j + 1].PontosGanhos &&
           timescampeonato[j].SaldoDeGols < timescampeonato[j + 1].SaldoDeGols)) {
        temp = timescampeonato[j];
        timescampeonato[j] = timescampeonato[j + 1];
        timescampeonato[j + 1] = temp;
      }
    }
  }

  printf("Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average\n");
  for (i = 0; i < notimes; ++i) {
    printf("%d,%s,%d,%d,%d,%d,%d,%.3f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos,
           timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas,
           timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
  }
}

void informacoesTime(time *timescampeonato, int notimes, char *nomeTime) {
  int pos = encontratime(timescampeonato, nomeTime, notimes);
  
  if (pos != -1) {
    printf("Informações do time %s:\n", timescampeonato[pos].nome);
    printf("Pontos Ganhos: %d\n", timescampeonato[pos].PontosGanhos);
    printf("Gols Marcados: %d\n", timescampeonato[pos].GolsMarcados);
    printf("Gols Sofridos: %d\n", timescampeonato[pos].GolsSofridos);
    printf("Saldo de Gols: %d\n", timescampeonato[pos].SaldoDeGols);
    printf("Vitórias: %d\n", timescampeonato[pos].Vitorias);
    printf("Empates: %d\n", timescampeonato[pos].Empates);
    printf("Derrotas: %d\n", timescampeonato[pos].Derrotas);
    printf("Gol Average: %.3f\n", timescampeonato[pos].GolAverage);
  }
}


void salvaclassificacao(time *timescampeonato, int notimes, char *arquivo) {
  FILE *pont_arq;
  pont_arq = fopen(arquivo, "w");

  if (pont_arq == NULL) {
    printf("Erro na abertura do arquivo.");
    exit(1);
  }

  int i, j;
  time temp;

  for (i = 0; i < notimes - 1; ++i) {
    for (j = 0; j < notimes - i - 1; ++j) {
      if (timescampeonato[j].PontosGanhos < timescampeonato[j + 1].PontosGanhos ||
          (timescampeonato[j].PontosGanhos == timescampeonato[j + 1].PontosGanhos &&
           timescampeonato[j].SaldoDeGols < timescampeonato[j + 1].SaldoDeGols)) {
        temp = timescampeonato[j];
        timescampeonato[j] = timescampeonato[j + 1];
        timescampeonato[j + 1] = temp;
      }
    }
  }

  fprintf(pont_arq,"Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average\n");
  for (i = 0; i < notimes; ++i) {
    fprintf(pont_arq,"%d,%s,%d,%d,%d,%d,%d,%.3f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos,
           timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas,
           timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
  }

  fclose(pont_arq);
}


int main() {
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxJogos];
  int i, nojogos, golslocal = 0, golsvisitante = 0;
  char local[30], visitante[30];

  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for (i = 0; i < NumeroMaxJogos; ++i) {
    lenometime(local);
    lenometime(visitante);
    scanf("%d,%d", &golslocal, &golsvisitante);
    getchar(); // consome o enter do scanf

    if (golslocal < 0)
      break; // termina a entrada de dados

    if (strcmp(local, visitante) == 0)
      continue; // possui o mesmo nome time local e visitante

    strncpy(jogos[i].local, local, 30);
    strncpy(jogos[i].visitante, visitante, 30);
    jogos[i].golslocal = golslocal;
    jogos[i].golsvisitante = golsvisitante;
  }
  nojogos = i;

  int notimes = crialistatimes(times, jogos, nojogos);
  computadadostimes(times, notimes, jogos, nojogos);
  imprimeclassificacao(times, notimes);

  salvaclassificacao(times, notimes, "campeonatoIP.dat");
  
  char nomeTime[31];
  scanf("%s", nomeTime);
  informacoesTime(times, notimes, nomeTime);

  return 0;
}