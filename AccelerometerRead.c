#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"

/*The function to read from the accelerometer
	The accelerometer should be configured first!
	See GPIOConfig.c Accel_Config() for more details
*/

static int16_t x_raw, y_raw, z_raw;
static int16_t values[3];

int16_t* Accelerometer_Read(void)
{
	
	uint8_t Buffer[6];
	
	LIS3DSH_Read(&Buffer[0], LIS3DSH_OUT_X_L, 1);
	LIS3DSH_Read(&Buffer[1], LIS3DSH_OUT_X_H, 1);
	LIS3DSH_Read(&Buffer[2], LIS3DSH_OUT_Y_L, 1);
	LIS3DSH_Read(&Buffer[3], LIS3DSH_OUT_Y_H, 1);
	LIS3DSH_Read(&Buffer[4], LIS3DSH_OUT_Z_L, 1);
	LIS3DSH_Read(&Buffer[5], LIS3DSH_OUT_Z_H, 1);
	
	x_raw = Buffer[0] + (int16_t)(Buffer[1] << 8);
	y_raw = Buffer[2] + (int16_t)(Buffer[3] << 8);
	z_raw = Buffer[4] + (int16_t)(Buffer[5] << 8);
	
	values[0] = x_raw;
	values[1] = y_raw;
	values[2] = z_raw;
	
	return values;
}