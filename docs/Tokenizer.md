# Tokenizer

## Token Types

```cpp
    enum FATokenType
    {
        ttUnknown,

        ttCompilerCommand,

        ttConstString,
        ttConstDec,
        ttConstHex,

        ttKeywordIf,
        ttKeywordWhile,
        ttKeywordReturn,

        ttTypeSigned,
        ttTypeUnsigned,
        ttTypeVoid,
        ttTypeChar,
        ttTypeShort,
        ttTypeInt,

        ttSymbolLeftBrackt,
        ttSymbolRightBracket,
        ttSymbolLeftSquareBracket,
        ttSymbolRightSquareBracket,
        ttSymbolLeftCurlyBracket,
        ttSymbolRightCurlyBracket,
        ttSymbolComma,
        ttSymbolSemicolon,
        ttSymbolColon,
        ttSymbolQuestionMark,
        ttSymbolPlus,
        ttSymbolDash,
        ttSymbolAsteriks,
        ttSymbolForwardSlash,
        ttSymbolCommercialAnd,
        ttSymbolAnd,
        ttSymbolOr,
        ttSymbolExclamationMark,
        ttSymbolDefine,
        ttSymbolDefinePlus,
        ttSymbolDefineMinus,
        ttSymbolDefineTimes,
        ttSymbolEquals,
        ttSymbolNotEquals,
        ttSymbolIncrement,
        ttSymbolDecrement,


        ttIdentifier
    };
```
