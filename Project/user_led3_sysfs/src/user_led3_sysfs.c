/*
 ============================================================================
 Name        : user_led3_sysfs.c
 Author      : Charles Dias
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

/* This is the path corresponds to USER LEDS in the 'sys' directory */
#define SYS_FS_LEDS_PATH "/sys/class/leds"

/* This is the path corresponds to USER LED 3 in the 'sys' directory */
#define SYS_FS_USER_LED_3 "/sys/class/leds/beaglebone:green:usr3"

#define USR_LED_NUMBER 3
#define SOME_BYTES 100

/*This function writes the tigger values for the given "led_no"
 * returns 0 if success, else -1
 */
int write_trigger_values(uint8_t led_no, char *value)
{
	int fd,ret=0;
	char buf[SOME_BYTES];

	/* we are concatenating  2 strings and storing that in to 'buf'  */
	snprintf(buf,sizeof(buf),SYS_FS_LEDS_PATH "/beaglebone:green:usr%d/trigger",led_no);

	/* open the file in write mode */
	/*Returns the file descriptor for the new file. The file descriptor returned is always the smallest integer greater than zero that is still available. If a negative value is returned, then there was an error opening the file.*/
	fd = open(buf, O_WRONLY );
	if (fd <= 0) {
		perror(" write trigger error\n");
		return -1;
	}

	/* Write the 'value' in to the file designated by 'fd' */
	/*Returns the number of bytes that were written.
	  If value is negative, then the system call returned an error.
	*/
	ret = write(fd, (void*)value, strlen(value) );
	if ( ret <= 0)
	{
		printf("trigger value write error\n");
		return -1;
	}

	return 0;

}


int main( int argc, char *argv[] )
{
	unsigned char key;

	do
	{
		// Write the MENU options
		printf("####################################################\r\n");
		printf("Menu Control USER LED3\r\n\r\n");
		printf("Turn-off the LED 3 - press 0\r\n");
		printf("Turn-on  the LED 3 - press 1\r\n");
		printf("To exit            - press x\r\n");
		printf("####################################################\r\n");

		key = getchar();

		if(key == '0')
		{
			write_trigger_values(USR_LED_NUMBER, "none");
		}
		else if(key == '1')
		{
			write_trigger_values(USR_LED_NUMBER, "default-on");
		}

	}while(key != 'x');

    return 0;

}
