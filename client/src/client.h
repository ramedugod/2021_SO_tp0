#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "utils.h"

#define ARCHIVO_LOGS "tp0.log"
#define PROGRAMA "client"
#define VISIBILIDAD_EN_CONSOLA 1
#define NIVEL_MINIMO_DE_LOGS LOG_LEVEL_INFO
#define ARCHIVO_CONFIGURACION "tp0.config"
#define SALIDA ""

t_log* iniciar_logger(void);
t_config* iniciar_config(void);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif /* CLIENT_H_ */

