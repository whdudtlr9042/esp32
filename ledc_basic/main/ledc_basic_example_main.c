/* LEDC (LED Controller) basic example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <unistd.h>

#include "driver/ledc.h"
#include "esp_err.h"

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_TIMER2             LEDC_TIMER_1
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_MODE2              LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_OUTPUT_IO2         (8) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_CHANNEL2           LEDC_CHANNEL_1
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY25               (2048) // Set duty to 25%. (2 ** 13) * 25% = 2048
#define LEDC_DUTY50               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_DUTY75               (6144) // Set duty to 75%. (2 ** 13) * 75% = 6144
#define LEDC_FREQUENCY            (4000) // Frequency in Hertz. Set frequency at 4 kHz
#define LEDC_FREQUENCY4K          (4000) // Frequency in Hertz. Set frequency at 4 kHz
#define LEDC_FREQUENCY6K          (6000) // Frequency in Hertz. Set frequency at 6 kHz
#define LEDC_FREQUENCY6K          (8000) // Frequency in Hertz. Set frequency at 8 kHz
/*

#define LEDC_DUTY2               (512)
#define LEDC_FREQUENCY2          (100)

*/
/* Warning:
 * For ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C2, ESP32C6, ESP32H2, ESP32P4 targets,
 * when LEDC_DUTY_RES selects the maximum duty resolution (i.e. value equal to SOC_LEDC_TIMER_BIT_WIDTH),
 * 100% duty cycle is not reachable (duty cannot be set to (2 ** SOC_LEDC_TIMER_BIT_WIDTH)).
 */

static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    /* ★ 다른 핀에도 출력 시키기  */
    /* ledc_timer_config_t ledc_timer2 = {
		.speed_mode       = LEDC_MODE,
		.duty_resolution  = LEDC_DUTY_RES,
		.timer_num        = LEDC_TIMER,
		.freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
		.clk_cfg          = LEDC_AUTO_CLK
   };
     ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer2));

       ledc_channel_config_t ledc_channel2 = {
    	        .speed_mode     = LEDC_MODE,
    	        .channel        = LEDC_CHANNEL,
    	        .timer_sel      = LEDC_TIMER,
    	        .intr_type      = LEDC_INTR_DISABLE,
    	        .gpio_num       = LEDC_OUTPUT_IO2,
    	        .duty           = 0, // Set duty to 0%
    	        .hpoint         = 0
       };
      ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel2));*/
}

void app_main(void)
{
	/*
	 * basic source
	 */
	/*
	// Set the LEDC peripheral configuration
	example_ledc_init();
	// Set duty to 50%
	ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
	// Update duty to apply the new value
	ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
	 */

	////////////////////////////////////////////////////////////////////////////////////

	// Set the LEDC peripheral configuration
	example_ledc_init();


	// ★ duty 값 변경, 로직 순서상 마지막 50% 가 적용됨.

    // Set duty to 25%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY25));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    // Set duty to 50%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY50));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));


    // ★ duty set and update - Fail, duty 적용안됨. 다른 Task 일때 사용하는 함수로 보이는데 ....
    //esp_err_t ledc_set_duty_and_update(ledc_mode_t speed_mode, ledc_channel_t channel, uint32_t duty, uint32_t hpoint)
	// These APIs can be called from different tasks.
	//ESP_ERROR_CHECK(ledc_set_duty_and_update(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY75, 0));


    //★ 주파수 4K 셋 //ledc_set_freq(ledc_mode_t speed_mode, ledc_timer_t timer_num, uint32_t freq_hz)
    //ESP_ERROR_CHECK(ledc_set_freq(LEDC_MODE, LEDC_TIMER, LEDC_FREQUENCY4K));


   /* ★ 반복문으로 duty 조절
    while(1){
    	sleep(1);
		// Set duty to 75%
		ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY25));
		// Update duty to apply the new value
		ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
		sleep(1);
		// Set duty to 75%
		ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY75));
		// Update duty to apply the new value
		ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));

    }*/



    /* 2 */
    // Set duty to 50%
    /*
   ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE2, LEDC_CHANNEL2, LEDC_DUTY2));
   ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE2, LEDC_CHANNEL2));
*/


}
