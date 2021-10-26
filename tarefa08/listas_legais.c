#include <stdio.h>
#include <stdlib.h>

/***Implementação da árvore balanceada rubro-negra esquerdista(como visto em aula)**/
enum cor {VERMELHO, PRETO};

typedef struct info{
    long int inteiro;
    long int contador;
}info;

typedef struct No{
    info dado;    
    enum cor cor;
    struct No *esq, *dir;    
}No;

typedef No * ponteiro_no;

ponteiro_no cria_arvore(){
    return NULL;
}

int eh_vermelho(ponteiro_no x){
    if(x == NULL){
        return 0;
    }
    return x->cor == VERMELHO;
}

int eh_preto(ponteiro_no x){
    if(x == NULL){
        return 1;
    }
    return x->cor == PRETO;
}

ponteiro_no rotaciona_para_esquerda(ponteiro_no r){
    ponteiro_no x = r->dir;
    r->dir = x->esq;
    x->esq = r;
    x->cor = r->cor;
    r->cor = VERMELHO;
    return x;
}

ponteiro_no rotaciona_para_direita(ponteiro_no r){
    ponteiro_no x = r->esq;
    r->esq = x->dir;
    x->dir = r;
    x->cor = r->cor;
    r->cor = VERMELHO;
    return x;
}

void sobe_vermelho(ponteiro_no r){
    r->cor = VERMELHO;
    r->esq->cor = PRETO;
    r->dir->cor = PRETO;
}

void libera_a_arvore(ponteiro_no r){
    if(r != NULL){
        libera_a_arvore(r->esq);
        libera_a_arvore(r->dir);
        free(r);
    }
}

ponteiro_no inserir(ponteiro_no r, long int x){
    ponteiro_no novo;
    if(r == NULL){
        novo = malloc(sizeof(No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->dado.inteiro = x;
        novo->dado.contador = 1;
        novo->cor = VERMELHO;
        return novo;
    }
    if(x < r->dado.inteiro){
        r->esq = inserir(r->esq, x);
    }
    else{
        r->dir = inserir(r->dir,x);
    }
    if(eh_vermelho(r->dir) && eh_preto(r->esq)){
        r = rotaciona_para_esquerda(r);
    }
    if(r->esq != NULL && eh_vermelho(r->esq) && eh_vermelho(r->esq->esq)){
        r = rotaciona_para_direita(r);
    }
    if(eh_vermelho(r->esq) && eh_vermelho(r->dir)){
        sobe_vermelho(r);
    }
    return r;
}

/***Retorna o ponteiro com o x buscado ou NULL**/
ponteiro_no ta_na_arvore(ponteiro_no r, long int x){
     if(r == NULL || r->dado.inteiro == x){
        return r;
    }
    if(x > r->dado.inteiro){
        return ta_na_arvore(r->dir,x);
    }
    else{
        return ta_na_arvore(r->esq,x);
    }
}

/***Insere o número caso não esteja na árvore e se estiver, aumenta o contdor dele**/
ponteiro_no insere_na_arvore(ponteiro_no r, long int x){
    ponteiro_no novo = ta_na_arvore(r,x);
    if(novo == NULL){
        r = inserir(r,x);
    }
    else{
        novo->dado.contador++;
    }
    return r;
}

/***Para saber quantas vezes um número aparece na árvore**/
void operacao_2(ponteiro_no r, long int x){
    ponteiro_no buscado = ta_na_arvore(r,x);
    if(buscado != NULL){
        printf("%ld\n", buscado->dado.contador);
    }
    else{
        printf("0\n");
    }
}

/****Percorre a árvore somando ao contador**/
int percorre_arvore(ponteiro_no r, int c){
    if(r != NULL){
        c = percorre_arvore(r->esq,c) + percorre_arvore(r->dir,c);
        if(r->dado.contador != r->dado.inteiro){
            if(r->dado.contador < r->dado.inteiro){   /*devemos tirar todos esses numeros da lista */
                c = c + r->dado.contador;
            }
            if(r->dado.contador > r->dado.inteiro){  /*devemos tirar os números que estão a mais do que o contador*/
                c = c + r->dado.contador - r->dado.inteiro; 
            }
        }
    }
    return c;
}
/***Descobre quantos itens devem ser retirados da árvore para que a lista seja legal**/
void operacao_3(ponteiro_no r){
    int c = 0;
    c = percorre_arvore(r,c);
    printf("%d\n", c);

}

/***Descobre a operação buscada e encaminha para ela**/
void operacao(ponteiro_no r, int op){
    info x;
    if(op == 1){
        scanf("%ld", &x.inteiro);
        r = insere_na_arvore(r,x.inteiro);
    }
    if(op == 2){
        scanf("%ld", &x.inteiro);
        operacao_2(r,x.inteiro);
    }
    if(op==3){
        operacao_3(r);
    }
}

int main(){
    int n,k,op,i=0;
    info x;
    ponteiro_no r = cria_arvore();
    scanf("%d %d", &n, &k);
    for(i=0;i<n;i++){
        scanf("%ld", &x.inteiro);
        r = insere_na_arvore(r,x.inteiro);
    }
    for(i=0;i<k;i++){
        scanf("%d ", &op);
        operacao(r,op);
    }
    libera_a_arvore(r);

    return 0;
}




