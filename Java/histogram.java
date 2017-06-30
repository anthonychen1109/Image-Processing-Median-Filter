import java.io.PrintStream;

public class histogram {
    int[] histogramAry;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    
    histogram(int maxVal){
        histogramAry = new int[maxVal+1];
        for(int i=0; i<=maxVal; i++){
            histogramAry[i] = 0;
        }//for
    }//constructor
    
    void computeHistogram(int data){
        histogramAry[data]++;
    }//computeHistogram
    
    public void printAry(PrintStream outFile1, int maxVal){
        for(int i=1; i<=maxVal;i++){
            if(histogramAry[i] >= 80){
                outFile1.println("(" + i + "):" + "80 +'s");
            }//if
            else{
            	outFile1.print("(" + i + "):" + histogramAry[i] + " ");
                for(int count=0; count<histogramAry[i]; count++){
                	outFile1.print("+");
                }//for
                outFile1.println();
            }//else
        }//for
    }//printAry
}
