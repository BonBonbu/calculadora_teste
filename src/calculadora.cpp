#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

void caracteres_invisiveis(char array[]);
int verifica_parenteses(char conta[], int inicio);
double multiplicacao(double numero1, double numero2);
double divisao(double numero, double divisor);
double adicao(double numero1, double numero2);

int main()
{
    int i = 0, j = 0, parenteses_inicial = 0, parenteses_final = 0, contador = 0;
    char conta[101], caracteres1[50], caracteres2[50], operador;
    double numeros1, numeros2;

    caracteres_invisiveis(conta);

    printf("Conta a ser efetuada: ");
    //sem espacos pois nao tem em calculadoras
    //limite de 100 caracteres
    fgets(conta, 101, stdin);
    //armazena a conta e termina em /0

    while(conta[i] != '\0' && conta[i] != '\n')
    {
        //prioridade (raiz e potencia)

        //10+2*(4+10)
        //prioridade dos parenteses

        if(conta[i] == '(')
        {
            parenteses_inicial = i;
            parenteses_final = verifica_parenteses(conta, i);
            //vai ler desde o inicial ate fechar em 0 pois achou o final

            j = parenteses_inicial;

            while(j < parenteses_final)
            {
                if((isdigit(conta[j]) || conta[j] == '.') && contador == 0)
                {
                    //se o caractere for numerico ou um . armazena na array
                    caracteres1[j] = conta[j];
                }
                else if((isdigit(conta[j]) || conta[j] == '.') && contador == 1)
                {
                    caracteres2[j] = conta[j];
                }
                else
                {
                    operador = conta[j];
                    contador++;
                }
                
                j++;
            }

            numeros1 = atof(caracteres1);
            numeros2 = atof(caracteres2);


            if(parenteses_final == NAN)
            {
                printf("Parenteses nao fechado\n");
                return printf("Erro\n");
            }

        }

        i++;
    }

    return 0;
}

void caracteres_invisiveis(char array[])
{
    //para que nao tenha espacos vazios

    int i = 0;

    while(array[i] != '\0')
    {
        array[i] = '#';
        i++;
    }
}

int verifica_parenteses(char conta[], int i)
{
    int parenteses_contagem = 1;
    i++;

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
