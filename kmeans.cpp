#include <iostream> 
#include <fstream>
#include <sys/resource.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <float.h>
#include <unistd.h>
using namespace std;

double *c[2]; //Cluster Center
double *ca[2]; //Vector Sum of cluster movement
int * q; //Number of points assigned to cluster
double *p; //distance c[j] last moved
double *s; //distance from c[j] to closest cluster

double *x[2]; //points
int *a; // a[i] =clust point assigned too
double *u; //upper bound
double *l; //lower bound

bool testing = false;

int k; //numb of clusters
int n; //numb of data points


/* Functions */
int PAC(int i); // Point all cluster

int main(int argc, char **argv)
{
srand (time(0));
ifstream ds;
/* Initialize: Allocate memory then set up defaults */
if(argc !=3 && argc !=4)
{
	cout << "Usage: kmeans input_filename number_of_clusters [optional: t]" << endl;
	return -1;
}

//If True will also print out the stats at the end
if(argc==4 && argv[3][0] == 't')
	testing = true;


ds.open(argv[1]);
if(!ds)
{
        cerr << "Unable to open file " << argv[1] << endl;
        return -1;

}


/* Number of input comes from file, k from user input */
ds >> n>> k;
k = atoi(argv[2]);
if(n<k)
{
	cout << "n must be greater than k" << endl;
	return -1;
}
/* Allocating memory for different lists */
c[0] = new double[k];
c[1] = new double[k];
ca[0] = new double[k];
ca[1] = new double[k];
q = new int[k];
p = new double[k];
s = new double[k];

x[0] = new double[n];
x[1] = new double[n];
a = new int[n];
u = new double[n];
l = new double[n];

/* reading in data */
for(int i = 0; i < n;++i)
	ds >> x[0][i] >> x[1][i];
ds.close();


/* Initializing Cluster Location, using random point method */

int loc = 0;
int choice;
bool valid;

for(int i = 0; i < k; ++i) c[0][i]=c[1][i]=-1;
while(loc !=k)
{

choice = rand()%n;
valid = true;
for(int i = 0; i < loc; ++i)
{
if(c[0][i] == x[0][choice] && c[1][i] == x[1][choice])
        {valid = false;break;}
}
if(valid)
{
c[0][loc] = x[0][choice];
c[1][loc] = x[1][choice];
++loc;
}
}


/* # of points per cluster and vector movement = 0 */
for(int i = 0; i < k;++i)
{
q[i] = 0;
ca[0][i] = 0;
ca[1][i] = 0;
}


/* assigning points to initial clusters */

for(int i = 0; i < n;++i)
{
a[i] = PAC(i);
q[a[i]]++;
ca[0][a[i]]+=x[0][i];
ca[1][a[i]]+=x[1][i];
}




/* Main Hamerly Loop! */
bool conv = false; //Flag to test for convergance based on cluster movement
double temp; //Used for temp holding during inner cluster distnace testing
double m; //max value to check with
int aa; //holds previous cluster assignment
double cs[2]; //holds previous cluster center
double pc; //Sum of distance moved, used for convergance checking
int r; //Max distance last moved
int ra; //Second max distance last moved

while(!conv)
{

/* Finding Inner Cluster Distance */
for(int i = 0; i < k; ++i) {

	s[i] = sqrt(c[0][i]*c[0][i]-2*c[0][i]*c[0][(i+1)%k]+c[0][(i+1)%k]*c[0][(i+1)%k] + c[1][i]*c[1][i]-2*c[1][i]*c[1][(i+1)%k]+c[1][(i+1)%k]*c[1][(i+1)%k]);
	for(int j = 0; j < k;++j)
	{
		if(j==i) continue;
		temp = sqrt(c[0][i]*c[0][i]-2*c[0][i]*c[0][j]+c[0][j]*c[0][j] + c[1][i]*c[1][i]-2*c[1][i]*c[1][j]+c[1][j]*c[1][j]);
		if(temp < s[i])
			s[i] = temp;
	}
	

}





/* Assigning Points to Clusters */

for(int i = 0; i < n;++i)
{

if(s[a[i]]/2 > l[i])
	m = s[a[i]]/2;
else
	m = l[i];

if(u[i] > m) //First  Bound Check
{
u[i]  = sqrt(c[0][a[i]]*c[0][a[i]]-2*c[0][a[i]]*x[0][i]+x[0][i]*x[0][i] + c[1][a[i]]*c[1][a[i]]-2*c[1][a[i]]*x[1][i]+x[1][i]*x[1][i]);

if(u[i] > m) //Second Bound Check
{
aa = a[i];
a[i] = PAC(i);
if(aa!=a[i])
{

q[aa]-=1;
q[a[i]]+=1;

/*
  While the sudo code outlined in Hamerly's paper makes use of and updates c' here
  due to unknown reasons this was producing incorrect answers even though I verified that
  there was no miss calculations in the addition and subtraction. I make use of a more direct
  calculation method which will match the worst case senario for Hamerly's algorithm but will be
  slower on the average case senario 
  
  Hamerly's code left commented out bellow
*/

//ca[0][aa]-=x[0][aa];
//ca[1][aa]-=x[1][aa];
//ca[0][a[i]]+=x[0][a[i]];
//ca[1][a[i]]+=x[1][a[i]];


}//Cluster Change

}//Second Bound

}//First Bound

}//for all points

/* Updates the centers as needed  */

/* Alternate method of calculating cluster movement by taking the average of all points,
  Hamerly's method would simply skip over these two for loops */
  
for(int i = 0; i < k; ++i)
{
ca[0][i] = ca[1][i] = 0;
}
for(int i = 0; i < n; ++i)
{
ca[0][a[i]]+=x[0][i];
ca[1][a[i]]+=x[1][i];
}

for(int i = 0; i < k; ++i)
{

cs[0] = c[0][i];
cs[1] = c[1][i];

/* It is possible for some clusters to end up having 0 points assigned to them 
  This has not happened since certain bugs have been solved, but has been left in since it is still 
  technically possible for this to open*/
if(q[i] > 0){
c[0][i] = ca[0][i]/q[i];
c[1][i] = ca[1][i]/q[i];
}
p[i] = sqrt(cs[0]*cs[0]-2*cs[0]*c[0][i]+c[0][i]*c[0][i] +  cs[1]*cs[1]-2*cs[1]*c[1][i]+c[1][i]*c[1][i]);
}



/*Checking for if the data has converged, sum up distance moved, if nothing moved then we dont need to run again*/
pc = 0;
for(int i = 0; i < k;++i)
	pc+=p[i];
conv = (pc==0); 


/* Update the bounds as needed */


if(!conv)
{
/* Here is the second difference between Hamerly's code and mine
   In my testing I found that if I reduced the lower bound by
   p[ra] or p[r] as done in Hamerly's algorithm it could sevearly
   reduce the accuracy of the code
   Making use of R and RA reduces the amount of inner loop checks needed
   However I choose to prefer accuracy over speed up, and given I am avoiding
   K steps here the trade off should not be as bad

   Hamerly's code would include the following commented out code block
   It would include the next commented out code block that starts with
   if(r==a[i])
   and would comment out the line 
   l[i]-=p[a[i]];
*/

/*
//cout << "Clust Moved" << endl;
r = 0;
ra= 0;
for(int i = 0; i < k;++i)
{

if(p[r] >p[i])
{
ra = r;
r = i;
}
else if (p[ra] > p[i])
	ra = i;

}
*/

for(int i = 0; i < n; ++i)
{
u[i]+=p[a[i]];
l[i]-=p[a[i]];

/*
if(r==a[i])
	l[i]-=p[ra];
else
	l[i]-=p[r];
*/
}

} //if not conv


} //while not converged 


/*Data Collection Code*/
/* While memory usage won't be affected by being placed before
   or after the print/delete statements
   cpu time however is heavily affected by output and I am here to
   measure the time it takes for hamerly's to run, not how long
   it takes to print out

*/

if(testing){

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
else
{
/* Printing Out Cluster Data */
//number of data points, dimensions, number of clusters
cout << n << " 2 " << k << endl;
for(int i = 0; i < k;++i)
cout << c[0][i] << " " << c[1][i] << endl;
for(int i = 0; i < n;++i)
cout << a[i] << " " << x[0][i] << " " << x[1][i] << endl;
}

delete [] c[0];
delete [] c[1];
delete [] ca[0];
delete [] ca[1];
delete [] q;
delete [] p;
delete [] s;

delete [] x[0];
delete [] x[1];
delete [] a;
delete [] u;
delete [] l;

return 0;
}//Main



int PAC(int i)
{
int clust = 0;
double temp;
u[i] = DBL_MAX; //Set a max value so there is no problem w/ comparasons 
l[i] = DBL_MAX;
for(int j = 0; j < k; ++j)
{
temp  = c[0][j]*c[0][j]-2*c[0][j]*x[0][i]+x[0][i]*x[0][i] + c[1][j]*c[1][j]-2*c[1][j]*x[1][i]+x[1][i]*x[1][i];
if(temp < u[i]){
	l[i] = u[i];
	u[i] = temp;
	clust = j;
	}
else if(temp < l[i]) //This is added in to solve edge cases caused by initialization 
	 l[i] = temp;
}

l[i] = sqrt(l[i]);
u[i] = sqrt(u[i]);
return clust; 
}
