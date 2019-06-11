Tarea 2 - Daniel San Martín

1. COMPILACION:
------------------
Realizar make dentro de la carpeta.

2. EJECUCION:
------------------
./tarea2 alg < input_file
* alg: 0 o 1. 0 Para el algoritmo fuerza bruta y 1 para el algoritmo propuesto.
* input_file: ruta del archivo de entrada.

3. COMPARACION:
-----------------
./benchmark.sh alg
* alg: 0 o 1. 0 Para el algoritmo fuerza bruta y 1 para el algoritmo propuesto.

Para guardar los tiempos realizar el comando
./benchmark.sh alg &> file_name

4. GRAFICO:
-----------------
python plot.py file_alg_1 file_alg_2
* file_alg_n: Ruta del archivo de tiempos para cada algoritmo (obtenido de la parte 3.)


