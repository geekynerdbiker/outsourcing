package edu.hanyang.submit;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.core.SimpleAnalyzer;
import org.apache.lucene.analysis.tokenattributes.CharTermAttribute;
import org.tartarus.snowball.ext.PorterStemmer;

import java.io.IOException;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;


public class HanyangSETokenizer1 implements Tokenizer {
    private Analyzer analyzer = null;
    private PorterStemmer s = null;

    /**
     * Tokenizer 객체를 생성하고 준비하는 단계
     */
    @Override
    public void setup() {
        analyzer = new SimpleAnalyzer();
        s = new PorterStemmer();
        // TODO: your code here...
    }

    /**
     * 입력 문장을 split 및 tokenizer하는 단계
     *
     * @param str
     * @return
     */
    @Override
    public List<String> split(String text) {
        List<String> result = new ArrayList<String>();
        try {
            TokenStream stream = analyzer.tokenStream(null, new StringReader(text));
            while (stream.incrementToken()) {
                result.add(stemString(
                        stream.getAttribute(
                                CharTermAttribute.class).toString()));
            }
            stream.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return result;
        // TODO: your code here...
    }

    private String stemString(String word) {
        s.setCurrent(word);
        s.stem();
        return s.getCurrent();
    }

    /**
     * Tokenizer 객체를 모두 닫는 단계
     */
    @Override
    public void clean() {
        analyzer.close();
        // TODO: your code here...
    }
}
