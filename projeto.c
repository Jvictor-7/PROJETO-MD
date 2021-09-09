#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int inverso(int a, int c, int a2)
{
    if ((a*a2)%c == 1) return a2;
    else inverso(a, c, a2+1);
}

void encriptar(){
    FILE *mensagem_encriptada;
    char mensagem[255];
    long int mensagem_em_numeros[255];

    // DEIXAANDO TODOS OS ELEMENTOS DO ARRAY MENSAGEM = 0
    for (int i = 0; i < 255; i++){
        mensagem_em_numeros[i] = -63;
        mensagem[i] = 0;
    }

    int n, e;

    printf("Digite a mensagem a ser encriptada:\n");
    scanf(" %[^\n]", mensagem);
    printf("Digite a sua chave pública recebida previamente:\n");
    scanf("%d %d", &n, &e);

    // DEIXANDO TODOS OS ELEMENTOS DO ARRAY MENSAGEM COM O VALOR CERTO DO PROJETO, USANDO TABELA ASCII
    for (int i = 0; i < 255; i++){
        if (mensagem[i] == ' ') mensagem_em_numeros[i] = 28;
        else mensagem_em_numeros[i] = mensagem[i] - 63;
    }

    // CRIPTOGRAFANDO A MENSAGEM
    for (int i = 0; i < 255; i++){
        if (mensagem_em_numeros[i] != -63 && mensagem_em_numeros[i+1] == -63)
        {
            printf("MENSAGEM[i] antes: %ld\n", mensagem_em_numeros[i]);
            mensagem_em_numeros[i] = pow(mensagem_em_numeros[i],e);
            mensagem_em_numeros[i] %= n;
            printf("MENSAGEM[i] depois: %ld\n", mensagem_em_numeros[i]);
            break;
        }
        else{
            printf("MENSAGEM[i] antes: %ld\n", mensagem_em_numeros[i]);
            mensagem_em_numeros[i]  = pow(mensagem_em_numeros[i],e);
            mensagem_em_numeros[i] %= n;
            printf("MENSAGEM[i] depois: %ld\n", mensagem_em_numeros[i]);
        }
    }

    // Abrir/Criar arquivo txt
    mensagem_encriptada = fopen("encrypted_message.txt", "w"); 
    fprintf(mensagem_encriptada, "Você digitou: ");
    for (int i = 0; i < 255; i++){
        if (mensagem[i] != -63 && mensagem[i+1] == -63)
        {
            fprintf(mensagem_encriptada, "%d\n", mensagem[i]);
            break;
        }
        else fprintf(mensagem_encriptada, "%d", mensagem[i]);
    }
    fclose(mensagem_encriptada);
}

void gerar_chave(){
    FILE *chave_publica;
    int p, q, n, e, d, z;

    //Inserir P, Q e E

    printf("Você escolheu gerar uma chave pública...\n");
    printf("Por favor, digite um par de números primos:\n");
    scanf("%d%d", &p, &q);
    n = p * q;
    z = (p-1)*(q-1);
    printf("Agora digite um expoente relativamente primo a %d:\n", z);
    scanf("%d", &e);
    d = inverso(e, (p-1)*(q-1), 0);

    // Abrir/Criar arquivo txt

    chave_publica = fopen("public_key.txt", "w"); 
    fprintf(chave_publica, "Sua chave pública: (%d, %d)", n, e);
    fclose(chave_publica);
}

int main(){
    printf("Bem vindo ao projeto de Criptografia RSA!\n");
    printf("Escolha uma das opções seguintes:\n1 - Gerar chave pública\n2 - Encriptar\n3 - Desencriptar\n");

    int opcao;
    scanf("%d", &opcao);

    while(opcao != 1 && opcao !=2 && opcao !=3){
        printf("Escolha inválida, tente novamente!\n");
        scanf("%d", &opcao);
    }

    if(opcao == 1){
        gerar_chave();
    }
    if(opcao == 2){
        encriptar();
    }
    if(opcao == 3){

    }
    
    return 0;
}