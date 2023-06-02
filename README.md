## Índice
- [1. Spawn de enemigos](#1-spawn-de-enemigos)
	- [1.1. Helicópteros](#11-helicopteros)
	- [1.2. Soldados](#12-soldados)
- [2. Movimiento del jugador](#2-movimiento-del-jugador)
- [3. Disparo](#3-disparo)
- [4. Limpieza de objetos](#4-limpieza-de-objetos)
	- [4.1. Helicópteros](#41-helicópteros)
	- [4.2. Soldados](#42-soldados)
	- [4.3. Disparos](#43-disparos)
- [5. Cosas pendientes de acabar](#5-cosas-pendientes-de-acabar)


# 1. Spawn de enemigos

El spawn de enemigos lo tengo divido en dos partes, una para los helicópteros y otra para los soldados.

## 1.1. Helicopteros

Como en los requisitos de se especificaba que las alturas de aparición de los helicópteros podían ser solo dos
he decidido tener una constante con las posiciones de inicio de cada nivel así como el sentido. 

	const int yStartPositions[2] = {25, 75};

De esta manera quiero evitar que haya helicópteros en el mismo nivel que se muevan en direcciones opuestas

	newHelicopter.PrepareHelicopter(yStartPositions[direction], static_cast<bool>(direction));

Finalmente queda el tiempo de spawn entre los diferentes helicópteros. Para hacer esto he definido un contador en
screen_Gameplay que se incrementa a cada frame. Después para darle un poco más de aleatoriedad tengo un array constante con
diferentes tiempos de spawn. 

	const int helicopterSpawnInterval[3] = { 2, 3, 4 };

En el momento inicial, o después de spawnear un Helicóptero se elige al azar una posición del
array.
El problema aquí es que el contador se incrementa, en mi caso a sesenta por segundo así que en el momento de comprobar si toca
spawnear divido el valor entre los frames a los que va el juego.

	if (timeFromLastHelicopterSpawn / framesPerSecond >= currentHelicopterSpawn)

## 1.2. Soldados

Implementan el mismo mecanismo de spawn que los helicópteros pero la diferencia es que en vez de spawnear usando el array de 
niveles lo hace usando la lista de los helicópteros. En esto punto  he querido excluir los extremos de la pantalla, de esta manera evitor que
salten soldados en lugares en los que no puede ver el jugador. Por otro lado también he descartado la parte central de la pantalla, donde
se encuentra el jugador.

	if ((it->GetPosition() > 0 && it->GetPosition() < screenWidth - 30 && it->GetPosition() != screenWidth / 2) &&
			!(it->GetPosition() > screenWidth / 2 && it->GetPosition() < screenWidth / 2 + 150  ))

# 2. Movimiento del jugador

Para el movimiento del jugador he querido que sea un poco lento/tosto, de manera que ir de lado a lado en su rango de acción supongo un
gasto de tiempo elevado (aunque puede disparar mientras se mueve).
El movimiento se basa en la rotación de la textura. El problema es que la textura por defecto rota sobre su parte superior izquierda por
lo que hay que aplicar esta rotación en otro punto de la textura, concretamente la parte inferior.

	// Init variables
	cannonOriginRectangle = { 0.f, 0.f, (float)playerCannon.width, (float)playerCannon.height };
	cannonDestRectangle = { screenWidth / 2.f,(float) screenHeight - playerBase.height + 7 , (float)playerCannon.width * cannonScale, (float)playerCannon.height * cannonScale };
	playerCannonV = { (float)playerCannon.width / 2.f, (float)playerCannon.height };
	// Draw Method
	DrawTexturePro(playerCannon, cannonOriginRectangle, cannonDestRectangle, playerCannonV, cannonRotation, WHITE);

# 3. Disparo

Para mi a sido la parte más complicada de toda la práctica. 

    newShoot.position = { player.GetDestination().x + sin(player.GetCannonRotation() * DEG2RAD),  player.GetDestination().y - cos(player.GetCannonRotation() * DEG2RAD) };

# 4. Limpieza de objetos

## 4.1. Helicópteros

En screen_gameplay se generan muchos objetos constantemente, por lo que hay que ir eliminandolos cuando ya no son necesarios.
Para los helicópteros basta con saber si estan fuera del rango de la pantalla. Esto lo hago con un pequeño metodo que mira cada
helicóptero que tengo en la lista y comprueba si su posicion en la coordenada x es menor que 0 o mayor que el ancho de la pantalla.
Al hacer esto he visto que no funciona del todo bien, esto es debido a que la posición que tengo de la textura esta en la esquina
superior izquierda por lo tanto tengo que añadir un offset para tener en cuenta el tamaño de la textura completo.

	bool Helicopter::IsOutOfScreen()
	{
		if (!movingLeft) {
			return ((xPos + helicopterTexture.width) < 0);
		}
		else
		{
			return ((xPos - helicopterTexture.width > screenWidth));
		}
	}

Finalmente en el elemento que toca ser eliminado se saca de la lista y se sacan de memoria sus texturas.

## 4.2. Soldados

He decidido no eliminar los soldados.

## 4.3. Disparos

Los disparos se pueden eliminar de dos formas, una por salir fuera de los límites de la pantalla y otra por que han impactado con un
enemigo.
En el caso de los límites de la pantalla, teniendo en cuenta que los proyectiles nunca van a poder ir en dirección sur se tiene que
controlar el límite superior y los extremos.

	if (it->position.x > screenWidth || it->position.x < 0 ||it-> position.y < 0)

Para el caso de la colisión con un enemigo miro si el radio de la posición del proyectil se encuentra dentro de un enemigo.

	if (CheckCollisionCircleRec(itShoot->position, ballRadius, itSoldier->GetCollisionRectangle()))

# 5. Cosas pendientes de acabar

No he implementado el textureManager ni el AudioManager. Entiendo que el texture manager, como su nombre indica, se encarga de proporcionar
las texturas que se tienen que cargar. Supongo que la idea es aprovechar para cargar en memória una sola textura de cada tipo,
por ejemplo un helicóptero, un soldado...
Mi idea era implementar una clase con un patrón singleton que al instanciarse cargase las texturas, y mediante un método Get devolviese
la textura que se ha pedido.
En mi caso cada objeto gestiona su propia textura. Cuando se crea un helicóptero se carga su textura y cuando se derriba o sale de la pantalla
se borra.
Así mismo esto se aplica en el unload de la pantalla.

Para el audio manager no tengo tan claro como funciona y como implementarlo.

