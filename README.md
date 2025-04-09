# 🧠Análisis Comparativo: CYK vs Bison

Este proyecto presenta un análisis comparativo entre el algoritmo **CYK (Cocke–Younger–Kasami)** y el generador de analizadores sintácticos **Bison**, aplicados sobre gramáticas en Forma Normal de Chomsky (**CNF**). El estudio incluye evaluación teórica y pruebas empíricas de rendimiento realizadas en un entorno controlado.

## 🧩Descripción

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
⚠️ Nota:Debe tener Homebrew instalado y simplemente ejecutar este comando.
```
brew install flex bison
```

## 📘Gramática en forma normal de Chomsky (CNF) para la comparación

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

# 🚀Ejecución de los analizadores

Ingresar a la carpeta la cual queremos realizar las pruebas.

## 🔹CYK
Utilizando MakeFile ejecutamos el siguiente comando para ejecutar la compilación:
```
make analizador
```
Luego ya generado el ejecutable realizamos el comando para su ejecución con las expresiones:
```
cat <archivo> | ./analizador
```
Si se requiere eliminar el ejecutable, con el siguiente comando:
```
make clean
```
⚠️ El algoritmo CYK fue implementado en C. Presenta un crecimiento cúbico (O(n^3)) por lo que manejar cadenas largas puede generar segmentación si no se optimiza la memoria.

## 🔹Bison
Utilizando MakeFile ejecutamos el siguiente comando para ejecutar y compilar:
```
make analizador
```
Luego ya generado el archivo ejecutable realizamos el comando para su ejecucion con las expresiones:
```
cat <archivo> | ./analizador
```
Si se requiere eliminar los archivos generados por flex y bison, con el siguiente comando:
```
make clean
```
✅ Bison es eficiente incluso para cadenas largas, mostrando un comportamiento más lineal en tiempo de ejecución.

# 📉 Gráficas de comparación

## 🔹CYK
![image](https://github.com/user-attachments/assets/c4f41c46-0f7a-4e4b-a1a3-531d22ee3f6f)

## 🔹Bison
![image](https://github.com/user-attachments/assets/d10221cf-2d00-45f8-b010-1e44408d4968)

# 💬Conclusiones:
- Bison muestra un rendimiento superior en comparación con CYK, especialmente a medida que aumenta la cantidad de expresiones. Mientras que CYK presenta un crecimiento exponencial en el tiempo de ejecución, lo que lo hace menos escalable frente a Bison, cuyo comportamiento es más lineal.
- La variabilidad de los tiempos también es menor en Bison, indicando mayor estabilidad en sus ejecuciones. Estos resultados sugieren que Bison es más adecuado para aplicaciones donde se requiere analizar grandes volúmenes de expresiones de forma rápida y consistente.
- Además, los datos teóricos sobre la complejidad de cada algoritmo se ven reflejados empíricamente en sus respectivas gráficas de rendimiento. En el caso de Bison, se observa un comportamiento lineal, coherente con su enfoque optimizado de análisis descendente. Por otro lado, el algoritmo CYK presenta una curva cúbica, lo cual es consistente con su complejidad teórica de orden O(n³). Esta diferencia evidencia que, aunque CYK garantiza análisis sintáctico para cualquier gramática en CNF, su costo computacional es significativamente mayor frente a soluciones especializadas como Bison.
