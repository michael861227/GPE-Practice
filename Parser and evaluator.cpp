#include <cctype>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Parser {
private:
    const string& expression;
    size_t pos;
    bool valid;

    // 如果目前字元等於 expected，就吃掉該字元
    bool consume(char expected) {
        if (pos < expression.size() &&
            expression[pos] == expected) {
            ++pos;
            return true;
        }
        return false;
    }

    /*
     * 最低優先序：二元 +、-
     *
     * Expression :=
     *     MulDiv { ('+' | '-') MulDiv }
     *
     * 使用 while 立即累積結果，形成左結合。
     */
    long long parseExpression() {
        long long value = parseMulDiv();

        while (valid && pos < expression.size() &&
               (expression[pos] == '+' ||
                expression[pos] == '-')) {

            char op = expression[pos++];
            long long right = parseMulDiv();

            // 運算子後面沒有合法運算元
            if (!valid) {
                return 0;
            }

            if (op == '+') {
                value += right;
            } else {
                value -= right;
            }
        }

        return value;
    }

    /*
     * 第三層優先序：二元 *、/
     *
     * MulDiv :=
     *     Modulo { ('*' | '/') Modulo }
     *
     * 注意：右運算元呼叫 parseModulo()，
     * 所以 % 會比 *、/ 更早計算。
     */
    long long parseMulDiv() {
        long long value = parseModulo();

        while (valid && pos < expression.size() &&
               (expression[pos] == '*' ||
                expression[pos] == '/')) {

            char op = expression[pos++];
            long long right = parseModulo();

            if (!valid) {
                return 0;
            }

            if (op == '*') {
                value *= right;
            } else {
                /*
                 * 題目沒有說明除以 0 的輸出方式。
                 * 這裡防禦性地將它視為無法接受，
                 * 避免發生 C++ 未定義行為。
                 */
                if (right == 0) {
                    valid = false;
                    return 0;
                }

                // C++ 整數除法
                value /= right;
            }
        }

        return value;
    }

    /*
     * 第二層優先序：%
     *
     * Modulo :=
     *     Unary { '%' Unary }
     */
    long long parseModulo() {
        long long value = parseUnary();

        while (valid && consume('%')) {
            long long right = parseUnary();

            if (!valid) {
                return 0;
            }

            if (right == 0) {
                valid = false;
                return 0;
            }

            value %= right;
        }

        return value;
    }

    /*
     * 最高優先序：一元正負號
     *
     * Unary :=
     *       '+' Unary
     *     | '-' Unary
     *     | Primary
     *
     * 使用遞迴，因此 --5、+-5 等運算式也能處理。
     */
    long long parseUnary() {
        if (consume('+')) {
            return parseUnary();
        }

        if (consume('-')) {
            return -parseUnary();
        }

        return parsePrimary();
    }

    /*
     * Primary :=
     *       Number
     *     | '(' Expression ')'
     */
    long long parsePrimary() {
        // 括號運算式
        if (consume('(')) {
            long long value = parseExpression();

            // 解析完括號內部後，一定要出現 ')'
            if (!valid || !consume(')')) {
                valid = false;
                return 0;
            }

            return value;
        }

        // 不是 '('，就必須是一個數字
        return parseNumber();
    }

    /*
     * Number := Digit { Digit }
     *
     * 讀取一個或多個連續數字。
     */
    long long parseNumber() {
        // Number 至少要有一個數字
        if (pos >= expression.size() ||
            !isdigit(
                static_cast<unsigned char>(expression[pos])
            )) {

            valid = false;
            return 0;
        }

        long long value = 0;

        while (pos < expression.size() &&
               isdigit(
                   static_cast<unsigned char>(expression[pos])
               )) {

            value = value * 10 + (expression[pos] - '0');
            ++pos;
        }

        return value;
    }

public:
    explicit Parser(const string& input)
        : expression(input), pos(0), valid(true) {}

    pair<bool, long long> parse() {
        // 空字串不符合文法
        if (expression.empty()) {
            return make_pair(false, 0);
        }

        long long answer = parseExpression();

        /*
         * 即使前半段可以解析，只要還有剩餘字元，
         * 整個輸入仍然不合法。
         *
         * 這也會抓到空白、英文字母、多餘右括號等問題。
         */
        if (pos != expression.size()) {
            valid = false;
        }

        return make_pair(valid, answer);
    }
};

int main() {
    string line;
    int caseNumber = 1;

    // 每一行是一個案例，讀到 EOF
    while (getline(cin, line)) {
        // 防止 Windows CRLF 的 '\r' 被當成運算式內容
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        Parser parser(line);
        pair<bool, long long> result = parser.parse();

        cout << "case " << caseNumber++ << ":\n";

        if (result.first) {
            cout << result.second << '\n';
        } else {
            cout << "syntactically incorrect\n";
        }

        // 每個案例最後都要有一個空白行
        cout << '\n';
    }

    return 0;
}