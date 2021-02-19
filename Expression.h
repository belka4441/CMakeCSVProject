#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <math.h>

class Expression {

public:
    Expression();
    Expression(const std::string& express);

    void setExpression(const std::string& express);

    void parse();
    float solve();

private:
    std::string expression;
    std::queue<std::string> rpnExpression;
    std::stack<char> operators;

    unsigned int priority(char operation);

};