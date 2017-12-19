// AlgorithmModule.cpp: 定义 DLL 应用程序的导出函数。
//

#include "algorithm_module.h"

namespace GraphAlgorithm {

	PUBLIC PathType
		bfs(
			int idx_start_v, int idx_dest_v,
			const FirstEdgeAdapter & firstOf, const NextEdgeAdapter & nextOf,
			const EdgeToAdapter & destOf) {

		std::list<int> indexList{ idx_start_v };
		std::unordered_map<int, int> prevOf{ std::make_pair(idx_start_v,NIL) };
		std::unordered_map<int, int> prevEdgeOf{ std::make_pair(idx_start_v,NIL) };

		for (int v : indexList) {
			if (v == idx_dest_v) {
				PathType ret;
				for (int u = v; u != NIL; u = prevOf[u]) {
					ret.first.push_front(u);
					ret.second.push_back(prevEdgeOf[u]);
				}
				ret.second.pop_front(); //prevEdgeOf[idx_start_v] == NIL
				return ret;
			}
			if (v != idx_start_v) indexList.pop_front();

			for (int edge = firstOf(v); edge != NIL; edge = nextOf(v, edge)) {
				const int v1 = destOf(v, edge);

				if (prevOf.count(v1) != 0) continue;

				prevOf.insert(std::make_pair(v1, v));
				prevEdgeOf.insert(std::make_pair(v1, edge));
				indexList.push_back(v1);
			}
		}
		return NIL_PATH;
	}
}
