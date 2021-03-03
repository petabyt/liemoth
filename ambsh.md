# Ambsh Unofficial Documentation
Ambsh/Ambashell is a programming language built into Ambarella based  
cameras. They can often be run with an autoexec.ash file on the root
of the SD card.

## Reserved Keywords:
IF
FI
WHILE
LOOP
UNTIL
DONE
ELSE
DO
THEN

## Syntax
- For strings, always use single quotes.
- `;` can be used instead of a newline.
- Use `#` for comments.
- Spaces not required (?) `echo'Hello, World'`


## Loops
```
while true; do
	echo Hello, World
done

loop 10; do
	echo Hello, World
done

until true; do
	echo Hello, World
done
```

## Conditions
true/false also seem to be commands.
```
if true; then
	echo Hello, world
else
	echo Goodbye
fi

if false; then
	echo This will not show
fi
```

## Pipes
>>
<<
>
<
&
|
```
echo Hello, World >> foo.txt
echo 'Hi' > foo.txt # buggy
```

## Variables
I couldn't find any evidence for variables in ambsh.
`foo=1` return a syntax error.
