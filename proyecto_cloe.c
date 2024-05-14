#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <unistd.h>

#define TRIG_PIN 6 //GPIO6 = WPI22
#define ECHO_PIN 5 //GPIO5 = WPI21

#define servo_pin_upper_leg_left 17
#define servo_pin_lower_leg_left 22
#define servo_pin_lower_leg_right 23
#define servo_pin_upper_leg_right 18

#define SOUND_SPEED 34300
#define NUM_SAMPLES 10
#define MIN_ANGLE -90
#define MAX_ANGLE 90
#define MIN_PULSE_WIDTH 1000 // Anchura de pulso mínima en microsegundos
#define MAX_PULSE_WIDTH 2000 // Anchura de pulso máxima en microsegundos

void setup();
double get_distance(); 
void move_servo(int servo_pin, int angle);
void turn();
void move();

void setup() {
    if(gpioInitialise() < 0) {
		printf("Failed to initialize");
		exit(1);
	}
    
    gpioSetMode(TRIG_PIN, PI_OUTPUT);
    gpioSetMode(ECHO_PIN, PI_INPUT);
    gpioSetMode(servo_pin_upper_leg_left, PI_OUTPUT);
    gpioSetMode(servo_pin_lower_leg_left, PI_OUTPUT);
    gpioSetMode(servo_pin_lower_leg_right, PI_OUTPUT);
    gpioSetMode(servo_pin_upper_leg_right, PI_OUTPUT);
    gpioWrite(TRIG_PIN, PI_LOW);
}

double get_distance() {
    struct timespec pulse_start, pulse_end;
    
    gpioWrite(TRIG_PIN, PI_HIGH);
    usleep(10);
    gpioWrite(TRIG_PIN, PI_LOW);

    while (gpioRead(ECHO_PIN) == 0);
    clock_gettime(CLOCK_REALTIME, &pulse_start);
    
    while (gpioRead(ECHO_PIN) == 1);
    clock_gettime(CLOCK_REALTIME, &pulse_end);

    double pulse_duration = (pulse_end.tv_sec - pulse_start.tv_sec)* 1e9;
    pulse_duration += pulse_end.tv_nsec - pulse_start.tv_nsec;
    double distance = (pulse_duration * 0.0343 / 2) / 1000;

    return distance;
}

void move_servo(int servo_pin, int angle) {
    double duty;

    // Asegurar que el ángulo está dentro del rango permitido
    if (angle < MIN_ANGLE) {
        angle = MIN_ANGLE;
    } else if (angle > MAX_ANGLE) {
        angle = MAX_ANGLE;
    }

    // Convertir el ángulo al rango de pulsos del servo
    duty = (angle + 45) * ((MAX_PULSE_WIDTH - MIN_PULSE_WIDTH) / 180.0) + MIN_PULSE_WIDTH;

    // Iniciar el daemon pigpio
    if (gpioInitialise() < 0) {
        fprintf(stderr, "Error al inicializar pigpio\n");
        return;
    }

    // Mover el servo al ángulo especificado
    gpioSetMode(servo_pin, PI_OUTPUT);
    gpioServo(servo_pin, (int)duty); // Pigpio espera el valor en microsegundos
    usleep(300000); // Esperar 0.5 segundos
    gpioServo(servo_pin, 0); // Detener el servo
    //gpioTerminate(); // Terminar el daemon pigpio
}

void turn() {
	
    move_servo(servo_pin_lower_leg_left, -45);
	move_servo(servo_pin_upper_leg_left,90);
	move_servo(servo_pin_lower_leg_left, -90);
	move_servo(servo_pin_upper_leg_left,0);
}

void move() {
	// Movimiento de la pierna izquierda hacia adelante
	move_servo(servo_pin_lower_leg_left, -45);
	move_servo(servo_pin_upper_leg_left,90);
	move_servo(servo_pin_lower_leg_left, -90);
	move_servo(servo_pin_upper_leg_left,0);
	
	// Movimiento de la pierna derecha hacia adelante
	move_servo(servo_pin_lower_leg_right, 0);
	move_servo(servo_pin_upper_leg_right, 0);
	move_servo(servo_pin_lower_leg_right, 50);
	move_servo(servo_pin_upper_leg_right, 90);
}

int main() {
	
    setup();
    while (1) {
        float dist = get_distance();
        printf("Distancia: %.2f cm\n", dist);
        //usleep(1000); // Tiempo de espera en milisegundos
        if (dist > 20 ){
			move();
		}
		else {
			turn();
		}

        
    }
    return 0;
}
