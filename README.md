# AvlTree

This program is able to read a set of integers from a file, dataX, and a set of ranges from a second file, rangeX,and, for each range [a, b] in rangeX, report the SUM of all the integers in dataX which are in the range [a, b].


As the integers are read from file dataX, insert them in a binary search tree. After all the integers have been inserted into the binary search tree, read the ranges from file rangeX and query the binary search tree to report the sum. For instance, if file dataX has the integers (3,−2, 2, 5, 2,−6, 1) and file rangeX has the ranges ([−3, 4], [0, 5]) then the output should be:


Range [-3,4]. Sum = 6.
Range [0,5]. Sum = 13.
The program runs in O(h) time where h is the height of the tree.The expected height of the tree is O(log2(n)).)
