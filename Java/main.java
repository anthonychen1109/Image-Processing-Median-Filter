import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintStream;
import java.util.Scanner;

public class main {
	public static void main(String args[]) throws FileNotFoundException{
		String input = args[0];
		String output = args[1];
		FileReader file = new FileReader(input);
		PrintStream outFile = new PrintStream(output);
		
		Scanner inFile = new Scanner(file);
	    
	    medianFilter MF = new medianFilter();
	    
	    MF.readImage(input); //read header
	    MF.loadImage(input); //load image into mirrorFramedAry
	    MF.mirrorFrame(outFile); //copy values to the frame
	    MF.getMedian(outFile); //get median
	    MF.printMedian(outFile);
	   System.out.println();
	    
	    FileReader file1 = new FileReader(args[1]);
		Scanner inFile1 = new Scanner(file1);
		PrintStream outFile1 = new PrintStream(args[2]);
		PrintStream outFile2 = new PrintStream(args[3]);

	    FileReader file2 = new FileReader(args[2]);

	    int data = 0;
	    int numRows;
	    int numCols;
	    int minVal;
	    int maxVal;
	    int[][] img;
	    int thr_value;
	    
	    numRows = inFile1.nextInt();
		System.out.println("numRows: " + numRows);
		numCols = inFile1.nextInt();
		System.out.println("numCols: " + numCols);
		minVal = inFile1.nextInt();
		System.out.println("minVal: " + minVal);
		maxVal = inFile1.nextInt();
		System.out.println("maxVal: " + maxVal);
	    
	    histogram myHistogram = new histogram(maxVal);
	 
	    Scanner input1 = new Scanner(System.in);
		System.out.println("enter a thr_value: ");
		thr_value = input1.nextInt();
	    
	    threshold myThreshold = new threshold(maxVal,numRows,numCols);
	    
	    img = new int[numRows][numCols];
	    
	    for(int i=0; i<numRows; i++){
	        for(int j=0; j<numCols; j++){
	            while(inFile1.hasNext()){
	                img[i][j] = inFile1.nextInt();
	                myHistogram.computeHistogram(img[i][j]);
	                myThreshold.computeThreshold(outFile2, img[i][j], thr_value, i, j);
	                break;
	            }//while
	        }//for j
	    }//for i
	    myHistogram.printAry(outFile1, maxVal);
	    //myThreshold.printThreshold(outFile2, numRows, numCols);
	    myThreshold.prettyPrint(outFile2, numRows, numCols, minVal, maxVal);
	    
	    outFile.close();
	}//main
}//class
