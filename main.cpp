#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
const string TOKEN_OP = "Operator";
const string TOKEN_IDENTIFIER = "Identifier";
const string TOKEN_Keyword = "Keyword";
const string TOKEN_EOF = "-1";
static unordered_set<string> keywords = {
    "auto",     "bool",      "break",    "case",      "catch",   "char",
    "class",    "const",     "continue", "default",   "delete",  "do",
    "double",   "else",      "enum",     "explicit",  "extern",  "false",
    "float",    "for",  "goto",      "if",      "inline",
    "int",      "long",      "mutable",  "namespace", "new",     "operator",
    "private",  "protected", "public",   "register",  "return",  "short",
    "signed",   "sizeof",    "static",   "struct",    "switch",  "template",
    "this",     "throw",     "true",     "try",       "typedef", "virtual", "void",
    "volatile", "wchar_t",   "while"};
bool checkDigit(char c) { return c >= '0' && c <= '9'; }
bool checkLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool checkKeyword(const string &input) { return keywords.count(input) > 0; }

string valid_statement(const string &statement) {
  size_t statement_pos = statement.find('=');
  size_t semicolon_pos = statement.find(';');
  if (statement_pos == string::npos || semicolon_pos == string::npos ||
      statement_pos >= semicolon_pos) {
    return "syntax is invalid";
  } 
  string var_name = statement.substr(0, statement_pos);
  string value_str =
      statement.substr(statement_pos + 1, semicolon_pos - statement_pos - 1);

  // Step 2: check if variable name is valid
  if (!isalpha(var_name[0]) && var_name[0] != '_') {

    return "syntax is invalid";
  }
  for (char c : var_name.substr(1)) {
    size_t type_pos = statement.find(" ");
    string type_name = statement.substr(0, type_pos);
    if(checkKeyword(type_name)){
      return "syntax is valid";
    }
     if (!isalnum(c) && c != '_') {
      return "syntax is invalid";
    }
  }
  if (checkKeyword(var_name)) {
    return "variable name cannot be a keyword";
  }

  // Step 3: check if value is valid
  try {
    int value = stoi(value_str);
  } catch (invalid_argument &e) {
    return "syntax is invalid";
  }

  // Step 4: syntax is valid
  return "syntax is valid";
}

void LexicalGenerator(string input, int &position, string &token, string &lexeme) {
  lexeme = "";
  token = TOKEN_EOF;
  // Skip whitespace
  while (position < input.length() && isspace(input[position])) {
    position++;
  }
  // Check for end of input
  if (position >= input.length()) {
    return;
  }
  // Check for integer
  if (checkDigit(input[position])) {
    token = TOKEN_IDENTIFIER;
    while (position < input.length() && checkDigit(input[position])) {
      lexeme += input[position];
      position++;
    }
  }
  // Check for operator or parentheses
  else if (input[position] == '+') {
    token = TOKEN_OP;
    lexeme = "+";
    position++;
  } else if (input[position] == ';') {
    token = TOKEN_OP;
    lexeme = ";";
    position++;
  } else if (input[position] == '=') {
    token = TOKEN_OP;
    lexeme = "=";
    position++;
  } else if (input[position] == '-') {
    token = TOKEN_OP;
    lexeme = "-";
    position++;
  } else if (input[position] == '*') {
    token = TOKEN_OP;
    lexeme = "*";
    position++;
  } else if (input[position] == '/') {
    token = TOKEN_OP;
    lexeme = "/";
    position++;
  } else if (input[position] == '(') {
    token = TOKEN_OP;
    lexeme = "(";
    position++;
  } else if (input[position] == ')') {
    token = TOKEN_OP;
    lexeme = ")";
    position++;
  }
  else if (checkLetter(input[position])) {
     
    while (position < input.length() &&
           (checkLetter(input[position]) || checkDigit(input[position]))) {
      size_t type_pos = input.find(" ");
      string type_name = input.substr(0, type_pos);
      if (checkKeyword(type_name)&& position<=type_pos) {
                token = TOKEN_Keyword;
            }
      else{
                token = TOKEN_IDENTIFIER;
      }
      lexeme += input[position];
                position++;

    }
  } 
  // Unknown character
  else {
    cerr << "Unknown character: " << input[position] << std::endl;
    position++;
  }
}

int main() {
 
  while (true) {
  int position = 0;
  string Lextoken;
  string lexeme;
    string input;
    cout << endl << "Enter a statement: ";
    getline(cin, input);
    cout << "Lexical Analysis:"<<endl;
    while (true) {
      LexicalGenerator(input, position, Lextoken, lexeme);
      cout << " Token is: " << Lextoken << ",  Lexeme is " << lexeme << std::endl;

      if (Lextoken == TOKEN_EOF) {
        break;
      }
    }
    if (input == "quit") {
      break;
    }
    cout<< "Syntax Validation: " + valid_statement(input);
  }
  return 0;
}
