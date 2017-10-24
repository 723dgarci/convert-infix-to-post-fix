#include <iostream>
#include "Stack.h"
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
using namespace cop4530;
using namespace std;

Stack<string> in2post(string , bool&);
int precede(char p);
bool isTor(char o);
bool parChk(string& s);
void ansr(Stack<string>&);
vector<string> subS(string &s, const string& del = " ");
int main () {
    std::cout << "BOP\n" << std::endl;
    /*
    Stack<int> intstk;

    cout << "inserting 10 elements" << endl;
    for (unsigned int i = 0; i < 10; ++i)
        intstk.push(i);

    cout << "Size: " << intstk.size() << endl;

    cout << "elements: " << intstk << endl;

    cout << "emptying the stack" << endl;
    while (!intstk.empty()) {
        cout << intstk.top() << " ";
        intstk.pop();
    }
    cout << endl;

    cout << "Size: " << intstk.size() << endl;

    cout << "inserting 10 elements" << endl;

    for (unsigned int i = 0; i < 10; ++i)
        intstk.push(i);

    Stack<int> intstk1(intstk);
    Stack<int> intstk2;
    intstk2 = intstk;

    //     cout << intstk << endl;
         cout << intstk1 << endl;
         cout << intstk2 << endl;

    if (intstk1 == intstk2)
        cout << "Equal stacks" << endl;
    else
        cout << "ERROR: stacks are not equal" << endl;

    intstk1.pop();
    cout << intstk1 << endl;
    cout << intstk2 << endl;

    if (intstk1 == intstk2)
        cout << "Error: equal stacks" << endl;
    else
        cout << "Stacks are not equal" << endl;

    if (intstk1 <= intstk2)
        cout << "intstk1 is less than or equal to intstk2" << endl;
    else
        cout << "ERROR: wrong comparision" << endl;
    */
    string str;
    Stack<string> post;
    bool eval = true;


    do{
        cout <<"Enter infix expression (\"exit\" to quit):";
        getline(cin,str, '\n');

        if(str != "exit") {


            post = in2post(str, eval);

            //cout << post.top().find("Error")<<endl;
            if( post.top().find("Error") != 0) {                                            //if error is not found
                cout << "Postfix expression:" << post << "eval: "<< eval<< '\n';
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



    std::cout << "\n\nEOP" << std::endl;
    return 0;
}/////////end of main()

bool parChk(string &s){
    Stack<char> o;
    for(unsigned int i =0;i < s.size();i++){
        if( s[i] == '(') {
            o.push('(');
        } else if(s[i]== ')'&& !o.empty()) {
            o.pop();
        }
        else if ( s[i] == ')'){
            o.push(')');
        }
    }
    cout << "\no in the end:"<< o<<'\n';
    return o.empty();

}

vector<string> subS(string &s, const string& del){
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

Stack<string> in2post(string v, bool& e) {
    //cout << "befor declarations\n";
    Stack<string> post;
    Stack<string> stk;
    //bool tor = false;
    //cout << "after declarations\n";
    //cout << "v : "<< v << ' ' << '\n';
    if(!parChk(v)){
        post.push("Error: Infix expression: "+ v +" has mismatched parens!");
        cout << "passing false0\n";
        e = false;
        return post;
    }
    if( isTor(v[0]) && v[0] != '('){
        post.push("Error: Missing operands in the expression");
        cout << "passing false1\n";
        e = false;
        return post;
    }

    vector<string> sub= subS(v);                     // get vecotr of substrings
    for(auto &tok: sub) {                            //splits string into substrings until size == 2 bc a string must have the last the null terminator
        //cout <<"GOING THROUGH WHILE\n";
        //cout <<"tok :"<< tok << endl;
        //cout << "v after cut :"<< v;
        //cout << "\nv.size:"<<v.size() <<'\n';
        if (!isTor(tok[0])) {                 // if the first thing in the vector is and operator or parenthesis
            if(isalpha(tok[0])) {                  //if any of the first chars of the operands is an alpha then the equation is not evaluable
                cout << "passing false2\n";
                e = false;
            }
            //Error: Missing operators in the expression

            //cout << "print operand" << endl;
            //cout<<"STORE :" << tok << endl;
            post.push(tok);
            //cout <<"test2\n";
        } else if (tok == "+" || tok == "-" || tok == "*" || tok == "/"|| tok == "(") {                                         //if the string is a an operator or paranthesis
            //Error: Missing operands in the expression


            if (!stk.empty()) {                                                                                                 //if stk is not empty
                //cout << "testing while " << (stk.top()[0] != '(') << ' ' << stk.top()[0] << " >= " << tok[0] << endl;
                while (!stk.empty() && stk.top()[0] != '(' && precede(stk.top()[0]) >= precede(tok[0])) {                       //if the precidence of the symbole on the stack is greater than the new one the print it (continue)
                    //cout << "in operator while print operator" << endl;
                    //cout<< "STORE :" << stk.top() << endl;
                    post.push(stk.top());
                    //cout << "in operator while pop stk" << endl;
                    stk.pop();
                }
            }
            //cout << "push operator\t"<< "tok :"<< tok << endl;
            stk.push(tok);              //push operator
            if(sub.size() == 0){                                       //if last input read in is an operator it is an error
                //cout << "first catch\n";        //delete
                //cout << "ERROR: last input was an operator\n";
                post.clear();
                post.push("ERROR: last input was an operator");
                cout << "passing false3\n";
                e = false;
                return post;
            }
        } else if (tok[0] == ')') {
            //cout << ") if statement \n" << post.top() << endl;
            if (post.top() == "+" || post.top() == "-"|| post.top() == "*"|| post.top() == "/") {
                //cout << "ERROR: <operator> ) ";
                post.clear();
                post.push("ERROR: <operator> ) ");
                cout << "passing false4\n";
                e = false;
                return post;
            } else {
                while (stk.top()[0] != '(') {
                    //cout << ") while loop printo stk top" << endl;
                    //cout <<"STORE :" << stk.top() << endl;
                    post.push(stk.top());
                    stk.pop();
                }
            }
        }

        //cout <<"post at end of while :"<<post<<'\n';
    } /////////////////end of while

    //cout << "end of for loop" << endl;
    if(!stk.empty()) {
        while (!stk.empty() ) {
            //cout << "in last while loop " << endl;
            //cout << "content os stk: "<< stk<<'\n';
            //cout << "stk.top() :"<< stk.top() << endl;
            //cout << "post b4:" << *post << '\n';
            if(stk.top()[0] != '(')                             //prevent parentheis from being in stack
                post.push(stk.top());
            //cout << "STORE post after:"<< *post << '\n';
            stk.pop();
        }
        //cout << "\nend of last while loop\n";
    }
    //cout<<*post<<'\n';
    return post;
    //cout << "\nend of in2post()\n";

} ////////////end of in2post()

void ansr(Stack<string>& stk){
    stk.rev();                             // reverse order os stack for the sake of the equation
    Stack<double> junk;                    // temp stack
    cout << "1st value in junk: " << stk.top() << '\n';
    if(isdigit(stk.top()[0])) {
        junk.push(stod(stk.top()));             //push  the first 2 elements of argument to junk
    }else{
        cout << "error operand was not found\n";
    }
    stk.pop();
    cout <<"2nd value in junk: " << stk.top()<<'\n';
    if(isdigit(stk.top()[0])){
        junk.push(stod(stk.top()));
    }else{
        cout << "error operand was not found\n";
    }

    stk.pop();
    //int i = 0;  //delete
    cout <<" before while\n";
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
                //cout << i <<':'<< l << '+'<<r<<" junk.top() :"<<junk.top()<<'\n';
            }
            else if(stk.top() == "-") {
                junk.push(l - r);
                //cout << i <<':'<< l << '-'<<r<<" junk.top() :"<<junk.top()<<'\n';
            }
            else if(stk.top() == "*") {
                junk.push(l * r);
                //cout << i <<':'<< l << '*'<<r<<" junk.top() :"<<junk.top()<<'\n';
            }
            else if (stk.top() == "/") {
                junk.push(l / r);
                //cout << i <<':'<< l << '/'<< r <<" junk.top() :"<<junk.top()<<'\n';
            }else{
                cout << "error: no operator found\n";
                break;
            }
            //i++;        //delete
        }
        //cout <<"junk :"<<junk<<'\n';
        stk.pop();      //used to increment to next element in stack

    }
    cout << "stk :"<< stk << '\n';
    cout << "junk.top() :"<< junk.top()<< '\n';
}
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


