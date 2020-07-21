## Argentum - TP Final - Taller de Programación I

## Docente asignado: Martín Di Paola 

### Alumnos: 

* Tomas Szemzo - 97771
* Hernan Tain - 98070

## Documentos del Proyecto

* Manual del proyecto: https://docs.google.com/document/d/1GmcXl18Py0kkTP8LkjxQ08TCIwdhX_ad7nioDZlPvL4/edit?usp=sharing
* Documentación técnica: https://docs.google.com/document/d/1kRTEceXyvtzqqkpvy2Lk5dLBvfUDv6I6VGAHoJygDIU/edit?usp=sharing
* Manual de usuario:
  https://docs.google.com/document/d/1_Pc4m-L8o1Re2u4rDfyTD-45QZyEbK-9hg-p50h0FEw/edit?usp=sharing


## Introducción

El presente trabajo práctico busca replicar el famoso juego online Argentum, en el cual cada jugador se crea un personaje escogiendo raza y clase, e irá aventurandose al mundo de Argentum en busca de oro, mágicos items y batallas que pueden ser contra criaturas (NPC) u otros jugadores que se encuentren conectados.

El proyecto incluye un servidor multithreading que se comunica con los clientes a través de sockets TCP, desarrollado en C++, utilizando la librería SDL para la parte gráfica del cliente; Tiled para editar el mapa en el cual se desarrollará el juego; MessagePack para la serialización binaria que se utiliza para el  protocolo y JsonCpp para poder parsear los archivos de configuración en formato JSON. 

### Dependencias

Para correr las aplicaciones cliente y servidor de este proyecto, se necesitan las siguientes dependencias:

* SDL 2
* msgpack
* Json CPP
* CMake (para instalar msgpack)


## SDL 2

Se puede instalar SDL 2 en el sistema corriendo los siguientes comandos en la terminal:

`sudo apt-get install libsdl2-dev`

`sudo apt-get install libsdl2-image-dev`

`sudo apt-get install libsdl2-image-ttf`

`sudo apt-get install libsdl2-ttf-dev`

`sudo apt-get install libsdl2-mixer-dev`

## msgpack y CMake

Para poder instalar msgpack, debemos tener previamente instalado CMake en nuestro sistema. 

La versión de CMake debe ser mayor o igual a la 3.0.0

Para instalar CMake se debe ejecutar el siguiente comando: 

`sudo apt-get -y install cmake`

Luego msgpack puede ser instalada corriendo los siguientes comandos: 

```bash
git clone https://github.com/msgpack/msgpack-c.git
cd msgpack-c
git checkout cpp_master
cmake -DMSGPACK_CXX[11|17]=ON .
sudo make install
```

Mas información acerca de msgpack en: https://github.com/msgpack/msgpack-c/tree/cpp_master


## JsonCPP

Para poder instalar JsonCPP debemos ejecutar el siguiente comando:

`sudo apt-get install libjsoncpp-dev`

## Instrucciones de Uso

Una vez realizada la instalación de dependencias mencionadas anteriormente, con el repositorio clonado, podremos ejecutar la aplicación de la siguiente forma:

Primero que todo, parados en la base del repositorio, hay que compilar los archivos con el comando `make`.

### Servidor

Se ejecuta corriendo: 

`./server <config_file>`

Se provee un archivo de configuración en el proyecto ubicado en la carpeta server_files por lo que puede ser levantado corriendo: 

`./server server_files/config.json`


### Cliente

Se ejecuta corriendo: 

`./client <raza> <clase>`

Se provee un archivo de configuración en el proyecto ubicado en la carpeta client_files/client_config.json para modificar el host y puerto 

Donde raza debe ser alguna de las siguientes:

* humano
* elfo
* enano
* gnomo

y clase: 

* mago
* clerigo
* paladin
* guerrero

### Teclas para jugar

Para poder jugar al Argentum se utilizarán las siguientes teclas:

* key_left-> mover el personaje a la izquierda.
* key_right-> mover el personaje a la derecha.
* key_down-> mover el personaje hacia abajo.
* key_up-> mover el personaje hacia arriba.
* click (sobre NPC o personaje)-> intentará atacar si se encuentra a la distancia adecuada. Recordar que los báculos y los arcos son armas de larga distancia, es decir, podremos atacar desde donde sea, mientras que para las armas de melee uno debe estar a poca distancia para que se concrete.
* click (sobre un ítem en el inventario)-> equipa o desequipa el ítem del inventario según este se encuentre ya equipado o no.
* click derecho (sobre un ítem en el inventario)-> droppea el ítem al suelo en caso de que este no esté equipado.
* f-> resucita al personaje si este se encuentra muerto y a corta distancia del sacerdote
* c-> cura al personaje (mana y vida) si este se encuentra vivo y a corta distancia del sacerdote
* z-> pone al personaje en estado de meditación para aumentar su mana.
* a-> toma un item del suelo si se encuentra debajo nuestro
* d-> deposita el oro del personaje en el banco en caso de que se encuentre un banquero próximo al personaje.
* s-> retira el oro del personaje del banco en caso de que se encuentre un banquero próximo al personaje.
* 0-> activa y desactiva la música.



