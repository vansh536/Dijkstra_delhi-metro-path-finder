#include <iostream>
#include <limits.h> 
#include<string>
#include<math.h>
#include<cstdlib>   
#include<vector>
#include<fstream>
#include<time.h>
#include<windows.h>   
using namespace std;

const int V=248;

struct metro_station_code
{
    string name;
    int code;
    string color;
};

struct metro_station_code station[V];

float graph[V][V];

struct node1
    {
        vector <float>p;
    }P[V];
   
string make_uppercase(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
}

int total_time(float dist); //v
int total_cost(float dist); //v
void Path(float dist,int e,int st);
int minDistance(float dist[], bool sptSet[]);
void dijkstra(float graph[V][V], int src,int targ);
void user_input();

void delay(unsigned int ms)
{
    clock_t goal=ms+clock();
    while(goal>clock());
}

int total_time(float dist)
{
    float speed=0.55;
    return ceil(dist/speed);
}

int total_cost(float dist)
{
    if(dist<=2)
        return 10;
    else if(dist>2&&dist<=5)
        return 20;
    else if(dist>5&&dist<=12)
        return 30;
    else if(dist>12&&dist<=21)
        return 40;
    else if(dist>21&&dist<=32)
        return 50;
    else
        return 60;
}

void Path(float d,int e,int st)
{
    int t=e,s;
    static float dist=0;
    dist+=d;

    cout<<endl<<"-------------------------"<<endl;
    cout<<"  THE SHORTEST PATH IS :"<<endl;
    cout<<"-------------------------"<<endl<<endl;
    delay(500);

    vector <int> path;
    path.push_back(t);
    while(t!=st)
    {
        s=P[t].p.size();
        t=P[t].p[s-1];
        path.push_back(t);
    }
    vector <int>::iterator i=path.end();
    string str;
    string color;

    vector<int>::iterator i2=path.end();
    i2--;

    int n_of_stations=0;

    while(i!=path.begin())
    {
        i--;

        if(i!=i2)
        {
        if(station[*(i2)].color!=station[*(i)].color)
        {
            delay(500);
            cout<<endl<<endl<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}"<<endl<<endl;
            delay(500);
        }
        i2--;
        }
        str=station[*i].name;
        cout<<" -->> "<<str;
        n_of_stations++;
    }

    delay(500);

    cout<<endl<<endl<<"----------------------------"<<endl;
    cout<<"PATH LENGTH IS : "<<d<<" KM"<<endl;
    delay(500);
    cout<<"AVERAGE TIME : "<<total_time(d)<<" MIN"<<endl;
    delay(500);
    cout<<"AVERAGE FARE : Rs "<<total_cost(d)<<endl;
    delay(500);
    cout<<"NO OF STATIONS : "<<n_of_stations-1<<endl;
    cout<<"----------------------------"<<endl<<endl;
    

  return;
}
 

int minDistance(float dist[], bool sptSet[])
{
   float min = INT_MAX;
   int min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}

void dijkstra(float graph[V][V], int src,int targ)
{
    //make shortest path 

    float dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V-1; count++)
    {
         int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                P[v].p.push_back(u);
            }
    }
    Path(dist[targ], targ,src);
}

int lcs( string X,string Y ) 
{ 
    //used in same match function 

	int m=X.length();
	int n=Y.length();
   int L[m+1][n+1]; 
   int i, j; 
   
   for (i=0; i<=m; i++) 
   { 
     for (j=0; j<=n; j++) 
     { 
       if (i == 0 || j == 0) 
         L[i][j] = 0; 
   
       else if (X[i-1] == Y[j-1]) 
         L[i][j] = L[i-1][j-1] + 1; 
   
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]); 
     } 

   } 
   return L[m][n]; 
} 

int sameMatch(string s){

    //return station code by matching user input with data sheet , if not found then returns -1 
	int max=0,maxi=-1;
	for(int i=0;i<248;i++){
		int val=lcs(s,station[i].name);
		if(val>max){
			maxi=station[i].code;
			max=val;
		}
	}
	if(max<station[maxi].name.length()/2)
		return -1;
	return maxi;
}

void user_input()
{	
    int loop =1 ;
    while(loop==1)
    {
        string start_s;
        string line,col;
        string end_s;

        cout<<"ENTER YOUR STARTING STATION : ";
        getline(cin,start_s);

        cout<<endl<<"ENTER THE DESTINATION STATION : ";
        getline(cin,end_s);

        start_s=make_uppercase(start_s);
        end_s=make_uppercase(end_s);

        int startcode,endcode; 
        int startflag=0,endflag=0; 

        startcode=sameMatch(start_s);
        endcode=sameMatch(end_s);

        if(startcode==-1)
        	startflag=1;
        if(endcode==-1)
        	endflag=1;

        int fault=0;
        if(startflag==1)
        {
            cout<<"WRONG STARTING STATION NAME ENTERED "<<endl;
            fault=1;
        }
        if(endflag==1)
        {
            cout<<"WRONG DESTINATION STATION NAME ENTERED "<<endl;
            fault=1;
        }
        if(fault==0){
            dijkstra(graph, startcode,endcode);
            cout<<"DO YOU WANT TO GET ANOTHER PATH ? ( YES / NO ) : ";
            string check;
            cin>>check;
            cout<<endl;
            cin.ignore();
            string val = make_uppercase(check);
            if(val!="YES")
            {
                loop=0;
            }
        }
    }	
}

int main()
{
    cout<<endl<<"WELCOME TO DELHI METRO SHORTEST PATH FINDER"<<endl;
    cout<<"==========================================="<<endl<<endl;

    int temp,n1,n2;
    float dis;
    ifstream fin;
    fin.open("node_values_new.txt");

    for(int i=0;i<248;i++)
    {
       for(int j=0;j<248;j++)
        graph[i][j]=0;
    }

    for(int i=1;i<=V;i++)
    {
        fin>>temp;
        fin>>n1;
        for( int j=0;j<temp;j++)
        {
           fin>>n2;
           fin>>dis;
           graph[n1-1][n2-1]=dis;
        }

    }

    string line,col;
    ifstream code;
    ifstream color;
    code.open("stationcodes.txt");
    color.open("stationcolorcodes.txt");
    for(int i=0;i<V;i++)
    {
        getline(code, line);
        station[i].name=line;
        station[i].code=i;
        getline(color,col);
        station[i].color=col;
    }  

    user_input();
}

