package com.vtcompression.algorithms;

import com.vtcompression.utils.InputStreamReader;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import com.vtcompression.utils.L;
import javafx.util.Pair;
import com.vtcompression.utils.Triple;

/**
 * Created by parker on 11/14/2016.
 */
public class LZ77 extends FileCompressionAlgorithm{


    private char currentByte;
    private int lookaheadWindowSize;
    private int historyWindowSize;
    private int offset;

    private String lookaheadBuffer;
    private String historyBuffer;
    private String match;
    private String outputCode;
    private OutputStream outputStream;


    public LZ77() {
        lookaheadWindowSize = 15;
        historyWindowSize = 60  ;
        currentByte = '0';
        offset = 0;

        lookaheadBuffer = "";
        historyBuffer = "";
        match = "";
        outputCode="";
    }

    public void compress(InputStreamReader inputFile, OutputStream outputFile) throws IOException, IllegalArgumentException {
        L.info("Begin Compression");
        if(outputFile == null){
            throw new IllegalArgumentException("Must specify an output file");
        }
        this.outputStream = outputFile;
        Pair<String, Integer> result; //String is the longest match, Integer is the offset
        int shiftAmount = 0;

        /**
         * Example algorithm
         * while( lookAheadBuffer not empty ) {
         *  get a pointer (position, match) to the longest match in the window for the lookAheadBuffer;
         *   output a (position, length, char()) triple;
         *   shift the window length+1 characters along;
         }
         */

        // Begin LZ77 Algorithm Loop. Currently testing out new functions.
        fillLookaheadBuffer(inputFile);
        while(!lookaheadBuffer.isEmpty()){
            currentByte = lookaheadBuffer.charAt(0);
            // Find Longest Match
            //L.info("Lookahead: " + lookaheadBuffer);
            //L.info("History: " + historyBuffer);
            result = findLongestMatch();
            //L.info("Current Byte: " + currentByte + ", Match: |" +  result.getKey() +"|, " + "Offset: " + result.getValue());
            // Output Tuplet
            if (result.getValue() > 0){
                codePointer(result.getValue(),result.getKey().length());
            }
            else {
                codeSymbol();
            }

            shiftAmount = Math.max(1, result.getKey().length());
            shiftBuffers(shiftAmount);

            fillLookaheadBuffer(inputFile);
            //L.info("");
        }

        outputStream.close();
        L.info("End Compression");
    }

    public void decompress(InputStreamReader inputFile, OutputStream outputFile) throws IOException, IllegalArgumentException {
        L.info("Begin Decompression");
        Triple<Integer, Integer, String> triple;
        String history = "";
        if(outputFile == null){
            throw new IllegalArgumentException("Must specify an output file");
        }
        this.outputStream = outputFile;

        //Read in file, for each code output regular text
        while (inputFile.hasMore()){
            triple = readNextPointer(inputFile);
            outputCode = "(" + triple.getFirst() + "," + triple.getSecond() + ")" + triple.getThird();
            //L.info(outputCode);
            if(triple.getFirst() == 0 && triple.getSecond() == 0){
                history += triple.getThird();
                if(history.length() > historyWindowSize){
                    history = history.substring(1);
                }
                outputStream.write(triple.getThird().getBytes());
            }
            else {
                //Write offset string to outputStream
                int offset = triple.getFirst();
                int length = triple.getSecond();
                //L.info("Offset: " + offset + ", Length: " + length + ", History Length: " + history.length());
                String outputStr = history.substring(history.length() - offset, history.length() - offset + length);
                history += outputStr;
                //L.info(outputStr);
                if(history.length() > historyWindowSize){
                    history = history.substring(length);
                }
                outputStream.write(outputStr.getBytes());
            }
        }

        outputStream.close();
        L.info("End Decompression");
    }

    private void fillLookaheadBuffer(InputStreamReader inputFile) throws IOException {
        while (inputFile.hasMore() && lookaheadBuffer.length() < lookaheadWindowSize){
            lookaheadBuffer += inputFile.readCharacter();
        }
        //L.info("Max size reached for lookaheadBuffer.");
        //L.info("Lookahead Buffer: " + lookaheadBuffer);
    }

    private void shiftBuffers(int shiftAmount) {
        //L.info("Shifting by " + shiftAmount + " character(s)");
        if (shiftAmount > lookaheadBuffer.length()) {
            shiftAmount = lookaheadBuffer.length();
        }
        String lookaheadShift = lookaheadBuffer.substring(0,shiftAmount);
        //L.info("Lookahead Shift: " + lookaheadShift);
        lookaheadBuffer = lookaheadBuffer.substring(shiftAmount);
        //L.info("Lookahead Buffer: " + lookaheadBuffer);
        historyBuffer += lookaheadShift;
        if (historyBuffer.length() > historyWindowSize){
            historyBuffer = historyBuffer.substring(historyBuffer.length() - historyWindowSize);
        }
        //L.info("History Buffer: " + historyBuffer);
        //L.info("Lookahead buffer size: " + lookaheadBuffer.length());
        //L.info("History buffer size: " + historyBuffer.length());
    }

    private Pair<String, Integer> findLongestMatch() {
        //L.info("Finding longest match.");
        String match = "";
        String currentSubstring = "";
        int offset = 0;
        int found = 0;

        for (int i = 1; i <= lookaheadBuffer.length(); i++) {
            //L.info("Current Substring: " + lookaheadBuffer.substring(0,i));
            currentSubstring = lookaheadBuffer.substring(0,i);
            found = historyBuffer.lastIndexOf(currentSubstring);
            if (found < 0) {
                break;
            }
            else {
                match = currentSubstring;
                offset = historyBuffer.length() - found;
            }
        }
        //L.info("Longest match found |" + match + "| with offset " + offset);
        return new Pair<String, Integer>(match, offset);
    }

    private void codeSymbol() throws IOException {
        outputCode = ("(0,0)" + lookaheadBuffer.charAt(0));
        //L.info(outputCode);
        outputStream.write(outputCode.getBytes());
    }

    private void codePointer(int offset, int length) throws IOException {
        outputCode = "(" + offset + "," + length + ")" + lookaheadBuffer.charAt(0);
        //L.info(outputCode);
        outputStream.write(outputCode.getBytes());
    }

    private Triple<Integer, Integer, String> readNextPointer(InputStreamReader inputFile) throws IOException{
        String lengthStr = "";
        String offsetStr = "";
        int offset = 0;
        int length = 0;
        String deviant = "";

        //eat parentheses
        inputFile.readCharacter();

        //start reading offset
        while(offsetStr.indexOf(',') == -1){
            offsetStr += inputFile.readCharacter();
        }
        offsetStr = offsetStr.substring(0, offsetStr.length() - 1);
        offset = Integer.valueOf(offsetStr);

        //start reading length
        while(lengthStr.indexOf(')') == -1){
            lengthStr += inputFile.readCharacter();
        }
        lengthStr = lengthStr.substring(0, lengthStr.length() - 1);
        length = Integer.valueOf(lengthStr);

        //read in deviant character
        deviant += inputFile.readCharacter();

        return new Triple<Integer, Integer, String>(offset, length, deviant);
    }

    private void decodeNextPointer(){

    }
    
}

