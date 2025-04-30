grammar LyraParser;

options {
	tokenVocab = LyraLexer;
}

root:
	refDeclare* (clip | sequenceClipContent) EOF; // 全局层级可省略大括号默认为串行Clip

// 声明引用
refDeclare: REF EQUALS element;

// clip：片段
// 片段通过自身类型和子元素锚点来组合子元素
// clip的unit属性将传递给其子元素，因此clip时值由子元素共同决定
clip: sequenceClip | parallelClip;

// 串行Clip
// 依次将前一个子元素的后对齐符与后一个子元素的前对齐符对齐，子元素间首尾相接
// 可选：语句/前后对齐锚点
sequenceClip: LBRACE sequenceClipContent RBRACE;
sequenceClipContent:
	propertyDeclare* sequenceHead? sequenceBody sequenceTail?;
sequenceHead: element* alignmentHeader;
sequenceTail: alignmentTailer element*;
sequenceBody: element*;

// 并行Clip
// 将所有子元素的前对齐符对齐
parallelClip: LPAREN propertyDeclare* element* RPAREN;

// 对齐标志符
// 对齐标识符用于设置对齐点，具体的对齐行为由父元素决定
alignmentHeader: COLON;
alignmentTailer: SEMI;

// 用于Clip声明属性
propertyDeclare: tonalProperty | riddimProperty;

// 调性属性
tonalProperty:
	AT_KEY WS? EQUALS WS? absolutePitch
	| AT_KEY WS? EQUALS WS? absolutePitch (WS SCALE)?; // 可选音阶，默认为major

// 节奏属性
riddimProperty:
	AT_TEMPO WS? EQUALS WS? (FLOAT | INT) // 速度，bpm，默认120
	| AT_METER WS? EQUALS WS? FRACTION // 拍号，默认4/4
	| AT_UNIT WS? EQUALS WS? FRACTION; // 单位时值，默认为1

// 元素
element: clip | container | REF;

// 容器
// 自身时值固定，默认由unit属性决定，可同后置时值修饰符改变
container: containerBody OCTAVE_MODIFIER? durationModifier?;

// 时值修饰符
durationModifier: TILDE FRACTION;

// 容器主体
// 可以为布局/基本元素
containerBody: layout | basicElement;

// 布局
// 可按照一定节奏型排布子元素（基本元素，时值由布局根据自身类型和自身时值计算得出）
// 通过布局修饰符确定类型
// 默认为均分布局
layout: typeModifier? layoutBody;

// 布局主体
layoutBody: LBRACK container* RBRACK;

// 布局类型修饰符
typeModifier: layoutType COLON;

// 布局类型
layoutType: SLICER; // 均分类型: 根据子元素个数n将自身时间均分为n份，将子元素的前对齐符对齐至第n等分点

// 基本元素
basicElement: chord | pitch | placeholder;

// 填充占位符
placeholder: DOT;

// 和弦
// 通过'与音高区分
chord: relativePitch APOSTROPHE chordBody;

chordBody: chordQuality alteration* tension* inversion?;

chordQuality:
	MAJOR_CHORD
	| MINOR_CHORD
	| DIM_CHORD
	| AUG_CHORD
	| SUS
	| EXTENSION; // 单独数字默认作为属和弦

// 音高
pitch: absolutePitch | relativePitch | REST;
relativePitch: pitchName | tonalPitch;

// 绝对音高
absolutePitch: pitchName OCTAVE_NUMBER;

// 音名
pitchName: PITCH_MODIFIER* PITCH_LETTER;

// 调内音高
tonalPitch: PITCH_MODIFIER* SCALE_STEP;

alteration: ALTERATION;
tension: (ADD | NO) EXTENSION;
inversion: SLASH absolutePitch;