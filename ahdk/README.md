# ashp
Ambashell preprocessor. It can be used to generate  
ASH scripts.  

I could use a general purpose preprocessor, but this    
is spiffier.  

# Compilation:
`cc *.c; ./a.out test.ash`

# Syntax
- ashp commands are enclosed in `[]`.
- To insert a preprocessor definition in regular text, use `{TOKEN_NAME}`
- Use `[end]` to terminate any statement
- Tokens in preprocessor statements are checked to find preprocessor definitions.  
Therefore, use strings in `ifdef` statements.

# Commands
```
define
ifeq
genunicode
writebin
writefile
ifdef
ifndef
```

A full syntax demonstration can be found in test.ash