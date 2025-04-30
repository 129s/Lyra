grammar LyraParser;

options {
	tokenVocab = LyraLexer;
}

root:
	refDeclare* (clip | sequenceClipContent) EOF; // 全局层级可省略大括号默认为串行Clip

// clip：片段
// 片段通过自身类型和子元素锚点来组合子元素
// clip的unit属性将传递给其子元素，因此clip时值由子元素共同决定
clip: sequenceClip | parallelClip;

// 串行Clip
// 依次将前一个子元素的后对齐符与后一个子元素的前对齐符对齐，子元素间首尾相接
// 可选：语句/前后对齐锚点
sequenceClip: '{' sequenceClipContent '}';
sequenceClipContent:
	propertyDeclare* sequenceHead sequenceBody sequenceTail;
sequenceHead: element*;
sequenceTail: element*;
sequenceBody: alignmentHeader? element* alignmentTailer?;

// 并行Clip
// 将所有子元素的前对齐符对齐
parallelClip: '(' propertyDeclare* element* ')';

// 对齐标志符
// 对齐标识符用于设置对齐点，具体的对齐行为由父元素决定
alignmentHeader: ':';
alignmentTailer: ';';

// 声明引用
refDeclare: '@' ref '=' element;

// 用于Clip声明属性
propertyDeclare: tonalProperty | riddimProperty;

// 调性属性
tonalProperty:
	'@key' WS? '=' WS? absolutePitch
	| '@key' WS? '=' WS? absolutePitch (WS SCALE)?; // 可选音阶，默认为major

// 节奏属性
riddimProperty:
	'@tempo' WS? '=' WS? (FLOAT | INT) // 速度，bpm，默认120
	| '@meter' WS? '=' WS? FRACTION // 拍号，默认4/4
	| '@unit' WS? '=' WS? FRACTION; // 单位时值，默认为1

// 元素
element: clip | container | ref;

// 容器
// 自身时值固定，默认由unit属性决定，可同后置时值修饰符改变
container: containerBody durationModifier?;

// 时值修饰符
durationModifier: '~' FRACTION;

// 容器主体
// 可以为布局/基本元素
containerBody: layout | basicElement;

// 布局
// 可按照一定节奏型排布子元素（基本元素，时值由布局根据自身类型和自身时值计算得出）
// 通过布局修饰符确定类型
// 默认为均分布局
layout: typeModifier? layoutBody;

// 布局主体
layoutBody: '[' container* ']';

// 布局类型修饰符
typeModifier: layoutType ':';

// 布局类型
layoutType:
	'slicer'; // 均分类型: 根据子元素个数n将自身时间均分为n份，将子元素的前对齐符对齐至第n等分点

// 基本元素
basicElement: pitch | chord | placeholder;

// 引用
ref: ID;

// 填充占位符
placeholder: '.';

// 音高
pitch: absolutePitch | relativePitch | REST;

// 绝对音高
absolutePitch:
	PITCH_MODIFIER* PITCH_LETTER OCTAVE_NUMBER OCTAVE_MODIFIER*
	| midiPitch;

// MIDI音高，用'!'与调内音高区分
midiPitch: '!' MIDI_NUMBER;

// 调内音高
relativePitch: PITCH_MODIFIER* SCALE_STEP OCTAVE_MODIFIER*;

// 休止符
REST: '0';

// 和弦
// 通过'与音高区分
chord: abosoluteChord | relativeChord;
abosoluteChord: absolutePitch '\'' chordBody;
relativeChord: relativePitch '\'' chordBody;

chordBody: (
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