package com.vtcompression.utils;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by jvronsky on 11/15/16.
 */
public class PairTest {

    @Test
    public void pairConstructorTest() {
        int testValue = 3;
        String testString = "hello";
        Pair<Integer, String> pair = new Pair<>(testValue, testString);
        assertEquals(new Integer(testValue), pair.getFirst());
        assertEquals(testString, pair.getSecond());
    }

    @Test
    public void pairEqualsTest() {
        int testValue1 = 3;
        int testValue2 = 4;
        String testString1 = "Hello";
        String testString2 = "not hello";
        Pair<Integer, String> pair1 = new Pair<>(testValue1, testString1);
        Pair<Integer, String> pair2 = new Pair<>(testValue1, testString1);
        Pair<Integer, String> pair3 = new Pair<>(testValue2, testString1);
        Pair<Integer, String> pair4 = new Pair<>(testValue1, testString2);
        Pair<Integer, String> pair5 = new Pair<>(testValue2, testString2);

        assertTrue(pair1.equals(pair1));
        assertTrue(pair1.equals(pair2));
        assertTrue(pair2.equals(pair1));

        assertFalse(pair1.equals(pair3));
        assertFalse(pair3.equals(pair1));
        assertFalse(pair1.equals(pair4));
        assertFalse(pair4.equals(pair1));
        assertFalse(pair1.equals(pair5));
        assertFalse(pair5.equals(pair4));
    }

    @Test
    public void pairHashTest() {
        int testValue1 = 3;
        int testValue2 = 4;
        String testString1 = "Hello";
        String testString2 = "not hello";
        Pair<Integer, String> pair1 = new Pair<>(testValue1, testString1);
        Pair<Integer, String> pair2 = new Pair<>(testValue1, testString1);
        Pair<Integer, String> pair3 = new Pair<>(testValue2, testString1);
        Pair<Integer, String> pair4 = new Pair<>(testValue1, testString2);
        Pair<Integer, String> pair5 = new Pair<>(testValue2, testString2);

        assertEquals(pair1.hashCode(), pair1.hashCode());
        assertEquals(pair1.hashCode(), pair2.hashCode());
        assertNotEquals(pair1.hashCode(), pair3.hashCode());
        assertNotEquals(pair1.hashCode(), pair4.hashCode());
        assertNotEquals(pair1.hashCode(), pair5.hashCode());
    }
}
