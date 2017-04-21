package com.vtcompression.algorithms.tools;

import com.vtcompression.utils.InputStreamReader;

import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

/**
 * Created by jvronsky on 11/15/16.
 */
public class FrequencyCalculator {

    private final Map<Symbol, Double> frequencyTable;

    private final SymbolReader symbolReader;

    /**
     * Creates calculator with an empty frequency table
     */
    public FrequencyCalculator() {
        frequencyTable = new LinkedHashMap<Symbol, Double>();
        this.symbolReader = DEFAULT_READER;
    }

    /**
     * Creates calculator with custom symbol reader.
     *
     * @param symbolReader to use for frequency computing
     */
    public FrequencyCalculator(SymbolReader symbolReader) {
        frequencyTable = new LinkedHashMap<Symbol, Double>();
        this.symbolReader = symbolReader;
    }

    /**
     * Compute the frequencies of all the symbols.
     */
    public void computeFrequencies(InputStreamReader reader) throws IOException {
        double total = 0.0;
        while (reader.hasMore()) {
            Symbol symbol = symbolReader.readSymbol(reader);
            frequencyTable.put(symbol, getFrequency(symbol) + 1.0);
            total += 1.0;
        }
        for (Symbol symbol : frequencyTable.keySet()) {
            frequencyTable.put(symbol, (getFrequency(symbol) / total));
        }
    }

    /**
     * Gets the frequency for a symbol
     *
     * @param symbol symbol to look for
     * @return the double value of frequency
     */
    public double getFrequency(String symbol) {
        return getFrequency(new Symbol(symbol));
    }

    private double getFrequency(Symbol symbol) {
        Double frequency = frequencyTable.get(symbol);
        return frequency == null ? 0 : frequency;
    }

    /**
     * Gets the frequency for a symbol
     *
     * @param symbol to look for its frequency
     * @return the double value of the frequency
     */
    public double getFrequency(byte[] symbol) {
        return getFrequency(new Symbol(symbol));
    }

    private static class Symbol {
        private byte[] symbol;

        public Symbol(byte[] symbol) {
            this.symbol = symbol;
        }

        public Symbol(String symbol) {
            this.symbol = symbol.getBytes();
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Symbol symbol1 = (Symbol) o;

            return Arrays.equals(symbol, symbol1.symbol);

        }

        @Override
        public int hashCode() {
            return Arrays.hashCode(symbol);
        }

        public byte[] getSymbol() {
            return symbol;
        }

        public String toString() {
            return new String(symbol);
        }
    }

    /**
     * This class is used to read symbols to use for frequencies.
     */
    public static abstract class SymbolReader {
        public abstract Symbol readSymbol(InputStreamReader inputStreamReader) throws IOException;
    }

    // Default SymbolReader reads character by character.
    public static final SymbolReader DEFAULT_READER = new SymbolReader() {
        @Override
        public Symbol readSymbol(InputStreamReader inputStreamReader) throws IOException {
            byte[] bytes = new byte[1];
            bytes[0] = (byte) inputStreamReader.readCharacter();
            return new Symbol(bytes);
        }
    };
}
