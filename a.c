// C program to implement the a-star search algorithm
// heuristic formula = straight line distance - min(# of vertices away from Bucharest)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 20

struct City{
	char name;
	int h;
};

// array of verticies
struct City* lstCities[MAX];

//adjacency matrix
int adjMatrix[MAX][MAX];

//city count
int cityCount=0;

//add city to the city list
void addCity(char name, int h){
	struct City* city = (struct City*)malloc(sizeof(struct City));
	city->name = name;
	city->h = h;
	lstCities[cityCount]=city;
	cityCount++;
}

//add edge to edge array.
void addEdge(int start, int end, int distance){
	adjMatrix[start][end]=distance;
	adjMatrix[end][start]=distance;
}

// tree
struct Tree{
	int city;
	struct Tree *parent;
	struct Tree *leftleft;
	struct Tree *leftmiddle;
	struct Tree *rightmiddle;
	struct Tree *rightright;
	int h;
	int g;
	int open;
};

struct Tree *insertNode(struct Tree *tree, int city, int h, int g){

	struct Tree *clone,*branch;

	branch = (struct Tree *)malloc(sizeof(struct Tree));
	tree->open=0;
	clone=tree;
	branch->city=city;
	branch->h=h;
	branch->g=g;
	branch->leftleft=NULL;
	branch->leftmiddle=NULL;
	branch->rightmiddle=NULL;
	branch->rightright=NULL;
	branch->open=1;
	if(clone->leftleft==NULL){
		clone->leftleft=branch;
		clone->leftleft->parent=clone;
		return clone;
	}
	if(clone->leftmiddle==NULL){
		clone->leftmiddle=branch;
		clone->leftmiddle->parent=clone;
		return clone;
	}
	if(clone->rightmiddle==NULL){
		clone->rightmiddle=branch;
		clone->rightmiddle->parent=clone;
		return clone;
	}
	if(clone->rightright==NULL){
		clone->rightright=branch;
		clone->rightright->parent=clone;
		return clone;
	}
};

struct Tree* gotoroot(struct Tree* tree){
	while(tree->parent!=NULL){
		tree=tree->parent;
	}
	return tree;
}

//global variables
int min_city = -1;
int min_f;
int path[MAX];

int minpath(struct Tree *tree){

	struct Tree *clone;
	struct Tree *cloneclone;

	clone = tree;
	if(clone->open==1){

		int f,k;

		f=clone->g+clone->h;
		if(f<min_f){
			for(k=0;k<MAX;k++){
				path[k]=-1;
			}
			k=0;
			min_f=f;	
			min_city=clone->city;
			cloneclone=clone;
			while(cloneclone!=NULL){
				path[k]=cloneclone->city;
				k++;
				cloneclone=cloneclone->parent;
			}
		}
	}
	if(clone->leftleft!=NULL)
		minpath(clone->leftleft);
	if(clone->leftmiddle!=NULL)
		minpath(clone->leftmiddle);
	if(clone->rightmiddle!=NULL)
		minpath(clone->rightmiddle);
	if(tree->rightright!=NULL)
		minpath(clone->rightright);
	return 0;
}

int main()
{
	int i, j;
	char source;
	
	//set adjacency matrix to 0
	for(i=0; i<MAX; i++){
		for(j=0; j<MAX; j++)
			adjMatrix[i][j]=0;
	}

	//construct vertices
	addCity('A',363);  // 0
	addCity('B',0);    // 1
	addCity('C',158);  // 2
	addCity('D',239);  // 3
	addCity('E',158);  // 4
	addCity('F',175);  // 5
	addCity('G',76);   // 6
	addCity('H',149);  // 7
	addCity('I',223);  // 8
	addCity('L',239);  // 9
	addCity('M',237);  // 10
	addCity('N',230);  // 11
	addCity('O',377);  // 12
	addCity('P',9);    // 13
	addCity('R',191);  // 14
	addCity('S',251);  // 15
	addCity('T',325);  // 16
	addCity('U',79);   // 17
	addCity('V',197);  // 18
	addCity('Z',370);  // 19

	// construct edges
	addEdge(0,19,75);  // A-Z
	addEdge(0,15,140); // A-S
	addEdge(0,16,118); // A-T
	addEdge(1,13,101); // B-P
	addEdge(1,6,90);   // B-G
	addEdge(1,17,35);  // B-U
	addEdge(1,5,211);  // B-F
	addEdge(2,13,138); // C-P
	addEdge(2,3,120);  // C-D
	addEdge(2,14,146); // C-R
	addEdge(3,10,75);  // D-M
	addEdge(4,7,36);   // E-H
	addEdge(5,15,99);  // F-S
	addEdge(7,17,98);  // H-U
	addEdge(8,11,87);  // I-N
	addEdge(8,18,92);  // I-V
	addEdge(9,10,70);  // L-M
	addEdge(9,16,111); // L-T
	addEdge(12,15,151);// O-S
	addEdge(12,19,71); // O-Z
	addEdge(13,14,97); // P-R
	addEdge(14,15,80); // R-S
	addEdge(17,18,142);// U-V

	int ida;

	// input source vertex
	printf("input: ");
	scanf("%c",&source);
	printf("IDA: ");
	scanf("%d",&ida);

	if(ida<0){
		printf("ida is less than zero\n");
		return 0;
	}
	if(ida==0){
		printf("ida is zero so start and end at %c\n",source);
		return 0;
	}

	// source state is goal state
	if(source=='B'){
		printf("\nYou are starting and ending at Bucharest. Total travel distance=0.\n\n");
		return 0;
	}

	// look for source vertex.
	int source_vertex=-1;
	for(i=0;i<MAX;i++){
		if(source==lstCities[i]->name)
			source_vertex=i;
	}
	if(source_vertex==-1){
		printf("input is not a city name");
		return 0;
	}
	else{
		printf("source %c\n", lstCities[source_vertex]->name);
	}

	struct Tree *root;

	root = (struct Tree *)malloc(sizeof(struct Tree));
	root->parent=NULL;
	root->leftleft=NULL;
	root->leftmiddle=NULL;
	root->rightmiddle=NULL;
	root->rightright=NULL;
	root->city=source_vertex;
	root->open=0;
	root->h=0;
	root->g=0;
	
	//function call to insert node
	for(i=0;i<MAX;i++){
		if(adjMatrix[root->city][i]!=0){
			root=insertNode(root, i, lstCities[i]->h,root->g+adjMatrix[root->city][i]);
			root->open=0;
			printf("%c->%c ",lstCities[root->city]->name,lstCities[i]->name);
			printf("f=g+h %d=%d+%d\n",lstCities[i]->h+adjMatrix[root->city][i],adjMatrix[root->city][i],lstCities[i]->h);
		}
	}

	//function call minpath
	min_f=2000;
	minpath(root);

	// sets root to last node of minpath
	for(i=MAX-1;i>=0;i--){
		if(path[i]==-1){
		}
		else{
			if(root->leftleft!=NULL){
				if(root->leftleft->city==path[i]){
					root=root->leftleft;
				}
				else{	
					if(root->leftmiddle!=NULL){
						if(root->leftmiddle->city==path[i]){
							root=root->leftmiddle;
						}
						else{
							if(root->rightmiddle!=NULL){
								if(root->rightmiddle->city==path[i]){
									root=root->rightmiddle;
								}
								else{
									if(root->rightright!=NULL){
										if(root->rightright->city==path[i]){
											root=root->rightright;
										}
									}
								}
							}
						}
					}
				}
			}
			printf("%c",lstCities[path[i]]->name);
			if(i!=0){printf("->");}
			else{printf(" is the best path with a %d evaluation\n", min_f);}
		}
	}
	if(min_city==1){
		printf("\nreached bucharest optimally end program\n");
		return 0;
	}
	if(ida==1){
		printf("ida is one end program\n");
		return 0;
	}

	//function call to insert node depth > 1
	int limit = 1;
	struct Tree *dummy;

	while(min_city!=1)
	{
		limit=1;
		for(i=0;i<MAX;i++){
			if(adjMatrix[root->city][i]!=0){
				root=insertNode(root, i, lstCities[i]->h,root->g+adjMatrix[root->city][i]);
				root->open=0;
				printf("%c->%c ",lstCities[root->city]->name,lstCities[i]->name);
				printf("f=g+h %d=%d+%d\n",lstCities[i]->h+adjMatrix[root->city][i]+root->g,root->g+adjMatrix[root->city][i],lstCities[i]->h);
			}
		}
		root=gotoroot(root);

		//function call minpath
		min_f=2000;
		minpath(root);
		for(i=MAX-1;i>=0;i--){
			if(path[i]==-1){
			}
			else{
				if(root->leftleft!=NULL){
					if(root->leftleft->city==path[i]){
						root=root->leftleft;
					}
					else{	
						if(root->leftmiddle!=NULL){
							if(root->leftmiddle->city==path[i]){
								root=root->leftmiddle;
							}
							else{
								if(root->rightmiddle!=NULL){
									if(root->rightmiddle->city==path[i]){
										root=root->rightmiddle;
									}
									else{
										if(root->rightright!=NULL){
											if(root->rightright->city==path[i]){
												root=root->rightright;
											}
										}
									}	
								}
							}
						}
					}
				}
				printf("%c",lstCities[path[i]]->name);
				if(i!=0){printf("->");}
				else{printf(" is the best path with a %d evaluation\n", min_f);}
			}
		}	
		if(min_city==1){
			printf("%d is distance to bucharest\n",min_f);
			printf("end program\n");
			return 0;
		}	
		dummy=root;
		while(dummy!=NULL){
			dummy=dummy->parent;
			limit++;
		}
		if(limit>ida+1){
			printf("ida limit\n");
			return 0;

		}
	}
}
