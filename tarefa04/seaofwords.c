#include <stdio.h>
#include <stdlib.h>
#define TAM_MAX 20
#define TEXTO_MAX 100

int conta_letras(char palavra[]){
    int tamanho_palavra = 0, i;
    for(i=0;i<=20;i++){
        if(palavra[i]!= '\0'){
            tamanho_palavra = tamanho_palavra + 1;
        } 
        else{
            break;
        }
    }
    return tamanho_palavra; 
}


void limpar_matriz(int matriz[][2], int n, int m){
    /** Deixa a matriz de forma que não hajam possíveis
     * posições válidas dentro dela*/
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            matriz[i][j] = -1;
        }
    }
}

int posicao_viavel(int posicoes[][2], int i, int j, int posicao){
    /** Identifica se a letra da posição já foi utilizada na palavra*/
    int c;
    for(c=0;c<=posicao;c++){
        if(posicoes[c][0] == i && posicoes[c][1]==j){
            return 0;
        }
    }
    return 1;
}

int acha_palavra(char palavra[], char texto[][TEXTO_MAX], int n, int m, int i, int j, int posicao, int posicoes_usadas[][2], int posicionamento){
    if(i<n && j<m && i>=0 && j>=0 && texto[i][j] == palavra[posicao]){
        posicoes_usadas[posicao][0] = i;
        posicoes_usadas[posicao][1] = j;
        if(posicao == conta_letras(palavra) - 1){
            return 1;
        }
        else{
            if(i<n-1 && texto[i+1][j] == palavra[posicao+1]){
                if(posicionamento == 0){
                    if(posicao_viavel(posicoes_usadas, i+1, j, posicao)==1){
                        if(acha_palavra(palavra, texto, n, m, i+1, j, posicao+1, posicoes_usadas, 0)==1 || acha_palavra(palavra, texto, n, m, i+1, j, posicao+1, posicoes_usadas, 1)==1 ||
    acha_palavra(palavra, texto, n, m, i+1, j, posicao+1, posicoes_usadas, 2)==1 || acha_palavra(palavra, texto, n, m, i+1, j, posicao+1, posicoes_usadas, 3)==1 ){
                            return 1;
                        }
                    }
                }
            }
            if(i>0 && texto[i-1][j] == palavra[posicao+1]){
                if(posicionamento == 1){
                    if(posicao_viavel(posicoes_usadas, i-1, j, posicao)==1){
                        if(acha_palavra(palavra, texto, n, m, i-1, j, posicao+1, posicoes_usadas, 0)==1 || acha_palavra(palavra, texto, n, m, i-1, j, posicao+1, posicoes_usadas, 1)==1 ||
    acha_palavra(palavra, texto, n, m, i-1, j, posicao+1, posicoes_usadas, 2)==1 || acha_palavra(palavra, texto, n, m, i-1, j, posicao+1, posicoes_usadas, 3)==1 )
                        return 1;
                    }
                }
            }
            if(j<m-1 && texto[i][j+1] == palavra[posicao+1]){
                if(posicionamento == 2){
                    if(posicao_viavel(posicoes_usadas, i, j+1, posicao)==1){
                        if(acha_palavra(palavra, texto, n, m, i, j+1, posicao+1, posicoes_usadas, 0)==1 || acha_palavra(palavra, texto, n, m, i, j+1, posicao+1, posicoes_usadas, 1)==1 ||
    acha_palavra(palavra, texto, n, m, i, j+1, posicao+1, posicoes_usadas, 2)==1 || acha_palavra(palavra, texto, n, m, i, j+1, posicao+1, posicoes_usadas, 3)==1 )
                        return 1;
                    }
                }
            }
            if(j>0 && texto[i][j-1] == palavra[posicao+1]){
                if(posicionamento == 3){
                    if(posicao_viavel(posicoes_usadas, i, j-1, posicao)==1){
                        if(acha_palavra(palavra, texto, n, m, i, j-1, posicao+1, posicoes_usadas, 0)==1 || acha_palavra(palavra, texto, n, m, i, j+1, posicao+1, posicoes_usadas, 1)==1 ||
    acha_palavra(palavra, texto, n, m, i, j-1, posicao+1, posicoes_usadas, 2)==1 || acha_palavra(palavra, texto, n, m, i, j-1, posicao+1, posicoes_usadas, 3)==1 )
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

           

int main(){
    int n, m, q, i, j, c;
    scanf("%d %d %d", &n, &m, &q);
    char texto[TEXTO_MAX][TEXTO_MAX]; 
    int posicoes_usadas[TAM_MAX][2];
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            scanf(" %c", &texto[i][j]);
        }
    } 
    for(c=0;c<q;c++){
        char palavra[TAM_MAX];
        int conta_chamadas = 0, conta_nao = 0;
        scanf("%s", palavra);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(texto[i][j]==palavra[0]){
                    limpar_matriz(posicoes_usadas, 20, 2);
                    conta_chamadas++;
                    if(acha_palavra(palavra, texto, n, m, i, j, 0, posicoes_usadas, 0)==1 || acha_palavra(palavra, texto, n, m, i, j, 0, posicoes_usadas, 1)==1 ||
    acha_palavra(palavra, texto, n, m, i, j, 0, posicoes_usadas, 2)==1 || acha_palavra(palavra, texto, n, m, i, j, 0, posicoes_usadas, 3)==1 ){
                        printf("sim\n");
                        break;
                    }
                    else{
                        conta_nao++;
                    }

                }
            }
        }
        if(conta_chamadas==conta_nao){
            printf("nao\n");
        }
        
    }    
    return 0;
}