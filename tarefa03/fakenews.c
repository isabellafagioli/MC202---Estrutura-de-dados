#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 

double encontra_maximo(int i, int m, double **historico){
    int j;
    double maximo = historico[i][0];
    for(j=0;j<m;j++){
        if(historico[i][j]>maximo){
            maximo = historico[i][j];
        }
    }
    printf(" %.2lf", maximo);  
    return maximo;
}

double encontra_minimo(int i, int m, double **historico){
    int j;
    double minimo = historico[i][0];
    for(j=0;j<m;j++){
        if(historico[i][j]<minimo){
            minimo = historico[i][j];
        }
    }
    printf(" %.2lf", minimo);  
    return minimo;
}

double calcula_media(int i, int m, double **historico){
    double media = 0;
    int j;
    for(j=0;j<m;j++){
        media = media + historico[i][j];
    }
    media = media/m;
    printf(" %.2lf", media);
    return media;
}

double calcula_desvio(int i, int m, double media, double **historico){
    double desvio = 0;
    int j;
    for(j=0;j<m;j++){
        desvio = desvio + pow(historico[i][j] - media, 2);
    }
    desvio = sqrt(desvio/m);
    printf(" %.2lf\n", desvio);
    return desvio;
}
char **inicializa_vetor_string(int n){
    int i;
    char ** v = (char **)malloc(n * sizeof(char *));
    for(i=0;i<n;i++){
        v[i] = (char *)malloc(25 * sizeof(char)); 
        if (v[i] == NULL) {
           printf("Memoria insuficiente.\n");
           exit(1);  
        }
    }
    return v;
}

double **inicializa_matriz(int n, int m){
    double ** v = (double **)malloc(n * sizeof(double *));
    for(int i=0;i<n;i++){
        v[i] = (double *)malloc(m * sizeof(double)); 
        if (v[i] == NULL) {
            printf("Memoria insuficiente.\n");
            exit(1);  
        }
    }
    return v;
}


void define_catergorias(double **resultados, int n, char **termos){
    int bot =0, surpreendente = 0, normal = 0, local = 0, irrelevante = 0, i;
    char **termos_bot = malloc(n * sizeof(char *));
    char **termos_surpreendente = malloc(n * sizeof(char *));
    char **termos_normal = malloc(n * sizeof(char *));
    char **termos_local = malloc(n * sizeof(char *));
    char **termos_irrelevante = malloc(n * sizeof(char *));
    for(i=0;i<n;i++){
        double maximo = resultados[i][0], minimo = resultados[i][1], media = resultados[i][2], desvio = resultados[i][3];
        if(media>=60 && desvio>15){
            termos_bot[bot] = termos[i];
            bot++; 
        }
        if(media>=60 && desvio<=15){
            termos_surpreendente[surpreendente] = termos[i];
            surpreendente++; 
        }
        if(media<60 && maximo>=80 && minimo > 20){
            termos_normal[normal] = termos[i];
            normal++; 
        }
        if(media<60 && maximo>=80 && minimo <= 20){
            termos_local[local] = termos[i];
            local++; 
        }
        if(media<60 && maximo<80){
            termos_irrelevante[irrelevante] = termos[i];
            irrelevante++; 
        }
    }
    printf("\nRESULTADO:");
    printf("\nBot (%d): ", bot);
    for(i=0;i<bot;i++){
        printf("%s ", termos_bot[i]);
    }
    printf("\nSurpreendente (%d): ", surpreendente);
    for(i=0;i<surpreendente;i++){
        printf("%s ", termos_surpreendente[i]);
    }
    printf("\nNormal (%d): ", normal);
    for(i=0;i<normal;i++){
        printf("%s ", termos_normal[i]);
    }
    printf("\nLocal (%d): ", local);
    for(i=0;i<local;i++){
        printf("%s ", termos_local[i]);
    }
    printf("\nIrrelevante (%d): ", irrelevante);
    for(i=0;i<irrelevante;i++){
        printf("%s ", termos_irrelevante[i]);
    }
    for(i=0;i<n;i++){
        free(termos[i]);
        free(resultados[i]);
    }
    free(termos_irrelevante); 
    free(termos_local);
    free(termos_normal);
    free(termos_surpreendente);
    free(termos_bot); 
    free(termos);
    free(resultados);
}

int main(){
    int n, m, i, j;
    scanf("%d %d", &n, &m);
    char **termos = inicializa_vetor_string(n);
    double **historico = inicializa_matriz(n,m);
    double **resultados = inicializa_matriz(n,4);
    for(i=0;i<n;i++){
        scanf("%s", termos[i]);
        for(j=0;j<m;j++){
            scanf("%lf", &historico[i][j]);
        }         
    }
    for(i=0;i<n;i++){  
        printf("%s", termos[i]);
        resultados[i][0] = encontra_maximo(i,m,historico);
        resultados[i][1] = encontra_minimo(i,m,historico);
        resultados[i][2] = calcula_media(i,m,historico);
        resultados[i][3] = calcula_desvio(i,m,resultados[i][2],historico);
    }
    define_catergorias(resultados, n, termos);
    for(i=0;i<n;i++){
        free(historico[i]);
    }
    free(historico);
    return 0;
}