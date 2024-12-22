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
#include<iomanip>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "file_ply_stl.h"

using namespace std;




/**	void initModel()

Inicializa el modelo y de las variables globales


**/


void calculoNormal(float x1 , float y1 , float z1 ,float x2 , float y2 , float z2 ,float x3 , float y3 , float z3 , float resultado[3]){

	float xv1 = x2 - x1;
	float yv1 = y2 - y1;
	float zv1 = z2 - z1;
	
	
	float xv2 = x3 - x1;
	float yv2 = y3 - y1;
	float zv2 = z3 - z1;
	
	
	float productoVectorialx =  (yv1*zv2) - (yv2*zv1);
	float productoVectorialy =   (zv1*xv2)-(xv1*zv2);
	float productoVectorialz =  (xv1*yv2) - (xv2*yv1);
	
	
	float modulo = sqrt( productoVectorialx*productoVectorialx + productoVectorialy*productoVectorialy + productoVectorialz*productoVectorialz);
	
	productoVectorialx = productoVectorialx/modulo;
	productoVectorialy = productoVectorialy/modulo;
	productoVectorialz = productoVectorialz/modulo;
	
	resultado[0] = productoVectorialx;
	resultado[1] = productoVectorialy;
	resultado[2] = productoVectorialz;
	
}



void
initModel ()
{

}



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
    glColor3f (0, 1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);

    glColor3f (1, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
  }
  glEnd ();
  glEnable (GL_LIGHTING);

}
} ; 
//******************************************************************************************************************************************************************************************************
class Malla:public Objeto3D{

public:
//++++++++++++++++++++++++++++++++++++++++++++++Constructor+++++++++++++++++++++++++++++++++++++++++++
	vector<float>vertices_ply;
	vector<int>caras_ply;
	vector<float>normales_vertices;
	vector<float>normales_caras;
	bool liso;
	Malla(){}
	
	Malla(const char cadena[],bool liso ){
	
	   ply::read( cadena , vertices_ply,caras_ply);
		 
           float acumuladorVertices[vertices_ply.size()] = {0.0};
		
		   //*******************************************************NORMALES DE CARAS*****************************************		
	   for(int i = 0 ; i < caras_ply.size() ; i = i + 3){
	 	 		
		   float resultado[3] = { 0.0,0.0,0.0};
		   
		   calculoNormal(vertices_ply[3*caras_ply[i]] , vertices_ply[3*caras_ply[i]+1] , vertices_ply[3*caras_ply[i]+2],vertices_ply[3*caras_ply[i+1]] , vertices_ply[3*caras_ply[i+1]+1] ,  vertices_ply[3*caras_ply[i+1]+2],vertices_ply[3*caras_ply[i+2]] , vertices_ply[3*caras_ply[i+2]+1] , vertices_ply[3*caras_ply[i+2]+2] ,  resultado);
		   
		    normales_caras.push_back(resultado[0]);
		    normales_caras.push_back(resultado[1]);
		    normales_caras.push_back(resultado[2]);
		    
		    //******************************************************NORMALES VERTICES******************************************	    
		    acumuladorVertices[3*caras_ply[i]] += resultado[0];
		    acumuladorVertices[3*caras_ply[i]+1] += resultado[1];
		    acumuladorVertices[3*caras_ply[i]+2] +=  resultado[2];
		    
		    acumuladorVertices[3*caras_ply[i+1]] += resultado[0];
		    acumuladorVertices[3*caras_ply[i+1]+1] += resultado[1];
		    acumuladorVertices[3*caras_ply[i+1]+2] += resultado[2]; 	
		    
		    acumuladorVertices[3*caras_ply[i+2]] += resultado[0];
		    acumuladorVertices[3*caras_ply[i+2]+1] += resultado[1];
		    acumuladorVertices[3*caras_ply[i+2]+2] += resultado[2];	
	    }
	 	 	
	 	 	
	    for ( int i = 0 ; i< vertices_ply.size() ; i = i + 3){
	    
		   float modulo = sqrt( (acumuladorVertices[i]*acumuladorVertices[i]) + (acumuladorVertices[i+1]*acumuladorVertices[i+1]) + (acumuladorVertices[i+2]*acumuladorVertices[i+2]));
		   
	           acumuladorVertices[i] = (acumuladorVertices[i] / modulo);
	           acumuladorVertices[i+1] = (acumuladorVertices[i+1] / modulo);
		   acumuladorVertices[i+2] = (acumuladorVertices[i+2] / modulo);
		    
		   normales_vertices.push_back(acumuladorVertices[i]);
		   normales_vertices.push_back(acumuladorVertices[i+1]);
		   normales_vertices.push_back(acumuladorVertices[i+2]);
	    
	    	   } 
	    	   
	    	   
	    	   //si liso es true nuestro atributo liso(this.liso) se pondra a true , esto se verá reflejado en el metodo draw.
	    	   this->liso = liso;
	}
	
	
//++++++++++++++++++++++++++++++++++++++++++++++Draw+++++++++++++++++++++++++++++++++++++++++++
	void draw(){
		
		if(!liso){
			glShadeModel( GL_FLAT );
			glBegin (GL_TRIANGLES);
		 	 {	
		 	   	for(int i = 0 ; i < caras_ply.size() ; i = i +3){
		 	   
		 	 		glNormal3f (normales_caras[i],normales_caras[i+1], normales_caras[i+2]); 
		 	 			
		 	 		glVertex3f(vertices_ply[3*caras_ply[i]] , vertices_ply[3*caras_ply[i]+1] , vertices_ply[3*caras_ply[i]+2]);
		 	 		glVertex3f(vertices_ply[3*caras_ply[i+1]] , vertices_ply[3*caras_ply[i+1]+1] , vertices_ply[3*caras_ply[i+1]+2]);
		 	 		glVertex3f(vertices_ply[3*caras_ply[i+2]] , vertices_ply[3*caras_ply[i+2]+1] , vertices_ply[3*caras_ply[i+2]+2]);
		 	 		
		 	 		}
		 	 }
		 	 glEnd();
	 	}else{
	 	
	 	
	 		glShadeModel( GL_SMOOTH );
		 	glBegin (GL_TRIANGLES);
		 	 {	
		 	   	for(int i = 0 ; i < caras_ply.size() ; i = i+3 ){
		 	   
		 	 		glNormal3f (normales_vertices[3*caras_ply[i]],normales_vertices[3*caras_ply[i]+1], normales_vertices[3*caras_ply[i]+2]); 
		 	 		glVertex3f(vertices_ply[3*caras_ply[i]] , vertices_ply[3*caras_ply[i]+1] , vertices_ply[3*caras_ply[i]+2]);
		 	 		
		 	 		glNormal3f (normales_vertices[3*caras_ply[i+1]],normales_vertices[3*caras_ply[i+1]+1], normales_vertices[3*caras_ply[i+1]+2]); 
		 	 		glVertex3f(vertices_ply[3*caras_ply[i+1]] , vertices_ply[3*caras_ply[i+1]+1] , vertices_ply[3*caras_ply[i+1]+2]);
		 	 		
		 	 		glNormal3f (normales_vertices[3*caras_ply[i+2]],normales_vertices[3*caras_ply[i+2]+1], normales_vertices[3*caras_ply[i+2]+2]); 
		 	 		glVertex3f(vertices_ply[3*caras_ply[i+2]] , vertices_ply[3*caras_ply[i+2]+1] , vertices_ply[3*caras_ply[i+2]+2]);
		 	 		
		 	 		
		 	 		}
		 	 		
		 	 		
		 	 		
		 	 }
		 	 glEnd();
		 	 }
		 	 
		 	
	   }
};


//******************************************************************************************************************************************************************************************************
class mallaRevolucion:public Malla{

	public:
		//cada copia tiene m vertices los vertices de abajo a arriba
		mallaRevolucion(const char cadena[] , int copias , bool liso){
			
			if(copias < 3){
				copias = 3;
			}
		
			ply::read_vertices( cadena , vertices_ply);
			
			int m = vertices_ply.size() ; 
			
			//pongo desde copias-1 hasta 0 con el objetivo de almacenar los vertices en sentido antihorario y facilitar la creación de las caras
			
			for ( int i = copias-1 ; i > 0 ; i--){
				
				for (int j = 0 ; j < m ; j = j+3){
				
					
					float x = vertices_ply[j]*cos(2.0*i*M_PI/(copias)) +
						vertices_ply[j+2]*sin(2.0*i*M_PI/(copias));
					
					float y = vertices_ply[j+1];
					
					float z = vertices_ply[j]*sin(2.0*i*M_PI/(copias)) +
						vertices_ply[j+2]*cos(2.0*i*M_PI/(copias));
					
					vertices_ply.push_back(x);
					vertices_ply.push_back(y);
					vertices_ply.push_back(z);	
				}
			}
			

			int modulo = vertices_ply.size() / 3;
			int m2 = m/3 ; 
		
		
			for ( int i = 0 ; i < copias ; i++){
				
				for (int j = 0 ; j < m2-1 ; j++){
					
					int k = i*m2+j;
				
					int xC1 = k%(modulo); 
					int yC1 = (k+m2)%(modulo);
					int zC1 = (k+m2+1)%(modulo);
					
					
					
					caras_ply.push_back(xC1);
					caras_ply.push_back(yC1);
					caras_ply.push_back(zC1);
					
			
					int xC2 = k%(modulo);
					int yC2 = (k+m2+1)%(modulo);
					int zC2 = (k+1)%(modulo);
					
					
					
					caras_ply.push_back(xC2);
					caras_ply.push_back(yC2);
					caras_ply.push_back(zC2);
				}
				
			}
			
			//si liso es true nuestro atributo liso(this.liso) se pondra a true , esto se verá reflejado en el draw.
	    	   	this->liso = liso;
			
			
			
//*****************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************			
						
	   float acumuladorVertices[vertices_ply.size()] = {0.0};
		
		   //*******************************************************NORMALES DE CARAS*****************************************		
	   for(int i = 0 ; i < caras_ply.size() ; i = i + 3){
	 	 		
		   float resultado[3] = { 0.0,0.0,0.0};
		   
		   calculoNormal(vertices_ply[3*caras_ply[i]] , vertices_ply[3*caras_ply[i]+1] , vertices_ply[3*caras_ply[i]+2],vertices_ply[3*caras_ply[i+1]] , vertices_ply[3*caras_ply[i+1]+1] ,  vertices_ply[3*caras_ply[i+1]+2],vertices_ply[3*caras_ply[i+2]] , vertices_ply[3*caras_ply[i+2]+1] , vertices_ply[3*caras_ply[i+2]+2] ,  resultado);
		   
		    normales_caras.push_back(resultado[0]);
		    normales_caras.push_back(resultado[1]);
		    normales_caras.push_back(resultado[2]);
		    
		    //******************************************************NORMALES VERTICES******************************************	    
		    acumuladorVertices[3*caras_ply[i]] += resultado[0];
		    acumuladorVertices[3*caras_ply[i]+1] += resultado[1];
		    acumuladorVertices[3*caras_ply[i]+2] +=  resultado[2];
		    
		    acumuladorVertices[3*caras_ply[i+1]] += resultado[0];
		    acumuladorVertices[3*caras_ply[i+1]+1] += resultado[1];
		    acumuladorVertices[3*caras_ply[i+1]+2] += resultado[2]; 	
		    
		    acumuladorVertices[3*caras_ply[i+2]] += resultado[0];
		    acumuladorVertices[3*caras_ply[i+2]+1] += resultado[1];
		    acumuladorVertices[3*caras_ply[i+2]+2] += resultado[2];	
	    }
	 	 	
	 	 	
	    for ( int i = 0 ; i< vertices_ply.size() ; i = i + 3){
	    
		   float modulo = sqrt( (acumuladorVertices[i]*acumuladorVertices[i]) + (acumuladorVertices[i+1]*acumuladorVertices[i+1]) + (acumuladorVertices[i+2]*acumuladorVertices[i+2]));
		   
	           acumuladorVertices[i] = (acumuladorVertices[i] / modulo);
	           acumuladorVertices[i+1] = (acumuladorVertices[i+1] / modulo);
		   acumuladorVertices[i+2] = (acumuladorVertices[i+2] / modulo);
		    
		   normales_vertices.push_back(acumuladorVertices[i]);
		   normales_vertices.push_back(acumuladorVertices[i+1]);
		   normales_vertices.push_back(acumuladorVertices[i+2]);
	    
	    	   } 
	    }			

};

//******************************************************************************************************************************************************************************************************
const char cadena[] = "beethoven";
const char cadena2[] = "perfil_chincheta";
const char cadena3[] = "big_dodge";
Ejes ejesCoordenadas;
Malla m(cadena,true);
mallaRevolucion m1(cadena2,8,false);
Malla m2(cadena3,false);



/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color[4] = { 1.0, 1.0, 1.0, 0.0};
  float  color1[4] = { 1.0, 0.0, 1.0, 0.0};
  float  color2[4] = { 1.0, 0.0, 0.0, 0.0};


  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glTranslatef ( -8 , 0 , 0 ); 
  m.draw();
  
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
  glTranslatef ( 8 , 0 , 0 ); 
  m1.draw();   
  
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  glTranslatef ( 12 , 0 , 0 ); 
  m2.draw(); 

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          

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
