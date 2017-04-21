package com.vtcompression.utils;

/**
 * This class provides utils for logging information.
 * Created by jvronsky on 11/14/16.
 */
public class L {

    // ANSI constants for colour printing.
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";

    /**
     * Logs information, if support ansi will print in green.
     * @param message the messages to log
     */
    public static void info(String message) {
        System.out.println(ANSI_GREEN + message + ANSI_RESET);
    }

    /**
     * logs a warning message, if support ansi will print in yellow.
     * @param message the message to log
     */
    public static void warn(String message) {
        System.out.println(ANSI_YELLOW + message + ANSI_RESET);
    }

    /**
     * logs an error, if support ansi will print in red. Also this will exit the program.
     * @param message the message to log
     */
    public static void err(String message) {
        System.out.println(ANSI_RED + message + ANSI_RESET);
        System.exit(1);
    }
}
