#include <bits/stdc++.h>
 
using namespace std;
enum CharTypes{
    Unknown,
    TextOrNumber,
    SpaceOrEndline,
    SpecialChar
};
unordered_map<char,CharTypes> CHAR_TYPE;
bool isCharEmpty(char c){
    return !(CHAR_TYPE[c]==TextOrNumber || CHAR_TYPE[c]==SpecialChar);
}
int isStringEmpty(string &s){
    for(auto i :s){
        if(!isCharEmpty(i)){
            return 0;
        }
    }
    return 1;
}
vector<string> &tokenize(string code){
    vector<string> &tokens=*(new vector<string>());
    string parser="";
    int quotesMode=0;
    /* quotesMode 0 for not under quotes
    quotesMode 1 for under '
    quoteMode 2 for under " */
    int skipCharMode=0;
    //will be used when '\' is used.
    for(char c:code){
        if(skipCharMode){
            parser+=c;
            skipCharMode=0;
            continue;
        }
        if(quotesMode && c=='\\'){
            skipCharMode=1;
            continue;
        }
        if(isCharEmpty(c) && !quotesMode){
            if(!isStringEmpty(parser)){
                tokens.push_back(parser);
            }
            parser="";
        }
        else if(quotesMode){
            if(quotesMode==1 && c=='\''){
                parser+='\'';
                tokens.push_back(parser);
                parser="";
                quotesMode=0;
            }
            else if(quotesMode==2 && c=='"'){
                parser+='"';
                tokens.push_back(parser);
                parser="";
                quotesMode=0;
            }
            else{
                parser+=c;
            }
        }
        else{
            if(c=='\'' || c=='"'){
                if(!isStringEmpty(parser)){
                    tokens.push_back(parser);
                }
                parser=""; 
                parser+=c;
                quotesMode=c=='\''?1:2;
            }
            else if(CHAR_TYPE[c]==SpecialChar){
                 if(!isStringEmpty(parser)){
                    tokens.push_back(parser);
                }
                parser=""; 
                parser+=c;
                tokens.push_back(parser);
                parser="";
            }
            else{
                parser+=c;
            }
        }
        
    }
    if(!isStringEmpty(parser)){
        tokens.push_back(parser);
    }
    return tokens;
}

void initCharTypes(){
    for(char c='a';c<='z';c++){
        CHAR_TYPE[c]=TextOrNumber;
    }
    for(char c='A';c<='Z';c++){
        CHAR_TYPE[c]=TextOrNumber;
    }
    for(char c='0';c<='9';c++){
        CHAR_TYPE[c]=TextOrNumber;
    }
    //additionally '_' is assumed to be textOrNumber
    CHAR_TYPE['_']=TextOrNumber;

    char otherChars[]={'+','-','*','/','\\','%','!','<','>',',','.','\'',
                        '"',';',':','[',']','{','}','(',')','^','&','|','?'};
    for(char c:otherChars){
        CHAR_TYPE[c]=SpecialChar;
    }
    CHAR_TYPE[' ']=SpaceOrEndline;
    CHAR_TYPE['\n']=SpaceOrEndline;
    CHAR_TYPE['\t']=SpaceOrEndline;
    CHAR_TYPE['\r']=SpaceOrEndline;
}
void init(){
    initCharTypes();

}

int main(int argCnt,char **args) {
    init();
    string examplecode="int  main(\"appke \nwo\nwo\\\' \"){}";
    vector<string> tokens=tokenize(examplecode);
    for(auto i : tokens){
        cout<<i<<endl;
    }
    return 0;
}