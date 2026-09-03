#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

int verifica_parenteses(char conta[], int inicio);
double multiplicacao(double numero1, double numero2);
double divisao(double numero, double divisor);
double adicao(double numero1, double numero2);

int main()
{
    int i = 0, j = 0, parenteses_inicial = 0, parenteses_final = 0, operador;
    char conta[101] = {0};
    double numero1[20], numero2[20];

    printf("Conta a ser efetuada: ");
    //sem espacos pois nao tem em calculadoras
    //limite de 100 caracteres
    fgets(conta, 101, stdin);
    //armazena a conta e termina em /0

    while(conta[i] != '\0' && conta[i] != '\n')
    {

        //prioridade (raiz e potencia)

        if(conta[i] == '^')
        {

        }

        //10+2*(4+10)
        //prioridade dos parenteses

        if(conta[i] == '(')
        {
            parenteses_inicial = i;
            parenteses_final = verifica_parenteses(conta, i);
            //vai ler desde o inicial ate fechar em 0 pois achou o final

            if(parenteses_final == NAN)
            {
                printf("Parenteses nao fechado\n");
                return printf("Erro\n");
            }

        }
    }

    return 0;
}

int verifica_parenteses(char conta[], int inicio)
{
    int parenteses_contagem = 1, i = inicio + 1; 
    //i = inicio para menor confusao

    while(conta[i] != '\0')
    {
        if(conta[i] == '(')
        {
            parenteses_contagem++;
        }

        if(conta[i] == ')')
        {
            parenteses_contagem--;

            if(parenteses_contagem == 0)
            {
                return i;
            }
        }

        i++;
    }

    return -1; //erro
}

double multiplicacao(double numero1, double numero2)
{
    return numero1 * numero2;
}

double divisao(double numero, double divisor)
{
    if(divisor != 0)
    {
        return numero / divisor;
    }
    
    return NAN; //erro
}

double adicao(double numero1, double numero2)
{
    return numero1 + numero2;
}

double subtracao(double numero1, double numero2)
{
    return numero1 - numero2;
}
