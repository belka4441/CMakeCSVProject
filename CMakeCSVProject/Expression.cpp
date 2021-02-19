#include "Expression.h"

Expression::Expression() : expression(), rpnExpression(), operators() {

    //TODO

}

Expression::Expression(const std::string& express) :
    expression(express), rpnExpression(), operators() {

    //TODO

}

void Expression::setExpression(const std::string& express) {

    expression = express;

}

void Expression::parse() {

    for (std::string::iterator it = expression.begin(); it != expression.end(); ++it) {

        if (*it >= '0' && *it <= '9') {

            std::string value;

            do {

                value += *it;

                ++it;

            } while (it != expression.end() && ((*it >= '0' && *it <= '9') || *it == '.'));

            --it;

            rpnExpression.push(value);

        }
        else {

            if (*it == ')') {

                while (operators.top() != '(') {

                    std::string value;
                    value = operators.top();

                    rpnExpression.push(value);

                    operators.pop();

                }

                operators.pop();

            }

            if (*it == '(') {

                operators.push(*it);

            }
            else {

                if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '^') {

                    if (operators.empty()) {

                        operators.push(*it);

                    }
                    else {

                        if (priority(*it) > priority(operators.top())) {

                            operators.push(*it);

                        }
                        else {

                            while (!operators.empty() && priority(operators.top()) >= priority(*it)) {

                                std::string value;
                                value = operators.top();

                                rpnExpression.push(value);

                                operators.pop();

                            }

                            operators.push(*it);

                        }

                    }

                }

            }

        }

    }

    while (!operators.empty()) {

        std::string value;
        value = operators.top();

        rpnExpression.push(value);

        operators.pop();

    }

}


float Expression::solve() {

    if (!rpnExpression.empty()) {

        std::stack<float> stack;
        std::string value;

        while (!rpnExpression.empty()) {

            value = rpnExpression.front();

            if (isdigit(value[0])) {

                stack.push(std::stof(value));

            }
            else {

                float secondValue = stack.top();
                stack.pop();
                float firstValue = stack.top();
                stack.pop();

                switch (*value.c_str()) {

                case '+':
                    stack.push(firstValue + secondValue);
                    break;

                case '-':
                    stack.push(firstValue - secondValue);
                    break;

                case '*':
                    stack.push(firstValue * secondValue);
                    break;

                case '/':
                    stack.push(firstValue / secondValue);
                    break;

                case '^':
                    stack.push(pow(firstValue, secondValue));
                    break;

                }

            }

            rpnExpression.pop();

        }

        return stack.top();

    }

    return 0.0f;

}

unsigned int Expression::priority(char operation) {

    switch (operation) {

    case '^':
        return 3;

    case '*':
    case '/':
        return 2;

    case '-':
    case '+':
        return 1;

    case '(':
        return 0;

    }

}