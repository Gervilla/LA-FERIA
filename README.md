<H1>LA FERIA</H1>



Codigo C de nuestro robot de combate para la asignatura de sistemas con microprocesadores.

El codigo esta hecho para funcionar en una placa de diseño personalizado por la universidad de Granada, compilado usando el programa CCS.

<H2>Estrategia de combate</H2>

El robot al activarse, retrocede buscando el borde de la arena, cuando lo encuentra avanza unos centimetros y ahi se para.
Permanece inmovil hata que el robot del oponente choca contra el:
Si choca por uno de los dos laterales, retrocede un poco por ese lateral, intentado siempre tenerlo de frente.
Si choca de frente, el robot avanzara recto hasta echar al contrincante de la arena.

Esto funciona ya que el frontal de nuestro robot posee una plancha metalica del mismo color que la arena, por tanto los contrincantes se subiran en dicha plataforma haciendo que unicamente tengan traccion con las ruedas traseras ya que las delanteras estan "encima" de nuestro robot, haciendo imposible que puedan hacerlo retroceder.
