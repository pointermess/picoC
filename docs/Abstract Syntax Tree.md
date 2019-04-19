# Abstract Syntax Tree


## 1.1 ASTElement

Base class which holds basic information for every AST element.

| Property | Data Type | Description |
| --- | --- | --- |
| Line | unsigned int | - |
| Position | unsigned int | - |
| Begin | unsigned int | - |
| End | unsigned int | - |


### 1.1.1 ASTBlockElement

An AST element which can hold other elements in a vector.

| Property | Data Type | Description |
| --- | --- | --- |
| Children | std::vector\<ASTElementPtr\> | - |


#### 1.1.1.1 ASTProgram


### 1.1.2 ASTExpression

Holds most of the picoC specific expressions.


#### 1.1.2.1 ASTTypeExpression

Holds most of the picoC specific expressions.

| Property | Data Type | Description |
| --- | --- | --- |
| Signed | bool (default "true") | - |
| DataType | std::string | - |


#### 1.1.2.2 ASTParenthesizedExpression

Specifies and expression between brackets.

| Property | Data Type | Description |
| --- | --- | --- |
| Expression | ASTExpression* | - |
