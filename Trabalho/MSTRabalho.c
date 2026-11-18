#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>
#define PI 3.14159265358979323846

// FEITO POR LUCAS EMANUEL GALVÃO CORREA E JOÃO PEDRO BRANDES

void calcular_flambagem() {
    int opcao_secao, opcao_k;
    // Foi escolhido o double ao invés do float pela precisão de
    // 15 a 16 casas decimais
    double comprimento_de_base_b = 0, altura_h = 0, diametro_d = 0, I = 0;
    double modulo_elasticidade_material_E = 0, comprimento_barra_L = 0, tipo_de_vinculacao_K = 0, Carga_critica_P = 0;
    char tem_excentricidade;

    printf("==================================================\n");
    printf("    CÁLCULO DE FLAMBAGEM (Pcrit e Deflexao Max)   \n");
    printf("==================================================\n\n");

    do {
        // 1. Escolha da geometria e cálculo do MENOR Momento de Inércia (I)
        printf("Selecione o tipo de seção transversal da barra:\n");
        printf("1 - Retangular\n");
        printf("2 - Quadrada\n");
        printf("3 - Circular\n");
        printf("Digite a opção (1, 2 ou 3): ");
        scanf("%d", &opcao_secao);
        printf("\nOBS: Utilize `.` para separar número com ponto flutuante.\n");

        if (opcao_secao == 1) {
            do {
                printf("Digite o comprimento da base (b) (em metros): ");
                scanf("%lf", &comprimento_de_base_b); // %lf para ler double
                if (comprimento_de_base_b <= 0) {
                    printf("Valor inválido! O comprimento da base deve ser positivo.\n");
                }
            } while (comprimento_de_base_b <= 0);

            do {
                printf("Digite a altura (h) (em metros): ");
                scanf("%lf", &altura_h);
                if (altura_h <= 0) {
                    printf("Valor inválido! A altura deve ser positiva.\n");
                }
            } while (altura_h <= 0);

            // Na flambagem, considera-se o menor momento de inércia da seção
            double I1 = (comprimento_de_base_b * pow(altura_h, 3)) / 12.0;
            double I2 = (altura_h * pow(comprimento_de_base_b, 3)) / 12.0;
            I = (I1 < I2) ? I1 : I2; // Operador Ternário
            // I1 < I2: verifica se I1 é menor que I2.
            // ? I1: se for verdadeiro, guarda o valor de I1.
            // : I2: se for falso, guarda o valor de I2.
        }
        else if (opcao_secao == 2) {
            do {
                printf("Digite o lado do quadrado (b) (em metros): ");
                scanf("%lf", &comprimento_de_base_b);
                if (comprimento_de_base_b <= 0) {
                    printf("Valor inválido! O comprimento do lado deve ser positivo.\n");
                }
            } while (comprimento_de_base_b <= 0);

            I = pow(comprimento_de_base_b, 4) / 12.0;
            // Momento de Inercia é igual tanto em X quanto em Y
        }
        else if (opcao_secao == 3) {
            do {
                printf("Digite o diâmetro do circulo (d) (em metros): ");
                scanf("%lf", &diametro_d);
                if (diametro_d <= 0) {
                    printf("Valor inválido! O diâmetro deve ser positivo.\n");
                }
            } while (diametro_d <= 0);

            I = (PI * pow(diametro_d, 4)) / 64.0;
            // fórmula com o raio => PI * pow(r,4) / 4
        }
        else {
            printf("\nOpção de seção inválida! Digite opção de seção válida\n\n");
        }
    } while (opcao_secao != 1 && opcao_secao != 2 && opcao_secao != 3);

    printf("\n-> Momento de inércia, da seção de área, mínimo calculado (I) (em m^4) = %.8g\n\n", I);

    // 2. Entrada dos dados do material e comprimento
    do {
        printf("Digite o Módulo de Elasticidade do material (E) (em pascal): ");
        scanf("%lf", &modulo_elasticidade_material_E);
        if (modulo_elasticidade_material_E <= 0) {
            printf("Valor inválido! O módulo de elasticidade deve ser positivo.\n");
        }
    } while (modulo_elasticidade_material_E <= 0);

    do {
        printf("Digite o comprimento da barra (L) (em metros): ");
        scanf("%lf", &comprimento_barra_L);
        if (comprimento_barra_L <= 0) {
            printf("Valor inválido! O comprimento deve ser positivo.\n");
        }
    } while (comprimento_barra_L <= 0);

    do {
        // 3. Tipo de vinculação (K)
        printf("\nSelecione o tipo de vinculação:\n");
        printf("1 - Biengastada (K = 0.5)\n");
        printf("2 - Engastada e articulada (K = 0.7)\n");
        printf("3 - Biarticulada (K = 1.0)\n");
        printf("4 - Engastada e livre (K = 2.0)\n");
        printf("Digite a opção de vinculação (1, 2, 3 ou 4): ");
        scanf("%d", &opcao_k);

        switch (opcao_k) {
            case 1: tipo_de_vinculacao_K = 0.5; break;
            case 2: tipo_de_vinculacao_K = 0.7; break;
            case 3: tipo_de_vinculacao_K = 1.0; break;
            case 4: tipo_de_vinculacao_K = 2.0; break;
            default:
                printf("\nOpção de vinculação inválida! Digite opção de vinculação válida.\n\n");
        }
    } while (opcao_k != 1 && opcao_k != 2 && opcao_k != 3 && opcao_k != 4);

    // 4. Cálculo da Carga Crítica (Pcrit)
    Carga_critica_P = (pow(PI, 2) * modulo_elasticidade_material_E * I) / pow(tipo_de_vinculacao_K * comprimento_barra_L, 2);

    // 5. Opção de Excentricidade e Cálculo da Deflexão Máxima (vmax)
    printf("\nExiste excentricidade 'e'? (S/N): ");
    do {
        scanf(" %c", &tem_excentricidade);
        tem_excentricidade = toupper(tem_excentricidade);
        if (tem_excentricidade != 'S' && tem_excentricidade != 'N') {
            printf("\nOpção inválida! Digite opção válida.\n\n");
        }
    } while (tem_excentricidade != 'S' && tem_excentricidade != 'N');

    printf("\n==================================================\n");
    printf("                    RESULTADOS                    \n");
    printf("==================================================\n");
    printf("Carga Crítica (Pcrit) = %.8g N\n", Carga_critica_P);

    if (tem_excentricidade == 'S') {
        double excentricidade_e, carga_aplicada_P;
        printf("\nDigite o valor da excentricidade (e) (em m): ");
        scanf("%lf", &excentricidade_e);
        printf("Digite o valor da carga aplicada (P) (em Newtons): ");
        scanf("%lf", &carga_aplicada_P);

        if (carga_aplicada_P >= Carga_critica_P) {
            printf("\nATENÇÃO: A carga aplicada (P) e maior ou igual a Carga Critica (Pcrit).\n");
            printf("A barra sofrerá flambagem imediata (instabilidade).\n");
        } else {
            // Fórmula: vmax = e * [ sec( sqrt(P / (E*I)) * (L / 2) ) - 1 ]
            double argumento = sqrt(carga_aplicada_P / (modulo_elasticidade_material_E * I)) * (comprimento_barra_L / 2.0);
            double secante = 1.0 / cos(argumento);
            double v_max = excentricidade_e * (secante - 1.0);
            printf("Deflexão Máxima (vmax) = %.8g m\n", v_max);
            printf("OBS: Essa expressão e valida para o caso clássico de uma coluna biarticulada\n");
            printf("com carga excentrica aplicada de maneira simétrica nas extremidades.\n");
        }
    }

    printf("==================================================\n");

    // Pausa o programa antes de fechar
    printf("\nPressione ENTER para sair...");
    getchar();
    getchar();
}

int main() {
    setlocale(LC_CTYPE, "Portuguese"); // É necessário colocar LC_CTYPE ao invés de LC_ALL pois o LC_ALL pode quebrar a leitura dos números, O LC_CTYPE mantém apenas os acentos.
    calcular_flambagem();
    return 0;
}