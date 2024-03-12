//Ficheiro extras META1
//Álvaro Fontaínhas Terroso 
//2021213782
#pragma once

#include "ofMain.h"
#include "projeto_extras.h"
#include "projeto_draw_extras.h"
#include "materials_textures.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void water_sketch();
    
        //images
        float ry, ry2;
        ofImage water;
        ofImage tester;
        ofImage normalMap;
        ofImage predio;
        ofImage esfero;
        ofImage cartao;
        ofImage pedra;
        ofImage metal;
        ofImage casa;
        ofImage vidro;
        ofImage batman;
        unsigned char* normalPixels = NULL;
    
        //water
        float waterTime; // Time accumulator for water animation
        float waterSpeedX; // Speed of water movement in X
        float waterSpeedY; // Speed of water movement in Y
            
        float phaseX;
        float phaseY;
        float freqs[10];
        float amps[10];
        vector<ofVec3f> vertexes;
        vector<ofVec3f> normals;
        vector<ofVec2f> texCoords;
            
		//floor
		GLint resX, resY;
		GLfloat floorWidth, floorHeight, floorHeightPos;

		//predio 1
		GLfloat p1W, p1D, p1H;
		GLint p1PosX, p1PosY;
		ofVec3f p1Pos;
		GLfloat windW, windH;
		GLfloat PwindWR, PwindWL, PwindD, PwindH;

		GLfloat PirStartX, PirStartY, PirSpace;

		//predio 2
		GLfloat p2W, p2D, p2H;

		//predio 3
		GLfloat p3W, p3D, p3H;
		GLfloat eW, eD, eH;
		GLfloat eboxW, eboxD, eboxH;
		GLfloat vel, elevadorZ;
		bool up;

		//piramide1
		GLfloat p4W, p4D, p4H;

		//piramide2
		GLfloat p5W, p5D, p5H;

		//piramide 3
		GLfloat p6W, p6D, p6H;

		//Ventoinha
		GLfloat angle;
		GLfloat vW, vD, vH;

		//predio 4
		GLfloat eaW, eaD, eaH;
		GLfloat p7W, p7D, p7H;
		GLfloat ebox7W, ebox7D, ebox7H;
		GLfloat ElevAutoZ;
		GLfloat velAuto;

		//predio 5
		GLfloat p8W, p8D, p8H;
		GLfloat pX8, pY8, pZ8;

		//view
		bool top, rotateCamara, perspectiva;
		float camaraAngle, camaraRaio, camaraHeight, camX, camY;
    
        //skybox
        GLfloat topAngle, maxAngle, leftTopAngle, rightTopAngle;
        bool isOpening, showBox;
        GLfloat sbX, sbY, sbZ;
		
        //lago
        GLfloat segments, in_raio, out_raio, l_height;
    
        //-----luzes----
        bool AmbP, DifP, SpecP, AmbD, DifD, SpecD, AmbF, DifF, SpecF, AmbC, DifC, SpecC;
        bool sun;
        GLfloat ambientLight[4];
        
        //direcional
        GLfloat dirVec[4];
        GLfloat dirAmb[4];
        GLfloat dirDif[4];
        GLfloat dirSpec[4];
        ofVec3f dirVec3f;
        GLfloat dirVecTheta;
        bool dirOn;
    
        //pontual
        GLfloat pointPos[4];
        GLfloat pointAmb[4];
        GLfloat pointDif[4];
        GLfloat pointSpec[4];
        GLfloat pointZtheta;
        GLfloat pointAtC, pointAtL, pointAtQ;
        bool pointOn;
    
        //foco
        GLfloat spotDir[3];
        GLfloat spotPos[4];
        GLfloat spotDif[4];
        GLfloat spotAmb[4];
        GLfloat spotSpec[4];
        GLfloat spotSpecular[4];
        GLfloat spotExponent;
        GLfloat spotCutoff;
        GLfloat spotTheta;
        GLfloat spotAtC, spotAtL, spotAtQ;
        bool spotOn;
    
        //batman sign
        GLfloat costumDir[3];
        GLfloat costumPos[4];
        GLfloat costumDif[4];
        GLfloat costumAmb[4];
        GLfloat costumSpec[4];
        GLfloat costumSpecular[4];
        GLfloat costumExponent;
        GLfloat costumCutoff;
        GLfloat costumTheta;
        GLfloat costumAtC, costumAtL, costumAtQ;
        GLfloat costumR, costumG, costumB;
        bool costumOn;
        bool cutoffOn;
        float random_color;
        GLfloat colorIncrement;
};
