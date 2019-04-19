


/************************************************************/
/*            TP2: Primitives 3D et couleur                 */
/************************************************************/
/*													        */
/*        ESGI: algorithmique pour l'infographie	        */
/*													        */
/************************************************************/
/*													        */
/*  Objectif: afficher des formes 3D et illuminer la sc�ne  */
/*													        */
/************************************************************/




#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include<stdio.h>




float angle = 0.0;


/* prototypes de fonctions */
void initRendering();
void display(void);
void reshape(int w,int h);
void update(int value);
void keyboard(unsigned char key, int x, int y);
void createTank();
void createBase();
void createTour();
void createPill1();
void createPill2();



/* Programme principal */
int main(int argc,  char **argv){

	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("TP2: primitives 3D et illumination");

	/* Initialisation d'OpenGL */
	initRendering();

	/* Enregistrement des fonctions de rappel */
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc (20,update, 0);
	glutKeyboardFunc(keyboard);

	/* Entr�e dans la boucle principale de glut, traitement des �v�nements */
    glutMainLoop();
    return 0;
}


/* Initialisation d'OpenGL pour le rendu de la sc�ne */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);

	/* d�finit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Activation des lumi�res */
	//glEnable(GL_LIGHTING);          // Activation du mode
	//glEnable(GL_LIGHT0);            // Activation lumi�re n�0
	//glEnable(GL_LIGHT1);            // Activation lumi�re n�1
	//glEnable(GL_LIGHT2);            // Activation lumi�re n�2

	/* Les normales (cr�es par glNormal(*)) sont automatiquement unitaires */
	glEnable(GL_NORMALIZE);


	/* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
	glShadeModel(GL_SMOOTH);

	/*  d�finit la taille d'un pixel*/
	glPointSize(2.0);

}

/* Cr�ation de la sc�ne avec lampes */
void display(void){



	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();




	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.0f, -5.0f);                      // d�placement cam�ra


	createTank();

	/* On force l'affichage */
	glFlush();
}


/* Fonction de mise � jour: mouvements des objets*/
void update(int value){
	angle += 0.2;
	if (angle > 360){
		angle -= 360;
	}



	glutPostRedisplay();
	glutTimerFunc(10,update, 0);


}


/*  Mise en forme de la sc�ne pour l'affichage */
void reshape(int w, int h){
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,	200.0);



}



/* Fonction de gestion au clavier des activations des lumi�res */
void keyboard(unsigned char key, int x, int y) {
		switch (key){

			case 'a':   /* activation lumi�re n�0 */
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glutPostRedisplay();
				break;

			case 'b':   /* activation lumi�re n�1*/
				glEnable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glutPostRedisplay();
				break;

			case 'c': //active l2
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT2);
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glutPostRedisplay();
				break;

			case 'l':   /* activation des lumi�res  */
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glutPostRedisplay();
				break;

			case 'L':   /* d�sactivation des lumi�res  */
				glDisable(GL_LIGHTING);
				glutPostRedisplay();
				break;

			case 'q':   /* Quitter le programme */
				exit(0);
		}
}

void createTank()
{
	createBase();
	createTour();
	createPill1();
	createPill2();
}

void createBase()
{
	/* Dessine la BASE en mvt */
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.25f, 0.4f, 0.34f);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glBegin(GL_QUADS);

	//Front
	glVertex3f(-4.0f, 0.0f, 2.0f); //a
	glVertex3f(4.0f, -0.5f, 2.0f); //b
	glVertex3f(3.5f, -2.0f, 2.0f); //c
	glVertex3f(-2.0f, -2.0f, 2.0f); //d

	//Right
	glVertex3f(4.0f, -0.5f, 2.0f); //b
	glVertex3f(4.0f, -0.5f, -2.0f); //e
	glVertex3f(4.0f, -2.0f, -2.0f); //f
	glVertex3f(3.5f, -2.0f, 2.0f); //c

	//Back
	glVertex3f(-4.0f, 0.0f, -2.0f); //g
	glVertex3f(4.0f, -0.5f, -2.0f); //e
	glVertex3f(4.0f, -2.0f, -2.0f); //f

	glVertex3f(-2.0f, -2.0f, -2.0f); //h

	//Left
	glVertex3f(-4.0f, 0.0f, 2.0f); //a
	glVertex3f(-4.0f, 0.0f, -2.0f); //g
	glVertex3f(-2.0f, -2.0f, -2.0f); //h

	glVertex3f(-2.0f, -2.0f, 2.0f); //d

	//top
	glVertex3f(-4.0f, 0.0f, 2.0f); //a
	glVertex3f(-4.0f, 0.0f, -2.0f); //g
	glVertex3f(4.0f, -0.5f, -2.0f); //e
	glVertex3f(4.0f, -0.5f, 2.0f); //b

	//bottom
	glVertex3f(-2.0f, -2.0f, -2.0f); //h
	glVertex3f(4.0f, -2.0f, -2.0f); //f
	glVertex3f(3.5f, -2.0f, 2.0f); //c
	glVertex3f(-2.0f, -2.0f, 2.0f); //d



	glEnd();
	glPopMatrix();
}

void createTour()
{
	/* Dessine la TOUR en mvt */
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.25f, 0.4f, 0.34f);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glBegin(GL_QUADS);

	//Front
		//central
	glVertex3f(0.75f, 4.0f, 1.0f); //a
	glVertex3f(2.75f, 4.0f, 1.0f); //b
	glVertex3f(2.75f, 3.0f, 1.0f); //e
	glVertex3f(0.75f, 3.0f, 1.0f); //f
		//right
	glVertex3f(2.75f, 4.0f, 1.0f); //b
	glVertex3f(3.0f, 3.75f, 1.0f); //c
	glVertex3f(3.0f, 3.25f, 1.0f); //d
	glVertex3f(2.75f, 3.0f, 1.0f); //e
		//left
	glVertex3f(0.75f, 4.0f, 1.0f); //a
	glVertex3f(0.75f, 3.0f, 1.0f); //f
	glVertex3f(0.0f, 3.25f, 1.0f); //g
	glVertex3f(0.0f, 3.75f, 1.0f); //h


	//Right
		//central
	glVertex3f(3.0f, 3.75f, 1.0f); //c
	glVertex3f(3.0f, 3.75f, -1.0f); //c
	glVertex3f(3.0f, 3.25f, -1.0f); //d
	glVertex3f(3.0f, 3.25f, 1.0f); //d
		//top
	glVertex3f(2.75f, 4.0f, 1.0f); //b
	glVertex3f(2.75f, 4.0f, -1.0f); //b
	glVertex3f(3.0f, 3.75f, -1.0f); //c
	glVertex3f(3.0f, 3.75f, 1.0f); //c
		//bottom
	glVertex3f(3.0f, 3.25f, 1.0f); //d
	glVertex3f(3.0f, 3.25f, -1.0f); //d
	glVertex3f(2.75f, 3.0f, -1.0f); //e
	glVertex3f(2.75f, 3.0f, 1.0f); //e

	//Back
		//central
	glVertex3f(0.75f, 4.0f, -1.0f); //a
	glVertex3f(2.75f, 4.0f, -1.0f); //b
	glVertex3f(2.75f, 3.0f, -1.0f); //e
	glVertex3f(0.75f, 3.0f, -1.0f); //f
		//right
	glVertex3f(2.75f, 4.0f, -1.0f); //b
	glVertex3f(3.0f, 3.75f, -1.0f); //c
	glVertex3f(3.0f, 3.25f, -1.0f); //d
	glVertex3f(2.75f, 3.0f, -1.0f); //e
		//left
	glVertex3f(0.75f, 4.0f, -1.0f); //a
	glVertex3f(0.75f, 3.0f, -1.0f); //f
	glVertex3f(0.0f, 3.25f, -1.0f); //g
	glVertex3f(0.0f, 3.75f, -1.0f); //h


	//Left
		//central
	glVertex3f(0.0f, 3.25f, 1.0f); //g
	glVertex3f(0.0f, 3.25f, -1.0f); //g
	glVertex3f(0.0f, 3.75f, -1.0f); //h
	glVertex3f(0.0f, 3.75f, 1.0f); //h
		//top
	glVertex3f(0.75f, 4.0f, -1.0f); //a
	glVertex3f(0.75f, 4.0f, 1.0f); //a
	glVertex3f(0.0f, 3.75f, 1.0f); //h
	glVertex3f(0.0f, 3.75f, -1.0f); //h
		//bottom
	glVertex3f(0.0f, 3.25f, 1.0f); //g
	glVertex3f(0.0f, 3.25f, -1.0f); //g
	glVertex3f(0.75f, 3.0f, -1.0f); //f
	glVertex3f(0.75f, 3.0f, 1.0f); //f


	//top
	glVertex3f(0.75f, 4.0f, -1.0f); //a
	glVertex3f(2.75f, 4.0f, -1.0f); //b
	glVertex3f(2.75f, 4.0f, 1.0f); //b
	glVertex3f(0.75f, 4.0f, 1.0f); //a


	//bottom
	glVertex3f(2.75f, 3.0f, -1.0f); //e
	glVertex3f(0.75f, 3.0f, -1.0f); //f
	glVertex3f(0.75f, 3.0f, 1.0f); //f
	glVertex3f(2.75f, 3.0f, 1.0f); //e

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void createPill1()
{
	 /* Dessine la COLLONE 1 en mvt */
	glPushMatrix();
	// glTranslatef(-1.5f, -1.5f, 1.5f);
	// glRotatef(angle, 1.0f, 0.0f, 0.0f);
	// glTranslatef(1.0f, 1.75f, -1.5f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.25f, 0.4f, 0.34f);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glBegin(GL_QUADS);

	//Front
	glVertex3f(-1.0f, -1.75f, 1.5f); //a
	glVertex3f(-2.0f, -1.25f, 1.5f); //b
	glVertex3f(1.75f, 3.5f, 1.5f); //c
	glVertex3f(2.75f, 3.5f, 1.5f); //d

	//Right
	glVertex3f(2.75f, 3.5f, 1.5f); //d
	glVertex3f(-2.0f, -1.25f, 1.0f); //f
	glVertex3f(1.75f, 3.5f, 1.0f); //g
	glVertex3f(1.75f, 3.5f, 1.5f); //c

	//Back
	glVertex3f(-1.0f, -1.75f, 1.0f); //e
	glVertex3f(-2.0f, -1.25f, 1.0f); //f
	glVertex3f(1.75f, 3.5f, 1.0f); //g
	glVertex3f(2.75f, 3.5f, 1.0f); //h

	//Left
	glVertex3f(-1.0f, -1.75f, 1.5f); //a
	glVertex3f(-1.0f, -1.75f, 1.0f); //e
	glVertex3f(2.75f, 3.5f, 1.0f); //h
	glVertex3f(2.75f, 3.5f, 1.5f); //d

	//top
	glVertex3f(1.75f, 3.5f, 1.5f); //c
	glVertex3f(2.75f, 3.5f, 1.5f); //d
	glVertex3f(2.75f, 3.5f, 1.0f); //h
	glVertex3f(1.75f, 3.5f, 1.0f); //g

	//bottom
	glVertex3f(-1.0f, -1.75f, 1.5f); //a
	glVertex3f(-2.0f, -1.25f, 1.5f); //b
	glVertex3f(-2.0f, -1.25f, 1.0f); //f
	glVertex3f(-1.0f, -1.75f, 1.0f); //e

	glEnd();
	glPopMatrix();
}

void createPill2()
{
	 /* Dessine la COLLONE 2 en mvt */
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.25f, 0.4f, 0.34f);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	//glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glBegin(GL_QUADS);

	//Front
	glVertex3f(-1.0f, -1.75f, -1.0f); //a
	glVertex3f(-2.0f, -1.25f, -1.0f); //b
	glVertex3f(1.75f, 3.5f, -1.0f); //c
	glVertex3f(2.75f, 3.5f, -1.0f); //d

	//Right
	glVertex3f(2.75f, 3.5f, -1.0f); //d
	glVertex3f(-2.0f, -1.25f, -1.5f); //f
	glVertex3f(1.75f, 3.5f, -1.5f); //g
	glVertex3f(1.75f, 3.5f, -1.0f); //c

	//Back
	glVertex3f(-1.0f, -1.75f, -1.5f); //e
	glVertex3f(-2.0f, -1.25f, -1.5f); //f
	glVertex3f(1.75f, 3.5f, -1.5f); //g
	glVertex3f(2.75f, 3.5f, -1.5f); //h

	//Left
	glVertex3f(-1.0f, -1.75f, -1.0f); //a
	glVertex3f(-1.0f, -1.75f, -1.5f); //e
	glVertex3f(2.75f, 3.5f, -1.5f); //h
	glVertex3f(2.75f, 3.5f, -1.0f); //d

	//top
	glVertex3f(1.75f, 3.5f, -1.0f); //c
	glVertex3f(2.75f, 3.5f, -1.0f); //d
	glVertex3f(2.75f, 3.5f, 1.0f); //h
	glVertex3f(1.75f, 3.5f, 1.0f); //g

	//bottom
	glVertex3f(-1.0f, -1.75f, -1.0f); //a
	glVertex3f(-2.0f, -1.25f, -1.0f); //b
	glVertex3f(-2.0f, -1.25f, -1.5f); //f
	glVertex3f(-1.0f, -1.75f, -1.5f); //e

	glEnd();
	glPopMatrix();

}
