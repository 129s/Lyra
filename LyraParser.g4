grammar LyraParser;

options {
	tokenVocab = LyraLexer;
}

root: content EOF;

element: container | pitch | chord | placeholder | ref | stmt;

// 语句
stmt: refstmt;

// 引用语句
refstmt: AT ref EQUAL element;
ref: ID (DOT ID)*;

// 容器
container:
	sequenceContainer
	| parallelContainer
	| sliceContainer;

// 串行容器
sequenceContainer: LBRACE content RBRACE;
// 依次将前一个子元素的后对齐符与后一个子元素的前对齐符对齐，子元素间首尾相接

// 并行容器
parallelContainer: LPAREN content RPAREN;
// 将所有子元素的前对齐符对齐

// 均分容器
sliceContainer: LBRACK content RBRACK;
// 根据子元素个数n将自身时间均分为n份，将子元素的前对齐符对齐至第n等分点 

// 容器内容
content:
	element* alignmentHeader? element* alignmentFooter? element*;

// 填充占位符
placeholder: DOT;

// 对齐标志符
alignmentHeader: COLON;
alignmentFooter: SEMI;
// 对齐标识符用于设置容器的对齐点，具体的对齐行为由容器的父容器决定

// 元数据
metadata:
	AT NAME EQUAL ID
	| AT TEMPO EQUAL (FLOAT | INT)
	| AT UNIT EQUAL FRACTION
	| AT METER EQUAL FRACTION
	| AT KEY EQUAL PITCH_LETTER
	| AT OCT EQUAL INT;

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