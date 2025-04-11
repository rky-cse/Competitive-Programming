#include<bits/stdc++.h>
using namespace std;



int main(){

    int n;cin>>n;
    vector<string> s(n);
    for(int i=0;i<n;i++){
        cin>>s[i];
    }
    queue<pair<int,int>> q;
    int m=s[0].size();  
    vector<vector<int>>dist(n,vector<int>(m,1e9));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j]=='*'){
                dist[i][j]=0;
                q.push({i,j});
            }
        }
    }
    vector<vector<int>> vis(n,vector<int>(m,0));
    vector<int>dx={1,0,-1,0};
    vector<int>dy={0,1,0,-1};

    while(!q.empty()){
        auto [x,y]=q.front();q.pop();
        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];
            if(nx>=0 && nx<n && ny>=0 && ny<m && s[nx][ny]!='*' && dist[nx][ny]>dist[x][y]+1){
                dist[nx][ny]=dist[x][y]+1;
                q.push({nx,ny});
            }
        }
       
    }

    int sti,stj,eni,enj;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i][j]=='S'){
                sti=i;stj=j;
            }
            if(s[i][j]=='E'){
                eni=i;enj=j;
            }
        }
    }

    int low=0,high=(n+m);

    while(low<=high){
        int mid=(low+high)/2;
        bool ok=false;
        while(!q.empty()) q.pop();
        q.push({sti,stj});
        vis.assign(n,vector<int>(m,0));
        vis[sti][stj]=1;

        while(!q.empty()){
            auto [x,y]=q.front();q.pop();
            
            
            for(int i=0;i<4;i++){
                int nx=x+dx[i];
                int ny=y+dy[i];
                if(nx>=0 && nx<n && ny>=0 && ny<m && s[nx][ny]!='*' && dist[nx][ny]>=mid && vis[nx][ny]==0){
                    vis[nx][ny]=1;
                    if(nx==eni && ny==enj){
                        ok=true;
                        break;
                    }
                    q.push({nx,ny});
                }
            }
            if(ok) break;
        }
        if(ok){
            low=mid+1;
        }else{
            high=mid-1;
        }

        
    }
    cout<<high<<endl;





    return 0;
}