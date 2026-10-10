# 1. Specificarea Minilimbajului de Programare (MLP)

## Caracteristicile limbajului

*Cuvinte cheie:*
* Pentru tipuri de date: int, float, struct.
* Pentru instructiuni: cin, cout, if, else, while, return, main.

*Operatori:*
* Aritmetici: +, -, *, /, %
* Relaționali: ==, !=, <, >, <=, >=
* Atribuire: =
* Intrare / Iesire: >>, <<
* Acces memorie struct: .

*Separatori:*
* Paranteze si blocuri: (, ), {, }
* Punctuație: ;
* Spații albe: ` ` (spațiu), \t (tab), \n (newline).

### Restrictii lexicale suplimentare

- Identificatori: incep cu litera sau `_`, contin litere, cifre sau `_` și au lungimea de maximum 8 caractere
- Constante numerice reale: format strict `cifre.cifre` (minim o cifra intreaga si o cifra zecimala). Formatele prescurtate de tipul `.5` sau `5.` sunt interzise lexical
- Constante sir: delimitate obligatoriu prin ghilimele duble (`"..."`)

## Tabel codificari

| Atom Lexical                    | Cod Numeric |
|:--------------------------------| :---: |
| identificator                   | 0 |
| constanta                       | 1 |
| int                             | 2 |
| float                           | 3 |
| struct                          | 4 |
| if                              | 5 |
| else                            | 6 |
| while                           | 7 |
| cin                             | 8 |
| cout                            | 9 |
| return                          | 10 |
| main                            | 11 |
| =                               | 12 |
| +                               | 13 |
| -                               | 14 |
| *                               | 15 |
| /                               | 16 |
| %                               | 17 |
| ==                              | 18 |
| !=                              | 19 |
| <                               | 20 |
| <=                              | 21 |
| >                               | 22 |
| >=                              | 23 |
| >>                              | 24 |
| <<                              | 25 |
| (                               | 26 |
| )                               | 27 |
| {                               | 28 |
| }                               | 29 |
| ;                               | 30 |
| .                               | 31 |

## Gramatica formala: EBNF

```ebnf
Program = { StructDecl } "int" "main" "(" ")" CompoundStmt .

StructDecl = "struct" Identificator "{" { Tip Identificator ";" } "}" ";" .
Tip = "int" | "float" | Identificator .

CompoundStmt = "{" { Declaratie | Instructiune } "}" .
Declaratie = Tip Identificator [ "=" Expresie ] ";" .

Instructiune = Atribuire
           | InstructiuneIO
           | InstructiuneIf
           | InstructiuneWhile
           | CompoundStmt .

Atribuire = Identificator [ "." Identificator ] "=" Expresie ";" .
InstructiuneIO = "cin" ">>" Identificator [ "." Identificator ] ";"
             | "cout" "<<" ( Expresie | Constantasir ) ";" .
InstructiuneIf = "if" "(" Conditie ")" Instructiune [ "else" Instructiune ] .
InstructiuneWhile = "while" "(" Conditie ")" Instructiune .

Conditie = Expresie OperatorRel Expresie .
OperatorRel = "==" | "!=" | "<" | "<=" | ">" | ">=" .

Expresie = Termen { ( "+" | "-" ) Termen } .
Termen = Factor { ( "*" | "/" | "%" ) Factor } .
Factor = Identificator [ "." Identificator ] | Numar | "(" Expresie ")" .

Identificator = ( Litera | "_" ) { Litera | Cifra | "_" } .  (* max 8 caractere *)
Numar = Intreg | Real .
Intreg = Cifra { Cifra } .
Real = Cifra { Cifra } "." Cifra { Cifra } .
Constantasir = '"' { Caracter } '"' .

Litera = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m"
      | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z"
      | "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M"
      | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" .
Cifra = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" .
```

---

## 2. 3 programe sursa corecte

### Program 1 - Perimetrul si aria cercului

```cpp
#include <iostream>
using namespace std;

struct Cerc {
    float r;
    float p;
    float a;
};

int main() {
    Cerc c;
    float pi;
    pi = 3.1415;
    cin >> c.r;
    c.p = 2.0 * pi * c.r;
    c.a = pi * c.r * c.r;
    cout << c.p;
    cout << c.a;
    return 0;
}
```

### Program 2 - CMMDC a doua numere naturale

```cpp
#include <iostream>
using namespace std;

int main() {
    int a;
    int b;
    cin >> a;
    cin >> b;
    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    cout << a;
    return 0;
}
```

### Program 3 - Suma a n numere

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    int s;
    int x;
    int i;
    cin >> n;
    s = 0;
    i = 0;
    while (i < n) {
        cin >> x;
        s = s + x;
        i = i + 1;
    }
    cout << s;
    return 0;
}
```

---

## 3. 2 programe sursa cu erori

### 3.1. 2 erori comune (valide/invalid in MLP si C++)

Erori:

- Identificator invalid: `2var` începe cu cifra.
- Sir de caractere neterminat: `cout << "Eroare sir;` (lipseste inchiderea).

```cpp
#include <iostream>
using namespace std;

int main() {
    int 2var; // identificator invalid
    cout << "Eroare sir; // sir neterminat
    return 0;
}
```

### 3.2. 2 erori conforme MLP, dar valide în C++

Erori:

- Identificator prea lung: `identificatorLung` are 18 caractere (MLP impune max 8).
- Format constanta reala invalid: `val = .75;` (lipsesc cifre inainte de `.` in MLP).

```cpp
#include <iostream>
using namespace std;

int main() {
    int identificatorLung; // depaseste 8 caractere conform MLP
    identificatorLung = 10;
    float val;
    val = .75; // format invalid in MLP, valid in C++
    cout << identificatorLung;
    cout << val;
    return 0;
}
```

---

## 4. Identificarea atomilor lexicali

Citeste codul sursa dintr-un fisier, scaneaza secventele si clasifica atomii lexicali, semnaland erorile impreuna cu numarul liniei.

```cpp
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
