#include <stdio.h>
#include "professor_carlos.h"

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
    int i;
    Turma turma_escolhida = t[j];
    Aluno aluno_mais_novo = turma_escolhida.alunos[0];
    for(i=1;i<qtd_turmas;i++){
        if(turma_escolhida.alunos[i].nascimento.ano> aluno_mais_novo.nascimento.ano){
            aluno_mais_novo = turma_escolhida.alunos[i];
        }
        else if(turma_escolhida.alunos[i].nascimento.ano== aluno_mais_novo.nascimento.ano){
            if(turma_escolhida.alunos[i].nascimento.mes> aluno_mais_novo.nascimento.mes){
                aluno_mais_novo = turma_escolhida.alunos[i];
            }
            else if(turma_escolhida.alunos[i].nascimento.mes== aluno_mais_novo.nascimento.mes){
                if(turma_escolhida.alunos[i].nascimento.dia> aluno_mais_novo.nascimento.dia){
                    aluno_mais_novo = turma_escolhida.alunos[i];
                }
                else if(turma_escolhida.alunos[i].nascimento.dia== aluno_mais_novo.nascimento.dia){
                        aluno_mais_novo = coloca_ordem_alfabetica(aluno_mais_novo, turma_escolhida.alunos[i]);
                }
            }
        }

    }
    printf("%s\n", aluno_mais_novo.nome);
    return aluno_mais_novo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    int i;
    Turma turma_escolhida = t[j];
    Aluno aluno_mais_velho = turma_escolhida.alunos[0];
    for(i=1;i<qtd_turmas;i++){
        if(turma_escolhida.alunos[i].nascimento.ano< aluno_mais_velho.nascimento.ano){
            aluno_mais_velho = turma_escolhida.alunos[i];
        }
        else if(turma_escolhida.alunos[i].nascimento.ano== aluno_mais_velho.nascimento.ano){
            if(turma_escolhida.alunos[i].nascimento.mes< aluno_mais_velho.nascimento.mes){
                aluno_mais_velho = turma_escolhida.alunos[i];
            }
            else if(turma_escolhida.alunos[i].nascimento.mes== aluno_mais_velho.nascimento.mes){
                if(turma_escolhida.alunos[i].nascimento.dia< aluno_mais_velho.nascimento.dia){
                    aluno_mais_velho = turma_escolhida.alunos[i];
                }
                else if(turma_escolhida.alunos[i].nascimento.dia== aluno_mais_velho.nascimento.dia){
                    aluno_mais_velho = coloca_ordem_alfabetica(aluno_mais_velho, turma_escolhida.alunos[i]);
                   }
                    }
                }
            }
    printf("%s\n", aluno_mais_velho.sobrenome);
    return aluno_mais_velho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    int c, i;
    Aluno aluno_mais_velho = t[0].alunos[0];
    for(c = 0;c < qtd_turmas;c++){
        for(i = 0;i < t[c].qtd;i++){
            if(t[c].alunos[i].nascimento.ano < aluno_mais_velho.nascimento.ano){
                aluno_mais_velho = t[c].alunos[i];
            }
            else if(t[c].alunos[i].nascimento.ano == aluno_mais_velho.nascimento.ano){
                if(t[c].alunos[i].nascimento.mes < aluno_mais_velho.nascimento.mes){
                    aluno_mais_velho = t[c].alunos[i];
                }
                else if(t[c].alunos[i].nascimento.mes == aluno_mais_velho.nascimento.mes){
                    if(t[c].alunos[i].nascimento.dia < aluno_mais_velho.nascimento.dia){
                        aluno_mais_velho = t[c].alunos[i];
                    }
                    else if(t[c].alunos[i].nascimento.dia == aluno_mais_velho.nascimento.dia){
                        aluno_mais_velho = coloca_ordem_alfabetica(aluno_mais_velho, t[c].alunos[i]);
                    }
                }
            }
        }
    }
    printf("%s\n", aluno_mais_velho.nome);
    return aluno_mais_velho;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
    int c, i;
    Aluno aluno_mais_novo = t[0].alunos[0];
    for(c=0;c<qtd_turmas;c++){
        for(i=0;i<t[c].qtd;i++){
            if(t[c].alunos[i].nascimento.ano> aluno_mais_novo.nascimento.ano){
            aluno_mais_novo = t[c].alunos[i];
        }
            else if(t[c].alunos[i].nascimento.ano== aluno_mais_novo.nascimento.ano){
                if(t[c].alunos[i].nascimento.mes> aluno_mais_novo.nascimento.mes){
                    aluno_mais_novo = t[c].alunos[i];
            }
                else if(t[c].alunos[i].nascimento.mes== aluno_mais_novo.nascimento.mes){
                    if(t[c].alunos[i].nascimento.dia> aluno_mais_novo.nascimento.dia){
                        aluno_mais_novo = t[c].alunos[i];
                }
                    else if(t[c].alunos[i].nascimento.dia== aluno_mais_novo.nascimento.dia){
                        aluno_mais_novo = coloca_ordem_alfabetica(aluno_mais_novo, t[c].alunos[i]);
                            }
                    }
                }
            }
        }
    printf("%s\n", aluno_mais_novo.sobrenome);
    return aluno_mais_novo;
}

int add_aluno(Turma t[], Aluno A, int j){
    t[j].alunos[t[j].qtd] = A;
    t[j].qtd = t[j].qtd + 1;
    printf("%d\n", t[j].qtd);
    return t[j].qtd;
}

int remove_aluno(Turma t[], int j){
    t[j].qtd = t[j].qtd - 1;
    printf("%d\n", t[j].qtd);
    return t[j].qtd;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao){
    int c, i, qtd_substrings = 0;
    for(c=0;c<qtd_turmas;c++){
        for(i=0;i<t[c].qtd;i++){
           char *string = t[c].alunos[i].nome;
           int j;
           for (j = 0; string[j] != '\0'; j++){
                if(existe_substring(j, padrao, string) == 1){
                    qtd_substrings = qtd_substrings + 1;
                    break;
                }
            }                  
        }                   
    }         
    printf("%d\n", qtd_substrings);
    return qtd_substrings;
}

int conta_letras(char *palavra){
    int tamanho_palavra, i;
    for(i=0;i<=15;i++){
        if(palavra[i]!= '\0'){
            tamanho_palavra= tamanho_palavra + 1;
        } 
    }
    return tamanho_palavra; 
}

Aluno coloca_ordem_alfabetica(Aluno aluno1, Aluno aluno2){
    int i,c = 0;
    if(conta_letras(aluno1.nome)>=conta_letras(aluno2.nome)){
        c = conta_letras(aluno1.nome);
    }
    else{
        c = conta_letras(aluno2.nome);
    }
    for(i=0;i<c;i++){
        if(aluno1.nome[i]<aluno2.nome[i]){
            return aluno1;
            break;
        }
        else if(aluno1.nome[i]>aluno2.nome[i]){
            return aluno2;
            break;
        }
    }
    if(conta_letras(aluno1.sobrenome)>=conta_letras(aluno2.sobrenome)){
        c = conta_letras(aluno1.sobrenome);
    }
    else{
        c = conta_letras(aluno2.sobrenome);
    }
    for(i=0;i<c;i++){
        if(aluno1.sobrenome[i]<aluno2.sobrenome[i]){
            return aluno1;
            break;
        }
        else if(aluno1.sobrenome[i]>aluno2.sobrenome[i]){
            return aluno2;
            break;
        }
    }
    return aluno1;
}

int existe_substring(int j, char *padrao, char *string){
    int z;
    for (z = 0; padrao[z] != '\0'; z++){
        if((z+j)<conta_letras(string)-1){
            if (string[j + z] != padrao[z] || (string[j + z] == '\0' && padrao[z] != '*')){
                return 0;                          
            }
        }
    }
    return 1;
}
