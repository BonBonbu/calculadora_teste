#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//ele ira percorrer a cadeia de char e nao podera modifica-la
const char *ponteiro;

void pula_espacos();
double verifica_parenteses();
double multiplicacao(double numero1, double numero2);
double divisao(double numero, double divisor);
double adicao(double numero1, double numero2);

int main()
{
    char conta[101], caracteres1[50], caracteres2[50], operador;
    double numeros1, numeros2;

    printf("Conta a ser efetuada: ");
    //sem espacos pois nao tem em calculadoras
    //limite de 100 caracteres
    fgets(conta, 101, stdin);
    //armazena a conta e termina em \0

    conta[strcspn(conta, "\n")] = '\0';
    //para remover \n caso a pessoa aperte enter
    //main encurtada para deixar a ordem de prioridade melhor e mais editavel com chamadas de funcao
    
    ponteiro = conta;

    return 0;
}

void pula_espacos()
{
    while(isspace(*ponteiro))
    {
        //se onde o ponteiro aponta eh ' ', o ponteiro avanca
        ponteiro++;
    }
}

double verifica_parenteses()
{
    pula_espacos();

    if(*ponteiro == '(')
    {
        ponteiro++;
    }
    
    //criar o que resolva o que tem aqui dentro
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
