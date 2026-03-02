## Phase 1 — Tokenizer (1-2 months)
- [ ] Replicate `src/tokenizer/types.ts` — all token types in C++
- [ ] Port `src/tokenizer/state.ts` — tokenizer state machine
- [ ] Port `src/tokenizer/context.ts` — context tracking
- [ ] Port `src/tokenizer/index.ts` — main tokenizer logic
- [ ] **Goal:** Given JS source, produce identical token stream to Babel

---

## Phase 2 — Core Parser (2-4 months)
- [ ] Port `src/parser/` — this is the biggest chunk
- [ ] Handle expressions, statements, declarations
- [ ] Build the AST node types from `src/types.ts`
- [ ] **Goal:** Parse basic JS files and produce a valid AST

---

## Phase 3 — Plugin System (1-2 months)
- [ ] Design a C++ equivalent of Babel's plugin architecture
- [ ] Port `src/plugins/` one by one (start with TypeScript and JSX)
- [ ] **Goal:** Extensible system that mirrors Babel's flexibility

---

## Phase 4 — Error Handling (1 month)
- [ ] Port `src/parse-error/`
- [ ] Meaningful error messages with line/column info
- [ ] **Goal:** Errors that are as good as Babel's

---

## Phase 5 — Transforms & Codegen (2-4 months)
- [ ] AST traversal/visitor pattern
- [ ] Core transforms (ES2015+, JSX, TypeScript stripping)
- [ ] Code generation (AST back to source)
- [ ] **Goal:** Round-trip JS through your compiler

---

## Phase 6 — Hardening (ongoing)
- [ ] Run Babel's existing test suite against your output
- [ ] Performance benchmarking vs SWC/Babel
- [ ] Node.js bindings via NAPI so people can actually use it

---

