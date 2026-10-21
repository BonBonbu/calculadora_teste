#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char *ponteiro;
int erro = 0;

// Leitura e prioridades
void pula_espacos();
double soma_diferenca();
double produto_quociente();
double potencia();
double unario();
double verifica_prioridade();

// Operacoes basicas
double multiplicacao(double numero1, double numero2);
double divisao(double numero, double divisor);
double adicao(double numero1, double numero2);
double subtracao(double numero1, double numero2);

// Operacoes cientificas
double calcular_funcao(const char *funcao, double numero);
double porcentagem(double numero);

int main()
{
    char conta[101];
    double resultado;

    printf("Conta a ser efetuada: ");

    if (fgets(conta, sizeof(conta), stdin) == NULL)
    {
        printf("Erro ao ler a conta.\n");
        return 1;
    }

    conta[strcspn(conta, "\n")] = '\0';

    ponteiro = conta;
    erro = 0;

    resultado = soma_diferenca();

    pula_espacos();

    // Verifica se toda a expressao foi interpretada
    if (erro || *ponteiro != '\0' || !isfinite(resultado))
    {
        printf("Erro: expressao invalida ou operacao impossivel.\n");
        return 1;
    }

    printf("Resultado: %.10g\n", resultado);

    return 0;
}

void pula_espacos()
{
    while (isspace((unsigned char)*ponteiro))
    {
        ponteiro++;
    }
}

double soma_diferenca()
{
    double resultado = produto_quociente();

    while (!erro)
    {
        pula_espacos();

        if (*ponteiro == '+')
        {
            ponteiro++;
            resultado = adicao(resultado, produto_quociente());
        }
        else if (*ponteiro == '-')
        {
            ponteiro++;
            resultado = subtracao(resultado, produto_quociente());
        }
        else
        {
            break;
        }
    }

    return resultado;
}

double produto_quociente()
{
    double resultado = unario();

    while (!erro)
    {
        pula_espacos();

        if (*ponteiro == '*')
        {
            ponteiro++;
            resultado = multiplicacao(resultado, unario());
        }
        else if (*ponteiro == '/')
        {
            ponteiro++;

            double divisor = unario();

            if (divisor == 0)
            {
                erro = 1;
                return NAN;
            }

            resultado = divisao(resultado, divisor);
        }
        else
        {
            break;
        }
    }

    return resultado;
}

double unario()
{
    pula_espacos();

    if (*ponteiro == '+')
    {
        ponteiro++;
        return unario();
    }

    if (*ponteiro == '-')
    {
        ponteiro++;
        return -unario();
    }

    return potencia();
}

double potencia()
{
    double base = verifica_prioridade();

    pula_espacos();

    // Porcentagem: 50% = 0.5
    while (*ponteiro == '%' && !erro)
    {
        ponteiro++;
        base = porcentagem(base);
        pula_espacos();
    }

    if (*ponteiro == '^' && !erro)
    {
        ponteiro++;

        // Permite potencias como 2^3^2
        double expoente = unario();
        base = pow(base, expoente);
    }

    return base;
}

double verifica_prioridade()
{
    double resultado;

    pula_espacos();

    // Parenteses
    if (*ponteiro == '(')
    {
        ponteiro++;
        resultado = soma_diferenca();

        pula_espacos();

        if (*ponteiro == ')')
        {
            ponteiro++;
            return resultado;
        }

        erro = 1;
        return NAN;
    }

    // Constante pi (UTF-8)
    if (strncmp(ponteiro, "π", strlen("π")) == 0)
    {
        ponteiro += strlen("π");
        return acos(-1.0);
    }

    // Raiz quadrada usando o simbolo √
    if (strncmp(ponteiro, "√", strlen("√")) == 0)
    {
        ponteiro += strlen("√");

        resultado = unario();

        if (resultado < 0)
        {
            erro = 1;
            return NAN;
        }

        return sqrt(resultado);
    }

    // Funcoes cientificas
    if (isalpha((unsigned char)*ponteiro))
    {
        char funcao[10];
        int i = 0;

        while (isalpha((unsigned char)*ponteiro))
        {
            if (i < (int)sizeof(funcao) - 1)
            {
                funcao[i++] = *ponteiro;
            }

            ponteiro++;
        }

        funcao[i] = '\0';

        pula_espacos();

        // As funcoes devem ser seguidas de parenteses
        if (*ponteiro != '(')
        {
            erro = 1;
            return NAN;
        }

        ponteiro++;

        resultado = soma_diferenca();

        pula_espacos();

        if (*ponteiro != ')')
        {
            erro = 1;
            return NAN;
        }

        ponteiro++;

        return calcular_funcao(funcao, resultado);
    }

    // Numeros inteiros e decimais
    if (isdigit((unsigned char)*ponteiro) || *ponteiro == '.')
    {
        char *final;
        resultado = strtod(ponteiro, &final);

        if (final == ponteiro)
        {
            erro = 1;
            return NAN;
        }

        ponteiro = final;
        return resultado;
    }

    erro = 1;
    return NAN;
}

double calcular_funcao(const char *funcao, double numero)
{
    // A calculadora usa graus na trigonometria
    double radianos = numero * acos(-1.0) / 180.0;

    if (strcmp(funcao, "sin") == 0)
    {
        return sin(radianos);
    }

    if (strcmp(funcao, "cos") == 0)
    {
        return cos(radianos);
    }

    if (strcmp(funcao, "tan") == 0)
    {
        // Evita tangente de 90, 270, etc.
        double angulo = fmod(fabs(numero), 180.0);

        if (fabs(angulo - 90.0) < 1e-10)
        {
            erro = 1;
            return NAN;
        }

        return tan(radianos);
    }

    if (strcmp(funcao, "sqrt") == 0)
    {
        if (numero < 0)
        {
            erro = 1;
            return NAN;
        }

        return sqrt(numero);
    }

    if (strcmp(funcao, "log") == 0)
    {
        if (numero <= 0)
        {
            erro = 1;
            return NAN;
        }

        return log10(numero);
    }

    if (strcmp(funcao, "ln") == 0)
    {
        if (numero <= 0)
        {
            erro = 1;
            return NAN;
        }

        return log(numero);
    }

    erro = 1;
    return NAN;
}

double porcentagem(double numero)
{
    return numero / 100.0;
}

double multiplicacao(double numero1, double numero2)
{
    return numero1 * numero2;
}

double divisao(double numero, double divisor)
{
    return numero / divisor;
}

double adicao(double numero1, double numero2)
{
    return numero1 + numero2;
}

double subtracao(double numero1, double numero2)
{
    return numero1 - numero2;
}
