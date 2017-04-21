package com.vtcompression.utils;

import com.vtcompression.algorithms.LZ77;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import java.io.*;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

/**
 * Created by parker on 11/14/2016.
 */
public class LZ77Test {
    public final static String compInputFile = "test.txt";
    public final static String noFile = "";
    public final static String compOutputFile = "comp.out";
    public final static String decompInputFile = "test.comp";
    public final static String decompOutputFile = "decomp.out";

    private LZ77 compressor;

    @Before
    public void setUp() {
        compressor = new LZ77();
    }

    @Test
    public void compressTest() throws IOException {
        compressor.compress(new InputStreamReader(compInputFile), new FileOutputStream(compOutputFile));
    }

    @Test
    public void decompressTest() throws IOException {
        compressor.decompress(new InputStreamReader(decompInputFile), new FileOutputStream(decompOutputFile));
    }
}
