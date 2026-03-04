# Parser
____

#### Inheritance Hierarchy
    Parser -> StatementParser -> ExpressionParser -> LValueParser ->NodeUtils -> UtilsParser -> Tokenizer -> CommentParser -> BaseParser



#### Porting Statement 

```typescript
export type Statement =
  | BlockStatement          // Integrated.
  | BreakStatement          // Integrated.
  | ContinueStatement       // Integrated.
  | DebuggerStatement       // Integrated.
  | DoWhileStatement        // Integrated.
  | EmptyStatement          // Integrated.
  | ExpressionStatement     // Integrated, Needs work.
  | ForInStatement          // Integrated
  | ForStatement
  | FunctionDeclaration
  | IfStatement
  | LabeledStatement
  | ReturnStatement
  | SwitchStatement
  | ThrowStatement
  | TryStatement
  | VariableDeclaration     // Integrated.
  | WhileStatement
  | WithStatement
  | ClassDeclaration
  | ExportAllDeclaration
  | ExportDefaultDeclaration
  | ExportNamedDeclaration
  | ForOfStatement
  | ImportDeclaration
  | FlowDeclareClass
  | FlowDeclareFunction
  | FlowDeclareInterface
  | FlowDeclareModule
  | FlowDeclareModuleExports
  | FlowDeclareTypeAlias
  | FlowDeclareOpaqueType
  | FlowDeclareVariable
  | FlowDeclareExportDeclaration
  | FlowEnumDeclaration
  | FlowInterface
  | FlowOpaqueType
  | FlowTypeAlias
  | TSDeclareFunction
  | TsInterfaceDeclaration
  | TsTypeAliasDeclaration
  | TsEnumDeclaration
  | TsModuleDeclaration
  | TsImportEqualsDeclaration
  | TsExportAssignment
  | TsNamespaceExportDeclaration;
```


#### Porting Literals 
______

```typescript
export type Literal =
  | RegExpLiteral           // Integrated
  | NullLiteral             // Integrated
  | StringLiteral           // Integrated
  | BooleanLiteral          // Integrated
  | NumericLiteral          // Integrated
  | BigIntLiteral;          // Integrated cavaet being that right now it's more like a fixed-width 128-bit integer. see C _int128 perhaps utilize a method that allows the value to "grow" dynamically
``` 


#### Porting Decorators
____

- [x] FDecorator.
- [x] HasDecorator.

#### Porting Patterns 
____
```typescript 
export type Pattern =
  | Identifier
  | ObjectPattern
  | ArrayPattern
  | RestElement
  | AssignmentPattern
  | VoidPattern;
```

#### Porting Assignable  (RELIES ON PATTERNS)
______ 

```typescript
export type Assignable =
  | Pattern // A bit complicated because it is a concept.
  | MemberExpression
  | ParenthesizedExpression
  | TsTypeCastExpression
  | TypeCastExpression;
```
