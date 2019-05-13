#include <mainboard.h>
#use delay (clock=44MHz)

/**
 * Primero, debemos de comprobar los dos sensores infrarrojos para encontrar la banda
 * negra más cercana a nuestra parte trasera. Esto se realizará  al inicio y cuando 
 * dejemos de detectar a un oponente durante 500 ms.
 * 
 * Aquí podemos entrar en varios estados. Si los bumpers detectan algo, el robot se 
 * moverá según que bumpers se han activado. Si lleva cerca de minuto y medio sin moverse
 * o sin detectar ningún enemigo, el robot avanzará a una potencia media o baja.
 * 
 * El tipo de movimiento según los bumpers será el siguiente:
 * 
 *    ·    Si se detecta por uno de los dos lados, el robot girará hacia atrás al lado detectado
 *       durante un corto periodo de tiempo o hasta cuando se detecte una línea negra, lo que 
 *       ocurra antes.
 * 
 *    ·    Si se detecta por ambos lados, significa que el oponente va de frente hacia nosotros,
 *       así que avanzaremos con toda nuestra potencia hacia delante.
 * 
 * Si se añaden más cuestiones y funcionalidades, se deben de añadir después del siguiente TODO.
 * 
 * TODO: 
 * 
 * Si se ven cosas que se deben de arreglar, se deben de añadir después del siguiente FIXME.
 * 
 * FIXME:
*/

//int aux = 0;
//int pwm = 128;
//unsigned int16 m = 0;
//int pulsador = 0;

#define FORWARD 0
#define RIGHT_FORWARD 1
#define LEFT_FORWARD 2
#define BACK 3
#define RIGHT_BACK 4
#define LEFT_BACK 5
#define STOP 7

float time = 0;

void move(int m)
{
   switch (m)
   {
      case FORWARD:
         M1_H();
         M2_H();
         M3_H();
         M4_H();
         break;

      case RIGHT_FORWARD:
         // FIXME: Cambiarlo para que corresponda a giro hacia la derecha con el lado derecho como pivote
         break;

      case LEFT_FORWARD:
         // FIXME: Cambiarlo para que corresponda a giro hacia la izquierda con el lado izquierdo como pivote
         break;
      
      case BACK:
         M1_A();
         M2_A();
         M3_A();
         M4_A();
         break;
      
      case RIGHT_BACK:
         // FIXME: Cambiarlo para que corresponda a giro hacia la derecha con el lado derecho como pivote
         break;

      case LEFT_BACK:
         // FIXME: Cambiarlo para que corresponda a giro hacia la izquierda con el lado izquierdo como pivote
         break;

      case STOP:
         M1_P();
         M2_P();
         M3_P();
         M4_P();
   }
}

void prepare_to_fight()
{
   move(BACK);

   while(!IN3 && !IN4){}

   if (IN3)
      move(LEFT_BACK);
   else
      move(RIGHT_BACK);
   
   while(!IN3 || !IN4){}
   
   move(FORWARD);
   delay_ms(750);
   move(STOP);
}

#INT_TIMER0
void int_tmr0()
{
   set_timer0(0);

   time+=1.5f;
}

void main()
{
   while(!IN1){}

   //TODO: Inicializar timer 0 para que cuando sobrepase se active un flag que haga que el robot vaya poco a poco hacia delante.
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);

   set_timer0(0);

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   delay_ms(3000);

   prepare_to_fight();

   while(TRUE)
   {
      while(!IN1 && !IN2 && time < 10){}
      
      delay_ms(500);

      if(IN1 || IN2)
      {
         //TODO: Arreglar la potencia para que sea la máxima.
         delay_ms(500);
         prepare_to_fight();
      }
      else if(time > 10)
      {
         //TODO: Arreglar la potencia para que sea reducida.
         move(FORWARD);
      }
   }
}
