package com.vtcompression;

import com.vtcompression.algorithms.FileCompressionAlgorithm;
import com.vtcompression.utils.HashingUtils;
import com.vtcompression.utils.L;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Created by jvronsky on 11/14/16.
 */
public class CompressionManager {

    private static final String DEFAULT_WORK_DIRECTORY = "/tmp/";
    private List<FileCompressionAlgorithm> compressionAlgorithmList;

    public CompressionManager() {
        compressionAlgorithmList = new ArrayList<>();
    }

    public void execute(File input, File output) throws IOException, NoSuchAlgorithmException {
        if(compressionAlgorithmList.size() == 0) {
            throw new IllegalStateException("Must add at least one algorithm before executing");
        }
        // Create working directory.
        String workingDirectoryString = makeWorkDirectory();
        L.info("Working in: " + workingDirectoryString);


        File previousFile = new File(workingDirectoryString + "/step0");
        File currentFile = null;
        Files.copy(Paths.get(input.getAbsolutePath()), new FileOutputStream(previousFile));
        int iteration = 1;
        // Execute all compression algorithms.
        for(FileCompressionAlgorithm algorithm : compressionAlgorithmList) {
            currentFile = new File(workingDirectoryString + "/step" + iteration);
            algorithm.compress(previousFile, currentFile);
            previousFile.delete();
            previousFile = currentFile;
            iteration++;
        }

        Files.copy(Paths.get(currentFile.getAbsolutePath()), new FileOutputStream(output));
        // Remove last file.
        currentFile.delete();
        // Delete the temporary directory.
        File workingDirectory = new File(workingDirectoryString);
        workingDirectory.delete();
        if(workingDirectory.exists()) {
            L.warn("Could not delete " + workingDirectoryString);
        }

        long originalFileSize = input.length();
        long compressedFileSize = output.length();
        double percentCompressed = ((double) (originalFileSize - compressedFileSize) / (double) originalFileSize) * 100.0;

        L.info("Compressed by: " + String.format("%1$.3f", percentCompressed) + "%");
    }

    private String makeWorkDirectory() throws IOException, NoSuchAlgorithmException {
        String currentTime = HashingUtils.hashToHexString(HashingUtils.hash(String.valueOf(System.currentTimeMillis())));
        File workDirectory = new File(DEFAULT_WORK_DIRECTORY + currentTime);
        if(!workDirectory.mkdirs()) {
            throw new IllegalStateException("Could not create directories");
        }
        return workDirectory.getAbsolutePath();
    }

    /**
     * Adds an algorithm to use in the manager.
     * @param fileCompressionAlgorithm the algorithm to add
     */
    public void addAlgorithm(FileCompressionAlgorithm fileCompressionAlgorithm) {
        compressionAlgorithmList.add(fileCompressionAlgorithm);
    }

}
