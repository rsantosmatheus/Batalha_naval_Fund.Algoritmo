#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*
*Acad�mico: Matheus Rosa dos Santos - RA 80409 - Fundamentos de algor�tmos.
*Para desenvolver o jogo utilizei a cria��o de dois grid 10x10. Um chamado FrontGrid, que ser� visto pelo usu�rio e ser� utilizado para
*salvar as jogadas realizadas, e o backgrid onde estar�o salvos as posi��es dos barcos, gerados aleatoriamente a cada jogo.
*
*Ao realizar a jogada, o programa analisa se foi um erro ou acerto baseado nas posi��es do backgrid e analisando o frontGrid que
*mostra e salva as jogadas j� feitas.
*Caso a jogada seja um erro o grid mostrar� um X na posi��o escolhida, seguido da mensagem informando o erro,
*caso um acerto, o grid mostrar� o numero do barco qual foi acertado seguido da mensagem de acerto.
*
*Escolhi ir um pouco al�m do pedido, primeiramente para ter uma sensa��o mais real do jogo de batalha naval,
*mas principalmente para aproveitar ao m�ximo da oportunidade de ter o c�digo, a l�gica e as boas pr�ticas avaliada pelo professor.
*Como tenho a inten��o de ser programador, o feedback avaliativo tem um grande valor para mim, n�o apenas academico mas tamb�m profissional.
//Muito obrigado pela oportunidade de fazer esse trabalho.
*/

//inicializar o backGrid com valor inteiro 0 em todas as casas
void GridInit(int grid[10][10]){
    for(int i =0; i<10;i++){
        for(int j=0; j<10;j++){
            grid[i][j]=0;
        }
    }
}

//inicializar frontGrid com valores char 0.
void GridFrontInit(char grid[10][10]){
    for(int i =0; i<10;i++){
        for(int j=0; j<10;j++){
            grid[i][j]='0';
        }
    }
}

//fun��o para imprimir o backGrid.
void PrintGrid(int grid[10][10]){
    printf("[0][1][2][3][4][5][6][7][8][9]\n");
    for(int i =0; i<10;i++){
        for(int j=0; j<10;j++){
            printf(" %i ",grid[i][j]);
        }
    printf("[%i]\n",i);
    }
}

//fun��o para imprimir o frontGrid
 void PrintFrontGrid(char grid[10][10]){
    printf("[0][1][2][3][4][5][6][7][8][9]\n");
    for(int i =0; i<10;i++){
        for(int j=0; j<10;j++){
            printf(" %c ",grid[i][j]);
        }
    printf("[%i]\n",i);
    }
}

//Criar barco com posicionamento rand�mico.
//A linha e coluna representam o local do grid onde o ponto central do barco se encontra
//A orienta��o do barco, 0 e 1 dizem se o barco estar� na horizontal ou vertical no grid. sendo 0 horizontal e 1 vertical
//A vida do barco, representa o quanto de dano ele pode tomar.
void BoatInit(int barco[], int i){
    int barcoOrient = (rand()%2);
    int barcoLinha = (rand()%10);
    int barcoColuna = (rand()%10);
    int vidaDoBarco = 3;
    //Resolvendo problema das quinas e bordas.
    //Caso uma parte do barco fique para fora do grid, ele ir� mover um espa�o para a esquerda, direita, cima ou baixo, dependendo
    //de sua posi��o e orienta��o.

    //Para os barco na horizontal
    if(barcoOrient == 0){
        if(barcoColuna ==0){
            barcoColuna +=1;
        }
        else if(barcoColuna ==9){
            barcoColuna -=1;
        }
    }
    //barco os barcos na vertical
    else if(barcoOrient == 1){
        if(barcoLinha==0){
            barcoLinha +=1;
        }
        if(barcoLinha==9){
            barcoLinha -=1;
        }
    }
    else{
        printf("Erro BoatInit Linha 68 na orienta��o do barco[%i]",i);
    }
    barco[0] = i;
    barco[1] = barcoLinha;
    barco[2] = barcoColuna;
    barco[3] = barcoOrient;
    barco[4] = vidaDoBarco;
}

//fun��o para criar e inserir barco no grid
void SetGridPosition(int grid[10][10], int barco[]){
    int idBarco = barco[0];
    int linhaBarco = barco[1];
    int colunaBarco = barco[2];
    int orientBarco = barco[3];
    //horizontal
    if(orientBarco == 0){
        grid[linhaBarco][(colunaBarco - 1)] = idBarco;
        grid[linhaBarco][colunaBarco] = idBarco;
        grid[linhaBarco][(colunaBarco + 1)] = idBarco;
    }
    //vertical
    else if(orientBarco == 1){
        grid[(linhaBarco - 1)][colunaBarco] = idBarco;
        grid[linhaBarco][colunaBarco] = idBarco;
        grid[(linhaBarco + 1)][colunaBarco] = idBarco;
    }
    else{
        printf("Erro setGridPosition Linha 106 barco[%i]",barco[0]);

    }
}

//Pegando os valores dos barcos, gerados aleat�riamente e colocando-os no backGrid.
void SetGame(int gridBack[10][10], int barco1[], int barco2[], int barco3[]){
    GridInit(gridBack);
    BoatInit(barco1,1);
    BoatInit(barco2,2);
    BoatInit(barco3,3);
    SetGridPosition(gridBack, barco1);
    SetGridPosition(gridBack, barco2);
    SetGridPosition(gridBack, barco3);
}

//Essa fun��o marca o ultimo ponto de verifica��o antes de come�ar o jogo
//Ela verifica se todos os barcos est�o colocados corretamente e n�o est�o se sobrepondo.
void GameInit(char gridFront[10][10], int gridBack[10][10], int barco1[], int barco2[], int barco3[]){
    GridFrontInit(gridFront);
    SetGame(gridBack, barco1,barco2,barco3);
    int count;
    //verifica��o para ver se os barcos n�o est�o se sobreponto
    count =0;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(gridBack[i][j] != 0){
                count +=1;
            }
        }
    }
    //caso esteja se sobrepondo, s�o geradas novas posi��es at� que n�o estejam se sobrepondo
    if(count != 9){
        while(count != 9){
            count = 0;
            SetGame(gridBack, barco1,barco2,barco3);
            for(int i=0; i<10; i++){
                for(int j=0; j<10; j++){
                    if(gridBack[i][j] != 0){
                        count +=1;
                    }
                }
            }
        }
    }
}

//A fun��o Ataque, marca uma jogada.
//Ela analisa a entrada do jogador, vendo se foi um erro,um acerto ou uma jogada repetida, salvando a jogada no frontGrid
void Atack (char gridFront[10][10], int gridBack[10][10],int barco1[], int barco2[], int barco3[], int *contErrosConsecutivos, int modoTeste){
    int palpite[2];
    printf("Entre com o palpite (linha e coluna): ");
    scanf("%i %i", &palpite[0],&palpite[1]);
    char mensagem[30] = {};
    //limpando a tela
    system("cls");
    //verificando acerto ou erro
    if(palpite[0]<10 && palpite[1]<10){
        if((gridBack[palpite[0]][palpite[1]] == 0) && (gridFront[palpite[0]][palpite[1]]=='0')){
            *contErrosConsecutivos += 1;
            strcpy(mensagem,"Palpite Errado!\n");
            gridFront[palpite[0]][palpite[1]] = 'x';
        }
        else if((gridBack[palpite[0]][palpite[1]] == 1) && (gridFront[palpite[0]][palpite[1]]=='0')){
            *contErrosConsecutivos = 0;
            gridFront[palpite[0]][palpite[1]] = '1';
            strcpy(mensagem,"Palpite certo!\n");
            barco1[4]-=1;
        }
        else if((gridBack[palpite[0]][palpite[1]] == 2)&& (gridFront[palpite[0]][palpite[1]]=='0')){
            *contErrosConsecutivos = 0;
            gridFront[palpite[0]][palpite[1]] = '2';
            strcpy(mensagem,"Palpite certo!\n");
            barco2[4]-=1;
        }
        else if((gridBack[palpite[0]][palpite[1]] == 3)&& (gridFront[palpite[0]][palpite[1]]=='0')){
            *contErrosConsecutivos = 0;
            gridFront[palpite[0]][palpite[1]] = '3';
            strcpy(mensagem,"Palpite certo!\n");
            barco3[4]-=1;
        }
        else{
            strcpy(mensagem,"Errou! Palpite repetido!\n");
            *contErrosConsecutivos += 1;
        }
    }
    else{
        strcpy(mensagem,"Errou! Palpite fora do grid\n");
        *contErrosConsecutivos += 1;
    }
    //Mostrando os resltados do ataque
    PrintFrontGrid(gridFront);
    //mostrar o grid com as respostas caso modo teste esteja ativado.
    if(modoTeste == 1){
        PrintGrid(gridBack);
        printf("vida do barco1 [%i]\n",barco1[4]);
        printf("vida do barco2 [%i]\n",barco2[4]);
        printf("vida do barco3 [%i]\n",barco3[4]);
    }
    printf("Erros consecutivos: [%i]\n", *contErrosConsecutivos);
    printf("%s",mensagem);
}

void checkBoatsHealth(int barco1[], int barco2[], int barco3[], int *barcosAfundados,int *gatilho1,int *gatilho2,int *gatilho3){
    int boatCheck = 3, afundouNesseround = 0;
    //os gatilhos s�o disparados ao afundar um barco

    if(barco1[4]==0 && *gatilho1 == 0){
        printf("Parab�ns! Voc� acabou de afundar um navio. ");
        *gatilho1 = 1;
        *barcosAfundados +=1;
        afundouNesseround = 1;
    }
    if(barco2[4]== 0 && *gatilho2 == 0){
        printf("Parab�ns! Voc� acabou de afundar um navio. ");
        *gatilho2 = 1;
       *barcosAfundados +=1;
        afundouNesseround = 1;
    }
    if(barco3[4]== 0 && *gatilho3 == 0){
        printf("Parab�ns! Voc� acabou de afundar um navio. ");
        *gatilho3 = 1;
        *barcosAfundados +=1;
        afundouNesseround = 1;
    }
    if(afundouNesseround == 1){
        if(barco1[4]==0){
            boatCheck -=1;
        }
        if(barco2[4]==0){
            boatCheck -=1;
        }
        if(barco3[4]==0){
            boatCheck -=1;
        }
        printf("Ainda resta(m) %i navio(s).\n",boatCheck);
    }
    afundouNesseround =  0;
}

void printImage(){
    printf("---------------BATALHA------------------\n");
    printf("--------------------NAVAL---------------\n");
    printf("              |    |    |     \n");
    printf("             )_)  )_)  )_)    \n");
    printf("            )___))___))___)\\    \n");
    printf("           )____)____)_____)\\\\  \n");
    printf("         _____|____|____|____\\\\__  \n");
    printf("---- ----\\                  /---------  \n");
    printf("  ~~~ ~~~~\\~~~~~~~~~~~~~~~~/~~~~~~~~~~  \n");
    printf("    ^^^^      ^^^^     ^^^    ^^    ^^  \n");
    printf("               ^^^^      ^^^  \n");
}

//Interface inicial do jogo, com op��s com o jogo ou o modo teste
void InterfaceInicial(int *modoTeste){
    int entrada;
    printImage();
    printf("Para iniciar jogo digite 0. \nPara iniciar o jogo no modo teste digite 1.\n");
    printf("O modo teste permite que voc� veja a posi��o dos barcos\n");
    printf("MODO DE JOGO -> ");
    scanf("%i", &entrada);
    *modoTeste = entrada;
    system("cls");

    if(entrada == 0 ){
        printf("selecionado op��o [%i]\n", *modoTeste);
        printf("Jogo inicializado com sucesso\n");
        printf("Aten��o Linhas e Colunas v�o de 0 a 9\n");
        printf("Separe a linha e a coluna com um espa�o\n");
    }
    else{
        printf("modo selecionado [%i]\n", *modoTeste);
        printf("Jogo inicializado com sucesso \n");
        printf("Aten��o Linhas e Colunas v�o de 0 a 9\n");
        printf("Separe a linha e a coluna com um espa�o\n");
        printf("INICIANDO MODO TESTE...");
    }
    printf("\n");
    system("pause");
    system("cls");
}
//Checa se todos os par�metros para terminar o jogo foram atendidos e entrega se o jogador ganhou ou perdeu.
void EndGame(int gatilho1, int gatilho2, int gatilho3, int contErrosConsecutivos, int gridBack[10][10]){
    if(gatilho1==1 && gatilho2==1 && gatilho3==1){
        system("cls");
        PrintGrid(gridBack);
        printf("               PARAB�NS!! \n               TODOS OS NAVIOS FORAM AFUNDADOS");
    }
    else if(contErrosConsecutivos>=3){
        system("cls");
        PrintGrid(gridBack);
        printf("               FIM DE JOGO!!!\n               VOC� PERDEU!");
    }
    else{
        printf("Erro!");
    }
    printf("\n");
    system("pause");
}


int main() {
    setlocale (LC_ALL, "Portuguese");
    srand(time(NULL));
    char gridFront[10][10];
    int gridBack[10][10];
    int barco1[5], barco2[5],barco3[5];
    int contErrosConsecutivos = 0, barcosAfundados = 0;
    int gatilho1=0, gatilho2=0,gatilho3=0, modoTeste = 0;

    InterfaceInicial(&modoTeste);
    GameInit(gridFront, gridBack, barco1,barco2,barco3);
    PrintFrontGrid(gridFront);
    if(modoTeste==1){
        PrintGrid(gridBack);
    }
    while(((gatilho1==0 || gatilho2==0 || gatilho3==0)&&(contErrosConsecutivos<3))){
        Atack(gridFront,gridBack,barco1,barco2,barco3,&contErrosConsecutivos, modoTeste);
        checkBoatsHealth(barco1,barco2,barco3, &barcosAfundados, &gatilho1, &gatilho2,&gatilho3);
    }

    EndGame(gatilho1, gatilho2, gatilho3, contErrosConsecutivos, gridBack);
    return 0;
}
