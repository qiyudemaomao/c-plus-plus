
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#define PI 3.14159
#define S 16            
#define WJ  "C:\\TC20\\hzk16" /*汉字库*/
typedef struct /*student*/
{
    char name[8];
    double math;
    double english;
    double computer;
    double sum;
}STU;
typedef struct         
{
    char name[11];
    char type;
    long start;
    char size;
    char field_dight;
    char empty[14];
}File;
typedef struct       
{
    char type;
    char date[3];
    long file_num;
    short file_sidth;
    short file_width;
    char empty[20];
}Head;

/*汉字*/
void disphz(int x,int y,char *zi,int color,int n)/*n为放大倍数*/
{
	FILE *fp;
	char qh,wh;
	long offset;
	int i,j,t;
	int m=0;
	int k=0;
	char buffer[S*S/8];
	char mask[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
	fp=fopen(WJ,"rb");
	if(fp==NULL)
	{
		exit(0);
	}

	while(*zi!='\0')
	{
		qh=*zi-160;
		zi++;
		wh=*zi-160;
		zi++;
		offset=(94L*(qh-1)+wh-1)*S*S/8;
		fseek(fp,offset,0);
		fread(buffer,S*S/8,1,fp);

		for(i=0;i<S;i++)
		{
			for(j=0;j<S;j++)
			{
				t=buffer[S/8*i+j/8]&mask[j%8];
				if(t!=0)
				for(k=0;k<n;k++)
				for(m=0;m<n;m++)
				putpixel(x+j*n+k,y+i*n+m,color);

			}
		}
		x+=S*m;
	}
	fclose(fp);
}

void title()               /*第一页*/
 {
    int *zi;
	int gdriver=DETECT;
	int gmode;
	int i;
	initgraph(&gdriver,&gmode,"");

	setbkcolor(3);
	setcolor(14);
	for(i=100;i<550;i=i+110)
	{
		setfillstyle(1,14);
		circle(i,160,55);
		floodfill(i,160,14);
	}/*(45,160),r=55*/
	setcolor(12);
	setfillstyle(1,12);
	bar(190,260,450,420);
	floodfill(320,280,12);
	setcolor(4);
	settextstyle(1,0,12);
	outtextxy(70,90,"C");
	disphz(170,120,"综",4,5);
	disphz(285,120,"合",4,5);
	disphz(390,120,"应",4,5);
	disphz(505,120,"用",4,5);


	disphz(200,270,"程序功能",14,1);

	setcolor(14);
	settextstyle(1,0,1);
	outtextxy(268,265,":");
	outtextxy(195,300,"1.");
	outtextxy(195,323,"2.");

	disphz(210,302,"展示学生成绩直方图",14,1);

	disphz(210,325,"展示各分段成绩圆饼图",14,1);

	disphz(270,400,"按任意键继续",1,1);
	getch();
	cleardevice();
}

void second()                 /*第二页*/
{
	int *zi;
	int gdriver=DETECT;
	int gmode;
	int i;
	initgraph(&gdriver,&gmode,"");

	setbkcolor(0);
	setcolor(4);
	rectangle(0,0,639,479);

	disphz(25,50,"请输入数据库文件名：",15,1);
	settextstyle(1,0,1);
	setcolor(12);
	setfillstyle(1,0);
	rectangle(25,75,220,96);
	floodfill(50,80,12);

	disphz(25,110,"提示：",14,1);
	setcolor(14);



	disphz(89,130,"可以带盘符和路径，如",14,1);

	disphz(121,157,"可以忽略",14,1);


	setcolor(11);
	settextstyle(1,0,1);
	outtextxy(75,127,"1.");
	outtextxy(75,155,"2.");
	outtextxy(250,127,"C:\\TC20\\student.dbf");
	outtextxy(85,155,".dbf");
}

/*直方和圆饼*/
void picture(STU *stu,long count)
{
	int *zi;
	int gmode,gdriver=DETECT;
	int key;
	char *g;
	int prev=0,angle=0;
	char fun[2];

	long i=0,panduan,a1=0,a2=0,a3=0,a4=0,a5=0,j,eve,w;
	long kmp=50;
	long yanse=9;
	initgraph(&gdriver,&gmode,"");
	eve=360/count;
	fun[1]=0;
	for(j=0;j<count;j++)
	{
		if(stu[j].sum/3<60)
			a1++;
		if(stu[j].sum/3>=60&&stu[j].sum/3<70)
			a2++;
		if(stu[j].sum/3>=70&&stu[j].sum/3<80)
			a3++;
		if(stu[j].sum/3>=80&&stu[j].sum/3<90)
			a4++;
		if(stu[j].sum/3>=90)
			a5++;
	}
	while(fun[1]!=1)
	{
		if(count%3==2)
			panduan=count-2;
		else
			panduan=count-1;
		for(;i<panduan;)                          /*满*/
		{
            cleardevice();
			setcolor(RED);
			rectangle(0,0,639,479);
			setcolor(15);
			setfillstyle(1,12);
			bar3d(150,25,180,35,5,1);
			floodfill(155,24,15);
			floodfill(182,30,15);
			disphz(195,23,"数学",12,1);

			setcolor(4);
			setfillstyle(1,10);
			bar3d(300,25,330,35,5,1);
			floodfill(305,24,4);
			floodfill(332,30,4);
			disphz(345,23,"计算机",10,1);

			setcolor(14);
			setfillstyle(1,11);
			bar3d(450,25,480,35,5,1);
			floodfill(455,24,14);
			floodfill(482,30,14);
			disphz(495,23,"英语",11,1);

			rectangle(0,0,639,479);
			disphz(225,345,"学生成绩示意图",14,2);

			setcolor(14);
			setfillstyle(1,7);
			bar3d(20,400,140,475,15,1);
			floodfill(50,390,14);
			floodfill(145,450,14);

			bar3d(260,400,380,475,15,1);
			floodfill(300,390,14);
			floodfill(385,450,14);

			bar3d(500,400,620,475,15,1);
			floodfill(530,390,14);
			floodfill(625,450,14);
			setcolor(5);
			settextstyle(1,0,2);
			outtextxy(65,440,"(O)");
			disphz(54,410,"上一页",15,1);

			disphz(304,410,"结束",15,1);
			outtextxy(295,440,"(ESC)");

			disphz(534,410,"下一页",15,1);
			outtextxy(545,440,"(P)");


			setcolor(WHITE);/*math*/
			setfillstyle(1,12);
			bar3d(150,300-2*stu[i].math,190,300,20,1);
			floodfill(170,290-2*stu[i].math,WHITE);
			floodfill(192,300-2*stu[i].math,WHITE);

			bar3d(300,300-2*stu[i+1].math,340,300,20,1);
			floodfill(320,290-2*stu[i+1].math,WHITE);
			floodfill(342,300-2*stu[i+1].math,WHITE);

			bar3d(450,300-2*stu[i+2].math,490,300,20,1);
			floodfill(470,290-2*stu[i+2].math,WHITE);
			floodfill(492,300-2*stu[i+2].math,WHITE);

			setcolor(RED);/*com*/
			setfillstyle(1,10);
			bar3d(190,300-2*stu[i].computer,230,300,20,1);
			floodfill(210,290-2*stu[i].computer,RED);
			floodfill(232,300-2*stu[i].computer,RED);

			bar3d(340,300-2*stu[i+1].computer,380,300,20,1);
			floodfill(360,290-2*stu[i+1].computer,RED);
			floodfill(382,300-2*stu[i+1].computer,RED);

			bar3d(490,300-2*stu[i+2].computer,530,300,20,1);
			floodfill(510,290-2*stu[i+2].computer,RED);
			floodfill(532,300-2*stu[i+2].computer,RED);

			setcolor(YELLOW);/*engl*/
			setfillstyle(1,CYAN);
			bar3d(230,300-2*stu[i].english,270,300,20,1);
			floodfill(250,290-2*stu[i].english,YELLOW);
			floodfill(272,300-2*stu[i].english,YELLOW);

			bar3d(380,300-2*stu[i+1].english,420,300,20,1);
			floodfill(400,290-2*stu[i+1].english,YELLOW);
			floodfill(422,300-2*stu[i+1].english,YELLOW);

			bar3d(530,300-2*stu[i+2].english,570,300,20,1);
			floodfill(550,290-2*stu[i+2].english,YELLOW);
			floodfill(572,300-2*stu[i+2].english,YELLOW);

			setcolor(15);
			settextstyle(0,0,1);
			line(100,50,100,300);
			line(100,50,95,55);
			line(100,50,105,55);
			outtextxy(82,55,"x");

			line(100,300,615,300);
			line(615,300,610,295);
			line(615,300,610,305);
			outtextxy(620,282,"y");
			outtextxy(95,300,"0");

			line(100,260,110,260);
			outtextxy(80,260,"20");
			line(100,220,110,220);
			outtextxy(80,220,"40");
			line(100,180,110,180);
			outtextxy(80,180,"60");
			line(100,140,110,140);
			outtextxy(80,140,"80");
			line(100,100,110,100);
			outtextxy(75,100,"100");


			disphz(190,310,stu[i].name,6,1);

			disphz(340,310,stu[i+1].name,6,1);

			disphz(490,310,stu[i+2].name,6,1);
			break;
		}
		key=bioskey(0);
		fun[0]=key;
		fun[1]=key>>8;
		if(fun[1]==25&&i<(count-count%3))
			i+=3;
		if(fun[1]==24&&i!=0)
			i-=3;
		if(count%3==1&&i==panduan)                /*少2*/
		{
			cleardevice();
			setcolor(RED);
			rectangle(0,0,639,479);
			setcolor(15);
			setfillstyle(1,12);
			bar3d(150,25,180,35,5,1);
			floodfill(155,24,15);
			floodfill(182,30,15);

			disphz(195,23,"数学",12,1);

			setcolor(4);
			setfillstyle(1,10);
			bar3d(300,25,330,35,5,1);
			floodfill(305,24,4);
			floodfill(332,30,4);

			disphz(345,23,"计算机",10,1);

			setcolor(14);
			setfillstyle(1,11);
			bar3d(450,25,480,35,5,1);
			floodfill(455,24,14);
			floodfill(482,30,14);

			disphz(495,23,"英语",11,1);

			rectangle(0,0,639,479);
			disphz(225,345,"学生成绩示意图",14,2);

			setcolor(14);
			setfillstyle(1,7);
			bar3d(20,400,140,475,15,1);
			floodfill(50,390,14);
			floodfill(145,450,14);

			bar3d(260,400,380,475,15,1);
			floodfill(300,390,14);
			floodfill(385,450,14);

			bar3d(500,400,620,475,15,1);
			floodfill(530,390,14);
			floodfill(625,450,14);
			setcolor(5);
			settextstyle(1,0,2);
			outtextxy(65,440,"(O)");
			disphz(54,410,"上一页",15,1);

			disphz(304,410,"结束",15,1);
			outtextxy(295,440,"(ESC)");

			disphz(534,410,"下一页",15,1);
			outtextxy(545,440,"(P)");


			setcolor(WHITE);/*math*/
			setfillstyle(1,12);
			bar3d(150,300-2*stu[i].math,190,300,20,1);
			floodfill(170,290-2*stu[i].math,WHITE);
			floodfill(192,300-2*stu[i].math,WHITE);

			setcolor(RED);/*com*/
			setfillstyle(1,10);
			bar3d(190,300-2*stu[i].computer,230,300,20,1);
			floodfill(210,290-2*stu[i].computer,RED);
			floodfill(232,300-2*stu[i].computer,RED);

			setcolor(YELLOW);/*engl*/
			setfillstyle(1,CYAN);
			bar3d(230,300-2*stu[i].english,270,300,20,1);
			floodfill(250,290-2*stu[i].english,YELLOW);
			floodfill(272,300-2*stu[i].english,YELLOW);

			setcolor(15);
			settextstyle(0,0,1);
			line(100,50,100,300);
			line(100,50,95,55);
			line(100,50,105,55);
			outtextxy(82,55,"x");

			line(100,300,615,300);
			line(615,300,610,295);
			line(615,300,610,305);
			outtextxy(620,302,"y");
			outtextxy(95,300,"0");

			line(100,260,110,260);
			outtextxy(80,260,"20");
			line(100,220,110,220);
			outtextxy(80,220,"40");
			line(100,180,110,180);
			outtextxy(80,180,"60");
			line(100,140,110,140);
			outtextxy(80,140,"80");
			line(100,100,110,100);
			outtextxy(75,100,"100");

			disphz(190,310,stu[i].name,6,1);

		}
		if(count%3==2&&i==panduan)            /*少1*/
		{
			cleardevice();
			setcolor(RED);
			rectangle(0,0,639,479);
			setcolor(15);
			setfillstyle(1,12);
			bar3d(150,25,180,35,5,1);
			floodfill(155,24,15);
			floodfill(182,30,15);

			disphz(195,23,"数学",12,1);

			setcolor(4);
			setfillstyle(1,10);
			bar3d(300,25,330,35,5,1);
			floodfill(305,24,4);
			floodfill(332,30,4);

			disphz(345,23,"计算机",10,1);

			setcolor(14);
			setfillstyle(1,11);
			bar3d(450,25,480,35,5,1);
			floodfill(455,24,14);
			floodfill(482,30,14);

			disphz(495,23,"英语",11,1);

			disphz(225,345,"学生成绩示意图",14,2);

			setcolor(14);
			setfillstyle(1,7);
			bar3d(20,400,140,475,15,1);
			floodfill(50,390,14);
			floodfill(145,450,14);

			bar3d(260,400,380,475,15,1);
			floodfill(300,390,14);
			floodfill(385,450,14);

			bar3d(500,400,620,475,15,1);
			floodfill(530,390,14);
			floodfill(625,450,14);
			setcolor(5);
			settextstyle(1,0,2);
			outtextxy(65,440,"(O)");
			disphz(54,410,"上一页",5,1);

			disphz(304,410,"结束",5,1);
			outtextxy(295,440,"(ESC)");

			disphz(534,410,"下一页",5,1);
			outtextxy(545,440,"(P)");


			setcolor(WHITE);/*math*/
			setfillstyle(1,12);
			bar3d(150,300-2*stu[i].math,190,300,20,1);
			floodfill(170,290-2*stu[i].math,WHITE);
			floodfill(192,300-2*stu[i].math,WHITE);

			bar3d(300,300-2*stu[i+1].math,340,300,20,1);
			floodfill(320,290-2*stu[i+1].math,WHITE);
			floodfill(342,300-2*stu[i+1].math,WHITE);

			setcolor(RED);/*com*/
			setfillstyle(1,10);
			bar3d(190,300-2*stu[i].computer,230,300,20,1);
			floodfill(210,290-2*stu[i].computer,RED);
			floodfill(232,300-2*stu[i].computer,RED);

			bar3d(340,300-2*stu[i+1].computer,380,300,20,1);
			floodfill(360,290-2*stu[i+1].computer,RED);
			floodfill(382,300-2*stu[i+1].computer,RED);

			setcolor(YELLOW);/*engl*/
			setfillstyle(1,CYAN);
			bar3d(230,300-2*stu[i].english,270,300,20,1);
			floodfill(250,290-2*stu[i].english,YELLOW);
			floodfill(272,300-2*stu[i].english,YELLOW);

			bar3d(380,300-2*stu[i+1].english,420,300,20,1);
			floodfill(400,290-2*stu[i+1].english,YELLOW);
			floodfill(422,300-2*stu[i+1].english,YELLOW);

			setcolor(15);
			settextstyle(0,0,1);
			line(100,50,100,300);
			line(100,50,95,55);
			line(100,50,105,55);
			outtextxy(82,55,"x");

			line(100,300,615,300);
			line(615,300,610,295);
			line(615,300,610,305);
			outtextxy(620,302,"y");
			outtextxy(95,300,"0");

			line(100,260,110,260);
			outtextxy(80,260,"20");
			line(100,220,110,220);
			outtextxy(80,220,"40");
			line(100,180,110,180);
			outtextxy(80,180,"60");
			line(100,140,110,140);
			outtextxy(80,140,"80");
			line(100,100,110,100);
			outtextxy(75,100,"100");
			rectangle(0,0,639,479);


			disphz(190,310,stu[i].name,6,1);

			disphz(340,310,stu[i+1].name,6,1);
		}
}
	cleardevice();
	setcolor(6);
	rectangle(480,40,610,210);
	/*饼*/
    for(i=0;i<5;i++)
{
	setcolor(14);
	settextstyle(1,0,2);
	setfillstyle(1,yanse++);
	bar(490,kmp,515,20+kmp);
	if(i==0)
		outtextxy(520,kmp,"0--60");
	if(i==1)
		outtextxy(520,kmp,"60--70");
	if(i==2)
		outtextxy(520,kmp,"70--80");
	if(i==3)
		outtextxy(520,kmp,"80--90");
	if(i==4)
		outtextxy(520,kmp,"90--100");
	kmp+=30;
}

	setfillstyle(1,9);
    angle=eve*a1;
    sprintf(g,"%d",a1*10);
	pieslice(200,200,0,angle,150);
	outtextxy(180+113*cos(angle*PI/360),200-115*sin(angle*PI/360),g);
	outtextxy(180+113*cos(angle*PI/360)+16,200-115*sin(angle*PI/360),"%");


	setfillstyle(1,10);
    prev=angle;
    angle=angle+eve*a2;
    sprintf(g,"%d",a2*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");


	setfillstyle(1,11);
    prev=angle;
    angle=angle+eve*a3;
    sprintf(g,"%d",a3*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");


	setfillstyle(1,12);
    prev=angle;
    angle=angle+eve*a4;
    sprintf(g,"%d",a4*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");

	setfillstyle(1,13);
    prev=angle;
    angle=angle+eve*a5;
    sprintf(g,"%d",a5*10);
	pieslice(200,200,prev,angle,150);
	outtextxy(180+113*cos((prev+angle)*PI/360),200-115*sin((prev+angle)*PI/360),g);
	outtextxy(180+113*cos((prev+angle)*PI/360)+16,200-115*sin((prev+angle)*PI/360),"%");

	disphz(100,420,"各分段成绩圆饼图",14,2);
    getch();
    cleardevice();
}
void read_file()/*读取*/
{
        FILE *fp;
        Head headd;
        File file[5];
        STU stu[100];
        STU qq;
        long i=0,n=0,k,j=0,count=0,p,o;
        char huan[20],filename[20];
        char fun;
        gotoxy(5,6);
		scanf("%s",&filename);
		if(strcmp(&filename[strlen(filename)-4],".dbf")!=0)/*判断.dbf*/
			strcat(filename,".dbf");
		fp=fopen(filename,"rb");

		if(fp==NULL)
        {
		disphz(210,250,"无法打开文件，请重新运行程序",4,1);
		disphz(210,300,"任意键退出程序",4,1);
            getch();
            exit(1);
        }
		fread(&headd,32,1,fp);                       
		for(i=1;i<=(headd.file_sidth-33)/32;i++)
		{
			fread(&file[0],32,1,fp);
			if(strcmp(file[0].name,"姓名")==0)
				file[1]=file[0];
			else
				if(strcmp(file[0].name,"数学")==0)
					file[2]=file[0];
				else
					if(strcmp(file[0].name,"英语")==0)
						file[3]=file[0];
					else
						if(strcmp(file[0].name,"计算机")==0)
							file[4]=file[0];
		}

		for(i=0;i<headd.file_num;i++)
		{
			fseek(fp,headd.file_sidth+headd.file_width*i,0);
			fread(&fun,1,1,fp);
			if(fun=='*')
				continue;
			fseek(fp,headd.file_sidth+headd.file_width*i+file[1].start,0);
			fread(stu[count].name,file[1].size,1,fp);
			stu[count].name[file[1].size]=0;
			for(p=file[1].size-1;p>=0;p--)
			{
				if(stu[count].name[p]==' ')
					stu[count].name[p]=0;
				else
					break;
			}
			fseek(fp,headd.file_sidth+headd.file_width*i+file[2].start,0);
			ftell(fp);
			fread(huan,file[2].size,1,fp);
			huan[file[2].size]=0;
			stu[count].math=(float)atof(huan);

			fseek(fp,headd.file_sidth+headd.file_width*i+file[3].start,0);
			ftell(fp);
			fread(huan,file[3].size,1,fp);
			huan[file[3].size]=0;
			stu[count].english=(float)atof(huan);

			fseek(fp,headd.file_sidth+headd.file_width*i+file[4].start,0);
			ftell(fp);
			fread(huan,file[4].size,1,fp);
			huan[file[4].size]=0;
			stu[count].computer=(float)atof(huan);

			stu[count].sum=stu[count].computer+stu[count].math+stu[count].english;
			count++;
		}

		fclose(fp);
		picture(stu,count);
		return 0;
}
 void  mysound(unsigned int freq, int times)       /*音乐*/
{
    int i;
    union
   {
		int divisor;
		char c[2];
   }sound;
	char bits;
	sound.divisor=1193180/freq;

	outportb(0x43,0xb6);
	outportb(0x42,sound.c[0]);
	outportb(0x42,sound.c[1]);

	bits=inportb(0x61);
	outportb(0x61,bits|3);
	for(i=0;i<times;i++)
	delay(100);
	outportb(0x61,bits&0xfc);
	outportb(0x61,bits);
}
void end()
{
	int freq[8] = {0,349,392,440,494,524,588,660};
	int song[] ={
		
		3,5,8,6,6,5,5,6,6,5,1,3,8,
		6,6,5,5,6,6,5,1,2,3,3,1,-6,1,3,5,6,6,3,5,
		6,6,8,7,5,6,0};
	int div[] = {4,1,8,8,8,8,8,8,8,4,
	8,4,8,8,8,8,8,8,8,4,8,4,2,8,8,4,1,8,4,8,2,8,4,8,2,2,8,4,1,0};
	char arr[][10]={"感","谢","曹","老","师","的","教","导"};
	char brr[][10]={"如","有","不","足","请","多","多","包","涵"};
	char crr[][10]={"岳","书","腾"};
	unsigned int f;
	int k=0,y=0,t=0;
	int i,h,o,j,times,gdriver, gmode;
        	gdriver = DETECT;
	initgraph(&gdriver, &gmode,"");
		for(o=0;o<8;o++)
		{
		 disphz(10+k,80,arr[o],3,2);
		 k+=32;
		 delay(100);
		}
		for(h=0;h<9;h++)
		{
		disphz(10+y,170,brr[h],3,2);
		y+=32;
		delay(100);
		}
		for(j=0;j<3;j++)
		{
			disphz(330+t,220,crr[j],3,2);
			t+=32;
			delay(100);
		}
	
	for(i= 0;song[i];i++)
	{
		if(song[i] < 0)
			f = freq[-song[i]]/2;
		else
			if(song[i]>7)
				f = freq[song[i] % 7]*2;
			else
				f = freq[song[i]];
			times=16/div[i];
			mysound(f,times);
			if(i==13)
			{
				disphz(300,280,"程序结束",14,3);
			}
			if(i==18)
			{
				disphz(300,350,"谢谢观看",14,3);
			}
			if(i==22)
			{

				cleardevice();
			}
			if(i==25)
			{
			setcolor(4);
			settextstyle(1,0,7);
			outtextxy(100,200,"The END");
			}
			if(i==30)
			{
				disphz(540,460,"按任意键退出",9,1);
			}
			

	}




    getch();
    closegraph();
}

int main()                                         /*主函数*/
{
	int *zi;
	int mode,driver=DETECT;
	initgraph(&driver,&mode,"");
	title();                                /*显示第一页*/
	second();
	read_file();
	end();
	return 0;
}
