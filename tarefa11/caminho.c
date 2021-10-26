#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10

typedef struct posicao{
    double x;
    double y;
}posicao;

typedef struct ponto{
    int indice;
    posicao coordenadas;
    char tipo;
}ponto;

/***Implementação do grafo (visto em aula)**/
typedef struct No {
    ponto p;
    double dist;
    struct No *prox;
} No;

typedef No * p_no;

typedef struct {
    p_no *adjacencia;
    int n;
} Grafo;

typedef Grafo * p_grafo;

p_grafo criar_grafo(int n) {
    int i;
    p_grafo g = malloc(sizeof(Grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));
    for (i = 0; i < n; i++){
        g->adjacencia[i] = NULL;
    }
    return g;
}

void libera_lista(p_no lista) {
    if (lista != NULL) {
        libera_lista(lista->prox);
    }
    free(lista);
}

void destroi_grafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++)
        libera_lista(g->adjacencia[i]);
    free(g->adjacencia);
    free(g);
}

p_no insere_na_lista(p_no lista, ponto p) {
    p_no novo = malloc(sizeof(No));
    novo->p = p;
    novo->prox = lista;
    return novo;
}


double dist_euclidiana(ponto p1, ponto p2){
    double DELTA_x = p1.coordenadas.x - p2.coordenadas.x;
    double DELTA_y = p1.coordenadas.y - p2.coordenadas.y;
    return sqrt(pow(DELTA_x, 2) + pow(DELTA_y, 2));
}

void insere_aresta(p_grafo g, ponto p1, ponto p2) {
    g->adjacencia[p1.indice] = insere_na_lista(g->adjacencia[p1.indice], p2);
    /*Determina o "peso" da aresta*/
    g->adjacencia[p1.indice]->dist = dist_euclidiana(p1,p2); 
}

/***Pega a lista ligada de pontos da entrada e transforma em um grafo**/
p_grafo transforma_em_grafo(p_no lista, p_grafo g){
    p_no lista_aux = lista;
    p_no aux = lista;     /*para poder liberar depois*/
    while(lista != NULL){
        while (lista_aux != NULL){
            /*não adiciona o início nem o próprio ponto a lista de adjacência*/
            if(lista_aux->p.indice != lista->p.indice && lista_aux->p.indice != 0){ 
                insere_aresta(g,lista->p, lista_aux->p);
            }  
            lista_aux = lista_aux->prox;
        }
        lista_aux = aux;
        lista = lista->prox;      
    }
    libera_lista(aux);
    return g;
}

/***Determina se existe um caminho cuja maior aresta é menor que d**/
int encontra_caminho(p_grafo g, int d, p_no vizinhos, int *visitados){
    while(vizinhos != NULL){
        if(visitados[vizinhos->p.indice] == 0){
            if(vizinhos->dist <= d){
                if(vizinhos->p.tipo == 'L'){
                    return 1;
                }
                else{
                    visitados[vizinhos->p.indice] = 1;
                    if(encontra_caminho(g,d,g->adjacencia[vizinhos->p.indice], visitados) == 1){
                        return 1;
                    }
                }
            }
        }
        vizinhos = vizinhos->prox;
    }
    return 0;
}

void zera(int *vetor, int tamanho){
    for(int i=0;i<tamanho;i++){
        vetor[i] = 0;
    }
}

/***Define uma distância mínima tal que exista um caminho em que todas
 * as arestas sejam menores que ela**/
int acha_distancia(p_grafo g, int d_max){
    int d, d_min = 0;
    int *visitados = malloc(g->n * sizeof(int));
    while (d_min != d_max){
        d = (d_max + d_min)/2;
        zera(visitados, g->n);
        visitados[0] = 1;
        if(encontra_caminho(g,d,g->adjacencia[0],visitados) == 0){
            d_min = d;
        }
        else{
            d_max = d;
        }
        if(abs(d_min - d_max) == 1){   /*se os limites forem muito próximos*/
            if(encontra_caminho(g,d_min,g->adjacencia[0],visitados) == 1){
                d = d_min;
            }
            else{
                d = d_max;
            }
            break;
        }
    }  
    free(visitados);
    return d;    
}

/***Encontra a maior aresta do grafo**/
int acha_dist_max(p_grafo g){
    int i;
    double d_max = 0;
    p_no lista;
    for(i=0;i<g->n;i++){
       lista = g->adjacencia[i];
       while((lista != NULL)){
           if(lista->dist > d_max){
               d_max = lista->dist;
           }           
           lista = lista->prox;
       }       
    }
    return (int) ceil(d_max);
}

int main(){
    ponto p, ini;
    int n = 1;
    /*como não sabemos a quantidade de pontos, vamos inserí-los numa lista 
    antes de colocar no grafo*/
    p_no lista_pontos = NULL;
    scanf("%lf %lf", &ini.coordenadas.x, &ini.coordenadas.y);
    ini.indice = 0;
    lista_pontos = insere_na_lista(lista_pontos, ini);
    char *s = calloc(MAX, sizeof(char));
    while(scanf("%lf %lf %s", &p.coordenadas.x, &p.coordenadas.y, s) != EOF){
        p.tipo = s[0];
        p.indice = n;
        n++;
        lista_pontos = insere_na_lista(lista_pontos, p);
    }
    p_grafo grafo = criar_grafo(n);
    grafo = transforma_em_grafo(lista_pontos, grafo);
    int maior_aresta = acha_dist_max(grafo);
    int d = acha_distancia(grafo, maior_aresta);
    free(s);
    printf("%d\n", d);
    destroi_grafo(grafo);
    return 0;
}