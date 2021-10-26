#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***Para lista ligada de int**/
typedef struct No_int{
    int dado;
    struct No_int *proximo;    
} No_int;
typedef struct No_int *p_no_int;

p_no_int cria_lista(){
    return NULL;
}
p_no_int adiciona_elemento(p_no_int lista, int elemento){
   p_no_int novo_elemento;
    novo_elemento = malloc(sizeof(No_int));
    if (novo_elemento == NULL) {
           printf("Memoria insuficiente.\n");
           exit(1);  
        }
    novo_elemento->dado = elemento;
    novo_elemento->proximo = lista;
    return novo_elemento;
}
void destruir_lista_int(p_no_int lista){
    if(lista!=NULL){
        destruir_lista_int(lista->proximo);
        free(lista);
    }
}
p_no_int inverte_lista(p_no_int lista){
    p_no_int nova_lista = cria_lista();
    p_no_int p_aux = lista;
    while(lista != NULL){
        nova_lista = adiciona_elemento(nova_lista, lista->dado);
        lista = lista->proximo;
    }
    if(p_aux != NULL){
        destruir_lista_int(p_aux);
    }
    return nova_lista;
}

/***Informações necessárias do paciente**/
typedef struct Paciente{
    char nome[51];
    char prioridade[13];
    int tempo;
    int ordem;
    p_no_int atendimentos;
} Paciente;

/***Implementação da lista ligada**/
typedef struct No{
    Paciente dado;
    struct No *proximo;  
} No;
typedef struct No * ponteiro_no;

/***Implementação da fila com possibilidade de inserção no fim e no início e remoção no início (vistos em aula)**/
typedef struct{
    ponteiro_no ini, fim;
} Fila;

typedef Fila * ponteiro_fila;

ponteiro_fila cria_fila(){
    ponteiro_fila f;
    f = malloc(sizeof(Fila));
    if (f == NULL) {
           printf("Memoria insuficiente.\n");
           exit(1);  
    }
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void insere_inicio(ponteiro_fila f, Paciente p){
    ponteiro_no novo = malloc(sizeof(No));
    if (novo == NULL) {
           printf("Memoria insuficiente.\n");
           exit(1);  
    }
    novo->dado = p;
    novo->proximo = f->ini;
    f->ini = novo;
    if(f->fim == NULL){
        f->fim = f->ini;
    }
}

void insere_fim(ponteiro_fila f, Paciente p){
    ponteiro_no novo;
    novo = malloc(sizeof(No));
    if (novo == NULL) {
           printf("Memoria insuficiente.\n");
           exit(1);  
    }
    novo->dado = p;
    novo->proximo = NULL;
    if(f->ini == NULL){
        f->ini = novo;
    }
    else{
        f->fim->proximo = novo;
    }
    f->fim = novo;    
}

Paciente remove_inicio(ponteiro_fila f){
    ponteiro_no primeiro = f->ini;
    Paciente x = primeiro->dado;
    f->ini = f->ini->proximo;
    if (f->ini == NULL){
        f->fim = NULL;
    }
    free(primeiro);
    return x;  
}

typedef struct Especialidade{
    ponteiro_fila f;
    int qtd_profissionais;
    int qtd_pacientes;
} Especialidade;

typedef struct pacientes_esperando{
    ponteiro_fila f;
    int qtd;
} pacientes_esperando;

void insere_fila(ponteiro_fila f, Paciente p){
    if(p.prioridade[0] == 'p'){
        insere_inicio(f,p);
    } else{
        insere_fim(f,p);
    }
}
int define_qtd_prof(int i){
    int qtd;
    if(i==0){
        qtd = 10;
    }
    if(i==1){
        qtd = 2;
    }
    if(i==2){
        qtd = 5;
    }
    if(i==3){
        qtd = 3;
    }
    if(i==4){
        qtd = 4;
    }
    if(i==5){
        qtd = 7;
    }
    if(i==6){
        qtd = 2;
    }
    if(i==7){
        qtd = 1;
    }
    if(i==8){
        qtd = 4;
    }
    return qtd;
}
/***Encontra o horário de saída e imprime seguido do nome**/
void sair(Paciente p){
    int hora = 0, minuto = 0;
    hora = 8 + p.tempo/60;
    minuto = p.tempo%60;
    if(hora>=10 && minuto>0){
        printf("%d:%d %s\n", hora, minuto, p.nome); 
    }
    else if(minuto == 0 && hora<=9){
        printf("0%d:%d0 %s\n", hora, minuto, p.nome); 
        
    }
     else if(hora<=9){
        printf("0%d:%d %s\n", hora, minuto, p.nome);
    }
    else if(minuto == 0){
        printf("%d:%d0 %s\n", hora, minuto, p.nome);       
    }  
}
/***Coloca o paciente na fila da especialidade desejada**/
void encaminha(Especialidade especialidades[], Paciente p){
    if(p.atendimentos == NULL){
        free(p.atendimentos);
        sair(p);
    }
    else{
        p_no_int atendimento = p.atendimentos;
        int indice = atendimento->dado - 1;
        p.atendimentos = p.atendimentos->proximo;
        free(atendimento);
        insere_fila(especialidades[indice].f,p);
        especialidades[indice].qtd_pacientes++;
    }
}

void incrementa_tempo(ponteiro_no especialidade){
    if(especialidade!= NULL){
        incrementa_tempo(especialidade->proximo);
        especialidade->dado.tempo = especialidade->dado.tempo + 10;
    }
}
/***Aumenta o tempo de espera e retira os pacientes das filas de atendimentos**/
pacientes_esperando atender(Especialidade especialidades[]){
    int i,j;
    Paciente p;
    pacientes_esperando f;
    f.f = cria_fila();
    f.qtd = 0;
    for(i=0;i<9;i++){
        int n;
        incrementa_tempo(especialidades[i].f->ini);
        if(especialidades[i].qtd_pacientes>0){
            if(especialidades[i].qtd_pacientes<especialidades[i].qtd_profissionais){
                n = especialidades[i].qtd_pacientes;
            }
            else{
                n = especialidades[i].qtd_profissionais;
            }
            for(j=0;j<n;j++){
                p = remove_inicio(especialidades[i].f);
                especialidades[i].qtd_pacientes--;
                insere_fila(f.f, p);
                f.qtd++; 
            }
        }       
    }
    return f;
}

int fila_vazia(Especialidade especialidades[]){
    int i;
    for(i=0;i<9;i++){
        if(especialidades[i].qtd_pacientes != 0){
            return 0;
        }
    }
    return 1;
}

int comparador(const void *a, const void *b) {
    int x = ((Paciente *)a)->ordem;
    int y = ((Paciente *)b)->ordem;
    return (x - y);
}

int organizar_espera(pacientes_esperando fila, Especialidade especialidades[]){
    if(fila.qtd == 0){
        if(!fila_vazia(especialidades)){
            atender(especialidades);
            return organizar_espera(fila,especialidades);
        }
        else{
            free(fila.f);
            return 0;
        }
    }
    else{
        while(fila.f->fim != NULL){
            Paciente p = remove_inicio(fila.f);
            encaminha(especialidades,p);
            fila.qtd--;
        }
        free(fila.f);
        fila = atender(especialidades);
        Paciente *v_pacientes = malloc(fila.qtd * sizeof(Paciente));
        int i = 0;
        while (fila.f->ini != NULL){
            v_pacientes[i] = remove_inicio(fila.f);
            i++;                  
        }
        qsort(v_pacientes, fila.qtd, sizeof(Paciente), comparador);
        for(i=0;i<fila.qtd;i++){
            insere_fila(fila.f,v_pacientes[i]);
        }
        free(v_pacientes);
        return organizar_espera(fila,especialidades);
    }
}

Paciente inicializa_paciente(){
    Paciente p;
    strcpy(p.nome, "\0");
    strcpy(p.prioridade, "\0");
    p.ordem = 0;
    p.tempo = 0;
    return p;
}

int main(){
    Paciente p = inicializa_paciente();
    pacientes_esperando fila; 
    fila.f = cria_fila();  
    int at;
    char inicio_linha;
    int i=0;
    while(scanf(" %c", &inicio_linha) != EOF){ 
        p.atendimentos = cria_lista(); 
        scanf("%[^\"]%*c", p.nome);   
        scanf(" %s", p.prioridade);
        while(scanf(" %d", &at) == 1){
            if(at>0){
                p.atendimentos = adiciona_elemento(p.atendimentos, at);         
            }
        }
        /*Como os números recebidos são colocados do último para o primeiro, é necessário inverter para ficar na ordem certa*/
        p.atendimentos = inverte_lista(p.atendimentos);
        p.ordem = i;
        i++;
        insere_fim(fila.f,p);
    }
    fila.qtd = i;
    Especialidade especialidades[9];
    for(i=0;i<9;i++){
       especialidades[i].f = cria_fila();
       especialidades[i].qtd_profissionais = define_qtd_prof(i);
       especialidades[i].qtd_pacientes = 0;
    }
    organizar_espera(fila,especialidades);
    for(i=0;i<9;i++){
        free(especialidades[i].f);
    }
    return 0;
}