#include <bits/stdc++.h>
#include "Scan.h"
#include "Token.h"
using namespace std;

/*
This program implements a scanner (lexical analyzer).
It scans the code in the newly defined language(as per the question)
and generates tokens as output for the sample code in file "sample.n"
This uses 2 classes namely, Token and Scan. The implementation  of these Scan
be found in the respective header files. The sample code is the same as the one
given in the problem. The result was verified by visual inspection. Note that Scan
class also has a lookup table as described in one of the parts of the question.
*/
int main()
{
    
    ifstream fout;
    fout.open("sample.n");
    
    Scan s(fout);
    s.tokenize();
    cout<<s;
    
    ofstream outputfile;
    outputfile.open("output.txt");
    outputfile<<s;
    
    outputfile.close();
    fout.close();
    
    
    return 0;
}