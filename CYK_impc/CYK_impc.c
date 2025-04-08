#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_TOKEN_CAPACITY 100  // Capacidad inicial para el arreglo de tokens (usado en tokenize dinámica)
#define MAX_RULES 50
#define MAX_SYMBOLS 10
#define MAX_STR_SIZE 200

// Estructura para una regla de gramática.
typedef struct {
    char lhs[MAX_STR_SIZE];
    int rhs_len;
    char rhs[MAX_SYMBOLS][10];
} Rule;

Rule rules[MAX_RULES];
int rule_count = 0;

// Agregar una regla a la gramática.
void add_rule(const char* lhs, int rhs_len, const char* rhs[]) {
    strcpy(rules[rule_count].lhs, lhs);
    rules[rule_count].rhs_len = rhs_len;
    for (int i = 0; i < rhs_len; i++) {
        strcpy(rules[rule_count].rhs[i], rhs[i]);
    }
    rule_count++;
}

// Función auxiliar para tokenización dinámica de una línea.
// Se aplican las siguientes reglas:
//    '+' o '-'      -> "opSuma"
//    '*' o '/'      -> "opMul"
//    '(' o ')'      -> "(" o ")"
//    [0-9]+         -> "num"
//    [a-zA-Z_][a-zA-Z0-9_]* -> "id"
// Se ignoran espacios y tabuladores.
// El arreglo de tokens se asigna dinámicamente y se retorna su tamaño en count.
int tokenize(const char *line, char ***tokens_out) {
    int capacity = INITIAL_TOKEN_CAPACITY;
    int count = 0;
    char **tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        perror("Error al asignar memoria para tokens");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (line[i] != '\0') {
        // Ignorar espacios y tabuladores
        if (line[i] == ' ' || line[i] == '\t') {
            i++;
            continue;
        }
        const char *token_val = NULL;
        if (line[i] == '+') {
            token_val = "+";
            i++;
        }
        else if (line[i] == '-') {
            token_val = "-";
            i++;
        }
        else if (line[i] == '*') {
            token_val = "*";
            i++;
        }
        else if (line[i] == '/') {
            token_val = "/";
            i++;
        }
        // Paréntesis
        else if (line[i] == '(') {
            token_val = "(";
            i++;
        }
        else if (line[i] == ')') {
            token_val = ")";
            i++;
        }
        // Secuencia de dígitos: [0-9]+
        else if (isdigit((unsigned char)line[i])) {
            while (isdigit((unsigned char)line[i])) {
                i++;
            }
            token_val = "num";
        }
        // Secuencia de letras o guion bajo: [a-zA-Z_][a-zA-Z0-9_]*
        else if (isalpha((unsigned char)line[i]) || line[i] == '_') {
            while (isalnum((unsigned char)line[i]) || line[i] == '_') {
                i++;
            }
            token_val = "id";
        }
        // Si no coincide con ninguna regla conocida, se trata como token individual.
        else {
            char *temp = malloc(2);
            if (temp == NULL) {
                perror("Error al asignar memoria para token individual");
                exit(EXIT_FAILURE);
            }
            temp[0] = line[i];
            temp[1] = '\0';
            token_val = temp;
            i++;
        }

        // Reajustar el arreglo de tokens si es necesario.
        if (count >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(char *));
            if (tokens == NULL) {
                perror("Error al re-asignar memoria para tokens");
                exit(EXIT_FAILURE);
            }
        }
        tokens[count++] = (char *) token_val;
    }
    *tokens_out = tokens;
    return count;
}

// Función auxiliar para verificar si en la celda (i,j) de la tabla dinámica ya existe el símbolo.
int contains_dyn(char ****table, int **table_count, int i, int j, const char *symbol) {
    for (int k = 0; k < table_count[i][j]; k++) {
        if (strcmp(table[i][j][k], symbol) == 0)
            return 1;
    }
    return 0;
}

// Función CYK que asigna dinámicamente la tabla según el número de tokens (n).
// La tabla es de dimensiones n x n, y en cada celda se almacenan hasta MAX_SYMBOLS cadenas (cada una de 10 caracteres).
// Se libera toda la memoria al finalizar.
_Bool cykParse(char* w[], int n) {
    // Asignar dinámicamente la tabla (4D) y table_count (2D)
    char ****table = malloc(n * sizeof(char***));
    int **table_count = malloc(n * sizeof(int*));
    if (table == NULL || table_count == NULL) {
        perror("Error al asignar memoria para la tabla CYK");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        table[i] = malloc(n * sizeof(char**));
        table_count[i] = malloc(n * sizeof(int));
        if (table[i] == NULL || table_count[i] == NULL) {
            perror("Error al asignar memoria para tabla[i] o table_count[i]");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < n; j++) {
            // Inicializamos table_count en 0
            table_count[i][j] = 0;
            table[i][j] = malloc(MAX_SYMBOLS * sizeof(char *));
            if (table[i][j] == NULL) {
                perror("Error al asignar memoria para table[i][j]");
                exit(EXIT_FAILURE);
            }
            for (int k = 0; k < MAX_SYMBOLS; k++) {
                table[i][j][k] = malloc(10 * sizeof(char));
                if (table[i][j][k] == NULL) {
                    perror("Error al asignar memoria para table[i][j][k]");
                    exit(EXIT_FAILURE);
                }
                table[i][j][k][0] = '\0';
            }
        }
    }

    // Fase 1: Incluir reglas terminales en la diagonal.
    for (int j = 0; j < n; j++) {
        for (int r = 0; r < rule_count; r++) {
            if (rules[r].rhs_len == 1 && strcmp(rules[r].rhs[0], w[j]) == 0) {
                strcpy(table[j][j][ table_count[j][j]++ ], rules[r].lhs);
            }
        }
    }

    // Fase 2: Procesar reglas no terminales.
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                for (int r = 0; r < rule_count; r++) {
                    if (rules[r].rhs_len == 2) {
                        for (int a = 0; a < table_count[i][k]; a++) {
                            for (int b = 0; b < table_count[k+1][j]; b++) {
                                if (strcmp(table[i][k][a], rules[r].rhs[0]) == 0 &&
                                    strcmp(table[k+1][j][b], rules[r].rhs[1]) == 0) {
                                    if (!contains_dyn(table, table_count, i, j, rules[r].lhs)) {
                                        strcpy(table[i][j][ table_count[i][j]++ ], rules[r].lhs);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Verificar si el símbolo inicial "E" está en la celda (0, n-1).
    _Bool accepted = false;
    for (int i = 0; i < table_count[0][n-1]; i++) {
        if (strcmp(table[0][n-1][i], "E") == 0) {
            accepted = true;
            break;
        }
    }

    // Liberar la memoria asignada a la tabla CYK.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < MAX_SYMBOLS; k++) {
                free(table[i][j][k]);
            }
            free(table[i][j]);
        }
        free(table[i]);
        free(table_count[i]);
    }
    free(table);
    free(table_count);

    return accepted;
}

int main(int argc, char **argv) {
    // Definición de las reglas de la gramática.
    const char* r1[] = {"E", "DERECHASUMA"};         add_rule("E", 2, r1);
    const char* r2[] = {"T", "DERECHAMUL"};            add_rule("E", 2, r2);
    const char* r3[] = {"id"};                         add_rule("E", 1, r3);
    const char* r4[] = {"num"};                        add_rule("E", 1, r4);
    const char* r5[] = {"PARI", "PARENCIERRE"};         add_rule("E", 2, r5);
    const char* r6[] = {"OPSUMA", "T"};                  add_rule("DERECHASUMA", 2, r6);
    const char* r7[] = {"T", "DERECHAMUL"};              add_rule("T", 2, r7);
    const char* r8[] = {"OPMUL", "F"};                   add_rule("DERECHAMUL", 2, r8);
    add_rule("T", 1, r3);
    add_rule("T", 1, r4);
    add_rule("T", 2, r5);
    add_rule("F", 1, r3);
    add_rule("F", 1, r4);
    add_rule("F", 2, r5);
    const char* r15[] = {"E", "PARD"};                 add_rule("PARENCIERRE", 2, r15);
    const char* r16[] = {"*"};                         add_rule("OPMUL", 1, r16);
    const char* r17[] = {"/"};                         add_rule("OPMUL", 1, r17);
    const char* r18[] = {"+"};                         add_rule("OPSUMA", 1, r18);
    const char* r19[] = {"-"};                         add_rule("OPSUMA", 1, r19);
    const char* r20[] = {"("};                         add_rule("PARI", 1, r20);
    const char* r21[] = {")"};                         add_rule("PARD", 1, r21);

    FILE *file = stdin;
    if (!file) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Leer líneas del archivo usando getline.
    while ((read = getline(&line, &len, file)) != -1) {
        if (read > 0 && line[read-1] == '\n')
            line[read-1] = '\0';

        char **tokens;
        int tokenCount = tokenize(line, &tokens);

        if (!cykParse(tokens, tokenCount))
            printf("Cadena no aceptada\n");
        free(tokens);
    }
    free(line);
    fclose(file);
    return 0;
}
