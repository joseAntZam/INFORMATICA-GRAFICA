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
#include <chrono>
#include <thread>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "file_ply_stl.h"
#include "lector-jpg.h"

using namespace std;




/**	void initModel()

Inicializa el modelo y de las variables globales


**/

void Objeto3D::aniadeTextura(const char *nombre_arch , unsigned &ancho , unsigned &alto){
	textura = LeerArchivoJPEG (nombre_arch,ancho,alto );      
}



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





float vectorColorDifusa[4]={ 0.0, 0.0, 0.0, 0.0};
float vectorColorEspecular[4]={ 0.0, 0.0, 0.0, 0.0};

void Especular(float color[]){
	for ( int i = 0 ; i < 4 ; i++){
		vectorColorEspecular[i] = color[i];	
	}
}

void Difusa(float color[]){
	for ( int i = 0 ; i < 4 ; i++){
		vectorColorDifusa[i] = color[i];	
	}
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



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


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class mallaRevolucion:public Malla{

	public:
		vector<float>coordenadasTexturas;
		int numero_vertices_iniciales;
	
	//int numero_vertices_iniciales;
		//cada copia tiene m vertices los vertices de abajo a arriba
		mallaRevolucion(const char cadena[] , int copias , bool liso){
		
			
			if(copias < 3){
				copias = 3;
			}
		
			ply::read_vertices( cadena , vertices_ply);
			
			int m = vertices_ply.size() ; 
			
			numero_vertices_iniciales = m;
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
					
					//cout<<" "<<x<<" "<<y<<" "<<z<<endl;	
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
	    	   
	    	   
	    	   
	    	   
	    	   
	    	   
	    	  //A la hora de crear la malla de revolución le calculo las posibles coordenadas de textura , para si queremos, poderlas aplicar o no 
	    	   
	    	  //float n = 1.0;
	    	float angulo = 360/copias;
	    	int contador= 0;
	    	float distanciaMax = 0;
	    	
	    	for ( int i = 0 ; i < numero_vertices_iniciales/3 ; i++){
			float xv1 = vertices_ply[i+3] - vertices_ply[i];
			float yv1 = vertices_ply[i+3+1] - vertices_ply[i+1];
			float zv1 = vertices_ply[i+3+2] - vertices_ply[i+2];
			distanciaMax += sqrt( xv1*xv1 + yv1*yv1 + zv1*zv1);
	    	 }
	    	
	    	
	    	int contadorquitar= 1;
	    	float uAux = 0.0;
	    	float u = 0.0;
	    	
	    	 for(int i = 0 ; i < vertices_ply.size() ; i = i + 3){
	    	 	
	    	 	float v = 0.0;
	    	 	if(contador == numero_vertices_iniciales/3){
	    	 		//n++;
	    	 		uAux += angulo;
	    	 		u = uAux/360;
	    	 		contador=0;
	    	 	}
	    	 	
	    	 	
	    	 	
	    	 	float distancia = 0.0;
	    	 	
	    	 	for ( int a = 0 ; a < contador ; a++){
				float xv1 = vertices_ply[3*a+3] - vertices_ply[3*a];
				float yv1 = vertices_ply[3*a+3+1] - vertices_ply[3*a+1];
				float zv1 = vertices_ply[3*a+3+2] - vertices_ply[3*a+2];
				distancia += sqrt( xv1*xv1 + yv1*yv1 + zv1*zv1);
	    	 	}
	    	 	
	    	 	v = distancia/distanciaMax;
	    	 	
	    	 	
	    	 	coordenadasTexturas.push_back(u);
	    	 	coordenadasTexturas.push_back(v);
	    	 	contador++;
	    	 	contadorquitar++;
	    	 } 
   
	    }
	    
	    
	    
	    void draw(){
		
		
		
			glGenTextures( 1 , &idText );
			glBindTexture( GL_TEXTURE_2D ,idText ) ;
			glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP ) ;
			glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T, GL_CLAMP ) ;
			glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR ) ;
			glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR ) ;
			glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGB , ancho, alto, 0 ,GL_RGB ,GL_UNSIGNED_BYTE , textura ) ;
			
			
	
	
	
			
			if(!liso){
				glShadeModel( GL_FLAT );
				glBegin (GL_TRIANGLES);
			 	 {	
			 	 
			 	 
			 	   	for(int i = 0 ; i < caras_ply.size() ; i = i +3){
			 	   
			 	 		glNormal3f (normales_caras[i],normales_caras[i+1], normales_caras[i+2]); 
			 	 		
			 	 		
			 	 		
						float primer_u_text=coordenadasTexturas[2*caras_ply[i]];
						 		 	 		
						if(i/3 > (((numero_vertices_iniciales/3)*2)-3)){
							if(caras_ply[i] < (numero_vertices_iniciales/3)){
								primer_u_text = 1.0; 
							} 
						}
			 	 		glTexCoord2f(primer_u_text,coordenadasTexturas[2*caras_ply[i]+1]);
				 	 	glVertex3f(vertices_ply[3*caras_ply[i]] , vertices_ply[3*caras_ply[i]+1] , vertices_ply[3*caras_ply[i]+2]);
				 	 		
				 	 		
				 	 		
						float segundo_u_text=coordenadasTexturas[2*caras_ply[i+1]];		 	 		
									 	 		
						if(i/3 > (((numero_vertices_iniciales/3)*2)-3)){
							if(caras_ply[i+1] < (numero_vertices_iniciales/3)){
								segundo_u_text = 1.0;
							} 
						}
						
				 	 	glTexCoord2f(segundo_u_text,coordenadasTexturas[2*caras_ply[i+1]+1]);
				 	 	glVertex3f(vertices_ply[3*caras_ply[i+1]] , vertices_ply[3*caras_ply[i+1]+1] , vertices_ply[3*caras_ply[i+1]+2]);


			 	 	
						float tercero_u_text=coordenadasTexturas[2*caras_ply[i+2]];		 	 		
									 	 		
						if(i/3 > (((numero_vertices_iniciales/3)*2)-3)){
							if(caras_ply[i+2] < (numero_vertices_iniciales/3)){
								tercero_u_text = 1.0;
							} 
						}			 	 	
				 	 	
				 	 	glTexCoord2f(tercero_u_text,coordenadasTexturas[2*caras_ply[i+2]+1]);
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
			 	 		float primer_u_text=coordenadasTexturas[2*caras_ply[i]];
 		 	 		
							if(i/3 > (((numero_vertices_iniciales/3)*2)-3)){
								if(caras_ply[i] < (numero_vertices_iniciales/3)){
									primer_u_text = 1.0; 
								} 
							}
							
						glTexCoord2f(primer_u_text,coordenadasTexturas[2*caras_ply[i]+1]);
			 	 		glVertex3f(vertices_ply[3*caras_ply[i]] , vertices_ply[3*caras_ply[i]+1] , vertices_ply[3*caras_ply[i]+2]);
			 	 		
			 	 		
			 	 			
			 	 		glNormal3f (normales_vertices[3*caras_ply[i+1]],normales_vertices[3*caras_ply[i+1]+1], normales_vertices[3*caras_ply[i+1]+2]); 
			 	 		float segundo_u_text=coordenadasTexturas[2*caras_ply[i+1]];		 	 		
			 	 		
							if(i/3 > (((numero_vertices_iniciales/3)*2)-3)){
								if(caras_ply[i+1] < (numero_vertices_iniciales/3)){
									segundo_u_text = 1.0;
								} 
							}
							
			 	 		glTexCoord2f(segundo_u_text,coordenadasTexturas[2*caras_ply[i+1]+1]);
			 	 		glVertex3f(vertices_ply[3*caras_ply[i+1]] , vertices_ply[3*caras_ply[i+1]+1] , vertices_ply[3*caras_ply[i+1]+2]);
			 	 		
			 	 		
			 	 		
			 	 		glNormal3f (normales_vertices[3*caras_ply[i+2]],normales_vertices[3*caras_ply[i+2]+1], normales_vertices[3*caras_ply[i+2]+2]);
			 	 		float tercero_u_text=coordenadasTexturas[2*caras_ply[i+2]];		 	 		
			 	 		
						if(i/3 > (((numero_vertices_iniciales/3)*2)-3)){
							if(caras_ply[i+2] < (numero_vertices_iniciales/3)){
								tercero_u_text = 1.0;
							} 
						}			 	 	
			 	 	
			 	 		glTexCoord2f(tercero_u_text,coordenadasTexturas[2*caras_ply[i+2]+1]); 
			 	 		glVertex3f(vertices_ply[3*caras_ply[i+2]] , vertices_ply[3*caras_ply[i+2]+1] , vertices_ply[3*caras_ply[i+2]+2]);
			 	 		
			 	 		
			 	 		}
			 	 		
			 	 		
			 	 		
			 	 }
			 	 glEnd();
			 	 }
			 	 
			 	
		   }
	   
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class CuboBrazo:Objeto3D
{
	private :
		float lado;
	public: 

	CuboBrazo(float lado){
		this->lado = lado;
		}
		
	void draw(){
			
		  	glBegin (GL_QUAD_STRIP);
			    {				
			    
			    glNormal3f (0.0, 0.0, 1.0);	
			    glVertex3f (lado/1.5,0.3,lado);
			    glVertex3f (0,0.3,(lado/7)*4);
			    glVertex3f (lado/1.5, 0, lado);
			    glVertex3f (0, 0, (lado/7)*4);
			    
			    
			    glNormal3f (0.0, -1.0, 0.0);
			    glVertex3f (lado/1.5, 0, 0);
			    glVertex3f (0, 0, (lado/7)*3);
			    
			    
			    glNormal3f (0.0, 0.0, -1.0);
			    glVertex3f (lado/1.5, 0.3, 0);
			    glVertex3f (0, 0.3, (lado/7)*3);
			    
			    
			    
			    glNormal3f (0.0, 1.0, 0.0);	
			    glVertex3f (lado/1.5, 0.3, lado);
			    glVertex3f (0, 0.3, (lado/7)*4);
			  }
		  	glEnd ();
		  	
		  	
		  	glBegin (GL_QUADS);
			  {				
			  
			    
			    glNormal3f (1.0, 0.0, 0.0);
			    glVertex3f (lado/1.5, 0, 0);
			    glVertex3f (lado/1.5, 0.3, 0);
			    glVertex3f (lado/1.5, 0.3, lado);
			    glVertex3f (lado/1.5, 0, lado);
			    
			    
			    
			    glNormal3f (-1.0, 0.0, 0.0);
			    glVertex3f (0, 0, (lado/7)*3);
			    glVertex3f (0, 0, (lado/7)*4);
			    glVertex3f (0, 0.3, (lado/7)*4);
			    glVertex3f (0, 0.3, (lado/7)*3);
			  }
		  	glEnd ();
		  
		 
		}



};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Cubo:public Objeto3D
{
private :
	float lado;
	
public: 


Cubo(float lado){
	this->lado = lado;
	}

void draw()
{
	
        
       
	glGenTextures( 1 , &idText );
	glBindTexture( GL_TEXTURE_2D ,idText ) ;
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP ) ;
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T, GL_CLAMP ) ;
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR ) ;
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR ) ;
	glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGB , ancho, alto, 0 ,GL_RGB ,GL_UNSIGNED_BYTE , textura ) ;
	
	
	
  	glBegin(GL_QUADS);
	    {				
	    
	    
	    //1**********************************
	    glNormal3f (0.0, 0.0, 1.0);	
	    
	    glTexCoord2f(0.5,0.5);
	    glVertex3f (lado,lado,lado);
	    
	    glTexCoord2f(0.5,0.75);
	    glVertex3f (0,lado,lado);
	    
	    glTexCoord2f(0.75,0.75);
	    glVertex3f (0, 0, lado);
	    
	    glTexCoord2f(0.75,0.5);
	    glVertex3f (lado, 0, lado);
	    
	    
	    //2**********************************************
	    glNormal3f (0.0, -1.0, 0.0);
	    
	    glTexCoord2f(1,0.5);
	    glVertex3f (lado, 0, 0);
	    
	    glTexCoord2f(0.75,0.5);
	    glVertex3f (lado, 0, lado);
	    
	    glTexCoord2f(0.75,0.75);
	    glVertex3f (0, 0, lado);
	    
	    glTexCoord2f(1,0.75);
	    glVertex3f (0, 0, 0);
	    
	    
	    
	    
	    
	    //3*********************************
	    glNormal3f (0.0, 0.0, -1.0);
	    
	    glTexCoord2f(0.25,0.5);
	    glVertex3f (lado,lado,0);
	    
	    glTexCoord2f(0,0.5);
	    glVertex3f (lado, 0, 0);
	    
	    glTexCoord2f(0,0.75);
	    glVertex3f (0, 0, 0);
	    
	    glTexCoord2f(0.25,0.75);
	    glVertex3f (0,lado,0);
	    
	    
	    
	    
	    
	    
	    //4************************************
	    glNormal3f (0.0, 1.0, 0.0);
	    
	    glTexCoord2f(0.25,0.5);
	    glVertex3f (lado, lado, 0);
	    
	    glTexCoord2f(0.25,0.75);
	    glVertex3f (0, lado, 0);
	    
	    glTexCoord2f(0.5,0.75);
	    glVertex3f (0, lado, lado);
	    
	    glTexCoord2f(0.5,0.5);
	    glVertex3f (lado, lado, lado);
	    
	    
		
	  
	    //5*****************************************************
	    glNormal3f (1.0, 0.0, 0.0);
	    
	    glTexCoord2f(0.75,0.25);
	    glVertex3f (lado, 0, 0);
	    
	    glTexCoord2f(0.5,0.25);
	    glVertex3f (lado, lado, 0);
	    
	    glTexCoord2f(0.5,0.5);
	    glVertex3f (lado, lado, lado);
	    
	    glTexCoord2f(0.75,0.5);
	    glVertex3f (lado, 0, lado);
	    
	    
	    //6*******************************************************
	    glNormal3f (-1.0, 0.0, 0.0);
	    
	    glTexCoord2f(0.75,1);
	    glVertex3f (0, 0, 0);
	    
	    glTexCoord2f(0.75,0.75);
	    glVertex3f (0, 0, lado);
	    
	    glTexCoord2f(0.5,0.75);
	    glVertex3f (0, lado, lado);
	    
	    glTexCoord2f(0.5,1);
	    glVertex3f (0, lado, 0);
	  }
  	glEnd ();
 
}



};



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Brazo:public Objeto3D{

	public:
		int contadorVecesDedosArriba;
		int contadorVecesDedosAbajo;
		int contadorDedosArriba;
		int contadorDedosAbajo;

		int contadorBajarAntebrazo;

		int contadorVecesIzquierda;
		int contadorVecesDerecha;
		int contadorSaludoIzquierda;
		int contadorSaludoDerecha;

		int contadorMano;

		bool estadoAnimacion;

		int anguloAntebrazo;
		int anguloSaludo;
		int anguloMano;
		int anguloDedos;
		
		Malla m = Malla("brazook22",false);
		mallaRevolucion m2= mallaRevolucion("perfil",8,true);
		Malla m3= Malla("antebrazo",false);
		Malla mpulgar = Malla("pulgar",false);
		Malla mdedos = Malla("dedos",false);
		CuboBrazo cubito = CuboBrazo (1.8);
	
//******************************************************************************************************************************************************************************************************
	
	
		Brazo(){
		
			contadorVecesDedosArriba = 0;
			contadorVecesDedosAbajo = 0;
			contadorDedosArriba = 0 ;
			contadorDedosAbajo = 0 ;

			contadorBajarAntebrazo = 0;

			contadorVecesIzquierda = 0;
			contadorVecesDerecha = 0;
			contadorSaludoIzquierda =45;
			contadorSaludoDerecha = 0;

			contadorMano = 0;

			estadoAnimacion = true;

			anguloAntebrazo = 0;
			anguloSaludo = 0;
			anguloMano = 0;
			anguloDedos = 0;
			

		}
		
//******************************************************************************************************************************************************************************************************
		
		void draw(){
			  float  color[4] = { 1.0, 1.0, 1.0, 0.0};
			  float  color1[4] = { 1.0, 0.0, 1.0, 0.0};
			  float  color2[4] = { 1.0, 0.0, 0.0, 0.0};
			  float  color3[4] = { 1.0, 1.0, 1.0, 0.0};
		  	  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3); 
			  m.draw();
			  
			  
			  
			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			  glTranslatef ( 2.2 , 0 , 0 );  
			  glRotatef(anguloAntebrazo ,0.0f,0.0f,1.0f);
			  glRotatef(anguloSaludo ,0.0f,1.0f,0.0f);
			  glPushMatrix();
			  glTranslatef ( 0 , -1 , 0 );  
			  m2.draw();   
			  
			  
			  
			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
			  glTranslatef ( 2.7 , 1 , 0 ); 
			  m3.draw(); 



			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
			  glTranslatef ( 4.1 , 0 , 0 );  
			  glRotatef(anguloMano ,1.0f,0.0f,0.0f);
			  glPushMatrix();
			  glTranslatef ( -1.7, -0.15 , -0.9 );  
			  cubito.draw(); 



			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
			  glTranslatef ( 0, 0 , 1 ); 
			  mpulgar.draw(); 
			  

			  
			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
			  glTranslatef ( 1.2 , 0.3 , 0.75 );  
			  glRotatef(anguloDedos ,0.0f,0.0f,1.0f);
			  glPushMatrix();
			  glTranslatef ( 0.0, -0.3 , -0.25 );
			  mdedos.draw(); 
			  
			  
			  
			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
			  glTranslatef ( 0, 0 , -0.5 ); 
			  mdedos.draw();
			  
			  
			  
			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
			  glTranslatef ( 0, 0 , -0.5 ); 
			  mdedos.draw();
			  
			  
			  
			  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
			  glTranslatef ( 0, 0 , -0.5 ); 
			  mdedos.draw();
			  

			  
			   glPopMatrix ();
			   glPopMatrix ();
			   glPopMatrix ();

		}

	    	void movimientoDedosArriba(){
			if(anguloDedos + 1 <= 180){
				anguloDedos += 1;
			}
		}

//******************************************************************************************************************************************************************************************************


		void movimientoDedosAbajo(){

			if(anguloDedos - 1 >= 0){
				anguloDedos -= 1;
			}
		}

//******************************************************************************************************************************************************************************************************


		void movimientoManoDerecha(){
			if(anguloMano == 0 ){
				anguloMano = 360;
				anguloMano -= 1;
			}
			else {
				anguloMano -= 1;
			}
		}

//******************************************************************************************************************************************************************************************************


		void movimientoManoIzquierda(){
			if(anguloMano == 360 ){
				anguloMano = 0;
				anguloMano += 1;
			}
			else {
				anguloMano += 1;
			}
		}

//******************************************************************************************************************************************************************************************************


		void saludoDerecha(){
			if(((anguloSaludo>315 && anguloSaludo<=360) || (anguloSaludo<=45 && anguloSaludo>=0))){
				if(anguloSaludo == 0 ){
					anguloSaludo = 360;
					anguloSaludo -= 1;
				}
				else{
					anguloSaludo -= 1;
				}
			}
		}

//******************************************************************************************************************************************************************************************************


		void saludoIzquierda(){
			if( ((anguloSaludo<45 && anguloSaludo>=0) || (anguloSaludo>=315 && anguloSaludo<=360))){
				if(anguloSaludo == 360 ){
					anguloSaludo = 0;
					anguloSaludo += 1;
				}
				else{
					anguloSaludo += 1;
				}
			}
		}

//******************************************************************************************************************************************************************************************************

		void levantaAntebrazo(){
			if(anguloAntebrazo + 1 <= 90){
				anguloAntebrazo += 1;
			}
		}

//******************************************************************************************************************************************************************************************************

		void bajaAntebrazo(){
			if(anguloAntebrazo - 1 >= 0){
				anguloAntebrazo -= 1;
			}
		}

//******************************************************************************************************************************************************************************************************


		void setAnimacion( bool estado){

			if(estado){
				estadoAnimacion= true;
			}
			else{
				estadoAnimacion= false;
			}
			
		}
//******************************************************************************************************************************************************************************************************


		bool estadoAnimacionFuction(){
			if(estadoAnimacion){
				return true;
			}
			else{
				return false;
			}
		}
//******************************************************************************************************************************************************************************************************

		void iniciarAnimacion(){

			

			
			if(anguloAntebrazo != 90 && contadorBajarAntebrazo==0){
				anguloAntebrazo += 1;
			}
			else if (contadorMano < 360){
				movimientoManoIzquierda();
				contadorMano++;
			}
			else if (contadorSaludoIzquierda < 90 && contadorVecesIzquierda < 4){
				saludoIzquierda();
				contadorSaludoIzquierda++;
				if(contadorSaludoIzquierda==90 ){
					contadorSaludoDerecha = 0;
					contadorVecesIzquierda++;
					
				}
			}
			else if (contadorSaludoDerecha < 90 && contadorVecesDerecha < 3){
				saludoDerecha();
				contadorSaludoDerecha++;
				if(contadorSaludoDerecha==90){
					contadorSaludoIzquierda = 0;
					contadorVecesDerecha++;
					if(contadorVecesIzquierda == 3){
						contadorSaludoIzquierda = 45;
					}
				}
			}
			
			else if ( contadorBajarAntebrazo < 45){
				
				contadorBajarAntebrazo++;
				anguloAntebrazo -=1;
			
			}
			
			else if (contadorDedosArriba < 90 && contadorVecesDedosArriba < 3){
				movimientoDedosArriba();
				contadorDedosArriba++;
				if(contadorDedosArriba==90 ){
					contadorDedosAbajo = 0;
					contadorVecesDedosArriba++;
					
				}
			}
			else if (contadorDedosAbajo < 90 && contadorVecesDedosAbajo < 3){
				movimientoDedosAbajo();
				contadorDedosAbajo++;
				if(contadorDedosAbajo==90){
					contadorDedosArriba = 0;
					contadorVecesDedosAbajo++;
				}
			
			}
			
			else if ( contadorBajarAntebrazo >= 45 && contadorBajarAntebrazo < 90){
				
				contadorBajarAntebrazo++;
				anguloAntebrazo -=1;
				}
			
			else if (contadorBajarAntebrazo = 90){
				inicializarAngulosContadores();
			}	
			
			
			
		}



//******************************************************************************************************************************************************************************************************


		void inicializarAngulosContadores(){

			//Con este if provoco que el objeto vuelva a la posicion inicial , cuando el programa lo requiera.
			if((anguloAntebrazo != 0 || (anguloSaludo !=0 && anguloSaludo != 360) ||(anguloMano != 0 && anguloMano !=360)|| anguloDedos != 0)){
				if(anguloAntebrazo != 0){
					anguloAntebrazo--;
				} 
				
				else if(anguloSaludo != 0 && anguloSaludo != 360){
					if(anguloSaludo <= 45 && anguloSaludo >0){
						anguloSaludo--;
					}
					else{
						anguloSaludo++;
					}
				}
				
				else if(anguloMano != 0 && anguloMano !=360){ //quitar 360
					//anguloMano--
					if(anguloMano <180){
						anguloMano--;
					}
					else{
					anguloMano++;
						if(anguloMano == 360){
							anguloMano=0;
						}
					}
				}
				
				else if(anguloDedos != 0){
					anguloDedos--;
				}
			}

			contadorVecesDedosArriba = 0;
		 	contadorVecesDedosAbajo = 0;
		 	contadorDedosArriba = 0 ;
		 	contadorDedosAbajo = 0 ;
		 	
		 	contadorBajarAntebrazo = 0;

		 	contadorVecesIzquierda = 0;
		 	contadorVecesDerecha = 0;
		 	contadorSaludoIzquierda =45;
		 	contadorSaludoDerecha = 0;

		 	contadorMano = 0;
		}

};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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
	float  color2[4] = { 1.0, 0.0, 0.0, 0.0};
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
	    glNormal3f (resultado1[0], resultado1[1], resultado1[2]); 
	    glVertex3f (lado/2 , altura, lado/2);
	    glVertex3f (0, 0, lado);	
	    glVertex3f (lado,0, lado);
	    
	    
	   float resultado2[3]={0.0,0.0,0.0}; 
	   
	   calculoNormal(lado/2.0 , altura , lado/2.0 ,lado , 0.0 , 0.0 ,0.0  , 0.0  , 0.0 ,  resultado2);
	    glNormal3f (resultado2[0], resultado2[1], resultado2[2]); 
	    glVertex3f (lado/2 , altura, lado/2);
	    glVertex3f (lado, 0, 0);
	    glVertex3f (0, 0, 0);
	    
	 
	 
	    float resultado3[3]={0.0,0.0,0.0};
	    
	    calculoNormal(lado/2.0 , altura , lado/2.0 ,lado , 0.0 , lado ,lado  , 0.0  , 0.0 ,  resultado3);
	    glNormal3f (resultado3[0], resultado3[1], resultado3[2]);
	    glVertex3f (lado/2 , altura, lado/2);
	    glVertex3f (lado, 0, lado);
	    glVertex3f (lado, 0, 0);
	    
	    
	    float resultado4[3]={0.0,0.0,0.0};
	    
	     calculoNormal(lado/2.0 , altura , lado/2.0 ,lado , 0.0 , 0.0 ,0.0  , 0.0  , lado,  resultado3);
	    glNormal3f (resultado3[0], resultado3[1], resultado3[2]);
	    glVertex3f (lado/2  , altura, lado/2); 
	    glVertex3f (0, 0, 0);
	    glVertex3f (0, 0, lado);

	  }
  	glEnd ();
  
 
}


};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++











//******************************************************************************************INICIO************************************************************************************************








const char cadena[] = "lata-pcue";
const char cadena2[] = "lata-pinf";
const char cadena3[] = "lata-psup";
mallaRevolucion lata = mallaRevolucion(cadena,10,true);
mallaRevolucion latasup(cadena2,10, true);
mallaRevolucion latainf(cadena3,10, true);
Cubo cubotextura(1.5);
Piramide piramideMaterial1(1,1);
Piramide piramideMaterial2(1,1);
Piramide piramideMaterial3(1,1);
Ejes ejesCoordenadas;
bool luz = true;


void modificaLuz(bool estado){luz = estado;}


void initModel(){
	cubotextura.aniadeTextura("dado.jpg",cubotextura.ancho,cubotextura.alto);
	lata.aniadeTextura("cocacola.jpg",lata.ancho,lata.alto);
}

void Dibuja (void)
{
	          float  color[4] = { 1.0, 1.0, 1.0, 0.0};
		  float  color1[4] = { 1.0, 0.0, 1.0, 0.0};
		  float  color2[4] = { 0.0, 1.0, 1.0, 1.0};
		  float  color3[4] = { 1.0, 1.0, 0.0, 0.0};
		  static GLfloat  pos[4] = { 3.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
		  static GLfloat  pos1[4] = { -3.0, -5.0, -10.0, 0.0 };
		  Especular(color2);
		  Difusa(color);
		  
		
		
		  glPushMatrix ();		// Apila la transformacion geometrica actual
		  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
		  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer
		  transformacionVisualizacion ();
		 
		  //***************************************************************Declaracion de dos focos de luz***********************************************************************************
		  //***************************************************************Azul por delante y amarilla por detras****************************************************************************
		  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
		  glLightfv (GL_LIGHT0, GL_DIFFUSE ,color2); 
		  
		  
		  glLightfv (GL_LIGHT1, GL_POSITION, pos1);	// Declaracion de luz. Colocada aqui esta fija en la escena
		  glLightfv (GL_LIGHT1, GL_AMBIENT ,color3); 
		  
		  //****************************************************************Apagar/Encender Focos de luz************************************************************************************** 
		  if(luz){
		  	glEnable( GL_LIGHT0 ) ;
		  	glEnable( GL_LIGHT1 ) ;
		  }
		  else{
		  	glDisable( GL_LIGHT0 ) ;
		  	glDisable( GL_LIGHT1 ) ;
		  }
		  
		  //*********************************************************************************************************************************************************************************



		  ejesCoordenadas.draw();			// Dibuja los ejes
		  /*
		 glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, vectorColorDifusa);
		 glMaterialfv (GL_FRONT, GL_DIFFUSE, vectorColorEspecular);
		 
		  */
		  glEnable( GL_TEXTURE_2D ) ;
		  cubotextura.draw();
		  glDisable( GL_TEXTURE_2D ) ;
		  
		 
		  glEnable( GL_TEXTURE_2D ) ;
		  glTranslatef ( 3 , 0 , 0 ); 
		  lata.draw();
		  glDisable( GL_TEXTURE_2D ) ;
		  
		  
		  latasup.draw();
		  latainf.draw();
		  
		 
		 
		 glTranslatef ( -3 , 3 , 0 );
		 //glMaterialfv (GL_FRONT, GL_DIFFUSE, color2);
		 piramideMaterial1.draw();
		 
		 
		 glTranslatef ( 1.5 , 0 , 0 );
		 //glMaterialfv (GL_FRONT, GL_SHININESS, color1);
		 piramideMaterial2.draw();
		 
		 glTranslatef ( 1.5 , 0 , 0 );
		 //glMaterialfv (GL_FRONT, GL_DIFFUSE, color3);
		 piramideMaterial3.draw();
		
		  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          

		  glPopMatrix ();		// Desapila la transformacion geometrica
                  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
		  //glDisable(GL_LIGHT0);



}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/



//******************************************************************************************************************************************************************************************************
//******************************************************************************************************************************************************************************************************



int contador1 = 0;

void idle (int v)
{
	/*
  if(b1.estadoAnimacionFuction()){
  	
	  	//En el caso de que la animación se haya activado lo primero que hago es llevar el objeto al origen
	  	//El contador1 me sirve para poder saber cuando el objeto ha alcanzado el origen y pueda seguir avanzando.
	  	if(contador1 == 0){
			 b1.inicializarAngulosContadores();
			 
			 if((b1.anguloAntebrazo == 0 && (b1.anguloSaludo ==0 || b1.anguloSaludo == 360) && (b1.anguloMano == 0 || b1.anguloMano ==360) && b1.anguloDedos == 0)){ contador1++; }
	  		       }
	  	else{
	  		b1.iniciarAnimacion();
	  	    }
	  	    
  	
 }
  else { contador1=0; }
 
  */
  glutPostRedisplay ();		// Redibuja
 //glutIdleFunc(iniciarAnimacion);
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
