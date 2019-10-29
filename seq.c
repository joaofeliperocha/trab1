#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

//Macro utilizado para definir todas as funções
#define FUNCAO(opcao, x) ((opcao) == 'a') ? 1 + (x) : ((opcao) == 'c') ? sqrt(1 + pow(x, 4)) : ((opcao) == 'd') ? sin(pow(x, 2)): ((opcao) == 'e') ? cos(pow(2.71828182845904523536, x * -1)) : ((opcao) == 'f') ? cos(pow(2.71828182845904523536, x * -1)) * x : ((opcao) == 'g') ? cos(pow(2.71828182845904523536, x * -1)) * (0.005 * pow(x, 3) + 1) : (x > -1 || x < 1) ? sqrt(1 - pow(x, 2)) : 0 


//Função recursiva do método de integração numérica retangular que utiliza a estratégia da quadratura adaptativa 
double quadAdapt(char funcEscolhida, double a, double b, double err) {

    double m, f, AltRet1, AltRet2, retMenorA, retMenorB, retMaior;
    double m1, m2;

    //Cálculo do ponto médio
    m = ((a + b) / 2);

    //Chamando a função que será calculada 
    f = FUNCAO(funcEscolhida, m);

    m1 = ((a + m) / 2);
    m2 = ((m + b) / 2);

    //Altura dos retângulos
    AltRet1 = FUNCAO(funcEscolhida, m1);
    AltRet2 = FUNCAO(funcEscolhida, m2);

    //Área do retângulo maior
    retMaior = (b - a) * f;

    //Área dos outros retângulos menores
    retMenorA = (m - a) * AltRet1;
    retMenorB = (b - m) * AltRet2;

    //Se o cáculo desse módulo for maior que o erro
    if (fabsf(retMaior - (retMenorA + retMenorB)) > err) {
        //Será realizado uma chamada recursiva, onde a área é definida pela a soma das áreas dos retângulos menores
        retMaior = quadAdapt(funcEscolhida, a, m, err) + quadAdapt(funcEscolhida, m, b, err);
    }
    //Retorna a área do retângulo 
    return retMaior;
}

int main(int argc, char const *argv[]) {
    double a, b, erro;
    double inicio, fim, tempoGasto;
    char funcEscolhida;

    GET_TIME(inicio);

    if (argc < 4) {
        printf("Digite: <(intervalo minimo)> <(intervalo maximo)> <(erro)>\n");
        exit(1);
    }
    a = atof(argv[1]);
    b = atof(argv[2]);
    erro = atof(argv[3]);

    printf("Deseja usar qual funcao?\n");
    printf(" a) f(x) = 1 + x \n b) f(x) = sqrt(1 - x^2), -1 < x < 1  \n c) f(x) = sqrt(1 + x^4) \n d) f(x) = sen(x^2) \n e) f(x) = cos(e^-x) \n f) f(x) = cos(e^-x) * x \n g) f(x) = cos(e^-x) * (0.005 * x^3 + 1)\n");
    do {
        printf("a, b, c, d, e, f ou g (somente letras minusculas):");
        scanf("%c", &funcEscolhida);
        if (funcEscolhida == 'b' && (a < -1 || b > 1)) {
            printf("Intervalo incorreto!\n");
            funcEscolhida = 'h';
        }
    } while (funcEscolhida != 'a' && funcEscolhida != 'b' && funcEscolhida != 'c' && funcEscolhida != 'd' && funcEscolhida != 'e' && funcEscolhida != 'f' && funcEscolhida != 'g') ;

    printf("Valor aproximado da integral: %.10f\n", quadAdapt(funcEscolhida, a, b, erro));

    GET_TIME(fim);
    tempoGasto = fim - inicio;
    printf("Tempo gasto: %.5f\n", tempoGasto);

    return 0;
}