lexer grammar LyraLexer;

// 空白字符忽略
COMMENT: '//' ~[\r\n]* -> skip;
WS: [ \t\r\n]+ -> skip;

// 休止符
REST: '0';

// 元数据
TEMPO: 'tempo';
METER: 'meter';
UNIT: 'unit';
KEY: 'key';
OCT: 'oct';

// 标志符
ID: [a-zA-Z_][a-zA-Z0-9_]*;

// 容器符号
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
LPAREN: '(';
RPAREN: ')';

// 声明元数据
AT: '@';
EQUAL: '=';

// 数值类型
FLOAT: '0' '.' [0-9]+ | [1-9][0-9]* '.' [0-9]+;
FRACTION: [0-9]+ '/' [0-9]+;
INT: [0-9]+;

// 音高相关
PITCH_LETTER: [CDEFGAB];
MODIFIER: ('b' | '#')+;
OCTAVE_MOD: [+-]+;

// 时间对齐
COLON: ':';
SEMI: ';';

// 空白填充
DOT: '.';

// 和弦声明
APOSTROPHE: '\'';