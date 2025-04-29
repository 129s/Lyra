// Generated from l:/CppProject/vscode-extension/Lyra/LyraParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class LyraParserParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, COMMENT=1, WS=2, REST=3, TEMPO=4, METER=5, 
		UNIT=6, KEY=7, OCT=8, LBRACE=9, RBRACE=10, LBRACK=11, RBRACK=12, LPAREN=13, 
		RPAREN=14, AT=15, EQUAL=16, FLOAT=17, FRACTION=18, INT=19, PITCH_LETTER=20, 
		MODIFIER=21, OCTAVE_MOD=22, COLON=23, SEMI=24, REF=25, DOT=26, APOSTROPHE=27;
	public static final int
		RULE_root = 0, RULE_element = 1, RULE_container = 2, RULE_sequenceContainer = 3, 
		RULE_parallelContainer = 4, RULE_sliceContainer = 5, RULE_content = 6, 
		RULE_placeholder = 7, RULE_alignmentHeader = 8, RULE_alignmentFooter = 9, 
		RULE_metadata = 10, RULE_pitch = 11, RULE_chord = 12, RULE_chordQuality = 13, 
		RULE_chordSus = 14, RULE_chordAlteration = 15, RULE_chordExtension = 16, 
		RULE_chordModification = 17, RULE_chordSlash = 18;
	private static String[] makeRuleNames() {
		return new String[] {
			"root", "element", "container", "sequenceContainer", "parallelContainer", 
			"sliceContainer", "content", "placeholder", "alignmentHeader", "alignmentFooter", 
			"metadata", "pitch", "chord", "chordQuality", "chordSus", "chordAlteration", 
			"chordExtension", "chordModification", "chordSlash"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'M'", "'m'", "'0'", "'tempo'", "'meter'", "'unit'", "'key'", "'oct'", 
			"'{'", "'}'", "'['", "']'", "'('", "')'", "'@'", "'='", "'/'", "'add'", 
			"'no'", "'omit'", null, null, "':'", "';'", "'ref'", "'.'", "'''"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, "MODIFIER", "OCTAVE_MOD", 
			"COLON", "SEMI", "REF", "DOT", "APOSTROPHE"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "LyraParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public LyraParserParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class RootContext extends ParserRuleContext {
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode EOF() { return getToken(LyraParserParser.EOF, 0); }
		public RootContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_root; }
	}

	public final RootContext root() throws RecognitionException {
		RootContext _localctx = new RootContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_root);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(38);
			content();
			setState(39);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElementContext extends ParserRuleContext {
		public ContainerContext container() {
			return getRuleContext(ContainerContext.class,0);
		}
		public PitchContext pitch() {
			return getRuleContext(PitchContext.class,0);
		}
		public ChordContext chord() {
			return getRuleContext(ChordContext.class,0);
		}
		public PlaceholderContext placeholder() {
			return getRuleContext(PlaceholderContext.class,0);
		}
		public ElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_element; }
	}

	public final ElementContext element() throws RecognitionException {
		ElementContext _localctx = new ElementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_element);
		try {
			setState(45);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(41);
				container();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(42);
				pitch();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(43);
				chord();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(44);
				placeholder();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ContainerContext extends ParserRuleContext {
		public SequenceContainerContext sequenceContainer() {
			return getRuleContext(SequenceContainerContext.class,0);
		}
		public ParallelContainerContext parallelContainer() {
			return getRuleContext(ParallelContainerContext.class,0);
		}
		public SliceContainerContext sliceContainer() {
			return getRuleContext(SliceContainerContext.class,0);
		}
		public ContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_container; }
	}

	public final ContainerContext container() throws RecognitionException {
		ContainerContext _localctx = new ContainerContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_container);
		try {
			setState(50);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__8:
				enterOuterAlt(_localctx, 1);
				{
				setState(47);
				sequenceContainer();
				}
				break;
			case T__12:
				enterOuterAlt(_localctx, 2);
				{
				setState(48);
				parallelContainer();
				}
				break;
			case T__10:
				enterOuterAlt(_localctx, 3);
				{
				setState(49);
				sliceContainer();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SequenceContainerContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(LyraParserParser.LBRACE, 0); }
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode RBRACE() { return getToken(LyraParserParser.RBRACE, 0); }
		public SequenceContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sequenceContainer; }
	}

	public final SequenceContainerContext sequenceContainer() throws RecognitionException {
		SequenceContainerContext _localctx = new SequenceContainerContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_sequenceContainer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(52);
			match(T__8);
			setState(53);
			content();
			setState(54);
			match(T__9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ParallelContainerContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(LyraParserParser.LPAREN, 0); }
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(LyraParserParser.RPAREN, 0); }
		public ParallelContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parallelContainer; }
	}

	public final ParallelContainerContext parallelContainer() throws RecognitionException {
		ParallelContainerContext _localctx = new ParallelContainerContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_parallelContainer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(56);
			match(T__12);
			setState(57);
			content();
			setState(58);
			match(T__13);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SliceContainerContext extends ParserRuleContext {
		public TerminalNode LBRACK() { return getToken(LyraParserParser.LBRACK, 0); }
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode RBRACK() { return getToken(LyraParserParser.RBRACK, 0); }
		public SliceContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sliceContainer; }
	}

	public final SliceContainerContext sliceContainer() throws RecognitionException {
		SliceContainerContext _localctx = new SliceContainerContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_sliceContainer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(60);
			match(T__10);
			setState(61);
			content();
			setState(62);
			match(T__11);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ContentContext extends ParserRuleContext {
		public List<ElementContext> element() {
			return getRuleContexts(ElementContext.class);
		}
		public ElementContext element(int i) {
			return getRuleContext(ElementContext.class,i);
		}
		public AlignmentHeaderContext alignmentHeader() {
			return getRuleContext(AlignmentHeaderContext.class,0);
		}
		public AlignmentFooterContext alignmentFooter() {
			return getRuleContext(AlignmentFooterContext.class,0);
		}
		public ContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_content; }
	}

	public final ContentContext content() throws RecognitionException {
		ContentContext _localctx = new ContentContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_content);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(67);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(64);
					element();
					}
					} 
				}
				setState(69);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,2,_ctx);
			}
			setState(71);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COLON) {
				{
				setState(70);
				alignmentHeader();
				}
			}

			setState(76);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,4,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(73);
					element();
					}
					} 
				}
				setState(78);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,4,_ctx);
			}
			setState(80);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==SEMI) {
				{
				setState(79);
				alignmentFooter();
				}
			}

			setState(85);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 70789640L) != 0)) {
				{
				{
				setState(82);
				element();
				}
				}
				setState(87);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PlaceholderContext extends ParserRuleContext {
		public TerminalNode DOT() { return getToken(LyraParserParser.DOT, 0); }
		public PlaceholderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_placeholder; }
	}

	public final PlaceholderContext placeholder() throws RecognitionException {
		PlaceholderContext _localctx = new PlaceholderContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_placeholder);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(88);
			match(DOT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AlignmentHeaderContext extends ParserRuleContext {
		public TerminalNode COLON() { return getToken(LyraParserParser.COLON, 0); }
		public AlignmentHeaderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_alignmentHeader; }
	}

	public final AlignmentHeaderContext alignmentHeader() throws RecognitionException {
		AlignmentHeaderContext _localctx = new AlignmentHeaderContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_alignmentHeader);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(90);
			match(COLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AlignmentFooterContext extends ParserRuleContext {
		public TerminalNode SEMI() { return getToken(LyraParserParser.SEMI, 0); }
		public AlignmentFooterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_alignmentFooter; }
	}

	public final AlignmentFooterContext alignmentFooter() throws RecognitionException {
		AlignmentFooterContext _localctx = new AlignmentFooterContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_alignmentFooter);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(92);
			match(SEMI);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MetadataContext extends ParserRuleContext {
		public TerminalNode AT() { return getToken(LyraParserParser.AT, 0); }
		public TerminalNode TEMPO() { return getToken(LyraParserParser.TEMPO, 0); }
		public TerminalNode EQUAL() { return getToken(LyraParserParser.EQUAL, 0); }
		public TerminalNode FLOAT() { return getToken(LyraParserParser.FLOAT, 0); }
		public TerminalNode INT() { return getToken(LyraParserParser.INT, 0); }
		public TerminalNode UNIT() { return getToken(LyraParserParser.UNIT, 0); }
		public TerminalNode FRACTION() { return getToken(LyraParserParser.FRACTION, 0); }
		public TerminalNode METER() { return getToken(LyraParserParser.METER, 0); }
		public TerminalNode KEY() { return getToken(LyraParserParser.KEY, 0); }
		public TerminalNode PITCH_LETTER() { return getToken(LyraParserParser.PITCH_LETTER, 0); }
		public TerminalNode OCT() { return getToken(LyraParserParser.OCT, 0); }
		public MetadataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata; }
	}

	public final MetadataContext metadata() throws RecognitionException {
		MetadataContext _localctx = new MetadataContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_metadata);
		int _la;
		try {
			setState(114);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(94);
				match(T__14);
				setState(95);
				match(T__3);
				setState(96);
				match(T__15);
				setState(97);
				_la = _input.LA(1);
				if ( !(_la==T__16 || _la==T__18) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(98);
				match(T__14);
				setState(99);
				match(T__5);
				setState(100);
				match(T__15);
				setState(101);
				match(T__17);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(102);
				match(T__14);
				setState(103);
				match(T__4);
				setState(104);
				match(T__15);
				setState(105);
				match(T__17);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(106);
				match(T__14);
				setState(107);
				match(T__6);
				setState(108);
				match(T__15);
				setState(109);
				match(T__19);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(110);
				match(T__14);
				setState(111);
				match(T__7);
				setState(112);
				match(T__15);
				setState(113);
				match(T__18);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PitchContext extends ParserRuleContext {
		public TerminalNode PITCH_LETTER() { return getToken(LyraParserParser.PITCH_LETTER, 0); }
		public TerminalNode INT() { return getToken(LyraParserParser.INT, 0); }
		public TerminalNode MODIFIER() { return getToken(LyraParserParser.MODIFIER, 0); }
		public List<TerminalNode> OCTAVE_MOD() { return getTokens(LyraParserParser.OCTAVE_MOD); }
		public TerminalNode OCTAVE_MOD(int i) {
			return getToken(LyraParserParser.OCTAVE_MOD, i);
		}
		public TerminalNode REST() { return getToken(LyraParserParser.REST, 0); }
		public PitchContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pitch; }
	}

	public final PitchContext pitch() throws RecognitionException {
		PitchContext _localctx = new PitchContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_pitch);
		int _la;
		try {
			setState(133);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__18:
			case T__19:
			case MODIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(117);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==MODIFIER) {
					{
					setState(116);
					match(MODIFIER);
					}
				}

				setState(127);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case T__19:
					{
					setState(119);
					match(T__19);
					setState(124);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
					case 1:
						{
						setState(120);
						match(T__18);
						setState(122);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
						case 1:
							{
							setState(121);
							match(OCTAVE_MOD);
							}
							break;
						}
						}
						break;
					}
					}
					break;
				case T__18:
					{
					setState(126);
					match(T__18);
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(130);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==OCTAVE_MOD) {
					{
					setState(129);
					match(OCTAVE_MOD);
					}
				}

				}
				break;
			case T__2:
				enterOuterAlt(_localctx, 2);
				{
				setState(132);
				match(T__2);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordContext extends ParserRuleContext {
		public PitchContext pitch() {
			return getRuleContext(PitchContext.class,0);
		}
		public TerminalNode APOSTROPHE() { return getToken(LyraParserParser.APOSTROPHE, 0); }
		public List<ChordQualityContext> chordQuality() {
			return getRuleContexts(ChordQualityContext.class);
		}
		public ChordQualityContext chordQuality(int i) {
			return getRuleContext(ChordQualityContext.class,i);
		}
		public List<ChordSusContext> chordSus() {
			return getRuleContexts(ChordSusContext.class);
		}
		public ChordSusContext chordSus(int i) {
			return getRuleContext(ChordSusContext.class,i);
		}
		public List<ChordAlterationContext> chordAlteration() {
			return getRuleContexts(ChordAlterationContext.class);
		}
		public ChordAlterationContext chordAlteration(int i) {
			return getRuleContext(ChordAlterationContext.class,i);
		}
		public List<ChordExtensionContext> chordExtension() {
			return getRuleContexts(ChordExtensionContext.class);
		}
		public ChordExtensionContext chordExtension(int i) {
			return getRuleContext(ChordExtensionContext.class,i);
		}
		public List<ChordModificationContext> chordModification() {
			return getRuleContexts(ChordModificationContext.class);
		}
		public ChordModificationContext chordModification(int i) {
			return getRuleContext(ChordModificationContext.class,i);
		}
		public List<ChordSlashContext> chordSlash() {
			return getRuleContexts(ChordSlashContext.class);
		}
		public ChordSlashContext chordSlash(int i) {
			return getRuleContext(ChordSlashContext.class,i);
		}
		public ChordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chord; }
	}

	public final ChordContext chord() throws RecognitionException {
		ChordContext _localctx = new ChordContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_chord);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(135);
			pitch();
			setState(136);
			match(APOSTROPHE);
			setState(143); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					setState(143);
					_errHandler.sync(this);
					switch (_input.LA(1)) {
					case T__0:
					case T__1:
					case T__2:
					case T__3:
					case T__4:
					case T__5:
						{
						setState(137);
						chordQuality();
						}
						break;
					case T__6:
						{
						setState(138);
						chordSus();
						}
						break;
					case T__9:
					case T__10:
						{
						setState(139);
						chordAlteration();
						}
						break;
					case T__12:
					case T__13:
					case T__14:
					case T__15:
						{
						setState(140);
						chordExtension();
						}
						break;
					case T__17:
					case T__18:
					case T__19:
						{
						setState(141);
						chordModification();
						}
						break;
					case T__16:
						{
						setState(142);
						chordSlash();
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(145); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,15,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordQualityContext extends ParserRuleContext {
		public ChordQualityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chordQuality; }
	}

	public final ChordQualityContext chordQuality() throws RecognitionException {
		ChordQualityContext _localctx = new ChordQualityContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_chordQuality);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(147);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 126L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordSusContext extends ParserRuleContext {
		public ChordSusContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chordSus; }
	}

	public final ChordSusContext chordSus() throws RecognitionException {
		ChordSusContext _localctx = new ChordSusContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_chordSus);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(149);
			match(T__6);
			setState(151);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				{
				setState(150);
				_la = _input.LA(1);
				if ( !(_la==T__7 || _la==T__8) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordAlterationContext extends ParserRuleContext {
		public ChordAlterationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chordAlteration; }
	}

	public final ChordAlterationContext chordAlteration() throws RecognitionException {
		ChordAlterationContext _localctx = new ChordAlterationContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_chordAlteration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(153);
			_la = _input.LA(1);
			if ( !(_la==T__9 || _la==T__10) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(154);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 61440L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordExtensionContext extends ParserRuleContext {
		public ChordExtensionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chordExtension; }
	}

	public final ChordExtensionContext chordExtension() throws RecognitionException {
		ChordExtensionContext _localctx = new ChordExtensionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_chordExtension);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(156);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 122880L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(162);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				{
				setState(157);
				match(T__16);
				setState(159);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==T__9 || _la==T__10) {
					{
					setState(158);
					_la = _input.LA(1);
					if ( !(_la==T__9 || _la==T__10) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
				}

				setState(161);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 61440L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordModificationContext extends ParserRuleContext {
		public ChordModificationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chordModification; }
	}

	public final ChordModificationContext chordModification() throws RecognitionException {
		ChordModificationContext _localctx = new ChordModificationContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_chordModification);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(164);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 1835008L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			setState(165);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 94976L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ChordSlashContext extends ParserRuleContext {
		public PitchContext pitch() {
			return getRuleContext(PitchContext.class,0);
		}
		public TerminalNode REST() { return getToken(LyraParserParser.REST, 0); }
		public ChordSlashContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chordSlash; }
	}

	public final ChordSlashContext chordSlash() throws RecognitionException {
		ChordSlashContext _localctx = new ChordSlashContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_chordSlash);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(167);
			match(T__16);
			setState(170);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				{
				setState(168);
				pitch();
				}
				break;
			case 2:
				{
				setState(169);
				match(T__2);
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u001b\u00ad\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001"+
		"\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004"+
		"\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007"+
		"\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b"+
		"\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007"+
		"\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007"+
		"\u0012\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0003\u0001.\b\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0003\u00023\b\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0006\u0005\u0006B\b\u0006\n\u0006"+
		"\f\u0006E\t\u0006\u0001\u0006\u0003\u0006H\b\u0006\u0001\u0006\u0005\u0006"+
		"K\b\u0006\n\u0006\f\u0006N\t\u0006\u0001\u0006\u0003\u0006Q\b\u0006\u0001"+
		"\u0006\u0005\u0006T\b\u0006\n\u0006\f\u0006W\t\u0006\u0001\u0007\u0001"+
		"\u0007\u0001\b\u0001\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001\n\u0001\n"+
		"\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0003\ns\b"+
		"\n\u0001\u000b\u0003\u000bv\b\u000b\u0001\u000b\u0001\u000b\u0001\u000b"+
		"\u0003\u000b{\b\u000b\u0003\u000b}\b\u000b\u0001\u000b\u0003\u000b\u0080"+
		"\b\u000b\u0001\u000b\u0003\u000b\u0083\b\u000b\u0001\u000b\u0003\u000b"+
		"\u0086\b\u000b\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f\u0001\f"+
		"\u0001\f\u0004\f\u0090\b\f\u000b\f\f\f\u0091\u0001\r\u0001\r\u0001\u000e"+
		"\u0001\u000e\u0003\u000e\u0098\b\u000e\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0003\u0010\u00a0\b\u0010\u0001\u0010"+
		"\u0003\u0010\u00a3\b\u0010\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0012"+
		"\u0001\u0012\u0001\u0012\u0003\u0012\u00ab\b\u0012\u0001\u0012\u0000\u0000"+
		"\u0013\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018"+
		"\u001a\u001c\u001e \"$\u0000\b\u0002\u0000\u0011\u0011\u0013\u0013\u0001"+
		"\u0000\u0001\u0006\u0001\u0000\b\t\u0001\u0000\n\u000b\u0001\u0000\f\u000f"+
		"\u0001\u0000\r\u0010\u0001\u0000\u0012\u0014\u0003\u0000\b\t\f\u000e\u0010"+
		"\u0010\u00b7\u0000&\u0001\u0000\u0000\u0000\u0002-\u0001\u0000\u0000\u0000"+
		"\u00042\u0001\u0000\u0000\u0000\u00064\u0001\u0000\u0000\u0000\b8\u0001"+
		"\u0000\u0000\u0000\n<\u0001\u0000\u0000\u0000\fC\u0001\u0000\u0000\u0000"+
		"\u000eX\u0001\u0000\u0000\u0000\u0010Z\u0001\u0000\u0000\u0000\u0012\\"+
		"\u0001\u0000\u0000\u0000\u0014r\u0001\u0000\u0000\u0000\u0016\u0085\u0001"+
		"\u0000\u0000\u0000\u0018\u0087\u0001\u0000\u0000\u0000\u001a\u0093\u0001"+
		"\u0000\u0000\u0000\u001c\u0095\u0001\u0000\u0000\u0000\u001e\u0099\u0001"+
		"\u0000\u0000\u0000 \u009c\u0001\u0000\u0000\u0000\"\u00a4\u0001\u0000"+
		"\u0000\u0000$\u00a7\u0001\u0000\u0000\u0000&\'\u0003\f\u0006\u0000\'("+
		"\u0005\u0000\u0000\u0001(\u0001\u0001\u0000\u0000\u0000).\u0003\u0004"+
		"\u0002\u0000*.\u0003\u0016\u000b\u0000+.\u0003\u0018\f\u0000,.\u0003\u000e"+
		"\u0007\u0000-)\u0001\u0000\u0000\u0000-*\u0001\u0000\u0000\u0000-+\u0001"+
		"\u0000\u0000\u0000-,\u0001\u0000\u0000\u0000.\u0003\u0001\u0000\u0000"+
		"\u0000/3\u0003\u0006\u0003\u000003\u0003\b\u0004\u000013\u0003\n\u0005"+
		"\u00002/\u0001\u0000\u0000\u000020\u0001\u0000\u0000\u000021\u0001\u0000"+
		"\u0000\u00003\u0005\u0001\u0000\u0000\u000045\u0005\t\u0000\u000056\u0003"+
		"\f\u0006\u000067\u0005\n\u0000\u00007\u0007\u0001\u0000\u0000\u000089"+
		"\u0005\r\u0000\u00009:\u0003\f\u0006\u0000:;\u0005\u000e\u0000\u0000;"+
		"\t\u0001\u0000\u0000\u0000<=\u0005\u000b\u0000\u0000=>\u0003\f\u0006\u0000"+
		">?\u0005\f\u0000\u0000?\u000b\u0001\u0000\u0000\u0000@B\u0003\u0002\u0001"+
		"\u0000A@\u0001\u0000\u0000\u0000BE\u0001\u0000\u0000\u0000CA\u0001\u0000"+
		"\u0000\u0000CD\u0001\u0000\u0000\u0000DG\u0001\u0000\u0000\u0000EC\u0001"+
		"\u0000\u0000\u0000FH\u0003\u0010\b\u0000GF\u0001\u0000\u0000\u0000GH\u0001"+
		"\u0000\u0000\u0000HL\u0001\u0000\u0000\u0000IK\u0003\u0002\u0001\u0000"+
		"JI\u0001\u0000\u0000\u0000KN\u0001\u0000\u0000\u0000LJ\u0001\u0000\u0000"+
		"\u0000LM\u0001\u0000\u0000\u0000MP\u0001\u0000\u0000\u0000NL\u0001\u0000"+
		"\u0000\u0000OQ\u0003\u0012\t\u0000PO\u0001\u0000\u0000\u0000PQ\u0001\u0000"+
		"\u0000\u0000QU\u0001\u0000\u0000\u0000RT\u0003\u0002\u0001\u0000SR\u0001"+
		"\u0000\u0000\u0000TW\u0001\u0000\u0000\u0000US\u0001\u0000\u0000\u0000"+
		"UV\u0001\u0000\u0000\u0000V\r\u0001\u0000\u0000\u0000WU\u0001\u0000\u0000"+
		"\u0000XY\u0005\u001a\u0000\u0000Y\u000f\u0001\u0000\u0000\u0000Z[\u0005"+
		"\u0017\u0000\u0000[\u0011\u0001\u0000\u0000\u0000\\]\u0005\u0018\u0000"+
		"\u0000]\u0013\u0001\u0000\u0000\u0000^_\u0005\u000f\u0000\u0000_`\u0005"+
		"\u0004\u0000\u0000`a\u0005\u0010\u0000\u0000as\u0007\u0000\u0000\u0000"+
		"bc\u0005\u000f\u0000\u0000cd\u0005\u0006\u0000\u0000de\u0005\u0010\u0000"+
		"\u0000es\u0005\u0012\u0000\u0000fg\u0005\u000f\u0000\u0000gh\u0005\u0005"+
		"\u0000\u0000hi\u0005\u0010\u0000\u0000is\u0005\u0012\u0000\u0000jk\u0005"+
		"\u000f\u0000\u0000kl\u0005\u0007\u0000\u0000lm\u0005\u0010\u0000\u0000"+
		"ms\u0005\u0014\u0000\u0000no\u0005\u000f\u0000\u0000op\u0005\b\u0000\u0000"+
		"pq\u0005\u0010\u0000\u0000qs\u0005\u0013\u0000\u0000r^\u0001\u0000\u0000"+
		"\u0000rb\u0001\u0000\u0000\u0000rf\u0001\u0000\u0000\u0000rj\u0001\u0000"+
		"\u0000\u0000rn\u0001\u0000\u0000\u0000s\u0015\u0001\u0000\u0000\u0000"+
		"tv\u0005\u0015\u0000\u0000ut\u0001\u0000\u0000\u0000uv\u0001\u0000\u0000"+
		"\u0000v\u007f\u0001\u0000\u0000\u0000w|\u0005\u0014\u0000\u0000xz\u0005"+
		"\u0013\u0000\u0000y{\u0005\u0016\u0000\u0000zy\u0001\u0000\u0000\u0000"+
		"z{\u0001\u0000\u0000\u0000{}\u0001\u0000\u0000\u0000|x\u0001\u0000\u0000"+
		"\u0000|}\u0001\u0000\u0000\u0000}\u0080\u0001\u0000\u0000\u0000~\u0080"+
		"\u0005\u0013\u0000\u0000\u007fw\u0001\u0000\u0000\u0000\u007f~\u0001\u0000"+
		"\u0000\u0000\u0080\u0082\u0001\u0000\u0000\u0000\u0081\u0083\u0005\u0016"+
		"\u0000\u0000\u0082\u0081\u0001\u0000\u0000\u0000\u0082\u0083\u0001\u0000"+
		"\u0000\u0000\u0083\u0086\u0001\u0000\u0000\u0000\u0084\u0086\u0005\u0003"+
		"\u0000\u0000\u0085u\u0001\u0000\u0000\u0000\u0085\u0084\u0001\u0000\u0000"+
		"\u0000\u0086\u0017\u0001\u0000\u0000\u0000\u0087\u0088\u0003\u0016\u000b"+
		"\u0000\u0088\u008f\u0005\u001b\u0000\u0000\u0089\u0090\u0003\u001a\r\u0000"+
		"\u008a\u0090\u0003\u001c\u000e\u0000\u008b\u0090\u0003\u001e\u000f\u0000"+
		"\u008c\u0090\u0003 \u0010\u0000\u008d\u0090\u0003\"\u0011\u0000\u008e"+
		"\u0090\u0003$\u0012\u0000\u008f\u0089\u0001\u0000\u0000\u0000\u008f\u008a"+
		"\u0001\u0000\u0000\u0000\u008f\u008b\u0001\u0000\u0000\u0000\u008f\u008c"+
		"\u0001\u0000\u0000\u0000\u008f\u008d\u0001\u0000\u0000\u0000\u008f\u008e"+
		"\u0001\u0000\u0000\u0000\u0090\u0091\u0001\u0000\u0000\u0000\u0091\u008f"+
		"\u0001\u0000\u0000\u0000\u0091\u0092\u0001\u0000\u0000\u0000\u0092\u0019"+
		"\u0001\u0000\u0000\u0000\u0093\u0094\u0007\u0001\u0000\u0000\u0094\u001b"+
		"\u0001\u0000\u0000\u0000\u0095\u0097\u0005\u0007\u0000\u0000\u0096\u0098"+
		"\u0007\u0002\u0000\u0000\u0097\u0096\u0001\u0000\u0000\u0000\u0097\u0098"+
		"\u0001\u0000\u0000\u0000\u0098\u001d\u0001\u0000\u0000\u0000\u0099\u009a"+
		"\u0007\u0003\u0000\u0000\u009a\u009b\u0007\u0004\u0000\u0000\u009b\u001f"+
		"\u0001\u0000\u0000\u0000\u009c\u00a2\u0007\u0005\u0000\u0000\u009d\u009f"+
		"\u0005\u0011\u0000\u0000\u009e\u00a0\u0007\u0003\u0000\u0000\u009f\u009e"+
		"\u0001\u0000\u0000\u0000\u009f\u00a0\u0001\u0000\u0000\u0000\u00a0\u00a1"+
		"\u0001\u0000\u0000\u0000\u00a1\u00a3\u0007\u0004\u0000\u0000\u00a2\u009d"+
		"\u0001\u0000\u0000\u0000\u00a2\u00a3\u0001\u0000\u0000\u0000\u00a3!\u0001"+
		"\u0000\u0000\u0000\u00a4\u00a5\u0007\u0006\u0000\u0000\u00a5\u00a6\u0007"+
		"\u0007\u0000\u0000\u00a6#\u0001\u0000\u0000\u0000\u00a7\u00aa\u0005\u0011"+
		"\u0000\u0000\u00a8\u00ab\u0003\u0016\u000b\u0000\u00a9\u00ab\u0005\u0003"+
		"\u0000\u0000\u00aa\u00a8\u0001\u0000\u0000\u0000\u00aa\u00a9\u0001\u0000"+
		"\u0000\u0000\u00ab%\u0001\u0000\u0000\u0000\u0014-2CGLPUruz|\u007f\u0082"+
		"\u0085\u008f\u0091\u0097\u009f\u00a2\u00aa";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}