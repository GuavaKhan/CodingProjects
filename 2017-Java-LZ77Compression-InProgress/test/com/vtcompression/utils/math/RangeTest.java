package com.vtcompression.utils.math;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import static org.junit.Assert.assertEquals;

/**
 * Created by jvronsky on 11/15/16.
 */
public class RangeTest {

    @Rule
    public final ExpectedException illegalArgumentException = ExpectedException.none();

    @Test
    public void validRangeTest() {
        Range<Integer> range = new Range<>(1, 4);
        assertEquals(new Integer(1), range.getFirst());
        assertEquals(new Integer(4), range.getSecond());
    }

    @Test
    public void invalidRangeTest() {
        illegalArgumentException.expect(IllegalArgumentException.class);
        illegalArgumentException.expectMessage("First value of range must be smaller than second (1 < 4)");
        Range<Integer> range = new Range<>(4, 1);
    }


}
