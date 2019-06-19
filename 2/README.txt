Tarea 2 - Daniel San Martín

1. COMPILACION:
------------------
Realizar make adentro de la carpeta.

2. EJECUCION:
------------------
2.1 Problema 1

./tarea2 alg < input_file
* alg: 0 o 1. 0 Para el algoritmo fuerza bruta y 1 para el algoritmo propuesto.
* input_file: ruta del archivo de entrada.

2.2 Problema 2

./insertion OPT N
* OPT: Version del algoritmo
* N: Tamaño del arreglo a ordenar.

3. COMPARACION:
-----------------
3.1 Problema 1

./benchmark.sh alg
* alg: 0 o 1. 0 Para el algoritmo fuerza bruta y 1 para el algoritmo propuesto.

Para guardar los tiempos realizar el comando
./benchmark.sh alg &> file_name

3.2 Problema 2

./benchmark_insertion.sh version
* Version: 0 o 1. Version del algoritmo.

4. GRAFICO:
-----------------
python plot.py file_alg_1 file_alg_2
* file_alg_n: Ruta del archivo de tiempos para cada algoritmo (obtenido de la parte 3.)


