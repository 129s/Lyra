grammar LyraParser;

options {
	tokenVocab = LyraLexer;
}

root: clip | clipContent EOF; //全局层级可省略大括号

// clip：音乐片段，可选：语句/前后对齐锚点
clip: LBRACE clipContent RBRACE;
// 依次将前一个子元素的后对齐符与后一个子元素的前对齐符对齐，子元素间首尾相接
clipContent:
	stmt* element* alignmentHeader? element* alignmentFooter? element*;

// 对齐标志符
alignmentHeader: COLON;
alignmentFooter: SEMI;
// 对齐标识符用于设置容器的对齐点，具体的对齐行为由容器的父容器决定

// 语句
stmt: refStmt;

// 引用语句
refStmt: AT ref EQUAL element;
ref: ID (DOT ID)*;

// 元语句
metaStmt:
	AT NAME EQUAL ID
	| AT TEMPO EQUAL (FLOAT | INT)
	| AT UNIT EQUAL FRACTION
	| AT METER EQUAL FRACTION
	| AT KEY EQUAL PITCH_LETTER
	| AT OCT EQUAL INT;

// 容器
container: parallelContainer | sliceContainer;

// 平行容器
parallelContainer: LPAREN element* RPAREN;
// 将所有子元素的前对齐符对齐

// 均分容器
sliceContainer: LBRACK element* RBRACK;
// 根据子元素个数n将自身时间均分为n份，将子元素的前对齐符对齐至第n等分点 

// 元素
element: container | pitch | chord | placeholder | ref;

// 填充占位符
placeholder: DOT;

// 音高
pitch:
	MODIFIER? (PITCH_LETTER (INT OCTAVE_MOD?)? | INT) OCTAVE_MOD?
	| REST;

// 和弦
chord:
	pitch APOSTROPHE (
		chordQuality
		| chordSus
		| chordAlteration
		| chordExtension
		| chordModification
		| chordSlash
	)+;

chordQuality: 'M' | 'm' | 'maj' | 'min' | 'aug' | 'dim';
chordSus: 'sus' ('2' | '4')?;
chordAlteration: ('b' | '#') ('5' | '9' | '11' | '13');
chordExtension: ('7' | '9' | '11' | '13') (
		'/' ( 'b' | '#')? ('5' | '9' | '11' | '13')
	)?;
chordModification: ('add' | 'no' | 'omit') (
		'2'
		| '4'
		| '5'
		| '7'
		| '9'
		| '11'
	);
chordSlash: '/' (pitch | REST);