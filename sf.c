#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define zd 100          
//**************************************************
typedef struct//�����ڽӾ���                  
{
	int vexs[zd];      		 
    int arcs[zd][zd];       
    int vexnum,arcnum;          
} Mgraph;                       
//***************************************************
typedef struct ANode//�����ڽӱ�           
{
    int adjvex;                 
    struct ANode *nextarc;        
} ArcNode;
typedef struct Vnode           
{
    int d;                
    ArcNode *firstarc;         
} VNode;
typedef struct
{
    VNode vertices[zd];            
    int vexnum,arcnum;               
} ALGraph;
//**************************************************
int LocateVex(Mgraph *G, int u)//�Ҷ����±�(�з����±꣬û�оͷ���-1)
{
    int i;
    for(i=0;i<G->vexnum;i++)
	{
        if(G->vexs[i] == u)
            return i;
	}
    return -1;
}
//**************************************************
void CreateMgraph(Mgraph *G,int a,int b)//�����ڽӾ���a��������b������
{
 
    int i,j,k,w;
    int v1,v2;
	G->vexnum=a;
    G->arcnum=b;
    if (G->vexnum<1||G->arcnum<1||(G->arcnum>(G->vexnum*(G->vexnum-1))/2))
    {
        printf("����ʧ��!���������иù���������ȷ���ݡ�\n");
        exit(0);
    }
	printf("%d������ֱ�Ϊ:",a);
    for(i=0;i<G->vexnum;i++)
    {
		G->vexs[i]=i;
		printf("%d ",G->vexs[i]);
    }
	printf("\n");
    for(i=0;i<G->vexnum;i++)// ��ʼ���ڽӾ���
        for(j=0;j<G->vexnum;j++)
           G->arcs[i][j]=0;
    printf("�������еı߶�Ӧ���������㡢Ȩֵ������:4������3����ʱ\n0 1 2\n1 2 1\n2 3 3\n\n");
    for(k=0;k<G->arcnum;k++)
    {
        scanf("%d %d %d",&v1,&v2,&w);
        i = LocateVex(G, v1);// ���Ҷ����ڶ��������е��±�
        j = LocateVex(G, v2);
        if((i==-1||j==-1))
            printf("û�иñ�����������\n");
        else
        {
            G->arcs[i][j]=w;//����Ȩֵ
            G->arcs[j][i]=w;
        }
    }
}
//***************************************************
void CreateALGraph(ALGraph *G,int a,int b)//�����ڽӱ�a��������b������
{
	int i=0,j,k;
	ArcNode *s;
	G->vexnum=a;
    G->arcnum=b;
	printf("%d������ֱ�Ϊ:",a);
    for(i = 0; i < G->vexnum; i++)
    {
		G->vertices[i].d=i;
		printf("%d ",G->vertices[i].d);
    }
	printf("\n");
	for(i=0;i<G->vexnum;i++)
		G->vertices[i].firstarc=NULL;   	//��ʼ�����б�ͷ�ڵ��ָ���� 
	printf("�������еı߹����ڽӱ�����:4������3����ʱ\n0 1\n1 2\n2 3\n\n");
	for(k=0;k<G->arcnum;k++)
	{   			                         //������ߣ������ڽӱ�  
		scanf("%d %d",&i,&j);    			  //����һ���ߵ������ڵ� 
		s=(ArcNode*)malloc(sizeof(ArcNode));  // ����һ���½ڵ� 
		s->adjvex=j;
		s->nextarc=G->vertices[i].firstarc;  //ͷ�巨�����½ڵ� 
		G->vertices[i].firstarc = s;
		s=(ArcNode*)malloc(sizeof(ArcNode)); //������һ���ԳƵ��µı߽ڵ� 
		s->adjvex=i;
		s->nextarc=G->vertices[j].firstarc;
		G->vertices[j].firstarc = s;
	}
}
//***************************************************
void MatToList(Mgraph g,ALGraph *G)//���ڽӾ���gת�����ڽӱ�G
{
    int i,j;
    ArcNode *p,*s;
    G=(ALGraph *)malloc(sizeof(ALGraph));
    for (i=0; i<g.vexnum; i++)             
        G->vertices[i].firstarc=NULL;
    for (i=0; i<g.vexnum; i++)    
        for (j=0; j<g.vexnum; j++)
            if (g.arcs[i][j]!=0) 
            {
	 			p=(ArcNode *)malloc(sizeof(ArcNode)); 
	            p->adjvex=j; p->nextarc=NULL;
				if(!G->vertices[i].firstarc)
					G->vertices[i].firstarc=p;
				else{
					s=G->vertices[i].firstarc;
					while(s->nextarc) s=s->nextarc;
					s->nextarc=p;
				}
            }
    G->vexnum=g.vexnum;
    G->arcnum=g.arcnum;
}
//***************************************************
void ListToMat(ALGraph G,Mgraph *g)//���ڽӱ�Gת�����ڽӾ���g
{	
	int i,j;
	ArcNode *p;
	for(i=0; i<G.vexnum; i++)
		for(j=0; j<G.vexnum; j++)
			g->arcs[i][j] = 0;
	for(i=0;i<G.vexnum;i++)
	{	
		p=G.vertices[i].firstarc;
		if (p!=NULL)
		{	g->arcs[i][p->adjvex]=1;
			p=p->nextarc;
		}
	}
	g->vexnum=G.vexnum;
	g->arcnum=G.arcnum;
}
//***************************************************
int visited[50];
void DFS (Mgraph *G,int v,int V)//�������
{
	
	int i;
	visited[v] = 1;	 
	printf("%d ",G->vexs[v]);	//	�����ǰ���� 
	for(i=0;i<V ;i++)
		if(visited[i]==0&&G->arcs[v][i]!=0) //	�����ǰ������ڽ�����ڣ���û�б����� ������ݹ����
		    DFS (G,i,V);	                //	�ݹ������ǰ������ڽ��� 	
}
void Init_DFS (Mgraph *G,int V)
{
	int i;
	for(i=0;i<V;i++)//��ʶ����ȫΪ0
		visited[i] = 0;
	for(i=0;i<V ;i++)	   // ���ÿһ�������Ƿ񱻷��ʵ� 
	{
		if(visited[i]==0)	
			DFS (G,i,V);   // ��ʼ��ȱ���	
	} 
	putchar('\n');
}
//***************************************************
void BFSGraph(ALGraph *G,int a)/*�������*/
{
	int visited[100];
     int i;
	 ArcNode *temp;
    //�Է��ʱ�־����ĳ�ʼ��
    for(i = 0;i<a;i++)
        visited[i] = 0;
    for(i = 0;i<a;i++){
        if(visited[i]==0){
         	printf("%d ",G->vertices[i].d);//���ʱ�ͷ�ڵ�
         visited[i]=1;//���÷��ʱ�ǩ
        }
         //�Ը�������б�������
         temp =G->vertices[i].firstarc;
         while(temp){
            if(visited[temp->adjvex]==0){//����ö���δ���ʹ�
                printf("%d ",G->vertices[temp->adjvex].d);
                visited[temp->adjvex] = 1;//���÷��ʱ�ǩ
            }
            temp = temp->nextarc;
        }
    }
}
//***************************************************
void print_graph(Mgraph G)//����ڽӾ���
{
    int i, j;
 
    printf("\n\n����ͼ�ڽӾ���:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
 
            printf("%d ", G.arcs[i][j]);
 
        printf("\n");
    }
}
//*************************************************** 
void Output(ALGraph G)//����ڽӱ�
{
    int i;
    ArcNode *p;
    for (i=0; i<G.vexnum; i++)
    {
        p=G.vertices[i].firstarc;
        printf("v%d:",i);
        while (p!=NULL)
        {
            printf("%2d",p->adjvex);
            p=p->nextarc;
        }
        printf("\n");
    }
}
//***************************************************
int main()
{
    Mgraph g,g1;
    ALGraph G,G1;
	int a,b,c;	
	printf(        "���������봴��ͼ�Ķ���ͱ�������ѡ���Ժ��ַ�ʽ����ͼ\n");
	printf("������Ҫ������ͼ�Ķ�����\n");
	scanf("%d",&a);
	printf("������Ҫ������ͼ�ı���\n");
	scanf("%d",&b);
	printf("              ������С����\n");
    printf("*****************************************\n");
	printf(        "        1. ����\n");
	printf(        "        2. ���ڽӾ���g����������\n");
	printf(        "        3. ���ڽӱ�G����������\n");
	printf(        "        4. ���ڽӾ���gת��Ϊ�ڽӱ�G\n");
    printf(        "        5. ���ڽӱ�Gת��Ϊ�ڽӾ���g\n");
	printf(        "        6. ���ڽӾ���g������ȱ���\n");
    printf(        "        7. ���ڽӱ�G������ȱ���\n");
    printf(        "        8. �˳�\n");
	printf("*****************************************\n");
	while(1)
	{
		printf("����:");
		scanf("%d",&c);
		if(c==1)
		{
			system("cls");
			printf("              ������С����\n");
			printf("*****************************************\n");
			printf(        "        1. ����\n");
			printf(        "        2. ���ڽӾ���g����������\n");
			printf(        "        3. ���ڽӱ�G����������\n");
			printf(        "        4. ���ڽӾ���gת��Ϊ�ڽӱ�G\n");
			printf(        "        5. ���ڽӱ�Gת��Ϊ�ڽӾ���g\n");
			printf(        "        6. ���ڽӾ���g������ȱ���\n");
			printf(        "        7. ���ڽӱ�G������ȱ���\n");
			printf(        "        8. �˳�\n");
			printf("*****************************************\n");
		}
		if(c==2)
		{
			CreateMgraph(&g,a,b);
			print_graph(g);
		}
		if(c==3)
		{
			CreateALGraph(&G1,a,b);
			Output(G1);
		}
		if(c==4)
		{
			printf("ͼ���ڽӾ���gת�����ڽӱ�G:\n");
			MatToList(g,&G);
			Output(G);
		}
		if(c==5)
		{
			ListToMat(G1,&g1);
			print_graph(g1);
			
		}
		if(c==6)
		{
			printf("����������������ڽӾ���g���Ϊ:\n");
			Init_DFS (&g,a);
		}
		if(c==7)
		{
			printf("����������������ڽӱ�G���Ϊ:\n");
			BFSGraph(&G1,a);
		}
		if(c==8)
		{
			system("cls");
			break;
		}
	}	
    return 0;  
}