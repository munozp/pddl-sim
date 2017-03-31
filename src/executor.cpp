/**
    executor.cpp
    PDDL basic executive.

    @author Pablo Muñoz
    @version 30/03/17 
*/
#include <cstdlib>
#include <cstdio>
#include "Planner.h"

using namespace std;


/**
PDDL executive.
*/
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Bad arguments. The PDDL configuration file shall be provided as only argument.\n");
        return -1;
    }
    //Create PDDL planner and generate plan
    printf("Using %s file for PDDL configuration.\n",argv[1]);
    Planner planificador(argv[1]);    
    int ret=planificador.planificar();  
    if(ret==0)
    {
        int numaccion=1;
        float duracion=0;
        char* accion = new char[31];
        char* objetos = new char[TAM_LINEA/2];
        // Read and execute plan
        while(numaccion>0)
        {
            numaccion=planificador.sig_accion(accion,objetos,&duracion);
            printf("Next action: %s (duration: %01.2fs)\n",accion,duracion);
            // Select action behaviour
            if(!strcmp(accion,(char*)FINAL_PLAN))
            {
                printf("PLAN COMPLETED!\n");
            }
            // Beavhiour for MOVEMENT
            else if(!strncmp(accion,(char*)"move",4))
            {
                switch(accion[4])
                {
                    case 'n': // Move to north
                        printf("INCLUDE YOUR CODE TO MOVE NORTH\n");
                        break;
                    case 's': // Move to south
                        printf("INCLUDE YOUR CODE TO MOVE SOUTH\n");
                        break;
                    case 'e': // Move to east
                        printf("INCLUDE YOUR CODE TO MOVE EAST\n");
                        break;
                    case 'w': // Move to west
                        printf("INCLUDE YOUR CODE TO MOVE WEST\n");
                        break;
                    default: 
                        printf("Unknown movement action\n");
                }
            }
            else
            {
                // Other actions behaviours
                printf("Unrecongnized action\n");
            }
        }
    }
    else //PLANNING FAILURE!
    {
        switch(ret){
            case -1:printf("\nFALLO AL ABRIR ARCHIVO\n"); break;
            case -2:printf("\nFALLO AL BUSCAR PREDICADO/FUNCION\n"); break;
            case -11:printf("\nFALLO AL ABRIR EL ARCHIVO DE CONFIGURACION (dominio)\n"); break;
            case -12:printf("\nNO HAY ACCIONES EN EL ARCHIVO DE CONFIGURACION (dominio)\n"); break;
            case -13:printf("\nNUMERO DE ACCIONES LEIDAS INCORRECTO\n"); break;
            case -14:printf("\nPOSICION DEL VECTOR INCORRECTA O VECTOR VACIO\n"); break;
            case -21:printf("\nPLAN NO ABIERTO\n"); break;
            case -22:printf("\nPLAN SIN ACCIONES\n"); break;
            case -23:printf("\nACCION DESCONOCIDA EN EL PLAN\n"); break;
            case -31:printf("\nFALLO AL ABRIR EL ARCHIVO DE CONFIGURACION (planner)\n"); break;
            case -32:printf("\nNO SE HAN LEIDO TODOS LOS DATOS NECESARIOS PARA EL PLANIFICADOR\n"); break;
            case -33:printf("\nERROR AL CREAR EL PROCESO PARA EL PLANIFICADOR\n"); break;
            default: printf("\nFALLO EN EL SISTEMA DE ARCHIVOS, DEL PLANIFICADOR O ERROR DESCONOCIDO\n");
        }
        return -1;
    }

    return 0;
}
