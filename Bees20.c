/*bees2.0�� ����� ����تZ��*/
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define   DELAY 50       /*�C��delay ms*/
#define   HMB   40       /*�e����,�����ܼ�r*/
#define   HMG1  4        /*�ڤ�l�u��*/
#define   HMG2  50       /*�e���l�u��*/
#define   HMAPM 3        /*�@�����ʫ���j���*/
#define   HFAPM 3        /*�C�j�鲾�ʹ��I��*/
#define   HMADD 100      /*�e�����k���ʶZ��*/
#define   APL   30       /*��������*/
#define   APR   609      /*�����k��*/
#define   BEESTOP -10    /*�e���M�εe�����A�W�U�`����*/
#define   GUNTOP -100    /*�e����*/
#define   GUNBOTTOM 399  /*�e����*/
#define   HLG2  5        /*�e���l�u��*/
#define   HFG2  5        /*�e���l�u�C�j��U�����I��*/
#define   SL    0        /*�I������*/
#define   SR    640      /*�I���k��*/
#define   HMR   3        /*�e���������u�`��*/
#define   HMSTEP 206     /*�������u�B��*/
#define   HMS   6        /*�����`�ơA1-5�A0���L�n*/
#define   MAXS  50       /*���ĳ̪��W��*/

void ATC(void);          /*�]�w�@�e������*/
void SHOOT1(void);       /*�����g�l�u*/
void SHOOT2(void);       /*�e���g�l�u*/
void MOVE_ADD(void);     /*�e�������k��*/
void INPUT(void);        /*��J*/
void APMOV(void);        /*��������*/
void GUNMOV(void);       /*����l�u����*/
void BOOM(void);         /*�����e��*/
void APBOOM(void);       /*��������*/
void SOUND(void);        /*��X�n��*/
void OUTPUT(void);       /*��X�e��*/
void STAR(void);         /*���ͭI���P�P*/
void WEAPON(void);
void MAKE_WEAPON(int,int,int);

struct WEAPON
{
	int x,y;
	char life,type;
}weapon;
struct BEES              /*�e�����c*/
{
	int x,y;            /*�y��*/
	char life,atc,ro;   /*��A�������H�A�������u*/
	unsigned char where;/*�����B�ơAmax 206*/
	char t;             /*�e������*/
}BEES[HMB];
struct AP                /*�����Τl�u���c*/
{
	int x,y;            /*�y��*/
	char life,active;   /*����*/
}AP;
struct GUN1              /*�ڤ�l�u*/
{
	int x,y;            /*�y��*/
	char life,l;     	/*�l�u���L�H�A����*/
	int tx,ty;       	/*�l�ܥؼ�*/
}GUN1[HMG1];
struct GUN2              /*�e���l�u*/
{
	int x,y;           	/*�y��*/
	char life;         	/*�l�u���L*/
}GUN2[HMG2];
struct star              /*�I���P�P���c*/
{
	int y;              /*y�y��*/
	char c;             /*�C��*/
}static star[SR-SL+1];   /*�P�P�ƶq�P�ù��e�׬ۦP*/
struct ro                /*�e�����ʸ��u���c*/
{
	int x,y;            /*�U���y�Ц첾�q(�V�q)*/
}ro[HMR][HMSTEP];        /*�s��������uarray*/

FILE *fp[12];            /*�}�ɥ��ɮ׫���*/
void *app,*bp,*bp2,*bp2n,*bo1,*bo2,*bo3,*wl,*wd;	/*���V�Ϥ�buffer����*/
long score=0,addscore=0; /*�s����ƪ��ܼ�*/
char sbuf[40];          	/*�s����Ʀr��*/
int n=0,s=0,r=0,l=0,om=0,dela=DELAY,round=1,
    cos=10000,cog2=1000,dog2=800,coa=100,
    sou[HMS][MAXS],sp1=0,sp2=0,soun=1,ingame=1,
    gamestatus=0,statuscounter=0;
					/*   n:�e�������k���p�ƾ�*/
					/*   s:�e�������k���X��  */
					/*   l:�p�g�X��          */
					/*  om:�������ʭp�ƾ�    */
					/* cos:�P�P�X�{���v      */
					/*cog2:�e���g�����v      */
					/*dog2:�e�������ɾ��v���@*/
					/* coa:�e����������v    */
					/*   sou:�s���n��array	*/
					/*   sp1:���V�������n��*/
					/*   sp2:���V�n����step	*/
					/*  soun:�n���}��		*/
int color[16]={0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63},bug;

main()
{
	int i,j,k,drive=VGA,mode=VGAMED;
	char filename[12][40]={"bees.sav",
					   "bees.rod",
					   "bees.snd",
					   "bees.bug",
					   "bees.b2",
					   "bees.b2n",
					   "bees.bos",
					   "bees.bo2",
					   "bees.bo3",
					   "bees.ap",
					   "beesl.img",
					   "beesd.img"};
	randomize();
	initgraph(&drive,&mode,"");
	if(graphresult()!=grOk)	/*�Ұ�ø�ϼҦ�*/
     {
          printf("EGAVGA.BGI not found!\n\7\7");
          fcloseall();
          getch();
          exit(1);
     }
     setactivepage(0);
	setvisualpage(1);
	setbkcolor(0);
	for(i=10;i<12;i++)
	{
		if((fp[i]=fopen(filename[i],"r+b"))==NULL)
		{
			printf("%s not found!\n\7\7",filename[i]);
			fcloseall();
			exit(0);
		}
	}
	wl=(void *)malloc(imagesize(0,0,19,19));
	wd=(void *)malloc(imagesize(0,0,19,19));
	fread(wl,imagesize(0,0,19,19),1,fp[10]);
	fread(wd,imagesize(0,0,19,19),1,fp[11]);
	fclose(fp[10]);
	fclose(fp[11]);
	for(i=0;i<10;i++)
     {
          if((fp[i]=fopen(filename[i],"r+t"))==NULL)
          {
               printf("%s not found!\n\7\7",filename[i]);
               fcloseall();
               exit(0);
          }
     }
     for(i=0;i<HMSTEP;i++)                                  /*Ū�����u��*/
     {
          for(j=0;j<HMR;j++)
          {
               fscanf(fp[1],"%d %d",&ro[j][i].x,&ro[j][i].y);
          }
     }
     for(i=0;i<MAXS;i++)
     {
          for(j=0;j<HMS;j++)
          {
               fscanf(fp[2],"%d",&sou[j][i]);
          }
     }
     for(i=0;i<20;i++)             /*�e����*/
     {
          for(j=0;j<20;j++)
          {
			fscanf(fp[3],"%d",&bug);
               putpixel(j,i,bug);
               fscanf(fp[4],"%d",&bug);
               putpixel(i+20,j,bug);
               fscanf(fp[5],"%d",&bug);
               putpixel(i+40,j,bug);
               fscanf(fp[6],"%d",&bug);
               putpixel(i+60,j,bug);
               fscanf(fp[7],"%d",&bug);
               putpixel(i+80,j,bug);
               fscanf(fp[8],"%d",&bug);
			putpixel(i+100,j,bug);
          }
     }
     for(i=0;i<36;i++)               /*�e����*/
     {
          for(j=0;j<35;j++)
          {
               fscanf(fp[9],"%d",&bug);
               putpixel(j+100,i+100,bug);
          }
     }
     for(i=1;i<10;i++)
     {
          fclose(fp[i]);
     }
     bp=malloc(imagesize(0,0,19,19));        /*�s��*/
     getimage(0,0,19,19,bp);
	bp2=malloc(imagesize(20,0,39,19));
     getimage(20,0,39,19,bp2);
	bp2n=malloc(imagesize(40,0,59,19));
     getimage(40,0,59,19,bp2n);
	bo1=malloc(imagesize(60,0,79,19));
     getimage(60,0,79,19,bo1);
	bo2=malloc(imagesize(80,0,99,19));
     getimage(80,0,99,19,bo2);
	bo3=malloc(imagesize(100,0,119,19));
     getimage(100,0,119,19,bo3);
     app=malloc(imagesize(100,100,134,135));
	getimage(100,100,134,135,app);
	AP.life=3;                    /*�w�������*/
     AP.x=320;
	AP.y=getmaxy()-50;
	AP.active=1;
	weapon.life=0;
     for(i=0;i<HMG1;i++)           /*�w�ڤ�l�u���*/
     {
          GUN1[i].life=0;
     }
     for(i=0;i<HMG2;i++)             /*�w�e���l�u���*/
     {
          GUN2[i].life=0;
     }
	for(i=0;ingame;i=!i,statuscounter++)        /*�j�j��}�l*/
	{
		switch(gamestatus)
		{
			case 0:
				statuscounter=0;
				if(!AP.active)
				{
					AP.x=320;
					AP.active=1;
				}
				gamestatus=1;
				break;
			case 1:
				if(statuscounter==50)
				gamestatus=2;
				break;
			case 2:
				rewind(fp[0]);
				fprintf(fp[0],"ROUND %d%c",round,'\0');
				rewind(fp[0]);
				fgets(sbuf,39,fp[0]);
				outtextxy(290,150,sbuf);
				if(statuscounter==100)
				gamestatus=3;
				break;
			case 3:
				if(statuscounter==150)
				gamestatus=4;
				break;
			case 4:
				rewind(fp[0]);
				fprintf(fp[0],"READY%c",'\0');
				rewind(fp[0]);
				fgets(sbuf,39,fp[0]);
				outtextxy(290,150,sbuf);
				AP.active=2;
				if(statuscounter==200)
				gamestatus=5;
				break;
			case 5:
				if(!r)
				{
					for(j=0;j<(HMB/10);j++)         /*�w�e�����*/
					{
						for(k=0;k<10;k++)
						{
							BEES[j*10+k].atc=0;     /*�k�s�������A*/
							BEES[j*10+k].x=k*40+130; /*�]�w�y��*/
							BEES[j*10+k].y=j*30+20;
						}
					}
					for(j=0;j<HMB/2;j++)              /*�e�b���f��*/
					{
						BEES[j].life=2;
						BEES[j].t=1;
					}
					for(;j<HMB;j++)                   /*��b������*/
					{
						BEES[j].life=1;
						BEES[j].t=0;
					}
					for(j=0;j<4;j++)                  /*4���e��*/
					{
						BEES[j+3].life=3;
						BEES[j+3].t=2;
					}
					n=50;
					r=HMB;
					addscore=100;
				}
				gamestatus=6;
				break;
			case 6:
				if(!r)
				{
					gamestatus=7;
					r=0;
				}
				break;
			case 7:
				round++;             /*�L���A�W�[����*/
				dela-=3;
				coa-=10;
				cog2-=100;
				dog2-=10;
				n=50;
				s=0;
				gamestatus=0;
				break;
			case 8:
				setcolor(EGA_RED);
				setlinestyle(0,0,1);
				setfillstyle(SOLID_FILL,EGA_RED);
				if(statuscounter<30)
				pieslice(AP.x,AP.y+20,0,360,statuscounter*5);
				for(j=0,k=0;j<HMB;j++)
				{
					k+=BEES[j].atc;
				}
				if(statuscounter>100&&!k)
					gamestatus=0;
				if(!AP.life&&statuscounter>100)
					gamestatus=9;
				break;
			case 9:
				rewind(fp[0]);
				fprintf(fp[0],"GAME OVER%c",'\0');
				rewind(fp[0]);
				fgets(sbuf,39,fp[0]);
				outtextxy(290,150,sbuf);
			default:
				break;
		}
		setactivepage(i);
		setfillstyle(0,0);
		bar(0,0,getmaxx(),getmaxy());/*�M���ù�*/
		STAR();                      /*�e�P�P*/
		if(!random(coa))
		{
			if(gamestatus==6)
                    ATC();                  /*����*/
		}
		if(i)                         /*��鲾�ʤ@��*/
		{
			MOVE_ADD();              /*�e������*/
		}
		if(gamestatus==6)
			SHOOT2();                       /*�e���g��*/

		GUNMOV();                       /*�l�u����*/
		BOOM();
		if(weapon.life)					/*�P�_�O�_����*/
			WEAPON();
		if(kbhit())
		{
			INPUT();                /*��J*/
		}
		if(soun)
		{
			SOUND();
		}
		if(om)                        /*�p�������ʤ�,�~�򲾰�*/
		{
			APMOV();
		}
		OUTPUT();                      /*��X*/
		setvisualpage(i);
		delay(dela);
	}                                     /*�j�j�鵲��*/
     nosound();                                 /*�C������*/
	free(bp);
	free(bp2);
	free(bp2n);
	free(bo1);
	free(bo2);
	free(bo3);
	free(app);
	free(wl);
	free(wd);
     fcloseall();
     closegraph();
}

void ATC(void)
{
     int i,j,c;
     for(i=0;i<100;i++)
     {
          c=random(HMB);
		if((BEES[c].life>0)&&(!BEES[c].atc))
          {
               switch(BEES[c].t)
               {
				case 0:          /*��������*/
                          BEES[c].atc=1;
                          BEES[c].ro=random(2);
                          BEES[c].where=0;
                          break;
                     case 1:                      /*�f������*/
                          BEES[c].atc=1;
                          if(BEES[c].life==2)
                          {
                               BEES[c].ro=2;      /*�����*/
                          }
                          else                    /*���ˮ�*/
                          {
                               BEES[c].ro=random(3);
                          }
                          BEES[c].where=0;
                          break;
                     case 2:                      /*�e������*/
                          BEES[c].atc=1;
                          BEES[c].where=0;
                          if(BEES[c].life==1)     /*��W*/
                          {
                               BEES[c].ro=2;
                          }
                          else                    /*�a�@��*/
                          {
                               BEES[c].ro=random(2);
                               for(j=0;j<3;j++)
                               {
                                    if(BEES[c+9+j].life&&(!BEES[c+9+j].atc))
                                    {
                                         BEES[c+9+j].atc=1;
                                         BEES[c+9+j].ro=BEES[c].ro;
                                         BEES[c+9+j].where=0;
                                    }
                               }
                          }
                          break;
               }
               sp1=1;                             /*�]�w����*/
               sp2=0;
               return;
          }
     }
}

void SHOOT2(void)               /*�e���g��*/
{
     int i,j;
     for(i=0;i<HMB;i++)
     {
		if(BEES[i].life>0)
          {
               for(j=0;(j<HMG2)&&(GUN2[j].life==1);j++);  /*��X�e���l�u���Ů�*/
               if(j==HMG2)/*�P�_�l�u�ƬO�_�B��*/
               {
                    return;
               }
               if(random(cog2-BEES[i].atc*dog2)==0)
               {                                 /*�g�l�u*/
                    GUN2[j].x=BEES[i].x;
                    GUN2[j].y=BEES[i].y+HLG2;
                    GUN2[j].life=1;
               }
          }
     }
}

void SHOOT1(void)   /*�����l�u*/
{
	int p,q;
	switch(l)
	{
		case 0:
		case 1:
			for(p=0;(GUN1[p].life==1)&&(p<2);p++);  /*�̦h�G�o*/
			if(p==2)                                /*�p�S���Ů�*/
			{
				return;
			}
			break;
		case 2:/*�l�ܭ��u*/
			for(p=0;(GUN1[p].life==1)&&(p<1);p++);  /*�̦h�@�o*/
			if(p)                                   /*�p�S���Ů�*/
			{
				return;
			}
			break;
		case 3:
			for(p=0;(GUN1[p].life==1)&&(p<4);p++);
			for(q=p+1;(GUN1[q].life==1)&&(q<4);q++);
			if(q>=4)                                   /*�p�S���Ů�*/
			{
				return;
			}
			break;
		default:
			break;
	}
	if(l==3)
	{
		GUN1[p].life=GUN1[q].life=1;
		GUN1[p].l=GUN1[q].l=0;
		GUN1[p].y=GUN1[q].y=AP.y-1;
		GUN1[p].x=AP.x-15;
		GUN1[q].x=AP.x+15;
	}
	else
	{
		GUN1[p].life=1;
		GUN1[p].l=l;
		GUN1[p].x=AP.x;
		GUN1[p].y=AP.y-1;
		GUN1[p].tx=AP.x;
		GUN1[p].ty=GUNTOP-1000;
	}
     sp1=3;               /*�]�w����*/
	sp2=0;
	addscore--;
}

void MOVE_ADD()         /*�e�����ʥ��k�j��*/
{
     int i;
     if(n==HMADD)         /*�p�w���ʳ]�w�B��*/
     {
          s=!s;           /*�h�Ϥ�V*/
          n=0;
     }
     for(i=0;i<HMB;i++)
     {
		if(BEES[i].life>0)
          {
               if(s)
               {
                    BEES[i].x--;  /*����*/
               }
               else
               {
                    BEES[i].x++;  /*�k��*/
               }
               if(BEES[i].atc)    /*�����ɤ�����*/
               {
                    if((!ro[BEES[i].ro][BEES[i].where].x)&&  /*�p�����첾=0*/
                       (!ro[BEES[i].ro][BEES[i].where].y))
                    {
                         BEES[i].atc=0;  /*��������*/
                    }
                    else
                    {
                         BEES[i].x+=ro[BEES[i].ro][BEES[i].where].x;
                         BEES[i].y+=ro[BEES[i].ro][BEES[i].where].y;
                         BEES[i].where++;
                    }
               }
               if(BEES[i].x>SR)           /*�p�W�L�k��*/
               {
                    BEES[i].x-=SR-SL+1;   /*���쥪��*/
               }
               if(BEES[i].x<SL)           /*�p�W�L����*/
               {
                    BEES[i].x+=SR-SL+1;   /*����k��*/
               }
               if(BEES[i].y>GUNBOTTOM)    /*�p�W�L�U��*/
               {
                    BEES[i].y-=GUNBOTTOM-BEESTOP+1;  /*���ܤW��*/
               }
               if(BEES[i].y<BEESTOP)      /*�p�W�L�W��*/
               {
                    BEES[i].y+=GUNBOTTOM-BEESTOP+1;  /*���ܤU��*/
               }
          }
     }
     n++;
}

void INPUT(void)            /*��J*/
{
     char in;
     in=getch();
     switch(in)
     {
		case ',':           /*����*/
			om=-1;
               break;
          case '.':           /*�k��*/
			om=1;
               break;
          case 's':           /*�n���}��*/
               soun=!soun;
               nosound();
               break;
          case 'p':           /*�Ȱ�*/
			nosound();
			setactivepage(0);
			OUTPUT();
			rewind(fp[0]);
			fprintf(fp[0],"TEE TIME!%c",'\0');
			rewind(fp[0]);
			fgets(sbuf,39,fp[0]);
			outtextxy(270,170,sbuf);
			setvisualpage(0);
               getch();
               break;
          case 'q':           /*quit*/
			ingame=0;
               break;
		default:/*    �g��         */
			if(AP.active==2)
				SHOOT1();
               break;
     }
}

void APMOV()
{
     if((om-1!=HMAPM)&&(om+1!=-HMAPM))  /*�pom counter�|���W�LHMAPM(How many AP move)*/
     {
          if(om>0)
          {
               AP.x+=HFAPM;
               if(AP.x>=APR)
               {
                    AP.x=APR;
                    om=0;
                    return;
               }
               om++;
          }
          else
          {
               AP.x-=HFAPM;
               if(AP.x<=APL)
               {
                    AP.x=APL;
                    om=0;
                    return;
               }
               om--;
          }
     }
     else
     {
          om=0;
     }
}

void GUNMOV()          /*�l�u����*/
{
     int a,i,j;
     for(i=0;i<HMG1;i++)
     {
          if(GUN1[i].life)
          {
               if(GUN1[i].l==2)  /*�l�ܭ��u*/
               {
                    GUN1[i].tx=GUN1[i].x;
                    GUN1[i].ty=GUN1[i].y-1000;
                    for(j=0;j<HMB;j++)
                    {
                          if((BEES[j].life>0)&&  /*�P�_�ó]�w�l�ܥؼ�*/
                            ( (abs(AP.x-BEES[j].x)+abs(AP.y-BEES[j].y)  )<
                            (abs(AP.x-GUN1[i].tx)+abs(AP.y-GUN1[i].ty))) )
                            {
                                    GUN1[i].tx=BEES[j].x;
                                    GUN1[i].ty=BEES[j].y-5;
                            }
                    }
                                GUN1[i].x+=5*(GUN1[i].tx>GUN1[i].x+5)+(-5)*(GUN1[i].tx<GUN1[i].x-5);
                                GUN1[i].y+=5*(GUN1[i].ty>GUN1[i].y+5)+(-5)*(GUN1[i].ty<GUN1[i].y-5);
               }
               else
               {
                    if(GUN1[i].l)  /*�p�g*/
                    {
                         GUN1[i].y-=5;
                    }
                    else           /*���q�l�u*/
                    {
					GUN1[i].y-=20;
                    }
               }
               if(GUN1[i].y<GUNTOP)  /*�p�W�X�W��*/
               {
                    GUN1[i].life=0;  /*�M��*/
               }
          }
     }
     for(a=0;a<HMG2;a++)             /*�e���l�u*/
     {
          GUN2[a].y+=HFG2;           /*�U��*/
          if(GUN2[a].y>GUNBOTTOM)    /*�p�W�X�U��*/
          {
               GUN2[a].life=0;       /*�M��*/
          }
     }
}

void BOOM()              /*�����P�_*/
{
     int a,b;
     for(a=0;a<HMG1;a++)  /*�e���P�ڤ�l�u*/
     {
          for(b=0;(b<HMB)&&GUN1[a].life;b++)
          {
			if(BEES[b].life>0)
               {
                    if(!GUN1[a].l)  /*���q�l�u*/
                    {
					if((BEES[b].y>=GUN1[a].y)&&(BEES[b].y<=GUN1[a].y+25)&&
                            (GUN1[a].x>=BEES[b].x-9)&&(GUN1[a].x<=BEES[b].x+10))
                         {
                              BEES[b].life--;  /*�e���l��*/
                              if(!BEES[b].life)  /*���F�H*/
                              {
							r--;
							BEES[b].atc=0;
							score+=addscore;  /*�[��*/
							if(BEES[b].t==2)
								MAKE_WEAPON(4,BEES[b].x,BEES[b].y);
                              }
                              GUN1[a].life=0;   /*�M���l�u*/
                              sp1=2;            /*����������*/
                              sp2=0;
                         }
                    }
                    if(GUN1[a].l==1)            /*�p�g*/
                    {
                         if((BEES[b].y>=GUN1[a].y)&&(BEES[b].y<=GUN1[a].y+100)&&
                            (GUN1[a].x>=BEES[b].x-9)&&(GUN1[a].x<=BEES[b].x+10))
                         {
                              if(BEES[b].t==2)  /*�����e��*/
                              {
                                   BEES[b].life-=2;  /*�l��*/
                                   if(BEES[b].life<=0)  /*�����F�H*/
                                   {
                                        BEES[b].life=0;
								r--;
								BEES[b].atc=0;
								score+=addscore;
								if(BEES[b].t==2)
									MAKE_WEAPON(4,BEES[b].x,BEES[b].y);
                                        sp1=2;
                                        sp2=0;
                                   }
                                   else                /*�S��*/
                                   {
                                        GUN1[a].life=0;  /*�l���p�g*/
                                        sp1=4;
                                        sp2=0;
                                   }
                              }
                              else  /*������L*/
                              {
                                   BEES[b].life--;
                                   if(!BEES[b].life)
                                   {
								r--;
								BEES[b].atc=0;
                                        score+=addscore;
                                        sp1=2;
                                        sp2=0;
                                   }
                              }
                         }
                    }
                    if(GUN1[a].l==2)  /*�l�ܭ��u*/
                    {
                         if((BEES[b].y>=GUN1[a].y)&&(BEES[b].y<=GUN1[a].y+10)&&
                            (GUN1[a].x+5>=BEES[b].x-9)&&(GUN1[a].x-5<=BEES[b].x+10))
                         {
                              BEES[b].life--;
                              if(!BEES[b].life)
                              {
							r--;
							BEES[b].atc=0;
                                   score+=addscore;
                              }
                              GUN1[a].life=0;
                              sp1=2;
                              sp2=0;
                         }
                    }
               }
          }
	}
	if(AP.active)
	{
		for(a=0;a<HMG2;a++)   /*�ڤ�P�e���l�u*/
		{
			if(GUN2[a].life&&(AP.y+20<=GUN2[a].y)&&(AP.y+20>=GUN2[a].y-HFG2)&&
			  (GUN2[a].x>=AP.x-17)&&(GUN2[a].x<=AP.x+17))
			{
				GUN2[a].life=0;
				AP.life--;
				APBOOM();                 /*�z���Ƶ{��*/
				return;
			}
		}
		for(a=0;a<HMB;a++)  /*�e���P����*/
		{
			if(BEES[a].life>0)
			{
				if(((BEES[a].x-9<=AP.x+2)&&(BEES[a].x+10>=AP.x-2)&&
				    (BEES[a].y>=AP.y+3)&&(BEES[a].y<=AP.y+35))||
				   ((AP.y+20>=BEES[a].y-12)&&(AP.y+20<=BEES[a].y+1)&&
				    (AP.x+17>=BEES[a].x-9)&&(AP.x-17<=BEES[a].x+10)))
				{
					AP.life--;
					BEES[a].life--;
					if(!BEES[a].life)
					{
						r--;
						BEES[a].atc=0;
						score+=addscore;
					}
					APBOOM();
					return;
				}
			}
		}
	}
}

void APBOOM(void)        /*�z��*/
{
	gamestatus=8;
	statuscounter=0;
	AP.active=0;
	l=0;
	sp1=5;
	sp2=0;
	return;
}

void SOUND(void)
{
     if(sou[sp1][sp2])
     {
          sound(sou[sp1][sp2]);
          sp2++;
     }
     else
     {
          nosound();
          sp1=sp2=0;
     }
}

void OUTPUT(void)        /*��X���*/
{
	int i;
	setcolor(YELLOW);
	setlinestyle(0,0,3);
     for(i=0;i<HMG1;i++)   /*�e�ڤ�l�u*/
     {
          if(GUN1[i].life)
          {
               switch(GUN1[i].l)
               {
                    case 0:
                         line(GUN1[i].x,GUN1[i].y,GUN1[i].x,GUN1[i].y+10);
                         break;
                    case 1:
                         line(GUN1[i].x,GUN1[i].y,GUN1[i].x,GUN1[i].y+100);
                         break;
                    case 2:
					setlinestyle(0,0,0);
                         circle(GUN1[i].x,GUN1[i].y+5,5);
                         break;
               }
          }
     }
	if(AP.active)  /*�e����*/
     {
          putimage(AP.x-17,AP.y,app,COPY_PUT);
     }
     for(i=0;i<HMG2;i++)  /*�e�e���l�u*/
     {
          if(GUN2[i].life)
          {
               setlinestyle(0,0,3);
               line(GUN2[i].x,GUN2[i].y,GUN2[i].x,GUN2[i].y-HLG2);
          }
     }
     for(i=0;i<HMB;i++)  /*�e�e��*/
     {
		if(BEES[i].life>0)
          {
               switch(BEES[i].t)
               {
                    case 0:
					putimage(BEES[i].x-9,BEES[i].y-14,bp,COPY_PUT);
                         break;
                    case 1:
                         if(BEES[i].life==2)
                         {
                              putimage(BEES[i].x-9,BEES[i].y-14,bp2,COPY_PUT);
                         }
                         else
                         {
                              putimage(BEES[i].x-9,BEES[i].y-14,bp2n,COPY_PUT);
                         }
                         break;
				case 2:
                         if(BEES[i].life==3)
                         {
                              putimage(BEES[i].x-9,BEES[i].y-14,bo1,COPY_PUT);
                         }
                         else
                         {
                              if(BEES[i].life==2)
                              {
                                   putimage(BEES[i].x-9,BEES[i].y-14,bo2,COPY_PUT);
                              }
                              else
                              {
                                   putimage(BEES[i].x-9,BEES[i].y-14,bo3,COPY_PUT);
                              }
                         }
                         break;
               }
          }
     }
	rewind(fp[0]);  /*��ܤ���*/
	fprintf(fp[0],"SCORE  %ld%c",score,'\0');
	rewind(fp[0]);
	fgets(sbuf,39,fp[0]);
	outtextxy(0,0,sbuf);
	rewind(fp[0]);
	fprintf(fp[0],"PLAYER %d%c",AP.life,'\0');
	rewind(fp[0]);
	fgets(sbuf,39,fp[0]);
	outtextxy(0,10,sbuf);
}

void STAR(void)
{
	int i,w=SR-SL+1;
	for(i=0;i<w;i++)
     {
          if(star[i].y)  /*�p�P�P�w�s�b*/
          {
               putpixel(i,star[i].y,color[star[i].c]);  /*�e*/
               star[i].y+=(star[i].c>7)+1;  /*����*/
               if(star[i].y>=GUNBOTTOM)
               {
                    star[i].y=0;
               }
          }
          else
          {
               if(!random(cos))  /*cos��10000*/
               {
                    star[i].c=random(16);
                    star[i].y=1;
               }
          }
     }
}
void WEAPON(void)
{
	int i,w;
	weapon.y+=3;
	if(weapon.y>=AP.y)
	{
		if((weapon.x>=AP.x-17)&&(weapon.x<=AP.x+17))
		{
			weapon.life=0;
			l=weapon.type*2+1;
		}
	}
	if(weapon.y>GUNBOTTOM)
	{
		weapon.life=0;
	}
	if(weapon.type)
	{
		putimage(weapon.x-10,weapon.y-10,wd,COPY_PUT);
	}
	else
	{
		putimage(weapon.x-10,weapon.y-10,wl,COPY_PUT);
	}
}
void MAKE_WEAPON(int c,int x,int y)
{
	if(!weapon.life)
	{
		if(!random(c))
		{
			weapon.x=x;
			weapon.y=y;
			weapon.type=random(2);
			weapon.life=1;
		}
	}
}