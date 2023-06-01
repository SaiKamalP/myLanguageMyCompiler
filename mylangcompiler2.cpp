#include <bits/stdc++.h>
 
using namespace std;
unordered_map<char,int> chartype;
unordered_map<string,string> wordRephraser;
int isEmpty(string &s){
    for(char x:s){
        if(chartype.count(x) && chartype[x]!=0){
            return false;
        }
    }
    return true;
}
void init(){
    wordRephraser["long"]="long long";
    wordRephraser["take"]="cin>>";
    wordRephraser["say"]="cout<<";
    wordRephraser["loop"]="for";
}
int main(int argCnt,char **args) {
    vector<string> tabs(256);
    tabs[0]="";
    for(int i=1;i<tabs.size();i++){
        tabs[i]=tabs[i-1];
        tabs[i]+="\t";
    }
    init();
    for(char c='a';c<='z';c++){
        chartype[c]=1;
    }    
    for(char c='A';c<='Z';c++){
        chartype[c]=1;
    }    
    for(char c='0';c<='9';c++){
        chartype[c]=1;
    }
    chartype['_']=1;
    char otherchars[]={'/', '\\', '"', '\'', ':', ';', '.', ',', '!', '+', '-', '*', '%',
                         '<', '>', '(', ')', '{', '}', '[', ']', '|', '&', '^', '=', '?'};
    for(char oc:otherchars){
        chartype[oc]=20;
    }

    ifstream fin("example.txt");
    ofstream fout("out.cpp");
    fout<<"#include <bits/stdc++.h>\n\nusing namespace std;\n\n";
    stringstream buffer;
    buffer<<fin.rdbuf();
    string code=buffer.str();

    vector<string> words;
    string parser="";
    int countMode=0;
    for(char c:code){
        if(chartype[c]==1 || countMode==1 || countMode==2){
            parser+=c;
            if((countMode==1 && c=='\'') || (countMode==2 && c=='"')){
                words.push_back(parser);
                parser="";
                countMode=0;
            }
        }
        else{
            if(!isEmpty(parser)){
                words.push_back(parser);
            }
            parser="";
            parser+=c;
            if(c=='\'' || c=='"'){
                if(c=='\''){
                    countMode=1;
                }
                else{
                    countMode=2;
                }
            }
            else{
                if(!isEmpty(parser)){
                    words.push_back(parser);
                }
                parser="";
            }
            
        }
    }
    if(!isEmpty(parser)){
        words.push_back(parser);
    }
    string final_content="";
    int indl=0;
    int fw=1;
    int writemode=0;
    int loopargc=0;
    string loopvar="";
    int bc=0;
    for(auto i:words){
        if(fw && i!="}"){

            final_content+=tabs[indl];
            fw=0;
        }
        if(i=="long") i="long long";
        if(i=="space") i="\" \"";
        if(i=="nline") i="endl";
        if(i!="}"){
            if(writemode==0){
                if(i=="take"){
                    final_content+="cin>>";
                    writemode=1;
                }
                else if(i=="say"){
                    final_content+="cout<<";
                    writemode=2;
                }
                else if(i=="loop"){
                    final_content+="for";
                    writemode=3;
                    loopargc=-1;
                    bc=0;
                }
                else{
                    final_content+=i;
                }
            }
            else if(writemode==1){
                if(i==","){
                    final_content+=">>";
                }
                else if(i==";"){
                    final_content+=";";
                    writemode=0;
                }
                else{
                    final_content+=i;
                }
            }
            else if(writemode==2){
                if(i==","){
                    final_content+="<<";
                }
                else if(i==";"){
                    final_content+=";";
                    writemode=0;
                }
                else{
                    final_content+=i;
                }
            }
            else if(writemode==3){
                if(i=="("){
                    bc+=1;
                }
                else if(i==")"){
                    bc-=1;
                    if(bc<0){
                        throw runtime_error("() unmatched");
                    }
                }
                if(loopargc==-1){
                    final_content+=i;
                    loopargc=0;
                }
                else if(i==","){
                    loopargc=loopargc%2==0?loopargc+2:loopargc+1;
                }
                else if(loopargc==0){
                    final_content+="long long ";
                    final_content+=i;
                    loopvar=i;
                }
                else if(loopargc==2){
                    final_content+="= ";
                    final_content+=i;
                    loopargc=3;
                }
                else if(loopargc==3){
                    final_content+=i;
                }
                else if(loopargc==4){
                    final_content+="; ";
                    final_content+=loopvar;
                    final_content+=" < ";
                    final_content+=i;
                    loopargc=5;
                }
                else if(loopargc==5){
                    if(bc==0){
                        final_content+="; "+loopvar+"++ ";
                        writemode=0;
                    }
                    final_content+=i;
                }
                
            }
        }
        if(i==";"){
            final_content+="\n";
            fw=1;
        }
        else if(i=="{"){
            final_content+="\n";
            indl++;
            fw=1;

        }
        else if(i=="}"){
            indl--;
            if(indl<0){
                throw runtime_error("flour brackets not closed propoerly");
            }
            final_content+=tabs[indl];
            final_content+="}\n";
            fw=1;

        }
        else{
            if(i!="=" && i!=";" && i!="+" && i!="-" && i!="*" && i!="/" && i!="%" && i!="(" && i!=")" && i!="{" && i!="}" && i!="[" && i!="]" && i!="^" && i!="&" && i!="|" && i!="!"){
                final_content+=" ";
            }
        }
    }
    fout<<final_content;
    fin.close();
    fout.close();
    return 0;
}