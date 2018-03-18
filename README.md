# PDDL simulation
Prácticas para integración de planificación PDDL con simulación robótica

## Ejecución del planificación
1. En el terminal, cambiar el directorio de trabajo a la raíz del proyecto
2. Si no estaba hecho, compilar el proyecto ejecutando ``make''
3. Lanzar el simulador: ``roslaunch launch/rooms.launch''
4. En otro terminal (o pestaña), lanzar el ejecutor desde la raíz del proyecto: ``./bin/launch_sim.sh''

Existe un segundo archivo launch (`teleop.launch`) para la teleoperación del robot, útil para depuración.

## Descripción de la librería de manejo del planificador

Para poder llevar a cabo la ejecución, lectura y modificación del entorno modelado en PDDL y del planificador encargado de resolver los problemas, se ha desarrollado una librería en C++ que permite manejar estos elementos de forma genérica. Esta librería esta compuesta por una seríe de clases cuyas funciones se exponen a continuación:
* CPDDLstruct: este archivo definirá las estructuras de datos necesarias para almacenar información de predicados, funciones y acciones de los archivos PDDL.
* CDominio: esta clase permite almacenar y acceder a un vector con la información de las acciones de que consta el dominio. El formato de las acciones contiene los datos necesarios para informar a las clases hijas de los aspectos relativos al formateo de salida del planificador.
* CProblema: permite insertar o modificar estados iniciales, funciones o metas del problema PDDL empleado para la planificación. Para ello el archivo debe tener una única linea por predicado sin espacios antes ni después del mismo. Actualmente no se permite insertar o modificar los objetos, por tanto no se podrán hacer modificaciones que incluyan nuevos objetos o la planificación fallará.
* CPlan: esta clase permite leer el plan generado por el planificador a partir del archivo en que haya sido guardado. Para ello requiere conocer el formato de salida de las ordenes y la ruta al archivo. Proveerá de la información relevante de la acción, esto es, nombre y objetos involucrados en la misma.
* Planner: permite instanciar un planificador PDDL genérico y ejecutarlo de forma correcta mediante los datos contenidos en un fichero de configuración. Permite la lectura del plan obtenido por éste y la modificación del archivo de problema. El formato definido para el archivo de configuración del planificador es el que se explica a continuación y el cual será necesario modificar para adpatarlo al dominio creado por el alumno.


## Archivo de configuración del planificador

Para manejar el planificador PDDL deberá haber un archivo de configuración que defina tanto el programa planificador, como los archivos de dominio y problema PDDL empleados. Además será importante indicar como es el formato de salida de las acciones entregadas por el planificador de cara a poder *entender* el plan obtenido. Debido a esto, para que un planificador sea utilizable mediante la librería PDDL debe cumplir unos mínimos aspectos de formato en la salida del plan generado, siendo fundamental que pueda guardar el plan obtenido en un archivo, y, que dentro del archivo cada acción del plan ocupe una única línea, así como algunos aspectos menores que se verán a continuación. El formato del archivo de configuración es estático y debe seguir el orden que se expondrá, pudiendo incluirse líneas de comentarios iniciando la línea con el carácter '%'. El contenido de cada línea variará en función del planificador empleado y el significado de cada líneas es el siguiente:

1. Ruta (total o relativa) al archivo ejecutable del planificador.
2. Parámetro empleado por el planificador elegido para indicar el archivo de dominio PDDL a emplear.
3. Ruta al archivo de dominio PDDL deseado.
4. Parámetro empleado por el planificador para designar el archivo del problema PDDL a resolver.
5. Parámetro del planificador para indicar en que archivo se volcará el plan generado.
6. Ruta al archivo en que se vuelca el plan obtenido por el planificador.
7. Cadena de texto que precede a la lista de acciones del plan. Dicha cadena no tiene necesariamente que ser la cadena completa (algunos planificadores multihilo modifican esta cadena para indicar que hilo encontró la solución), pero si debe ser suficiente para reconocer el inicio de las acciones de manera unequivoca. Además deberá haber una línea sin información útil entre esta cadena y la primera acción del plan.
8. Esta línea corresponde a una cadena de la forma `ACCIONES# *num-acciones*`, donde *num-acciones* es el número de acciones de que consta el dominio de planificación.
9. A partir de esta línea se deberán incluir *num-acciones* líneas que definan las acciones del dominio y el formato en que las presenta el planificador. Se deberá incluir una línea por acción con los siguientes campos separados por un espacio:
    1. Nombre de la acción en el dominio PDDL, distinguiéndose entre mayúsculas y minúsculas.
    2. Posición en la cual se encuentra el nombre de la acción. Esto responde a que cada planificador muestra la información de una forma diferente, por ello la librería al leer las acciones del archivo elimina todos los símbolos (salvo '-', '.' y '\_') y espacios. Con esta línea *limpia* y comenzando a contar en 1 se pueden extraer los elementos importantes de la acción.  
    3. Este parámetro indica el número de objetos de la acción indicada. Los objetos deberán ser una lista de elementos separados por espacios (o símbolos especiales) y encontrarse a continuación de la acción.
    4. Aquí debe indicarse la posición donde se encuentra la duración de la acción. La duración puede encontrarse tanto antes del nombre de la acción como después.
    5. Finalmente se encuentra una cadena de texto sin espacios que puede proporcionar información extra de la acción y que puede ser leída durante la ejecución.

A continuación se muestra un ejemplo para clarificar la línea de formato de las acciones:

```
Salida del planificador: 21.004: (GIRAR ESTE SUR) [3.0000]
Linea "limpia"         : 21.004 GIRAR ESTE SUR 3.0000
Posiciones             :   1      2    3    4     5
Línea de configuración : GIRAR 2 2 5 informacion-extra
```

El archivo que se encuentra en `bin/pddlconfig` puede ser usado como base para utilizar en el desarrollo de la práctica.

# Dependencias
Paquetes ROS que deben estar instalados:

* stdr_simulator
* stdr_resources
* stdr_gui
* stdr_robot

Si tienes algún problema cargando el robot, intenta actualizar el sistema (`apt-get update && apt-get upgrade`).
