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
  | BigIntLiteral;          // Integrated
```
