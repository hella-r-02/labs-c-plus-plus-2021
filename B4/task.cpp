#include <vector>
#include <algorithm>
#include <iterator>

#include "dataStruct.hpp"

void task(std::istream& in, std::ostream& out)
{
  std::vector<DataStruct> vector;
  std::for_each(std::istream_iterator<DataStruct>(in), std::istream_iterator<DataStruct>(), [&](const DataStruct& dataStruct)
                {
                  vector.push_back(dataStruct);
                });

  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(out));
}
