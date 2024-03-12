//Ficheiro extras META1
//Álvaro Fontaínhas Terroso 
//2021213782
#pragma once
#include "ofMain.h"
#include "projeto_extras.h"
#include "materials_textures.h"
#include <cmath>
#ifndef PROJETO_DRAW_EXTRAS_H
#define PROJETO_DRAW_EXTRAS_H

//CÓDIGO PROF
inline void axis3d() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

inline void apply_texture(ofImage image){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    image.bind();
    glBegin(GL_QUADS);

    glTexCoord2f(0., 0.);
    glVertex3f(-0.5, -0.5, 0);

    glTexCoord2f(0., 1.);
    glVertex3f(-0.5, 0.5, 0);

    glTexCoord2f(1., 1.);
    glVertex3f(0.5, 0.5, 0);

    glTexCoord2f(1., 0.);
    glVertex3f(0.5, -0.5, 0);
        
    glEnd();
    image.unbind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


inline void square_unit() {
    GLfloat p = 0.5;
    glBegin(GL_QUADS);

    glVertex3f(-p, 0, p);
    glVertex3f(p, 0, p);
    glVertex3f(p, 0, -p);
    glVertex3f(-p, 0, -p);

    glEnd();
}

//CÓDIGO PROF
//função que desenha malha unitária com resolução mxn
inline void malha_unit(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_LINES);
	// Desenha linhas verticais
	for (int i = 0; i <= m; i++) {
		GLfloat x = i * x_step + x_start;
		glVertex2f(x, y_start);
		glVertex2f(x, y_start + 1.0);
	}
	// Desenha linhas horizontais
	for (int j = 0; j <= n; j++) {
		GLfloat y = j * y_step + y_start;
		glVertex2f(x_start, y);
		glVertex2f(x_start + 1.0, y);
	}
	glEnd();
}

inline void drawBoxTopHalf(bool isRightHalf, GLfloat p, GLfloat TopAngle, GLfloat scale, ofImage cartao) {
    GLfloat x = p; // x-coordinate for stationary vertices
    if (!isRightHalf) {
        x = -x;
    }

    // Calculate the angle for rotation
    GLfloat angle = isRightHalf ? TopAngle : -TopAngle;

    // Enable texturing and set texture parameters (if not set globally)
    cartao.bind();

    // Drawing the half-box top with rotation around the edge
    glPushMatrix();
    
    // Translate to the edge (A or C) for rotation
    glTranslatef(x, p, p);
    
    // Rotate around the y-axis
    glRotatef(angle, 0, 1, 0);
    
    // Translate back from the edge to the original center position
    glTranslatef(-x, -p, -p);
    
    // Draw the square that represents the half of the box top with texture
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(x, p, p);         // Corner A or C
    glTexCoord2f(1, 0); glVertex3f(x, p, - x/scale);  // Adjusted to ensure the size is equal
    glTexCoord2f(1, 1); glVertex3f(x, -p, - x/scale); // Opposite corner of the square
    glTexCoord2f(0, 1); glVertex3f(x, -p, p);        // Back to starting corner
    glEnd();
    
    cartao.unbind();
    glPopMatrix();
}

inline void apply_texture_to_face(ofImage &cartao, GLfloat p1, GLfloat p2, GLfloat p3, GLfloat p4, GLfloat q1, GLfloat q2, GLfloat q3, GLfloat q4, GLfloat r1, GLfloat r2, GLfloat r3, GLfloat r4){
    cartao.bind();
    glTexCoord2f(0., 0.); glVertex3f(p1, q1, r1);
    glTexCoord2f(1., 0.); glVertex3f(p2, q2, r2);
    glTexCoord2f(1., 1.); glVertex3f(p3, q3, r3);
    glTexCoord2f(0., 1.); glVertex3f(p4, q4, r4);
    cartao.unbind();
}


inline void caixa_skybox(GLfloat topAngle, GLfloat xScale, GLfloat yScale, GLfloat zScale, bool showBox, GLfloat scale, ofImage cartao){
    
    if (!showBox) return;
    
    GLfloat p = 0.5;
    
    //frente
    /*
     glPushMatrix();
         glTranslated(0., 0., p);
         //glScaled(m, n, 1.0);
         apply_texture(cartao);
     glPopMatrix();
     */
    // Frente
    cartao.bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    //frente
    glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0., 0.);   glVertex3f(-p, -p, p);
        glTexCoord2f(1., 0.);   glVertex3f(-p, -p, -p);
        glTexCoord2f(1., 1.);   glVertex3f(p, -p, -p);
        glTexCoord2f(0., 1.);   glVertex3f(p, -p, p);
    glEnd();
    glPopMatrix();

    //tras
    glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0., 0.);   glVertex3f(-p, -p, -p);
        glTexCoord2f(1., 0.);   glVertex3f(p, -p, -p);
        glTexCoord2f(1., 1.);   glVertex3f(p, p, -p);
        glTexCoord2f(0., 1.);   glVertex3f(-p, p, -p);
    glEnd();
    glPopMatrix();

    //baixo
    glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0., 0.);   glVertex3f(-p, p, p);
        glTexCoord2f(1., 0.);   glVertex3f(-p, p, -p);
        glTexCoord2f(1., 1.);   glVertex3f(p, p, -p);
        glTexCoord2f(0., 1.);   glVertex3f(p, p, p);
    glEnd();
    glPopMatrix();

    //esq
    glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0., 0.);   glVertex3f(-p, -p, p);
        glTexCoord2f(1., 0.);   glVertex3f(-p, -p, -p);
        glTexCoord2f(1., 1.);   glVertex3f(-p, p, -p);
        glTexCoord2f(0., 1.);   glVertex3f(-p, p, p);
    glEnd();
    glPopMatrix();

    //dir
    glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0., 0.);   glVertex3f(p, -p, p);
        glTexCoord2f(1., 0.);   glVertex3f(p, p, p);
        glTexCoord2f(1., 1.);   glVertex3f(p, p, -p);
        glTexCoord2f(0., 1.);   glVertex3f(p, -p, -p);
    glEnd();
    glPopMatrix();

    cartao.unbind();
    
    glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        drawBoxTopHalf(true, p,topAngle,scale,cartao); // Right half
        drawBoxTopHalf(false, p, topAngle,scale, cartao); // Left half
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnd();
    glPopMatrix();

}


//CÓDIGO PROF
inline void cube_unit() {
	GLfloat p = 0.5;
	glBegin(GL_QUADS);

	//frente
	glVertex3f(-p, -p, p);
	glVertex3f(-p, p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, -p, p);

	//tras
	glVertex3f(-p, -p, -p);
	glVertex3f(p, -p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(-p, p, -p);

	//cima
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, -p, p);
	glVertex3f(p, -p, p);
	glVertex3f(p, -p, -p);

	//baixo
	glVertex3f(-p, p, p);
	glVertex3f(-p, p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(p, p, p);

	//esq
	glVertex3f(-p, -p, p);
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, p, -p);
	glVertex3f(-p, p, p);

	//dir
	glVertex3f(p, -p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, p, -p);
	glVertex3f(p, -p, -p);

	glEnd();

}

inline void lamina_ventoinha() {
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0); // Centro no topo do poste
	glVertex3f(-0.1, 0, -0.40); // Extremidade esquerda da lâmina
	glVertex3f(0.1, 0, -0.40); // Extremidade direita da lâmina
	glEnd();
}

inline void ventoinha(GLfloat angle) {
	//glRotatef(, 0, 0, 1);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0); // Base do poste
	glVertex3f(0, 0, 1); // Topo do poste
	glEnd();

	// Desenhar as lâminas
	for (int i = 0; i < 3; ++i) { // Três lâminas
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glTranslatef(0, 0, 1); // Move o centro de rotação para o topo do poste
		glRotatef(angle + i * 120, 0, 1, 0); // Rotação das lâminas
		lamina_ventoinha();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPopMatrix();
	}
}

inline void predio_cubos_malhados(GLint n) {
	GLfloat l = 1;
	for (int k = 0; k < n; k++) { // Height
		for (int i = 0; i < n; i++) { // Depth
			for (int j = 0; j < n; j++) { // Width
				glPushMatrix(); // Save the current transformation matrix
				// Translate to the correct location
				glTranslatef(j * l, i * l, k * l);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				cube_unit(); // Draw the cube at the current location
				glPopMatrix(); // Restore the transformation matrix
			}
		}
	}
}

// Draws a unit cube made of unit malhas centered in the origin
inline void cube_malha_unit(GLint m, GLint n) {
	GLfloat p = 0.5;
    
	// frente
	glPushMatrix();
		glTranslated(0., 0., p);
		malha_unit(m, n);
	glPopMatrix();

	// tras
	glPushMatrix();
		glTranslated(0., 0., -p);
		glRotated(180, 0, 1, 0);
		malha_unit(m, n);
	glPopMatrix();

	// topo
	glPushMatrix();
		glTranslated(0., -p, 0.);
		glRotated(90, 1, 0, 0);
		malha_unit(m, n);
	glPopMatrix();

	// baixo
	glPushMatrix();
		glTranslated(0., p, 0.);
		glRotated(-90, 1, 0, 0);
		malha_unit(m, n);
	glPopMatrix();

	// esquerda
	glPushMatrix();
		glTranslated(-p, 0., 0.);
		glRotated(-90, 0, 1, 0);
		malha_unit(m, n);
	glPopMatrix();

	// direita
	glPushMatrix();
		glTranslated(p, 0., 0.);
		glRotated(90, 0, 1, 0);
		malha_unit(m, n);
	glPopMatrix();
}

inline void predio_malhado(float m, float n) {
	cube_malha_unit(m, n);
}

inline void piramide(GLint n, GLfloat p4W, GLfloat p4D, GLfloat p4H) {
	GLfloat stepW = p4W / n; // Passo para diminuir a largura para cada andar
	GLfloat stepD = p4D / n; // Passo para diminuir a profundidade para cada andar
	GLfloat currentW = p4W;
	GLfloat currentD = p4D;
	GLfloat currentH = 0; // Iniciar do chão

	for (int i = 0; i < n; i++) {
		glPushMatrix(); // Salva a matriz de transformação atual
		glTranslatef(0, 0, currentH + (p4H / n) / 2);// Posiciona o andar atual na altura correta
		glScalef(currentW, currentD, p4H / n);// Aplica a escala para o andar atual
		cube_unit(); // Desenha o andar atual
		glPopMatrix(); // Restaura a matriz de transformação
		// Atualiza as dimensões para o próximo andar
		currentW -= stepW;
		currentD -= stepD;
		currentH += p4H / n; // Aumenta a altura para o próximo andar
	}
}

inline void predio_texture(GLfloat m, GLfloat n, ofImage image){
    GLfloat p = 0.5;
    GLfloat q = 0.5;

    // Frente
    glPushMatrix();
        glTranslated(0., 0., q);
        //glScaled(m, n, 1.0);
        apply_texture(image);
    glPopMatrix();

    // Tr‡s
    glPushMatrix();
        glTranslated(0., 0., -q);
        //glScaled(m, n, 1.0);
        glRotated(180, 0, 1, 0);
        apply_texture(image);
    glPopMatrix();

    // Topo
    glPushMatrix();
        glTranslated(0., -q, 0.);
        //glScaled(m, 1.0, n);
        glRotated(90, 1, 0, 0);
        apply_texture(image);
    glPopMatrix();

    // Baixo
    glPushMatrix();
        glTranslated(0., q, 0.);
        //glScaled(m, 1.0, n);
        glRotated(-90, 1, 0, 0);
        apply_texture(image);
    glPopMatrix();

    // Esquerda
    glPushMatrix();
        glTranslated(-p, 0., 0.);
        //glScaled(1.0, n, m);
        glRotated(-90, 0, 1, 0);
        apply_texture(image);
    glPopMatrix();

    // Direita
    glPushMatrix();
        glTranslated(p, 0., 0.);
        //glScaled(1.0, n, m);
        glRotated(90, 0, 1, 0);
        apply_texture(image);
    glPopMatrix();

}

inline void drawPool(GLfloat X, GLfloat Y, GLfloat Z, ofImage pedra){
    
    // Draw the walls of the pool (4 sides)
    // back
    glPushMatrix();
        glTranslated(0, - Y*2 + 5 , 0); // Move to the front edge
        glScaled(X, Y, 20.0);
        glRotated(-90, 1, 0, 0); // Rotate to make vertical
        predio_texture(5, 3, pedra); // Draw a grid representing the wall
    glPopMatrix();
    
    // right
    glPushMatrix();
        glTranslated(60, 0, 0); // Move to the back edge
        glScaled(Y, X-10, 20.0);
        glRotated(0, 1, 0, 0); // Rotate to make vertical
        predio_texture(5, 3, pedra); // Draw a grid representing the wall
    glPopMatrix();

    // front
    glPushMatrix();
        glTranslated(0, Y*2 - 5, 0); // Move to the left edge
        glScaled(X, Y, 20.0);
        glRotated(90, 0, 1, 0); // Rotate to make vertical
        predio_texture(5, 3, pedra); // Draw a grid representing the wall
    glPopMatrix();

    // left
    glPushMatrix();
        glTranslated(-60, 0, 0); // Move to the right edge
        glScaled(Y, X-10, 20.0);
        glRotated(-90, 0, 1, 0); // Rotate to make vertical
        predio_texture(5, 3, pedra); // Draw a grid representing the wall
    glPopMatrix();


}

inline void floor_texture(ofImage img){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    img.bind();
    glPushMatrix();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);//coordenada de textura
    glVertex3f(-0.5, 0.5, 0);//vertex(x, y, z)

    glTexCoord2f(0, 1);//coordenada de textura
    glVertex3f(-0.5, -0.5, 0);//vertex(x, y, z)

    glTexCoord2f(1, 1);//coordenada de textura
    glVertex3f(0.5, -0.5, 0);//vertex(x, y, z)

    glTexCoord2f(1, 0);//coordenada de textura
    glVertex3f(0.5, 0.5, 0);//vertex(x, y, z)

    glEnd();
    glPopMatrix();

    img.unbind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

inline void drawCircle(float radius, int segments) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; i++) {
        float angle = 2 * M_PI * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0);
    }
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


//CÓDIGO PROF
//implementa o algoritmo de lookAt
inline void lookat(
	GLfloat camX,
	GLfloat camY,
	GLfloat camZ,
	GLfloat targetX,
	GLfloat targetY,
	GLfloat targetZ,
	GLfloat upX,
	GLfloat upY,
	GLfloat upZ)
{
	ofVec3f cam = ofVec3f(camX, camY, camZ);
	ofVec3f target = ofVec3f(targetX, targetY, targetZ);
	ofVec3f up = ofVec3f(upX, upY, upZ);


	ofVec3f N = cam - target;
	N = N.normalized();
	ofVec3f U = cross(up, N);
	U = U.normalized();
	ofVec3f V = cross(N, U);
	V = V.normalized();

	/*GLfloat camTransformMatrix[4][4] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};*/

	GLfloat camTransformMatrix[4][4] = {
		{U.x, V.x, N.x, 0},
		{U.y, V.y, N.y, 0},
		{U.z, V.z, N.z, 0},
		{-U.dot(cam), -V.dot(cam), -N.dot(cam), 1}
	};

	/*camTransformMatrix[0][0] = U.x;
	camTransformMatrix[1][0] = U.y;
	camTransformMatrix[2][0] = U.z;
	camTransformMatrix[0][1] = V.x;
	camTransformMatrix[1][1] = V.y;
	camTransformMatrix[2][1] = V.z;
	camTransformMatrix[0][2] = N.x;
	camTransformMatrix[1][2] = N.y;
	camTransformMatrix[2][2] = N.z;
	camTransformMatrix[3][0] = -U.dot(cam);
	camTransformMatrix[3][1] = -V.dot(cam);
	camTransformMatrix[3][2] = -N.dot(cam);*/


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(&camTransformMatrix[0][0]);
	//glTranslatef(-cam.x, -cam.y, -cam.z);
}

//CÓDIGO PROF
//calcula o frustum com base em theta, alpha e beta
inline void perspective(GLfloat theta, GLfloat alpha, GLfloat beta, bool invertX = false, bool invertY = false) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat tan = tanf(theta * 0.5 * PI / 180.0);
	GLfloat d = (gh() / 2.0) / tan;
	GLfloat nearClip = d / alpha;
	GLfloat farClip = d * beta;
	GLfloat ymax = nearClip * tan;
	GLfloat xmax = (gw() / gh()) * ymax;
	if (invertX) {
		xmax = -xmax;
	}
	if (invertY) {
		ymax = -ymax;
	}
	glFrustum(-xmax, xmax, -ymax, ymax, nearClip, farClip);
}

//CÓDIGO PROF
inline void lookat(ofVec3f cam, ofVec3f look, ofVec3f up) {
	lookat(cam.x, cam.y, cam.z, look.x, look.y, look.z, up.x, up.y, up.z);
}

#endif // PROJETO_DRAW_EXTRAS_H
