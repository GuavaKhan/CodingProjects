package com.vtcompression.algorithms;

import java.io.*;

import com.vtcompression.utils.InputStreamReader;

/**
 * Created by jvronsky on 11/14/16.
 */public abstract class FileCompressionAlgorithm {

    public void compress(String inputFile, String outputFile) throws IOException {
        compress(new InputStreamReader(inputFile), new FileOutputStream(outputFile));
    }

    public void compress(File inputFile, File outputFile) throws IOException {
        compress(new InputStreamReader(inputFile), new FileOutputStream(outputFile));
    }

    public abstract void compress(InputStreamReader inputFile, OutputStream outputFile) throws IOException;

    public void decompress(String inputFile, String outputFile) throws IOException {
        decompress(new InputStreamReader(inputFile), new FileOutputStream(outputFile));
    }

    public void decompress(File inputFile, File outputFile) throws IOException {
        compress(new InputStreamReader(inputFile), new FileOutputStream(outputFile));
    }

    public abstract void decompress(InputStreamReader inputFile, OutputStream outputFile) throws IOException;
}

