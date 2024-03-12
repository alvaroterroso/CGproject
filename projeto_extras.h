//Ficheiro extras META1
//Álvaro Fontaínhas Terroso
//2021213782

//CÓDIGO FULL PROF
#include "ofMain.h"
#ifndef PROJETO_EXTRAS_H
#define PROJETO_EXTRAS_H

//short named function to put Frame Rate as window title
inline void setFrWt() {
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//short named function to get screen width
inline float gw() {
	return ofGetWidth();
}

//short named function to get screen height
inline float gh() {
	return ofGetHeight();
}

inline GLfloat getMultiNoise(float x, float y, float f[], float a[], int numBands) {
    float noise = 0;
    float maxAmp = 0.;

    for (int i = 0; i < numBands; i++) {
        noise += a[i] * ofNoise(f[i] * x, f[i] * y);
        maxAmp += a[i];
    }
    return noise / maxAmp;
}

//printa a ModelViewMatrix
inline void coutModelviewMatrix() {

	GLfloat Matriz[4][4];
	cout << endl << "Modelview Matrix" << endl;
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << Matriz[j][i] << " ";
		}
		cout << endl;
	}
	//return;
}

//print projectio matrix
inline void coutProjectionMatrix() {

	GLfloat Matriz[4][4];
	cout << endl << "Projection Matrix" << endl;
	glGetFloatv(GL_PROJECTION_MATRIX, &Matriz[0][0]);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << Matriz[j][i] << " ";
		}
		cout << endl;
	}
	//return;
}

//pega os valores de TranslaÁ„o da matriz modelview
inline ofVec3f getModelViewMatrixPos() {
	GLfloat Matriz[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);
	ofVec3f aux;
	aux.x = Matriz[3][0];
	aux.y = Matriz[3][1];
	aux.z = Matriz[3][2];
	//cout << endl << aux.x<<" "<<aux.y<<" "<<aux.z;
	return aux;
}

//print de matrix 4x4
inline void printMatrix(GLfloat m[][4]) {
	cout << endl << "Matrix 4x4" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << m[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl << "matrix" << endl;
}

//guardar vetors 3d
inline ofVec3f cross(ofVec3f A, ofVec3f B) {
	ofVec3f aux;
	aux.x = A.y * B.z - A.z * B.y;
	aux.y = A.z * B.x - A.x * B.z;
	aux.z = A.x * B.y - A.y * B.x;

	return aux;
}


#endif
