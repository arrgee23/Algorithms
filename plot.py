import matplotlib;
import matplotlib.pyplot as plt;

X, Y = [], [];
for line in open('temp.dat', 'r'):
    values = [float(s) for s in line.split()];
    X.append(values[0]);
    Y.append(values[1]);
#print(X)
#plt.xlabel('Months');
#plt.ylabel('Books Read');
plt.plot(X, Y);
#plt.show();
plt.savefig('books_read.png');