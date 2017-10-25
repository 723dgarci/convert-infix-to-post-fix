#include <iostream>
#include "Stack.h"
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
using namespace cop4530;
using namespace std;

Stack<string> in2post(const string &, bool&);                  //converts infix string equation into a post fix stack (error handleing is taken care of here)
int precede(char p);                                    //returns value of precedence for char
bool isTor(char o);                                     //returns true if char is = {+,-,*,/,(,)}
bool asmd(const string &);                              //returns true if string is = {+,-,*,/}

void ansr(Stack<string>&);                              //evaluates post fix string
int opChk(const vector<string> & v);                    //checks if there is an operator next another operator or an operand next another operand
vector<string> subS(string s, const string& del = " ");//returns vector of sub-strings of string with del as the deliminators

int main () {
    string str;                             // holds incoming string
    Stack<string> post;                     //holds post fix version of equation
    bool eval;                              //used to check if equation is evaluable

    do{
        eval = true;
        cout <<"Enter infix expression (\"exit\" to quit):";
        getline(cin,str, '\n');
        if(str != "exit") {
            post = in2post(str, eval);
            if( post.top().find("Error") != 0) {            //if it is not an error                                         //if error is not found
                cout << "Postfix expression:" << post << '\n';
                if (eval) {
                    cout << "Postfix evaluation: " << post << " = " ;
                    ansr(post);
                    cout << '\n';
                } else {
                    cout << "Postfix evaluation: " << post << " = " << post << '\n';
                }
            }
            else{
                cout << post<<'\n';
            }
        }
    }while(str != "exit");

    return 0;
}/////////end of main()



bool asmd(const string &s){
    return s == "+"|| s == "-"||s == "/"|| s == "*";
 }

vector<string> subS(string s, const string& del){
    vector<string> sub;
    string tok;
    unsigned int pos;
    while(!s.empty()){
        pos = s.find(del);
        tok = s.substr(0,pos);
        if(tok[tok.size()-1]=='\r')                     //takes care of strings with carriage return
            tok =tok.substr(0,tok.size()-1);
        s.erase(0,pos + del.length());
        sub.push_back(tok);
    }
    return sub;
}

int opChk(const vector<string> & v){
    Stack<string> chk;                      //good case - only contains operators and has size == 1 in the end
    Stack<string> o;
    for(auto &x: v){
        //cout << "in opChk() x : "<< x<<'\n';
        if(!chk.empty()) {                                          //if chk is not on the first element on the stack
            if (asmd(x) && (asmd(chk.top()))) {                     //if operator and operator are nex to each other
                return 1;
            } else if (!isTor(x[0]) && !isTor(chk.top()[0])) {      //if operand and operand are next to each other
                return 2;
            }else if( asmd(x) && chk.top() == "("){                 // if there is '(' <operand>
                return 1;
            }else if(x == ")" && asmd(chk.top())){                  //if there is <operand> ')'
                return 1;
            }else if( x == "(" && !isTor(chk.top()[0])){            //if there is <operator> '('
                return 2;
            }else if( !isTor(x[0]) && chk.top() ==")"){             //if there is ')' <operator>
                return 2;
            }
        }
        chk.push(x);
        if(x == "(" ) {                     // chk '(' and ')' are proper
            //cout << "pushing ( onto o\n";
            o.push("(");
        } else if(x == ")"&& !o.empty()){
            o.pop();
        }else if ( x == ")"){
            o.push(")");
        }
        //cout << "o : "<< o<<'\n';
        //cout << "chk: "<< chk<<'\n';
    }
    if(!o.empty()) {
        return 3;
    }
    return 4;


}

Stack<string> in2post(const string &v, bool& e) {
    Stack<string> post;
    Stack<string> stk;
    /*
    if(!parChk(v)){                                                         //exception handling : { ) 2 + 1 ( }
        post.push("Error: Infix expression: "+ v +" has mismatched parens!");
        return post;
    }
     */
    vector<string> sub= subS(v);                                        // get vecotr of substrings
    if( asmd(sub[0]) || asmd(sub[sub.size()-1])){                       //takes care of exceptions like: + a + b and a + b +
        post.push("Error: Missing operand in the expression");
        return post;
    }

    int temp = opChk(sub);                                            //call checking funciton
    if(temp == 1){
        post.push("Error: Missing operand in the expression");
        return post;
    }else if(temp == 2){
        post.push("Error: Missing operator in the expression");
        return post;
    }else if(temp == 3){
        post.push("Error: Infix expression: "+ v +" has mismatched parens!");
        return post;
    }


    for(auto &tok: sub) {                            //splits string into substrings until size == 2 bc a string must have the last the null terminator
        if (!isTor(tok[0])) {                        // if the first thing in the vector is and operator or parenthesis
            if(isalpha(tok[0])) {                    //if any of the first chars of the operands is an alpha then the equation is not evaluable
                e = false;
            }
            post.push(tok);
        } else if (tok == "+" || tok == "-" || tok == "*" || tok == "/"|| tok == "(") {                                         //if the string is a an operator or paranthesis
            if (!stk.empty()) {                                                                                                 //if stk is not empty
                while (!stk.empty() && stk.top()[0] != '(' && precede(stk.top()[0]) >= precede(tok[0])) {                       //if the precidence of the symbole on the stack is greater than the new one the print it (continue)
                    post.push(stk.top());
                    stk.pop();
                }
            }
            stk.push(tok);              //push operator

        } else if (tok[0] == ')') {
            while (stk.top()[0] != '(') {
                    post.push(stk.top());
                    stk.pop();
            }
        }
    } /////////////////end of while

    if(!stk.empty()) {
        while (!stk.empty() ) {
            if(stk.top()[0] != '(')                             //prevent parentheis from being in stack
                post.push(stk.top());
            stk.pop();
        }
    }
    return post;
} ////////////end of in2post()

void ansr(Stack<string>& stk){
    stk.rev();                             // reverse order os stack for the sake of the equation
    Stack<double> junk;                    // temp stack
    if(isdigit(stk.top()[0])) {
        junk.push(stod(stk.top()));             //push  the first 2 elements of argument to junk
    }else{
        cout << "0\n";
        return;
    }
    stk.pop();
    if(isdigit(stk.top()[0])){
        junk.push(stod(stk.top()));
    }else{
        cout << "0\n";
        return;
    }
    stk.pop();
    while(!stk.empty()){                    //go through each element of argument
        if(!isTor(stk.top()[0])){           //if operand
            junk.push(stod(stk.top()));     //push it to the temp stack (convert string to double)
        }
        else{                               //else evaluate last 2 operands on stack
            double r =junk.top();
            junk.pop();
            double l =junk.top();
            junk.pop();
            if(stk.top() == "+") {
                junk.push(l + r);           //push result to top of junk stack
            }
            else if(stk.top() == "-") {
                junk.push(l - r);
            }
            else if(stk.top() == "*") {
                junk.push(l * r);
            }
            else if (stk.top() == "/") {
                junk.push(l / r);
            }
        }
        stk.pop();      //used to increment to next element in stack

    }

    cout << junk.top()<< '\n';
}   ////// end of ansr()

bool isTor(char o){
    return o == '-' || o == '+' || o == '/' || o == '*' || o == '(' ||o == ')';

}

int precede(char p){
    if(p == '(' ||p == ')' )
        return 3;
    else if(p == '*' ||p == '/' )
        return 2;
    else if(p == '+' ||p == '-' )
        return 1;
    else                //error case
        return 0;
}