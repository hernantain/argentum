## Argentum - TP Final - Taller de Programación I

## Docente asignado: Martín Di Paola 

### Alumnos: 

* Tomas Szemzo - 97771
* Hernan Tain - 98070

## Introducción:

El presente trabajo práctico busca replicar el famoso juego online Argentum, en el cual cada jugador se crea un personaje escogiendo raza y clase, e irá aventurandose al mundo de Argentum en busca de oro, mágicos items y batallas que pueden ser contra criaturas (NPC) u otros jugadores que se encuentren conectados.

El proyecto incluye un servidor multithreading que se comunica con los clientes a través de sockets TCP, desarrollado en C++, utilizando la librería SDL para la parte gráfica del cliente; Tiled para editar el mapa en el cual se desarrollará el juego; MessagePack para la serialización binaria que se utilizará para el  protocolo y JsonCpp para poder parsear los archivos de configuración en formato JSON. 

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

## msgpack y CMake

Para poder instalar msgpack, debemos tener previamente instalado CMake en nuestro sistema. 

La versión de CMake debe ser mayor o igual a la 3.0.0

Para instalar CMake se debe ejecutar el siguiente comando: `sudo apt-get -y install cmake`

Luego msgpack puede ser instalada corriendo los siguientes comandos: 

```bash
git clone https://github.com/msgpack/msgpack-c.git
cd msgpack-c
git checkout cpp_master
cmake -DMSGPACK_CXX[11|17]=ON .
sudo make install
```

Mas información acerca de msgpack en: https://github.com/msgpack/msgpack-c/tree/cpp_master


## Json CPP

Se instala corriendo: 

`sudo apt-get install libjsoncpp-dev`

## Instrucciones de Uso

Una vez realizada la instalación previa de dependencias que se menciona anteriormente, con el repositorio clonado, podremos ejecutar la aplicación de la siguiente forma:

### Servidor

Se ejecuta corriendo: 

`./server <config_file>`

Se provee un archivo de configuración en el proyecto ubicado en la carpeta server_files por lo que puede ser levantado corriendo: `./server server_files/config.json`


### Cliente

Se ejecuta corriendo: 

`./client <raza> <clase>`

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
Para esta primera versión se utilizarán las siguientes teclas:

* key_left-> mover el personaje a la izquierda.
* key_right-> mover el personaje a la derecha.
* key_down-> mover el personaje hacia abajo.
* key_up-> mover el personaje hacia arriba.
* y-> equipa un arma Hacha.
* u-> equipa un arma Espada.
* i-> equipa un arma Martillo.
* o-> equipa un arma Báculo Nudoso.
* p-> equipa un arma Báculo Engarzado.
* h-> equipa un casco Capucha.
* j-> equipa un casco Casco de Hierro.
* k-> equipa un casco Sombrero Mágico.
* l-> desequipa cualquier casco que posea.
* b-> desequipa cualquier armadura que posea.
* n-> equipa una armadura Armadura de Placas.
* m-> equipa una armadura Armadura de Cuero.
* click-> ataca al personaje ubicado en la posición del click (en caso de que pueda)
