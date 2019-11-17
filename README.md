# EjercicioC
Repositorio para el ejercicio de C del TP3
## Consigna
Como el proceso de consulta del maestro de artículos funcionó tan bien y fue un éxito, se decide que también se quiere publicar el mismo como un servicio por red. Se debe crear un proceso demonio que abra un puerto TCP (indicado por parámetro o configuración), a donde se conectarán los clientes que le envíen las consultas de los artículos. El servidor debe ser capaz de atender más de una conexión de cliente a la vez. 
Los clientes deben leer las consultas en forma interactiva por estándar input, mostrando el resultado por estándar output. Las consultas se ingresan con el mismo formato que en los ejercicios anteriores, de a una por vez y al apretar enter se envían al servidor; y a continuación se debe imprimir el resultado. El cliente finaliza al ingresar la palabra QUIT en vez de una consulta.
### Criterios de corrección 
                Control                                                             Criticidad
Compila sin errores con el makefile entregado                                       Obligatorio
Funciona correctamente según enunciado                                              Obligatorio
Existe algún tipo de ayuda para la ejecución del proceso                            Obligatorio
Valida correctamente los parámetros                                                 Obligatorio
Acepta correctamente paths absolutos y relativos                                    Obligatorio
No se aceptan soluciones que utilicen system() o popen()                            Obligatorio
Cierra o destruye correctamente los recursos abiertos al finalizar los procesos     Obligatorio
Se conecta por red desde distintos hosts (máquinas)                                 Obligatorio
Soporta múltiples clientes (se probará con más de 3)                                Obligatorio
Generan correctamente el proceso demonio                                            Obligatorio
Maneja correctamente el cierre de los puertos al finalizar                          Deseable
Tiene archivo de configuración (deben entregarlo)                                   Deseable
Se conecta con nombre de máquinas                                                   Deseable
