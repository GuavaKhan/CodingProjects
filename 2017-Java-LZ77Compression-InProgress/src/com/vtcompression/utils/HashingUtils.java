package com.vtcompression.utils;

import com.sun.org.apache.xerces.internal.impl.dv.util.HexBin;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

/**
 * Created by jvronsky on 11/14/16.
 */
public class HashingUtils {

    public static final String ALGORITHM = "SHA-256";

    public static byte[] hash(String string) throws IOException, NoSuchAlgorithmException {
        return hash(new InputStreamReader(new ByteArrayInputStream(string.getBytes())));
    }

    public static byte[] hash(File file) throws IOException, NoSuchAlgorithmException {
        return hash(new InputStreamReader(file));
    }

    /**
     * Hashes an inputStreamReader into a message digest
     * @param inputStreamReader the reader to digest
     * @return byte[] digest of the message
     * @throws NoSuchAlgorithmException
     * @throws IOException
     */
    public static byte[] hash(InputStreamReader inputStreamReader) throws NoSuchAlgorithmException, IOException {
        MessageDigest md = MessageDigest.getInstance(ALGORITHM);
        while(inputStreamReader.hasMore()) {
            md.update((byte) inputStreamReader.readCharacter());
        }
        return md.digest();
    }

    /**
     * Turn byte[] into a hex string.
     * @param hash to transfer
     * @return the hex string representation
     */
    public static String hashToHexString(byte[] hash) {
        return HexBin.encode(hash);
    }

    /**
     * Compare two hash values.
     * @param hash1
     * @param hash2
     * @return the boolean of their comparison
     */
    public static boolean compareHashes(byte[] hash1, byte[] hash2) {
        return Arrays.equals(hash1, hash2);
    }

}
