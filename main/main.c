#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "../ecies/encrypt.h"
#include "display/oled.h"
#include "gatts/gatts.h"


void app_main(void)
{

	/* Do all used peripherals here */

	/* Init HW for the OLED */
	i2c_master_init();
	ssd1306_init();
//	xTaskCreate(&task_ssd1306_display_text, "ssd1306_display_text",  2048,
//			(void *)"Hello world!\nMulitine is OK!\nAnother line", 6, NULL);

	/* Call the bluetooth app function */
	gatts_main();
}

