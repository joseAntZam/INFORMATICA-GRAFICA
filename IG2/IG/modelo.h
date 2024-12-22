/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================

	 modelo.h


*/




void setAnimacionMOV( bool estado);
bool estadoAnimacionFuctionMOV();
void movimientoDedosArribaMOV();
void movimientoDedosAbajoMOV();
void movimientoManoDerechaMOV();
void movimientoManoIzquierdaMOV();
void saludoDerechaMOV();
void saludoIzquierdaMOV();
void levantaAntebrazoMOV();
void bajaAntebrazoMOV();
void modificaLuz(bool estado);

void calculoNormal(float x1 , float y1 , float z1 ,float x2 , float y2 , float z2 ,float x3 , float y3 , float z3 , float resultado[3]);
/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();



class Objeto3D 
{ 
public: 
unsigned char *textura;
unsigned ancho;
unsigned alto;

GLuint idText;
void aniadeTextura(const char *nombre_arch , unsigned &ancho , unsigned &alto);
virtual void draw( ) = 0; // Dibuja el objeto
} ; 




