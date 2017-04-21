package com.vtcompression.algorithms;

import com.vtcompression.utils.InputStreamReader;

import java.io.*;

/**
 * Created by jvronsky on 11/14/16.
 */
public class DummyAlgorithm extends FileCompressionAlgorithm {
    @Override
    public void compress(InputStreamReader inputFile, OutputStream outputFile) throws IOException {
        int i = 0;
        while (inputFile.hasMore()) {
            char c = inputFile.readCharacter();
            outputFile.write(c);
        }
        outputFile.close();
    }

    @Override
    public void decompress(InputStreamReader inputFile, OutputStream outputFile) {

    }
}
