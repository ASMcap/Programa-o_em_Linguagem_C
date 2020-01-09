#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#define X(a,b) (((a) == 'X' && (b) == 'X' || (a) == 1 ) ? 1 : (((a) == 'X') ? (a) : (b)))
#define CompCaractX(a,b,c) (X(X(a,b),c))
#define ProcuraVasio(a,b,c) (((a) == ' ') ? 1 : (((b) == ' ') ? 2 : (((c) == ' ') ? 3 : 0)))
#define O(a,b) (((a) == 'O' && (b) == 'O' || (a) == 1 ) ? 1 : (((a) == 'O') ? (a) : (b)))
#define CompCaractO(a,b,c) (O(O(a,b),c))
#define CompCaractVerificaGalo(a,b) (((a) == 'X' && (b) == 'O' || (a) == 'O' && (b) == 'X') ? 1 : (((a) != ' ') ? (a) : (b)))
#define VerificaGalo(a,b,c) ((CompCaractVerificaGalo(CompCaractVerificaGalo(a,b),c) == 1) ? 1 : 0)

enum tipoJogo{doisJogadores =1, contraMaquina=2}tipo;
static struct Jogador {int vitorias; char nome[60];};
static struct Jogador jogador_1, jogador_2;
//static struct Jogador ;
int fimJogo = 0, jogada =0, jogo =0;
char tabuleiro[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, exemplo[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Cria ficheiro de dados se não existir
void CriaFicheiro(){
    FILE *fp;
    fp = fopen ("Dados.txt", "w");
    if (fp == NULL) {
       printf ("Houve um erro ao criar o ficheiro.\n");
       exit(0);
    }
    printf ("Ficheiro criado com sucesso.\n");
    fclose (fp);
    AtualizaFicheiro();
}

// Atualiza ficheiros de nome dos jogadores e pontuação
void AtualizaFicheiro(){
    FILE *f;
    char c;
        f = fopen("Dados.txt", "a");
        if(f == NULL){
            CriaFicheiro();
        }
        switch(tipo){
            case doisJogadores:
                fprintf(f, " Jogador: %s - Vitórias: %d \n", jogador_1.nome, jogador_1.vitorias);
                fprintf(f, " Jogador: %s - Vitórias: %d \n", jogador_2.nome, jogador_2.vitorias);
                break;
            case contraMaquina:
                fprintf(f, " Jogador: %s - Vitórias: %d \n", jogador_1.nome, jogador_1.vitorias);
                break;
            default: printf("Ocorreu um erro inesperado\n"); exit(0); break;
        }
    printf ("Nome gravado com sucesso.\n");
    fclose(f);
}

// Imprime menu principal do jogo
int MenuTipoJogo(){
    int result=0;
    switch(fimJogo){
        case 0:
            printf("\n\n===============================================================================\n\n                                   Jogo do Gálo\n\n===============================================================================\n\n");
            printf("Escolha uma opção\n1 - Jogo com dois jogadores\n2 - Jogar contra o computador\n3 - Ver histórico de vitórias\n4 - Sair\n5 - Apagar\n");
            scanf("%d", &result);
            if(result == 5){
               remove("Dados.txt");
            }
            tipo = result;
            break;
        case 1:
            printf("\n\n===============================================================================\n\n                                   Jogo do Gálo\n\n===============================================================================\n\n");
            printf("Escolha uma opção\n1 - Continuar jogo\n2 - Voltar ao menu principal\n3 - Sair\n\n");
            scanf("%d", &result);
            if(result == 1){
                system("cls");
                fimJogo = 0;
                jogada=0;
                result = 6;
            }else if(result == 2){
                AtualizaFicheiro();
                jogador_1.vitorias = 0;
                jogador_2.vitorias = 0;
                system("cls");
                fimJogo = 0;
                jogada=0;
                result = 5;
            }else{
                AtualizaFicheiro();
                result = 4;
            }
            break;
    }
    return result;
}

// Regista jogador
void RegistaJogador(){
    //tipo = MenuTipoJogo();
    switch(MenuTipoJogo()){
        case doisJogadores:
            printf("Insira o nome do jogador 1\n");
            scanf("%s", jogador_1.nome);
            printf("Insira o nome do jogador 2\n");
            scanf("%s", jogador_2.nome);
            break; // Dois jogadores
        case contraMaquina:
            printf("Insira o nome do jogador\n");
            scanf("%s", jogador_1.nome);
            char str[8] = "Máquina";
            int i =0;
            while(i<8){
                jogador_2.nome[i] = str[i];
                i++;
            }
            break; // Jogar contra a máquina
        case 3: ListaVitorias(); break;
        case 4: exit(0); break;
        case 5: RegistaJogador(); break;
        case 6: break;
        default: printf("Selecione uma opção válida!\n"); MenuTipoJogo(); break;
    }
}

// ListaVitorias
void ListaVitorias(){
    FILE *fl;
    int c;
    system("cls");
    if((fl = fopen("Dados.txt", "r")) == NULL)
    {
        CriaFicheiro();
        RegistaJogador();
    }
    while((c = fgetc(fl)) != EOF)
        printf("%c", c);

    fclose(fl);
    RegistaJogador();
}

// Imprime tabuleiro
void Tabuleiro(){
    Exemplo();
    printf("\n Jogador: %s - Vitórias: %d | Jogador: %s - Vitórias: %d \n\n", jogador_1.nome, jogador_1.vitorias,jogador_2.nome, jogador_2.vitorias);
 for(int x = 0; x<9; x++){
    if(x == 2 || x == 5){

        printf(" %c \n                                     ---|---|---\n", tabuleiro[x]);
    }else if(x == 8){
        printf(" %c ", tabuleiro[x]);
    }else{
        if(x == 0 || x == 3 || x == 6)
            printf("                                     ");
        printf(" %c |", tabuleiro[x]);
    }
 }
}

// Tabuleiro exemplo
void Exemplo(){
    printf("\n\n");
    printf("==========================================================================================\n|                                                                                        |\n|");
    printf("    Na hora de escolher a jogada digite o número da posição no tabuleiro (de 1 a 9)     |\n|                                                                                        |\n|");
 for(int x = 0; x<9; x++){
    if(x == 2 || x == 5){

        printf(" %c                                          |\n|                                    ---|---|---                                         |\n|", exemplo[x]);
    }else if(x == 8){
        printf(" %c                                          |", exemplo[x]);
    }else{
        if(x == 0 || x == 3 || x == 6)
            printf("                                    ");
        printf(" %c |", exemplo[x]);
    }
 }
    printf("\n|                                                                                        |\n");
    printf("==========================================================================================\n\n");
}

int SubJogada(int i){
                while(tabuleiro[i-1] != ' ' || i == 0){
                        i = rand() % 10;
                }
                if(CompCaractX(tabuleiro[0],tabuleiro[1],tabuleiro[2]) == 1){
                        switch(ProcuraVasio(tabuleiro[0],tabuleiro[1],tabuleiro[2])){
                            case 1: i = 1; break;
                            case 2: i = 2; break;
                            case 3: i = 3; break;
                        }
                }else if(CompCaractX(tabuleiro[3],tabuleiro[4],tabuleiro[5]) == 1){
                        switch(ProcuraVasio(tabuleiro[3],tabuleiro[4],tabuleiro[5])){
                            case 1: i = 4; break;
                            case 2: i = 5; break;
                            case 3: i = 6; break;
                        }
                }else if(CompCaractX(tabuleiro[6],tabuleiro[7],tabuleiro[8]) == 1){
                        switch(ProcuraVasio(tabuleiro[6],tabuleiro[7],tabuleiro[8])){
                            case 1: i = 7; break;
                            case 2: i = 8; break;
                            case 3: i = 9; break;
                        }
                }else if(CompCaractX(tabuleiro[0],tabuleiro[3],tabuleiro[6]) == 1){
                        switch(ProcuraVasio(tabuleiro[0],tabuleiro[3],tabuleiro[6])){
                            case 1: i = 1; break;
                            case 2: i = 4; break;
                            case 3: i = 7; break;
                        }
                }else if(CompCaractX(tabuleiro[1],tabuleiro[4],tabuleiro[7]) == 1){
                        switch(ProcuraVasio(tabuleiro[1],tabuleiro[4],tabuleiro[7])){
                            case 1: i = 2; break;
                            case 2: i = 5; break;
                            case 3: i = 8; break;
                        }
                }else if(CompCaractX(tabuleiro[2],tabuleiro[5],tabuleiro[8]) == 1){
                        switch(ProcuraVasio(tabuleiro[2],tabuleiro[5],tabuleiro[8])){
                            case 1: i = 3; break;
                            case 2: i = 6; break;
                            case 3: i = 9; break;
                        }
                }else if(CompCaractX(tabuleiro[0],tabuleiro[4],tabuleiro[8]) == 1){
                        switch(ProcuraVasio(tabuleiro[0],tabuleiro[4],tabuleiro[8])){
                            case 1: i = 1; break;
                            case 2: i = 5; break;
                            case 3: i = 9; break;
                        }
                }else if(CompCaractX(tabuleiro[2],tabuleiro[4],tabuleiro[6]) == 1){
                        switch(ProcuraVasio(tabuleiro[2],tabuleiro[4],tabuleiro[6])){
                            case 1: i = 3; break;
                            case 2: i = 5; break;
                            case 3: i = 7; break;
                        }
                }
                if(CompCaractO(tabuleiro[0],tabuleiro[1],tabuleiro[2]) == 1){
                        switch(ProcuraVasio(tabuleiro[0],tabuleiro[1],tabuleiro[2])){
                            case 1: i = 1; break;
                            case 2: i = 2; break;
                            case 3: i = 3; break;
                        }
                }else if(CompCaractO(tabuleiro[3],tabuleiro[4],tabuleiro[5]) == 1){
                        switch(ProcuraVasio(tabuleiro[3],tabuleiro[4],tabuleiro[5])){
                            case 1: i = 4; break;
                            case 2: i = 5; break;
                            case 3: i = 6; break;
                        }
                }else if(CompCaractO(tabuleiro[6],tabuleiro[7],tabuleiro[8]) == 1){
                        switch(ProcuraVasio(tabuleiro[6],tabuleiro[7],tabuleiro[8])){
                            case 1: i = 7; break;
                            case 2: i = 8; break;
                            case 3: i = 9; break;
                        }
                }else if(CompCaractO(tabuleiro[0],tabuleiro[3],tabuleiro[6]) == 1){
                        switch(ProcuraVasio(tabuleiro[0],tabuleiro[3],tabuleiro[6])){
                            case 1: i = 1; break;
                            case 2: i = 4; break;
                            case 3: i = 7; break;
                        }
                }else if(CompCaractO(tabuleiro[1],tabuleiro[4],tabuleiro[7]) == 1){
                        switch(ProcuraVasio(tabuleiro[1],tabuleiro[4],tabuleiro[7])){
                            case 1: i = 2; break;
                            case 2: i = 5; break;
                            case 3: i = 8; break;
                        }
                }else if(CompCaractO(tabuleiro[2],tabuleiro[5],tabuleiro[8]) == 1){
                        switch(ProcuraVasio(tabuleiro[2],tabuleiro[5],tabuleiro[8])){
                            case 1: i = 3; break;
                            case 2: i = 6; break;
                            case 3: i = 9; break;
                        }
                }else if(CompCaractO(tabuleiro[0],tabuleiro[4],tabuleiro[8]) == 1){
                        switch(ProcuraVasio(tabuleiro[0],tabuleiro[4],tabuleiro[8])){
                            case 1: i = 1; break;
                            case 2: i = 5; break;
                            case 3: i = 9; break;
                        }
                }else if(CompCaractO(tabuleiro[2],tabuleiro[4],tabuleiro[6]) == 1){
                        switch(ProcuraVasio(tabuleiro[2],tabuleiro[4],tabuleiro[6])){
                            case 1: i = 3; break;
                            case 2: i = 5; break;
                            case 3: i = 7; break;
                        }
                }
    return i;
}

// Regista uma jogada
void Jogada(){
    srand(time(NULL));
    if((jogada%2) == 0){
        if((jogo%2) ==0){
            printf("\nVez de %s ", jogador_1.nome);
        }else{
            printf("\nVez de %s ", jogador_2.nome);
        }
    }else{
        if((jogo%2) ==0){
            printf("\nVez de %s ", jogador_2.nome);
        }else{
            printf("\nVez de %s ", jogador_1.nome);
        }
    }
    int i = 1;
    switch(tipo){
        case 1:
            scanf("%d", &i);
            break;
        case 2:
            if(jogada%2 == 0){
                if((jogo%2) == 0){
                    scanf("%d", &i);
                }else{
                    i = SubJogada(i);
                }
            }else{
                if((jogo%2) == 0){
                    i = SubJogada(i);
                }else{
                    scanf("%d", &i);
                }
            }
            break;
    }
    system("cls");
    if(jogada%2 == 0){
        if(tabuleiro[i-1] == ' '){
            tabuleiro[i-1] = 'X';
        }else{
            printf("Opção inválida!");
            jogada--;
        }
    }else{
        if(tabuleiro[i-1] == ' '){
            tabuleiro[i-1] = 'O';
        }else{
            printf("Opção inválida!");
            jogada--;
        }
    }
    ValidaJogada();
    Tabuleiro();
}



// Valida a jogada para ver se alguem ganhou
void ValidaJogada(){
    if(tabuleiro[0] == 'X' && tabuleiro[1] == 'X' && tabuleiro[2] == 'X'
       || tabuleiro[3] == 'X' && tabuleiro[4] == 'X' && tabuleiro[5] == 'X'
       || tabuleiro[6] == 'X' && tabuleiro[7] == 'X' && tabuleiro[8] == 'X'
       || tabuleiro[0] == 'X' && tabuleiro[3] == 'X' && tabuleiro[6] == 'X'
       || tabuleiro[1] == 'X' && tabuleiro[4] == 'X' && tabuleiro[7] == 'X'
       || tabuleiro[2] == 'X' && tabuleiro[5] == 'X' && tabuleiro[8] == 'X'
       || tabuleiro[0] == 'X' && tabuleiro[4] == 'X' && tabuleiro[8] == 'X'
       || tabuleiro[2] == 'X' && tabuleiro[4] == 'X' && tabuleiro[6] == 'X'){
        if((jogo%2) == 0){
            printf("\n %s Venceu!\n", jogador_1.nome);
            jogador_1.vitorias++;
        }else{
            printf("\n %s Venceu!\n", jogador_2.nome);
            jogador_2.vitorias++;
        }

        fimJogo = 1;
        ZeraTabuleiro(); // Zerar tabuleiro
        RegistaJogador(); // Chamar o sub menu

    }else if(tabuleiro[0] == 'O' && tabuleiro[1] == 'O' && tabuleiro[2] == 'O'
             || tabuleiro[3] == 'O' && tabuleiro[4] == 'O' && tabuleiro[5] == 'O'
             || tabuleiro[6] == 'O' && tabuleiro[7] == 'O' && tabuleiro[8] == 'O'
             || tabuleiro[0] == 'O' && tabuleiro[3] == 'O' && tabuleiro[6] == 'O'
             || tabuleiro[1] == 'O' && tabuleiro[4] == 'O' && tabuleiro[7] == 'O'
             || tabuleiro[2] == 'O' && tabuleiro[5] == 'O' && tabuleiro[8] == 'O'
             || tabuleiro[0] == 'O' && tabuleiro[4] == 'O' && tabuleiro[8] == 'O'
             || tabuleiro[2] == 'O' && tabuleiro[4] == 'O' && tabuleiro[6] == 'O'){
        if((jogo%2) == 0){
            printf("\n %s Venceu!\n", jogador_2.nome);
            jogador_2.vitorias++;
        }else{
            printf("\n %s Venceu!\n", jogador_1.nome);
            jogador_1.vitorias++;
        }

        fimJogo = 1;
        ZeraTabuleiro();
        RegistaJogador();
    }else{
        if(VerificaGalo(tabuleiro[0],tabuleiro[1],tabuleiro[2]) == 1 &&
           VerificaGalo(tabuleiro[3],tabuleiro[4],tabuleiro[5]) == 1 &&
           VerificaGalo(tabuleiro[6],tabuleiro[7],tabuleiro[8]) == 1 &&
           VerificaGalo(tabuleiro[0],tabuleiro[3],tabuleiro[6]) == 1 &&
           VerificaGalo(tabuleiro[1],tabuleiro[4],tabuleiro[7]) == 1 &&
           VerificaGalo(tabuleiro[2],tabuleiro[5],tabuleiro[8]) == 1 &&
           VerificaGalo(tabuleiro[0],tabuleiro[4],tabuleiro[8]) == 1 &&
           VerificaGalo(tabuleiro[2],tabuleiro[4],tabuleiro[6]) == 1 ){
            printf("\n Deu Galo!\n");
            fimJogo = 1;
            ZeraTabuleiro();
            RegistaJogador();
        }
    }
}

// Função que reseta o jogo
void ZeraTabuleiro(){
    for(int x=0;x<9;x++){
        tabuleiro[x] = ' ';
    }
    jogo++;
}

// Função principal
int main()
{
    setlocale(LC_ALL, "Portuguese");
    RegistaJogador();
    Tabuleiro();
    while(jogada < 9){
        jogada++;
        Jogada();
    }
    RegistaJogador();
    return 0;
}
