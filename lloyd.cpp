#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <time.h>
#include <fstream>
#include <sys/resource.h>
#include <unistd.h>
#include <cmath>

using namespace std;

int POINTS;
int CLUST;

double *x;
double *y;
int *own;
double *dist;
double *xC;
double *yC;
double *xCa;
double * yCa;
int *size;
double *xT;
double *yT;

int main(int argc, char **argv)
{
bool testing = false;

if(argc != 2 && argc !=3)
{
	cout << "Usage lloyd number_of_clusters [optional: t] < file_name" << endl;
	return -1;
}

if(argc == 3 && argv[2][0] == 't')
{
	testing = true;
}



//read in
cin >> POINTS >> CLUST;
CLUST = atoi(argv[1]);
if(CLUST<POINTS)
{
	cout << "k must be greater than n" << endl;
	return -1;
}

 dist =new double[POINTS];
 x =new double[POINTS];
  y =new double[POINTS];
 own =new int[POINTS];
 xC =new double[CLUST];
 yC= new double[CLUST];
 size = new int[CLUST];
 xT = new double[CLUST];
 yT = new double[CLUST];
xCa = new double[CLUST];
yCa = new double[CLUST];


for(int i = 0; i<POINTS; cin >> x[i] >> y[i], ++i);
//for(int i = 0; i<POINTS;cout << i << " " << x[i] << " " << y[i] << endl, ++i);

//clust selection
bool valid;
int choice;
int loc=0;
srand (time(0));

for(int i = 0; i < CLUST; ++i) xC[i]=yC[i]= -1;
while(loc !=CLUST)
{

choice = (int)(rand()%POINTS);
valid = true;
for(int i = 0; i < loc; ++i)
{
if(xC[i] == x[choice] && yC[i] == y[choice])
	{valid = false;break;}
}
if(valid)
{
xC[loc] = x[choice];
yC[loc] = y[choice];
++loc;
}


}


//convergence testing
bool converged = false;
int count =0;
double tDist;
double cMove;
for(int i = 0; i < POINTS;++i){own[i] = -1;dist[i] = DBL_MAX;}

while(!converged)
{
//if(count == 0)count =1;
//else 
converged = true;

for(int i = 0; i < CLUST; ++i) xT[i] = yT[i] = size[i] = 0;

for(int i = 0; i < POINTS; ++i)
{

for(int j = 0; j < CLUST; ++j)
{
tDist = sqrt((x[i]-xC[j])*(x[i]-xC[j])+(y[i]-yC[j])*(y[i]-yC[j]));
//tDist = tDist < 0 ? tDist*-1 : tDist;
if(tDist < dist[i])
{
dist[i] = tDist;
own[i] = j;
//converged = false;
}
}//j to clust

++size[own[i]];
xT[own[i]]+=x[i];
yT[own[i]]+=y[i];
}//i to point

cMove =0;
for(int j = 0; j < CLUST;++j) {xCa[j] = xC[j]; yCa[j] = yC[j];}
for(int j = 0; j < CLUST; ++j) {xC[j] = xT[j]/size[j];yC[j]=yT[j]/size[j];}
for(int j = 0; j < CLUST;++j) cMove += sqrt( (xCa[j] - xC[j])*(xCa[j]-xC[j])+(yCa[j]-yC[j])*(yCa[j]-yC[j])); 
if(cMove != 0)
	converged = false;
}//til converged

if(testing){
	
ifstream ds;
struct timeval time;
struct rusage cpuTime;
double t;
unsigned int memUsage;

getrusage(RUSAGE_SELF,&cpuTime);
time=cpuTime.ru_utime;
t = (double)time.tv_sec+(double)time.tv_usec/1000000.0;
cout << "Time Taken: " << t << endl;

char buffer[50];
snprintf(buffer,sizeof(buffer),"/proc/%d/statm",getpid());
ds.open(buffer);
ds >> memUsage;
ds >> memUsage;
cout << "Memory Usage: " << memUsage << " kb"<< endl;
ds.close();
}
else{
cout << POINTS << " 2 " << CLUST << endl;
for(int i = 0; i < CLUST;++i)
cout << xC[i] << " " << yC[i] << endl;
for(int i = 0; i < POINTS;++i)
cout << own[i] << " " << x[i] << " " << y[i] << endl;
}

delete [] x;
delete [] y;
delete [] own;
delete [] dist;
delete [] xC;
delete [] yC;
delete [] size;
delete [] xT;
delete [] yT;


return 0;
}
