/*
 * TASK: You are given a directed graph. Given a root node of this graph (i.e.,
 *       a node which can reach any other node), clone the original graph.
 *
 * NOTE: This question is slightly more general than the original one, but the
 *       added generality does not add significant complexity to the problem.
 */

#include <algorithm>
#include <cassert>
#include "node.h"

/**
 * @brief Generates a random graph with n nodes and returns a pointer to the
 *        first generated node (a root node).
 * @note Complexity: O(n) in both time and space.
 */
node* random_graph(const size_t n)
{
    if (n == 0)
    {
        return nullptr;
    }

    static std::random_device device;
    static std::mt19937 generator(device());

    /* the first generated node is the root */
    std::vector<node*> nodes = {new node(0)};

    while (nodes.size() < n)
    {
        std::uniform_int_distribution<size_t> node_chooser(0, nodes.size() - 1);

        node* new_node = new node(nodes.size());

        size_t index = node_chooser(generator);
        nodes[index]->connect(new_node);

        nodes.push_back(new_node);
    }

    return nodes.front();
}

int main()
{
    for (size_t n = 1; n <= 50; ++n)
    {
        for (int i = 0; i < 1000; ++i)
        {
            node* n1 = random_graph(n);
            node* n2 = n1->clone();

            assert(equal(n1, n2) == true);

            delete n1;
            delete n2;
        }

        std::cout << "passed random tests for graphs of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
