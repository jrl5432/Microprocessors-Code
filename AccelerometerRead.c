#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"
#include <math.h>

/*The function to read from the accelerometer
	The accelerometer should be configured first!
	See Accel_Config.c Accel_Config() for more details
	
	No inputs required
	Returns an array containing the raw x, raw y and raw z values
	
*/

static int16_t x_raw, y_raw, z_raw;
static int16_t values[3];

float ACC11, ACC21, ACC31, ACC12, ACC22, ACC32, ACC13, ACC23, ACC33, ACC10, ACC20, ACC30;
float normalized[3];
float rotations[3];

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


/*A function that calculates the normalized valuesof the raw sensor data
takes in an array of 3 floats that are the axes measurements
x = index 0, y = index 1, z = index 2
returns a array of 3 values containing the normalized results
*/

float* normalize(int16_t* vals)
{
	ACC11 = 0.993;
	ACC21 = 0.003;
	ACC31 = -0.017;
	
	ACC12 = -0.037;
	ACC22 = 0.981;
	ACC32 = -0.0392;
	
	ACC13 =0.110;
	ACC23 =0.096;
	ACC33 = 1.023;
	
	ACC10 = 105.634;
	ACC20 = 242.354;
	ACC30 = 1780.432;
	
	normalized[0] = vals[0]*ACC11 + vals[1]*ACC12 + vals[3]*ACC13 + ACC10;
	normalized[1] = vals[0]*ACC21 + vals[1]*ACC22 + vals[3]*ACC23 + ACC20;
	normalized[2] = vals[0]*ACC31 + vals[1]*ACC32 + vals[3]*ACC33 + ACC30;
	
	return normalized;
}

/*takes in 3 axes values
returns the angles of pitch (index 0), roll (index 1) and yaw (index 2)
the return is an array with the three values
*/
float* accelerometer_calculate_rotation(float x, float y, float z) {
	
	//pitch:
	if (y != 0 && z != 0) {
		rotations[0] = (180.0/3.1415)*(atan(x / sqrt(y*y + z*z)));
	}
	
	//roll
	if (x != 0 && z != 0) {
		rotations[1] = (180.0/3.1415)*(atan(y / sqrt(x*x + z*z)));
	}
	//yaw
	if (x != 0 && y != 0) {
		rotations[2] = (180.0/3.1415)*(atan(z / sqrt(x*x + y*y)));
	}
	
	return rotations;
}