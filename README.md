# 🧠 Análisis Comparativo: CYK vs Bison

Este proyecto presenta un análisis comparativo entre el algoritmo **CYK (Cocke–Younger–Kasami)** y el generador de analizadores sintácticos **Bison**, aplicados sobre gramáticas en Forma Normal de Chomsky (**CNF**). El estudio incluye evaluación teórica y pruebas empíricas de rendimiento realizadas en un entorno controlado.

## 🧩 Descripción

Se comparan dos enfoques de análisis sintáctico:
- **CYK**: Algoritmo basado en programación dinámica para gramáticas en CNF. Complejidad teórica: `O(n^3)`.
- **Bison**: Generador de analizadores sintácticos que permite crear parsers eficientes con enfoque descendente.

## ⚙️ Requisitos

- Para compilar y ejecutar este proyecto localmente necesitas:

- Sistema operativo basado en UNIX (Linux/MacOS).

- Compilador GCC (gcc).

- Herramientas de análisis léxico/sintáctico: flex,bison

Puedes instalar estas herramientas en sistemas con los siguiente comando:

# Para Linux:
```
sudo apt update
sudo apt install build-essential flex bison
```
# Para MacOS:

```
brew install flex bison
```
⚠️ Nota:Si ya tienes Homebrew instalado, simplemente ejecuta los anteriores comandos.

## 📘 Gramática en forma normal de Chomsky (CNF) para la comparación

```
OPMUL -> * | /
OPSUMA -> + | -
PARI -> (
PARD -> )

E -> E DERECHASUMA | T DERECHAMUL | id | num | PARI PARENCIERRE
DERECHASUMA -> OPSUMA T
T -> T DERECHAMUL
DERECHAMUL -> OPMUL F

T -> id | num | PARI PARENCIERRE
F -> id | num | PARI PARENCIERRE

PARENCIERRE -> E PARD
```

# 🚀 Ejecución de los analizadores

🔹 CYK

⚠️ Nota: El algoritmo CYK fue implementado en C. Presenta un crecimiento cúbico (O(n^3)) por lo que manejar cadenas largas puede generar segmentación si no se optimiza la memoria.

🔹 Bison

✅ Bison es eficiente incluso para cadenas largas, mostrando un comportamiento más lineal en tiempo de ejecución.

# 📉 Gráficas de comparación


