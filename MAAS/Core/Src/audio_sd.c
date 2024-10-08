/*
 * audio_sd.c
 *
 *  Created on: Oct 7, 2024
 *      Author: David
 */
#include "audio_sd.h"
#include "stdio.h"
#include "fatfs.h"

static FRESULT sd_result;
static FATFS sdCard;
static FIL testFile;
void sd_card_init() {
	uint8_t file_name[] = "test.txt";
	uint8_t temp_number;
	uint8_t test_text[] = "Hola, esto es un texto de prueba.";
	// montando una tarjeta SD
	sd_result = f_mount(&sdCard,SDPath,1);
	if (sd_result != 0) {
		printf("Error montando la tarjeta SD: %d \n", sd_result);
		while(1);
	}
	else {
		printf("Tarjeta SD montada \n");
	}
	sd_result = f_open(&testFile, (void*) file_name, FA_WRITE|FA_CREATE_ALWAYS);
	if (sd_result != 0) {
		printf("Error creando un archivo: %d \n", sd_result);
		while(1);
	}
	else {
		printf("Archivo de prueba creado \n");
	}
	// escribiendo al archivo
	sd_result = f_write(&testFile, (void *) test_text, (UINT) sizeof(test_text), (UINT *) &temp_number);
	if (sd_result != 0) {
		printf("Error escribiendo al archivo: %d \n", sd_result);
		while(1);
	}
	else {
		printf("Contenido del archivo escrito: %d \n", temp_number);
	}
	f_close(&testFile);
}
