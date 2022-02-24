//
// Created by 破忆断回 on 2021/9/24.
//

#ifndef SSH_LISTAGLO_H
#define SSH_LISTAGLO_H

#include "folly/FBString.h"
#include "folly/FBVector.h"
#include "folly/String.h"
#include <iostream>
#include <array>
#include <fmt/format.h>
#include <folly/Format.h>

using folly::fbstring;
using folly::fbvector;
using folly::Optional;
using std::addressof;
using std::array;
using std::cout;
using std::string_view;

class ListAlgo {
public:
    struct Node {
        Node *next = nullptr;
        int value = 0;
    };

    struct BinaryTreeNode {
        using UniquePtr = std::unique_ptr<BinaryTreeNode>;
        UniquePtr left = nullptr;
        UniquePtr right = nullptr;
        int value = 0;

        BinaryTreeNode(int v) : value{v}, left{nullptr}, right{nullptr} {}

        static UniquePtr New(int value) {
            return std::make_unique<BinaryTreeNode>(value);
        }
    };

    static void get_node_counter();

    static void create_tree();

    static void partition_list_by_value();

    static void deal_three_list(Node *root, int target);

    static void partition_other();

private:
    static void deal_back(Node *cur, Node *tail_node, Node *head);

    static Node *deal_front(Node *root, Node *cur, Node *tail_node);

    static Node *get_tail_node(Node *pNode); // note 安装值来划分链表
};

#endif // SSH_LISTAGLO_H
