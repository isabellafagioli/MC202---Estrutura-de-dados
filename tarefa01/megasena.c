#include <stdio.h>
#define MAX 1000

void le_matriz(int volante[6][10]){
    // A função lê a matriz binária que corresponde aos números marcados pelo apostador
    int i,j;
    for(i=0; i<6; i++){
        for(j=0; j<10; j++){
            scanf("%d", &volante[i][j]);
        }
    }
}

void encontra_marcados(int volante[6][10], int numeros_marcados[][15], int apostador){
    // Descobre a partir das matrizes binárias quais foram os números marcados
    int i,j,numeros = 0;
    for(i=0; i<6; i++){
        for(j=0; j<10; j++){
            if(volante[i][j] == 1){
                numeros_marcados[apostador][numeros] = (i*10) + j + 1;
                numeros+=1;
            }
        }    
    }    
}

void definir_premio(int resultados[MAX], double n, int m){
   // Divide o prêmio entre os ganhadores
   int sena, quina, quadra, i;
   double premio;
   for(i=0; i<m; i++){
       if(resultados[i] == 6){
           sena+=1;
       }
       else if(resultados[i] == 5){
           quina+=1;
       }
       else if(resultados[i] == 4){
           quadra+=1;      
       }
   } 
   for(i=0; i<m; i++){
       if(resultados[i] == 6){;
           premio = (62*n/100)/sena;
       }
       else if(resultados[i] == 5){
           premio = (19 *n/100)/(quina);
       }
       else if(resultados[i] == 4){
           premio = (19*n/100)/(quadra);
       }
       else{
           premio = 0;
       }
       printf("%.2lf\n", premio);
   }
}

void verificar_acertos(int sorteados[6], int numeros_marcados[][15], int m, int resultados[MAX], double n){
    // Compara os números marcados por cada apostador com os números sorteados
    int i, j, c;
    for(i=0; i<m; i++){
        int acertos = 0;
        for(j=0; j<15; j++){
            int marcado = numeros_marcados[i][j];
            for(c=0; c<6;c++){
                if(sorteados[c] == marcado){
                    acertos+=1;
                }    
            }
        }    
        resultados[i] = acertos;     
    }        
    definir_premio(resultados, n, m);
}

int main(){
    int m, i;
    double n;
    int numeros_marcados[MAX][15], volante[6][10];
    int sorteados[6], resultados[MAX];
    scanf("%d %lf", &m, &n);
    if(m >= 5 && m<=1000 && n >= 1000000.00 && n <= 3000000000.00){
        for(i=0; i<m; i++){
            le_matriz(volante);
            encontra_marcados(volante, numeros_marcados, i);
        }
        for(i=0;i<6;i++){
            scanf("%d", &sorteados[i]);
        }
        verificar_acertos(sorteados, numeros_marcados, m, resultados, n); 
        return 0;
    }
}