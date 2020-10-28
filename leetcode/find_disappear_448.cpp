#include<iostream>
#include<vector>
#include<new>

using namespace std;

/*
题目描述：
给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。

找到所有在 [1, n] 范围之间没有出现在数组中的数字。

您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array
*/

/*创建一个长度为n的数组temp， 元素置为0
遍历nums数组，若元素出现则对应位置加一,最后temp数组为0的索引即未出现的数字。
*/
vector<int> findDisappearedNumbers(vector<int>& nums)
{
    int nums_size = nums.size();
    vector<int> temp(nums_size + 1);
    vector<int> ans;
    // int *temp = new (nothrow) int[nums_size];
    // int *temp = new int[nums_size + 1];
    // int *ans = new int[nums_size + 1];
    for (int i = 0; i < nums_size + 1; i++)
    {
        temp[i] == 0;
    }
    for (int i = 0; i < nums_size; i++)
    {
        int count = nums[i];
        temp[count] += 1;
    }
    for (int i = 1; i < nums_size + 1; i++)
    {
        int count = 0;
        if (temp[i] == 0)
            ans.push_back(i);        
    }
    return ans;
}


/*
1.将数组元素对应为索引的位置加n
2.遍历加n后的数组，若数组元素值小于等于n，则说明数组下标值不存在，即消失的数字*/

vector<int> findDisappearedNumbers_v1(vector<int>& nums) {
        vector<int> res;
        if(nums.empty()) return nums;
        for(int i=0;i<nums.size();i++)
        {
            int index=(nums[i]-1)%nums.size();
            nums[index]+=nums.size();
        }
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]<=nums.size())
                res.push_back(i+1);
        }
        return res;
    }


int main()
{
    // // the iterator constructor can also be used to construct from arrays:
    int testarray[] = {4,3,2,7,8,2,3,1};
    vector<int> test (testarray, testarray + sizeof(testarray) / sizeof(int));
    vector<int> ans;
    ans = findDisappearedNumbers(test);
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << ' ';
    return 0;
}