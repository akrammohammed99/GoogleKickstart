// Question link: https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff43/00000000003379bb
#include<bits/stdc++.h>
using namespace std;
vector<int>adj[26];   //adjaceny list to store represent the graph
int n,m;
string s[30];
bool vis[26];         // tracking visited nodes for performing topological sort
int visited[26];      // tracking visited nodes for checking if there is a cycle in the graph
stack <char> mystack; // stack to hold the topologically sorted nodes
bool flag = 0;        // flag to indicate if there is a cycle in the graph
void cycledfs(int node)
{
  if(visited[node] == -1)
  {
      flag = 1;
      return;
  }

  visited[node] = -1;

  for(int i = 0; i < adj[node].size(); i++)
  {
      if(visited[adj[node][i]] != 1)
      {
          cycledfs(adj[node][i]);
      }
  }
  visited[node] = 1;
}
void dfs(int node)
{
    if(!vis[node])
    {
        vis[node] = 1;
        for(int i = 0; i < adj[node].size(); i++)
        {
            if(!vis[adj[node][i]])
                dfs(adj[node][i]);

        }
        mystack.push((node +'A'));
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin>>tc;
    for(int z = 1; z <= tc; z++)
    {
        cin>>n>>m;
        set <char> t; //stores all the unique nodes 
        for(int i = 0; i <n; i++)
        {
            cin>>s[i];
            for(int j = 0; s[i][j]!='\0';j++)
                t.insert(s[i][j]);

            if(i)  // if I Am not in the topmost row
            {
                for(int j = 0; s[i][j]!='\0';j++) 
                {
                    auto it = find(adj[s[i][j]-'A'].begin(), adj[s[i][j]-'A'].end(), (s[i-1][j]-'A')); 
                    if(((s[i][j]-'A') != (s[i-1][j]-'A')) &&(it==adj[s[i][j]-'A'].end())) //to check if the brick above me is different from me. Also making sure no duplicates in the graph.
                        adj[s[i][j]-'A'].push_back((s[i-1][j]-'A'));
                }

            }
        }
        //INITIALIZING 
        flag = 0;
        memset(visited, 0, sizeof(visited));
        memset(vis, 0, sizeof(vis));
        // checking if there is a cycle
        for(char i: t) //for each unique node
        {
          //cout<<(i-'A')<<"\n";
          if(visited[i-'A'] == 0)
               cycledfs(i-'A');
          if(flag)
            break;
        }
        if(flag)
            cout<<"Case #"<<z<<": "<<"-1"<<"\n";
        else
        {
            // there is no cycle, time for the topological sorting
            string result ="";
            for(char x: t)
                dfs(x-'A');
            while(!mystack.empty())
            {
                char ans = mystack.top();
                result.push_back(ans);
                mystack.pop();
            }
            cout<<"Case #"<<z<<": "<<result<<"\n";

        }
         for(int i = 0; i < 26; i++) //Because I declared it globally I have to clear it.
                adj[i].clear();
    }

}

