package com.vtcompression.utils;

/**
 * Created by jvronsky on 11/15/16.
 */
public class Triple<T, Q, S> {

    protected T first;
    protected Q second;
    protected S third;

    protected Triple() {
        this.first = null;
        this.second = null;
        this.third = null;
    }

    public Triple(T first, Q second, S third) {
        this.first = first;
        this.second = second;
        this.third = third;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Triple<?, ?, ?> triple = (Triple<?, ?, ?>) o;

        if (first != null ? !first.equals(triple.first) : triple.first != null) return false;
        if (second != null ? !second.equals(triple.second) : triple.second != null) return false;
        return third != null ? third.equals(triple.third) : triple.third == null;
    }

    @Override
    //incomplete
    public int hashCode() {
        int result = first != null ? first.hashCode() : 0;
        result = 31 * result + (second != null ? second.hashCode() : 0);
        //need to hash third value
        return result;
    }

    public T getFirst() {
        return first;
    }

    public Q getSecond() {
        return second;
    }

    public S getThird() { return third; }
}
