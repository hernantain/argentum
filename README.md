## Argentum - TP Final - Taller de Programación I

### Alumnos: 

* Tomas Szemzo - 97771
* Hernan Tain - 98070

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

Para poder instalar msgpack, debemos tener CMake instalado en nuestro sistema. La versión de CMake debe ser mayor o igual a la 3.0.0

Puede ser instalada corriendo: `sudo apt-get -y install cmake`

Esta libreria puede ser instalada corriendo los siguientes comandos: 

```bash
git clone https://github.com/msgpack/msgpack-c.git
cd msgpack-c
git checkout cpp_master
cmake -DMSGPACK_CXX[11|17]=ON .
sudo make instal
```

Mas información acerca de msgpack en: https://github.com/msgpack/msgpack-c/tree/cpp_master


## Json CPP

Se instala corriendo: 

`sudo apt-get install libjsoncpp-dev`

## Correr las aplicaciones

### Servidor

Se puede levantar el server corriendo `./server <config_file>`

En nuestro caso el mismo se encuentra en la carpeta server_files por lo que puede ser levantado corriendo: `./server server_files/config.json`


### Cliente

Para correr el cliente hay que correr: 

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

