#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include "Token.h"

using namespace std;

class Scan{
    vector<string> lines;
    unordered_set<string> keywords;
    vector<Token> tokens;
    unordered_map<int,string> lookup;
    unordered_map<string,Token> identifiers;
    
    public:
    Scan();
    Scan(ifstream&);
    string strip(string str);
    void tokenize();
    string findType(string);
    
    friend ostream& operator<< (ostream& out, const Scan& scan);
};

Scan::Scan(){
}

string Scan::strip(string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str.erase(remove(str.begin(), str.end(), '\n'), str.end());
	str.erase(remove(str.begin(), str.end(), '\t'), str.end());
	str.erase(remove(str.begin(), str.end(), '\r'), str.end());
	str.erase(remove(str.begin(), str.end(), '\v'), str.end());
	str.erase(remove(str.begin(), str.end(), '\f'), str.end());
	return str;
}

ostream& operator<<(ostream& out, const Scan& scan){
    // for(int i=0;i<scan.lines.size();i++){
    //     out<<scan.lines[i]<<endl;
    // }
    
    out<<endl<<"<TYPE, VALUE, TOKEN_ID>"<<endl<<endl;
    for(Token x:scan.tokens){
        out<<x<<endl;
    }
    return out;
}

Scan::Scan(ifstream& fout){
    string str;
    while(getline(fout,str)){
        string line=strip(str);
        if(line.size()==0)continue;
        string compressed="";
        bool flag=false;
        bool prev=false;
        for(int i=0;i<str.size();i++){
            char a=str[i];
            if(flag==false && a=='-' && i+1<str.size() && str[i+1]=='-'){
                break;
            }
            if((a==' '||a=='\n'||a=='\t')&&flag==false){
                if(!prev){
                    prev=true;
                    if(compressed.size()>0){
                        lines.push_back(compressed);
                        compressed="";
                    }
                }
                continue;
            }else if(a=='"'){
                compressed+=a;
                flag=!flag;
                prev=false;
            }else{
                compressed+=a;
                prev=false;
            }
        }
        if(compressed.size()>0)
            lines.push_back(compressed);
    }
    vector<string> temp({"PROGRAM","BEGIN","END","FUNCTION",
                        "READ","WRITE","IF","ELSIF","ENDIF",
                        "DO","WHILE","CONTINUE","BREAK","RETURN",
                        "INT","VOID","STRING","FLOAT","TRUE","FALSE"});
    keywords=unordered_set<string>(temp.begin(),temp.end());
    tokens=vector<Token>();
}

string Scan::findType(string str){
    if(isalpha(str[0])){
        try{
            if(str.size()>31){
                throw 10;
            }
        }catch(int x){
            cout<<"Warning: Invalid Identifier! Identifier must start with a letter followed by numbers/letters less than 30 in number."<<endl;
            assert(str.size()<31);
        }
        return "IDENTIFIER";
    }else if(isdigit(str[0])){
        string res="INTLITERAL";
        for(int i=0;i<str.size();i++){
            assert(isdigit(str[i])||str[i]=='.');
            if(str[i]=='.'){
                res="FLOATLITERAL";
            }
        }
        return res;
    }
    return "";
}

void Scan::tokenize(){
    for(string &str:lines){
        string curr="";
        for(int i=0;i<str.size();i++){
            char a=str[i];
            if(a=='"'){
                i++;
                while(i<str.size() && str[i]!='"'){
                    curr+=str[i];
                    i++;
                }
                try{
                    if(curr.size()>80){
                        throw 10;
                    }
                    
                }catch(int x){
                    cout<<"Warning: String Literal with size greater than 80 characters."<<endl;
                }
                curr+='"';
                curr='"'+curr;
                Token temp("STRINGLITERAL",curr);
                tokens.push_back(temp);
                lookup.insert({temp.getId(),temp.getValue()});
                curr="";
                continue;
            }
            
            if(isalnum(a)||a=='.'){
                curr+=a;
            }else{
                Token temp;
                if(curr.size()>0){
                    string type=findType(curr);
                    if(type=="IDENTIFIER"){
                        if(identifiers.find(curr)==identifiers.end()){
                            temp=Token(type,curr);
                            tokens.push_back(temp);
                            lookup.insert({temp.getId(),temp.getValue()});
                            identifiers.insert({curr,temp});
                        }else{
                            tokens.push_back(identifiers[curr]);
                        }
                    }else{
                        temp=Token(type,curr);
                        tokens.push_back(temp);
                        lookup.insert({temp.getId(),temp.getValue()});
                    }
                }
                curr="";
                
                if(a=='<'||a=='>'||a=='!'||a==':'){
                    curr+=a;
                    if(i+1<str.size() && str[i+1]=='='){
                        i++;
                        curr+=str[i];
                    }
                    temp=Token("OPERATOR",curr);
                    tokens.push_back(temp);
                    lookup.insert({temp.getId(),temp.getValue()});
                }else if(a==';'||a==','||a=='='||a=='*'||a=='('||a==')'||a=='+'||a=='-'||a=='/'){
                    curr+=a;
                    temp=Token("OPERATOR",curr);
                    tokens.push_back(temp);
                    lookup.insert({temp.getId(),temp.getValue()});
                }
                curr="";
            }
            
            if(keywords.find(curr)!=keywords.end()){
                if(curr=="END" && i+2<str.size() && str[i+1]=='I'&&str[i+2]=='F'){
                    curr+="IF";
                    i+=2;
                }
                Token temp("KEYWORD",curr);
                tokens.push_back(temp);
                lookup.insert({temp.getId(),temp.getValue()});
                curr="";
            }
        }
        if(curr.size()>0){
            string type=findType(curr);
            Token temp;
            if(type=="IDENTIFIER"){
                if(identifiers.find(curr)==identifiers.end()){
                    temp=Token(type,curr);
                    tokens.push_back(temp);
                    lookup.insert({temp.getId(),temp.getValue()});
                    identifiers.insert({curr,temp});
                }else{
                    tokens.push_back(identifiers[curr]);
                }
            }else{
                temp=Token(type,curr);
                tokens.push_back(temp);
                lookup.insert({temp.getId(),temp.getValue()});
            }
        }
    }
}



