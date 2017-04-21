package com.vtcompression.utils;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;

/**
 * Created by jvronsky on 11/14/16.
 */
public class InputStreamReaderTest {

    // Values used for testing.
    public final static String testString = "ab123456789";
    public final static String emptyString = "";

    @Rule
    public final ExpectedException illegalStateException = ExpectedException.none();

    private InputStream testStream;
    private InputStream emptyStream;

    @Before
    public void setUp() {
        testStream = new ByteArrayInputStream(testString.getBytes());
        emptyStream = new ByteArrayInputStream(emptyString.getBytes());
    }

    /**
     * Tests whether the readCharacter() reads correctly.
     * @throws IOException
     */
    @Test
    public void readCharacterCorrectlyTest() throws IOException {
        com.vtcompression.utils.InputStreamReader reader = new com.vtcompression.utils.InputStreamReader(testStream);
        char[] expectedResults = {'a', 'b', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        int expectedIterationCount = expectedResults.length;
        int index = 0;
        while (reader.hasMore()) {
            assertEquals(expectedResults[index++], reader.readCharacter());
        }
        assertFalse(reader.hasMore());
        assertEquals(expectedIterationCount, index);
    }

    /**
     * Makes sure to test an exception is thrown when read illegally.
     * @throws IOException
     */
    @Test
    public void readCharacterIllegalStateExceptionTest() throws IOException {
        com.vtcompression.utils.InputStreamReader reader = new com.vtcompression.utils.InputStreamReader(emptyStream);
        illegalStateException.expect(IllegalStateException.class);
        illegalStateException.expectMessage("Cannot read when stream does not have more values");
        reader.readCharacter();
    }

    /**
     * Checks the readCharactes(int,StringBuilder) function operate correctly.
     * @throws IOException
     */
    @Test
    public void readCharactersCorrectlyTest() throws IOException {
        com.vtcompression.utils.InputStreamReader reader = new com.vtcompression.utils.InputStreamReader(testStream);
        assertCharactersRead(reader, 2, 2, "ab");
        assertCharactersRead(reader, 3, 3, "123");
        assertEquals('4', reader.readCharacter());
        assertCharactersRead(reader, 4, 4, "5678");
        assertCharactersRead(reader, 8, 1, "9");
    }

    /**
     * Helper method to test the readCharacters work.
     * @param reader reader to read from
     * @param n number of characters to read
     * @param expectedN expected characters to be read
     * @param expectedResults expected string to be read
     * @throws IOException
     */
    private void assertCharactersRead(com.vtcompression.utils.InputStreamReader reader, int n,
                                      int expectedN, String expectedResults) throws IOException {
        StringBuilder result = new StringBuilder();
        int charactersRead = 0;
        charactersRead = reader.readCharacters(n, result);
        assertEquals(expectedResults, result.toString());
        assertEquals(expectedN, charactersRead);
    }
}
