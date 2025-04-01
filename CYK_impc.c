#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define MAX_RULES 50
#define MAX_SYMBOLS 10

// Estructura para una regla    
typedef struct {
    char lhs[10];                 
    int rhs_len;                    
    char rhs[MAX_SYMBOLS][10];      
} Rule;

    
char table[MAX][MAX][MAX_SYMBOLS][10]; 
int table_count[MAX][MAX];             

// Lista de reglas
Rule rules[MAX_RULES];
int rule_count = 0;

// Agregar una regla
void add_rule(const char* lhs, int rhs_len, const char* rhs[]) {
    strcpy(rules[rule_count].lhs, lhs);
    rules[rule_count].rhs_len = rhs_len;
    for (int i = 0; i < rhs_len; i++) {
        strcpy(rules[rule_count].rhs[i], rhs[i]);
    }
    rule_count++;
}

// Verifica si ya existe un símbolo en la tabla
int contains(int i, int j, const char* symbol) {
    for (int k = 0; k < table_count[i][j]; k++) {
        if (strcmp(table[i][j][k], symbol) == 0) return 1;
    }
    return 0;
}

// Agrega un símbolo a la tabla
void insert_symbol(int i, int j, const char* symbol) {
    if (!contains(i, j, symbol)) {
        strcpy(table[i][j][table_count[i][j]++], symbol);
    }
}

// Algoritmo CYK
void cykParse(char* w[], int n) {
    memset(table_count, 0, sizeof(table_count));

    // Fase 1: colocar reglas terminales
    for (int j = 0; j < n; j++) {
        for (int r = 0; r < rule_count; r++) {
            if (rules[r].rhs_len == 1 && strcmp(rules[r].rhs[0], w[j]) == 0) {
                insert_symbol(j, j, rules[r].lhs);
            }
        }
    }

    // Fase 2: reglas no terminales
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                for (int r = 0; r < rule_count; r++) {
                    if (rules[r].rhs_len == 2) {
                        for (int a = 0; a < table_count[i][k]; a++) {
                            for (int b = 0; b < table_count[k + 1][j]; b++) {
                                if (strcmp(table[i][k][a], rules[r].rhs[0]) == 0 &&
                                    strcmp(table[k + 1][j][b], rules[r].rhs[1]) == 0) {
                                    insert_symbol(i, j, rules[r].lhs);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Verificar si el símbolo inicial está en la raíz de la tabla
    int found = 0;
    for (int i = 0; i < table_count[0][n - 1]; i++) {
        if (strcmp(table[0][n - 1][i], "E") == 0) {
            found = 1;
            break;
        }
    }

    printf("%s\n", found ? "True" : "False");
}

// Main
int main() {
    // Reglas de la gramática
    const char* r1[] = {"E", "DERECHASUMA"};   add_rule("E", 2, r1);
    const char* r2[] = {"T", "DERECHAMUL"};    add_rule("E", 2, r2);
    const char* r3[] = {"id"};                 add_rule("E", 1, r3);
    const char* r4[] = {"num"};                add_rule("E", 1, r4);
    const char* r5[] = {"PARI", "PARENCIERRE"}; add_rule("E", 2, r5);
    const char* r6[] = {"OPSUMA", "T"};        add_rule("DERECHASUMA", 2, r6);
    const char* r7[] = {"T", "DERECHAMUL"};    add_rule("T", 2, r7);
    const char* r8[] = {"OPMUL", "F"};         add_rule("DERECHAMUL", 2, r8);
    const char* r9[] = {"id"};                 add_rule("T", 1, r9);
    const char* r10[] = {"num"};               add_rule("T", 1, r10);
    const char* r11[] = {"PARI", "PARENCIERRE"}; add_rule("T", 2, r11);
    const char* r12[] = {"id"};                add_rule("F", 1, r12);
    const char* r13[] = {"num"};               add_rule("F", 1, r13);
    const char* r14[] = {"PARI", "PARENCIERRE"}; add_rule("F", 2, r14);
    const char* r15[] = {"E", "PARD"};         add_rule("PARENCIERRE", 2, r15);
    const char* r16[] = {"*"};                 add_rule("OPMUL", 1, r16);
    const char* r17[] = {"/"};                 add_rule("OPMUL", 1, r17);
    const char* r18[] = {"+"};                 add_rule("OPSUMA", 1, r18);
    const char* r19[] = {"-"};                 add_rule("OPSUMA", 1, r19);
    const char* r20[] = {"("};                 add_rule("PARI", 1, r20);
    const char* r21[] = {")"};                 add_rule("PARD", 1, r21);

    // Ejemplo de expresión a analizar
    char* sentence[] = {"num", "+", "num", "/", "(","num","-","num",")"};
    int n = sizeof(sentence) / sizeof(sentence[0]);

    cykParse(sentence, n);

    return 0;
}
