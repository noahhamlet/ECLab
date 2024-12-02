#include <iostream>
#include <string>
#include <cctype>

double extractNumeric(const std::string& input) {
    bool hasDecimal = false;
    bool hasSign = false;
    bool hasDigit = false;
    size_t i = 0;

    // Check for optional sign at the beginning
    if (input[i] == '+' || input[i] == '-') {
        hasSign = true;
        i++;
    }

    // Traverse the string to extract numeric value
    for (; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            hasDigit = true;
        } else if (input[i] == '.') {
            if (hasDecimal) {
                // More than one decimal point
                return -999999.99;
            }
            hasDecimal = true;
        } else {
            // Invalid character found
            return -999999.99;
        }
    }

    // Check if there was at least one digit
    if (!hasDigit) {
        return -999999.99;
    }

    // Convert string to double manually
    double result = 0.0;
    double decimalFactor = 1.0;
    bool isNegative = (input[0] == '-');
    size_t startIndex = (hasSign) ? 1 : 0;

    for (size_t j = startIndex; j < input.length(); ++j) {
        if (isdigit(input[j])) {
            if (hasDecimal) {
                decimalFactor /= 10.0;
                result += (input[j] - '0') * decimalFactor;
            } else {
                result = result * 10.0 + (input[j] - '0');
            }
        } else if (input[j] == '.') {
            hasDecimal = true;
        }
    }

    return isNegative ? -result : result;
}

int main() {
    std::string input;

    while (true) {
        std::cout << "Enter a string (or 'END' to quit): ";
        std::getline(std::cin, input);

        if (input == "END") {
            break;
        }

        double result = extractNumeric(input);

        if (result == -999999.99) {
            std::cout << "The input is invalid." << std::endl;
        } else {
            std::cout << "The input is: " << std::fixed << std::setprecision(4) << result << std::endl;
        }
    }

    return 0;
}