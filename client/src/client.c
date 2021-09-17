#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	log_info(logger, "Soy un log");

	config = iniciar_config();

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");

	//Loggear valor de config
	log_info(logger, "El valor de \"CLAVE\" es \"%s\"", valor);

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servidor
	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create(ARCHIVO_LOGS, PROGRAMA, VISIBILIDAD_EN_CONSOLA, NIVEL_MINIMO_DE_LOGS);
	if(nuevo_logger == NULL)
	{
		perror("No pude crear el logger\n");
		exit(1);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create(ARCHIVO_CONFIGURACION);
	if(nuevo_config == NULL)
	{
		perror("No pude crear el config\n");
		exit(2);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	// Acá la idea es que imprimas por el log lo que recibis de la consola.
	while(strcmp(leido, SALIDA) != 0)
	{
		log_info(logger, leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();

	leido = readline(">");
	while(strcmp(leido, SALIDA) != 0)
	{
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
		leido = readline(">");
	}

	free(leido);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	if (logger != NULL)
		log_destroy(logger);
	else
		printf("El logger que se quiere cerrar no es valido");

	if (config != NULL)
		config_destroy(config);
	else
		printf("El config que se quiere cerrar no es valido");

	liberar_conexion(conexion);
}
