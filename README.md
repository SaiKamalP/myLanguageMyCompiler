# myLanguageMyCompiler
(UNDER DEVELOPMENT)
An attempt to make my own language that works for at least Competitive coding. Plan is to make human readable CP code, that would then compile to standard c++.

clone the repository

write your code in same directory and name the file "example.txt"
and run mylangcompiler to get your output into out.cpp

writing code in this language:
  some stuff is automatically included.
  
    #include<bits/stdc++.h>
    
    using namespace std;
    
  you have to write your code without including them.
  
  To start with its the same as C++, but small changes are made
  
    cin and cout is replaced with take and say
    you can just replace intermediate << and >> of cin and cout with just coma ','
    to say " ", you can use word space or " "
    to say endl, you can use word "nline" or "endl"
    to say for(long long i=a;i<b;i++), you can use loop(i,a,b)
    to say long long, you can just say long once

Example code written in this language
    
    void dfs(long child,long parent,vector<long> *adj){
    visit(child);
    loop(i,0,adj[child].size()){
        if(adj[child][i]!=parent){
            dfs(adj[child][i],parent,adj);
        }
    }
    }

    int main(){
        int t;
        take t;
        loop(r,0,t){
            int u,v;
            take u,v;
            otherCode();
        }
        int ans=10;
        say ans,space,ans*ans,nline;
    }
    
Output of the example code in c++
    
    #include <bits/stdc++.h>

    using namespace std;

    void dfs (long long child , long long parent , vector < long long > *adj ){
      visit (child );
      for (long long i  = 0  ; i < adj [child ]. size (); i++ ){
        if (adj [child ][i ]!=parent ){
          dfs (adj [child ][i ], parent , adj );
        }
      }
    }
    int main (){
      int t ;
      cin>> t ;
      for (long long r  = 0  ; r < t ; r++ ){
        int u , v ;
        cin>> u >> v ;
        otherCode ();
      }
      int ans =10 ;
      cout<< ans << " " << ans *ans << endl ;
    }
    


