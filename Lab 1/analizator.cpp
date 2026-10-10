#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <iomanip>

using namespace std;

// Clasificarea categoriilor de atomi lexicali pentru MLP
enum AtomType {
    ATOM_KEYWORD,
    ATOM_IDENTIFIER,
    ATOM_INT_CONST,
    ATOM_FLOAT_CONST,
    ATOM_STRING_CONST,
    ATOM_OPERATOR,
    ATOM_SEPARATOR,
    ATOM_ERROR
};

struct Token {
    AtomType type;
    string value;
    int line;
    string errorMsg;
};

// Seturi de atomi predefiniti
const unordered_set<string> KEYWORDS = {
    "int", "float", "struct", "if", "else", "while", "cin", "cout", "return", "using", "namespace"
};

const unordered_set<string> OPERATORS = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", "<=", ">", ">=", "<<", ">>"
};

const unordered_set<char> SEPARATORS = {
    '(', ')', '{', '}', ';', '.'
};

string getAtomTypeName(AtomType t) {
    switch (t) {
        case ATOM_KEYWORD:      return "CUVANT_CHEIE";
        case ATOM_IDENTIFIER:   return "IDENTIFICATOR";
        case ATOM_INT_CONST:    return "CONST_INT";
        case ATOM_FLOAT_CONST:  return "CONST_FLOAT";
        case ATOM_STRING_CONST: return "CONST_SIR";
        case ATOM_OPERATOR:     return "OPERATOR";
        case ATOM_SEPARATOR:    return "SEPARATOR";
        case ATOM_ERROR:        return "EROARE_LEXICALA";
        default:                return "NECUNOSCUT";
    }
}

// Functia principala de scanare lexicala
vector<Token> scanTokens(const string& src) {
    vector<Token> tokens;
    int line = 1;
    size_t i = 0;
    size_t n = src.length();

    while (i < n) {
        char c = src[i];

        // 1. Spatii albe si linii noi
        if (c == '\n') {
            line++;
            i++;
            continue;
        }
        if (isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }

        // 2. Comentarii de tip // si directive de preprocesare (#...)
        if (c == '#' || (c == '/' && i + 1 < n && src[i + 1] == '/')) {
            while (i < n && src[i] != '\n') {
                i++;
            }
            continue;
        }

        // 3. Constante sir de caractere: "..."
        if (c == '"') {
            string lit;
            size_t start = i++;
            bool closed = false;
            while (i < n && src[i] != '\n') {
                if (src[i] == '"') {
                    closed = true;
                    i++;
                    break;
                }
                lit += src[i++];
            }
            if (closed) {
                tokens.push_back({ATOM_STRING_CONST, "\"" + lit + "\"", line, ""});
            } else {
                tokens.push_back({ATOM_ERROR, src.substr(start, i - start), line, "Sir de caractere neinchis"});
            }
            continue;
        }

        // 4. Separatori
        if (SEPARATORS.count(c)) {
            // Caz de eroare lexicala in MLP: punct urmat imediat de cifra (ex: .75)
            if (c == '.' && i + 1 < n && isdigit(static_cast<unsigned char>(src[i + 1]))) {
                string invalidFloat = ".";
                i++;
                while (i < n && isdigit(static_cast<unsigned char>(src[i]))) {
                    invalidFloat += src[i++];
                }
                tokens.push_back({ATOM_ERROR, invalidFloat, line, "Format float invalid (lipseste partea intreaga)"});
                continue;
            }

            tokens.push_back({ATOM_SEPARATOR, string(1, c), line, ""});
            i++;
            continue;
        }

        // 5. Operatori (simpli sau compusi de 2 caractere)
        if (string("+-*/%=!<>").find(c) != string::npos) {
            if (i + 1 < n) {
                string op2 = string(1, c) + src[i + 1];
                if (OPERATORS.count(op2)) {
                    tokens.push_back({ATOM_OPERATOR, op2, line, ""});
                    i += 2;
                    continue;
                }
            }
            string op1(1, c);
            if (OPERATORS.count(op1)) {
                tokens.push_back({ATOM_OPERATOR, op1, line, ""});
                i++;
            } else {
                tokens.push_back({ATOM_ERROR, op1, line, "Operator invalid"});
                i++;
            }
            continue;
        }

        // 6. Constante numerice
        if (isdigit(static_cast<unsigned char>(c))) {
            string num;
            bool isFloat = false;
            while (i < n && isdigit(static_cast<unsigned char>(src[i]))) {
                num += src[i++];
            }
            if (i < n && src[i] == '.') {
                if (i + 1 < n && isdigit(static_cast<unsigned char>(src[i + 1]))) {
                    isFloat = true;
                    num += src[i++]; // adauga '.'
                    while (i < n && isdigit(static_cast<unsigned char>(src[i]))) {
                        num += src[i++];
                    }
                }
            }

            // Daca numarul e urmat imediat de litera sau underscore -> identificator eronat
            if (i < n && (isalpha(static_cast<unsigned char>(src[i])) || src[i] == '_')) {
                while (i < n && (isalnum(static_cast<unsigned char>(src[i])) || src[i] == '_')) {
                    num += src[i++];
                }
                tokens.push_back({ATOM_ERROR, num, line, "Identificator invalid (incepe cu cifra)"});
            } else {
                tokens.push_back({isFloat ? ATOM_FLOAT_CONST : ATOM_INT_CONST, num, line, ""});
            }
            continue;
        }

        // 7. Identificatori sau Cuvinte Cheie
        if (isalpha(static_cast<unsigned char>(c)) || c == '_') {
            string word;
            while (i < n && (isalnum(static_cast<unsigned char>(src[i])) || src[i] == '_')) {
                word += src[i++];
            }

            if (KEYWORDS.count(word)) {
                tokens.push_back({ATOM_KEYWORD, word, line, ""});
            } else {
                // Restrictia specifica MLP: maxim 8 caractere
                if (word.length() > 8) {
                    tokens.push_back({ATOM_ERROR, word, line, "Identificatorul depaseste 8 caractere"});
                } else {
                    tokens.push_back({ATOM_IDENTIFIER, word, line, ""});
                }
            }
            continue;
        }

        // 8. Simboluri nepermise
        tokens.push_back({ATOM_ERROR, string(1, c), line, "Simbol necunoscut/nepermis"});
        i++;
    }

    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Utilizare: " << argv[0] << " <fisier_sursa.cpp>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fisierul " << argv[1] << "\n";
        return 1;
    }

    stringstream buffer;
    buffer << fin.rdbuf();
    fin.close();

    vector<Token> tokens = scanTokens(buffer.str());

    cout << "================= TABEL ATOMI LEXICALI ================\n";
    cout << left
         << setw(6)  << "Linie"
         << setw(18) << "Categorie"
         << setw(22) << "Lexem (Valoare)"
         << "Mesaj Eroare\n";
    cout << "----------------------------------------------------------------------\n";

    for (const auto& tok : tokens) {
        cout << left
             << setw(6)  << tok.line
             << setw(18) << getAtomTypeName(tok.type)
             << setw(22) << tok.value;
        if (tok.type == ATOM_ERROR) {
            cout << "[EROARE] " << tok.errorMsg;
        }
        cout << "\n";
    }

    return 0;
}