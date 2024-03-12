//Ficheiro extras META1
//Álvaro Fontaínhas Terroso 
//2021213782
#include "ofApp.h"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();//para utilizar coordenadas de textura normalizadas
	coutModelviewMatrix();
    coutProjectionMatrix();
	ofBackground(0.05, 0.05, 0.05);
	glLineWidth(2);
    glEnable(GL_DEPTH_TEST);
    
    waterTime = 0.0; // Time accumulator for water animation
    phaseX = .0;
    phaseY = .0;
    
	//view
    isOpening = false;
    topAngle = 90.0f;
	top = false;
	up = true;
    showBox = true;
	rotateCamara = false;
	perspectiva = true;
	camaraAngle = 0;
	camaraRaio = 300;
	camaraHeight = 400;
    maxAngle = 270.0f;
    costumOn = false;
    
    //lights
    AmbD = true;
    DifD = true;
    SpecD = true;
    AmbF = true;
    DifF = true;
    SpecF = true;
    AmbP = true;
    DifP = true;
    SpecP = true;
    AmbC = true;
    DifC = true;
    SpecC = true;
    pointOn = false;
    spotOn = false;
    dirOn = false;
    sun = false;
    pointZtheta = 0;
    spotExponent = 0;
    spotCutoff = 180;;
    costumExponent = 0;
    costumCutoff = 0;
    cutoffOn = true;
    colorIncrement = 0.01f;
    costumR = 1.0;
    costumG = 1.0;
    costumB = 1.0;

    
	// ---> CHANGE BUILDINGS WEIGHT, WIDTH, DEPTH HERE

	//floor parameters1
	resX = 15;
	resY = 10;
	floorWidth = gw()* 1.2;
	floorHeight = gh() * 0.60;
	floorHeightPos = 0.;//gh() * 0.75;

	//glTranslatef(-300, -100, p1H / 2);

	//predio1
	p1W = 55;
	p1D = 50;
	p1H = 200;
	PwindWL = -292;
	PwindWR = -284;
	PwindD = -75;
	PwindH = 150;
	windW = 8;
	windH = 10;

	//predio2
	p2W = 70;
	p2D = 90;
	p2H = 300;

	//predio3 (elevador manual)
	p3W = 60;
	p3D = 60;
	p3H = 200;
	eboxW = 20;
	eboxD = 20;
	eboxH = 200;
	eW = 20;
	eD = 20;
	eH = 30;
	elevadorZ = 30;
	vel = 1.0;

	//primeira piramide
	p4W = 100;
	p4D = 100;
	p4H = 100;

	//segunda piramide
	p5W = 150;
	p5D = 150;
	p5H = 150;

	//terceira piramide
	p6W = 125;
	p6D = 125;
	p6H = 125;

	//ventoinha
	vW = 125;
	vD = 20;
	vH = 200;

	//predio4 (elevado automatico)
	p7W = 60;
	p7D = 60;
	p7H = 300;
	ebox7W = 20;
	ebox7D = 20;
	ebox7H = 300;
	eaW = 20;
	eaD = 20;
	eaH = 30;
	ElevAutoZ = 30;
	velAuto = 1.0;

	//predio 5 (malhado)
	
	p8H = 250;
	p8D = 60;
	p8W = 70;
	pX8 = -200;
	pY8 = 150;
	pZ8 = p8H / 2;
    
    //skybox
    sbX = floorWidth * 2;
    sbY = floorHeight * 2;
    sbZ = 500;
    
    //lago
    segments = 32;
    in_raio = 40;
    l_height = 30;
	
    //IMAGES
    if (!water.load("water.jpg")) {
        ofLogError("ofApp::setup") << "Could not load image from water.jpg";
    }
    ry = 0.;
    normalMap.load("normalMap.jpg");
    predio.load("predio.jpg");
    esfero.load("esferovite.jpg");
    cartao.load("cartao.jpg");
    pedra.load("albedo.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    std::random_device rd;
    std::mt19937 eng(rd()); // Mersenne Twister 19937 generator, seeded with rd()
    std::uniform_real_distribution<> distr(0, 1);
    
    //------- UPDATE CUTOFF-----------
    if(cutoffOn){
        if(costumCutoff < 90){
            costumCutoff += 0.10;
        }else{
            cutoffOn = !cutoffOn;
        }
    }else{
        if(costumCutoff > 0){
            costumCutoff -= 0.10;
        }else{
            random_color = distr(eng);
            costumR = random_color;
            random_color = distr(eng);
            costumB = random_color;
            random_color = distr(eng);
            costumG = random_color;
            cutoffOn = !cutoffOn;
        }
    }
    
	//----------- UPDATE ANGULO VENTOINHA --------

	angle += 1.0f; // Aumenta o ângulo para a rotação das lâminas
	if (angle > 360.0f) {
		angle -= 360.0f; // Mantém o ângulo dentro de um intervalo de 360 graus
	}
    
	//----------- UPDATE ELEVADOR AUTOMATICO -----------
	if (up) {
		if (ElevAutoZ > ebox7H - eaH/2) {
			ElevAutoZ = ebox7H - eaH/2;
			up = false; 

		}
		else {
			ElevAutoZ += velAuto;
		}
	}
	else {
		if (ElevAutoZ < eaH/2) {
			ElevAutoZ = eaH / 2;
			up = true;
		}
		else {
			ElevAutoZ -= velAuto;
		}
	}

	//---------- UPDATE CAMARA ROTATION -------------

	if (rotateCamara) {
		camaraAngle += 0.25f;
		if (camaraAngle > 360.0f) {
			camaraAngle -= 360.0f;
		}
	}
    
    //--------- SKYBOX TOP OPENING ------------------

    if (isOpening && topAngle < maxAngle) {
            topAngle += 1.0f; // Open the top
        } else if (!isOpening && topAngle > 90.0f) {
            topAngle -= 1.0f; // Close the top
        }
    
    //------- SUN ------
    if(sun){
        //calculo da posicao da luz pontual
        pointPos[0] = 300 * cos(pointZtheta * PI / 180.0);
        pointPos[1] = 300 * sin(pointZtheta * PI / 180.0);
        pointPos[2] = 500;
        pointZtheta += 0.75;

    }else{
        
        pointPos[0] = 0;
        pointPos[1] = 0;
        pointPos[2] = 500;
        
        dirVec3f = ofVec3f(0, 0, 600);
        
        spotDir[0] = 0;
        spotDir[1] = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);//clear buffer
	glEnable(GL_DEPTH_TEST);

	// --------- TIPO DE CAMARA ----------
	// --------- GLPROJECTION ------------

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (perspectiva) {
		const GLfloat angle = 135;
		const GLfloat a = 2.0f * (gw() / gh());
		const GLfloat b = 100.0f;
		perspective(angle, a, b, true, false);
	}else if (!perspectiva) {
		// Orthogonal Projection
		glOrtho(gw()/2, -gw()/2, -gh()/2,gh()/2, -1000.0, 1000.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//------------ MODEL VIEW --------------

	if (top) {
		lookat(0, 0, 600, // Camera is above the scene at z=600
			0, 0, 0,   // Looking at the origin
			0, -1, 0);  // Y is up
	}
	else if (rotateCamara) {
		camX = cos(ofDegToRad(camaraAngle)) * camaraRaio;
		camY = sin(ofDegToRad(camaraAngle)) * camaraRaio;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		lookat(-camX, camY, camaraHeight, 
			0, 0, 0,                  
			0, 0, 1);
	}else {
		lookat(0, 400, 800, 0, 0, 0, 0, 0, 1);
	}
    
    //------------- ILUMINA‚ÌO ---------------------
    //inicia iluminacao
    glEnable(GL_LIGHTING);//habilita o uso de iluminação
    glEnable(GL_NORMALIZE);//utiliza versores para normais (normais normalizadas)
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, true);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    
    //-------------POSIC‚ÌO DA LUZ PONTUAL-----------
    dirVec[0] = dirVec3f.x;//x
    dirVec[1] = dirVec3f.y;//y
    dirVec[2] = dirVec3f.z;//z
    dirVec[3] = 0;//vetor - direção!
    
    //--------POSI‚ÌO & DIRE‚ÌO DA LUZ FOCO--------------
    spotPos[0] = 0;
    spotPos[1] = 0;
    spotPos[2] = 800;
    spotPos[3] = 1.;
    
    spotDir[0] = 0;
    spotDir[1] = 0;
    spotDir[2] = -1;
    
    //------------POSI‚ÌO & DIRE‚ÌO DA LUZ BATMAN---------
    costumPos[0] = 0;
    costumPos[1] = 0;
    costumPos[2] = 800;
    costumPos[3] = 1.;
    
    costumDir[0] = 0;
    costumDir[1] = 0;
    costumDir[2] = -1;
    
    //--------COMPONENTES LUZ PONTUAL-------
    
    if(AmbP){
        pointAmb[0] = 1.;//R
        pointAmb[1] = 1.;//G
        pointAmb[2] = 1.;//B
        pointAmb[3] = 1.;//constante
    }else{
        pointAmb[0] = 0.;//R
        pointAmb[1] = 0.;//G
        pointAmb[2] = 0.;//B
        pointAmb[3] = 1.;//constante
    }
    if(DifP){
        pointDif[0] = 1.;//R
        pointDif[1] = 1.;//G
        pointDif[2] = 1.;//B
        pointDif[3] = 1.;//constante
    }else{
        pointDif[0] = 0.;//R
        pointDif[1] = 0.;//G
        pointDif[2] = 0.;//B
        pointDif[3] = 1.;//constante
    }
    if(SpecP){
        pointSpec[0] = 1.;//R
        pointSpec[1] = 1.;//G
        pointSpec[2] = 1.;//B
        pointSpec[3] = 1.;//constante
    }else{
        pointSpec[0] = 0.;//R
        pointSpec[1] = 0.;//G
        pointSpec[2] = 0.;//B
        pointSpec[3] = 1.;//constante
    }
    
    //--------COMPONENTES LUZ DIRECIONL-------
    
    if(AmbD){
        dirAmb[0] = 1.;//R
        dirAmb[1] = 1.;//G
        dirAmb[2] = 1.;//B
        dirAmb[3] = 1.;//constante
    }else{
        dirAmb[0] = 0.;//R
        dirAmb[1] = 0.;//G
        dirAmb[2] = 0.;//B
        dirAmb[3] = 1.;//constante
    }
    if(DifD){
        dirDif[0] = 1.;//R
        dirDif[1] = 1.;//G
        dirDif[2] = 1.;//B
        dirDif[3] = 1.;//constante
    }else{
        dirDif[0] = 0.;//R
        dirDif[1] = 0.;//G
        dirDif[2] = 0.;//B
        dirDif[3] = 1.;//constante
    }
    if(SpecD){
        dirSpec[0] = 1.;//R
        dirSpec[1] = 1.;//G
        dirSpec[2] = 1.;//B
        dirSpec[3] = 1.;//constante
    }else{
        dirSpec[0] = 0.;//R
        dirSpec[1] = 0.;//G
        dirSpec[2] = 0.;//B
        dirSpec[3] = 1.;//constante
    }
    
    //---------COMPONENTES LUZ FOCO--------
    
    if(AmbF){
        spotAmb[0] = 1.;//R
        spotAmb[1] = 1.;//G
        spotAmb[2] = 1.;//B
        spotAmb[3] = 1.;//constante
    }else{
        spotAmb[0] = 0.;//R
        spotAmb[1] = 0.;//G
        spotAmb[2] = 0.;//B
        spotAmb[3] = 1.;//constante
    }
    if(DifF){
        spotDif[0] = 1.;//R
        spotDif[1] = 1.;//G
        spotDif[2] = 1.;//B
        spotDif[3] = 1.;//constante
    }else{
        spotDif[0] = 0.;//R
        spotDif[1] = 0.;//G
        spotDif[2] = 0.;//B
        spotDif[3] = 1.;//constante
    }
    if(SpecF){
        spotSpec[0] = 1.;//R
        spotSpec[1] = 1.;//G
        spotSpec[2] = 1.;//B
        spotSpec[3] = 1.;//constante
    }else{
        spotSpec[0] = 0.;//R
        spotSpec[1] = 0.;//G
        spotSpec[2] = 0.;//B
        spotSpec[3] = 1.;//constante
    }
    
    //--------COMPONENTE DA LUZ COSTUM---------
    
    if(AmbC){
        costumAmb[0] = costumR;//R
        costumAmb[1] = costumG;//G
        costumAmb[2] = costumB;//B
        costumAmb[3] = 1.;//constante
    }else{
        costumAmb[0] = 0.;//R
        costumAmb[1] = 0.;//G
        costumAmb[2] = 0.;//B
        costumAmb[3] = 1.;//constante
    }
    if(DifC){
        costumDif[0] = costumR;//R
        costumDif[1] = costumG;//G
        costumDif[2] = costumB;//B
        costumDif[3] = 1.;//constante
    }else{
        costumDif[0] = 0.;//R
        costumDif[1] = 0.;//G
        costumDif[2] = 0.;//B
        costumDif[3] = 1.;//constante
    }
    if(SpecC){
        costumSpec[0] = costumR;//R
        costumSpec[1] = costumG;//G
        costumSpec[2] = costumB;//B
        costumSpec[3] = 1.;//constante
    }else{
        costumSpec[0] = 0.;//R
        costumSpec[1] = 0.;//G
        costumSpec[2] = 0.;//B
        costumSpec[3] = 1.;//constante
    }
    
    glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);
    
    glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);
    
    glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
    glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);
    glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpecular);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);
    
    glLightfv(GL_LIGHT3, GL_POSITION, costumPos);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, costumDir);
    glLightfv(GL_LIGHT3, GL_AMBIENT, costumAmb);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, costumDif);
    glLightfv(GL_LIGHT3, GL_SPECULAR, costumSpecular);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, costumExponent);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, costumCutoff);
    
    
    //-------- ATIVAR A LUZ PONTUAL------------
    if (pointOn) {
        glEnable(GL_LIGHT1);
    }else{
        glDisable(GL_LIGHT1);
    }
    //-----------ATIVAR A LUZ DIRECIONAL--------
    
    if(dirOn){
        glEnable(GL_LIGHT0);
    }else{
        glDisable(GL_LIGHT0);
    }
    
    //-----------ATIVAR A LUZ FOCO---------
    
    if(spotOn){
        glEnable(GL_LIGHT2);
    }else{
        glDisable(GL_LIGHT2);
    }
    
    //--------------ATIVAR A LUZ COSTUM-----------
    
    if(costumOn){
        glEnable(GL_LIGHT3);
    }else{
        glDisable(GL_LIGHT3);
    }
    
    glEnable(GL_TEXTURE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// --------- CHAMADA DAS CONSTRUCOES
	//  ----------- MASTER PUSH ---------------
	glPushMatrix();
    
    //floor push
    glPushMatrix();
        loadMaterial(16);
        glScalef(floorWidth, floorHeight, 1.0);
        floor_texture(esfero);
    glPopMatrix();
	
	//---------- PREDIO 1 -----------
    glPushMatrix();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    loadMaterial(1);
	glTranslatef(-300, -100, p1H / 2);//posição no tabuleiro + above ground
	glScalef(p1W, p1D, p1H);
	cube_unit();
	glPopMatrix();// p1 pop
        //JANELA DIREITA
        glPushMatrix();
        loadMaterial(2);
        glTranslatef(PwindWR, PwindD+1, PwindH);
        glScalef(windW, 0, windH);
        square_unit();
        glPopMatrix();
        //JANELA ESQUERDA
        glPushMatrix();
        loadMaterial(2);
        glTranslatef(PwindWL, PwindD+1, PwindH);
        glScalef(windW, 0, windH);
        square_unit();
        glPopMatrix();
        //INTERIOR
		glPushMatrix();
        loadMaterial(11);
		glTranslatef(-288, -74, 150);
		glScalef(windW, 0, windH);
        square_unit();
        //apply_texture(casa);
		glPopMatrix();
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPopMatrix();
	
	//--------- PREDIO 2 (composto por cubos) -----------------

	glPushMatrix();
        GLint n = 3; //n lados
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        loadMaterial(2);
        glTranslatef(-200, -100, (p2H / n)/2);
        GLfloat cubeScaleW = p2W;
        GLfloat cubeScaleD = p2D;
        GLfloat cubeScaleH = p2H;
        glScalef(cubeScaleW, cubeScaleD, cubeScaleH);// Apply the scale for each cube
        cube_unit(); // This will draw the building as a 5x5x5 grid of wireframe cubes
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPopMatrix();

	//------- PREDIO ELEVADOR MANUAL ----------
    glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        loadMaterial(6);
        glTranslatef(300, 100, p3H / 2);//posicao no tabuleiro + above ground
        glScalef(p3W, p3D, p3H);
        cube_unit();
        glPopMatrix();
        //caixa de translação
        glPushMatrix();
        glTranslatef(285, 85, eboxH / 2);
        glScalef(eboxW, eboxD, eboxH);
        cube_unit();
        glPopMatrix();
        //caixa do elevador
        glPushMatrix();
        loadMaterial(1);
        glTranslatef(285, 85, elevadorZ);
        glScalef(eW, eD, eH);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPopMatrix();

	//---------- PIRAMIDES --------

	PirStartX = 200;
	PirStartY = -150;
	PirSpace = 10;
	
	//------PRIMEIRA------
	n = 7; // n de andares
	glPushMatrix();
    loadMaterial(10);
	glTranslatef(PirStartX, PirStartY, 0); //(p4H/n)/2
	//preenchimento
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	piramide(n, p4W, p4D, p4H);
	//contorno
    loadMaterial(9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	piramide(n, p4W, p4D, p4H);
	glPopMatrix();
	
	//------SEGUNDA--------
	PirStartX += p4W + PirSpace + 25;
	n = 10; // n de andares
	glPushMatrix();
    loadMaterial(10);
	glTranslatef(PirStartX, PirStartY, 0); //(p4H/n)/2
	//preenchimento
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	piramide(n, p5W, p5D, p5H);
	//contorno
    loadMaterial(9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	piramide(n, p5W, p5D, p5H);
	glPopMatrix();

	//---------TERCEIRA-----------
	PirStartX += p5W;
	n = 8; // n de andares
	glPushMatrix();
    loadMaterial(10);
	glTranslatef(PirStartX, PirStartY, 0); //(p4H/n)/2
	//preenchimento
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	piramide(n, p6W, p6D, p6H);
	//contorno
    loadMaterial(9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	piramide(n, p6W, p6D, p6H);
	glPopMatrix();

	//--------- VENTOINHA ---------
	glPushMatrix();
    loadMaterial(16);
	glTranslatef(0, 100, 0);
	glScalef(vW, vD, vH);
	ventoinha(angle);
	glPopMatrix();
	update();// atuliza o angulo

	//--------	PREDIO ELEVADOR AUTOMATICO ---------
	glPushMatrix();
        loadMaterial(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glTranslatef(200, 100, p7H / 2);//posicao no tabuleiro + above ground
        glScalef(p7W, p7D, p7H);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPopMatrix();
	//caixa de translação
    glPushMatrix();
        loadMaterial(2);
        glTranslatef(160, 85, ebox7H / 2);
        glScalef(ebox7W, ebox7D, ebox7H);
        cube_unit();
	glPopMatrix();
	//caixa do elevador
	glPushMatrix();
        loadMaterial(2);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glTranslatef(160, 85, ElevAutoZ);
        glScalef(eaW, eaD, eaH);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPopMatrix();

	//------------ PREDIO RETANGULO MALHADO ------------
	glPushMatrix();
        loadMaterial(10);
        glTranslatef(pX8, pY8, pZ8);
        glScalef(p8W, p8D, p8H);
        predio_texture(5, 6,predio);
	glPopMatrix();
    
    //------------ SKYBOX --------------------
    glPushMatrix();
        glTranslated(0, 0, sbZ/2 - 20);
        glScalef(sbX, sbY, sbZ);
        caixa_skybox(topAngle, sbX, sbY, sbZ, showBox, sbX, cartao);
    glPopMatrix();
    
    //------------ LAGO ----------------------
    glPushMatrix();
        //loadMaterial(10);
        glTranslated(0, -150, l_height/2);
        water_sketch();
        drawPool(100, 20, 50, pedra);
    glPopMatrix();
    
	//------------- MASTER POP --------------
	glPopMatrix();
    glDisable(GL_TEXTURE);
    glDisable(GL_LIGHTING);
    
    if(costumOn){
        glColor3f(1., 1.,1.);
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glTranslatef(costumPos[0], costumPos[1], costumPos[2]);
        glScalef(30, 30, 30);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPopMatrix();
    }
    if(spotOn){
        glColor3f(1., 1., 1.);
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
        glScalef(30, 30, 30);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPopMatrix();
    }
    if(dirOn){
        glColor3f(1., 1., 1.);
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z);
        glScalef(30, 30, 30);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPopMatrix();
    }
    if(pointOn){
        glColor3f(1., 1., 1.);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPushMatrix();
        glTranslatef(pointPos[0], pointPos[1], pointPos[2]);
        glScalef(30, 30, 30);
        cube_unit();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPopMatrix();
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
        case OF_KEY_UP: // Tecla 'up' pressionada
            elevadorZ += vel; // Subir o elevador
            if (elevadorZ > eboxH - eH / 2) {
                // Verificar limite superior
                elevadorZ = eboxH - eH / 2;
            }
            break;
        case OF_KEY_DOWN: // Tecla 'down' pressionada
            elevadorZ -= vel; // Descer o elevador
            if (elevadorZ < eH / 2) {
                // Verificar limite inferior
                elevadorZ = eH / 2;
            }
            break;
        case 't': //top
            top = !top;
            break;
        case 'o': //windows
            if ((PwindWL - PwindWR) == -8) {
                PwindWL -= windW;
                PwindWR += windW;
            }
            else {
                PwindWL += windW;
                PwindWR -= windW;
            }
            break;
        case 'r': //rotation
            rotateCamara = !rotateCamara;
            break;
        case 'p': //switch p -> o
            perspectiva =! perspectiva;
            break;
        case 'b': // open box
             isOpening = !isOpening;
            break;
        case 'l': //show box
            showBox = !showBox;
            break;
        case 's': //rotation
            sun = !sun;
            break;
        case '.': // pontual
            pointOn = !pointOn;
            break;
        case 'f': //foco
            spotOn = !spotOn;
            break;
        case 'd': //direcional
            dirOn = !dirOn;
            break;
        case 'z': //costum
            costumOn = !costumOn;
        case '1':
            AmbP = !AmbP;
            break;
        case '2':
            DifP = !DifP;
            break;
        case '3':
            SpecP = !SpecP;
            break;
        case '4':
            AmbD = !AmbD;
            break;
        case '5':
            DifD = !DifD;
            break;
        case '6':
            SpecD = !SpecD;
            break;
        case '7':
            AmbF = !AmbF;
            break;
        case '8':
            DifF = !DifF;
            break;
        case '9':
            SpecF = !SpecF;
            break;
        case 'q':
            AmbC = !AmbC;
            break;
        case 'w':
            DifC = !DifC;
            break;
        case 'e':
            SpecC = !SpecC;
            break;
        }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp:: water_sketch(){
    glPushMatrix();
    
    for (int i = 0; i < 10; i++) {
        freqs[i] = 0.25 + 0.25 * i * 5;
        amps[i] = 1. / (i * 0.25 + 1);
    }

    // Calculate phaseX and phaseY using waterTime instead of dirVecTheta
    //phaseX += 0.00002;
    //phaseY -= 0.00003;
    
    int m = 100;
    int n = 80;
    GLfloat x_start = -0.5;
    GLfloat y_start = 0.5;
    GLfloat x_step = 1.0 / GLfloat(m);
    GLfloat y_step = 1.0 / GLfloat(n);
    GLfloat noise = 0.;
    GLfloat z;
    ofVec3f normal;
    
    texCoords.clear();
    vertexes.clear();
    
    for (int j = 0; j <n; j++) {
        for (int i = 0; i <m; i++) {
            noise = getMultiNoise((i)*x_step + phaseX, (j)*y_step + phaseY, freqs, amps, 10);
            float x = i * x_step + x_start;
            float y = -j * y_step + y_start;
            float z = noise - 0.5;
            vertexes.push_back(ofVec3f(x, y, z));
            texCoords.push_back(ofVec2f(i * x_step, j * y_step));
        }
    }
    
    normals.clear();
    for (int j = 0; j<n; j++) {
        for (int i = 0; i<m; i++) {
            if (i < m-1 && j < n-1) {
                int i1 = j * m + i;
                int i2 = j * m + (i + 1);
                int i3 = (j + 1) * m + i;
                ofVec3f v1 = vertexes[i2] - vertexes[i1];
                ofVec3f v2 = vertexes[i3] - vertexes[i1];
                normal = cross(v2, v1).normalized();
                normals.push_back(normal);
            }
            else {
                normals.push_back(normals[normals.size() - 1]);
            }
            
        }
    }
    water.bind();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    //comment 33
    //completar
    //aqui escalamos a malha em z com um valor que oscila no tempo, assim podemos
    //criar a sensação das ondas aumentarem/diminuirem
    //experimentem com outros valores para ver como o resultadó é afetado
    glPushMatrix();
    glScalef(100, 50, 30);
    
    glBegin(GL_QUADS);
    for (int j = 0; j < n-1; j++) {
        for (int i = 0; i < m-1; i++) {
            int i1 = j * m + i;
            int i2 = (j+1) * m + i;
            int i3 = (j+1) * m + (i+1);
            int i4 = j * m + (i + 1);
            glTexCoord2f(texCoords[i1].x, texCoords[i1].y);
            glNormal3f(normals[i1].x, normals[i1].y, normals[i1].z);
            glVertex3f(vertexes[i1].x, vertexes[i1].y, vertexes[i1].z);

            glTexCoord2f(texCoords[i2].x, texCoords[i2].y);
            glNormal3f(normals[i2].x, normals[i2].y, normals[i2].z);
            glVertex3f(vertexes[i2].x, vertexes[i2].y, vertexes[i2].z);

            glTexCoord2f(texCoords[i3].x, texCoords[i3].y);
            glNormal3f(normals[i3].x, normals[i3].y, normals[i3].z);
            glVertex3f(vertexes[i3].x, vertexes[i3].y, vertexes[i3].z);

            glTexCoord2f(texCoords[i4].x, texCoords[i4].y);
            glNormal3f(normals[i4].x, normals[i4].y, normals[i4].z);
            glVertex3f(vertexes[i4].x, vertexes[i4].y, vertexes[i4].z);
        }
    }
    glEnd();
    glPopMatrix();
    water.unbind();
    glPopMatrix();

}
