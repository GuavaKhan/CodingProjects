package com.vtcompression.utils;

import com.sun.org.apache.xerces.internal.impl.dv.util.HexBin;
import org.junit.Test;

import java.io.IOException;
import java.security.NoSuchAlgorithmException;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * Created by jvronsky on 11/14/16.
 */
public class HashingUtilsTest {

    @Test
    public void hashTest() throws IOException, NoSuchAlgorithmException {
        String expectedHash = "A591A6D40BF420404A011733CFB7B190D62C65BF0BCDA32B57B277D9AD9F146E";
        String testString = "Hello World";

        assertEquals(expectedHash, HexBin.encode(HashingUtils.hash(testString)));
    }

    @Test
    public void hashEqualsTest() throws IOException, NoSuchAlgorithmException {
        String expectedHash = "A591A6D40BF420404A011733CFB7B190D62C65BF0BCDA32B57B277D9AD9F146E";
        String testString = "Hello World";

        assertTrue(HashingUtils.compareHashes(HashingUtils.hash(testString), HashingUtils.hash(testString)));
        assertFalse(HashingUtils.compareHashes(HashingUtils.hash(testString), HashingUtils.hash(expectedHash)));
    }

    @Test
    public void hashToHexStringTest() throws IOException, NoSuchAlgorithmException {
        String expectedHash = "A591A6D40BF420404A011733CFB7B190D62C65BF0BCDA32B57B277D9AD9F146E";
        String testString = "Hello World";

        assertEquals(expectedHash, HashingUtils.hashToHexString(HashingUtils.hash(testString)));
    }
}
