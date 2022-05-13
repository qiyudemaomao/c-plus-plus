#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define zd 100          
//**************************************************
typedef struct//定义邻接矩阵                  
{
	int vexs[zd];      		 
    int arcs[zd][zd];       
    int vexnum,arcnum;          
} Mgraph;                       
//***************************************************
typedef struct ANode//定义邻接表           
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
int LocateVex(Mgraph *G, int u)//找顶点下标(有返回下标，没有就返回-1)
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
void CreateMgraph(Mgraph *G,int a,int b)//建立邻接矩阵（a顶点数，b边数）
{
 
    int i,j,k,w;
    int v1,v2;
	G->vexnum=a;
    G->arcnum=b;
    if (G->vexnum<1||G->arcnum<1||(G->arcnum>(G->vexnum*(G->vexnum-1))/2))
    {
        printf("建立失败!请重新运行该功能输入正确数据。\n");
        exit(0);
    }
	printf("%d个顶点分别为:",a);
    for(i=0;i<G->vexnum;i++)
    {
		G->vexs[i]=i;
		printf("%d ",G->vexs[i]);
    }
	printf("\n");
    for(i=0;i<G->vexnum;i++)// 初始化邻接矩阵
        for(j=0;j<G->vexnum;j++)
           G->arcs[i][j]=0;
    printf("输入所有的边对应的两个顶点、权值。例如:4个顶点3条边时\n0 1 2\n1 2 1\n2 3 3\n\n");
    for(k=0;k<G->arcnum;k++)
    {
        scanf("%d %d %d",&v1,&v2,&w);
        i = LocateVex(G, v1);// 查找顶点在顶点向量中的下标
        j = LocateVex(G, v2);
        if((i==-1||j==-1))
            printf("没有该边请重新输入\n");
        else
        {
            G->arcs[i][j]=w;//存入权值
            G->arcs[j][i]=w;
        }
    }
}
//***************************************************
void CreateALGraph(ALGraph *G,int a,int b)//建立邻接表（a顶点数，b边数）
{
	int i=0,j,k;
	ArcNode *s;
	G->vexnum=a;
    G->arcnum=b;
	printf("%d个顶点分别为:",a);
    for(i = 0; i < G->vexnum; i++)
    {
		G->vertices[i].d=i;
		printf("%d ",G->vertices[i].d);
    }
	printf("\n");
	for(i=0;i<G->vexnum;i++)
		G->vertices[i].firstarc=NULL;   	//初始化所有表头节点的指针域 
	printf("输入所有的边构造邻接表。例如:4个顶点3条边时\n0 1\n1 2\n2 3\n\n");
	for(k=0;k<G->arcnum;k++)
	{   			                         //输入各边，构造邻接表  
		scanf("%d %d",&i,&j);    			  //输入一条边的两个节点 
		s=(ArcNode*)malloc(sizeof(ArcNode));  // 生成一个新节点 
		s->adjvex=j;
		s->nextarc=G->vertices[i].firstarc;  //头插法建立新节点 
		G->vertices[i].firstarc = s;
		s=(ArcNode*)malloc(sizeof(ArcNode)); //生成另一个对称的新的边节点 
		s->adjvex=i;
		s->nextarc=G->vertices[j].firstarc;
		G->vertices[j].firstarc = s;
	}
}
//***************************************************
void MatToList(Mgraph g,ALGraph *G)//将邻接矩阵g转换成邻接表G
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
void ListToMat(ALGraph G,Mgraph *g)//将邻接表G转换成邻接矩阵g
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
void DFS (Mgraph *G,int v,int V)//深度优先
{
	
	int i;
	visited[v] = 1;	 
	printf("%d ",G->vexs[v]);	//	输出当前顶点 
	for(i=0;i<V ;i++)
		if(visited[i]==0&&G->arcs[v][i]!=0) //	如果当前顶点的邻近点存在，且没有遍历过 则继续递归遍历
		    DFS (G,i,V);	                //	递归遍历当前顶点的邻近点 	
}
void Init_DFS (Mgraph *G,int V)
{
	int i;
	for(i=0;i<V;i++)//标识数组全为0
		visited[i] = 0;
	for(i=0;i<V ;i++)	   // 检查每一个顶点是否被访问到 
	{
		if(visited[i]==0)	
			DFS (G,i,V);   // 开始深度遍历	
	} 
	putchar('\n');
}
//***************************************************
void BFSGraph(ALGraph *G,int a)/*广度优先*/
{
	int visited[100];
     int i;
	 ArcNode *temp;
    //对访问标志数组的初始化
    for(i = 0;i<a;i++)
        visited[i] = 0;
    for(i = 0;i<a;i++){
        if(visited[i]==0){
         	printf("%d ",G->vertices[i].d);//访问表头节点
         visited[i]=1;//设置访问标签
        }
         //对该链表进行遍历访问
         temp =G->vertices[i].firstarc;
         while(temp){
            if(visited[temp->adjvex]==0){//如果该顶点未访问过
                printf("%d ",G->vertices[temp->adjvex].d);
                visited[temp->adjvex] = 1;//设置访问标签
            }
            temp = temp->nextarc;
        }
    }
}
//***************************************************
void print_graph(Mgraph G)//输出邻接矩阵
{
    int i, j;
 
    printf("\n\n无向图邻接矩阵:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
 
            printf("%d ", G.arcs[i][j]);
 
        printf("\n");
    }
}
//*************************************************** 
void Output(ALGraph G)//输出邻接表
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
	printf(        "先输入你想创建图的顶点和边数量再选择以何种方式建立图\n");
	printf("请输入要创建的图的顶点数\n");
	scanf("%d",&a);
	printf("请输入要创建的图的边数\n");
	scanf("%d",&b);
	printf("              无向网小程序\n");
    printf("*****************************************\n");
	printf(        "        1. 清屏\n");
	printf(        "        2. 以邻接矩阵g建立无向网\n");
	printf(        "        3. 以邻接表G建立无向网\n");
	printf(        "        4. 将邻接矩阵g转换为邻接表G\n");
    printf(        "        5. 将邻接表G转换为邻接矩阵g\n");
	printf(        "        6. 将邻接矩阵g深度优先遍历\n");
    printf(        "        7. 将邻接表G广度优先遍历\n");
    printf(        "        8. 退出\n");
	printf("*****************************************\n");
	while(1)
	{
		printf("功能:");
		scanf("%d",&c);
		if(c==1)
		{
			system("cls");
			printf("              无向网小程序\n");
			printf("*****************************************\n");
			printf(        "        1. 清屏\n");
			printf(        "        2. 以邻接矩阵g建立无向网\n");
			printf(        "        3. 以邻接表G建立无向网\n");
			printf(        "        4. 将邻接矩阵g转换为邻接表G\n");
			printf(        "        5. 将邻接表G转换为邻接矩阵g\n");
			printf(        "        6. 将邻接矩阵g深度优先遍历\n");
			printf(        "        7. 将邻接表G广度优先遍历\n");
			printf(        "        8. 退出\n");
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
			printf("图的邻接矩阵g转换成邻接表G:\n");
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
			printf("深度优先搜索遍历邻接矩阵g结果为:\n");
			Init_DFS (&g,a);
		}
		if(c==7)
		{
			printf("广度优先搜索遍历邻接表G结果为:\n");
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