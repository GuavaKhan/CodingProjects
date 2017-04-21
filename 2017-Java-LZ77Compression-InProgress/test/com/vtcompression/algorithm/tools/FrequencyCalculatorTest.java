package com.vtcompression.algorithm.tools;

import com.vtcompression.algorithms.tools.FrequencyCalculator;
import com.vtcompression.utils.InputStreamReader;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

import static org.junit.Assert.assertEquals;

/**
 * Created by jvronsky on 11/15/16.
 */
public class FrequencyCalculatorTest {

    private static final double ALPHA = 0.000001;
    private static final String TEST_STRING = "HelloWorld";
    InputStreamReader testStream;

    @Test
    public void testFrequencyCountingTest() throws IOException {
        Map<String, Double> expectedFrequencies = new HashMap<>();
        expectedFrequencies.put("H", 0.1);
        expectedFrequencies.put("e", 0.1);
        expectedFrequencies.put("l", 0.3);
        expectedFrequencies.put("o", 0.2);
        expectedFrequencies.put("W", 0.1);
        expectedFrequencies.put("d", 0.1);
        expectedFrequencies.put("r", 0.1);
        testStream = new InputStreamReader(new ByteArrayInputStream(TEST_STRING.getBytes()));
        FrequencyCalculator frequencyCalculator = new FrequencyCalculator();
        frequencyCalculator.computeFrequencies(testStream);

        for(int i = 0; i < TEST_STRING.length(); i++) {
            assertEquals(expectedFrequencies.get(String.valueOf(TEST_STRING.charAt(i))),
                    frequencyCalculator.getFrequency(String.valueOf(TEST_STRING.charAt(i))), ALPHA);
        }
        assertEquals(0.0, frequencyCalculator.getFrequency("K".getBytes()), ALPHA);
    }


}
