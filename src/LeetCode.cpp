﻿#include "LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
#include <fmt/format.h>
#include <folly/Range.h>
#include <unordered_map>
#include <numeric>
#include <unordered_set>
#include <set>

using std::string;

void
LeetCode::fib() {
    constexpr auto answer = [] {
        constexpr int n = 3;
        constexpr auto fib_impl = [] {
            std::array<int, 31> fib{0, 1};
            for (int i = 2; i != 31; ++i) {
                fib[i] = fib[i - 1] + fib[i - 2];
            }
            return fib;
        }();

        return fib_impl[n];
    };
}

void
LeetCode::tribonacci() {
    //T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2
    constexpr auto fib_impl = [] {
        std::array<int, 37> fib{0, 1, 1};
        for (int i = 3; i != 31; ++i) {
            fib[i] = fib[i - 1] + fib[i - 2] + fib[i - 3];
        }
        return fib;
    }();
    auto answer = [&](int n) {
        return fib_impl[n];
    };
}

void
LeetCode::minCostClimbingStairs() {
    std::vector<int> data = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    const auto minCostClimbingStairsImpl = [](vector<int> &cost) {
        std::unordered_map<int, int> cache;
        const auto impl = [&](int cur, int spend, auto &&self) -> int {
            if (cur == cost.size()) {
                return spend;
            }
            if (cur > cost.size()) {
                return INT_MAX;
            }
            int msg = cur * 1000 + spend;
            if (cache.find(msg) != cache.end()) {
                return cache[msg];
            }
            cache[msg] = std::min(self(cur + 2, spend + cost[cur], self),
                                  self(cur + 1, spend + cost[cur], self));
            return cache[msg];
        };
    };
    const auto dpAnswer = [](vector<int> &cost) {

        // 将不同的元素的对应起来
        // dp[i]=min(dp[i-1]+cost[i-1],dp[i-2]+cost[i-2])


        // dp[i] 为到达第i级阶梯的所需要的最小代价 接着向上走则需要花费当前的cost[i]
        // 同时 有两种方法到达 相关的 从i-1 或者i-2位置向上走
        // dp[i] = min(dp[i-1]+cost[i-1] ,dp[i-2]+cost[i-2])

        int first = 0;
        int second = 0; //dp[0]  dp[1]
        for (int i = 2; i <= cost.size(); i++) //最后到达 size()处 需要多少
        {
            //到达 i 位置则
            int tmp = std::min(first + cost[i - 2], second + cost[i - 1]);
            first = second;
            second = tmp;
        }
        return second;
    };
}

void
LeetCode::findAnagrams() {
    //给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

    // 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
    /*
    * 输入: s = "cbaebabacd", p = "abc"
    输出: [0,6]
    */


    //auto findAnagramsEnum = [](string s, string p)->vector<int> {
    //	//  直接暴力匹配当前出现的字符串
    //	string::size_type sSize = s.size();
    //	string::size_type pSize = p.size();
    //	if (sSize < pSize)return {};
    //	std::array<int, 26> count_p = { 0 };
    //	for (char pChar : p) {
    //		count_p[static_cast<int>(pChar)] += 1;
    //	}
    //	std::array<int, 26> check_count = { 0 };


    //	int first = 0;
    //	int second = 1;
    //	check_count[static_cast<int>(s[0])] += 1;
    //	string::size_type lastFirst = sSize - pSize;
    //
    //	auto compare = [&]()->std::pair<int, int> {
    //		for (int i = 0; i < 26; i++)
    //		{
    //			if (count_p[i] == check_count[i]) {
    //				continue;
    //			}
    //			else if (count_p[i] > check_count[i]) {
    //				return { -1,i };
    //			}
    //			else {
    //				return { 1, i };
    //			}
    //		}
    //		return { 0,0 };
    //	};

    //	vector<int> result;
    //	while (first <= lastFirst and second < s.size())
    //	{
    //		auto compareResult = compare();
    //		if (compareResult.first == 0) {
    //			result.push_back(first);
    //			check_count[s[first]] -= 1;
    //			first++;
    //		}
    //		else if (compareResult.first > 0) {
    //			check_count[s[first]] -= 1;
    //			first++;
    //			if (first <= lastFirst) {
    //				check_count[s[first]] += 1;
    //			}
    //		}
    //		else {
    //			if(s[second] ==)
    //		}
    //	}

    ///std::equal(count_p.begin(), count_p.end(), check_count.begin(), check_count.end());
    //};


    string first = "abacbabc";
    string second = "abc";
    auto findAnagramsEnum = [](string s, string p) -> vector<int> {
        string::size_type sSize = s.size();
        string::size_type pSize = p.size();
        if (sSize < pSize)
            return {};
        std::array<int, 26> firstCount{};
        std::array<int, 26> secondCount{};
        for (int i = 0; i < pSize; i++) {
            firstCount[static_cast<int>(p[i] - 'a')]++;
            secondCount[static_cast<int>(s[i] - 'a')]++;
        }
        vector<int> result;
        if (std::equal(firstCount.begin(), firstCount.end(), secondCount.begin(), secondCount.end())) {
            dbg(firstCount, secondCount);
            result.push_back(0);
        }
        for (int i = pSize; i < sSize; i++) {
            // 将当前的 pSize 添加进入
            secondCount[static_cast<int>(s[i - pSize] - 'a')]--;
            secondCount[static_cast<int>(s[i] - 'a')]++;
            dbg(secondCount);
            if (std::equal(firstCount.begin(), firstCount.end(), secondCount.begin(), secondCount.end())) {
                result.push_back(i - pSize + 1);
            }
        }
        return result;
    };
    //dbg(findAnagramsEnum(first, second));


    const auto answerslidingWindow = [](string const &s, string const &p) -> vector<int> {
        // 将当前存在的 range 标识为 滑动窗口的 range
        string::size_type sSize = s.size();
        string::size_type pSize = p.size();
        if (sSize < pSize)
            return {};
        std::array<int, 26> firstCount{};
        std::array<int, 26> secondCount{};
        for (int i = 0; i < pSize; i++) {
            firstCount[static_cast<int>(p[i] - 'a')]++;
        }
        int left = 0;
        vector<int> result;
        for (int right = 0; right < sSize; right++) {
            // 将其填入当前所匹配的子串中
            int curGet = static_cast<int>(s[right] - 'a');
            secondCount[curGet]++;
            auto range = folly::Range(s.begin() + left, s.begin() + right + 1);
            auto cur = fmt::format(" left {} right {} cur {}", left, right, s[left]);
            dbg(cur, range);
            while (secondCount[curGet] > firstCount[curGet]) {
                //当前的填入的字符 超过了当前的总数
                // left 一直回退 直到当前情况下的 secondCount[curGet] ==firstCount[curGet]
                // 最坏情况是 left 到达了 right 位置

                auto range = folly::Range(s.begin() + left + 1, s.begin() + right + 1);
                int curLeft = static_cast<int>(s[left] - 'a');
                secondCount[curLeft]--;
                left++;
                string cur = fmt::format(" left-1 {} right {} cur {}", left - 1, right, left);
                dbg(range, cur);
            }
            if (right - left + 1 == pSize) {
                result.push_back(left);
                dbg("result.push_back(left) " + std::to_string(left));

            }

        }
        return result;

    };
    dbg(answerslidingWindow("cbaebabacd", "abc"));
}

void
LeetCode::numSubarrayProductLessThanK() {

    // 双指针 将当前的窗口缩小到合适位置
    const auto answerDp = [](vector<int> &nums, int k) -> int {
        int cur = 1;
        int left = 0;
        int result = 0;
        vector<int>::size_type numSize = nums.size();
        for (int right = 0; right < numSize; right++) {
            cur = cur * nums[right];
            if (cur < k) {
                if (right > left + 1) { //包含了多个元素的成绩证明可以添加多个进入
                    result += right - left + 1;
                    const auto &range = folly::Range(
                            nums.begin() + left, nums.begin() + right + 1);
                    dbg(range, left, right);
                } else {
                    result++;
                }
            }
            while (cur > k) {
                // 左侧指针前进到
                cur /= nums[left];
                left++;
            }

        }
        return result;
    };
    std::vector<int> data = {10, 5, 2, 6};
    answerDp(data, 100);
}

void
LeetCode::allPathsSourceTarget() {
    auto answer = [](vector<vector<int>> &graph) -> vector<vector<int>> {
        size_t graphSize = graph.size();
        std::vector<std::vector<int>> result;
        std::vector<int> curResult;
        auto dfs = [&](int curPos, auto &&dfs) -> void {
            curResult.push_back(curPos);
            if (curPos == graphSize - 1) {
                result.push_back(curResult);
            } else {
                for (int nextPos: graph[curPos]) {
                    dfs(nextPos, dfs);
                    result.pop_back();
                }
            }
        };
        dfs(0, dfs);
        return result;
    };
}

void
LeetCode::findTargetSumWays() {

    auto answer_ = [](vector<int> &nums, int target) {

        int result = 0;
        //  dfs

        std::vector<int> data{1, 1, 1, 1, 1};
        // 递归lambda表达式
        auto dfs = [&](int index, int cur, auto dfs) {
            if (index == data.size()) {
                if (cur == target) {
                    result++;
                }
                return;
            }
            dfs(index + 1, cur + data[index], dfs);
            dfs(index + 1, cur - data[index], dfs);
        };
        // 动态规划
        auto dynamic = [&]() {
            int sum = 0;
            for (int num: nums)
                sum += num;
            if (pow(sum, 2) < pow(target, 2) || (sum + target) % 2 == 1)
                return 0;
            target = (sum + target) / 2;
            vector<int> dp(target + 1);
            dp[0] = 1;
            for (int num: nums) {
                for (int i = target; i >= num; i--) {
                    dp[i] = dp[i] + dp[i - num];
                }
            }
            return dp[target];
        };
    };
}

void
LeetCode::remove_all_words() {
    vector<string> words = {"owuxnmzhus", "umhowszxun"};
    // 删除对应字母的 异位词
    vector<long> con;
    con.reserve(words.size());
    constexpr int cur[26] = {
            2,
            3,
            5,
            7,
            11,
            13,
            17,
            19,
            23,
            29,
            31,
            37,
            41,
            43,
            47,
            53,
            59,
            61,
            67,
            71,
            73,
            89,
            97,
            101,
            103,
            107,
    };
    for (auto begin = words.begin(); begin != words.end(); ++begin) {
        double count = 1;
        for (char i: *begin) {
            count *= cur[i - 'a'];
        }
        con.emplace_back(count);
    }
    for (int i = 1; i < words.size(); ++i) {
        while (i - 1 >= 0 and i < con.size() and con[i] == con[i - 1]) {
            //触发删除操作
            con.erase(con.begin() + i);
            words.erase(words.begin() + i);
            dbg(i, words, con);
        }
    }
}

int
LeetCode::maxConsecutive(int bottom, int top, vector<int> &special) {
    std::sort(special.begin(), special.end());
    int count = 0;
    int cur = 0;
    auto size = special.size();
    int max = 0;
    for (int i = bottom; i <= top; ++i) {

        if (cur < size and i == special[cur]) {
            ++cur;
            if (count > max) {
                max = count;
            }
            count = 0;
        } else {
            // 前进n 步  首先当前就不等于
            if (cur < size) {
                count = special[cur] - i;
                i = special[cur] - 1;
            } else {
                count = top - i + 1;
                i = top;
            }
        }

        if (count > max) {
            max = count;
        }
    }
    return max;
}

int
LeetCode::largestCombination() {
    vector<int> candidates{16, 17};
    auto size = candidates.size();
    if (size == 1)
        return candidates[0];
    int maxElem = *std::max_element(candidates.begin(), candidates.end());
    double forwardBits = std::log2(maxElem) + 1;
    int max = 1;
    for (int i = 0; i < forwardBits; ++i) {
        int cur = 1 << i;
        int count = 0;

        for (int a: candidates) {
            if ((a & cur) != 0)
                ++count;
        }

        if (count > max) {
            max = count;
        }
    }
    dbg(max);
    return max;
}

void
LeetCode::digitSum() {
    string data = "11111222223";
    int k = 3;

    while (data.size() > k) {
        for (int i = 0; i < data.size();) {
            dbg(data);
            int cur = 0;
            for (int j = 0; j < k and i + j < data.size(); ++j) {
                cur += data[i + j] - '0';
            }
            int count = std::min(static_cast<int>((data.size() - i)), k);
            dbg(i, count);
            const string &Right = std::to_string(cur);
            data.replace(i, i + count, Right);

            i += Right.size();
            data.erase(i, count - k);// 将实验上的部分给结束
            i += k;
        }

    }
    dbg(data);

}

void
LeetCode::intersection() {
    // vector<vector<int>>& nums
    vector<vector<int>> nums;
    std::unordered_set<int> cur;
    std::unordered_set<int> other;
    for (int &i: nums[0]) {
        cur.insert(i);
    }
    for (int i = 1; i < nums.size(); ++i) {
        for (int v: nums[i]) {
            if (cur.find(v) != cur.end()) {
                other.insert(v);
            }
        }
        cur = std::move(other);
        other.clear();
    }
    vector<int> result(cur.begin(), cur.end());
}

void
LeetCode::countLatticePoints() {
    // 遍历所有节点
    //vector<vector<int>>& circles
    vector<vector<int>> circles = {{2, 2, 2},
                                   {3, 4, 1}};
    int result = 0;
    if (circles.size() == 1) {
        result = 5;
        return;
    }
    // 一个 set fixme 错位枚举法
    {
        struct PairHash {
            size_t
            operator()(const std::pair<int, int> &p) const {
                return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
            }
        };
        std::unordered_set<std::pair<int, int>, PairHash> set;
        // 1/4 的数量

        const auto one_circle = [&set](const vector<int> &circle) {
            std::pair<int, int> center{circle[0], circle[1]};
            int radius = circle[2];
            // 添加五个点进入数组中去
//        set.reserve(set.size()+5);
            set.insert(center);
            set.insert({center.first - radius, center.second});
            set.insert({center.first + radius, center.second});
            set.insert({center.first, center.second - radius});
            set.insert({center.first, center.second + radius});
            // 判断最大的正方体的区域的点
            std::pair<int, int> rightTop{center.first + radius - 1, center.second + radius - 1};
            while (rightTop.first != center.first and rightTop.second != center.second) {
                double distance = std::sqrt(
                        std::pow(rightTop.first - center.first, 2) +
                        std::pow(rightTop.second - center.second, 2));

                if (distance < radius) {
                    // 确定又上顶点 将顶点加入到set 中去
                    int startX = rightTop.first - (rightTop.first - center.first) * 2;
                    int endY = rightTop.second - (rightTop.second - center.second) * 2;
//                dbg(startX, endY)
                    for (int x = startX; x <= rightTop.first; ++x) {
                        for (int y = rightTop.second; y >= endY; --y) {
                            set.insert({x, y});
                        }
                    }
                    break;
                }
                --rightTop.first;
                --rightTop.second;
            }

        };
        for (const vector<int> &circle: circles) {
            one_circle(circle);
        }

        dbg(set);
        string dbg_str;
        for (auto i: set) {
            dbg_str.append("[" + std::to_string(i.first) + "," + std::to_string(i.second) + "]");
        }
        dbg(dbg_str);
    }
//    return set.size();

    // 差分方法
    int mx = circles[0][0];
    int my = circles[0][1];
    for (const auto &v: circles) {
        if (v[0] > mx)
            mx = v[0];
        if (v[1] > my)
            my = v[1];
    }
    dbg(mx, my);
    vector<vector<int>> diff(mx + 2, vector<int>(my + 1));
    for (const vector<int> &data: circles) {
        int curX = data[0];
        int curY = data[1];
        int radius = data[2];
        for (int y = curY - radius; y <= curY + radius; ++y) {
            int z = floor(sqrt(radius * radius - (y - curY) * (y - curY)));
            dbg(z);
            diff[curX - z][y] += 1;
            diff[curX + z + 1][curY] -= 1;
        }
        dbg(diff);
    }
    result = std::accumulate(diff.begin(),
                             diff.end(),
                             0,
                             [](int a, const vector<int> &val) {
                                 return a + std::accumulate(val.begin(),
                                                            val.end(),
                                                            0,
                                                            [](int c, int a) { return c + (a > 0 ? 1 : 0); });
                             });

}

