import matplotlib
import matplotlib.pyplot as plt


nameArr = ["QuickSort.dat","QuickSortIterative.dat","MergeSort.dat",
        "MergeSortIterative.dat","HeapSort.dat","HeapSortIterative.dat"]
#ufc on espn 2 philadelphia
def readData():
        tupoftup = {}

        for datafile in nameArr:
                #print(datafile)
                comparisons = []
                swaps = []
                time = []
                n = []
                for line in open(datafile, 'r'):
                        #print(line);
                        values = [float(s) for s in line.split()]

                        if(values):
                                comparisons.append(values[0])
                                swaps.append(values[1])
                                time.append(values[2])
                                n.append(values[3])
                                #X.append(values[4])
                temp = {}
                temp["comparisons"] = comparisons
                temp["swaps"] = swaps
                temp["time"] = time
                temp["n"] = n

                tupoftup[datafile[:-4]] = temp #leave .datExtension

        return (tupoftup)

def plotGraph(tupoftup,sortnames,properties,title,yAxisName="Time(s)"):
        plt.figure(figsize=(10,10))
        plt.xlabel('No of items')
        plt.ylabel(yAxisName)
        
        for name in sortnames:
                for p in properties:
                        #print(name+" "+p)
                        #print(tupoftup[name][p])
                        plt.plot(tupoftup[name]["n"],tupoftup[name][p],label=name+"-"+p)

        plt.legend()
        #plt.show();

        plt.savefig(title)

tt = readData()
"""
for dim1 in tt:
        print(dim1)
        for dim2 in tt[dim1]:
                print(dim2)
                print(tt[dim1][dim2])
"""
sortnames = ["QuickSort","HeapSort","MergeSort",
                "QuickSortIterative","HeapSortIterative","MergeSortIterative"]

properties = ["comparisons","swaps","time","n"]

"""
#plotGraph(tt,[sortnames[0],sortnames[1],sortnames[2]],[properties[2]]);
plotGraph(tt,sortnames,[properties[0]],"AllComparisons.png",yAxisName="comparisons");
plotGraph(tt,sortnames,[properties[1]],"Allswaps.png",yAxisName="swaps");
plotGraph(tt,sortnames,[properties[2]],"Alltime.png",yAxisName="time");

plotGraph(tt,[sortnames[0],sortnames[1],sortnames[2]],[properties[0]],"RecursiveSortComparisons.png",yAxisName="comparisons");
plotGraph(tt,[sortnames[0],sortnames[1],sortnames[2]],[properties[1]],"RecursiveSortswaps.png",yAxisName="swaps");
plotGraph(tt,[sortnames[0],sortnames[1],sortnames[2]],[properties[2]],"RecursiveSorttime.png",yAxisName="time");

plotGraph(tt,[sortnames[3],sortnames[4],sortnames[5]],[properties[0]],"IterativeSortComparisons.png",yAxisName="comparisons");
plotGraph(tt,[sortnames[3],sortnames[4],sortnames[5]],[properties[1]],"IterativeSortswaps.png",yAxisName="swaps");
plotGraph(tt,[sortnames[3],sortnames[4],sortnames[5]],[properties[2]],"IterativeSorttime.png",yAxisName="time");
"""

plotGraph(tt,[sortnames[3],sortnames[4],sortnames[5]],[properties[0]],"IterativeSortComparisons.png",yAxisName="comparisons")
plotGraph(tt,[sortnames[0],sortnames[3]],[properties[2]],"qsVqsI.png",yAxisName="time(s)")
plotGraph(tt,[sortnames[1],sortnames[4]],[properties[2]],"msVmsI.png",yAxisName="time(s)")
plotGraph(tt,[sortnames[2],sortnames[5]],[properties[2]],"hsVhsI.png",yAxisName="time(s)")