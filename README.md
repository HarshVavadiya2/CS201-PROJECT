# CS201-PROJECT

#TEAM MEMBERS:
Vavadiya Harsh 2021CSB1139
Patel Het 2021CSB1119
Ayush Sahu 2021CSB1077

##Instructor:
Dr. Anil Shukla

##Mentoring Teaching Assistant:
Vinay Sir

APPLICATIONS & IMPLEMENTATION OF ZIP TREE AND BLOOM FILTER

##Project Summary:
We introduce the zip tree, a form of randomized binary search tree that integrates previous ideas into one practical, performant, and pleasant-to-implement package. A zip tree is a binary search tree in which each node has a numeric rank and the tree is (max)-heap-ordered with respect to ranks, with rank ties broken in favor of smaller keys. Zip trees are essentially treaps (Seidel and Aragon 1996), except that ranks are drawn from a geometric distribution instead of a uniform distribution, and we allow rank ties. These changes enable us to use fewer random bits per node. We perform insertions and deletions by unmerging and merging paths ("unzipping" and "zipping") rather than by doing rotations, which avoids some pointer changes and improves efficiency. The methods of zipping and unzipping take inspiration from previous top-down approaches to insertion and deletion (Stephenson 1980; Martínez and Roura 1998; Sprugnoli 1980). From a theoretical standpoint, this work provides two main results. First, zip trees require only O(loglogn) bits (with high probability) to represent the largest rank in an n-node binary search tree; previous data structures require O(logn) bits for the largest rank. Second, zip trees are naturally isomorphic to skip lists (Pugh 1990), and simplify the mapping of (Dean and Jones 2007) between skip lists and binary search trees.Bloom Filter is a probabilistic data structure which saves memory space and time efficiently, but the trade-off remains as false positives. It tells us if the value is definitely not in the input stream or maybe in the stream. Since Standard Bloom Filters do not support deleting elements various variants of Bloom Filters have been introduced. Due to the positives of Bloom Filters like compact summarization of streaming data, it has gained importance in applications that use higher volumes of data like in network traffic management, database management and cloud security. In this paper we implement a Bloom Filter to test membership of URLs and provide a warning to malicious websites or access to kid friendly websites. By creating a second Bloom Filter with maximized size we cross verify the query results of the first Bloom Filter to declare with absolute certainty of no false positive result.