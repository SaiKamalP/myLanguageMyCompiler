#include <bits/stdc++.h>
 
using namespace std;
//block class
class Block{
    public:
    vector<Block> subBlocks;
    vector<string> snippetTokens;
    char blockStartChar='b';
    char blockEndChar='d';
    Block(){
    }
    Block(vector<string> &sTokens){
        snippetTokens=sTokens;
    }
};

void generateNestedSubBlocks(Block &block){
    queue<string> tokensQueue;
    stack<char> bracketsSatck;
    auto &blocktokens=block.snippetTokens;
    int i=0;
    Block *createdSubBlock;
    //createdSubBlock=new Block();
    while(i<blocktokens.size()){
        if(bracketsSatck.size()>0){
            if(blocktokens[i]=="{" || blocktokens[i]=="("){
                tokensQueue.push(blocktokens[i]);
                bracketsSatck.push(blocktokens[i][0]);
            }
            else if(blocktokens[i]=="}" || blocktokens[i]==")"){
                if((blocktokens[i]==")" && bracketsSatck.top()=='(' ) || (blocktokens[i]=="}" && bracketsSatck.top()=='{' )){
                    bracketsSatck.pop();
                }
                else{
                    throw std::runtime_error("brackets unmatched");
                }
                if(bracketsSatck.size()==0){
                    while(tokensQueue.size()>0){
                        createdSubBlock->snippetTokens.push_back(tokensQueue.front());
                        tokensQueue.pop();
                    }
                    createdSubBlock->blockEndChar=blocktokens[i][0];
                    block.subBlocks.push_back(*createdSubBlock);
                }
                else{
                    tokensQueue.push(blocktokens[i]);
                }
            }
            else{
                tokensQueue.push(blocktokens[i]);
            }
        }
        else if(blocktokens[i]=="{" || blocktokens[i]=="("){
            if(tokensQueue.size()){
                createdSubBlock=new Block();
                while(!tokensQueue.empty()){
                    createdSubBlock->snippetTokens.push_back(tokensQueue.front());
                    tokensQueue.pop();
                }
                block.subBlocks.push_back(*createdSubBlock);
            }
            createdSubBlock=new Block();
            createdSubBlock->blockStartChar=blocktokens[i][0];
            bracketsSatck.push(blocktokens[i][0]);
        }
        else if(blocktokens[i]!="," && blocktokens[i]!=";" && blocktokens[i]!=":"){
            tokensQueue.push(blocktokens[i]);
        }
        else{
            createdSubBlock=new Block();
            createdSubBlock->blockEndChar=blocktokens[i][0];
            while(!tokensQueue.empty()){
                createdSubBlock->snippetTokens.push_back(tokensQueue.front());
                tokensQueue.pop();
            }
            createdSubBlock->blockStartChar='s';
            block.subBlocks.push_back(*createdSubBlock);
        }
        i++;
    }
    if(!tokensQueue.empty()){
        createdSubBlock=new Block();
        while(!tokensQueue.empty()){
            createdSubBlock->snippetTokens.push_back(tokensQueue.front());
            tokensQueue.pop();
        }
        createdSubBlock->blockStartChar='s';
        block.subBlocks.push_back(*createdSubBlock);   
    }
    for(Block &subBlock:block.subBlocks){
        if(subBlock.blockStartChar!='s'){
            cout<<"yes"<<endl;
            generateNestedSubBlocks(subBlock);
        }
    }
}
//block class end


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
                        '"',';',':','[',']','{','}','(',')','^','&','|','?','='};
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
void printBlock(Block b,int level=0){
    if(b.blockStartChar=='s'){
        for(int i=0;i<level;i++) cout<<"    ";
        for (auto i:b.snippetTokens){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    else{
        for(Block sb:b.subBlocks){
            for(int i=0;i<level;i++) cout<<"    ";
            cout<<sb.blockStartChar<<endl;
            printBlock(sb,level+1);
            for(int i=0;i<level;i++) cout<<"    ";
            cout<<sb.blockEndChar<<endl;
        }
    }
}
int main(int argCnt,char **args) {
    init();
    string examplecode="{}(code,apple;apple";
    vector<string> tokens=tokenize(examplecode);
    Block codeBlocks(tokens);
    generateNestedSubBlocks(codeBlocks);
    printBlock(codeBlocks);
    return 0;
}