package com.vtcompression.utils;

/**
 * Created by jvronsky on 11/15/16.
 */
public class Pair<T, Q> {

    protected T first;
    protected Q second;

    protected Pair() {
        this.first = null;
        this.second = null;
    }

    public Pair(T first, Q second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Pair<?, ?> pair = (Pair<?, ?>) o;

        if (first != null ? !first.equals(pair.first) : pair.first != null) return false;
        return second != null ? second.equals(pair.second) : pair.second == null;

    }

    @Override
    public int hashCode() {
        int result = first != null ? first.hashCode() : 0;
        result = 31 * result + (second != null ? second.hashCode() : 0);
        return result;
    }

    public T getFirst() {
        return first;
    }

    public Q getSecond() {
        return second;
    }
}
