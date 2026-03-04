# Parser
____

#### Inheritance Hierarchy
    Parser -> StatementParser -> ExpressionParser -> LValueParser ->NodeUtils -> UtilsParser -> Tokenizer -> CommentParser -> BaseParser



#### Porting Statement 

```typescript
export type Statement =
  | BlockStatement // Integrated.
  | BreakStatement // Integrated.
  | ContinueStatement
  | DebuggerStatement
  | DoWhileStatement
  | EmptyStatement
  | ExpressionStatement
  | ForInStatement
  | ForStatement
  | FunctionDeclaration
  | IfStatement
  | LabeledStatement
  | ReturnStatement
  | SwitchStatement
  | ThrowStatement
  | TryStatement
  | VariableDeclaration
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
