# Ambsh Unofficial Documentation
Ambsh/Ambashell is a programming language built into Ambarella based  
cameras. You can often run Ambsh code with an autoexec.ash file in the  
root directory of the SD card.

## Reserved Keywords:
```
IF
FI
WHILE
LOOP
UNTIL
DONE
ELSE
DO
THEN
```

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
`if` tests the return value of a command.  
True and false are both commands.
```
if true; then
	echo Hello, world
else
	echo Goodbye
fi
```
When a command returns an error, this means  
it should return false.
```
if rm foo.txt; then
	echo Failed to remove foo.txt
fi
```

## Pipes
```
>>
<<
>
<
&
|
```

```
echo Hello, World >> foo.txt
echo 'Hi' > foo.txt # buggy
```

## Variables
I couldn't find any evidence for variables in ambsh.  
`foo=1` return a syntax error.
