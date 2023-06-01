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
