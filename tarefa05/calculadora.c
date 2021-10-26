#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    struct No *proximo;  
} No;

typedef struct No * ponteiro_no;

ponteiro_no cria_lista(){
    return NULL;
}

ponteiro_no adiciona_elemento(ponteiro_no lista, int elemento){
    ponteiro_no novo_elemento;
    novo_elemento = malloc(sizeof(No));
    if (novo_elemento == NULL) {
           printf("Memoria insuficiente.\n");
           exit(1);  
        }
    novo_elemento->dado = elemento;
    novo_elemento->proximo = lista;
    return novo_elemento;
}

ponteiro_no transforma_em_lista(char *n){
    /**Cria uma lista ligada a partir da string */
    int i = 0, algarismo;
    ponteiro_no lista = cria_lista();
    while(n[i]!='\0'){
        algarismo = n[i] - '0';
        lista = adiciona_elemento(lista, algarismo);
        i++;
    }
    return lista;
}

char *desloca_elementos(char *n){
    int i;
    for(i=24;i>0;i--){
        n[i] = n[i-1];
    }
    return n;
}

int conta_elementos(ponteiro_no lista){
    /**Conta os elementos da lista ligada*/
    int contador = 0;
    while (lista != NULL){
        contador++;
        lista = lista->proximo;        
    }
    return contador;    
}
int conta_numeros(char *n){
    /**Conta quantos números tem na string de entrada*/
    int i = 0;
    while(n[i] != '\0'){
        i++;
    }
    return i;
}

char *iguala_tamanho(char *n_menor, char *n_maior){
    /**Iguala o tamanho das strings de entrada*/
    while(conta_numeros(n_menor)<conta_numeros(n_maior)){
        n_menor = desloca_elementos(n_menor);
        n_menor[0] = '0';
    }
    return n_menor;
}

void destruir_lista(ponteiro_no lista){
    if(lista!=NULL){
        destruir_lista(lista->proximo);
        free(lista);
    }
}

void imprime(ponteiro_no lista){
    if(lista != NULL){
        printf("%d", lista->dado);
        imprime(lista->proximo);
    }
}

int eh_maior(char *n1, char *n2){
    /**Descobre qual número é maior a partir da string*/
    int i;
    if(conta_numeros(n1)<conta_numeros(n2)){
        return 0;               
    }
    else if(conta_numeros(n1)>conta_numeros(n2)){
        return 1;
    }
    else{        
        for(i=0;i<conta_numeros(n1);i++){
            if(n1[i] - '0'> n2[i] - '0'){
                return 1;
            }
            else if(n1[i] - '0'< n2[i] - '0'){
                return 0;
            }      
        }
    }
    return 0;
}

int eh_zero(ponteiro_no lista){
    /**Descobre se a lista é apenas 0*/
    while(lista != NULL){
        if(lista->dado != 0){
            return 0;
        }
        lista = lista->proximo;
    }
    return 1;
}

ponteiro_no numeros_validos(ponteiro_no lista){
    /**Retira os zeros a esquerda*/
    ponteiro_no lista_sem_zero = lista;
    while (lista_sem_zero != NULL){
        if(lista_sem_zero->dado == 0){
            lista_sem_zero = lista_sem_zero->proximo;
        }
        else{
            break;
        }
    }
    return lista_sem_zero;
    
}

ponteiro_no soma_por_lista(ponteiro_no lista1, ponteiro_no lista2){
    ponteiro_no lista_soma = cria_lista();
    int elemento;
    while (lista1 != NULL){
        elemento = lista1->dado + lista2->dado;
        if(elemento>=10){
            elemento = elemento % 10;
            if(lista1->proximo != NULL){
            lista1->proximo->dado = lista1->proximo->dado + 1;
            }
            else{
                lista_soma = adiciona_elemento(lista_soma, elemento); 
                lista_soma = adiciona_elemento(lista_soma, 1); 
                break;
            }
        }
        lista_soma = adiciona_elemento(lista_soma, elemento); 
        lista1 = lista1->proximo;
        lista2 = lista2->proximo;
    }
    return lista_soma;
}

ponteiro_no sub_por_lista(ponteiro_no lista_menor, ponteiro_no lista_maior){
    ponteiro_no lista_sub = cria_lista();
    int elemento;
    while(lista_maior != NULL){
        if(lista_maior->dado>=lista_menor->dado){
            elemento = lista_maior->dado - lista_menor->dado;
        }
        else{
            elemento = 10 + lista_maior->dado - lista_menor->dado;
            lista_maior->proximo->dado--;
        }
        lista_sub = adiciona_elemento(lista_sub, elemento);
        lista_menor = lista_menor->proximo;
        lista_maior = lista_maior->proximo;

    }
    return lista_sub;
}
ponteiro_no iguala_tamanho_lista(ponteiro_no lista1, ponteiro_no lista2){
    /**Iguala o tamanho das listas*/
    while (conta_elementos(lista1) < conta_elementos(lista2)){
        lista1 = adiciona_elemento(lista1, 0);
    }
    return lista1;
}

ponteiro_no inverte_lista(ponteiro_no lista){
    /**Inverte a ordem dos números na lista para que possam ser trabalhados de forma correta na soma e subtração*/
    ponteiro_no nova_lista = cria_lista();
    ponteiro_no p_aux = lista;
    while(lista != NULL){
        nova_lista = adiciona_elemento(nova_lista, lista->dado);
        lista = lista->proximo;
    }
    if(p_aux != NULL){
        destruir_lista(p_aux);
    }
    return nova_lista;
}

ponteiro_no mult_por_lista(ponteiro_no lista_maior, ponteiro_no lista_menor){
    ponteiro_no lista_mult = cria_lista();
    int i;
    while (lista_menor != NULL){
        lista_mult = inverte_lista(lista_mult);
        lista_mult = iguala_tamanho_lista(lista_mult, lista_maior);
        lista_mult = inverte_lista(lista_mult);
        for(i = 0; i< lista_menor->dado; i++){
            lista_maior = inverte_lista(lista_maior);
            lista_maior = iguala_tamanho_lista(lista_maior, lista_mult);
            lista_maior = inverte_lista(lista_maior);
            ponteiro_no p_aux = lista_mult;
            lista_mult = soma_por_lista(lista_mult, lista_maior);
            free(p_aux);
            lista_mult = inverte_lista(lista_mult);
        }
        lista_maior = adiciona_elemento(lista_maior, 0);
        lista_menor = lista_menor->proximo;       
    } 
    lista_mult = inverte_lista(lista_mult);
    return lista_mult;
}

void soma(char *n1,char *n2){
    ponteiro_no lista_n1, lista_n2, lista_resultado;
    if(conta_numeros(n1)<conta_numeros(n2)){
        n1 = iguala_tamanho(n1, n2);        
    }
    else if(conta_numeros(n1)>conta_numeros(n2)){
        n2 = iguala_tamanho(n2, n1);
    }
    lista_n1 = transforma_em_lista(n1);
    lista_n2 = transforma_em_lista(n2);
    lista_resultado = soma_por_lista(lista_n1, lista_n2);
    imprime(lista_resultado);
    printf("\n");
    destruir_lista(lista_n1);
    destruir_lista(lista_n2);
    destruir_lista(lista_resultado);
}


void subtrai(char *n1,char *n2){
    ponteiro_no lista_n1, lista_n2, lista_resultado;
    if(eh_maior(n1, n2) == 1){
        n2 = iguala_tamanho(n2, n1);
        lista_n1 = transforma_em_lista(n2);
        lista_n2 = transforma_em_lista(n1);
    }
    else{
        n1 = iguala_tamanho(n1, n2);
        lista_n1 = transforma_em_lista(n1);
        lista_n2 = transforma_em_lista(n2);
    }
    lista_resultado = sub_por_lista(lista_n1, lista_n2);
    if(eh_zero(lista_resultado)){
        printf("0");
    }
    else{
        lista_resultado = numeros_validos(lista_resultado);
        imprime(lista_resultado);
    }    
    printf("\n");
    destruir_lista(lista_n1);
    destruir_lista(lista_n2);
    destruir_lista(lista_resultado);
}

void multiplica(char *n1,char *n2){
    ponteiro_no lista_n1, lista_n2, lista_resultado;
    if(eh_maior(n1, n2) == 1){
            lista_n1 = transforma_em_lista(n1);
            lista_n2 = transforma_em_lista(n2);
        }
        else{
            lista_n1 = transforma_em_lista(n2);
            lista_n2 = transforma_em_lista(n1);
        }
    lista_resultado = mult_por_lista(lista_n1, lista_n2);
    if(eh_zero(lista_resultado)){
        printf("0");
    }
    else{
        lista_resultado = numeros_validos(lista_resultado);
        imprime(lista_resultado);
    }    
    printf("\n");
    destruir_lista(lista_n1);
    destruir_lista(lista_n2);
    destruir_lista(lista_resultado);
}

void calcular(char op, char *n1, char *n2){
    /**Define qual operação será feita*/
    if(op == '+'){
        soma(n1,n2);
    }
    else if(op == '-'){
        subtrai(n1,n2);
    }
    else if(op == '*'){
        multiplica(n1,n2);
    }

}

int main(){
    int n, i;
    char op;
    char n1[24], n2[24];
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf(" %c", &op);
        scanf("%s %s", n1, n2);
        calcular(op,n1,n2);
    }
    return 0;
}