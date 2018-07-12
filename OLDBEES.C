#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define   DELAY 50
#define   HMB   40       /*蜜蜂數,對應變數r*/
#define   HMG1  2        /*我方子彈數*/
#define   HMG2  50       /*蜜蜂子彈數*/
#define   HMAPM 3        /*一次移動持續迴圈數*/
#define   HFAPM 3        /*每迴圈移動像點數*/
#define   HMADD 150      /*蜜蜂左右移動距離*/
#define   APL   30       /*飛機左界*/
#define   APR   609      /*飛機右界*/
#define   BEESTOP -10
#define   GUNTOP -100    /*畫面頂*/
#define   GUNBOTTOM 399  /*畫面底*/
#define   HLG2  5        /*蜜蜂子彈長*/
#define   HFG2  5        /*蜜蜂子彈每迴圈下移像點數*/
#define   SL    0        /*背景左界*/
#define   SR    640      /*背景右界*/
#define   HMR   3
#define   HMSTEP 206
#define   HMS   5        /*1-4*/
#define   MAXS  50

void ATC(void);          /*設定一蜜蜂攻擊*/
void SHOOT1(void);       /*飛機射子彈*/
void SHOOT2(void);       /*蜜蜂射子彈*/
void MOVE_ADD(void);     /*蜜蜂左移右移*/
void INPUT(void);        /*輸入*/
void APMOV(void);        /*飛機移動*/
void GUNMOV(void);       /*雙方子彈移動*/
void BOOM(void);         /*擊中蜜蜂*/
void APBOOM(void);       /*擊中飛機*/
void SOUND(void);
void OUTPUT(void);       /*輸出畫面*/
void STAR(void);         /*產生背景星星*/

struct BEES              /*蜜蜂結構*/
{
     int x,y;
     char life,atc,ro;
     unsigned char where;    /*max 206*/
     char t;
}BEES[HMB];
struct AP                /*飛機及子彈結構*/
{
     int x,y;
     char life;
}AP;
struct GUN1
{
     int x,y;
        char life,l;
        int tx,ty;

}GUN1[HMG1];
struct GUN2
{
        int x,y;
        char life;
}GUN2[HMG2];
struct star              /*背景星星結構*/
{
     int y;
     char c;
}static star[SR-SL+1];
struct ro                /*蜜蜂移動路線結構*/
{
     int x,y;
}ro[HMR][HMSTEP];

FILE *fp1,*fp2;
void *app,*bp,*bp2,*bp2n,*bo1,*bo2,*bo3;
long score=0;
char sbuf[40];          /*存放分數字串*/
int n=0,s=0,r=HMB,l=0,om=0,dela=DELAY,round=1,
    cos=10000,cog2=1000,dog2=800,coa=100,
    sou[HMS][MAXS],sp1=0,sp2=0,soun=1;
                            /*   n:蜜蜂左移右移計數器 */
                            /*   s:蜜蜂左移右移旗標   */
                            /*   l:雷射旗標           */
                            /*  om:飛機移動計數器     */
                            /* cos:星星出現機率       */
                            /*cog2:蜜蜂射擊機率       */
                            /*dog2:蜜蜂攻擊時機率提昇 */
                            /* coa:蜜蜂整體攻擊率     */
int color[16]={0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63},bug;

main()
{
     int i,j,drive=VGA,mode=VGAMED;
     randomize();
        if((fp1=fopen("e:\\tc\\file\\bees.sav","r+t"))==NULL)   /*開啟分數檔*/
     {
          printf("bees.sav not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
        if((fp2=fopen("e:\\tc\\file\\bees.rod","rt"))==NULL)   /*開啟路線檔*/
     {
          printf("bees.rod not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<HMSTEP;i++)                                  /*讀取路線檔*/
     {
          for(j=0;j<HMR;j++)
          {
               fscanf(fp2,"%d %d",&ro[j][i].x,&ro[j][i].y);
          }
     }
     fclose(fp2);                                   /*關閉路線檔*/
        if((fp2=fopen("e:\\tc\\file\\bees.snd","rt"))==NULL)
     {
          printf("bees.snd not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<MAXS;i++)
     {
          for(j=0;j<HMS;j++)
          {
               fscanf(fp2,"%d",&sou[j][i]);
          }
     }
     fclose(fp2);
        initgraph(&drive,&mode,"e:\\tc");
     if(graphresult()!=grOk)         /*啟動繪圖模式*/
     {
          printf("EGAVGA.BGI not found!\n\7\7");
          fcloseall();
          getch();
          exit(1);
     }
     setactivepage(0);
        setvisualpage(1);
     setbkcolor(0);
     setcolor(YELLOW);
     setlinestyle(0,0,3);
        if((fp2=fopen("e:\\tc\\file\\bees.bug","rt"))==NULL)
     {
          printf("bees.bug not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<20;i++)             /*畫蝴蝶*/
     {
          for(j=0;j<20;j++)
          {
               fscanf(fp2,"%d",&bug);
               putpixel(j,i,bug);
          }
     }
     fclose(fp2);
        if((fp2=fopen("e:\\tc\\file\\bees.b2","rt"))==NULL)
     {
          printf("bees.b2 not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<20;i++)             /*畫蝴蝶*/
     {
          for(j=0;j<20;j++)
          {
               fscanf(fp2,"%d",&bug);
                        putpixel(i+20,j,bug);
          }
     }
     fclose(fp2);
        if((fp2=fopen("e:\\tc\\file\\bees.b2n","rt"))==NULL)
     {
          printf("bees.b2n not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<20;i++)             /*畫蝴蝶*/
     {
          for(j=0;j<20;j++)
          {
               fscanf(fp2,"%d",&bug);
                        putpixel(i+40,j,bug);
          }
     }
     fclose(fp2);
        if((fp2=fopen("e:\\tc\\file\\bees.bos","rt"))==NULL)
     {
          printf("bees.bos not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<20;i++)             /*畫蝴蝶*/
     {
          for(j=0;j<20;j++)
          {
               fscanf(fp2,"%d",&bug);
               putpixel(i+60,j,bug);
          }
     }
     fclose(fp2);
        if((fp2=fopen("e:\\tc\\file\\bees.bo2","rt"))==NULL)
     {
          printf("bees.bo2 not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<20;i++)             /*畫蝴蝶*/
     {
          for(j=0;j<20;j++)
          {
               fscanf(fp2,"%d",&bug);
               putpixel(i+80,j,bug);
          }
     }
     fclose(fp2);
        if((fp2=fopen("e:\\tc\\file\\bees.bo3","rt"))==NULL)
     {
          printf("bees.bo3 not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<20;i++)             /*畫蝴蝶*/
     {
          for(j=0;j<20;j++)
          {
               fscanf(fp2,"%d",&bug);
               putpixel(i+100,j,bug);
          }
     }
     fclose(fp2);
        if((fp2=fopen("e:\\tc\\file\\bees.ap","rt"))==NULL)
     {
          printf("bees.ap not found!\n\7\7");
          fcloseall();
          getch();
          exit(0);
     }
     for(i=0;i<36;i++)               /*畫飛機*/
     {
          for(j=0;j<35;j++)
          {
               fscanf(fp2,"%d",&bug);
               putpixel(j+100,i+100,bug);
          }
     }
     fclose(fp2);
     bp=malloc(imagesize(0,0,19,19));        /*存圖*/
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
        AP.life=3;                    /*定飛機初值*/
     AP.x=320;
     AP.y=getmaxy()-50;
     for(i=0;i<HMG1;i++)           /*定我方子彈初值*/
     {
          GUN1[i].life=0;
     }
     for(i=0;i<HMG2;i++)             /*定蜜蜂子彈初值*/
     {
          GUN2[i].life=0;
     }
     for(;AP.life;)
     {
          for(i=0,j=0;j<200;i=!i,j++)
          {
               setactivepage(i);
               setfillstyle(0,0);
               bar(0,0,getmaxx(),getmaxy());
               STAR();
               GUNMOV();
               BOOM();
               if(kbhit())
               {
                    INPUT();
               }
               if(soun)
               {
                    SOUND();
               }
               if(om)
               {
                    APMOV();
               }
               OUTPUT();
               if(j>50)
               {
                    rewind(fp1);
                    if(j>150)
                                {
                                        rewind(fp1);
                         fprintf(fp1,"READY%c",'\0');
                         rewind(fp1);
                         fgets(sbuf,39,fp1);
                         outtextxy(290,150,sbuf);
                    }
                    if(j<100)
                                {
                                        rewind(fp1);
                         fprintf(fp1,"ROUND %d%c",round,'\0');
                         rewind(fp1);
                         fgets(sbuf,39,fp1);
                         outtextxy(290,150,sbuf);
                    }
               }
               setvisualpage(i);
               delay(dela);
          }
          for(i=0;i<(HMB/10);i++)         /*定蜜蜂初值*/
          {
               for(j=0;j<10;j++)
               {
                    BEES[i*10+j].atc=0;
                    BEES[i*10+j].x=j*50+20;
                    BEES[i*10+j].y=i*30+20;
               }
          }
          for(i=0;i<HMB/2;i++)
          {
                BEES[i].life=2;
                BEES[i].t=1;
          }
          for(;i<HMB;i++)
          {
                BEES[i].life=1;
                BEES[i].t=0;
          }
          for(i=0;i<4;i++)
          {
                BEES[i+3].life=3;
                         BEES[i+3].t=2;
          }
          for(i=0;AP.life&&r;i=!i)        /*大迴圈開始*/
          {
               setactivepage(i);
               setfillstyle(0,0);
               bar(0,0,getmaxx(),getmaxy());
               STAR();
               if(!random(coa))
               {
                    ATC();
               }
                        if(i)                         /*兩圈移動一次*/
               {
                    MOVE_ADD();              /*蜜蜂移動*/
               }
               SHOOT2();                       /*蜜蜂射擊*/
               GUNMOV();                       /*子彈移動*/
               BOOM();                         /*判斷是否擊中*/
               if(kbhit())
               {
                    INPUT();                /*輸入*/
               }
               if(soun)
               {
                    SOUND();
               }
               if(om)                        /*如飛機移動中,繼續移動*/
               {
                    APMOV();
               }
               OUTPUT();                      /*輸出*/
               setvisualpage(i);
               delay(dela);
          }                                     /*大迴圈結束*/
          round++;
          dela-=3;
          coa-=10;
          cog2-=100;
          dog2-=10;
          r=HMB;
          n=s=0;
     }
     nosound();
     getch();
        getch();
        free(bp);
        free(bp2);
        free(bp2n);
        free(bo1);
        free(bo2);
        free(bo3);
        free(app);
     fcloseall();
     closegraph();
     printf("\7\7");
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
                                 case 0:
                          BEES[c].atc=1;
                          BEES[c].ro=random(2);
                          BEES[c].where=0;
                          break;
                     case 1:
                          BEES[c].atc=1;
                          if(BEES[c].life==2)
                          {
                               BEES[c].ro=2;
                          }
                          else
                          {
                               BEES[c].ro=random(3);
                          }
                          BEES[c].where=0;
                          break;
                     case 2:
                          BEES[c].atc=1;
                          BEES[c].where=0;
                          if(BEES[c].life==1)
                          {
                               BEES[c].ro=2;
                          }
                          else
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
               sp1=1;
               sp2=0;
               return;
          }
     }
}

void SHOOT2(void)               /*蜜蜂射擊*/
{
     int i,j;
     for(i=0;i<HMB;i++)
     {
                if(BEES[i].life>0)  /*判斷子彈數是否額滿*/
          {
               for(j=0;(j<HMG2)&&(GUN2[j].life==1);j++);
               if(j==HMG2)
               {
                    return;
               }
               if(random(cog2-BEES[i].atc*dog2)==0)
               {                                 /*射子彈*/
                    GUN2[j].x=BEES[i].x;
                    GUN2[j].y=BEES[i].y+HLG2;
                    GUN2[j].life=1;
               }
          }
     }
}

void SHOOT1(void)   /*飛機子彈*/
{
        int p;
        if(l==2)
        {
                for(p=0;(GUN1[p].life==1)&&(p<1);p++);
                if(p)
                {
                        return;
                }
        }
        else
        {
                for(p=0;(GUN1[p].life==1)&&(p<2);p++);
                if(p==2)
                {
                        return;
                }
        }
     GUN1[p].life=1;
     GUN1[p].l=l;
     GUN1[p].x=AP.x;
     GUN1[p].y=AP.y-1;
     GUN1[p].tx=AP.x;
     GUN1[p].ty=GUNTOP-1000;
     sp1=3;
     sp2=0;
}

void MOVE_ADD()         /*蜜蜂移動左右迴圈*/
{
     int i;
     if(n==HMADD)
     {
          s=!s;
          n=0;
     }
     for(i=0;i<HMB;i++)
     {
                if(BEES[i].life>0)
          {
               if(s)
               {
                    BEES[i].x--;
               }
               else
               {
                    BEES[i].x++;
               }
               if(BEES[i].atc)
               {
                    if((!ro[BEES[i].ro][BEES[i].where].x)&&
                       (!ro[BEES[i].ro][BEES[i].where].y))
                    {
                         BEES[i].atc=0;
                    }
                    else
                    {
                         BEES[i].x+=ro[BEES[i].ro][BEES[i].where].x;
                         BEES[i].y+=ro[BEES[i].ro][BEES[i].where].y;
                         BEES[i].where++;
                    }
               }
               if(BEES[i].x>SR)
               {
                    BEES[i].x-=SR-SL+1;
               }
               if(BEES[i].x<SL)
               {
                    BEES[i].x+=SR-SL+1;
               }
               if(BEES[i].y>GUNBOTTOM)
               {
                    BEES[i].y-=GUNBOTTOM-BEESTOP+1;
               }
               if(BEES[i].y<BEESTOP)
               {
                    BEES[i].y+=GUNBOTTOM-BEESTOP+1;
               }
          }
     }
     n++;
}

void INPUT(void)            /*輸入*/
{
     char in;
     in=getch();
     switch(in)
     {
          case ',':
               om=-1;
               break;
          case '.':
               om=1;
               break;
          case 's':
               soun=!soun;
               nosound();
               break;
          case 'p':
               nosound();
/*                                      rewind(fp1);
                         fprintf(fp1,"TEE TIME!%c",'\0');
                         rewind(fp1);
                                        fgets(sbuf,39,fp1);
                                        setactivepage(0);
                                        outtextxy(290,150,sbuf);
                                        setvisualpage(0);                   */
               getch();
               break;
          case 'q':
               AP.life=0;
               break;
          default:/*    射擊         */
               SHOOT1();
               break;
     }
}

void APMOV()
{
     if((om-1!=HMAPM)&&(om+1!=-HMAPM))
     {
          if(om>0)
          {
               if(AP.x>=APR)
               {
                    AP.x=APR;
                    om=0;
                    return;
               }
               AP.x+=HFAPM;
               om++;
          }
          else
          {
               if(AP.x<=APL)
               {
                    AP.x=APL;
                    om=0;
                    return;
               }
               AP.x-=HFAPM;
               om--;
          }
     }
     else
     {
          om=0;
     }
}

void GUNMOV()          /*子彈移動*/
{
     int a,i,j;
     for(i=0;i<HMG1;i++)
     {
          if(GUN1[i].life)
          {
               if(GUN1[i].l==2)
               {
                    GUN1[i].tx=GUN1[i].x;
                    GUN1[i].ty=GUN1[i].y-1000;
                    for(j=0;j<HMB;j++)
                    {
                                           if((BEES[j].life>0)&&
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
                    if(GUN1[i].l)
                    {
                         GUN1[i].y-=5;
                    }
                    else
                    {
                                        GUN1[i].y-=20;
                    }
               }
               if(GUN1[i].y<GUNTOP)
               {
                    GUN1[i].life=0;
               }
          }
     }
     for(a=0;a<HMG2;a++)
     {
          GUN2[a].y+=HFG2;
          if(GUN2[a].y>GUNBOTTOM)
          {
               GUN2[a].life=0;
          }
     }
}

void BOOM()              /*擊中判斷*/
{
     int a,b;
     for(a=0;a<HMG1;a++)  /*蜜蜂與我方子彈*/
     {
          for(b=0;(b<HMB)&&GUN1[a].life;b++)
          {
                        if(BEES[b].life>0)
               {
                    if(!GUN1[a].l)
                    {
                                        if((BEES[b].y>=GUN1[a].y)&&(BEES[b].y<=GUN1[a].y+25)&&
                            (GUN1[a].x>=BEES[b].x-9)&&(GUN1[a].x<=BEES[b].x+10))
                         {
                              BEES[b].life--;
                              if(!BEES[b].life)
                              {
                                   r--;
                                   score+=100;
                              }
                              GUN1[a].life=0;
                              sp1=2;
                              sp2=0;
                         }
                    }
                    if(GUN1[a].l==1)
                    {
                         if((BEES[b].y>=GUN1[a].y)&&(BEES[b].y<=GUN1[a].y+100)&&
                            (GUN1[a].x>=BEES[b].x-9)&&(GUN1[a].x<=BEES[b].x+10))
                         {
                              if(BEES[b].t==2)
                              {
                                   BEES[b].life-=2;
                                   if(BEES[b].life<=0)
                                   {
                                        r--;
                                        score+=100;
                                        sp1=2;
                                        sp2=0;
                                   }
                                   else
                                   {
                                        GUN1[a].life=0;
                                        sp1=4;
                                        sp2=0;
                                   }
                              }
                              else
                              {
                                   BEES[b].life--;
                                   if(!BEES[b].life)
                                   {
                                        r--;
                                        score+=100;
                                        sp1=2;
                                        sp2=0;
                                   }
                              }
                         }
                    }
                    if(GUN1[a].l==2)
                    {
                         if((BEES[b].y>=GUN1[a].y)&&(BEES[b].y<=GUN1[a].y+10)&&
                            (GUN1[a].x+5>=BEES[b].x-9)&&(GUN1[a].x-5<=BEES[b].x+10))
                         {
                              BEES[b].life--;
                              if(!BEES[b].life)
                              {
                                   r--;
                                   score+=100;
                              }
                              GUN1[a].life=0;
                              sp1=2;
                              sp2=0;
                         }
                    }
               }
          }
     }
     for(a=0;a<HMG2;a++)   /*我方與蜜蜂子彈*/
     {
          if(GUN2[a].life&&(AP.y+20<=GUN2[a].y)&&(AP.y+20>=GUN2[a].y-HFG2)&&
            (GUN2[a].x>=AP.x-17)&&(GUN2[a].x<=AP.x+17))
          {
               GUN2[a].life=0;
               AP.life--;
               APBOOM();                 /*爆炸副程式*/
               return;
          }
     }
     for(a=0;a<HMB;a++)
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
                         score+=100;
                    }
                                APBOOM();
                    return;
               }
          }
     }
}

void APBOOM(void)        /*爆炸*/
{
        circle(AP.x,AP.y+17,17);
        setlinestyle(0,0,3);
        delay(10000);
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

void OUTPUT(void)        /*輸出顯示*/
{
     int i;
     for(i=0;i<HMG1;i++)
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
     if(AP.life)
     {
          putimage(AP.x-17,AP.y,app,COPY_PUT);
     }
     for(i=0;i<HMG2;i++)
     {
          if(GUN2[i].life)
          {
               setlinestyle(0,0,3);
               line(GUN2[i].x,GUN2[i].y,GUN2[i].x,GUN2[i].y-HLG2);
          }
     }
     for(i=0;i<HMB;i++)
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
     rewind(fp1);
     fprintf(fp1,"SCORE  %ld%c",score,'\0');
     rewind(fp1);
     fgets(sbuf,39,fp1);
     outtextxy(0,0,sbuf);
}

void STAR(void)
{
     int i;
     for(i=0;i<SR-SL+1;i++)
     {
          if(star[i].y)
          {
               putpixel(i,star[i].y,color[star[i].c]);
               star[i].y+=(star[i].c>7)+1;
               if(star[i].y>=GUNBOTTOM)
               {
                    star[i].y=0;
               }
          }
          else
          {
               if(!random(cos))
               {
                    star[i].c=random(16);
                    star[i].y=1;
               }
          }
     }
}
