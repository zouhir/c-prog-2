# 48430 Embedded C - Assignment 2

### Code Style

##### Code Blocks

Please do not have the opening curly bracket on a new line

WRONG:

```
void fun(void)
{
 //something
}
```

CORRECT ✅:

```
void fun(void) {
 //something
}
```

##### Block Padding

Please do not have extra block padding, ie: empty first line and empty last line.

WRONG:

```
void fun(void) {

 //something

}
```

CORRECT ✅:

```
void fun(void) {
 //something
}
```

### Comments Style

##### Block comments

start with 2 stars and then 1 spaced star, used for:

- Files heading

- Functions

- Structs

```

/**
 * comment
 */

```

##### Annotations

Used only in block comments, common used are:

```

@brief

@warning

@todo

@param

@return

```

##### Variable and struct members

if the line is not any longer than 80 character, comment next to the name using the following style:

```
int var = 0; /**< this is an integer variable */

```
