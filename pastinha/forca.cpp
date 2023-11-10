// ATIVIDADE JOGO DA FORCA
// Grupo:
// Gustavo Kenji Mendonça Kaneko - RA: 23002633
// Marcela de Siqueira Franco - RA: 23013238
#define TAM 11
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// BOAS VINDASSSSSSSS
int cabecalho(){
    int escolha;
    cout << " ====================================== " << endl;
    cout << "             JOGO DA FORCA              " << endl;
    cout << " -------------------------------------- " << endl;
    cout << "               1 - JOGAR                " << endl;
    cout << "               2 - SAIR                 " << endl;
    cout << " -------------------------------------- " << endl;
    cout << " > Digite sua escolha: ";
    cin >> escolha;
    return escolha;
}

// DESENHAR FORCAAAAAAAAAAAAAAAAAAAAA
void desenha_forca(int k, const char vetorErros[], const char vetorAcertos[]) {
    cout << "Forca:" << endl;
    // inicio da forca 
    cout << "---------" << endl;
    cout << "|       |" << endl;

    switch(k) {
        case 0: // zero erros imprime sem bonequinho
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            break;
        case 1: // 1 erro = cabeca
            cout << "|       O" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            break;
        case 2: // 2 erros = corpinho1
            cout << "|       O" << endl;
            cout << "|       |" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            break;
        case 3: // 3 erros = corpinho2
            cout << "|       O" << endl;
            cout << "|       |" << endl;
            cout << "|       |" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            break;
        case 4: // 4 erros = braco1
            cout << "|       O" << endl;
            cout << "|      /|" << endl;
            cout << "|       |" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            break;
        case 5: // 5 erros = braco2
            cout << "|       O" << endl;
            cout << "|      /|/ "<< endl;
            cout << "|       |" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            break;
            // final = bonequinho morto 
        default:
            cout << "|       O" << endl;
            cout << "|      /|/" << endl;
            cout << "|       |" << endl;
            cout << "|      / /" << endl;
            cout << "|" << endl;
            break;
    }

    cout << "|_______|" << endl;
    // imprime as letras q o usuario errou, armazenadas no vetorErros, k é o numero de erros
    cout << "Letras erradas: ";
    for (int i = 0; i < k; i++) {
        cout << vetorErros[i] << ' ';
    }
    cout << endl;

    // imprime a palavra com underline, trocando os que o usuario acertou a letra de acordo com o vetorAcertos
    cout << "Palavra: ";
    for (int i = 0; i < strlen(vetorAcertos); i++) {
        cout << vetorAcertos[i] << ' ';
    }
    cout << endl;
        
}

// FAZER A JOGADAAAAAAAAAAA
int jogada(const char palavra[], char vetorAcertos[], char vetorErros[], int *erros, int* acertos) {
    char letra;
    int i;
    // insercao da letra
    // verifica se é: asterisco -> letra -----> se realmente for uma letra ela vira maiuscula
    do {
        cout << "\nDigite uma letra: ";
        cin >> letra;

        if (letra == '*') {
        // asterisco = desistir --> retorna -1
        return -1;
        }
        
        // funcao isalpha = verifica se é parte do alfabeto, 
        if (!isalpha(letra)) {
            cout << "Por favor, insira uma letra válida." << endl;
        }
    } while (!isalpha(letra)); // repete ate que o usuario insira uma letra 

    letra = toupper(letra);  // se a letra digitada for minuscula ela viramaiuscula (funcao toupper)

    
    // VERIFICAR SE O USUARIO ACERTOU UMA LETRA DA PALAVRA SORTEADA OU NAO
    bool acertouu = false; // comeca a BOOl com false
    for (i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == letra) { // percorre a palavra secreta e verifica se a letra inserida pertence a palavra
            if (vetorAcertos[i] == '_') {
                vetorAcertos[i] = letra; // se SIM, substitui o underline da posicao da letra pela letra inserida
                acertouu = true; // BOOL vira TRUE dentro do FOR --> letra ESTÁ na palavra
                (*acertos)++; // aumenta o numero de acertos em 1 (letra)
            }
        }
    }

    if (!acertouu) { // se a BOOL não se tornou verdadeira dentro do FOR, entao o usuario nao acertou
        vetorErros[*erros] = letra; // adiciona a letra (errada) ao vetorErros para imprimir (na funcao da forca)
        (*erros)++; // aumenta o numero de erros em 1 (letra repetida conta como erro, maximo de 6 erros)
    }
    return 0;
}

// SORTEAR A PALAVRAAAAAA
void sorteio_palavra(char palavra[], char BANCOPALAVRAS[][21], char vetorAcertos[]){
    int i, m;
    m = rand() % TAM; // variavel m = recebe o numero de 1 a 11 (valor de TAM) q a funcao rand() sorteou
    strcpy(palavra, BANCOPALAVRAS[m]); // copia para a palavra secreta a palavra de indice m no banco de palavras
    // for para tracinhos
    for (i=0; i<strlen(palavra); i++) // percorre o comprimento da palavra secreta
    {
        vetorAcertos[i] = '_'; // imprime underline no vetor de acertos (palavra é secreta)
    }
    vetorAcertos[strlen(palavra)] = '\0'; // barra zero no final -- transforma o vetor em uma string
}

// INT MAINNNNNNNNNN
int main(){
    // funcao srand pra sortear a palavra 
    srand(time(0));

    // variaveis importantes
    char palavra[20]; // palavra secreta
    char vetorAcertos[30];
    char vetorErros[7];
    int acertos=0, erros=0; //tirar?
    int maximo_chances=6; // maximo de erros é 6
    int resultado; // variavel q recebe o resultado da jogada 
    // BANCO DE PALAVRAS, TEM 11
    char BANCOPALAVRAS [TAM][21] = {"VOLEI", "FUTEBOL", "BASQUETE", "NATACAO", "CICLISMO", "SKATE", "HANDBALL", "TENIS", "CORRIDA", "BOXING", "BASEBALL"};

    int opcao; // opcao é a variavel que recebe a escolha do jogador (1- jogar, 2- sair)
    do {
        opcao = cabecalho(); 
        if (opcao==1) {
            // se o jogador escolher 1- JOGAR, imprime as regras e inicia o jogo
            cout << " -------------------------------------- " << endl;
            cout << "                 REGRAS                 " << endl;
            cout << "  > Tente adivinhar a palavra secreta   "<< endl;
            cout << "           > Tema: Esportes             "<< endl;
            cout << "        > Máximo de erros = 6           "<< endl;
            cout << "  > Digite asterisco (*) para desistir  "<< endl;
            cout << " -------------------------------------- " << endl;
            cout << "            JOGO INICIADO!              \n" << endl;
            acertos=0; erros=0; // inicia com zeroo
            sorteio_palavra(palavra, BANCOPALAVRAS, vetorAcertos); // sorteia a palavra entre as do banco

            // CONTINUAR AQUI
            // enquanto o num de erros for menor q 6, e o num de acertos for menor q o comprimento da palavra secreta
            // repete o processo de imprimir a forca, jogada e verificacao se ganhou ou perdeu
            while(erros < maximo_chances && acertos < strlen(palavra))
            {
                desenha_forca(erros, vetorErros, vetorAcertos); // desenha a forca
                resultado = jogada(palavra, vetorAcertos, vetorErros, &erros, &acertos); // usuario faz a jogada
                if (resultado == -1) // quando retorna -1 é porque o usuário desistiu (digitou asterisco)
                {
                    cout << " -------------------------------------- " << endl;
                    cout << "           JOGO ENCERRADO!              " << endl;
                    break;
                }
            }
            if (erros == maximo_chances) desenha_forca(erros, vetorErros, vetorAcertos); // desenha a forca pro bonequinho morto (maximo de erros)
            if (acertos == strlen(palavra)) { // se o num de acertos for igual ao comprimento da palavra, entao o usuario GANHOU o jogo
                    cout << " -------------------------------------- " << endl;
                    cout << "          PARABENS, VOCE GANHOU!        \n" << endl;
                } else if (erros == maximo_chances) {
                    // se o num de erros atinge 6, o usuario PERDEU o jogo
                    cout << " -------------------------------------- " << endl;
                    cout << "             VOCE PERDEU!               \n" << endl;
                    cout << "   A palavra secreta era: " << palavra << "\n"; // imprime a resposta
                }
        }
    } while (opcao==1); // repete o menu quando acaba o jogo
    cout << " -------------------------------------- " << endl;
    cout << "                  FIM                   " << endl;
    return 0;
}
