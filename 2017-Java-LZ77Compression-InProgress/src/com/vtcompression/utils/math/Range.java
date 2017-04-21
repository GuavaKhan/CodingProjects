package com.vtcompression.utils.math;

import com.vtcompression.utils.Pair;

/**
 * Created by jvronsky on 11/15/16.
 */
public class Range<T extends Comparable<T>> extends Pair<T, T> {

    public Range(T first, T second) {
        if(first.compareTo(second) > 0) {
            throw new IllegalArgumentException("First value of range must be smaller than second " +
                    "(" + second +  " < " + first + ")");
        }
        this.first = first;
        this.second = second;
    }
}
