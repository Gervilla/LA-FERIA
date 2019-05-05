#include <mainboard.h>

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

void go_forward()
{
   M1_H();
   M2_H();
   M3_H();
   M4_H();
}

void go_back()
{
   M1_A();
   M2_A();
   M3_A();
   M4_A();
}

void turn_left()
{
   M1_H();
   M2_A();
   M3_H();
   M4_A();
}

void turn_right()
{
   M1_A();
   M2_H();
   M3_A();
   M4_H();
}

void stop()
{
   M1_P();
   M2_P();
   M3_P();
   M4_P();
}

void prepare_to_fight()
{
   go_back();

   while(!IN3 && !IN4){}

   if (IN3)
   {
      turn_right();
   }
   else
   {
      turn_left();
   }
   
   while(!IN3 || !IN4){}
   
   go_forward();
   //TODO: Añadir un delay de segundo y medio
   stop();
}

void avoid_left()
{

}

void avoid_right()
{

}

void fight_on()
{

}

void main()
{
   //TODO: Añadir un delay de 3 segundos.
   
   int time;

   prepare_to_fight();

   while(TRUE)
   {
      while(!IN1 && !IN2 && time < 1000000000/*FIXME: Valor correspondiente a minuto y medio*/)
         time += 10; // FIXME: Cambiar por un valor que corresponda al tiempo que ha pasado
                  // desde la última vez que ha pasado el bucle.
      
      if(IN1 || IN2)
      {
         //TODO: Arreglar la potencia para que sea la máxima.
         //TODO: Delay de 500 ms.
         prepare_to_fight();
      }
      else
      {
         //TODO: Arreglar la potencia para que sea reducida.
         go_forward();
      }
   }
}
