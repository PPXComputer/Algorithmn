// Created by Administrator on 2022/3/21.
//

#include <cmath>
#include <string>
#include <random>
#include <set>
#include <numeric>
#include <vector>
#include <dbg.h>
#include <fmt/core.h>

#include<unordered_map>
#include "Offer.h"

using std::vector;
using std::set;
using std::string;
using std::unordered_map;


int Offer::divide() {
    int a = 15, b = 2;
    bool negative = true;
    if (a < 0 and b < 0) negative = false;
    a = std::abs(a);
    b = std::abs(b);

    int answer = a / b;
    return 0;
}

int Offer::addBinary() {
    string first = "10";
    string second = "101111";
    size_t secondSize = second.size();
    size_t firstSize = first.size();
    std::string result;
    if (firstSize >= secondSize) {
        std::swap(first, second);
        std::swap(firstSize, secondSize);
    }

    bool isMetric = false;
    result.reserve(secondSize + 1);
    int firstIndex = firstSize - 1;
    int secondIndex = secondSize - 1;
    while (firstIndex >= 0) {
        int addNum = 0;
        if (isMetric) {
            addNum = first[firstIndex] + second[secondIndex] - '0' * 2 + 1;

        } else {
            addNum = first[firstIndex] + second[secondIndex] - '0' * 2;

        }
        dbg(addNum);
        if (addNum >= 2) {
            result.push_back(addNum + '0' - 2);
            isMetric = true;
        } else {
            result.push_back('0' + addNum);
            isMetric = false;
        }
        --firstIndex;
        --secondIndex;
    }

    dbg(result);
    while (secondIndex >= 0) {
        if (isMetric) {
            char addNum = 0;
            addNum = static_cast<char>(second[secondIndex] - '0' + 1);
            if (addNum == 2) {
                isMetric = true;
                result.push_back('0');
            } else {
                result.push_back('1');
                --secondIndex;
                while (secondIndex >= 0) {
                    result.push_back(second[secondIndex]);
                    --secondIndex;
                }
                isMetric = false;
            }
        } else {
            result.push_back(second[secondIndex]);
        }
        --secondIndex;
    }
    if (isMetric) {
        result.push_back('1');
    }


    std::reverse(result.begin(), result.end());
    dbg(result);


    vector<int> resultA;
    int newCapacity = 80;
    resultA.reserve(newCapacity);

    resultA.push_back(0);
    for (int i = 1; i < newCapacity; ++i) {
        if ((i & 1) == 1) { //奇数则 将当前的 存在的 转换为
            resultA.push_back(resultA[i >> 1] + 1);
        } else {
            resultA.push_back(resultA[i >> 1]);
        }
    }


    return 0;
}

void Offer::singleNum() {
    std::vector<int> nums{0, 1, 0, 1, 0, 1, 99};
    std::sort(nums.begin(), nums.end());
    int count = 1;
    int last = nums[0];
    for (auto start = nums.begin() + 1; start != nums.end(); ++start) {
        if (*start == last) {
            count++;
        } else {
            if (count == 1) {
                dbg(last);
                break;
            }
            count = 1;
            last = *start;
        }
    }
    //    dbg(nums.back());
    std::vector<std::string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    int n = words.size();
    int *masks = new int[n]{};
    for (int i = 0; i < n; ++i) {
        dbg(masks[i]);
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        int bitMask = 0;
        for (char c: words[i]) {
            bitMask |= (1 << (c - 'a'));
        }
        masks[i] = bitMask;
        dbg(masks[i]);
    }
    delete[] masks;
}

void Offer::threeSum() {
    //    std::unordered_map<int, int> mMap;
    //    for (int i: data) {
    //        mMap[i]++;
    //    }
    //    size_t size = data.size();
    //    vector<vector<int>> result;
    //    for (int i = 0; i + 2 < size; ++i) {
    //        int first = data[i];
    //        if (mMap[first] > 0) {
    //            --mMap[first];
    //            bool isSuccess = false;
    //            for (int j = i + 1; j + 1 < size; ++j) {
    //
    //                int second = data[j];
    //                if (mMap[second] > 0) {
    //                    --mMap[second];
    //                    int third = -i - j;
    //                    if (mMap[third] > 0) {
    //                        --mMap[third];
    //                        isSuccess = true;
    //                        result.emplace_back(std::vector<int>{first, second, third});
    //                    } else {
    //                        ++mMap[second];
    //                    }
    //                }
    //
    //            }
    //            if (not isSuccess) {
    //                ++mMap[first];
    //            }
    //        }
    //    }
    //threeSumFirstAnswer(data);


    std::vector<int> data{-2, 0, 1, 1, 2};
    // threeSumSecondAnswer(data);
    // 使用  sort 的方法找到的当前的 需要的 
    auto answer = [&data]() {
        std::sort(data.begin(), data.end());
        auto size = std::size(data);
        dbg(data);
        std::vector<std::vector<int>> results;
        int left = 1;
        int right = size - 1;
        for (int i = 0; i < size;) {
            int cur = data[i];

            dbg(i, left, right);
            bool isFind = false;
            while (left < right) {

                const string &basicString = fmt::format("{} {} {}", cur, data[left], data[right]);
                dbg(basicString);
                //找到当前符合的两个位置的
                int curResult = data[left] + data[right] + cur;

                if (curResult > 0) {
                    --right;
                } else if (curResult < 0) {
                    ++left;
                } else {
                    results.emplace_back(std::vector<int>{cur, data[left], data[right]});
                    isFind = true;
                    break;
                }
            }
            if (i + 1 < size and data[i + 1] == data[i]) {
                while (i + 1 < size and data[i + 1] == data[i])
                    ++i;
            } else {
                ++i;
            }
            if (isFind)
                right = right - 1;
            left = i + 1;
        }
        dbg(results);
    };

    auto otherAnswer = [&data] {
        std::vector<std::vector<int>> result;
        std::sort(data.begin(), data.end());
        auto size = std::size(data);

        // 有两种情况
        //1. 数字重复了   比如 -1,-1,0,0,1,1   -1,0,1 成功后 left从0 要到一个不等于0的地方
        //2. 当前数字匹配多次 -2,-1,0,2,3    -2 0 2   -2  -1  3 所以匹配成功后left 要转到下一个地方 不能直接打破循环

        for (int i = 0; i < size; ++i) {
            if (i > 0 and data[i - 1] == data[i]) continue;
            int left = i + 1;
            int right = size - 1;
            while (left < right) {
                int curResult = data[left] + data[i] + data[right];
                if (curResult == 0) {
                    result.emplace_back(std::vector<int>{data[i], data[left], data[right]});
                    while (left < right and data[left] == data[1 + left])++left;
                    ++left; //到达下一个 left 不相同的地方
                    continue;
                } else if (curResult < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
        dbg(result);
    };
    otherAnswer();
}

void Offer::threeSumSecondAnswer(vector<int> &data) {
    std::unordered_map<int, int> mMap;
    for (int i: data) {
        mMap[i]++;
    }
    std::vector<std::vector<int>> results;
    auto size = data.size();
    for (int i = 0; i < size; ++i) {
        int cur = data[i];
        if (mMap[cur] > 0) {
            --mMap[cur];
            bool isSuccess = false;
            for (int j = i + 1; j < size; ++j) {
                int first = data[j];
                if (mMap[first] > 0) {
                    --mMap[first];
                    const auto &iterator = mMap.find(-cur - first);
                    if (iterator != mMap.end() and ((*iterator).second > 0)) {
                        dbg(*iterator);
                        results.emplace_back(std::vector<int>{cur, first, (*iterator).first});
                        isSuccess = true;
                        continue;
                    }
                    ++mMap[first];
                }
            }

            if (not isSuccess) {
                ++mMap[cur];
            }
        }
        // 跳过重复的数据


    }
    dbg(results);
}

void Offer::threeSumFirstAnswer(std::vector<int> &data) {
    std::vector<std::vector<int>> result;
    std::sort(data.begin(), data.end());
    int size = data.size();
    for (int i = 0; i < size; ++i) {

        while (i + 1 < size and data[i] == data[i + 1]) {
            ++i;
        }
        int left = i + 1;
        int right = size - 1;
        while (left < right) {
            if (data[i] + data[left] + data[right] == 0) {
                dbg(data[i], data[left], data[right]);
                result.emplace_back(std::vector<int>{data[i], data[left], data[right]});
                left++;
                right--;
                continue;
            } else if (data[i] + data[left] + data[right] > 0) {
                --right;
            } else {
                ++left;
            }
        }
    }
}

void Offer::minSubArrayLen() {
    // 滑动窗口
    std::vector<int> data{2, 3, 1, 2, 4, 3};
    int target = 7;
    auto size = data.size();
    int right = 0;
    int curResult = data[0];
    int result = INT_MAX;
    int left = 0;
    while (left <= right and right < size) {
        if (curResult < target) {
            ++right;
            if (right < size)curResult += data[right];
        } else if (curResult >= target) {
            int curRange = right - left + 1;
            if (result > curRange) {
                result = curRange;
            }
            curResult -= data[left];
            ++left;
        }
    }
    dbg(result);

}

void Offer::numSubarrayProductLessThanK() {
    //给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。
    // 给定一个长度 1850 长度为4数组的个数相当于 1+2+3+4   不断进行[fast-slow+1]
    auto answer = [] {
        std::vector<int> data{10, 5, 2, 6};
        int k = 100;
        int fast = 0;
        int slow = 0;
        auto size = data.size();
        int tmp = 1;
        int result = 0;
        //如果当前要加入的fast 节点越界 证明没啥需要加的了 直接退出
        while (fast < size) {
            // 结果为 result += fast  -slow+1  (fast 已经自增了)
            if (data[fast] * tmp < k) {
                tmp *= data[fast];
                ++fast;
                result += fast - slow;
            } else {
                // tmp 除去 slow的部分 slow移动到  slow+1
                // 如果 当前的只有一个元素都不行的话 fast和 slow需要一起+1
                tmp /= data[slow];
                if (fast == slow) {
                    ++fast;
                }
                ++slow;
            }
        }

        return result;
    };
//    dbg(answer());
    auto answerSumk = [] {
        vector<int> data{1, 1, 1};
        int k = 2;
        int size = data.size();
        // 当数组元素存在负数的情况时  则滑动窗口可能存在失效的问题
        // 当前的 大于当前元素的时候 无法前进 或者回溯
        // 构建 辅助前缀和的数据
        int preSum = 0;

        // 问题就转化成 前缀和中相差 为k的数据对数有多个了
        std::unordered_map<int, int> map;
        map.reserve(size + 1);
        map[0] = 1;
        int result = 0;
        for (int i = 0; i < size; ++i) {
            preSum += data[i];
            dbg(map, preSum);
            const auto &findIterator = map.find(preSum - k);
            if (findIterator != map.end()) {
                result += findIterator->second;
            }
            ++map[preSum];
        }
        return result;
    };
    dbg(answerSumk());
}

void Offer::findMaxLengthWithSameCount() {
    //给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。
    // 不能使用滑动窗口 因为你不知道当前的 前进会增加0 还是后退会增加零
    // 0,1 相同数量 进行前缀的异或和
    std::vector<int> data{0, 1};
    auto size = data.size();
    {

        int countSum = data[0];
        std::vector<int> countCache;
        countCache.reserve(size + 1);
        countCache.push_back(0);
        int result = 0;
        for (int i = 0; i < size; ++i) {
            int cur = data[i] ? 1 : -1;
            countCache.push_back(cur + countCache[i]);
        }
        dbg(countCache);
    }

    {
        std::unordered_map<int, int> mMap;
        mMap.reserve(size + 1);
        mMap.insert({0, 0});
        int count = 0;
        int result = 0;
        for (int i = 0; i < size; ++i) {
            count += data[i] ? 1 : -1;

            auto iterator = mMap.find(count);
            if (iterator != mMap.end()) {
                result = std::max(result, i - iterator->second + 1);
            } else {
                // 插入当前元素 第一次遇到则 赋值为 i
                mMap[count] = i;
            }

        }
        dbg(result);
    }
}

int Offer::pivotIndex() {
    /*
     * 给你一个整数数组 nums ，请计算数组的 中心下标 。

    数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

     */
    auto a = [] {
        std::vector<int> data{1, 7, 3, 6, 5, 6};
        dbg(data);
        auto size = data.size();

        if (size == 1) return -1;

        std::vector<int> sumCache;
        sumCache.reserve(size);
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
            sumCache.emplace_back(sum);
        }
        if (sum - data[0] == 0) {
            return 0;
        }
        dbg(data);
        // 将当前的 下标中索引求出
        dbg(sumCache);
        for (int i = 1; i < size; ++i) {
            dbg(sum - sumCache[i], sumCache[i - 1]);
            if (sum - sumCache[i] == sumCache[i - 1])return i;
        }
        return -1;
    };
    auto b = [] {
        std::vector<int> data{1, 7, 3, 6, 5, 6};
        auto size = data.size();
        int total = std::accumulate(data.begin(), data.end(), 0);
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i];
            if (total - sum == sum - data[i]) {
                return i;
            }
        }
        return -1;
    };
//    return a();

    std::vector<std::vector<int>> sumCache{};
    sumCache.emplace_back(std::vector<int>{-4});
    sumCache.emplace_back(std::vector<int>{-5});
    int row = sumCache.size();
    int col = sumCache[0].size();
    for (int i = 0; i < row; ++i) {
        for (int j = 1; j < col; ++j) {
            sumCache[i][j] += sumCache[i][j - 1];
        }
    }
    int result = 0;
    int row1 = 0;
    std::random_device device; //输出机器级别的随机数
    std::default_random_engine e{device()}; //固定好种子后
    // 将当前的 随机数发生器传给 分布实现去
    std::binomial_distribution<int> distribution(3, 2);
    int col1 = distribution(e) % 2 ? 0 : 1;
    int row2 = 0;
    int col2 = 1;
    for (int i = row1; i <= row2; ++i) {
        if (col1 != 0) {
            result += sumCache[i][col2] - sumCache[i][col1 - 1];
        } else {
            result += sumCache[i][col2];
        }
    }
    dbg(result);
    return 0;
}

int Offer::NumMatrix() {
    vector<vector<int>> matrix{{-4, -5},
                               {1,  2}};
    int row = matrix.size();
    int col = matrix[0].size();
    auto answer = [&matrix, row, col] {

        std::vector<std::vector<int>> preSum(row + 1, std::vector<int>(col + 1));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                preSum[i + 1][j + 1] = preSum[i][j + 1] + preSum[i + 1][j] - preSum[i][j] + matrix[i][j];
            }
        }

        auto sumRegion = [&](int row1, int col1, int row2, int col2) {
            ++row1;
            ++col1;
            ++row2;
            ++col2;
            return preSum[row2][col2] + preSum[row1 - 1][col1 - 1] - preSum[row1 - 1][col2] - preSum[row2][col1 - 1];
        };
        dbg(preSum);

        dbg(sumRegion(0, 0, 1, 1));
        int row1 = 1;
        int col1 = 1;
        int row2 = 2;
        int col2 = 2;
        dbg(preSum[row2][col2], preSum[row1 - 1][col1 - 1], preSum[row1 - 1][col2], preSum[row2][col - 1]);
    };


    auto inPlaceAnswer = [&matrix, row, col] {

        for (int i = 1; i < row; ++i) {
            matrix[i][0] += matrix[i - 1][0];
        }
        for (int j = 1; j < col; ++j) {
            matrix[0][j] += matrix[0][j - 1];
        }
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                matrix[i][j] += matrix[i - 1][j] + matrix[i][j - 1] - matrix[i - 1][j - 1];
            }
        }
        dbg(matrix);

    };
    inPlaceAnswer();
    return 0;
}

void Offer::checkInclusion() {
    //给定两个字符串 pattern 和 text，写一个函数来判断 text 是否包含 pattern 的某个变位词。
    //换句话说，第一个字符串的排列之一是第二个字符串的 子串 。
    //pattern = "ab" text = "eidbaooo" true

    auto answer = [] {
        string pattern = "ab";

        string text = "eidboaoo";
        const int patternLen = pattern.size();
        const int textLen = text.size();

        std::vector<int> data(26);
        for (int i = 0; i < patternLen; ++i) {
            ++data[pattern[i] - 'a'];
        }
        int left = 0;

        int right = left;
        while (right < textLen) {
            dbg(data);
            int curPos = text[right] - 'a';
            --data[curPos];
            while (data[curPos] < 0) {
                int leftPos = text[left] - 'a';
                ++data[leftPos];
                ++left;
            }

            //到达匹配的位置处
            // 如果是部分匹配则 可知当前的 right-left+1 < patternLen
            if (patternLen == right - left + 1) {
                return true;
            }
            ++right;
        }
        return false;
    };
    dbg(answer());
}

int Offer::lengthOfLongestSubstring(string &s) {
    int cache[256]{};
    const int length = s.length();
    int left = 0;
    int right = 0;
    int result = 0;
    while (right < length) {
        const char cur = s[right];
        ++cache[cur];
        while (cache[cur] > 1) {
            const char leftPos = s[left];
            --cache[leftPos];
            ++left;
        }
        result = std::max(right - left + 1, result);
        ++right;
    }
    return result;
}

int Offer::countSubstrings() {
    // 回文子串的个数
    string varString = "abababaadhqjqqq";
    const int len = varString.length();
    int result = 0;
    // 中心点为 一时 有 len 个
    // 中心点 为二时 有 len-1 个 故为  2*len-1
    for (int cur = 0; cur < 2 * len - 1; ++cur) {
        int left = cur / 2;
        // right 可能为 中心点为两个元素
        // right 应该字符串的 长度相关 可能为 偶数 或者奇数
        int right = left + cur % 2;
        while (right < len and left >= 0 and varString[left] == varString[right]) {
            --left;
            ++right;
            ++result;
        }
    }
    return result;
}

void Offer::removeNthFromEnd() {
    const std::unique_ptr<ListNode> &ptr = Offer::ListNode::new_list(10);
    auto root = ptr.get();
    ListNode::printAll(root);
    auto a = ListNode(0, root);
    auto dummy = std::addressof(a);
    int n = 2;

    auto first = dummy;
    auto second = dummy;
    while (n-- != 0) {
        second = second->next;
    }
    while (second != nullptr) {
        second = second->next;
        first = first->next;
    }
    first->next = first->next->next;
    // dummy->left;
}

void Offer::maxPathSum() {
    // 二叉树的最大路径和
    int maximum = INT_MIN;
    auto answer = [](TreeNode *root, int &result, int count) {
        if (root == nullptr) return;

        return;
    };
}


