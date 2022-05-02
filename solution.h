#include <iostream>
#include <map>
#include "node.h"
#include "forward.h"
#include "double.h"
#include "circular.h"

using namespace std;

struct Result{
    double result;
    bool error;
};

bool is_number(char c){
    if(c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9')
        return true;
    return false;
}

bool is_sign(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/')
        return true;
    return false;
}

bool string_is_sign(string c){
    if(c=="+" || c=="-" || c=="*" || c=="/")
        return true;
    return false;
}

int preference(char c){
    map<char, int> pref = {{'+', 1,},
                           {'-', 1,},
                           {'*', 2,},
                           {'/', 2,}};
    return pref[c];
}

Result evaluate(string input)
{
    // 1- descomponer el input y validar
    // 2- convertir de Infijo a Postfijo
    // 3- resolver la expresion

    //* Si no cumple la validacion retornar Result.error = true;

    Result resultado;

    List<string> *postfijo = new CircularList<string>();
    List<char> *stack1 = new CircularList<char>();
    List<double> *stack2 = new CircularList<double>();
    string num;
    string sign;

    if(is_sign(input[0]) || is_sign(input[input.size()-1])){
        resultado.error = true;
        return resultado;
    }

    for(int i=0; i<input.size(); ++i){
        if(is_number(input[i])){
            if(i==input.size()){
                num+=input[i];
                postfijo->push_back(num);
                num="";
            }
            else if(is_number(input[i+1]))
                num+=input[i];
            else if(!is_number(input[i+1])){
                num+=input[i];
                postfijo->push_back(num);
                num="";
            }
        }
        else if(input[i] == '(' || input[i] == '[') {
            stack1->push_back(input[i]);
        }
        else if(is_sign(input[i])){
            if(stack1->is_empty())
                stack1->push_back(input[i]);
            else if(is_sign(stack1->back()) && (preference(input[i]) <= preference(stack1->back()))){
                sign+=stack1->pop_back();
                postfijo->push_back(sign);
                sign="";
                stack1->push_back(input[i]);
            }
            else
                stack1->push_back(input[i]);
        }
        else if(input[i] ==')'){
            while(stack1->back()!='('){
                sign+=stack1->pop_back();
                postfijo->push_back(sign);
                sign="";
            }
            stack1->pop_back();
        }
        else if(input[i] ==']'){
            while(stack1->back()!='['){
                sign+=stack1->pop_back();
                postfijo->push_back(sign);
                sign="";
            }
            stack1->pop_back();
        }
        else if(input[i] != ' '){
            resultado.error = true;
            return resultado;
        }
    }

    sign="";
    while(!stack1->is_empty()) {
        sign += stack1->pop_back();
        postfijo->push_back(sign);
        sign = "";
    }

    for (ListIterator<string> i=postfijo->begin(); i!=postfijo->end(); ++i) {
        if (*i == "(" || *i == ")" || *i == "[" || *i == "]"){
            resultado.error = true;
            return resultado;
        }
    }

    while(!postfijo->is_empty()){
        string elem = postfijo->pop_front();
        if(!string_is_sign(elem)){
            double n = stod(elem);
            stack2->push_back(n);
        }
        else{
            if(stack2->size()<2){
                resultado.error = true;
                return resultado;
            }
            double op1 = stack2->pop_back();
            double op2 = stack2->pop_back();
            if(elem=="+"){
                stack2->push_back(op2+op1);
            }
            else if(elem=="-"){
                stack2->push_back(op2-op1);
            }
            else if(elem=="*"){
                stack2->push_back(op2*op1);
            }
            else{
                stack2->push_back(op2/op1);
            }
        }
    }

    resultado.result = stack2->pop_back();
    resultado.error = false;

    return resultado;
}
