#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 250


typedef struct posicao{
    int x;
    int y;
}posicao;

typedef struct cliente{
    char nome[16];
    double avaliacao;
    posicao inicio;
    posicao destino;
    int cancelado;
}cliente;

typedef struct FP{
    cliente *c;
    int n;
}FP;
typedef FP * p_fp;

typedef struct relatorio{
    cliente corrida_em_andamento;
    posicao inicial;
    int tem_corrida_acontecendo;
    int km_rodado;
    int km_recebido;
    double rend_bruto;
    double despesas;
    double rend_liq;
}relatorio;

/***Funções para implementação de max heap (vistas em aula)**/
#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1) 
#define F_DIR(i) (2*i+2) 

void troca(cliente *a, cliente *b) {
    cliente t = *a;
    *a = *b;
    *b = t;
}

p_fp criar_filaprio() {
    p_fp fprio = malloc(sizeof(FP));
    fprio->c = malloc(MAX * sizeof(cliente));
    fprio->n = 0;
    return fprio;
}

void sobe_no_heap(p_fp fprio, int k) {
    if (k > 0 && fprio->c[PAI(k)].avaliacao < fprio->c[k].avaliacao){
        troca(&fprio->c[k], &fprio->c[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }
}

void insere(p_fp fprio, cliente c){
    fprio->c[fprio->n] = c;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}

void desce_no_heap(p_fp fprio, int k){
    int maior_filho;
    if(F_ESQ(k) >= fprio->n && F_DIR(k) >= fprio->n){
        return;
    }
    if (F_ESQ(k) < fprio->n) {
        maior_filho = F_ESQ(k);
    }
    if (F_DIR(k) < fprio->n && fprio->c[F_ESQ(k)].avaliacao < fprio->c[F_DIR(k)].avaliacao){
        maior_filho = F_DIR(k);
    }
    if (maior_filho < fprio->n && fprio->c[k].avaliacao < fprio->c[maior_filho].avaliacao) {
        troca(&fprio->c[k], &fprio->c[maior_filho]);
        desce_no_heap(fprio, maior_filho);
    }
}

cliente extrai_maximo(p_fp fprio) {
    cliente c = fprio->c[0];
    troca(&fprio->c[0], &fprio->c[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return c;
}

int calcula_distancia(posicao inicial, posicao final){
    int d;
    d = abs(final.x - inicial.x) + abs(final.y - inicial.y);  /*distancia de Manhattan*/
    return d;
}
/***Faz os cálculos e imprime**/
void calcula_relatorio(relatorio r){
    r.km_rodado = r.km_rodado + r.km_recebido;
    r.despesas = r.despesas + (r.km_rodado * 0.4104);
    r.rend_bruto = r.rend_bruto + (r.km_recebido * 1.4);
    r.rend_liq = 0.75 * r.rend_bruto - r.despesas;
    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\n", r.km_rodado);
    printf("Rendimento bruto: %.2lf\n", r.rend_bruto);
    printf("Despesas: %.2lf\n", r.despesas);
    printf("Rendimento liquido: %.2lf\n", r.rend_liq);
}

/***Inicia a próxima corrida**/
relatorio prox_corrida(p_fp espera, relatorio r){
    r.corrida_em_andamento = extrai_maximo(espera);
    if(r.corrida_em_andamento.cancelado == 1){
        while(r.corrida_em_andamento.cancelado == 1 ){ /*o cliente é descartado caso tenha cancelado a corrida*/
            if(espera->n > 0){
                r.corrida_em_andamento = extrai_maximo(espera);
            }
            else{       /*não tema mais cliente na espera*/
                r.tem_corrida_acontecendo = 0;
                return r;
            }
        }
    }
    return r;
}

/***Adiciona o cliente a espera ou inicia a corrida com ele
 * caso não tenha ninguém esperando**/
relatorio add_cliente(p_fp espera, relatorio r){
    cliente c;
    scanf("%s %lf %d %d %d %d", c.nome, &c.avaliacao, &c.inicio.x, &c.inicio.y, &c.destino.x, &c.destino.y);
    c.cancelado = 0;
    if(r.tem_corrida_acontecendo == 0){   /*se não estiver acontecendo nenhuma corrida*/
        r.corrida_em_andamento = c;
        r.tem_corrida_acontecendo = 1;
    }
    else{
        insere(espera, c);
    }
    printf("Cliente %s foi adicionado(a)\n", c.nome);
    return r;
}

/***Finaliza uma corrida e inicia a próxima, caso haja espera**/
relatorio finaliza_corrida(p_fp espera, relatorio r){
    cliente c = r.corrida_em_andamento;
    r.km_rodado = r.km_rodado + calcula_distancia(r.inicial, r.corrida_em_andamento.inicio);
    r.inicial = r.corrida_em_andamento.inicio;
    r.km_recebido = r.km_recebido + calcula_distancia(r.inicial, c.destino);
    r.inicial = c.destino;
    printf("A corrida de %s foi finalizada\n", c.nome);
    if(espera->n == 0){     /*se não tiver nenhum cliente na espera*/
        r.tem_corrida_acontecendo = 0;
    }
    else{
        r = prox_corrida(espera,r);        
    }
    return r;
}

/***Cancela uma corrida e inicia outra caso a cancelada já esteja em andamento**/
relatorio cancela_corrida(p_fp espera, relatorio r){
    cliente c;
    scanf(" %s", c.nome);
    r.rend_bruto = r.rend_bruto + 7;
    if(strcmp(r.corrida_em_andamento.nome,c.nome) == 0){ /*Se a corrida do cliente que cancelar ja tiver sido iniciada*/
        if(espera->n == 0){                                
            r.tem_corrida_acontecendo = 0;
        }
        else{
            r = prox_corrida(espera,r);
        } 
    }
    else{
        for(int i=0;i<espera->n;i++){     /*encontra o cliente na espera e cancela sua corrida*/
            if(strcmp(espera->c[i].nome, c.nome) == 0){
                espera->c[i].cancelado = 1;
                break;
            }
        }
    }
    printf("%s cancelou a corrida\n", c.nome);
    return r;
}

/***Encaminha para a função pedida**/
relatorio operacao(p_fp espera, char acao, relatorio r){
    if(acao == 'A'){
        r = add_cliente(espera, r);       
    }
    if(acao == 'F'){
        r = finaliza_corrida(espera,r);        
    }       
    if(acao == 'C'){
        r = cancela_corrida(espera,r);
    }
    if(acao == 'T'){
        calcula_relatorio(r);
    }
    return r;
}

relatorio inicializa_dia(){
    relatorio r;
    r.despesas = 57;
    r.km_recebido = 0;
    r.km_rodado = 0;
    r.rend_bruto = 0;
    r.rend_liq = 0;
    r.tem_corrida_acontecendo = 0;
    r.inicial.x = 0;
    r.inicial.y = 0;
    return r;
}

int main(){
    char acao;
    relatorio r = inicializa_dia();
    p_fp espera = criar_filaprio();
    do{
        scanf(" %c", &acao);
        r = operacao(espera, acao, r);
    }while(acao != 'T');
    free(espera->c);
    free(espera);
    return 0;
}