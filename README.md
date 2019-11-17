# EjercicioC
Repositorio para el ejercicio de C del TP3
## Consigna
Como el proceso de consulta del maestro de artículos funcionó tan bien y fue un éxito, se decide que también se quiere publicar el mismo como un servicio por red. Se debe crear un proceso demonio que abra un puerto TCP (indicado por parámetro o configuración), a donde se conectarán los clientes que le envíen las consultas de los artículos. El servidor debe ser capaz de atender más de una conexión de cliente a la vez. 

Los clientes deben leer las consultas en forma interactiva por estándar input, mostrando el resultado por estándar output. Las consultas se ingresan con el mismo formato que en los ejercicios anteriores, de a una por vez y al apretar enter se envían al servidor; y a continuación se debe imprimir el resultado. El cliente finaliza al ingresar la palabra QUIT en vez de una consulta.
### Criterios de corrección 
  1. Compila sin errores con el makefile entregado
  2. Funciona correctamente según enunciado
  3. Existe algún tipo de ayuda para la ejecución del proceso
  4. Valida correctamente los parámetros
  5. Acepta correctamente paths absolutos y relativos
  6. No se aceptan soluciones que utilicen system() o popen()
  7. Cierra o destruye correctamente los recursos abiertos al finalizar los procesos
  8. Se conecta por red desde distintos hosts (máquinas)
  9. Soporta múltiples clientes (se probará con más de 3)
  10. Generan correctamente el proceso demonio
  11. Maneja correctamente el cierre de los puertos al finalizar
  12. Tiene archivo de configuración (deben entregarlo)
  13. Se conecta con nombre de máquina
