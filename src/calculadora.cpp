#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//ele ira percorrer a cadeia de char e nao podera modifica-la
const char *ponteiro;

//leitura e prioridades
void pula_espacos();
double soma_diferenca();
double produto_quociente();
double verifica_prioridade();

//operacoes basicas
double multiplicacao(double numero1, double numero2);
double divisao(double numero, double divisor);
double adicao(double numero1, double numero2);
double subtracao(double numero1, double numero2);

int main()
{
    char conta[101];
    double resultado;

    printf("Conta a ser efetuada: ");
    //limite de 100 caracteres
    fgets(conta, 101, stdin);
    //armazena a conta e termina em \0

    conta[strcspn(conta, "\n")] = '\0';
    //para remover \n caso a pessoa aperte enter
    
    ponteiro = conta;

    resultado = soma_diferenca();
    //chama o parser

    printf("%lf\n", resultado);

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

double soma_diferenca()
{
    double resultado = produto_quociente(); //chama para ver se 'pq' sabe resolver

    while(1)
    {
        pula_espacos();

        if(*ponteiro == '+')
        {
            ponteiro++;
            
            pula_espacos();

            resultado = adicao(resultado, produto_quociente());
        }
        
        else if(*ponteiro == '-')
        {
            ponteiro++;
            
            pula_espacos();

            resultado = subtracao(resultado, produto_quociente());
        }

        else
            break;
        
    }

    return resultado;
}

double produto_quociente()
{
    double resultado = verifica_prioridade(); //chama para ver se 'vp' sabe resolver

    while(1)
    {
        pula_espacos();

        if(*ponteiro == '*')
        {
            ponteiro++;

            pula_espacos();

            resultado = multiplicacao(resultado, verifica_prioridade());
            
        }

        else if(*ponteiro == '/')
        {
            ponteiro++;
            
            pula_espacos();

            resultado = divisao(resultado, verifica_prioridade());
        }

        else
            break;
        
    }

    return resultado;
}

double verifica_prioridade()
{
    double resultado;

    pula_espacos();

    if(*ponteiro == '(')
    {
        ponteiro++;

        pula_espacos();

        resultado = soma_diferenca();

        if(*ponteiro == ')')
        {
            ponteiro++;
            return resultado; //achouuuu
        }
        
    }

    if(isdigit(*ponteiro) || *ponteiro == '.')
    {
        double numero;
        char *final; // outro ponteiro pq essa funcao nao aceita const char * na segunda parte :(

        numero = strtod(ponteiro, &final);
        ponteiro = final;

        return numero;
    }

    return NAN; // nenhum dos ifs retornaram algo = erro
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
