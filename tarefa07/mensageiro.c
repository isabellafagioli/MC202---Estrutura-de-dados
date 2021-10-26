#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/***Informações no cartão dado ao mensageiro**/
typedef struct cartao{
    int numero;
    char texto[800];
}cartao;

cartao inicializa_cartao(){
    cartao c;
    c.numero = 0;
    strcpy(c.texto,"\0");
    return c;
}

/***Implementação da árvore (baseado no que foi visto em aula)**/
typedef struct No{
    cartao dado;
    struct No *esq, *dir;
}No;

typedef No * ponteiro_no;

ponteiro_no criar_arvore(){
    return NULL;
}

ponteiro_no inserir(ponteiro_no r, cartao x){
    if(r == NULL){
        ponteiro_no novo = malloc(sizeof(No));
        novo->dir = NULL;
        novo->esq = NULL;
        novo->dado = x;
        r = novo;
    }
    else if(r->dado.numero>x.numero){
        r->esq = inserir(r->esq, x);
    }
    else{
        r->dir = inserir(r->dir, x);
    }
    return r;
}

ponteiro_no minimo(ponteiro_no r){
    if(r == NULL || r->esq == NULL){
        return r;
    }
    return minimo(r->esq);
}

ponteiro_no maximo(ponteiro_no r){
    if( r == NULL || r->dir == NULL){
        return r;
    }
    return maximo(r->dir);
}

ponteiro_no remover(ponteiro_no r, int x){
    if(r==NULL){
        return NULL;
    }
    if(x < r->dado.numero){
        r->esq = remover(r->esq,x);
    }
    else if(x > r->dado.numero){
        r->dir = remover(r->dir, x);        
    }
    else{
        if(r->esq == NULL && r->dir == NULL){   /*sem filhos*/
            free(r);
            return NULL;
        }
        else if(r->esq == NULL){      /*só filho direito*/
            ponteiro_no aux = r;
            aux = aux->dir;
            free(r);
            return aux;
        }
        else if(r->dir == NULL){      /*só filho esquerdo*/
            ponteiro_no aux = r;
            aux = aux->esq;
            free(r);
            return aux;
        }
        else{       /*tem os dois filhos*/
            ponteiro_no aux = maximo(r->esq);
            r->dado = aux->dado;
            aux->dado.numero = x;
            r->esq = remover(r->esq, x);            
        }
    }
    return r;
}

ponteiro_no acha_pai(ponteiro_no r, ponteiro_no x){
    if(r == NULL){
        return NULL;
    }
    if(r->esq == x|| r->dir== x){
        return r;
    }
    if(x->dado.numero < r->dado.numero){  /*tá na árvore esquerda*/
        return acha_pai(r->esq, x);
    }
    else{
        return acha_pai(r->dir, x);
    }
}

ponteiro_no ancestral_a_direita(ponteiro_no r, ponteiro_no x){
    if(x == NULL){
        return NULL;
    }
    ponteiro_no pai = acha_pai(r,x);
    if(pai == NULL || pai->esq == x){
        return pai;
    }
    else{
        return ancestral_a_direita(r, pai);
    }
}


ponteiro_no sucessor(ponteiro_no r, ponteiro_no x){
    if(r == NULL){
        return NULL;
    }
    if(x->dir != NULL){
        return minimo(x->dir);      
    }
    else{
        return ancestral_a_direita(r,x);
    }
}

ponteiro_no ta_na_arvore(ponteiro_no r, int x){
    if(r == NULL || r->dado.numero == x){
        return r;
    }
    if(x > r->dado.numero){
        return ta_na_arvore(r->dir,x);
    }
    else{
        return ta_na_arvore(r->esq,x);
    }
}

void libera_a_arvore(ponteiro_no r){
    if(r != NULL){
        libera_a_arvore(r->esq);
        libera_a_arvore(r->dir);
        free(r);
    }
}

/***Devemos imprimir em ordem crescente e para isso, percorremos a árvore do min ao max **/
void imprime_mensagem(ponteiro_no r){
    ponteiro_no imprime = minimo(r);
    ponteiro_no fim_arvore = maximo(r);
    while(imprime != fim_arvore){
        printf("%s", imprime->dado.texto);
        imprime = sucessor(r,imprime);
    }
    printf("%s", fim_arvore->dado.texto);
    printf("\n");
}

/***Junta a tríade de cartões e insere na árvore**/
ponteiro_no concatenar(ponteiro_no r, ponteiro_no no1, ponteiro_no no2, ponteiro_no no3){
    cartao c = inicializa_cartao();
    c.numero = no1->dado.numero + no2->dado.numero + no3->dado.numero;
    strcpy(c.texto,no1->dado.texto);
    strcat(c.texto,no2->dado.texto);
    strcat(c.texto,no3->dado.texto);
    r = inserir(r,c);
    return r;
}

/***insere a concatenação na árvore e remove a tríade**/
ponteiro_no inserir_concatenacao(ponteiro_no r, ponteiro_no no1, ponteiro_no no2, ponteiro_no no3){
    r = concatenar(r,no1,no2,no3);
    r = remover(r, no1->dado.numero);
    r = remover(r, no2->dado.numero);
    r = remover(r, no3->dado.numero);
    return r;
}

/***encontra uma tríade cuja soma seja o valor de auoridade**/
ponteiro_no encontra_triade(ponteiro_no r, int autoridade){
    ponteiro_no no1, no2, no3;
    int soma;
    no1 = minimo(r);
    ponteiro_no fim_arvore = maximo(r);
    while(no1 != fim_arvore){
        no2 = sucessor(r,no1);
        while(no2 != fim_arvore){
            soma = no1->dado.numero + no2->dado.numero;
            no3 = ta_na_arvore(r, autoridade - soma);
            if(no3 != NULL){
                r = inserir_concatenacao(r,no1,no2,no3);
                return r;
            }
            else{
                no2 = sucessor(r,no2);
            }
        }
        no1 = sucessor(r,no1);
    }
    return r;
}

int main(){
    int m=0, n=0, autoridade;
    char aspas;
    cartao c = inicializa_cartao();
    while(scanf("%d %d", &m, &n)!= EOF){
        ponteiro_no r = criar_arvore();
        for(int i=0;i<m;i++){
            scanf(" %d",&c.numero);
            scanf(" %c", &aspas);
            scanf("%[^\"]%*c", c.texto);
            r = inserir(r,c);
        }
        for (int i=0;i<n;i++){
                scanf("%d", &autoridade);
                r = encontra_triade(r, autoridade);
        }
        imprime_mensagem(r);
        libera_a_arvore(r);
     }
    return 0;      
}
