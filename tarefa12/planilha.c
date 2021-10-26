#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 22

typedef struct celula{
    int numero;
    char *expressao;
    int chamado;
}celula;

celula resolve_expressao(celula c, celula **planilha);

int conta_digitos(char *s){
    int i = 1; /*começa com um espaço*/
    int c = 0;
    while (s[i] != ' '){
        c++;
        i++;
    }
    return c;    
}

/***Retorna o valor constante da célula**/
int resolve_numero(char *expressao){
    int mult = 1;
    int celula = 0;
    int digitos = conta_digitos(expressao);
    while (digitos != 0){
        if(expressao[digitos] != '-'){
            int num = (expressao[digitos] - '0') * mult;
            celula = celula + num;   
            mult = mult * 10;   
        }
        digitos--;              
    } 
    if(expressao[1] == '-'){
        celula = celula * (-1);
    }
    return celula;
}

/***Lê o arquivo e armazena em uma matriz**/
celula **le_arquivo(int linhas, int colunas, char nome_arquivo[]){
    int i,j;
    char *expressao;
    celula **planilha = calloc(linhas, sizeof(celula *));
    for(i=0;i<linhas;i++){
        planilha[i] = calloc(colunas, sizeof(celula));
    }
    FILE *arquivo = fopen(nome_arquivo, "r");
    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            fscanf(arquivo, "%m[^,\n]%*c", &expressao);
            planilha[i][j].expressao = expressao; 
            if(expressao[0] != '='){  /*valor constante*/
                planilha[i][j].numero = resolve_numero(planilha[i][j].expressao); 
            }
        }
    }
    fclose(arquivo);
    return planilha;
}

void destruir_planilha(celula **c, int m,int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            free(c[i][j].expressao);
        }
        free(c[i]);
    }
    free(c);
}

/***Encontra a linha a partir da coordenada da célula**/
int encontra_linha(char *coordenada){
    int i = 1, c = 0;  /*começa com a letra(coluna)*/
    while(coordenada[i] != '\0'){
        c++;
        i++;
    }
    int fator = 1;
    int num = 0;
    for(i=c;i>0;i--){
        num = num + ((coordenada[i] - '0') * fator);
        fator = fator * 10;
    }
    return num - 1;
}

/***Encontra a coluna a partir da coordenada da célula**/
int encontra_coluna(char coordenada){
    char *colunas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int j=0;
    while(colunas[j] != coordenada){
        j++;
    }
    return j;
}

/***Resolve uma expressão de 2 termos**/
int resolve_exp_binaria(char *exp, celula **planilha){
    char operador;
    char exp1[MAX],exp2[MAX];
    int i = 1, j = 0;
    while (exp[i] != ' '){
        exp1[j] = exp[i];
        i++;  
        j++;      
    }
    exp1[j] = '\0';
    i++;
    operador = exp[i];
    i = i+2;
    j = 0;
    while (exp[i] != ' '){
        exp2[j] = exp[i];
        i++;   
        j++;     
    }
    exp2[j] = '\0';
    celula c1,c2;
    i = encontra_linha(exp1);
    j = encontra_coluna(exp1[0]);
    c1 = planilha[i][j];
    if(c1.expressao[0] == '='){
        c1 = resolve_expressao(planilha[i][j],planilha);
    }
    i = encontra_linha(exp2);
    j = encontra_coluna(exp2[0]);
    c2 = planilha[i][j];
    if(c2.expressao[0] == '='){
        c2 = resolve_expressao(c2,planilha);
    }
    int resultado;
    if(operador == '+'){
        resultado = c1.numero + c2.numero;
    }
    else{
        resultado = c1.numero - c2.numero;
    }
    return resultado;
}

/***Resolve a expressão entre parenteses**/
int calcula_expressao(char *exp, celula **planilha){
    int i,j=0;
    char nova_exp[MAX];
    for(i=0;i<strlen(exp);i++){
        if(exp[i] == '('){
            while(exp[i] != ')'){
                nova_exp[j] = exp[i + 1];
                i++;
                j++;
            } 
        }
    }
    return resolve_exp_binaria(nova_exp,planilha);
}

/***Lê uma célula e resolve a expressão para achar seu valor**/
celula resolve_expressao(celula c, celula **planilha){
    if(c.expressao[2] == '('){
        c.numero = calcula_expressao(c.expressao,planilha);
    }
    else{     /*se refere apenas a uma outra célula sem calcular expressão*/
        int indice = 2, n = 0;
        char coordenada[MAX];
        while(c.expressao[indice] != ' '){
            coordenada[n] = c.expressao[indice];
            indice++; 
            n++;  
        }
        coordenada[n] = '\0';
        int i,j;
        j = encontra_coluna(coordenada[0]);
        i = encontra_linha(coordenada);
        if(planilha[i][j].expressao[0] == '='){
            c = resolve_expressao(planilha[i][j], planilha);
        }
        else{
            c.numero = planilha[i][j].numero;
        }        
    }
    return c;
}

void executa_acao(celula **planilha, char *coordenada, char acao){
    int i,j;
    i = encontra_linha(coordenada);
    j = encontra_coluna(coordenada[0]);
    celula c = planilha[i][j];
    if(acao == 'S'){
        int valor;
        scanf("%d ", &valor);
        printf("%s: %d -> %d\n", coordenada, c.numero, valor);
        planilha[i][j].numero = valor;
    }
    if(acao == 'G'){
        if(c.expressao[0] != '='){  /*valor constante*/  
            printf("%s: %d\n", coordenada, c.numero);              
        }
        else{   
            c = resolve_expressao(c,planilha);
            printf("%s: %d\n", coordenada, c.numero);     
        }
        
    }
}

int main(){
    char nome_arquivo[MAX];
    int linhas, colunas;
    scanf("%s %d %d ", nome_arquivo, &colunas, &linhas);
    celula **planilha = le_arquivo(linhas,colunas,nome_arquivo);
    char acao, coordenada[MAX];
    while(scanf("%c %s ", &acao, coordenada) != EOF){
        executa_acao(planilha,coordenada,acao);
    }
    destruir_planilha(planilha,linhas,colunas);
    return 0;
}