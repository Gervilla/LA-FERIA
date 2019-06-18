#include <mainboard.h>
#use delay (clock=44MHz)

#define FORWARD 0
#define RIGHT_FORWARD 1
#define LEFT_FORWARD 2
#define BACK 3
#define RIGHT_BACK 4
#define LEFT_BACK 5
#define STOP 7

int aux = 0;
int vel = 128;
int move= STOP;

/**
 * Método que ejecuta los movimientos necesarios antes de
 * luchar
 */
void prepare_to_fight()
{
   move = BACK;

   while(IN3 && IN4){}

   if (!IN4)
      move = LEFT_BACK;
   else
      move = RIGHT_BACK;
   
   while(IN3 || IN4){}
   
   move = FORWARD;
   delay_ms(750);
   move = STOP;
}

/**
 * Método que ejcuta los movimientos para esquivar al
 * atacante cuando este ataca a uno de los dos lados
 */
void dodge()
{
   vel = 250;

   if(IN1 && !IN2)
   {
      move = LEFT_BACK;
   }
   else if(IN2 && !IN1)
   {
      move = RIGHT_BACK;
   }

   delay_ms(250);
}

/**
 * Método que ejecuta los movimientos cuando el robot quiere
 * atacar
 */
void fight()
{
   vel = 250;
   move = FORWARD;
}

/**
 * TIMER0. Aquí realizamos los movimientos, que además tienen
 * la potencia controlada
 */
#INT_TIMER0
void int_tmr0()
{
   set_timer0(0);

   if(aux <= vel)
   {
      switch (move)
      {
         case FORWARD:
            M1_H();
            M2_H();
            M3_H();
            M4_H();
            break;

         case RIGHT_FORWARD:
            M1_P();
            M2_P();
            M3_H();
            M4_H();
            break;

         case LEFT_FORWARD:
            M1_H();
            M2_H();
            M3_P();
            M4_P();
            break;
         
         case BACK:
            M1_A();
            M2_A();
            M3_A();
            M4_A();
            break;
         
         case RIGHT_BACK:
            M1_P();
            M2_P();
            M3_A();
            M4_A();
            break;

         case LEFT_BACK:
            M1_A();
            M2_A();
            M3_P();
            M4_P();
            break;

         case STOP:
            M1_P();
            M2_P();
            M3_P();
            M4_P();
      }
   }
   else
   {
      M1_P();
      M2_P();
      M3_P();
      M4_P();
   }

   aux++;
}

/**
 * Comportamiento principal del robot. Se debe de tener en cuenta
 * los distintos métodos que aparecen antes de este
 */
void main()
{
   setup_timer_0(RTCC_INTERNAL | RTCC_8_BIT);

   set_timer0(0);

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   while(!IN1 && !IN2){}
   delay_ms(3000);

   prepare_to_fight();

   while(TRUE)
   {
      move = STOP;

      while(!IN1 && !IN2){}
      
      delay_ms(250);

      if((!IN1 && IN2)||(!IN2 && IN1)) 
      {
         dodge();
         vel = 128;
      }
      else if(IN1 && IN2)
      {
         fight();
         while(IN1 || IN2){}
         vel = 128;
         prepare_to_fight();
      }
   }
}
