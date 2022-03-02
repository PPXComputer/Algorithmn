#include "../include/LeetCode.h"
#include <dbg.h>
#include <cassert>
#include <array>
#include <fmt/format.h>
void LeetCode::medium_33()
{
	//旋转后的数组 
	auto impl = []() {
		std::array<int, 7> nums{ 4,5,6,7,0,1,2 };
		int target = 0;
		int left = 0; int right = nums.size() - 1;
		while (left < right)
		{
			int mid = ((right - left) >> 1) + left;
			dbg(left, right, mid, nums[mid]);
			if (target == nums[mid]) return mid;
			if (nums[mid] <= nums[right]) // 右侧有序
			{
				if (target <= nums[right] and target > nums[mid]) {
					left = mid + 1;
				}
				else {
					//向左边找
					right = mid - 1;
				}

			}
			else { //左侧有序
				if (target >= nums[left] and target < nums[mid]) {
					right = mid - 1;
				}
				else {
					//向右边找
					left = mid + 1;
				}
			}
		}
		if (nums[left] == target)return left;
		return -1;
	};
	dbg(impl());
}
void LeetCode::medium_34()
{
	using std::vector;
	auto answer = [](vector<int>& nums, int target)->vector<int> {
		if (nums.empty())return { -1,-1 };
		int left = 0;
		int right = static_cast<int>(nums.size() - 1);
		while (left < right) {
			//找到第一个出现target的地方
			int mid = left + ((right - left) >> 1);
			dbg(left, right, mid, nums[mid]);
			if (nums[mid] > target) {
				right = mid - 1;
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				right = mid; //等于则不动 可能他就是第一个
			}
		}
		if (nums[left] != target)return { -1,-1 };
		int left_result = left;
		left = 0; right = static_cast<int>(nums.size() - 1);

		while (left < right) {
			//找到最后一个出现target的地方
			int mid = left + ((right - left) >> 1) + 1; //向右侧偏移一格 向右边靠
			dbg(left, right, mid, nums[mid]);
			if (nums[mid] > target) {
				right = mid - 1;
			}
			else if (nums[mid] < target) {
				left = mid + 1;
			}
			else {
				left = mid;
			}

		}
		return { left_result,left };
	};
	vector<int>data{ 5, 7, 7, 8, 8, 10 };
	dbg(answer(data, 8));
}

void LeetCode::medium_74()
{
	std::array<std::array<int, 4>, 3> matrix = {
		std::array<int,4>{1,3,5,7},
		{10,11,16,20},
		{23,30,34,60}
	};
	// 将当前的搜索 转换为二维坐标
	int left = 0;
	constexpr size_t matrix_column = matrix.front().size();
	constexpr size_t matrix_row = matrix.size();
	int right = static_cast<int> (matrix_row * matrix_column - 1);
	int target = 3;
	auto transform_really_pos = [](int pos, int row, int column)->std::pair<int, int> {
		assert(pos >= 0 and pos < row* column);
		return { pos / column,pos % column };
	};
	auto find = [&]() {
		while (left < right)
		{
			int mid = ((right - left) >> 1) + left;
			dbg(fmt::format("{} {} {} ", left, right, mid));
			auto pos = transform_really_pos(mid, matrix_row, matrix_column);
			dbg(fmt::format("{}", matrix[pos.first][pos.second]));
			if (matrix[pos.first][pos.second] == target) {
				return true;
			}
			else if (matrix[pos.first][pos.second] > target) {
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}
		auto pos = transform_really_pos(left, matrix_row, matrix_column);
		return matrix[pos.first][pos.second] == target;

	};
	dbg(find());

}

void LeetCode::reverseKGroup()
{
	constexpr int length = 10;
	std::unique_ptr<ListNode> root_ptr = LeetCode::ListNode::new_list(length);
	ListNode* root = root_ptr.get();
	//多个值相连
	//旋转当前中最近的数据
	int k = 4;
	int time = length / 4;
	int count = 0;


	// 翻转后的 头  尾 和后一个元素
	auto reverse_list = [](ListNode* start, int need) {
		ListNode* head = nullptr;
		ListNode* cur = nullptr;
		int repeat_time = 0;
		std::tuple<ListNode*, ListNode*, ListNode*> result{ nullptr, start,nullptr };
		while (repeat_time != need)
		{
			cur = start->next;
			start->next = head;
			head = start;
			start = cur;
			repeat_time++;

			bool isLastTime = repeat_time == need;
			if (isLastTime)
			{
				//将当前最后一个的元素保留下来
				std::get<0>(result) = head;
				std::get<2>(result) = cur;
			}
		}
		return result;
	};

	ListNode* result = nullptr;
	ListNode* lastTail = nullptr;
	ListNode* lastStart = root;
	if (time > 0 and length != 1) {
		int start = 0;
		while (time != start) {
			auto result_tuple = reverse_list(lastStart, k);
			if (start == 0) {
				result = std::get<0>(result_tuple); //将结果保存
			}
			else {
				if (lastTail)lastTail->next = std::get<0>(result_tuple);

			}
			lastStart = std::get<2>(result_tuple);
			lastTail = std::get<1>(result_tuple);
			start++;
		}
	}


}

void LeetCode::findPeakElement()
{ //爬坡 不断向旁边最高前进
	vector<int> data{ 1,2,1,3,5,6,4 };
	int left = 0; int right = data.size() - 1;
	while (left < right) {
		int mid = ((right - left) >> 1) + left;

		dbg(fmt::format("{} {} {} ", left, right, mid));
		dbg(fmt::format("{} {} {} ", data[left], data[right], data[mid]));

		if (data[mid] < data[static_cast<size_t>(mid + 1)])
		{
			left = mid + 1;
		}
		else {
			right = mid; // 保留当前位置的点
		}
	}
	dbg(left);

}

void LeetCode::findMin()
{
	std::vector<int> data = { 3,4,5,1,2 };
	//找到旋转数组的最小值
	// 找到当前每次中到达的数据点 找到一个数当前的 左边的数大于他 右边的数小于他
	auto ans = [](vector<int>& nums) {
		// 一边有序的数组
		int left = 0;
		int right = static_cast<int>(nums.size() - 1);

		while (left < right)
		{
			int mid = ((right - left) >> 1) + left;
			dbg(fmt::format("{} {} {} ", left, right, mid));
			dbg(fmt::format("{} {} {} ", nums[left], nums[right], nums[mid]));
			if (nums[mid] < nums[right])
				right = mid;
			else
				left = mid + 1;

		}
		dbg(nums[left]);

	};
	ans(data);

}

void LeetCode::deleteDuplicatesFromList()
{
	//给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
	std::vector<int> data = { 1,1,2,2 };
	std::unique_ptr<ListNode> ptr = ListNode::new_list(data);
	auto head = ptr.get();
	auto answer_forward = [&]() {
		auto root = head;
		if (root == nullptr)return head;
		int val;
		auto cur = root->next;
		ListNode* prev = root;
		bool isFirstTime = true;
		while (cur != nullptr) {
			val = root->val;

			if (val == cur->val) {
				while (cur != nullptr and cur->val == val) {
					cur = cur->next;
				}

				if (prev == root) {
					if (cur == nullptr)return  static_cast<ListNode*>(nullptr);
					else {
						head = cur;
						prev = cur;
						root = cur;
					}
				}
				else
				{
					prev->next = cur;
					root = cur;
				}
				if (cur == nullptr)break;
				cur = cur->next;

			}
			else {
				prev = root;
				root = cur;
				cur = cur->next;
			}

		}
		return head;
	};
	//answer_forward();
	auto answer_dummpy_head = [&]() {
		auto root = head;
		if (root == nullptr)return head;
		auto dummy = std::make_unique<ListNode>(0, head);
		auto cur = dummy.get();
		while (cur->next != nullptr and cur->next->next != nullptr)
		{
			if (cur->next->val == cur->next->next->val) {
				auto forward = cur->next->next;
				do { forward = forward->next; } while (forward != nullptr and forward->val != cur->next->val);
				cur->next = forward;
			}
			else {
				cur = cur->next;
			}
		}
		return dummy->next;
	};
}

void LeetCode::three_num()
{
	// 找到所有和为 0的不重复的三元组
	std::vector nums = { -1,0,1,2,-1,-4 };
	
	auto answer = [&]()->std::vector<std::vector<int>> {
		if (nums.size() < 3)return {};

	};
}
