#include<iostream>
#include<vector>
// using namespace std;

void moveZeroes(std::vector<int>& nums) {
    // save the number which is non-zero
    int count_zero = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 0)
            count_zero++;
    } 
    std::vector<int> ans;
    // 遍历每个元素,选择非0元素
    for(int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != 0)
            ans.push_back(nums[i]);
    }
    // 将0移至数组后面
    while(count_zero--)
    {
        nums.push_back(0);
    }

    for(int i = 0; i < ans.size(); i++)
    {
        nums[i] = ans[i];
    }
}

/*
慢指针方法：设置一个位置lastNonZeroFoundAt = 0,指向第一个元素，然后只有遇到非0元素时，此位置会向前移动并赋予上非0值，当循环到数组末尾时，此慢指针已到达所有的非0元素终点，而且这些元素
依旧保持原来的顺序，此时将原数组与此指针位置相差的位置上的元素补0即可。

1. 这种方法与上面的工作方式相同，即先满足一个需求，然后满足另一个需求。它以一种巧妙的方式做到了这一点。上述问题也可以用另一种方式描述，“将所有非 0 元素置于数组前面，保持它们的相对顺序相同”。
这是双指针的方法。由变量 “cur” 表示的快速指针负责处理新元素。如果新找到的元素不是 0，我们就在最后找到的非 0 元素之后记录它。最后找到的非 0 元素的位置由慢指针 “lastnonzerofoundat” 变量表示。
2. 当我们不断发现新的非 0 元素时，我们只是在 “lastnonzerofoundat+1” 第个索引处覆盖它们。此覆盖不会导致任何数据丢失，因为我们已经处理了其中的内容（如果它是非 0 的，则它现在已经写入了相应的索引，
或者如果它是 0，则稍后将进行处理）。
3. 在 “cur” 索引到达数组的末尾之后，我们现在知道所有非 0 元素都已按原始顺序移动到数组的开头。现在是时候满足其他要求了，“将所有 0 移动到末尾”。我们现在只需要在 “lastnonzerofoundat” 索引之后用 0 
填充所有索引。

链接：https://leetcode-cn.com/problems/move-zeroes/solution/yi-dong-ling-by-leetcode/
*/
void moveZeroes_v1(std::vector<int>& nums) {
    int lastNonZeroFoundAt = 0;
    // If the current element is not 0, then we need to
    // append it just in front of last non 0 element we found. 
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[lastNonZeroFoundAt++] = nums[i];
        }
    }
    // After we have finished processing new elements,
    // all the non-zero elements are already at beginning of array.
    // We just need to fill remaining array with 0's.
    for (int i = lastNonZeroFoundAt; i < nums.size(); i++) {
        nums[i] = 0;
    }
}

/*前一种方法的操作是局部优化的。例如，所有（除最后一个）前导零的数组：[0，0，0，…，0，1]。对数组执行多少写操作？对于前面的方法，它写 0 n-1n−1 次，这是不必要的。
我们本可以只写一次。怎么用？… 只需固定非 0 元素。

最优方法也是上述解决方案的一个细微扩展。一个简单的实现是，如果当前元素是非 0 的，那么它的正确位置最多可以是当前位置或者更早的位置。如果是后者，则当前位置最终将被非 0 或 0 占据，
该非 0 或 0 位于大于 “cur” 索引的索引处。我们马上用 0 填充当前位置，这样不像以前的解决方案，我们不需要在下一个迭代中回到这里。

*******将向前赋值操作，改为交换*******
换句话说，代码将保持以下不变：

1. 慢指针（lastnonzerofoundat）之前的所有元素都是非零的。
2. 当前指针和慢速指针之间的所有元素都是零。
因此，当我们遇到一个非零元素时，我们需要交换当前指针和慢速指针指向的元素，然后前进两个指针。如果它是零元素，我们只前进当前指针。
*/

void move_Zeros_v2(std::vector<int>& nums)
{
    for (int slow = 0, cur = 0; cur < nums.size(); cur++)
    {
        if (nums[cur] != 0)
            std::swap(nums[slow++], nums[cur]);
    }
}

int main()
{
    int myarray[] = {1, 2, 0, 3, 0,5,6,7,9,0,3};
    std::cout << sizeof(myarray) << std::endl;
    std::vector<int> nums (myarray, myarray + sizeof(myarray) / sizeof(int));
    std::cout << "The contents of nums are:";
    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
    {
        std::cout<< ' ' << *it;
    }
    std::cout << '\n';
    moveZeroes_v1(nums);
    std::cout << "The length of nums now are:" << nums.size() << std::endl;
    std::cout << "The contents of nums after moveZeros are:";
    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
    {
        std::cout<< ' ' << *it;
    }
    std::cout << '\n';
    return 0;
}