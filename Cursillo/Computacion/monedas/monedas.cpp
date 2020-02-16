#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#include <cassert>
#include <cstdio>

using Solucion = std::array<int, 9>;

#define CRITERIO_LINDO 1
#define USAR_LINDO 1

#if CRITERIO_LINDO==0
std::vector<Solucion> encontrar_lindas (
	std::vector<Solucion> soluciones
) {
	std::vector<Solucion> soluciones_lindas;
	int fealdad = 9;
	for (auto const& sol : soluciones) {

		// salteo la solucion si tiene un cero
		if(*std::min_element(sol.begin(), sol.end()) < 1)
			continue;

		// cuantas veces aparece cada valor en la solucion?
		std::map<int, int> frecuencias;

		for(int val : sol){
			frecuencias[val] += 1;
		}

		// Cuantas veces aparece el valor mas frecuente?
		int mi_fealdad = frecuencias[sol[0]];
		for(auto& kv : frecuencias){
			mi_fealdad = std::max(mi_fealdad, kv.second);
		}

		// si mejoramos la solucion, eliminamos las otras
		if (mi_fealdad < fealdad){
			fealdad = mi_fealdad;
			soluciones_lindas.clear();
		}

		// si es igual de buena la agregamos a la lista
		if (mi_fealdad == fealdad) {
			soluciones_lindas.push_back(sol);
		}
	}

	return soluciones_lindas;
}
#else

std::vector<Solucion> encontrar_lindas (
	std::vector<Solucion> soluciones
) {
	std::vector<Solucion> soluciones_lindas;
	int fealdad = 50*50*9;

	for (auto const& sol : soluciones) {

		if(*std::min_element(sol.begin(), sol.end()) < 1)
			continue;

		int mi_fealdad = std::inner_product(
			sol.begin(), sol.end(), sol.begin(), 0);

		if (mi_fealdad < fealdad){
			fealdad = mi_fealdad;
			soluciones_lindas.clear();
		}

		if (mi_fealdad == fealdad) {
			soluciones_lindas.push_back(sol);
		}
	}

	return soluciones_lindas;
}
#endif

std::vector<Solucion> encontrar_soluciones (
	std::array<int, 3> const& row_sum,
	std::array<int, 3> const& col_sum
) {

	int bounds[3][3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			bounds[i][j] = std::min(col_sum[i], row_sum[j]);
		}
	}

	std::vector<Solucion> soluciones;

	for (int tl = 0; tl <= bounds[0][0]; ++tl) {
		for (int ml = 0; ml <= bounds[0][1]; ++ml) {
			int bl = col_sum[0] - tl - ml;
			if (bl < 0) break;
			for (int tm = 0; tm <= bounds[1][0]; ++tm) {
				int tr = row_sum[0] - tl - tm;
				if (tr < 0) break;
				for (int mm = 0; tm <= bounds[1][1]; ++mm) {
					int bm = col_sum[1] - tm - mm;
					int mr = row_sum[1] - ml - mm;
					if (bm < 0) break;
					if (mr < 0) break;
					int br = col_sum[2] - tr - mr;
					if (br < 0) continue;
					soluciones.push_back({tl, tm, tr, ml, mm, mr, bl, bm, br});
				}
			}
		}
	}

	return soluciones;
}


int main () {

	std::array<int, 3> row_sum = {13, 42, 36};
	std::array<int, 3> col_sum = { 7, 48, 36};

	std::vector<std::array<int, 9>> soluciones = encontrar_soluciones(row_sum, col_sum);

#if USAR_LINDO==1
	std::vector<std::array<int, 9>> soluciones_lindas = encontrar_lindas(soluciones);

	for(auto& s : soluciones_lindas){
		printf(
			"%2d %2d %2d\n"
			"%2d %2d %2d\n"
			"%2d %2d %2d\n\n",
			s[0], s[1], s[2],
			s[3], s[4], s[5],
			s[6], s[7], s[8]);
	}
#else
	for(auto& s : soluciones){
		printf(
			"%2d %2d %2d\n"
			"%2d %2d %2d\n"
			"%2d %2d %2d\n\n",
			s[0], s[1], s[2],
			s[3], s[4], s[5],
			s[6], s[7], s[8]);
	}
#endif

}
