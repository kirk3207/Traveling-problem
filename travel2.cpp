#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<fstream>
#include<sstream>
#define INF 1000000
using namespace std;

int w[100][100];
int d[100];
int parent[100];
int dist[100][100];
int sortedHappy[2][100];
int sortedDistance[2][100];
int order[2][100];
bool valid[100];
bool visit[100];
bool VISITED[100];

stack<int> trail;
stack<int> backTime;
vector<string> name;
vector<int> happiness;
vector<int> opentime;
vector<int> closetime;
int vertice, edge, quota, startTime, openTime, closeTime;
int weight,happy;
int nowtime=0;
int finalTime=0;
int finalHappiness=0;
int finalHappiness_plus=0;
string s;
string s1, s2;
int v1, v2;
ifstream fin;
ofstream fout1, fout2;
stringstream inlocation;
stringstream out1location;
stringstream out2location;

int transVertex(string s)
{
    int i;
    for(i=0;i<100;i++)
    {
        if(name[i]==s)
        {
            break;
        }
    }
    return i;
}

void dijkstra(int source)
{
    for (int i=0; i<100; i++) visit[i] = false;   // initialize
    for (int i=0; i<100; i++) d[i] = 1e9;

    d[source] = 0;
    parent[source] = source;

    for (int k=0; k<100; k++)
    {
        int a = -1, b = -1, min = 1e9;
        for (int i=0; i<100; i++)
            if (!visit[i] && d[i] < min)
            {
                a = i;  // 記錄這一條邊
                min = d[i];
            }

        if (a == -1) break;     // 起點有連通的最短路徑都已找完
//      if (min == 1e9) break;  // 不連通即是最短路徑長度無限長
        visit[a] = true;

        // 以邊ab進行relaxation
        for (b=0; b<100; b++)
            if (!visit[b] && d[a] + w[a][b] < d[b])
            {
                d[b] = d[a] + w[a][b];
                parent[b] = a;
            }
    }
}

void BubSort(int A[][100], int n)
{
    for(int i=n-1;i>0;i--)
    {
       for(int j=0;j<i;j++)
       {
          if(A[0][j] > A[0][j+1])
          {
              swap(A[0][j],A[0][j+1]);
              swap(A[1][j],A[1][j+1]);
          }
       }
    }
}

void find_path(int x)   // 印出由起點到x點的最短路徑
{
    if (x != parent[x])// 先把之前的路徑都印出來
    {
        //trail.push(x);
        //VISITED[x]=true;
        find_path(parent[x]);
    }
    trail.push(x);
    VISITED[x]=true;
    if(x==0)
    {

    }
    else
    {
        nowtime+=w[x][parent[x]];
        fout1 << name[x] <<" "<<nowtime<<" "<<nowtime<<endl; // 再把現在的位置印出來
        fout2 << name[x] <<" "<<nowtime<<" "<<nowtime<<endl;
        backTime.push(w[x][parent[x]]);
    }

}

void goBack(int x)
{
    trail.pop();
    while(!trail.empty())
    {
        nowtime+=backTime.top();
        fout1 << name[trail.top()] <<" "<<nowtime<<" "<<nowtime<<endl;
        fout2 << name[trail.top()] <<" "<<nowtime<<" "<<nowtime<<endl;
        trail.pop();
        backTime.pop();
    }
}

void find_path_1(int x)   // 印出由起點到x點的最短路徑
{
    if (x != parent[x])// 先把之前的路徑都印出來
    {
        //trail.push(x);
        //VISITED[x]=true;
        find_path_1(parent[x]);
    }
    trail.push(x);
    VISITED[x]=true;
    if(x==0)
    {

    }
    else
    {
        nowtime+=w[x][parent[x]];
        if(nowtime>=opentime[x] && nowtime<= closetime[x])
        {
            finalHappiness_plus+=happiness[x];
        }
        backTime.push(w[x][parent[x]]);
    }
}

void goBack_1(int x)
{
    trail.pop();
    while(!trail.empty())
    {
        nowtime+=backTime.top();
        if(nowtime>=opentime[trail.top()] && nowtime<= closetime[trail.top()])
        {
            finalHappiness_plus+=happiness[trail.top()];
        }
        trail.pop();
        backTime.pop();
    }
}

int main(int argc, char *argv[])
{

    inlocation<<"./"<<argv[1]<<"/tp.data";
    out1location<<"./"<<argv[1]<<"/ans1.txt";
    out2location<<"./"<<argv[1]<<"/ans2.txt";
    int i=0;
    int j=0;

    for(int i=0;i<100;i++)
    {
        if(i==0)VISITED[i]=true;
        else VISITED[i]=false;
    }

    for(int i=0;i<100;i++)
    {
        valid[i]=false;
    }

    for(int i=0;i<100;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(i==j) w[i][j]=0;
            else w[i][j]=1000000;
        }
    }
    fin.open(inlocation.str());
    fout1.open(out1location.str());
    fout2.open(out2location.str());
    fin>>vertice>>edge>>quota>>startTime;
    nowtime = startTime;

    while(i<vertice)
    {
        fin>>s>>happy>>openTime>>closeTime;
        name.push_back(s);
        happiness.push_back(happy);
        opentime.push_back(openTime);
        closetime.push_back(closeTime);
        //cout<<g.name[i]<<" "<<g.happiness[i]<<endl;
        i++;
    }

    if(startTime>=opentime[0] && startTime<= closetime[0]) finalHappiness_plus+=happiness[0];

    while(j<edge)
    {
        fin>>s1>>s2>>weight;
        v1=transVertex(s1);
        v2=transVertex(s2);
        w[v1][v2]=weight;
        w[v2][v1]=weight;
        j++;
    }

    dijkstra(0);

    for(int i=0;i<happiness.size();i++)
    {
        sortedHappy[0][i]=happiness[i];
        sortedHappy[1][i]=i;
    }

    for(int i=0;i<vertice;i++)
    {
        sortedDistance[0][i]=d[i];
        sortedDistance[1][i]=i;
    }

    BubSort(sortedHappy,vertice);
    BubSort(sortedDistance,vertice);

    for(int i=0;i<vertice;i++)
    {
        order[0][sortedDistance[1][i]]+=i;
        order[0][sortedHappy[1][i]]+=i;
        order[1][i]=i;
    }

    BubSort(order,vertice);

    for(int i=vertice-1;i>0;i--)
    {
        if(VISITED[i]==false)
        {
            if(finalTime+2*d[order[1][i]]<=quota)
            {
                find_path_1(order[1][i]);
                goBack_1(order[1][i]);
                finalTime+=2*d[order[1][i]];
            }
        }
    }

    for(int i=0;i<vertice;i++)
    {
        if(VISITED[i]==true)
        {
            finalHappiness+=happiness[i];
        }
    }

    fout1<<finalHappiness<<" "<<finalTime<<endl;
    fout2<<finalHappiness_plus<<" "<<finalTime<<endl;

    for(int i=0;i<100;i++)
    {
        if(i==0)VISITED[i]=true;
        else VISITED[i]=false;
    }

    finalHappiness = 0;
    finalTime = 0;
    nowtime = startTime;

    fout1<<name[0]<<" "<<startTime<<" "<<nowtime<<endl;
    fout2<<name[0]<<" "<<startTime<<" "<<nowtime<<endl;

    for(int i=vertice-1;i>0;i--)
    {
        if(VISITED[i]==false)
        {
            if(finalTime+2*d[order[1][i]]<=quota)
            {
                find_path(order[1][i]);
                goBack(order[1][i]);
                finalTime+=2*d[order[1][i]];
            }
        }
    }
    fin.close();
    fout1.close();
    fout2.close();
    return 0;
}

