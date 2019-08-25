
/*
 * mancala.c
 *
 *      Author:Aditi
 */
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>

int x1=210.0,y1=290.0,k=9,count=0,playerst=0;
int ca=4,cb=4,cc=4,cd=4,ce=4,cf=4,cg=4,ch=4,point1=0,point2=0;
int pxa=220,pxb=320,pxc=420,pxd=520,pxe=520,pxf=420,pxg=320,pxh=220,pya=320,pyb=320,pyc=320,
pyd=320,pye=420,pyf=420,pyg=420,pyh=420;
int selret,bchg=0,swap=0,state1=0;
int arry[8]={4,4,4,4,4,4,4,4};
int t2=0,t3=0;
void polygon(int xx1, int xx2, int yy1, int yy2);
void ppolygon(int px, int py, int dx1, int dx2, int dy1, int dy2);
void sel_polygon(int xx1, int xx2, int yy1, int yy2);
void beeds(int cnt, int px, int py);
void *currentfont;
void player(int selx);
int getpos(int selx, int sely);
int getcount(int selx);
void board();
int selection1();
void selection2();
void scorebeed(int);
void hpolygon(int xx1, int xx2, int yy1, int yy2);
void cups_polygon(int xx1, int xx2, int yy1, int yy2);
void beeds_print();
void text1(void);
void loading();
void help(void);
void title();
void text(void);
void rotate_board();
void screen_rotate(void);
void Game_over(void);
int page=1,dont1=0;
void help_below();

void setFont(void *font)
{
	currentfont=font;
}
void drawstring(float x,float y,float z,char *string)
{
	    char *c;
	glRasterPos3f(x,y,z);

	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glLoadIdentity();
	gluOrtho2D(0.0,800.0,0.0,600.0);
	glLineWidth(5.0);
	glutPostRedisplay();
	setFont(GLUT_BITMAP_HELVETICA_18);
}

void myMouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN && page==1)
	{
		page++;
		t2=1;
		glutPostRedisplay();
	}
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN && page==2)
	{
		page++;
		t2=2;
		glutPostRedisplay();
	}
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN && page==3)
	{
		page++;
		t2=3;
		glutPostRedisplay();
	}
}
void key(unsigned char p, int x,int y)
{
	switch(p)
	{
		case 13:
//			sndPlaySound("coin.wav",SND_ASYNC);
			if(state1==1)
			{
				player(selret);
				scorebeed(swap);
				//Sleep(1500);
				if(dont1==0)
				{
					screen_rotate();
					rotate_board();
					scorebeed(swap);
				}
			}
			glutPostRedisplay();
			break;
	}
}
void HandleSpecialKeyboard(int key,int x, int y)
{
	switch(key)
	{
		case  GLUT_KEY_RIGHT :
			if(x1<210 && y1<290)
			{
				x1=210;
				y1=290;
				k=9;
			}
			else if(x1>510 && y1>590)
			{
				x1=510;
				y1=590;
				k=9;
			}
			else k=1;
			glutPostRedisplay();
			break;

		case  GLUT_KEY_LEFT :
			if(x1<210 && y1<290)
			{
				x1=210;
				y1=290;
				k=9;
			}
			else if(x1>510 && y1>590)
			{
				x1=510;
				y1=590;
				k=9;
			}
			else k=0;
			glutPostRedisplay();
			break;

		default:break;

	}
}
void player(int selx)
{
	int j,l;
	arry[0]=ca;
	arry[1]=cb;
	arry[2]=cc;
	arry[3]=cd;
	arry[4]=ce;
	arry[5]=cf;
	arry[6]=cg;
	arry[7]=ch;

	printf("ca=%d ",ca);
	printf("cb=%d ",cb);
	printf("cc=%d ",cc);
	printf("cd=%d ",cd);
	printf("ce=%d ",ce);
	printf("cf=%d ",cf);
	printf("cg=%d ",cg);
	printf("ch=%d \n",ch);
	printf("Swap=%d\n",swap);

	l=getpos(selx,310);
	printf("position=%d\n",l);
	j=getcount(l);
	printf("count=%d\n",j);

	arry[l]=0;
	if(j==0)
		dont1=1;
	else
		dont1=0;
	if(swap==0)
	{
		while(j!=0)
		{
			l++;
			if(l==4)
			{
				point1=point1+1;
				if(j==1)
					dont1=1;
				else
					dont1=0;
				if(j!=1)
				{
					arry[l]=arry[l]+1;
					j--;
				}
			}
			else if(l==7)
			{
				arry[l]=arry[l]+1;
				l=-1;
			}
			else
			{
				arry[l]=arry[l]+1;
			}
			j--;
			printf("point1=%d\n",point1);
		}
		if(arry[l]==1)
		{
			if(l>=0 && l<=3)
			{
				point1=point1+1+arry[7-l];
				arry[l]=0;
				arry[7-l]=0;
			}
		}

		ca=arry[0];
		cb=arry[1];
		cc=arry[2];
		cd=arry[3];
		ce=arry[4];
		cf=arry[5];
		cg=arry[6];
		ch=arry[7];
		board();
		beeds_print();
	}
	else
	if(swap==1)
	{
		while(j!=0)
		{
			l++;
			if(l==4)
			{
				point2=point2+1;
				if(j==1)
					dont1=1;
				else
					dont1=0;
				if(j!=1)
				{
					arry[l]=arry[l]+1;
					j--;
				}
			}
			else if(l==7)
			{
				arry[l]=arry[l]+1;
				l=-1;
			}
			else
			{
				arry[l]=arry[l]+1;
			}
			j--;
			printf("point2=%d\n",point2);
		}
		if(arry[l]==1)
		{
			if(l>=0 && l<=3)
			{
				point2=point2+1+arry[7-l];
				arry[l]=0;
				arry[7-l]=0;
			}
		}
		ca=arry[0];
		cb=arry[1];
		cc=arry[2];
		cd=arry[3];
		ce=arry[4];
		cf=arry[5];
		cg=arry[6];
		ch=arry[7];
		board();
		beeds_print();
	}
	printf("ca=%d ",ca);
	printf("cb=%d ",cb);
	printf("cc=%d ",cc);
	printf("cd=%d ",cd);
	printf("ce=%d ",ce);
	printf("cf=%d ",cf);
	printf("cg=%d ",cg);
	printf("ch=%d \n",ch);

	if((ca==0 && cb==0 && cc==0 && cd==0) || (ce==0 && cf==0 && cg==0 && ch==0))
	{
		if(swap==0)
		{
			point1=point1+ca+cb+cc+cd;
			point2=point2+ce+cf+cg+ch;
			ca=0;
			cb=0;
			cc=0;
			cd=0;
			ce=0;
			cf=0;
			cg=0;
			ch=0;
		}
		else
		{
			point2=point2+ca+cb+cc+cd;
			point1=point1+ce+cf+cg+ch;
			ca=0;
			cb=0;
			cc=0;
			cd=0;
			ce=0;
			cf=0;
			cg=0;
			ch=0;
		}
	}

}

void display(void)
{
	switch(t2)
	{
		case 0:
			glClear(GL_COLOR_BUFFER_BIT);
//			sndPlaySound("start.wav",SND_ASYNC);
			title();
			break;
		case 1:
			text();
			break;
		case 2:
			help();
			break;
		case 3:
			loading();
			t2=4;
			state1=1;
			break;
		default:state1=1;
	}
	if(state1==1)
	{
		if((ca!=0 || cb!=0 || cc!=0 || cd!=0) && (ce!=0 || cf!=0 || cg!=0 || ch!=0))
		{
				glClear(GL_COLOR_BUFFER_BIT);
				board();
				beeds_print();
				scorebeed(swap);
				selret=selection1();
		}
		else
		{
			state1=0;
			Game_over();
		}
	}
//glutSwapBuffers();
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(760,570);
	glutInitWindowPosition(0,0);
	glutCreateWindow("MY MANCALA");
	//glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(key);
	glutSpecialFunc(HandleSpecialKeyboard);
	init();
	glutMainLoop();
	return 0;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------SEPERATOR---------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void beeds_print()
{
	beeds(ca,pxa,pya);
	beeds(cb,pxb,pyb);
	beeds(cc,pxc,pyc);
	beeds(cd,pxd,pyd);
	beeds(ce,pxe,pye);
	beeds(cf,pxf,pyf);
	beeds(cg,pxg,pyg);
	beeds(ch,pxh,pyh);
}

void sel_polygon(int xx1, int xx2, int yy1, int yy2)
{
	glColor3f(1.0,0.689,0.0);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(xx1,yy1);
		glVertex2f(xx2,yy1);
		glVertex2f(xx2,yy2);
		glVertex2f(xx1,yy2);
	}
	glEnd();
	glFlush();
}

void hpolygon(int xx1, int xx2, int yy1, int yy2)
{
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(xx1,yy1);
		glVertex2f(xx2,yy1);
		glVertex2f(xx2,yy2);
		glVertex2f(xx1,yy2);
	}
	glEnd();
	glFlush();
}

void cups_polygon(int xx1, int xx2, int yy1, int yy2)
{
	glBegin(GL_POLYGON);
	{
		glColor3f(1.0,0.0,0.0);
		glVertex2f(xx1,yy1);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(xx2,yy1);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(xx2,yy2);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(xx1,yy2);
	}
	glEnd();
	glFlush();
}
void polygon(int xx1, int xx2, int yy1, int yy2)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(xx1,yy1);
		glVertex2f(xx2,yy1);
		glVertex2f(xx2,yy2);
		glVertex2f(xx1,yy2);
	}
	glEnd();
	glFlush();
}

void ppolygon(int px, int py, int dx1, int dx2, int dy1, int dy2)
{
	glColor3f(0.5,0.9,0.9);
	glBegin(GL_POLYGON);
	{
		glVertex2f(px+dx1,py+dy1);
		glVertex2f(px+dx2,py+dy1);
		glVertex2f(px+dx2,py+dy2);
		glVertex2f(px+dx1,py+dy2);
	}
	glEnd();
	glFlush();
}
int getcount(int selx)
{
	switch(selx)
	{
		case 0: return ca;
			break;
		case 1: return cb;
			break;
		case 2: return cc;
			break;
		case 3: return cd;
			break;
	}
	return 0;
}
int getpos(int selx, int sely)
{
	if(sely==310)
	{
		switch(selx)
		{
			case 210: return 0;
				break;
			case 310: return 1;
				break;
			case 410: return 2;
				break;
			case 510: return 3;
			//	break;
		}
	}
	else
	{
		switch(sely)
		{
			case 510: return 4;
				break;
			case 410: return 5;
				break;
			case 310: return 6;
				break;
			case 210: return 7;
				break;
		}
	}
	return 0;
}
int selection1()
{
	if(k==1)
	{
		x1=x1+100.0;
		y1=y1+100.0;
		//glColor3f(1.0,1.0,0.0);
		sel_polygon(x1,y1,310,390);
	}
	else if(k==0)
	{
		x1=x1-100.0;
		y1=y1-100.0;
		//glColor3f(1.0,0.0,0.0);
		sel_polygon(x1,y1,310,390);
	}
	else
	{
		//glColor3f(1.0,1.0,0.0);
		sel_polygon(x1,y1,310,390);
	}
	return x1;
}
void scorebeed(int swap)
{
	int py1=310,px1=610,px2=110,p1,p2;
	if(swap==0)
	{
		p1=point1;
		p2=point2;
	}
	else
	{
		p2=point1;
		p1=point2;
	}
	//if(p1==0) return;
	if(p1>=1) ppolygon(px1,py1,35,45,90,100);
	if(p1>=2) ppolygon(px1,py1,35,45,70,80);
	if(p1>=3) ppolygon(px1,py1,20,30,80,90);
	if(p1>=4) ppolygon(px1,py1,50,60,80,90);
	if(p1>=5) ppolygon(px1,py1,35,45,110,120);
	if(p1>=6) ppolygon(px1,py1,35,45,50,60);
	if(p1>=7) ppolygon(px1,py1,20,30,100,110);
	if(p1>=8) ppolygon(px1,py1,20,30,60,70);
	if(p1>=9) ppolygon(px1,py1,50,60,100,110);
	if(p1>=10) ppolygon(px1,py1,50,60,60,70);
	if(p1>=11) ppolygon(px1,py1,5,15,90,100);
	if(p1>=12) ppolygon(px1,py1,5,15,70,80);
	if(p1>=13) ppolygon(px1,py1,65,75,90,100);
	if(p1>=14) ppolygon(px1,py1,65,75,70,80);
	if(p1>=15) ppolygon(px1,py1,35,45,130,140);
	if(p1>=16) ppolygon(px1,py1,35,45,30,40);
	if(p1>=17) ppolygon(px1,py1,20,30,120,130);
	if(p1>=18) ppolygon(px1,py1,50,60,40,50);
	if(p1>=19) ppolygon(px1,py1,20,30,40,50);
	if(p1>=20) ppolygon(px1,py1,50,60,120,130);
	if(p1>=21) ppolygon(px1,py1,35,45,150,160);
	if(p1>=22) ppolygon(px1,py1,35,45,10,20);
	if(p1>=23) ppolygon(px1,py1,5,15,140,150);
	if(p1>=24) ppolygon(px1,py1,65,75,20,30);
	if(p1>=25) ppolygon(px1,py1,65,75,140,150);
	if(p1>=26) ppolygon(px1,py1,5,15,20,30);


	//if(p2==0) return;
	if(p2>=1) ppolygon(px2,py1,35,45,90,100);
	if(p2>=2) ppolygon(px2,py1,35,45,70,80);
	if(p2>=3) ppolygon(px2,py1,20,30,80,90);
	if(p2>=4) ppolygon(px2,py1,50,60,80,90);
	if(p2>=5) ppolygon(px2,py1,35,45,110,120);
	if(p2>=6) ppolygon(px2,py1,35,45,50,60);
	if(p2>=7) ppolygon(px2,py1,20,30,100,110);
	if(p2>=8) ppolygon(px2,py1,20,30,60,70);
	if(p2>=9) ppolygon(px2,py1,50,60,100,110);
	if(p2>=10) ppolygon(px2,py1,50,60,60,70);
	if(p2>=11) ppolygon(px2,py1,5,15,90,100);
	if(p2>=12) ppolygon(px2,py1,5,15,70,80);
	if(p2>=13) ppolygon(px2,py1,65,75,90,100);
	if(p2>=14) ppolygon(px2,py1,65,75,70,80);
	if(p2>=15) ppolygon(px2,py1,35,45,130,140);
	if(p2>=16) ppolygon(px2,py1,35,45,30,40);
	if(p2>=17) ppolygon(px2,py1,20,30,120,130);
	if(p2>=18) ppolygon(px2,py1,50,60,40,50);
	if(p2>=19) ppolygon(px2,py1,20,30,40,50);
	if(p2>=20) ppolygon(px2,py1,50,60,120,130);
	if(p2>=21) ppolygon(px2,py1,35,45,150,160);
	if(p2>=22) ppolygon(px2,py1,35,45,10,20);
	if(p2>=23) ppolygon(px2,py1,5,15,140,150);
	if(p2>=24) ppolygon(px2,py1,65,75,20,30);
	if(p2>=25) ppolygon(px2,py1,65,75,140,150);
	if(p2>=26) ppolygon(px2,py1,5,15,20,30);

}

void beeds(int cnt, int px, int py)
{
	if(cnt==0)
		return;
	if(cnt>=1)
		ppolygon(px,py,5,15,45,55);
	if(cnt>=2)
		ppolygon(px,py,45,55,45,55);
	if(cnt>=3)
		ppolygon(px,py,5,15,5,15);
	if(cnt>=4)
		ppolygon(px,py,45,55,5,15);
	if(cnt>=5)
		ppolygon(px,py,25,35,25,35);
	if(cnt>=6)
		ppolygon(px,py,25,35,45,55);
	if(cnt>=7)
		ppolygon(px,py,5,15,25,35);
	if(cnt>=8)
		ppolygon(px,py,45,55,25,35);
	if(cnt>=9)
		ppolygon(px,py,25,35,5,15);
	if(cnt>=10)
		ppolygon(px,py,15,25,35,45);
	if(cnt>=11)
		ppolygon(px,py,35,45,35,45);
	if(cnt>=12)
		ppolygon(px,py,15,25,15,25);
	if(cnt>=13)
		ppolygon(px,py,35,45,15,25);
}
void board()
{
	//back ground board
	glColor3f(0.235,0.1,0.0);
	polygon(100,700,300,500);
	if(point1>point2)
	{
		glColor3f(0.0,0.0,0.0);
		polygon(500,750,150,250);
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(0.0,1.0,0.0);
		drawstring(500.0,200.0,1.0,"PLAYER : 1 IS LEADING");
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(1.0,0.0,0.0);
		drawstring(500.0,170.0,1.0,"PLAYER : 2 IS LAGGING");
		t3++;
	}
	else if(point2>point1)
	{
		glColor3f(0.0,0.0,0.0);
		polygon(500,750,150,250);
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(0.0,1.0,0.0);
		drawstring(500.0,200.0,1.0,"PLAYER : 2 IS LEADING");
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(1.0,0.0,0.0);
		drawstring(500.0,170.0,1.0,"PLAYER : 1 IS LAGGING");
	}
	else
	{
		glColor3f(0.0,0.0,0.0);
		polygon(500,750,150,250);
		if(t3!=0)
		{
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(0.0,1.0,0.0);
		drawstring(500.0,200.0,1.0,"SCORES ARE EQUAL");
		}
	}


	if(bchg==0)						//board colour change after the player shift
	{
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(1.0,1.0,0.0);
		drawstring(360.0,277.0,1.0,"PLAYER:1");

		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(1.0,1.0,0.0);
		drawstring(360.0,510.0,1.0,"PLAYER:2");


	}
	else
	{
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(1.0,1.0,0.0);
		drawstring(360.0,277.0,1.0,"PLAYER:2");

		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(1.0,1.0,0.0);
		drawstring(360.0,510.0,1.0,"PLAYER:1");


	}
	help_below();

	glBegin(GL_POLYGON);
	{								//points
		glColor3f(1.0,0.0,0.0);
		glVertex2f(110,310);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(190,310);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(190,490);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(110,490);
	}
	glEnd();
	glFlush();

	glBegin(GL_POLYGON);
	{
		glColor3f(1.0,0.0,0.0);
		glVertex2f(610,310);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(690,310);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(690,490);
		glColor3f(0.0,0.0,0.0);
		glVertex2f(610,490);
	}
	glEnd();
	glFlush();

	//cups small
	cups_polygon(220,280,320,380);
	cups_polygon(320,380,320,380);
	cups_polygon(420,480,320,380);
	cups_polygon(520,580,320,380);
	cups_polygon(220,280,420,480);
	cups_polygon(320,380,420,480);
	cups_polygon(420,480,420,480);
	cups_polygon(520,580,420,480);
	//cups small

	//cups border
	glColor3f(0.6,0.3,0.0);
	hpolygon(220,280,320,380);
	hpolygon(320,380,320,380);
	hpolygon(420,480,320,380);
	hpolygon(520,580,320,380);
	hpolygon(220,280,420,480);
	hpolygon(320,380,420,480);
	hpolygon(420,480,420,480);
	hpolygon(520,580,420,480);
	//cups border


	//borders lines
	glColor3f(0.6,0.3,0.0);
	hpolygon(100,700,300,500);
	glBegin(GL_LINES);
	{
		glVertex2f(200,300);
		glVertex2f(200,500);
	}
	glEnd();
	glFlush();
	glBegin(GL_LINES);
	{
		glVertex2f(600,300);
		glVertex2f(600,500);
	}
	glEnd();
	glFlush();
	glBegin(GL_LINES);
	{
		glVertex2f(200,400);
		glVertex2f(600,400);
	}
	glEnd();
	glFlush();

	hpolygon(110,190,310,490);
	hpolygon(610,690,310,490);

	//Border ends
}
void title()
{
	glColor3f(0.0,0.5,1.0);
	hpolygon(10,790,10,590);
	hpolygon(20,780,20,580);
	glBegin(GL_POLYGON);
	{	glColor3f(0.0,0.0,1.0);
		glVertex2i(20.0,20.0);
		glColor3f(0.6,0.3,0.8);
		glVertex2i(780.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,580.0);
		glColor3f(0.6,0.3,0.8);
		glVertex2i(20.0,580.0);
	}
	glEnd();
	glFlush();

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.99,0.4,0.0);
	drawstring(220.0,500.0,1.0,"         ANSAL UNIVERSITY");
	glColor3f(0.99,0.3,0.0);
	drawstring(175.0,470.0,1.0,"COMPUTER SCIENCE & ENGINEERING");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.2,0.6,0.9);
	drawstring(250.0,425.0,1.0,"IV SEM, COMPUTER GRAPHICS");
	glColor3f(0.0,0.8,1.0);
	drawstring(266.0,400.0,1.0,"PROJECT : MANCALA GAME");

	setFont(GLUT_BITMAP_HELVETICA_18);

	glColor3f(1.0,1.0,1.0);
	drawstring(300.0,220.0,1.0,"Developed By:-");

	glColor3f(0.0,1.0,1.0);
	drawstring(320.0,180.0,1.0,"Aditi Mathur");

	setFont(GLUT_BITMAP_HELVETICA_12);

	glColor3f(0.0,1.0,1.0);
	drawstring(230.0,180.0,1.0," ");

	glColor3f(0.0,1.0,1.0);
	drawstring(70.0,160.0,1.0,"  ");

	glColor3f(0.0,1.0,1.0);
	drawstring(70.0,140.0,1.0,"  ");

	setFont(GLUT_BITMAP_HELVETICA_18);

	glColor3f(0.0,1.0,1.0);
	drawstring(400.0,180.0,1.0,"           ");
	setFont(GLUT_BITMAP_HELVETICA_12);

	glColor3f(0.0,1.0,1.0);
	drawstring(610.0,180.0,1.0,"             ");

	glColor3f(0.0,1.0,1.0);
	drawstring(410.0,160.0,1.0,"          ");

	glColor3f(0.0,1.0,1.0);
	drawstring(410.0,140.0,1.0,"          ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,1.0,0.0);
	drawstring(300.0,30.0,1.0,"          PRESS MOUSE 'LEFT' BUTTON TO CONTINUE");

    glFlush();
}
void text(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	{
		glColor3f(0.6,0.3,0.8);
		glVertex2i(20.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,20.0);
		glColor3f(0.6,0.3,0.8);
		glVertex2i(780.0,580.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,580.0);
	}
	glEnd();
	glFlush();
	glFlush();

	setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
	drawstring(155.0,365.0,1.0,"*  *  *  *  *  *  *  *  *  MANCALA GAME *  *  *  *  *  *  *  *  *");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,1.0,1.0);
	drawstring(300.0,30.0,1.0,"       PRESS MOUSE 'RIGHT' BUTTON TO CONTINUE");

	glFlush();
}
void help(void)
{

glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	{
		glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,580.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,580.0);
	}
	glEnd();
	glFlush();
	glColor3f(0.8,0.1,0.0);
	hpolygon(20,780,20,580);

		setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,0.5,0.3);
	drawstring(180.0,550,1.0,"* * * * HOW TO PLAY MANCALA * * * *");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(125.0,525,1.0,"THE OBJECTIVE OF THE GAME IS TO COLLECT AS MANY STONES  ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,500,1.0," AS MANY  AS  POSSIBLE  BEFORE  YOUR OPPONENTS  CLEAR'S  ALL THE  ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,475,1.0," STONES ON HIS  SIDE OF THE  BOARD.EACH PLAYER  SITS FACING LONG ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,450,1.0," SIDE  OF  THE BOARD. THE  FOUR  CUPS ON  YOUR  SIDE  AND STORE ON");


	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,425,1.0," YOUR RIGHT , BELONGS TO  YOU. PLACE FOUR STONES  IN EACH NON -");


	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,400,1.0," SCORING CUP.ALTERNATE TURNS.TO TAKE YOUR TURN PICKUP ALL THE");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,375,1.0," STONES FROM ONE CUP OF YOUR SIDE AND PLACE ONEBYONE IN CUPS");


	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,350,1.0," ARROUND THE BOARD,INCLUDING YOUR STORE,IN A CLOCKWISE MOVE. ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(80.0,325,1.0,"         IF THE LAST  STONE  IS DROPPED  INTO  YOUR STORE, YOU  CAN ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,300,1.0," TAKE ANOTHER TURN.IF THE LAST STONE OF YOUR  TURN  IS  DROPPED ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,275,1.0," INTO  AN  EMPTY  CUP ON  YOUR SIDE,YOU MAY TAKE ALL THE STONES");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,250,1.0," FROM  OPPONENT'S CUP  DIRECTLY  OPPOSITE YOUR  EMPTY CUP.  ALL");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,225,1.0," THE CAPTURED STONES AND THE STONE YOU USED TO MAKE CAPTURE,");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,200,1.0," CAN BE PLACED IN YOUR MANCALA.");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(80.0,175,1.0,"        THE GAME ENDS  WHEN ONE  PLAYER  HAS NO MORE STONES ON ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,150,1.0," HIS SIDE.THE  REMAINING PLAYER CAN DEPOSIT ALL  THE  STONES LEFT ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,125,1.0," ON HIS SIDE INTO  HIS  STORE.THE WINNER  HAS MOST  STONES IN HIS ");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,0.0,0.0);
	drawstring(50.0,100,1.0," STORE.");

	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(0.0,1.0,1.0);
	drawstring(300.0,30.0,1.0,"          PRESS MOUSE 'LEFT' BUTTON TO CONTINUE");

	glFlush();
	/*setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0,1.0,1.0);
	drawstring(29,52,1.0,"LEVEL COMPLETED");*/
}
void text1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	setFont(GLUT_BITMAP_HELVETICA_18);
 /*   glColor3f(1.0,1.0,1.0);
	drawstring(95.0,565.0,1.0,"*  *  *  *  *  *  *  *  * MANCALA GAME *  *  *  *  *  *  *  *  *");
*/

    glColor3f(1.0,0.1,0.0);
	drawstring(338.0,210,1.0,"L O A D I N G . . .");

    glColor3f(0.6,0.3,0.0);
	hpolygon(200,600,190,200);
	glFlush();

}
void loading()
{
	text1();
	glFlush();

	int x1=200;
	float x2=200;
	int y1=190;
	int y2=200;
	int j=30;
	while(x2<=600)
	{
		x2=x2+0.1;
		glBegin(GL_POLYGON);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
		glEnd();
		glFlush();
	}
}
void help_below()
{	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(100.0,110.0);
	glVertex2f(100.0,225.0);
	glVertex2f(315.0,225.0);
	glVertex2f(315.0,110.0);
	glEnd();
	setFont(GLUT_BITMAP_HELVETICA_18);
	glColor3f(1.0,0.0,0.0);
	drawstring(115.0,200,1.0,"INSTRUCTIONS: ");
	setFont(GLUT_BITMAP_HELVETICA_12);
	glColor3f(1.0,0.0,0.0);
	drawstring(125.0,180,1.0,"1. USE NAVIGATION KEYS");
	setFont(GLUT_BITMAP_HELVETICA_12);
	glColor3f(1.0,0.0,0.0);
	drawstring(140.0,160,1.0,"FOR WINDOW MOVEMENT");

	setFont(GLUT_BITMAP_HELVETICA_12);
	glColor3f(1.0,0.0,0.0);
	drawstring(125.0,140,1.0,"2. USE ENTER KEY FOR PITS");

	setFont(GLUT_BITMAP_HELVETICA_12);
	glColor3f(1.0,0.0,0.0);
	drawstring(140.0,120,1.0,"SELECTION");

}
void rotate_board()
{
	int sw1,sw2,sw3,sw4;
	sw1=ca; sw2=cb; sw3=cc; sw4=cd;
	ca=ce; cb=cf; cc=cg; cd=ch;
	ce=sw1; cf=sw2; cg=sw3; ch=sw4;
	swap=!swap;
	printf("Board rotated\n");
	printf("ca=%d ",ca);
	printf("cb=%d ",cb);
	printf("cc=%d ",cc);
	printf("cd=%d ",cd);
	printf("ce=%d ",ce);
	printf("cf=%d ",cf);
	printf("cg=%d ",cg);
	printf("ch=%d \n",ch);
	bchg=!bchg;
}
void screen_rotate(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	{	glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,580.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,580.0);
	}
	glEnd();
	glFlush();
	glFlush();

	setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
	drawstring(155.0,365.0,1.0,"  *  *  *  ROTATING BOARD *  *  *  ");

	glFlush();
	//sndPlaySound("sword.wav",SND_ASYNC);
	//Sleep(1500);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Game_over(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	{
		glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,20.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(780.0,580.0);
		glColor3f(0.6,0.3,0.0);
		glVertex2i(20.0,580.0);
	}
	glEnd();
	glFlush();
	glFlush();

	setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
	drawstring(155.0,365.0,1.0,"  *  *  *  GAME OVER *  *  *  ");

	glFlush();
//	sndPlaySound("end.wav",SND_ASYNC);

	if(point1>point2)
	{
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(0.0,1.0,0.0);
		drawstring(300.0,200.0,1.0,"PLAYER : 1 WINS THE GAME");
		glFlush();
	}
	if(point2>point1)
	{
		setFont(GLUT_BITMAP_HELVETICA_18);
		glColor3f(0.0,1.0,0.0);
		drawstring(300.0,200.0,1.0,"PLAYER : 2 WINS THE GAME");
		glFlush();
	}

	//Sleep(1500);
}

