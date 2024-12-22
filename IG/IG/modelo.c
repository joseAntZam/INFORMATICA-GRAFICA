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

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


/**	void initModel()

Inicializa el modelo y de las variables globales


**/

bool iluminacion = true;
int modo = GL_FILL;


void calculoNormal(float x1 , float y1 , float z1 ,float x2 , float y2 , float z2 ,float x3 , float y3 , float z3 , float resultado[3]){

	float xv1 = x2 - x1;
	float yv1 = y2 - y1;
	float zv1 = z2 - z1;
	
	float xv2 = x3 - x1;
	float yv2 = y3 - y1;
	float zv2 = z3 - z1;
	
	
	float productoVectorialx =  (yv1*zv2) - (yv2*zv1);
	float productoVectorialy =  (xv1*zv2) - (xv2*zv1);
	float productoVectorialz =  (xv1*yv2) - (xv2*yv1);
	
	
	float modulo = sqrt( (productoVectorialx*productoVectorialx) + (productoVectorialy*productoVectorialy) + (productoVectorialz*productoVectorialz));
	
	productoVectorialx = productoVectorialx/modulo;
	productoVectorialy = productoVectorialy/modulo;
	productoVectorialz = productoVectorialz/modulo;
	
	resultado[0] = productoVectorialx;
	resultado[1] = productoVectorialy;
	resultado[2] = productoVectorialz;
	
}

void setModo ( int M ){
	modo = M;
	
}

void modIluminacion(){


	
	if(iluminacion == false){
		iluminacion = true;
	}
	else{
		iluminacion = false;
	}
}

void
initModel ()
{

}


//CLASE DE LOS EJES*****************************************************************
class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
void draw( )
{
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  {
  
    if (modo ==GL_FILL && iluminacion){
    glColor3f (0, 1, 0);
    
    }
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);
	
    if (modo ==GL_FILL && iluminacion){
    glColor3f (1, 0, 0);
    
    }
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);
	
	
    if (modo ==GL_FILL && iluminacion){
    glColor3f (0, 0, 1);
    
    }
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
    
 
    
  }
  glEnd ();
  
	//glEnable (GL_LIGHTING);
  
  
  if(modo == GL_FILL && iluminacion ){
  	glEnable (GL_LIGHTING);
  	}
 	
  else{
  	glDisable(GL_LIGHTING);
  }

	
}
} ; 



//CLASE CUBO ***************************************************************************
class Cubo:Objeto3D
{
private :
	float lado;
public: 

Cubo(float lado){
	this->lado = lado;
	
	}
	


void draw()
{
	
  	glBegin (GL_QUAD_STRIP);
	    {				
	    
	    glNormal3f (0.0, 0.0, 1.0);	
	    glVertex3f (lado,lado,lado);
	    glVertex3f (0,lado,lado);
	    glVertex3f (lado, 0, lado);
	    glVertex3f (0, 0, lado);
	    
	    
	    glNormal3f (0.0, -1.0, 0.0);
	    glVertex3f (lado, 0, 0);
	    glVertex3f (0, 0, 0);
	    
	    
	    glNormal3f (0.0, 0.0, -1.0);
	    glVertex3f (lado, lado, 0);
	    glVertex3f (0, lado, 0);
	    
	    
	    
	    glNormal3f (0.0, 1.0, 0.0);	
	    glVertex3f (lado, lado, lado);
	    glVertex3f (0, lado, lado);
	  }
  	glEnd ();
  	
  	
  	glBegin (GL_QUADS);
	  {				
	  
	    
	    glNormal3f (1.0, 0.0, 0.0);
	    glVertex3f (lado, 0, 0);
	    glVertex3f (lado, lado, 0);
	    glVertex3f (lado, lado, lado);
	    glVertex3f (lado, 0, lado);
	    
	    
	    
	    glNormal3f (-1.0, 0.0, 0.0);
	    glVertex3f (0, 0, 0);
	    glVertex3f (0, 0, lado);
	    glVertex3f (0, lado, lado);
	    glVertex3f (0, lado, 0);
	  }
  	glEnd ();
  
 
}



};

//**************************************************************************************

class Piramide:Objeto3D
{
private :
	float lado;
	float altura;
public: 

Piramide(float lado,float altura){
	this->lado = lado;
	this->altura = altura;
	
	}
	


void draw()
{
	
  	glBegin (GL_QUAD_STRIP);
	    {				
	    
	    glNormal3f (0.0, -1.0, 0.0);	
	   
	    glVertex3f (lado,0,lado);
	    glVertex3f (0, 0, lado);
	    glVertex3f (lado, 0, 0 );
	    glVertex3f (0, 0, 0 );
	    
	    
	    
	    }
	    
	   
  	glEnd ();
  	
  	
  	
  	glBegin (GL_TRIANGLES);
	  {				
	  
	  
	   float resultado1[3]={0.0,0.0,0.0};
	   
	   calculoNormal(lado/2.0 , altura , lado/2.0 ,0.0 , 0.0 , lado ,lado  , 0.0  , lado ,  resultado1);
	   
	   
	    //glNormal3f (0.0, 0.0, 1.0); 
	    
	    glNormal3f (resultado1[0], resultado1[1], resultado1[2]); 
	    
	    glVertex3f (lado/2 , altura, lado/2);
	    glVertex3f (0, 0, lado);	
	    glVertex3f (lado,0, lado);
	    
	    
	    
	    
	    
	   float resultado2[3]={0.0,0.0,0.0}; 
	   
	   calculoNormal(lado/2.0 , altura , lado/2.0 ,lado , 0.0 , 0.0 ,0.0  , 0.0  , 0.0 ,  resultado2);
	    //glNormal3f (0.0, 0.0, -1.0);
	    glNormal3f (resultado2[0], resultado2[1], resultado2[2]); 
	    glVertex3f (lado/2 , altura, lado/2);
	    glVertex3f (lado, 0, 0);
	    glVertex3f (0, 0, 0);
	    
	 
	 
	    float resultado3[3]={0.0,0.0,0.0};
	    
	    calculoNormal(lado/2.0 , altura , lado/2.0 ,lado , 0.0 , lado ,lado  , 0.0  , 0.0 ,  resultado3);
	    //glNormal3f (1.0, 0.0, 0.0);
	    glNormal3f (resultado3[0], resultado3[1], resultado3[2]);
	    glVertex3f (lado/2 , altura, lado/2);
	    glVertex3f (lado, 0, lado);
	    glVertex3f (lado, 0, 0);
	    
	    
	    float resultado4[3]={0.0,0.0,0.0};
	    
	     calculoNormal(lado/2.0 , altura , lado/2.0 ,lado , 0.0 , 0.0 ,0.0  , 0.0  , lado,  resultado3);
	    //glNormal3f (-1.0, 0.0, 0.0);
	    glNormal3f (resultado3[0], resultado3[1], resultado3[2]);
	    glVertex3f (lado/2  , altura, lado/2); 
	    glVertex3f (0, 0, 0);
	    glVertex3f (0, 0, lado);
	    
	    
	      //xyz
	  }
  	glEnd ();
  
 
}


};

//**************************************************************************************

class FiguraExtra:Objeto3D
{
private :
	float lado;
	float ancho;
public: 

FiguraExtra(float lado,float ancho){

	this->lado = lado;
	this->ancho = ancho;
	
	}
	


void draw()
{
	
  	glBegin (GL_POLYGON);
	    {				
	    
	    glNormal3f (0.0, 0.0, -1.0);	
	   
	   
	   
	   
	   
	    glVertex3f (0,lado,0);
	    glVertex3f (0, lado*2, 0);
	    glVertex3f (lado, lado*3, 0 );
	    glVertex3f (lado*2, lado*3, 0 );
	    glVertex3f (lado*3,lado*2,0);
	    glVertex3f (lado*3, lado, 0);
	    glVertex3f (lado*2, 0, 0 );
	    glVertex3f (lado, 0, 0 );
	    

	    
	    }
	    
	   
  	glEnd ();
  	
  	
  	  	glBegin (GL_TRIANGLES);
	    {				
	    
	  
	    //glNormal3f (-1.0, 0.0, 0.0);	
	   
	   
	     float resultado[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,lado , lado*3.0 , 0.0 ,0.0  , lado*2.0  , 0.0,  resultado);
	    
	    glNormal3f (resultado[0], resultado[1], resultado[2]);
	    
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (lado, lado*3, 0 );
	    glVertex3f (0, lado*2, 0);
	    
	    
	    
	    
	    
	    //glNormal3f (-1.0, 0.0, 0.0);	
	   
	   
	   
	        float resultado1[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,0.0 , lado*2.0 , 0.0 ,0.0  , lado  , 0.0,  resultado1);
	    
	    glNormal3f (resultado1[0], resultado1[1], resultado1[2]);
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (0, lado*2, 0 );
	    glVertex3f (0, lado, 0);
	    
	    
	    
	    
	    
	    
	    
	    //glNormal3f (-1.0, 0.0, 0.0);	
	    
	    
	     float resultado2[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,0.0 , lado , 0.0 ,lado  , 0.0  , 0.0,  resultado2);
	    
	    glNormal3f (resultado2[0], resultado2[1], resultado2[2]);
	   
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (0, lado, 0);
	    glVertex3f (lado, 0, 0 );
	    
	    
	    
	    
	    
	    
	    //glNormal3f (0.0, -1.0, 0.0);	
	   
	   
	   
	   float resultado3[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,lado , 0.0 , 0.0 ,lado*2.0  , 0.0  , 0.0,  resultado3);
	    
	    glNormal3f (resultado3[0], resultado3[1], resultado3[2]);
	    
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (lado, 0, 0 );
	    glVertex3f (lado*2, 0, 0);
	    
	    
	    
	    
	    
	    
	     //glNormal3f (1.0, 0.0, 0.0);	
	     
	     
	     float resultado4[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,lado*2.0 , 0.0 , 0.0 ,lado*3.0  , lado  , 0.0,  resultado4);
	    
	    glNormal3f (resultado4[0], resultado4[1], resultado4[2]);
	   
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (lado*2, 0, 0 );
	    glVertex3f (lado*3, lado, 0);
	    
	    
	    
	    
	    
	    
	     //glNormal3f (1.0, 0.0, 0.0);	
	   
	   
	    float resultado5[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,lado*3.0 , lado , 0.0 ,lado*3.0  , lado*2.0  , 0.0,  resultado5);
	    
	    glNormal3f (resultado5[0], resultado5[1], resultado5[2]);
	   
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (lado*3, lado, 0);
	    glVertex3f (lado*3, lado*2, 0 );
	    
	    
	    
	    
	    
	    
	    
	    //glNormal3f (1.0, 0.0, 0.0);	
	   
	   
	    float resultado6[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,lado*3.0 , lado*2.0 , 0.0 ,lado*2.0  , lado*3.0  , 0.0,  resultado6);
	    
	    glNormal3f (resultado6[0], resultado6[1], resultado6[2]);
	   
	   
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (lado*3, lado*2, 0 );
	    glVertex3f (lado*2, lado*3, 0);
	    
	    
	    
	    
	    
	    
	    //glNormal3f (0.0, 1.0, 0.0);	
	   
	    float resultado7[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado*3)/2.0 , lado*6.0 , ancho ,lado*2.0 , lado*3.0 , 0.0 ,lado  , lado*3.0  , 0.0,  resultado7);
	    
	    glNormal3f (resultado7[0], resultado7[1], resultado7[2]);
	   
	   
	    glVertex3f ((lado*3)/2, lado*6, ancho );
	    glVertex3f (lado*2, lado*3, 0);
	    glVertex3f (lado, lado*3, 0 );
	
	    }
	    
	    glEnd();
  	
  
 	
  	
}


};




//**************************************************************************************

class FiguraExtra2:Objeto3D
{
private :
	float lado;
	float altura;
public: 

FiguraExtra2(float lado,float altura){
	this->lado = lado;
	this->altura = altura;
	
	}
	


void draw()
{
	
  	glBegin (GL_QUAD_STRIP);
	    {				
	    
	    glNormal3f (0.0, -1.0, 0.0);	
	   
	    glVertex3f (lado,0,lado);
	    glVertex3f (0, 0, lado);
	    glVertex3f (lado, 0, 0 );
	    glVertex3f (0, 0, 0 );
	    
	    }
	    
	   
  	glEnd ();
  	
  	glBegin (GL_QUADS);
	    {	
  	
  	    //glNormal3f (-1.0, 0.0, 0.0);	
	   
	   
	    float resultado1[3]={0.0,0.0,0.0};
	    
	    calculoNormal(lado/4.0,altura,lado/4.0 ,0.0 , 0.0 , 0.0 ,0.0  , 0.0  , lado,  resultado1);
	    
	    glNormal3f (resultado1[0], resultado1[1], resultado1[2]);
	   
	    glVertex3f (lado/4.0,altura,lado/4.0);
	    glVertex3f (0, 0, 0 );
	    glVertex3f (0, 0, lado);
	    glVertex3f (lado/4.0, altura, (lado/4.0)*3.0);
	     
	     
	     //glNormal3f (0.0, 0.0, 1.0);
	     
	     
	    float resultado2[3]={0.0,0.0,0.0};
	    
	    calculoNormal(lado/4.0, altura, (lado/4.0)*3.0 ,0.0 , 0.0 , lado ,lado  , 0.0  , lado,  resultado2);
	    
	    glNormal3f (resultado2[0], resultado2[1], resultado2[2]);	
	      
	     glVertex3f (lado/4.0, altura, (lado/4.0)*3.0);
	     glVertex3f (0, 0, lado);
	     glVertex3f (lado, 0, lado);
	     glVertex3f ((lado/4.0)*3.0, altura, (lado/4.0)*3.0 );
	   	 
	   	 
	     //glNormal3f (1.0, 0.0, 0.0);
	     
	     float resultado3[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado/4.0)*3.0, altura, (lado/4.0)*3.0 ,lado, 0.0, lado ,lado  , 0.0  , 0.0,  resultado3);
	    
	    glNormal3f (resultado3[0], resultado3[1], resultado3[2]);
	     	
	     glVertex3f ((lado/4.0)*3.0, altura, (lado/4.0)*3.0 );
	     glVertex3f (lado, 0, lado);
	     glVertex3f (lado, 0, 0);
	     glVertex3f ((lado/4.0)*3.0, altura, lado/4.0 );
	      
	      
	      
	     //glNormal3f (0.0, 0.0, -1.0);
	     
	      float resultado4[3]={0.0,0.0,0.0};
	    
	    calculoNormal((lado/4.0)*3.0, altura, lado/4.0 ,lado, 0.0, 0.0 ,0.0  , 0.0  , 0.0,  resultado4);
	    
	    glNormal3f (resultado4[0], resultado4[1], resultado4[2]);
	    
	     glVertex3f ((lado/4.0)*3.0, altura, lado/4.0 );
	     glVertex3f (lado, 0, 0);
	     glVertex3f (0, 0, 0);
	     glVertex3f (lado/4.0,altura,lado/4.0);
	     	
	      
	      
	       glNormal3f (0.0, 1.0, 0.0);	
	   
	    glVertex3f (lado/4.0,altura,lado/4.0);
	    glVertex3f (lado/4.0, altura, (lado/4.0)*3.0);
	    glVertex3f ((lado/4.0)*3.0, altura, (lado/4.0)*3.0 );
	    glVertex3f ((lado/4.0)*3.0, altura, lado/4.0 );
	    
	   	}
	   	 glEnd ();
  	
}


};
//**************************************************************************************
Ejes ejesCoordenadas;
Cubo cubito(4);
Piramide p1(4,6);
FiguraExtra f1(2,6);
FiguraExtra2 f2(4,6);

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.3, 0.5, 1 };
  float color2[4] = { 1.0, 1.0, 0.0, 0.0 };
  float color3[4] = { 0.0, 1.0, 1.0, 1.0 };
  float color4[4] = { 1.0,0.0 , 0.0, 0.0 };
  
  if(iluminacion && modo == GL_FILL ){
  	glEnable(GL_LIGHTING);
  	
  	}
  	
  
  else {
  	glDisable(GL_LIGHTING);
  }
  
 



  
  
  glPolygonMode (GL_FRONT_AND_BACK , modo);
  
  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes
  
  
  

 glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);   
  
 cubito.draw(); 
  
  
  
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);  
 
  glTranslatef ( 5 , 0 , 0 ); 
  
  p1.draw();    
  
  
 glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);   
 glTranslatef ( 5 , 0 , 0 ); 
  
 f1.draw();
 
 
glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4); 
glTranslatef ( 7 , 0 , 0 ); 
 f2.draw();
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
