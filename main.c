#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct linhaMemPrincipal{
    int chave;
    }linhaMemPrincipal;

typedef struct linhaMemCache{
    int chave[2];
    int mod;
    int indice;
}linhaMemCache;



void preencheMemPrincipal(linhaMemPrincipal vetor[], int tamanhoMemPrincipal, FILE *fileMemPrincipal){

    int i;
    for(i=0; i<tamanhoMemPrincipal; i++){
        fscanf(fileMemPrincipal, "%d\n", &vetor[i].chave);
    }


    /*
    int i;
    srand((unsigned) time(NULL));
    for(i=0; i<tamanhoMemPrincipal; i++){
        vetor[i].chave = rand() % 100;
    }*/
}

void printaMemPrincipal(linhaMemPrincipal vetor[], int tamanhoMemPrincipal){

    int i;
    printf("\n#MAPA DA MEMORIA PRINCIPAL:\n");
    for(i=0; i<tamanhoMemPrincipal; i++){
        printf("[%d]=> %d || ", i, vetor[i].chave);
        if((i%5==0 && i > 4))
            printf("\n");
    }
    printf("\n\n");
}

void preencheMemCache(linhaMemCache memCache[], int tamanhoMemCache){

    int i;
    for(i=0; i<tamanhoMemCache; i++){
        memCache[i].chave[0] = -1;
        memCache[i].chave[1] = -1;
        memCache[i].mod = 0;
    }
}

void printaMemCache(linhaMemCache memCache[], int tamanhoMemCache){

    int i;
    printf("\n#MAPA DA MEMORIA CACHE:\n");
    for(i=0; i<tamanhoMemCache; i++){
        printf("L%d: chave[0] => %d   chave[1] => %d\n", i, memCache[i].chave[0], memCache[i].chave[1]);
    }
    printf("\n\n");
}





void leitura(linhaMemCache memCache[], int tamanhoMemCache, linhaMemPrincipal memPrincipal[], int tamanhoMemPrincipal, int* cont){


    int x = rand() % 100;
    int i, j, h, aux;
    printf("\n============================================\n");
    printf("\n##NUMERO PROCURADO NA MEMORIA PRINCIPAL: %d\n", x);

    for(i=0; i<tamanhoMemCache; i++){
        if(memCache[i].chave[1] == x){
             printf("\n\nNUMERO JA ESTA NA CACHE  LINHA: %d COLUNA: 2\n\n", i);
             printaMemCache(memCache, tamanhoMemCache);
             break;
        }
        if(memCache[i].chave[0] == x ){
             printf("\n\nNUMERO JA ESTA NA CACHE  LINHA: %d COLUNA: 1\n\n", i);
             printaMemCache(memCache, tamanhoMemCache);
             break;
        }
        else if(i == tamanhoMemCache -1 ){ // chegou na ultima iteração e não entrou no if acima => verificou toda a cache
            for(j=0; j<tamanhoMemPrincipal; j++){
                if(memPrincipal[j].chave == x){
                    printf("\n\n=>ACHOU A CHAVE NA MEMORIA PRINCIPAL\n");
                    memCache[i].indice = j;
                    for(h=0; h<tamanhoMemCache; h++){
                        if(memCache[h].chave[0] == -1){
                            memCache[h].chave[0] = x; //fazer a condiçao caso ja esteja preenchida.
                            if(j != tamanhoMemPrincipal-1)
                                memCache[h].chave[1] = memPrincipal[j+1].chave;
                            printf("\n##INSERSAO EM LINHA DE CACHE VAZIA##\n");
                            printaMemCache(memCache, tamanhoMemCache);
                            break;
                        }
                        else if(h == tamanhoMemCache -1){

                            //metodo random
                            /*
                            aux = (rand()%tamanhoMemCache);
                            printf("\n\nentrou no aleatorio\n\n");
                            printf("indice escolhido da cache pra ser sobreposto:%d\n\n", aux);
                            memCache[aux].chave[0] = x;
                            printaMemCache(memCache, tamanhoMemCache);
                            */

                            //metodo FIFO

                            memCache[*cont].chave[0] = x;
                            printf("\n\n#ALGORITIMO DE SUBISTITUICAO TEVE QUE SER UTILIZADO: FIFO\n\n=>INDICE A SER SUBSTITUIDO : %d\n\n", *cont);
                            *cont = *cont + 1;
                            if(*cont >= tamanhoMemCache){
                                *cont = 0;
                            }
                            printaMemCache(memCache, tamanhoMemCache);
                        }
                    }
                    break;
                }
            }
        }
    }

}

int verificaMemCache(linhaMemCache memCache[], int tamanhoMemCache, int x){

    int i;
    for(i=0; i<tamanhoMemCache; i++){
        if(memCache[i].chave[1] == x || memCache[i].chave[0] == x){
             printf("\n\n#NUMERO JA ESTA NA CACHE  LINHA: %d\n\n", i);
             printaMemCache(memCache, tamanhoMemCache);
             return 1;
        }
        if(i == tamanhoMemCache -1 && memCache[i].chave[1] != x && memCache[i].chave[0] != x)
            return 0;
    }
}

int verificaMemPrincipal(linhaMemPrincipal memPrincipal[], int tamanhoMemPrincipal, linhaMemCache memCache[], int x){

    int i;
    for(i=0; i<tamanhoMemPrincipal; i++){
        if(memPrincipal[i].chave == x){
            printf("\n#ACHOU A CHAVE NA MEMORIA PRINCIPAL\n\n");
            return i;
        }if(i == tamanhoMemPrincipal -1 && memPrincipal[i].chave != x)
            return -1;

    }

}

void subsRandom(linhaMemCache memCache[], int tamanhoMemCache, linhaMemPrincipal memPrincipal[], int aux2){

    int aux = (rand()%tamanhoMemCache);
    printf("\n\n#ALGORITIMO DE SUBISTITUICAO TEVE QUE SER UTILIZADO: RANDOM\n\n");
    printf("#INDICE ESCOLHIDO PARA SER SOBREPOSTO:%d\n\n", aux);
    memCache[aux].chave[0] = memPrincipal[aux2].chave;
    memCache[aux].chave[1] = memPrincipal[aux2+1].chave;
    printaMemCache(memCache, tamanhoMemCache);

}


int subsFifo(linhaMemCache memCache[], int tamanhoMemCache, linhaMemPrincipal memPrincipal[], int aux, int *cont){

    if(*cont == tamanhoMemCache){
        *cont = 0;
        return *cont;
    }

    printf("\n\n#ALGORITIMO DE SUBISTITUICAO TEVE QUE SER UTILIZADO: FIFO\n\n=>INDICE A SER SUBSTITUIDO : %d\n\n", *cont);
    if(memCache[*cont].mod == 1){
        memPrincipal[memCache[*cont].indice].chave = memCache[*cont].chave[0];
    }
    memCache[*cont].chave[0] = memPrincipal[aux].chave;
    memCache[*cont].chave[1] = memPrincipal[aux+1].chave;


    printaMemCache(memCache, tamanhoMemCache);
    return *cont;

}

void modMemCache(linhaMemCache memCache[], int z){

    int resp;

    printf("\n\nVALOR DE Z: %d\n\n", z);
    printf("#DESEJA MODIFICAR A CHAVE: %d?   1=>SIM | 2=>NAO\n\n", memCache[z].chave[0]);
    scanf("%d", &resp);
    if(resp == 1){
        printf("#INSIRA A CHAVE A SER MODIFICADA:\n\n");
        scanf("%d", &memCache[z].chave[0]);
        memCache[z].mod = 1;
    }


}

void leitura2(linhaMemCache memCache[], int tamanhoMemCache, linhaMemPrincipal memPrincipal[], int tamanhoMemPrincipal, int *cont, int *teste){

    int x = memPrincipal[(rand() % 100)].chave;
    int i, aux, verif, resp;

    printf("\n============================================\n");

    printf("\n#NUMERO A SER PROCURADO : %d\n", x);
    verif = verificaMemCache(memCache, tamanhoMemCache, x); // 1 = CACHE HIT  ||  2 = CACHE MISS

    if(!verif){ // SE FOR CACHE MISS...
        aux = verificaMemPrincipal(memPrincipal, tamanhoMemPrincipal, memCache, x); // RETORNA INDICE DO VETOR MEMORIA PRINCIPAL OU -1 SE NÃO ACHAR.
        if(aux != -1){ // SE ACHAR NA MEMORIA PRINCIPAL...
            for(i=0; i<tamanhoMemCache; i++){ // PROCURA POR LUGAR VAZIO NA CACHE.
                if(memCache[i].chave[0] == -1){ // SE ACHAR LUGAR VAZIO NA CACHE
                    memCache[i].chave[0] = memPrincipal[aux].chave; // PUXA DA PRINCIPAL PRA CACHE
                    if(aux != tamanhoMemPrincipal -1 ) // PUXA TAMBEM O N+1 CASO NAO ESTEJA NA ULTIMA POSIÇAO
                        memCache[i].chave[1] = memPrincipal[aux+1].chave;
                    else // SE ESTIVER NA ULTIMA POSICAO
                        memCache[i].chave[1] = memPrincipal[0].chave; // COLOCA O PRIMEIRO DO VETOR
                    memCache[i].indice = aux; // COLOCA NO CAMPO INDICE O AUX
                    printf("\n\n#INDICE NA MEMORIA PRINCIPAL: %d\n\n", memCache[i].indice);
                    printaMemCache(memCache, tamanhoMemCache);
                    modMemCache(memCache, teste);
                    break;
                }

                if(memCache[i].chave[0] != -1){
                    if(i == tamanhoMemCache-1){
                        modMemCache(memCache, teste);
                        //subsRandom(memCache, tamanhoMemCache, memPrincipal, aux);
                        subsFifo(memCache, tamanhoMemCache, memPrincipal, aux, cont);
                        printf("\n\n========================================\n\n");
                        printaMemPrincipal(memPrincipal, tamanhoMemPrincipal);
                        printf("\n");
                    }
                }
            }
        }
    }
}

void leitura3(linhaMemCache memCache[], int tamanhoMemCache, linhaMemPrincipal memPrincipal[], int tamanhoMemPrincipal, int *cont){

    int x = memPrincipal[(rand() % 100)].chave;
    int i, aux, verif, resp, z;
    int w;

    printf("\n============================================\n");

    printf("\n#NUMERO A SER PROCURADO : %d\n", x);
    verif = verificaMemCache(memCache, tamanhoMemCache, x); // 1 = CACHE HIT  ||  2 = CACHE MISS

    if(!verif){ // SE FOR CACHE MISS...
        aux = verificaMemPrincipal(memPrincipal, tamanhoMemPrincipal, memCache, x); // RETORNA INDICE DO VETOR MEMORIA PRINCIPAL OU -1 SE NÃO ACHAR.
        if(aux != -1){ // SE ACHAR NA MEMORIA PRINCIPAL...
            w = insereNaCache(memCache, tamanhoMemCache, memPrincipal, tamanhoMemPrincipal, aux);
            printaMemCache(memCache, tamanhoMemCache);
            if(!w){// ENTRA SE NÃO CONSEGUIR COLOCAR NA CACHE
                z = subsFifo(memCache, tamanhoMemCache, memPrincipal, aux, cont);
                *cont = *cont + 1;
                modMemCache(memCache, z);
            }
        }
    }
}

int insereNaCache(linhaMemCache memCache[], int tamanhoMemCache, linhaMemPrincipal memPrincipal[], int tamanhoMemPrincipal, int aux){
    int i;

    for(i = 0; i < tamanhoMemCache; i++){
        if(memCache[i].chave[0] == -1){
            memCache[i].indice = aux;
            memCache[i].chave[0] = memPrincipal[aux].chave;
            if(aux == tamanhoMemPrincipal - 1){
                memCache[i].chave[1] = memPrincipal[0].chave;
            }else
                memCache[i].chave[1] = memPrincipal[aux + 1].chave;

            printaMemCache(memCache, tamanhoMemCache);
            modMemCache(memCache, i);
            return 1;
        }
    }
    return 0;
}





int printaHeader(){
        int resp;
        printf("##################################################\n");
        printf("#             SIMULACAO MEMORIA CACHE            #\n");
        printf("#   1 -> PRINTAR MEMORIA PRINCIPAL               #\n");
        printf("#   2 -> PRINTAR MEMORIA CACHE                   #\n");
        printf("#   3 -> GERAR UM ACESSO ALEATORIO               #\n");
        printf("#   4 -> SYSTEM CLS                              #\n");
        printf("##################################################\n\n\n");
        scanf("%d", &resp);
        return resp;
        }


void main (void){



    FILE* fileMemPrincipal;
    fileMemPrincipal = fopen("arqMemPrincipal.txt", "r");

    int tamanhoMemPrincipal = 100;
    int tamanhoMemCache = 5;
    int resp;
    int cont = 0;
    int teste = 0;
    linhaMemPrincipal memPrincipal[tamanhoMemPrincipal];
    linhaMemCache memCache[tamanhoMemCache];

    preencheMemPrincipal(memPrincipal, tamanhoMemPrincipal, fileMemPrincipal);
    preencheMemCache(memCache, tamanhoMemCache);
    while(1){

        resp = printaHeader();

        switch(resp){
            case 1:

                printaMemPrincipal(memPrincipal, tamanhoMemPrincipal);
            break;
            case 2:
                printaMemCache(memCache, tamanhoMemCache);
                printf("\n\n\n");
            break;
            case 3:
                leitura3(memCache, tamanhoMemCache, memPrincipal, tamanhoMemPrincipal, &cont);

            break;
            case 4:
                system("cls");
            break;
            default:
            break;
        }
    }

    fclose(fileMemPrincipal);

}
