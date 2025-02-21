#include <iostream> 
#include <tbb/flow_graph.h>
#include "tbb/tbb.h"

int main() {

  tbb::flow::composite_node

  tbb::flow::graph g;

  tbb::flow::function_node<int, std::string> my_first_node(
      g, tbb::flow::unlimited, [](const int &in) -> std::string {
        std::cout << "first node received " << in << std::endl;
        return std::to_string(in);
      });
  tbb::flow::function_node<std::string> my_second_node(
      g, tbb::flow::unlimited, [](const std::string &in) {
        std::cout << "second node received " << in << std::endl;
      });
  // step 3 : make the edges
  tbb::flow::make_edge(my_first_node, my_second_node);

  // step 4 : send message
  my_first_node.try_put(10);

  // step 5 : wait for the graph to end
  g.wait_for_all();

  return 0;
};