#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <variant>
#include <string>
#include <cassert>
#include <unordered_map>

struct OpeningBracket {};

struct ClosingBracket {};

struct Number {
    int value;
};

struct UnknownToken {
    std::string value;
};

struct MinToken {};

struct AbsToken {};

struct Plus {};

struct Minus {};

struct Multiply {};

struct Modulo {};

struct Divide {};

struct MaxToken {};

struct SqrToken {};

struct Comma {};

using Token = std::variant<OpeningBracket, ClosingBracket, Number, UnknownToken, MinToken, AbsToken, Plus, Minus, Multiply, Modulo, Divide, MaxToken, SqrToken, Comma>;

const std::unordered_map<char, Token> kSymbol2Token{
    {'+', Plus{}}, {'-', Minus{}}, {'*', Multiply{}}, {'/', Divide{}}, {'%', Modulo{}}
};

int ToDigit(unsigned char symbol) {
    return symbol - '0';
}

Number ParseNumber(const std::string& input, size_t& pos) {
    int value = 0;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isdigit(symbol)) {
        value = value * 10 + ToDigit(symbol);
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }
    return Number{ value };
}

MaxToken ParseMax(const std::string& input, size_t& pos) {
    if (input.substr(pos, 3) == "max") {
        pos += 3;
        return MaxToken{};
    }
    throw std::invalid_argument("Error(max)");
}

SqrToken ParseSqr(const std::string& input, size_t& pos) {
    if (input.substr(pos, 3) == "sqr") {
        pos += 3;
        return SqrToken{};
    }
    throw std::invalid_argument("Error(sqr)");
}

Comma ParseComma(const std::string& input, size_t& pos) {
    if (input[pos] == ',') {
        pos++;
        return Comma{};
    }
    throw std::invalid_argument("Error(comma)");
}

Token ParseName(const std::string& input, size_t& pos) {
    std::string name;
    auto symbol = static_cast<unsigned char>(input[pos]);
    while (std::isalpha(symbol)) {
        name += symbol;
        if (pos == input.size() - 1) {
            break;
        }
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    if (name == "max") {
        return ParseMax(input, pos);
    }
    else if (name == "sqr") {
        return ParseSqr(input, pos);
    }
    else {
        return UnknownToken{ name };
    }
}

std::vector<Token> Tokenize(const std::string& input) {
    std::vector<Token> tokens;
    const size_t size = input.size();
    size_t pos = 0;
    while (pos < size) {
        const auto symbol = static_cast<unsigned char>(input[pos]);
        if (std::isspace(symbol)) {
            ++pos;
        }
        else if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(input, pos));
        }
        else if (std::isalpha(symbol)) {
            tokens.emplace_back(ParseName(input, pos));
        }
        else if (auto it = kSymbol2Token.find(symbol); it != kSymbol2Token.end()) {
            tokens.emplace_back(it->second);
        }
        else if (symbol == ',') {
            tokens.emplace_back(ParseComma(input, pos));
        }
        ++pos;
    }
    return tokens;
}

int main() {
    std::string input = "max(1, 2) + 3 * sqr(4) - 5 % 2";
    auto tokens = Tokenize(input);

    for (const auto& token : tokens) {
        if (std::holds_alternative<Number>(token)) {
            std::cout << "Number: " << std::get<Number>(token).value << std::endl;
        }
        else if (std::holds_alternative<MaxToken>(token)) {
            std::cout << "MaxToken" << std::endl;
        }
        else if (std::holds_alternative<SqrToken>(token)) {
            std::cout << "SqrToken" << std::endl;
        }
        else if (std::holds_alternative<Comma>(token)) {
            std::cout << "Comma" << std::endl;
        }
        else if (std::holds_alternative<UnknownToken>(token)) {
            std::cout << "UnknownToken: " << std::get<UnknownToken>(token).value << std::endl;
        }
    }

    return 0;
}
