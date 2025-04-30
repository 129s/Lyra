lexer grammar LyraLexer;

// 空白字符忽略
COMMENT: '//' ~[\r\n]* -> skip;
WS: [ \t\r\n]+ -> skip;

// 符号
COLON: ':';
SEMI: ';';
TILDE: '~';
APOSTROPHE: '\'';
DOT: '.';
BANG: '!';
SLASH: '/';
LBRACE: '{';
RBRACE: '}';
LPAREN: '(';
RPAREN: ')';
LBRACK: '[';
RBRACK: ']';
EQUALS: '=';
AT: '@';

// 属性关键字
AT_KEY: '@key';
AT_TEMPO: '@tempo';
AT_METER: '@meter';
AT_UNIT: '@unit';

// 音阶类型
SCALE:
	MAJOR
	| MINOR
	| IONIAN
	| DORIAN
	| PHRYGIAN
	| LYDIAN
	| MIXOLYDIAN
	| AEOLIAN
	| LOCRIAN
	| PENTATONIC;
MAJOR: 'major';
MINOR: 'minor';
IONIAN: 'ionian';
DORIAN: 'dorian';
PHRYGIAN: 'phrygian';
LYDIAN: 'lydian';
MIXOLYDIAN: 'mixolydian';
AEOLIAN: 'aeolian';
LOCRIAN: 'locrian';
PENTATONIC: 'pentatonic';

// 和弦类型
MAJOR_CHORD: 'maj' | 'M';
MINOR_CHORD: 'min' | 'm' | '-';
DIM_CHORD: 'dim' | '°';
AUG_CHORD: 'aug' | '+';
SUS: 'sus4' | 'sus2' | 'sus';
ADD: 'add';
NO: 'no' | 'omit';
EXTENSION: '7' | '9' | '11' | '13';
ALTERATION: ('#' | 'b' | '+') ('5' | EXTENSION);

// 音高相关
OCTAVE_NUMBER: [0-9];
MIDI_NUMBER:
	[0-9]
	| [1-9][0-9]
	| '1' [0-1][0-9]
	| '12' [0-7]; // 0-127
PITCH_LETTER: [A-G];
SCALE_STEP: [1-7] | '1' [0-3]; // 最高到13音
PITCH_MODIFIER: ('b' | '#')+;
OCTAVE_MODIFIER: [+-]+;

// 布局类型
SLICER: 'slicer';

// 数值类型
FLOAT: '0' '.' [0-9]+ | [1-9][0-9]* '.' [0-9]+;
FRACTION: [0-9]+ '/' [0-9]+ | INT;
REST: '0'; // 优先于INT和MIDI_NUMBER匹配
INT: [0-9]+;

// 引用标识符
REF: AT [a-zA-Z_][a-zA-Z0-9_]*;