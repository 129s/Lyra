lexer grammar LyraLexer;

// 空白字符忽略
COMMENT: '//' ~[\r\n]* -> skip;
WS: [ \t\r\n]+ -> skip;

// 标识符
ID: [a-zA-Z_][a-zA-Z0-9_]*;

// 数值类型
FLOAT: '0' '.' [0-9]+ | [1-9][0-9]* '.' [0-9]+;
FRACTION: [0-9]+ '/' [0-9]+ | INT;
INT: [0-9]+;

// 音高相关
OCTAVE_NUMBER: [0-9];
MIDI_NUMBER:
	[0-9]
	| [1-9][0-9]
	| '1' [0-1][0-9]
	| '12' [0-7]; // 0-127
PITCH_LETTER: [A-G];
SCALE_STEP: [1-7]| '1' [0-3]; // 最高到13音
PITCH_MODIFIER: ('b' | '#')+;
OCTAVE_MODIFIER: [+-]+;

// 音阶
SCALE:
	'major'
	| 'minor'
	| 'ionian'
	| 'dorian'
	| 'phrygian'
	| 'lydian'
	| 'mixolydian'
	| 'aeolian'
	| 'locrian'
	| 'minor pentatonic'
	| 'major pentatonic';