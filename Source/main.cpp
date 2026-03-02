#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <print>
#include <unordered_map>

#ifndef NODISCARD 
#define NODISCARD [[nodiscard("The result of this expression should not be ignored.")]]
#endif

#ifndef SHORTHAND_TYPES
#define SHORTHAND_TYPES

#include <cstdint>

using   U8      =   std::uint8_t;
using   U16     =   std::uint16_t;
using   U32     =   std::uint32_t;
using   U64     =   std::uint64_t;

using   I8      =   std::int8_t;
using   I16     =   std::int16_t;
using   I32     =   std::int32_t;
using   I64     =   std::int64_t;

using   F32     =   float;
using   F64     =   double;

#endif

enum class ETokenType
{
    TT_UNDEFINED,

    // Control flow
    TT_BREAK,
    TT_CASE,
    TT_CATCH,
    TT_CLASS,
    TT_CONST,
    TT_CONTINUE,
    TT_DEBUGGER,
    TT_DEFAULT,
    TT_DELETE,
    TT_DO,
    TT_ELSE,
    TT_EXPORT,
    TT_EXTENDS,
    TT_FINALLY,
    TT_FOR,
    TT_FUNCTION,
    TT_IF,
    TT_IMPORT,
    TT_IN,
    TT_INSTANCEOF,
    TT_NEW,
    TT_RETURN,
    TT_SUPER,
    TT_SWITCH,
    TT_THIS,
    TT_THROW,
    TT_TRY,
    TT_TYPEOF,
    TT_VAR,
    TT_VOID,
    TT_WHILE,
    TT_WITH,
    TT_YIELD,

    // Literals
    TT_TRUE,
    TT_FALSE,
    TT_NULL,

    // Async / modules
    TT_AWAIT,

    // Reserved / strict
    TT_ENUM,
    TT_IMPLEMENTS,
    TT_INTERFACE,
    TT_LET,
    TT_PACKAGE,
    TT_PRIVATE,
    TT_PROTECTED,
    TT_PUBLIC,
    TT_STATIC,

    TT_MAX,
};

struct Token 
{
    ETokenType  Type;       // Tokens Type. 
    U64         Attribute;  // Index into global symbol table. 

    Token(ETokenType type, U64 attribute) 
        : 
            Type{type},
            Attribute{attribute}

    {}

    ~Token() = default;
};



static const std::unordered_map<ETokenType, const char*> TokenMap = {
    { ETokenType::TT_BREAK, "break"},
    { ETokenType::TT_CASE, "case"},
    { ETokenType::TT_CATCH, "catch"},
    { ETokenType::TT_CLASS, "class"},
    { ETokenType::TT_CONST, "const"},
    { ETokenType::TT_CONTINUE, "continue"},
    { ETokenType::TT_DEBUGGER, "debugger"},
    { ETokenType::TT_DEFAULT, "default"},
    { ETokenType::TT_DELETE, "delete"},
    { ETokenType::TT_DO, "do"},
    { ETokenType::TT_ELSE, "else"},
    { ETokenType::TT_EXPORT, "export"},
    { ETokenType::TT_EXTENDS, "extends"},
    { ETokenType::TT_FINALLY, "finally"},
    { ETokenType::TT_FOR, "for"},
    { ETokenType::TT_FUNCTION, "function"},
    { ETokenType::TT_IF, "if"},
    { ETokenType::TT_IMPORT, "import"},
    { ETokenType::TT_IN, "in"},
    { ETokenType::TT_INSTANCEOF, "instanceof"},
    { ETokenType::TT_NEW, "new"},
    { ETokenType::TT_RETURN, "return"},
    { ETokenType::TT_SUPER, "super"},
    { ETokenType::TT_SWITCH, "switch"},
    { ETokenType::TT_THIS, "this"},
    { ETokenType::TT_THROW, "throw"},
    { ETokenType::TT_TRY, "try"},
    { ETokenType::TT_TYPEOF, "typeof"},
    { ETokenType::TT_VAR, "var"},
    { ETokenType::TT_VOID, "void"},
    { ETokenType::TT_WHILE, "while"},
    { ETokenType::TT_WITH, "with"},
    { ETokenType::TT_YIELD, "yield"},
    { ETokenType::TT_TRUE, "true"},
    { ETokenType::TT_FALSE, "false"},
    { ETokenType::TT_NULL, "null"},
    { ETokenType::TT_AWAIT, "await"},
    { ETokenType::TT_ENUM, "enum"},
    { ETokenType::TT_IMPLEMENTS, "implements"},
    { ETokenType::TT_INTERFACE, "interface"},
    { ETokenType::TT_LET, "let"},
    { ETokenType::TT_PACKAGE, "package"},
    { ETokenType::TT_PRIVATE, "private"},
    { ETokenType::TT_PROTECTED, "protected"},
    { ETokenType::TT_PUBLIC, "public"},
    { ETokenType::TT_STATIC, "static"},
};


struct FTokenizer { };

void Tokenize() { return; }
void Parse()    { return; }

/* 
    * idk is std::ifstream checks whether or not the file is valid when attempting to construct an instance. 
    * so this is what this function does.
 */

NODISCARD std::ifstream ReadFile(std::string fname)
{
    using   std::print; 
    using   std::filesystem::current_path; 
    using   std::filesystem::exists; 

    const std::string QualifiedFilename = std::string{current_path().c_str()} + "/" + fname ; 
    if (!exists(QualifiedFilename))
    {
        print("Error: File does not exist: {}\n", QualifiedFilename);
        std::exit(EXIT_FAILURE);
    }
    return std::ifstream{QualifiedFilename, std::ios_base::in}; 
}

int main(int argc, char* argv[])
{
    if ( argc < 2 )
    {
        std::cout << 
            "Error: Usage violation\nUsage: " <<
            argv[0] <<
            " <filename>\n";
        return EXIT_FAILURE;
    }

    auto File = ReadFile(argv[1]);
    std::string Buffer;

    while (std::getline(File, Buffer))
    {
    }
    return 0; 
}
