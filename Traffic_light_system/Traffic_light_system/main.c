/*
 * Traffic_light_system.c
 *
 * Created: 9/26/2022 8:18:27 AM
 * Author : hp
 */ 


#include "APPLICATION/APP.h"

int main(void)
{
	/*NOTE : there are warning for all LCD function used as implicit declaration and I don't know reason but it work */
	/*another NOTE : function handle mostly every thing so that not return ok or not ok and I don't find reason make it return not ok*/
	APP_init();
	APP_start();

}
