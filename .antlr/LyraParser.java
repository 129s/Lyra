// Generated from l:/JSProjects/lyra/docs/grammar2/LyraParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class LyraParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		WS=1, REST=2, METADATA_KEY=3, LBRACE=4, RBRACE=5, LBRACKET=6, RBRACKET=7, 
		LPAREN=8, RPAREN=9, METADATA_PREFIX=10, EQUALS=11, FLOAT=12, FRACTION=13, 
		INT=14, PITCH_LETTER=15, MODIFIER=16, OCTAVE_MOD=17, CHORD_QUALITY=18, 
		CHORD_SUS=19, CHORD_EXT=20, CHORD_ALTER=21, CHORD_MOD=22, CHORD_SLASH=23, 
		COLON=24, SEMI=25, DOT=26, EXTENSION=27, AT=28, EQ=29, TEMPO=30, METER=31, 
		UNIT=32, KEY=33, OCT=34, SLASH=35, NOTE=36, ACCIDENTAL=37;
	public static final int
		RULE_document = 0, RULE_container = 1, RULE_sequenceContainer = 2, RULE_uniformContainer = 3, 
		RULE_syncContainer = 4, RULE_content = 5, RULE_element = 6, RULE_note = 7, 
		RULE_chord = 8, RULE_metadata = 9, RULE_metadataKey = 10, RULE_metadataValue = 11, 
		RULE_rest = 12, RULE_placeholder = 13, RULE_alignmentMarker = 14;
	private static String[] makeRuleNames() {
		return new String[] {
			"document", "container", "sequenceContainer", "uniformContainer", "syncContainer", 
			"content", "element", "note", "chord", "metadata", "metadataKey", "metadataValue", 
			"rest", "placeholder", "alignmentMarker"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, "'0'", null, "'{'", "'}'", "'['", "']'", "'('", "')'", "'@'", 
			"'='", null, null, null, null, null, null, null, null, null, null, null, 
			null, "':'", "';'", "'.'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "WS", "REST", "METADATA_KEY", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", 
			"LPAREN", "RPAREN", "METADATA_PREFIX", "EQUALS", "FLOAT", "FRACTION", 
			"INT", "PITCH_LETTER", "MODIFIER", "OCTAVE_MOD", "CHORD_QUALITY", "CHORD_SUS", 
			"CHORD_EXT", "CHORD_ALTER", "CHORD_MOD", "CHORD_SLASH", "COLON", "SEMI", 
			"DOT", "EXTENSION", "AT", "EQ", "TEMPO", "METER", "UNIT", "KEY", "OCT", 
			"SLASH", "NOTE", "ACCIDENTAL"
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

	public LyraParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DocumentContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(LyraParser.EOF, 0); }
		public List<ContentContext> content() {
			return getRuleContexts(ContentContext.class);
		}
		public ContentContext content(int i) {
			return getRuleContext(ContentContext.class,i);
		}
		public DocumentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_document; }
	}

	public final DocumentContext document() throws RecognitionException {
		DocumentContext _localctx = new DocumentContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_document);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(33);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 335659348L) != 0)) {
				{
				{
				setState(30);
				content();
				}
				}
				setState(35);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(36);
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
	public static class ContainerContext extends ParserRuleContext {
		public SequenceContainerContext sequenceContainer() {
			return getRuleContext(SequenceContainerContext.class,0);
		}
		public UniformContainerContext uniformContainer() {
			return getRuleContext(UniformContainerContext.class,0);
		}
		public SyncContainerContext syncContainer() {
			return getRuleContext(SyncContainerContext.class,0);
		}
		public ContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_container; }
	}

	public final ContainerContext container() throws RecognitionException {
		ContainerContext _localctx = new ContainerContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_container);
		try {
			setState(41);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LBRACE:
				enterOuterAlt(_localctx, 1);
				{
				setState(38);
				sequenceContainer();
				}
				break;
			case LBRACKET:
				enterOuterAlt(_localctx, 2);
				{
				setState(39);
				uniformContainer();
				}
				break;
			case LPAREN:
				enterOuterAlt(_localctx, 3);
				{
				setState(40);
				syncContainer();
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
		public TerminalNode LBRACE() { return getToken(LyraParser.LBRACE, 0); }
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode RBRACE() { return getToken(LyraParser.RBRACE, 0); }
		public SequenceContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sequenceContainer; }
	}

	public final SequenceContainerContext sequenceContainer() throws RecognitionException {
		SequenceContainerContext _localctx = new SequenceContainerContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_sequenceContainer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(43);
			match(LBRACE);
			setState(44);
			content();
			setState(45);
			match(RBRACE);
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
	public static class UniformContainerContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(LyraParser.LBRACKET, 0); }
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode RBRACKET() { return getToken(LyraParser.RBRACKET, 0); }
		public UniformContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_uniformContainer; }
	}

	public final UniformContainerContext uniformContainer() throws RecognitionException {
		UniformContainerContext _localctx = new UniformContainerContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_uniformContainer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(47);
			match(LBRACKET);
			setState(48);
			content();
			setState(49);
			match(RBRACKET);
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
	public static class SyncContainerContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(LyraParser.LPAREN, 0); }
		public ContentContext content() {
			return getRuleContext(ContentContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(LyraParser.RPAREN, 0); }
		public SyncContainerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_syncContainer; }
	}

	public final SyncContainerContext syncContainer() throws RecognitionException {
		SyncContainerContext _localctx = new SyncContainerContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_syncContainer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(51);
			match(LPAREN);
			setState(52);
			content();
			setState(53);
			match(RPAREN);
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
		public List<MetadataContext> metadata() {
			return getRuleContexts(MetadataContext.class);
		}
		public MetadataContext metadata(int i) {
			return getRuleContext(MetadataContext.class,i);
		}
		public List<ElementContext> element() {
			return getRuleContexts(ElementContext.class);
		}
		public ElementContext element(int i) {
			return getRuleContext(ElementContext.class,i);
		}
		public ContentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_content; }
	}

	public final ContentContext content() throws RecognitionException {
		ContentContext _localctx = new ContentContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_content);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(58);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==AT) {
				{
				{
				setState(55);
				metadata();
				}
				}
				setState(60);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(62); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(61);
					element();
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(64); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,3,_ctx);
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
	public static class ElementContext extends ParserRuleContext {
		public NoteContext note() {
			return getRuleContext(NoteContext.class,0);
		}
		public ChordContext chord() {
			return getRuleContext(ChordContext.class,0);
		}
		public ContainerContext container() {
			return getRuleContext(ContainerContext.class,0);
		}
		public RestContext rest() {
			return getRuleContext(RestContext.class,0);
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
		enterRule(_localctx, 12, RULE_element);
		try {
			setState(71);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(66);
				note();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(67);
				chord();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(68);
				container();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(69);
				rest();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(70);
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
	public static class NoteContext extends ParserRuleContext {
		public TerminalNode PITCH_LETTER() { return getToken(LyraParser.PITCH_LETTER, 0); }
		public TerminalNode INT() { return getToken(LyraParser.INT, 0); }
		public TerminalNode MODIFIER() { return getToken(LyraParser.MODIFIER, 0); }
		public List<TerminalNode> OCTAVE_MOD() { return getTokens(LyraParser.OCTAVE_MOD); }
		public TerminalNode OCTAVE_MOD(int i) {
			return getToken(LyraParser.OCTAVE_MOD, i);
		}
		public RestContext rest() {
			return getRuleContext(RestContext.class,0);
		}
		public NoteContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_note; }
	}

	public final NoteContext note() throws RecognitionException {
		NoteContext _localctx = new NoteContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_note);
		int _la;
		try {
			setState(90);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case INT:
			case PITCH_LETTER:
			case MODIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(74);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==MODIFIER) {
					{
					setState(73);
					match(MODIFIER);
					}
				}

				setState(84);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case PITCH_LETTER:
					{
					setState(76);
					match(PITCH_LETTER);
					setState(81);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
					case 1:
						{
						setState(77);
						match(INT);
						setState(79);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,6,_ctx) ) {
						case 1:
							{
							setState(78);
							match(OCTAVE_MOD);
							}
							break;
						}
						}
						break;
					}
					}
					break;
				case INT:
					{
					setState(83);
					match(INT);
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(87);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==OCTAVE_MOD) {
					{
					setState(86);
					match(OCTAVE_MOD);
					}
				}

				}
				break;
			case REST:
				enterOuterAlt(_localctx, 2);
				{
				setState(89);
				rest();
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
		public NoteContext note() {
			return getRuleContext(NoteContext.class,0);
		}
		public TerminalNode CHORD_QUALITY() { return getToken(LyraParser.CHORD_QUALITY, 0); }
		public List<TerminalNode> EXTENSION() { return getTokens(LyraParser.EXTENSION); }
		public TerminalNode EXTENSION(int i) {
			return getToken(LyraParser.EXTENSION, i);
		}
		public ChordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_chord; }
	}

	public final ChordContext chord() throws RecognitionException {
		ChordContext _localctx = new ChordContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_chord);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(92);
			note();
			setState(93);
			match(CHORD_QUALITY);
			setState(97);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==EXTENSION) {
				{
				{
				setState(94);
				match(EXTENSION);
				}
				}
				setState(99);
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
	public static class MetadataContext extends ParserRuleContext {
		public MetadataKeyContext key;
		public MetadataValueContext value;
		public TerminalNode AT() { return getToken(LyraParser.AT, 0); }
		public TerminalNode EQ() { return getToken(LyraParser.EQ, 0); }
		public MetadataKeyContext metadataKey() {
			return getRuleContext(MetadataKeyContext.class,0);
		}
		public MetadataValueContext metadataValue() {
			return getRuleContext(MetadataValueContext.class,0);
		}
		public MetadataContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadata; }
	}

	public final MetadataContext metadata() throws RecognitionException {
		MetadataContext _localctx = new MetadataContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_metadata);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(100);
			match(AT);
			setState(101);
			((MetadataContext)_localctx).key = metadataKey();
			setState(102);
			match(EQ);
			setState(103);
			((MetadataContext)_localctx).value = metadataValue();
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
	public static class MetadataKeyContext extends ParserRuleContext {
		public TerminalNode TEMPO() { return getToken(LyraParser.TEMPO, 0); }
		public TerminalNode METER() { return getToken(LyraParser.METER, 0); }
		public TerminalNode UNIT() { return getToken(LyraParser.UNIT, 0); }
		public TerminalNode KEY() { return getToken(LyraParser.KEY, 0); }
		public TerminalNode OCT() { return getToken(LyraParser.OCT, 0); }
		public MetadataKeyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadataKey; }
	}

	public final MetadataKeyContext metadataKey() throws RecognitionException {
		MetadataKeyContext _localctx = new MetadataKeyContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_metadataKey);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(105);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 33285996544L) != 0)) ) {
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
	public static class MetadataValueContext extends ParserRuleContext {
		public MetadataValueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_metadataValue; }
	 
		public MetadataValueContext() { }
		public void copyFrom(MetadataValueContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FractionValueContext extends MetadataValueContext {
		public List<TerminalNode> INT() { return getTokens(LyraParser.INT); }
		public TerminalNode INT(int i) {
			return getToken(LyraParser.INT, i);
		}
		public TerminalNode SLASH() { return getToken(LyraParser.SLASH, 0); }
		public FractionValueContext(MetadataValueContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class KeyValueContext extends MetadataValueContext {
		public TerminalNode NOTE() { return getToken(LyraParser.NOTE, 0); }
		public TerminalNode ACCIDENTAL() { return getToken(LyraParser.ACCIDENTAL, 0); }
		public KeyValueContext(MetadataValueContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FloatValueContext extends MetadataValueContext {
		public TerminalNode FLOAT() { return getToken(LyraParser.FLOAT, 0); }
		public FloatValueContext(MetadataValueContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class IntValueContext extends MetadataValueContext {
		public TerminalNode INT() { return getToken(LyraParser.INT, 0); }
		public IntValueContext(MetadataValueContext ctx) { copyFrom(ctx); }
	}

	public final MetadataValueContext metadataValue() throws RecognitionException {
		MetadataValueContext _localctx = new MetadataValueContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_metadataValue);
		int _la;
		try {
			setState(116);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				_localctx = new FloatValueContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(107);
				match(FLOAT);
				}
				break;
			case 2:
				_localctx = new FractionValueContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(108);
				match(INT);
				setState(109);
				match(SLASH);
				setState(110);
				match(INT);
				}
				break;
			case 3:
				_localctx = new KeyValueContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(111);
				match(NOTE);
				setState(113);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==ACCIDENTAL) {
					{
					setState(112);
					match(ACCIDENTAL);
					}
				}

				}
				break;
			case 4:
				_localctx = new IntValueContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(115);
				match(INT);
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
	public static class RestContext extends ParserRuleContext {
		public TerminalNode REST() { return getToken(LyraParser.REST, 0); }
		public RestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_rest; }
	}

	public final RestContext rest() throws RecognitionException {
		RestContext _localctx = new RestContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_rest);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(118);
			match(REST);
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
		public TerminalNode DOT() { return getToken(LyraParser.DOT, 0); }
		public PlaceholderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_placeholder; }
	}

	public final PlaceholderContext placeholder() throws RecognitionException {
		PlaceholderContext _localctx = new PlaceholderContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_placeholder);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(120);
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
	public static class AlignmentMarkerContext extends ParserRuleContext {
		public TerminalNode COLON() { return getToken(LyraParser.COLON, 0); }
		public TerminalNode SEMI() { return getToken(LyraParser.SEMI, 0); }
		public AlignmentMarkerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_alignmentMarker; }
	}

	public final AlignmentMarkerContext alignmentMarker() throws RecognitionException {
		AlignmentMarkerContext _localctx = new AlignmentMarkerContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_alignmentMarker);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(122);
			_la = _input.LA(1);
			if ( !(_la==COLON || _la==SEMI) ) {
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

	public static final String _serializedATN =
		"\u0004\u0001%}\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002\u0002"+
		"\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002\u0005"+
		"\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002\b\u0007"+
		"\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002\f\u0007"+
		"\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0001\u0000\u0005\u0000 \b"+
		"\u0000\n\u0000\f\u0000#\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0003\u0001*\b\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0005\u00059\b"+
		"\u0005\n\u0005\f\u0005<\t\u0005\u0001\u0005\u0004\u0005?\b\u0005\u000b"+
		"\u0005\f\u0005@\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001"+
		"\u0006\u0003\u0006H\b\u0006\u0001\u0007\u0003\u0007K\b\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0003\u0007P\b\u0007\u0003\u0007R\b\u0007\u0001"+
		"\u0007\u0003\u0007U\b\u0007\u0001\u0007\u0003\u0007X\b\u0007\u0001\u0007"+
		"\u0003\u0007[\b\u0007\u0001\b\u0001\b\u0001\b\u0005\b`\b\b\n\b\f\bc\t"+
		"\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001\t\u0001\n\u0001\n\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b"+
		"r\b\u000b\u0001\u000b\u0003\u000bu\b\u000b\u0001\f\u0001\f\u0001\r\u0001"+
		"\r\u0001\u000e\u0001\u000e\u0001\u000e\u0000\u0000\u000f\u0000\u0002\u0004"+
		"\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u0000\u0002"+
		"\u0001\u0000\u001e\"\u0001\u0000\u0018\u0019\u0081\u0000!\u0001\u0000"+
		"\u0000\u0000\u0002)\u0001\u0000\u0000\u0000\u0004+\u0001\u0000\u0000\u0000"+
		"\u0006/\u0001\u0000\u0000\u0000\b3\u0001\u0000\u0000\u0000\n:\u0001\u0000"+
		"\u0000\u0000\fG\u0001\u0000\u0000\u0000\u000eZ\u0001\u0000\u0000\u0000"+
		"\u0010\\\u0001\u0000\u0000\u0000\u0012d\u0001\u0000\u0000\u0000\u0014"+
		"i\u0001\u0000\u0000\u0000\u0016t\u0001\u0000\u0000\u0000\u0018v\u0001"+
		"\u0000\u0000\u0000\u001ax\u0001\u0000\u0000\u0000\u001cz\u0001\u0000\u0000"+
		"\u0000\u001e \u0003\n\u0005\u0000\u001f\u001e\u0001\u0000\u0000\u0000"+
		" #\u0001\u0000\u0000\u0000!\u001f\u0001\u0000\u0000\u0000!\"\u0001\u0000"+
		"\u0000\u0000\"$\u0001\u0000\u0000\u0000#!\u0001\u0000\u0000\u0000$%\u0005"+
		"\u0000\u0000\u0001%\u0001\u0001\u0000\u0000\u0000&*\u0003\u0004\u0002"+
		"\u0000\'*\u0003\u0006\u0003\u0000(*\u0003\b\u0004\u0000)&\u0001\u0000"+
		"\u0000\u0000)\'\u0001\u0000\u0000\u0000)(\u0001\u0000\u0000\u0000*\u0003"+
		"\u0001\u0000\u0000\u0000+,\u0005\u0004\u0000\u0000,-\u0003\n\u0005\u0000"+
		"-.\u0005\u0005\u0000\u0000.\u0005\u0001\u0000\u0000\u0000/0\u0005\u0006"+
		"\u0000\u000001\u0003\n\u0005\u000012\u0005\u0007\u0000\u00002\u0007\u0001"+
		"\u0000\u0000\u000034\u0005\b\u0000\u000045\u0003\n\u0005\u000056\u0005"+
		"\t\u0000\u00006\t\u0001\u0000\u0000\u000079\u0003\u0012\t\u000087\u0001"+
		"\u0000\u0000\u00009<\u0001\u0000\u0000\u0000:8\u0001\u0000\u0000\u0000"+
		":;\u0001\u0000\u0000\u0000;>\u0001\u0000\u0000\u0000<:\u0001\u0000\u0000"+
		"\u0000=?\u0003\f\u0006\u0000>=\u0001\u0000\u0000\u0000?@\u0001\u0000\u0000"+
		"\u0000@>\u0001\u0000\u0000\u0000@A\u0001\u0000\u0000\u0000A\u000b\u0001"+
		"\u0000\u0000\u0000BH\u0003\u000e\u0007\u0000CH\u0003\u0010\b\u0000DH\u0003"+
		"\u0002\u0001\u0000EH\u0003\u0018\f\u0000FH\u0003\u001a\r\u0000GB\u0001"+
		"\u0000\u0000\u0000GC\u0001\u0000\u0000\u0000GD\u0001\u0000\u0000\u0000"+
		"GE\u0001\u0000\u0000\u0000GF\u0001\u0000\u0000\u0000H\r\u0001\u0000\u0000"+
		"\u0000IK\u0005\u0010\u0000\u0000JI\u0001\u0000\u0000\u0000JK\u0001\u0000"+
		"\u0000\u0000KT\u0001\u0000\u0000\u0000LQ\u0005\u000f\u0000\u0000MO\u0005"+
		"\u000e\u0000\u0000NP\u0005\u0011\u0000\u0000ON\u0001\u0000\u0000\u0000"+
		"OP\u0001\u0000\u0000\u0000PR\u0001\u0000\u0000\u0000QM\u0001\u0000\u0000"+
		"\u0000QR\u0001\u0000\u0000\u0000RU\u0001\u0000\u0000\u0000SU\u0005\u000e"+
		"\u0000\u0000TL\u0001\u0000\u0000\u0000TS\u0001\u0000\u0000\u0000UW\u0001"+
		"\u0000\u0000\u0000VX\u0005\u0011\u0000\u0000WV\u0001\u0000\u0000\u0000"+
		"WX\u0001\u0000\u0000\u0000X[\u0001\u0000\u0000\u0000Y[\u0003\u0018\f\u0000"+
		"ZJ\u0001\u0000\u0000\u0000ZY\u0001\u0000\u0000\u0000[\u000f\u0001\u0000"+
		"\u0000\u0000\\]\u0003\u000e\u0007\u0000]a\u0005\u0012\u0000\u0000^`\u0005"+
		"\u001b\u0000\u0000_^\u0001\u0000\u0000\u0000`c\u0001\u0000\u0000\u0000"+
		"a_\u0001\u0000\u0000\u0000ab\u0001\u0000\u0000\u0000b\u0011\u0001\u0000"+
		"\u0000\u0000ca\u0001\u0000\u0000\u0000de\u0005\u001c\u0000\u0000ef\u0003"+
		"\u0014\n\u0000fg\u0005\u001d\u0000\u0000gh\u0003\u0016\u000b\u0000h\u0013"+
		"\u0001\u0000\u0000\u0000ij\u0007\u0000\u0000\u0000j\u0015\u0001\u0000"+
		"\u0000\u0000ku\u0005\f\u0000\u0000lm\u0005\u000e\u0000\u0000mn\u0005#"+
		"\u0000\u0000nu\u0005\u000e\u0000\u0000oq\u0005$\u0000\u0000pr\u0005%\u0000"+
		"\u0000qp\u0001\u0000\u0000\u0000qr\u0001\u0000\u0000\u0000ru\u0001\u0000"+
		"\u0000\u0000su\u0005\u000e\u0000\u0000tk\u0001\u0000\u0000\u0000tl\u0001"+
		"\u0000\u0000\u0000to\u0001\u0000\u0000\u0000ts\u0001\u0000\u0000\u0000"+
		"u\u0017\u0001\u0000\u0000\u0000vw\u0005\u0002\u0000\u0000w\u0019\u0001"+
		"\u0000\u0000\u0000xy\u0005\u001a\u0000\u0000y\u001b\u0001\u0000\u0000"+
		"\u0000z{\u0007\u0001\u0000\u0000{\u001d\u0001\u0000\u0000\u0000\u000e"+
		"!):@GJOQTWZaqt";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}