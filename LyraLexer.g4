lexer grammar LyraLexer;

// 空白字符忽略
COMMENT: '//' ~[\r\n]* -> skip;
WS: [ \t\r\n]+ -> skip;

// 休止符
REST: '0';

// 容器元数据
NAME: 'name'; // 包名
TEMPO: 'tempo'; // bpm
METER: 'meter'; // 拍号
UNIT: 'unit'; // 单位时间
KEY: 'key'; // 调号
OCT: 'oct'; // 音域

// 标识符
ID: [a-zA-Z_][a-zA-Z0-9_]*;

// 符号
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
LPAREN: '(';
RPAREN: ')';

AT: '@';
EQUAL: '=';

COLON: ':';
SEMI: ';';
DOT: '.';
BANG: '!';
APOSTROPHE: '\'';
QUOTATION: '"';

// 数值类型
FLOAT: '0' '.' [0-9]+ | [1-9][0-9]* '.' [0-9]+;
FRACTION: [0-9]+ '/' [0-9]+;
INT: [0-9]+;

// 音高相关
PITCH_LETTER: [CDEFGAB];
MODIFIER: ('b' | '#')+;
OCTAVE_MOD: [+-]+;