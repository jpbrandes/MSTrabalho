#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void calcular_flambagem() {
    int opcao_secao, opcao_k;
    double b, h, d, I, E, L, K, P_crit;
    char tem_excentricidade;

    printf("==================================================\n");
    printf("   CALCULO DE FLAMBAGEM (Pcrit e Deflexao Max)    \n");
    printf("==================================================\n\n");

    // 1. Escolha da geometria e cálculo do Momento de Inércia (I)
    printf("Selecione o tipo de secao transversal da barra:\n");
    printf("1 - Retangular\n");
    printf("2 - Quadrada\n");
    printf("3 - Circular\n");
    printf("Digite a opcao (1, 2 ou 3): ");
    scanf("%d", &opcao_secao);

    if (opcao_secao == 1) {
        printf("Digite a base (b): ");
        scanf("%lf", &b);
        printf("Digite a altura (h): ");
        scanf("%lf", &h);
        
        // Na flambagem, considera-se o menor momento de inércia da seção
        double I1 = (b * pow(h, 3)) / 12.0;
        double I2 = (h * pow(b, 3)) / 12.0;
        I = (I1 < I2) ? I1 : I2;
    } 
    else if (opcao_secao == 2) {
        printf("Digite o lado do quadrado (b): ");
        scanf("%lf", &b);
        I = pow(b, 4) / 12.0;
    } 
    else if (opcao_secao == 3) {
        printf("Digite o diametro do circulo (d): ");
        scanf("%lf", &d);
        I = (M_PI * pow(d, 4)) / 64.0;
    } 
    else {
        printf("Opcao de secao invalida! Encerrando o programa.\n");
        return;
    }

    printf("\n-> Momento de inercia minimo calculado (I) = %.6e\n\n", I);

    // 2. Entrada dos dados do material e comprimento
    printf("Digite o Modulo de Elasticidade do material (E): ");
    scanf("%lf", &E);
    printf("Digite o comprimento da barra (L): ");
    scanf("%lf", &L);

    // 3. Tipo de vinculação (K)
    printf("\nSelecione o tipo de vinculacao:\n");
    printf("1 - Biengastada (K = 0.5)\n");
    printf("2 - Engastada e articulada (K = 0.7)\n");
    printf("3 - Biarticulada (K = 1.0)\n");
    printf("4 - Engastada e livre (K = 2.0)\n");
    printf("Digite a opcao de vinculacao (1, 2, 3 ou 4): ");
    scanf("%d", &opcao_k);

    switch (opcao_k) {
        case 1: K = 0.5; break;
        case 2: K = 0.7; break;
        case 3: K = 1.0; break;
        case 4: K = 2.0; break;
        default:
            printf("Opcao de vinculacao invalida! Encerrando o programa.\n");
            return;
    }

    // 4. Cálculo da Carga Crítica (Pcrit)
    P_crit = (pow(M_PI, 2) * E * I) / pow(K * L, 2);

    // 5. Opção de Excentricidade e Cálculo da Deflexão Máxima (vmax)
    printf("\nExiste excentricidade 'e'? (S/N): ");
    scanf(" %c", &tem_excentricidade);
    tem_excentricidade = toupper(tem_excentricidade);

    printf("\n==================================================\n");
    printf("                   RESULTADOS                     \n");
    printf("==================================================\n");
    printf("Carga Critica (Pcrit) = %.4f\n", P_crit);

    if (tem_excentricidade == 'S') {
        double e, P;
        printf("\nDigite o valor da excentricidade (e): ");
        scanf("%lf", &e);
        printf("Digite o valor da carga aplicada (P): ");
        scanf("%lf", &P);

        if (P >= P_crit) {
            printf("\nALERTA: A carga aplicada (P) e maior ou igual a Carga Critica (Pcrit).\n");
            printf("A barra sofrera flambagem imediata (instabilidade).\n");
        } else {
            // Fórmula: vmax = e * [ sec( sqrt(P / (E*I)) * (L / 2) ) - 1 ]
            double argumento = sqrt(P / (E * I)) * (L / 2.0);
            double secante = 1.0 / cos(argumento);
            double v_max = e * (secante - 1.0);
            printf("Deflexao Maxima (vmax) = %.6f\n", v_max);
        }
    }

    printf("==================================================\n");
    
    // Pausa o programa antes de fechar
    printf("\nPressione ENTER para sair...");
    getchar(); 
    getchar(); 
}

int main() {
    calcular_flambagem();
    return 0;
}