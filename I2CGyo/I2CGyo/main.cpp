#include <cstdio>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>


int main()
{
    //user variables
    int fileDescriptor = 0;
    int returnValue = 0;


    //open GY-521 i2c device in R/W mode
    fileDescriptor = open("/dev/i2c-1", O_RDWR);

    if (fileDescriptor < 0)
    {
        printf("Could not open I2C device on Linux \n");
        return -1;
    }
    else
    {
        printf("I2C Device opened in R/W mode \n");
    }

    // I2C_SLAVE defined in <linux/i2c-dev.h>
    //ioctl() defined in <sys/ioctl.h>, input output control API
    returnValue = ioctl(fileDescriptor, I2C_SLAVE, 0x68); //0x68 is MPU6050 device address
    returnValue < 0 ? printf("Could not find MPU050\n") : printf("MPU6050 Found\n");

    
    // who_am_i register address of MPU6050 is 0x75
    unsigned char buffer[1] = { 0x75 };
    returnValue = write(fileDescriptor, (const void*)&buffer, 1U); //write address to MPU6050
    if (returnValue < 0) printf("Could not write into I2C device\n");

    //Read value from 0x75 who_am_i register
    returnValue = read(fileDescriptor, (void*)&buffer, 1U);
    returnValue < 0 ? printf("Could not read from I2C device\n") : printf("Retrieved value from who_am_i register was 0x%x \n", buffer[0]);
   
    
    //Turn MPU6050 on by writing to 0x68 register
    unsigned char powerBuffer[2] = {0x68, 0x00};
    returnValue = write(fileDescriptor, (const void*)&powerBuffer, 2U);
    returnValue < 0 ? printf("Could not write to I2C device\n") : printf("Wrote 0x00 to power management register\n");
    

    //Acceler + thermo + gyro register begin at 0x38
    unsigned char adr[1] = { 0x3B };
    unsigned char values[14] = { 0 };
   
    //while (1) {
        //Read x accelerometer registers
        returnValue = write(fileDescriptor, (const void*)&adr, 1U);

        returnValue = read(fileDescriptor, (void*)&values, 14U);

        if (returnValue < 0)
        {
            printf("Could not read from I2C device\n");
        }
        else
        {
            printf("X Accel: %d, Y Accel:%d, Z Accel:%d \n", (values[0] << 8) | values[1], (values[2] << 8) | values[3], (values[4] << 8) | values[5]);
        }
   // }
    
    return 0;
}