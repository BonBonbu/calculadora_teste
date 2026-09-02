#include <stdio.h>
#include <locale.h>

float Num1, Num2;
char operador;

float Soma(float Num1, float Num2){
    return Num1 + Num2;
}

float Subitracao(float Num1, float Num2){
    return Num1 - Num2;
}

float divisao(float Num1, float Num2){
   return Num1 / Num2;
}

float multiplicacao(float Num1, float Num2){
    return Num1 * Num2;
}

int main(){

    printf("Digite primeiro numero: \n");
    scanf("%f", &Num1);

    while(1){ /*o while tem que ser 1 para ser verdadeira*/
        printf("Digite operador: \n");
        scanf(" %c", &operador);

        if(operador == '='){
            break;
        }

        printf("Digite segundo numero: \n");
        scanf("%f", &Num2);
        switch (operador)
        {
        case '+':
            Num1 = Soma(Num1, Num2);
            break;
        case '-':
            Num1 = Subitracao(Num1, Num2);
            break;
        case '/':
            if(Num2 != 0){
                Num1 = divisao(Num1, Num2);
            }
            else{
                printf("ERRO! Nao e possivel dividir por zero.\n");
                continue;
            }
            break;
        case '*':
            Num1 = multiplicacao(Num1, Num2);
            break;
        default: 
            printf("ERRO! Operador invalido.\n");
            continue;
        }
    }

    printf("Resultado: %.2f\n", Num1);

    return 0;
}