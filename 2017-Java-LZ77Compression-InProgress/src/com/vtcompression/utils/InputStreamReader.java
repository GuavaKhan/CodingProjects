package com.vtcompression.utils;

import java.io.*;


/**
 * This class help standardize the way InputStreams are read.
 * Created by jvronsky on 11/14/16.
 */
public class InputStreamReader {

    public static final int END_OF_STREAM = -1;

    private final InputStream inputStream;
    private int nextCharacter;
    private boolean hasMore;
    private File fileStream = null;

    /**
     * Creates InputStreamReader from the file in the path.
     *
     * @param filePath path to the file to open
     */
    public InputStreamReader(String filePath) throws IOException {
        this(new File(filePath));
    }

    /**
     * Creates InputStreamReader from a file object
     *
     * @param file the file object to read
     * @throws FileNotFoundException
     */
    public InputStreamReader(File file) throws IOException {
        this(new FileInputStream(file));
        this.fileStream = file;
    }

    /**
     * Creates InputStreamReader from an InputStream object
     *
     * @param inputStream the stream to read from
     * @throws IOException              if couldn't read or open a file
     * @throws IllegalArgumentException if inputStream was null
     */
    public InputStreamReader(InputStream inputStream) throws IOException {
        if (inputStream == null) {
            throw new IllegalArgumentException("InputStream cannot be null");
        }
        this.inputStream = inputStream;
        // Read the first character from the file, so we can process it from here onwards.
        int firstCharacter = inputStream.read();
        this.hasMore = (firstCharacter != END_OF_STREAM);
        // If the stream had nothing close it immediately.
        if (!this.hasMore) {
            L.warn("Stream was empty");
            inputStream.close();
        } else {
            this.nextCharacter = firstCharacter;
        }
    }

    /**
     * Reads the next character from stream. Read is only allowed if hasMore is set to true
     *
     * @return the character read or -1 if end of stream
     * @throws IOException           if could not read
     * @throws IllegalStateException if tried to read when no more characters available
     */
    public char readCharacter() throws IOException, IllegalStateException {
        assertInitializingReadAllowed();
        // Convert nextCharacter to a char value.
        char returnCharacter = (char) (this.nextCharacter & 0xFF);
        readAndCheckNext();
        return returnCharacter;
    }

    /**
     * Reads up to n character from the inputStream.
     * @param n the number of characters to read
     * @param result the StringBuilder to populate the with values read
     * @return the actual number of values read; this value will be between [0,n]
     * @throws IOException if could not read from file
     * @throws IllegalStateException if tried to initiate read when no values available
     */
    public int readCharacters(int n, StringBuilder result) throws IOException, IllegalStateException {
        assertInitializingReadAllowed();
        if(n > 0) {
            result.append(String.valueOf((char) (this.nextCharacter & 0xFF)));
            int readCount = 1;
            readAndCheckNext();
            while (readCount < n && hasMore) {
                result.append(String.valueOf((char) (this.nextCharacter & 0xFF)));
                readCount++;
                readAndCheckNext();
            }
            return readCount;
        } else {// if asked to read 0 return an empty string.
            return 0;
        }
    }

    /**
     * Reads and checks whether there is another character.
     * @throws IOException if cannot read
     */
    private void readAndCheckNext() throws IOException {
        this.nextCharacter = inputStream.read();
        if (nextCharacter == END_OF_STREAM) {
            setHasMore(false);
            close();
        }
    }

    /**
     * Close the inputStream.
     * @throws IOException
     */
    public void close() throws IOException {
        if(inputStream != null) {
            inputStream.close();
        }
    }

    /**
     * Resets the stream to the beginning
     * @throws IOException
     */
    public void reset() throws IOException {
        inputStream.reset();
        setHasMore(true);
        readAndCheckNext();
    }

    /**
     * Asserts that there are more values in the stream to initiate a read.
     * @throws IllegalStateException if tried to read when no characters available
     */
    private void assertInitializingReadAllowed() throws IllegalStateException {
        if (!hasMore) {
            throw new IllegalStateException("Cannot read when stream does not have more values");
        }
    }

    /**
     * Set the hasMore field.
     *
     * @param hasMore the new value for hasMore
     */
    private void setHasMore(boolean hasMore) {
        if (!this.hasMore && hasMore) {
            L.err("Stream cannot be changed from not having more to having more");
        }
        this.hasMore = hasMore;
    }

    /**
     * Returns whether this stream has more values.
     *
     * @return
     */
    public boolean hasMore() {
        return this.hasMore;
    }
}

