#pragma once
#include<iostream>
#include<string>

using namespace std;

class Token{
    string type;
    string value;
    int id;
    public:
    Token();
    Token(string, string);
    string getType();
    string getValue();
    int getId();
    friend ostream& operator<< (ostream&,const Token&);
};


Token::Token(){}

Token::Token(string type,string value):type(type),value(value){
    static int count=0;
    id=count++;
}

string Token::getType(){return type;}
string Token::getValue(){return value;}
int Token::getId(){return id;}

ostream& operator<< (ostream& out, const Token& token){
    out<<"<"<<token.type<<", "<<token.value<<", "<<token.id<<"> ";
    return out;
}

