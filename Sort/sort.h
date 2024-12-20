#ifndef __SORT_H_
#define __SORT_H_

using namespace std;
namespace mySort
{
    /**
     * 排序算法     平均时间复杂度      最好时间复杂度      最坏时间复杂度      空间复杂度      稳定性      100000 组
     * 冒泡排序     O(n^2)             O(n)               O(n^2)             O(1)           稳定        23.009 s
     * 选择排序     O(n^2)             O(n^2)             O(n^2)             O(1)           不稳定      9.059  s
     * 插入排序     O(n^2)             O(n)               O(n^2)             O(1)           稳定        5.715  s
     * 希尔排序     O(n^1.3)           O(n)               O(n^2)             O(1)           不稳定      4.42   s
     *             依赖不同的增量序列 
     * 
     * 插入排序的效率最好，尤其是在数据已经趋于有序的情况下，采用插入排序效率最高，希尔排序是快速排序的改进。
     * 
     * 快速排序     O(nlgn)            O(nlgn)            O(n^2)             O(lgn)-O(n)    不稳定      0.011  s               
     * ——未优化
     * 归并排序     O(nlgn)            O(nlgn)            O(nlgn)            O(n)           稳定        0.015  s
     * ——含BUFF
     * 堆  排序     O(nlgn)            O(nlgn)            O(nlgn)            O(1)           不稳定      0.019  s
     * 
     * 虽然快速排序最坏的时间复杂度是 n^2，但是对产生的大量随机数排序基本是最快的，因为只有对基本有序（顺或逆）的数据排序，才会性能降低。
     * 快排和归并排序在排序过程中遍历元素时都是按顺序遍历，缓存命中率高，而堆排序是随机访问，缓存命中率低，更多的是在内存中读取。
     * 堆排序下沉操作做的无效比较多。例如：堆顶元素在与最后一个元素交换后，新的堆顶元素可能很小，需要一些冗余的比较。
     * 
     * 基数排序     O(nd)              O(nd)              O(nd)              O(n)            稳定      
     */
    void bubblingSort(int arr[], int len);
    void selectSort(int arr[], int len);
    void insertSort(int arr[], int len);
    void shellSort(int arr[], int len);

    /**
     * 快速排序及其优化
     * 优化一：随着快排算法执行，数据越来越趋于有序，在一定的范围内，可以采用插入排序代替快速排序。
     * 优化二：基准数的选择（左中右取中者）。
     * 优化三：随机数选择一个数作为基准数。
    */
    void quickSort(int arr[], int len);
    void quickSort1(int arr[], int len);
    void quickSort2(int arr[], int len);
    void quickSort3(int arr[], int len);

    /**
     * 归并排序：
     * 无额外内存辅助。
     * 有额外内存辅助。
     */
    void mergeSort(int arr[], int len);
    void mergeSortBuff(int arr[], int len);

    /**
     * 堆排序
     */
    void heapSort(int arr[], int len);

    /**
     * 基数排序（桶排序）：
     * 处理整数的排序，包括负数
     */
    void radixSort(int arr[], int len);

    /**
     * STL的sort
     * 首先是快速排序（基准数的选择为左中右取中者），在递归过程中，如果分割后待排序序列个数小于给定的阈值，则采用插入排序；
     * 如果递归深度到达一定程度，则转成堆排序，防止递归树向一边倾斜；
     */

    /**
     * 外排序：
     * 通过归并排序实现，具体思想如下：
     * 分割（分块）阶段：
     * 将大规模的待排序数据分割成多个较小的块，每个块的大小适合于内存加载。
     * 对每个小块的数据进行内部排序。由于数据量较小，这部分可以直接在内存中进行排序，常用的排序算法包括快速排序、归并排序或插入排序。
     * 合并阶段：
     * 将已经排序好的小块进行合并。合并时，可以利用磁盘 I/O 将排序好的小块逐步合并成一个更大的块，直到最终将所有的数据合并成一个有序的大文件。
     * 这个阶段通常采用 归并排序，特别是 K 路归并（K-way merge）来处理多个已经排序的块。
     * 将每个小文件 K 路归并后，继续对归并后的各个文件做 K 路归并。
     * 重复过程：
     * 如果经过合并后数据仍然较大，无法完全放入内存中，就重复上述过程，直到所有数据都被合并成一个完全有序的文件。
     */
}

#endif