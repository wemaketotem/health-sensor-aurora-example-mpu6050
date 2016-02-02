#include "mbed.h"
#include "MPU6050.h"
 
DigitalOut debugLed(P0_21);
Serial pc(USBTX, USBRX);

MPU6050 mpu(MPU6050_ADDRESS_AD0_HIGH);
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
volatile bool new_data=false;

int main()
{     
    mpu.reset();
    wait(0.2);
    
    pc.printf("MPU6050 test\n\n");
    pc.printf("MPU6050 initialize \n");
 
    mpu.initialize();
    wait(0.2);
    pc.printf("MPU6050 testConnection \n");
 
    bool mpu6050TestResult = mpu.testConnection();
    
    if(!mpu6050TestResult)
    {
        pc.printf("Could not start MPU");
        while(1){
            debugLed = 1;
            wait(0.2);
            debugLed = 0;
            wait(0.2);
            pc.printf("Herstart Totem Healt Patch");
        }
    } else 
    
    pc.printf("MPU Started\r\n");
    
    while(1) {
        wait(1);
      
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);                           //haal de acc en gyro data op

        pc.printf("Address: %d", &ax);
        
        pc.printf("%d;%d;%d;%d;%d;%d\n\r",ax,ay,az,gx,gy,gz);                   //schrijf data weg over de uart
        
    }
}
