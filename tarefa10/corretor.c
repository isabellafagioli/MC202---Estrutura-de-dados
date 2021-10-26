#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***Implmentação do hash (visto em aula)**/
typedef struct No{
    char chave[26];
    struct No * prox;
} No;
typedef No *p_no;

#define MAX 8191

typedef struct Hash{
    p_no vetor[MAX];
}Hash;

typedef Hash * p_hash;

p_hash criar_hash(){
    p_hash h = malloc(MAX * sizeof(p_no));
    int i;
    for(i=0;i<MAX;i++){
        h->vetor[i] = NULL;
    }
    return h;
}

void destruir_lista(p_no lista){
    if(lista != NULL){
        destruir_lista(lista->prox);
    }
    free(lista);
}

void destruir_hash(p_hash h){
    int i;
    for(i=0;i<MAX;i++){
       destruir_lista(h->vetor[i]);
    }
    free(h);
}

int hash(char *chave) {
    int i, n = 0;
    for (i = 0; i < strlen(chave); i++)
    n = (256 * n + chave[i]) % MAX;
    return n;
}

p_no inserir_lista(p_no vetor, char *chave){
    p_no novo;
    novo = calloc(1,sizeof(No));
    if(novo == NULL){
        printf("Memoria insuficiente.\n");
        exit(1);  
    }
    for(int i=0;i<strlen(chave);i++){
        novo->chave[i] = chave[i]; 
    }
    novo->prox = vetor;
    return novo;
}

void inserir(p_hash h, char *chave) {
    int n = hash(chave);
    h->vetor[n] = inserir_lista(h->vetor[n], chave);
}

char *remove_caractere(char *palavra, int posicao){
    int i;
    char *palavra_errada = calloc(25,sizeof(char));
    for(i=0;i<posicao;i++){
        palavra_errada[i] = palavra[i];
    }
    for(i=posicao;i<strlen(palavra);i++){
        palavra_errada[i] = palavra[i+1];
    }
    return palavra_errada;
}

char *insere_caractere(char *palavra, int posicao, char letra){
    int i;
    char *palavra_errada = calloc(27,sizeof(char));
    for(i=0;i<posicao;i++){
        palavra_errada[i] = palavra[i];
    }
    palavra_errada[posicao] = letra;
    for(i=posicao + 1;i<strlen(palavra) + 1;i++){
        palavra_errada[i] = palavra[i-1];
    }
    return palavra_errada;
}

char *troca_caractere(char *palavra, int posicao, char letra){
    char *palavra_errada = calloc(26,sizeof(char));
    strcpy(palavra_errada, palavra);
    palavra_errada[posicao] = letra;
    return palavra_errada;
}

/***Encontra todas as possíveis variações de UM erro para uma palavra**/
void achar_variacoes(p_hash h, char *palavra){
    int n = strlen(palavra);
    int i,j;
    char *palavra_errada = NULL;
    char *alfabeto = "abcdefghijklmnopqrstuvwxyz";
    /*Um caractere a menos*/
    for(i=0;i<n;i++){
        palavra_errada = remove_caractere(palavra, i);
        inserir(h, palavra_errada);
        free(palavra_errada);
    }
    /*Um caractere a mais*/
    for(i=0;i<n;i++){
        for(j=0;j<strlen(alfabeto);j++){
            palavra_errada = insere_caractere(palavra, i, alfabeto[j]);
            inserir(h,palavra_errada);
            free(palavra_errada);
        }
    }
    /*Um caractere trocado*/
    for(i=0;i<n;i++){
        for(j=0;j<strlen(alfabeto);j++){
            palavra_errada = troca_caractere(palavra, i, alfabeto[j]);
            inserir(h,palavra_errada);
            free(palavra_errada);
        }
    }

}

/***Verifica se a palavra está no dicionário**/
int tem_palavra(p_no vetor, char *chave){
    if(vetor == NULL){
        return 0;
    }
    if(strcmp(vetor->chave, chave) == 0){
        return 1;
    }
    else{
        return tem_palavra(vetor->prox, chave);
    }
}

/***Verifica se a palavra está igual ao dicionário ou igual a uma palavra com um erro**/
void precisa_correcao(p_hash dicionario, p_hash palavras_erradas, char *palavra){
    int h = hash(palavra);
    if(tem_palavra(dicionario->vetor[h], palavra) == 1){
        printf("verde\n");
    }
    else if(tem_palavra(palavras_erradas->vetor[h], palavra)){
        printf("amarelo\n");
    }
    else{
        printf("vermelho\n");
    }
}

int main(){
    char *palavra = calloc(26,sizeof(char));
    int n,q,i;
    p_hash dicionario = criar_hash();
    p_hash erro_digitacao = criar_hash();
    scanf("%d %d", &n, &q);
    for(i=0;i<n;i++){
        scanf("%s", palavra);
        inserir(dicionario,palavra);
        achar_variacoes(erro_digitacao, palavra);
    }
    for(i=0;i<q;i++){
        scanf("%s", palavra);
        precisa_correcao(dicionario, erro_digitacao, palavra);
    }
    destruir_hash(dicionario);
    destruir_hash(erro_digitacao);
    free(palavra);
    return 0;
}