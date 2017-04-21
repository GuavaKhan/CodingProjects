package com.vtcompression;

import com.vtcompression.algorithms.DummyAlgorithm;
import com.vtcompression.utils.InputStreamReader;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.NoSuchAlgorithmException;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

/**
 * Created by jvronsky on 11/14/16.
 */
public class CompressionManagerTest {

    private static final String TEST_FILE = "./testFile" + System.currentTimeMillis() + ".txt";
    private static final String OUTPUT_FILE = "./outputFile" + System.currentTimeMillis() + ".txt";
    private static final String TEST_STRING = "Hello World";

    @BeforeClass
    public static void setUpClass() throws IOException {
        FileOutputStream fileOutputStream = new FileOutputStream(TEST_FILE);
        fileOutputStream.write(TEST_STRING.getBytes());
        fileOutputStream.close();
    }

    @AfterClass
    public static void destroyClass() {
        new File(TEST_FILE).delete();
        new File(OUTPUT_FILE).delete();
    }

    @Test
    public void executeTest() throws IOException, NoSuchAlgorithmException {
        CompressionManager compressionManager = new CompressionManager();
        compressionManager.addAlgorithm(new DummyAlgorithm());

        compressionManager.execute(new File(TEST_FILE), new File(OUTPUT_FILE));

        InputStreamReader inputStreamReader = new InputStreamReader(OUTPUT_FILE);
        String readInValue = readFile(inputStreamReader);
        assertEquals(TEST_STRING, readInValue);
        assertTrue(new File(OUTPUT_FILE).exists());
    }

    private String readFile(InputStreamReader inputStreamReader) throws IOException {
        String result = "";
        while(inputStreamReader.hasMore()) {
            result += inputStreamReader.readCharacter();
        }
        return result;
    }


}
