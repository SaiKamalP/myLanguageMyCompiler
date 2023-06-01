#include <bits/stdc++.h>
 
using namespace std;
 
int main(int argCnt,char **args) {    
    ifstream fin("example.txt");
    ofstream fout("out.txt");
    fout<<"#include <bits/stdc++.h>\n\nusing namespace std;\n\n";
    string s;
    string pre="";
    int mode=0;
    int indtl=0;
    string indts[30];
    int fw=true;
    indts[0]="";
    for(int i=1;i<30;i++){
        indts[i]=indts[i-1]+"\t";
    }
    while(fin>>s){
        s=pre+s;
        if(s=="take"){
            fout<<"cin<<";
            mode=1;
            continue;
        }
        else if(s=="long"){
            fout<<"long long ";
            continue;
        }
        if(mode==0){
            if(fw){
                fw=false;
            }
            else{
                fout<<" ";
            }
            for(int i=0;i<s.length();i++){
                if(s[i]!='{' && s[i]!='}' && s[i]!=';'){
                    fout<<s[i];
                }
                else if(s[i]=='{'){
                    fout<<s[i];
                    indtl++;
                    fout<<"\n"<<indts[indtl];
                    fw=true;
                }
                else if(s[i]=='}'){
                    fout<<s[i];
                    indtl--;
                    fout<<"\n"<<indts[indtl];
                    fw=true;
                }
                else if(s[i]==';'){
                    fout<<s[i];
                    fout<<"\n"<<indts[indtl];
                    fw=true;
                }
            }

        }
        else if(mode==1){
            for(int i=0;i<s.length();i++){
                if(s[i]!=',' && s[i]!=';'){
                    fout<<s[i];
                }
                else if(s[i]==','){
                    fout<<"<<";
                }
                else{
                    fout<<";"<<endl;
                    fout<<indts[indtl];
                    fw=true;
                    mode=0;
                }
            }
        }
    }

    fin.close();
    fout.close();
    return 0;
}