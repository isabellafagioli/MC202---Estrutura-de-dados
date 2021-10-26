#include <stdio.h>
#include "professor_carlos.h"


void ler_entrada(int *k, int *n, Turma turmas[50]){
    int i, j;
    scanf("%d %d", &*n, &*k);
    for(i=0;i<*n;i++){
        scanf("%d", &turmas[i].qtd);
        for(j=0;j<turmas[i].qtd;j++){
            scanf("%s %s %d %d %d", turmas[i].alunos[j].nome, turmas[i].alunos[j].sobrenome, &turmas[i].alunos[j].nascimento.dia, &turmas[i].alunos[j].nascimento.mes, &turmas[i].alunos[j].nascimento.ano);
        }
    }
}
int encontrar_operacao(){
    int operacao;
    scanf("%d", &operacao);
    return operacao;
}
int main(){
    Turma turmas[50];
    int i;
    int k, n;
    ler_entrada(&k, &n, turmas);
    for(i=0;i<k;i++){
        int operacao = encontrar_operacao();
        if(operacao==1){
            int j;
            scanf("%d", &j);
            procura_novo_na_turma(turmas, turmas[j].qtd, j);
        }
        else if(operacao==2){
            int j;
            scanf("%d", &j);
            procura_velho_na_turma(turmas, turmas[j].qtd, j);
        }
        else if(operacao==3){
            procura_velho_todas_turmas(turmas, n);
        }
        else if(operacao==4){
            procura_novo_todas_turmas(turmas, n);
        }
        else if(operacao==5){
            char s[5];
            scanf("%s", s);
            conta_substrings(turmas, n, s);  
        }
        else if(operacao==6){
            Aluno aluno;
            int j;
            scanf("%d %s %s %d %d %d", &j, aluno.nome, aluno.sobrenome, &aluno.nascimento.dia, &aluno.nascimento.mes, &aluno.nascimento.ano);
            add_aluno(turmas, aluno, j);
        }
        else if(operacao==7){
            int j;
            scanf("%d", &j);
            remove_aluno(turmas, j);
        }
    }
    return 0;
}

